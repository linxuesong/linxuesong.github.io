---
title: hexo+valine搭建博客评论系统
author: linxuesong
avatar: 'https://cdn.jsdelivr.net/gh/linxuesong/cdn/img/avatar.jpg'
authorLink: linxuesong.github.io
authorAbout: 一个好奇的人
authorDesc: 一个好奇的人
categories: 
 - [技术]
 - [主题]
comments: true
photos: >-
  https://cdn.jsdelivr.net/gh/linxuesong/cdn/img/articleCover/犬夜叉/201204113622-2-lp.jpg
date: 2020-12-26 10:26:53
tags: 
 - [主题美化]
description:
keywords:
---
# hexo+valine搭建博客评论系统

1.注册LeanCloud

2.在leanCloud中创建应用

3.拿到appid和appkey

然后 **进入应用->设置->应用key**

拿到你的appid和appkey之后，打开**主题配置文件** 搜索 **valine**，填入appid 和 appkey

4.修改hexo博客主题目录themes/Skaura/_config.yml配置文件中的valine部分内容

```
# Valine
valine: true
v_appId: GyC3NzMvd0hT9Yyd2hYIC0MN-gzGzoHsz
v_appKey: mgOpfzbkHYqU92CV4IDlAUHQ
```

5.记得在Leancloud -> 设置 -> 安全中心 -> Web 安全域名 把你的域名加进去





最后当我们发送一条评论后可以在leanCloud中的   存储/结构化数据/comment看到评论信息



PS:valine还可以美化评论背景样式、增加评论邮件通知等等的功能

参考博客:https://blog.csdn.net/cungudafa/article/details/104281764

PS:可以在https://en.gravatar.com/网站上注册头像呦，这样就可以在评论时显示自己邮箱绑定的头像了