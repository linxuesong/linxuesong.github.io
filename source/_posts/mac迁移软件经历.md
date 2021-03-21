---
title: mac迁移软件经历
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
  - 软件安装
photos: >-
  https://cdn.jsdelivr.net/gh/linxuesong/cdn/img/articleCover/鬼刃/200929110029-3-1200.jpg
date: 2021-03-20 11:10:25
keywords:
description:
---

Mac工作软件安装踩坑记录

# 1.Idea

先下载idea，在idea里面下载jdk，这样避免配置jdk

## 1.1下载idea

## 1.2在idea内部安装jdk

![使用idea安装jdk](https://raw.githubusercontent.com/linxuesong/TyporaPictures/master/img/截屏2021-03-19 下午7.45.35.png)

## 1.3修改maven配置

主要解决：解决maven包拉取不下来

打开一个项目文件，在配置中将原来电脑的setting.xml做替换，更新maven即可

![截屏2021-03-19 下午7.49.02](https://raw.githubusercontent.com/linxuesong/TyporaPictures/master/img/%E6%88%AA%E5%B1%8F2021-03-19%20%E4%B8%8B%E5%8D%887.49.02.png)

# 2.goland

## 2.1安装goland

## 2.2在goland中安装go环境

![截屏2021-03-19 下午7.53.10](/Users/linxuesong/Desktop/截屏2021-03-19 下午7.53.10.png)

![截屏2021-03-19 下午7.54.07](https://raw.githubusercontent.com/linxuesong/TyporaPictures/master/img/%E6%88%AA%E5%B1%8F2021-03-19%20%E4%B8%8B%E5%8D%887.54.07.png)

# 3.邮件

## 3.1关闭腾讯企业邮箱的安全登录

登录腾讯企业邮箱官网，设置-》账户，将账户安全修改如下：

![截屏2021-03-19 下午7.57.47](https://raw.githubusercontent.com/linxuesong/TyporaPictures/master/img/%E6%88%AA%E5%B1%8F2021-03-19%20%E4%B8%8B%E5%8D%887.57.47.png)

## 3.2mac邮件添加邮箱账户

选填加其他邮箱账户

电子邮件和密码是公司提供的，确认后进入如下界面

![截屏2021-03-19 下午8.02.55](https://raw.githubusercontent.com/linxuesong/TyporaPictures/master/img/%E6%88%AA%E5%B1%8F2021-03-19%20%E4%B8%8B%E5%8D%888.02.55.png)





这个配置的填写参考腾讯邮箱 设置-》客户端设置界面![截屏2021-03-19 下午8.04.00](https://raw.githubusercontent.com/linxuesong/TyporaPictures/master/img/%E6%88%AA%E5%B1%8F2021-03-19%20%E4%B8%8B%E5%8D%888.04.00.png)



配置tls端口时要先关闭“自动管理链接设置”



![截屏2021-03-19 下午8.17.18](https://raw.githubusercontent.com/linxuesong/TyporaPictures/master/img/%E6%88%AA%E5%B1%8F2021-03-19%20%E4%B8%8B%E5%8D%888.17.18.png)

参考博客：使用Mac自带邮箱添加腾讯企业邮箱 https://www.jianshu.com/p/2eb79645d94f