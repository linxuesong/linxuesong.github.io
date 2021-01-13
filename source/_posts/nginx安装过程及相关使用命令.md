---
title: nginx安装过程及相关使用命令
author: linxuesong
avatar: 'https://cdn.jsdelivr.net/gh/linxuesong/cdn/img/avatar.jpg'
authorLink: linxuesong.github.io
authorAbout: 一个好奇的人
authorDesc: 一个好奇的人
categories: 技术
comments: true
photos: >-
  https://cdn.jsdelivr.net/gh/linxuesong/cdn/img/articleCover/动漫女/20120Q20240-4-lp.jpg
date: 2020-12-21 17:12:00
tags: nginx
keywords:
description:
---



# 一、安装过程

Nginx安装过程

这里提供两种方式，快速使用

如果是ubuntu可以直接用下面命令安装

````
 apt install nginx
````



这里详细说一下第二种方式:

## 0.前期准备(重要，不然会导致下面第3步失败)

安装所需的gcc和依赖库

````
4.1、GCC——GNU编译器集合    

     ubuntu: apt-get install gcc     

     linux: yum install gcc-c++ 

4.2、PCRE库    

        ubuntu:apt-get install libpcre3 libpcre3-dev

        linux: yum install -y pcre pcre-devel

4.3、zlib库   

        ubuntu: apt-get install zlib1g zlib1g-dev

        linux: yum install -y zlib zlib-devel

4.4、OpenSSL库  

        ubuntu:apt-get install openssl openssl-dev

        linux: yum install -y openssl openssl-devel
````





## 1.下载源码文件，网址如下

http://nginx.org/en/download.html

这里我们选择linux下稳定版本文件

![image-20201221162501535](C:\Users\linxuesong\AppData\Roaming\Typora\typora-user-images\image-20201221162501535.png)

## 2.解压文件

将下载的文件放到linux电脑上，用如下命令解压文件，得到nginx-1.18.0文件夹,进入到文件夹种

````
tar -zxvf 文件名
cd 解压后的文件夹
````

## 3.执行命令安装nginx

安装到指定路径下

````
./config --prefix=/usr/local/nginx  
````

## 4.编译源码，生成目标文件、二进制文件

make命令可以将c++文件按照makefile指定的依赖规则进行编译

````
make
````

## 5.部署nginx

````
make install
````

安装完成，此时
nginx文件及相关配置在/user/local/nginx

nginx运行程序在/user/local/nginx/sbin

# 二、运行nginx

## 0.自定义相关配置

目录/usr/local/nginx/conf/nginx.conf

可以修改ngxin监听的端口及相关参数

## 1.启动nginx

````
./user/local/nginx/sbin/nginx
````

执行命令后使用ps -ef|grep nginx查看是否启动进程

![image-20201221170747420](C:\Users\linxuesong\AppData\Roaming\Typora\typora-user-images\image-20201221170747420.png)

也可以打开浏览器，网址localhost查看是否有内容
如果改了监听端口则写上localhost:监听端口

# 三、其他的相关nginx命令

## 1.关闭

````
./nginx -s stop
````

## 2.

