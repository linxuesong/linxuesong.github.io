---
title: JAVA异常机制
author: linxuesong
avatar: 'https://cdn.jsdelivr.net/gh/linxuesong/cdn/img/avatar.jpg'
authorLink: linxuesong.github.io
authorAbout: 一个好奇的人
authorDesc: 一个好奇的人
categories:
  - 技术
comments: true
tags:
  - 异常
  - java
photos: >-
  https://cdn.jsdelivr.net/gh/linxuesong/cdn/img/articleCover/动漫风景/images (10).jpg
date: 2021-04-14 17:16:25
keywords:
description: Java语法异常机制的说明及规范
---

# 一、异常

异常有两种选择：throws和catch，一种是抛给调用者，另一种是在本方法中捕获处理。

选择标准：如果知道如何处理就catch，不知道如何处理就throws

异常种类：Throwable是父类，                   <br/>					1⃣️Error子类是系统错误不可控，所以不用抛出、不用处理<br/>                    2⃣️Exception/RuntimeException是可控的要被控制,我们的代码不应有数组越界等错误
                    3⃣️Exception/IOException是文件读写错误，类加载错误<br/>

1⃣️2⃣️是不需要throws和catech的，3⃣️是需要throws或catch的,并且如果throws要列出所有可能抛出的IOException





```
public static void func1() throws IOException {//列出所有可能抛出的的IOException
  try{
     //检测代码
  }catch(FileNotFoundException | UnKonwHostException) {
  	// 处理捕获异常
  	throw new ServeletException("xx"); //也可以再次抛出异常
  }finally {
  	//最后一定执行的代码，常做一些关闭文件，释放资源的事情， 对于close也可能爆出异常，对此可以用带资源的try语句，保证最后关闭资源
  }
}
```

# 二、日志

将提示信息按照不同级别打印到指定文件中

## 1.JDK的Logging

```
import java.io.UnsupportedEncodingException;
import java.util.logging.Logger;
public class Main {
    public static void main(String[] args) 
        Logger logger = Logger.getLogger(Main.class.getName());
        logger.info("Start process...");
        try {
            "".getBytes("invalidCharsetName");
        } catch (UnsupportedEncodingException e) {
            // TODO: 使用logger.severe()打印异常
        }
        logger.info("Process end.");
    }
}
```

如果要打印到指定文件需要修改配置文件，JVM启动时传递的参数-Djava.util.logging.config.file=config-file-name

## 2.Commons Logging和Log4j

参考https://www.liaoxuefeng.com/wiki/1252599548343744/1264739436350112

## 3.SLF4J和Logback

https://www.liaoxuefeng.com/wiki/1252599548343744/1264739155914176