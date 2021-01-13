---
title: 使用主题的个人插件在文章中插入B站外链视频和图片
author: linxuesong
avatar: 'https://cdn.jsdelivr.net/gh/linxuesong/cdn/img/avatar.jpg'
authorLink: linxuesong.github.io
authorAbout: 一个好奇的人
authorDesc: 一个好奇的人
categories: 技术
comments: true
photos: >-
  https://cdn.jsdelivr.net/gh/linxuesong/cdn/img/articleCover/鬼刃/200929110029-3-1200.jpg
date: 2020-12-18 11:20:10
tags:
keywords:
description:
---

## 写文章配置

主题集成了个人插件hexo-tag-bili和hexo-tag-fancybox_img。其中hexo-tag-bili用来在文章或单页面中插入B站外链视频，使用语法如下：

```md
{% bili video_id [page] %}
```

详细使用教程详见[hexo-tag-bili](https://github.com/honjun/hexo-tag-bili/blob/master/README-zh_cn.md)。

hexo-tag-fancybox_img用来在文章或单页面中图片，使用语法如下：

```md
{% fb_img src [caption] %}
```

详细使用教程详见[hexo-tag-fancybox_img](https://github.com/honjun/hexo-tag-fancybox_img/blob/master/README-zh_cn.md)