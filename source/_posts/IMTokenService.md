# 问题背景

日志回捞使用流程发生改变 原有情况:业务方同学标记-》用户重启设备，检测是否标记-》上传日志-》查询日志， 日志由手动标记触发，数量少(几万条) 现有情况：VR、车商通直接调用接口上传日志文件，日志有接口调用产生，数量大(一百多万条)

# 解决方案

## 1.清楚不必要数据

子线程定时执行deleteTbLog函数，VR、车商通app保留7天，其他app保留62天。

## 2.针对查询条件增加前缀索引

查询条件

```
WHERE
  1 = 1
  and deviceId in (
    '0f6468ec9ea9ee74',
    '496d866694acba56',
    '64e14c1e8d69c46c',
    '6a086681e1346b95',
    '756d76a7a81daa66'
  )
  and category = '0'
  and app = 'com.anjuke.android.newbroker'
  and type = 'android'
  and starttime >= '20210524'
  and endtime <= '20210524'
ORDER BY
  uploadtime desc
LIMIT
  0, 10
```

一般业务线会指定deviceid，所以对该列加上索引。

因为列类型为varchar(255),编码为utf-8，字节长度为255*3(一个字符3字节),所以长度超过756byte限制，加前缀索引

前15字符可以代替所有deviceid

最后表的索引结构如下

```
PRIMARY KEY (`id`),
  KEY `idx_app` (`app`),
  KEY `idx_uptime` (`uploadtime`),
  KEY `idx_deviceId` (`deviceId`(15))
```

## 3.增加redis缓存

mysql原有查询语句为

```
WHERE 
? = ? 
AND `deviceId` IN (?) 
AND `category` = ? 
AND `app` = ? 
AND TYPE = ? 
AND `starttime` >= ? 
AND `endtime` <= ? 
AND `batchMark` = ? 
ORDER BY `uploadtime` 
DESC LIMIT ?
```

mysql业务场景为读少，写多。读时比较慢，在写的时候针对未来读的查询条件加上缓存，可以增加未来的读的效率

redis存储使用sorted set,zrangewithscore范围查找代替一个范围筛选条件,其余筛选按照逻辑比较

上传uploadLog接口写redis缓存如下：

![image-20210723162641302](https://raw.githubusercontent.com/linxuesong/TyporaPictures/master/img/image-20210723162641302.png)

上传方案存在的一个问题：设备A在redis中有日志1、2，新上传日志3，在写redis时失败redis信息较mysql中少，这种情况怎么处理？ redis和mysql数据同步问题，可有消息队列定时同步解决，但是实现太过复杂，实际出现redis失败情况，人工去mysql查。

存储到redis中的有序集合的member为JsonObject

| 字段           | 是否一定有值 |
| -------------- | ------------ |
| id             | 必有值       |
| deviceId       | 必有值       |
| type           | 必有值       |
| app            | 必有值       |
| category       | 必有值       |
| starttime      | 必有值       |
| endtime        | 必有值       |
| os_version     |              |
| logsdk_version |              |
| uploadtime     | 必有值       |
| batchMark      |              |
| os_version     |              |
|                |              |

下载查询日志downLoadLog接口读redis缓存如下：<br/> ![image-20210720161428968](https://raw.githubusercontent.com/linxuesong/TyporaPictures/master/img/image-20210720161428968.png)

ToDo: 上述方案存在问题 <br/> 问题一： zadd、expire为绑定原子操作，如果半个月内同设备连续上传，半月前上传的旧日志记录会被持久保存？ <br/> 解决方案： <br/> 方案一 查redis时如果最终redis的查询结果存在半个月前上传旧日志记录，认为当前的redis缓存失效，删除key，重新存   问题是如果一直不查redis内存就一直无法清除 <br/> 方案二 在存的时候同时读取该redis所有的日志记录，把uploadtime半个月前的mem清理掉 <br/>方案三 使用uploadtime作为score 推翻 <br/>方案四 定时清理任务，需要遍历整个redis并做json转换条件比较 综上，对于问题一使用方案二解决，仅对特定的key做操作 <br/> 方案五 只对自动上传的app执行设方案二，对其他app不执行方案二
# 测试报告
![image-wlog加入redis缓存测试报告](https://wos.58cdn.com.cn/pQnMlKjpQSW/iwikibucket/v1.1_ad6b16914d88387f5a330445eb11470f_wlog%E5%A2%9E%E5%8A%A0redis%E7%BC%93%E5%AD%98%E7%9A%84%E6%B5%8B%E8%AF%95%E6%8A%A5%E5%91%8A.png)

# 上传接口的优化方案

### 背景

增加redis缓存后，对于如VR每天连续上传日志的app，上传接口会开启一个线程删除7天前的redis以保证set的大小合理

### 存在的问题

对于上传接口如果并发请求量过大会出现开启线程数量过多的问题

### 解决方法

#### 方案一

1.对于相同的key，一天定时清理一次就可以了，标记当前是否清除过，根据是否标记过决定是否需要开线程清除

同一device减少清除的次数

2.对于不同的key

- 使用有界的线程池执行，防止高请求量时开线程。 缺点，当并行度不足时会让丢弃任务
- 使用无界的线程池，存在内存不足的危险

#### 方案二

运用方案一中相同key的处理方式加上如下的处理

使用redis或者wmb作为全局任务队列
   1.上传请求发生时，将删除任务放入redis,     lpush

   2.同时lpop取出一个删除任务开始执行
