---
title: hexo增加RSS订阅功能
author: linxuesong
avatar: 'https://wx1.sinaimg.cn/large/006bYVyvgy1ftand2qurdj303c03cdfv.jpg'
authorLink: linxuesong.github.io
authorAbout: 一个好奇的人
authorDesc: 一个好奇的人
categories: 技术
comments: true
date: 2020-12-04 12:12:05
tags:
keywords:
description:
photos:Hexo
---

# Hexo增加RSS订阅

## RSS介绍

生成自己网站的聚合信息，让别人去订阅供其收获你自己的最新消息 ——有了RSS后别人可以关注了你的最新博客动态了

## 向自己主题中添加RSS功能步骤

### 1.安装插件

````
npm install hexo-generator-feed
````

### 2.主题配置文件中增加

````
# Extensions
## Plugins: http://hexo.io/plugins/
#RSS订阅
plugin:
 hexo-generator-feed
#Feed Atom
feed:
  type: atom #RSS的类型(atom/rss2)
  path: atom.xml #文件路径,默认是atom.xml/rss2.xml
  limit: 20 #展示文章的数量,使用0或则false代表展示全部
  hub:
  content: #在RSS文件中是否包含内容 ,有3个值 true/false默认不填为false
  content_limit: 140 #指定内容的长度作为摘要,仅仅在上面content设置为false和没有自定义的描述出现
  content_limit_delim: ' ' #上面截取描述的分隔符,截取内容是以指定的这个分隔符作为截取结束的标志.在达到规定的内容长度之前最后出现的这个分隔符之前的内容,，防止从中间截断.
  order_by: -date
  icon: #icon.png
````

3.themes\sakura\_config.yml

````
# 简易信息聚合,站点共享
rss: /atom.xml
````

