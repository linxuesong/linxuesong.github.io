---
title: Redis常用命令整理
author: linxuesong
avatar: 'https://cdn.jsdelivr.net/gh/linxuesong/cdn/img/avatar.jpg'
authorLink: linxuesong.github.io
authorAbout: 一个好奇的人
authorDesc: 一个好奇的人
categories:
  - 技术
  - 主题
comments: true
tags:
  - Reids
photos: >-
  https://cdn.jsdelivr.net/gh/linxuesong/cdn/img/articleCover/动漫风景/images (7).jpg
date: 2021-04-01 14:59:02
keywords:
description:
---

# 0.前言及Redis的链接

redis缓存数据库，主要存放key-value键值对，其中key为字符串，value可为多种类型**字符串**、**列表**、**集合**、**字典**

# 1.设置字符串

```
set key value
get key value
```

# 2.设置列表

```
lpsuh key childElement // 头部插入
lpop  key // 头部删除
lrang key 0 10 // 从头部开始查询到10

// 注：尾部操作则将lpush替换成rpush
// 头部插入的下表说明，头部入A、B、C
下标:  0、  1、   2
元素:  A、  B、   C
下标:  -3、 -2、  -1
```

# 3.设置集合

集合分为无序集合和有序集合(元素含权重)，集合元素个数为2的32次方-1个

无序集合

```
sadd key member  // 添加元素
smemebers key    // 查询所有元素
scard key        // 获取集合中元素个数
sdiff key1 key2  // 差集
sinter key1 key2 // 集合的交集运算
sunion key1 key2 // 集合的补集
```

有序集合（元素含权重）

```
将sadd改为zadd极为有序集合
zadd key score member // 添加元素，score为元素权重
```

# 4.key的其他操作（移除、过期时间、检测）

```
del key   // 删除key
exist key // 检测key是否存在
type key // 查看key类型
expire   // 设置过期时间
persist key // 持久化key，移除key过期时间
ttl key   // 查寻key的剩余过期时间
```

# 5.Redis发布和订阅

# 6.Redis事务

# 7.Redis脚本

