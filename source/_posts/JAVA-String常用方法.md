---
title: JAVA String和StringBuilder常用方法
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
  - JAVA
  - String
photos: >-
  https://cdn.jsdelivr.net/gh/linxuesong/cdn/img/articleCover/鬼刃/200929110029-3-1200.jpg
date: 2021-04-08 16:02:34
keywords:
description: 介绍JAVA不可变字符串常用方法
---

# 一、String不可变字符串

## 1.int compareTo(String other) 比较两字符串大小

## 2.boolean equals(Object object)比较两字符串是否其内容一致

==比较运算符比较的是引用位置是否相等，而非其内容

## 3.boolean endsWith(String suffix)和Boolean startsWith(String prefix)以指定字符串开始或结尾返回true

## 4.int indexOf(String str)返回与指定字符串匹配的首个位置

如果还要其他要求，是有函数重载的

## 5.int length()字符串长度

## 6.String toLowerCase()和String toUpperCase()大小写转换

## 7.String trim()删除原始字符串头部和尾部的空格

更多方法可以参考Java的官网api文档

# 二、StringBuilder

string问题是每次做字符串拼接都会产生一个新的String对象，这样既耗时又费空间

使用StringBuilder则可以避免这个问题发生

## 1.String toString()转为字符串

## 2.StringBuilder insert(int offset， String str) 指定位置插入自负传

## 3.void setCharAt(int i， char c)设置指定位置字符

## 4.StringBuilder append（String str）追加字符串在尾部