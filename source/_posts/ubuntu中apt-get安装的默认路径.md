---
title: ubuntu中apt-get安装的默认路径
author: linxuesong
avatar: 'https://cdn.jsdelivr.net/gh/linxuesong/cdn/img/avatar.jpg'
authorLink: linxuesong.github.io
authorAbout: 一个好奇的人
authorDesc: 一个好奇的人
categories: 
  - [转载]
  - [技术]
comments: true
photos: >-
  https://cdn.jsdelivr.net/gh/linxuesong/cdn/img/articleCover/动漫风景/apic-in 色彩绚丽的风景动漫图片 (2).jpg
date: 2021-03-01 11:12:51
tags:
  - [linux]
keywords:
description:
---

博客源地址：https://blog.csdn.net/yanhx1204/article/details/54893581

# 一、apt-get 安装

deb是debian linus的安装格式，跟red hat的rpm非常相似，最基本的安装命令是：dpkg -i file.deb或者直接双击此文件

dpkg 是Debian Package的简写，是为Debian 专门开发的套件管理系统，方便软件的安装、更新及移除。所有源自Debian的Linux发行版都使用dpkg，例如Ubuntu、Knoppix 等。
以下是一些 Dpkg 的普通用法：

1、dpkg -i
    安装一个 Debian 软件包，如你手动下载的文件。

2、dpkg -c
    列出 的内容。

3、dpkg -I
   从 中提取包裹信息。

4、dpkg -r
    移除一个已安装的包裹。

5、dpkg -P
   完全清除一个已安装的包裹。和 remove 不同的是，remove 只是删掉数据和可执行文件，purge 另外还删除所有的配制文件。

6、dpkg -L
   列出 安装的所有文件清单。同时请看 dpkg -c 来检查一个 .deb 文件的内容。

7、dpkg -s
   显示已安装包裹的信息。同时请看 apt-cache 显示 Debian 存档中的包裹信息，以及 dpkg -I 来显示从一个 .deb 文件中提取的包裹信息。

8、dpkg-reconfigure
   重新配制一个已经安装的包裹，如果它使用的是 debconf (debconf 为包裹安装提供了一个统一的配制界面)。



#   二、软件安装后相关文件位置

   1.下载的软件存放位置
    /var/cache/apt/archives

   2.安装后软件默认位置
  /usr/share

   3.可执行文件位置 
  /usr/bin

   4.配置文件位置
   /etc

  5.lib文件位置
  /usr/lib