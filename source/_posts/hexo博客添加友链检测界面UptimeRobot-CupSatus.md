---
title: hexo博客添加友链检测界面UptimeRobot+CupSatus
author: linxuesong
avatar: 'https://cdn.jsdelivr.net/gh/linxuesong/cdn/img/avatar.jpg'
authorLink: linxuesong.github.io
authorAbout: 一个好奇的人
authorDesc: 一个好奇的人
categories: 技术
comments: true
photos: >-
  https://cdn.jsdelivr.net/gh/linxuesong/cdn/img/articleCover/鬼刃/200929110029-3-1200.jpg
date: 2021-02-03 18:01:58
tags:
keywords:
description:
---

# 0.效果展示

# 1.前期准备

a.注册UptimeRobot账号，将自己的网站和要检测的网站或者账号加上去

b.去https://github.com/izoyo/Cup网址下载CupStatus页面

# 2.应用到自己的hexo博客上

hexo new page "friendlink_status" 页面

在source/friendlink_status/中把CupSatus的所有文件放进去，目录如下

![image-20210203180642121](https://raw.githubusercontent.com/linxuesong/TyporaPictures/master/img/20210203180649.png)

按照开源项目CupSatus中说的把js/config.js中的key替换成自己upTimeRobot账号下对应的api key即可





然后在博客目录/config.yml  注意不是主题目录下的那个配置文件

加入skip-render:   -friendlink_status/**  不使用主题的layout.ejs渲染这个页面

在主题的配置文件中菜单导航栏上加入这个页面即可