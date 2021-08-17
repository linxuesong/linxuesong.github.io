---
title: Java中祖先类Object提供的基础方法
author: linxuesong
avatar: 'https://cdn.jsdelivr.net/gh/linxuesong/cdn/img/avatar.jpg'
authorLink: linxuesong.github.io
authorAbout: 一个好奇的人
authorDesc: 一个好奇的人
categories:
  - 技术
comments: true
tags:
  - JAVA
photos: >-
  https://cdn.jsdelivr.net/gh/linxuesong/cdn/img/articleCover/动漫风景/apic-in 色彩绚丽的风景动漫图片 (20).jpg
date: 2021-04-09 15:28:30
keywords:
description:
---

| 函数声明                          | Object中作用                         | 子类重写作用                                                 |
| --------------------------------- | ------------------------------------ | ------------------------------------------------------------ |
| boolean **equals** (Object other) | 两个对象的引用是否相等，而非其实例域 | 比较子类的两个对象其内容是否相等                             |
| String hashCode()                 | 由对象导出的散列码                   |                                                              |
| String **toString** ()            | 返回对象类名和散列码                 | 方便打印对象变量的实际内容，在JAVA语句中+x或x可以自动转为x.toString() |
| Class getClass ()                 | 返回包含对象信息的类对象             |                                                              |
| String getName()                  | 获取类名字                           |                                                              |



