---
title: Sakura添加在线和博主聊天功能
author: linxuesong
avatar: 'https://wx1.sinaimg.cn/large/006bYVyvgy1ftand2qurdj303c03cdfv.jpg'
authorLink: linxuesong.github.io
authorAbout: 一个好奇的人
authorDesc: 一个好奇的人
categories: 技术
comments: true
date: 2020-12-16 17:49:00
tags:
keywords:
description:
photos:
---

参考博客:https://blog.csdn.net/cungudafa/article/details/104295156



#  添加 [DaoVoice](http://www.daovoice.io/) 在线聊天功能

效果展示

![image-20201216202904581](https://raw.githubusercontent.com/linxuesong/TyporaPictures/master/img/20201216202906.png)

## 1.官网注册账号获取appid修改conifg文件

前往 [DaoVoice](http://www.daovoice.io/) 官网注册并且获取 `app_id`，并将 `app_id` 填入主题的 `_config.yml` 文件中。

````
daovoice:
  enable: true
  daovoice_app_id: 7e5676fe ##这里替换成你DaoVoice上的appid
````

## 2.在footer.ejs文件末尾中添加

```
  <script>
  (function(i,s,o,g,r,a,m){i["DaoVoiceObject"]=r;i[r]=i[r]||function(){(i[r].q=i[r].q||[]).push(arguments)},i[r].l=1*new Date();a=s.createElement(o),m=s.getElementsByTagName(o)[0];a.async=1;a.src=g;a.charset="utf-8";m.parentNode.insertBefore(a,m)})(window,document,"script",('https:' == document.location.protocol ? 'https:' : 'http:') + "//widget.daovoice.io/widget/<%= theme.daovoice.daovoice_app_id%>.js","daovoice");
    daovoice('init', {
      app_id: "<%= theme.daovoice.daovoice_app_id%>"
    });
    daovoice('update');
```

## 3.配置自己喜欢的聊天样式

![image-20201216202746421](https://raw.githubusercontent.com/linxuesong/TyporaPictures/master/img/20201216202754.png)

## 4.可以绑定微信\邮箱,如果有人发消息会邮箱\微信消息提醒,在官网查看

