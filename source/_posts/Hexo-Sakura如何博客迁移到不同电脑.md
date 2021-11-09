---
title: Hexo-Sakura如何博客迁移到不同电脑
author: linxuesong
avatar: 'https://cdn.jsdelivr.net/gh/linxuesong/cdn/img/avatar.jpg'
authorLink: linxuesong.github.io
authorAbout: 一个好奇的人
authorDesc: 一个好奇的人
categories: 技术
comments: true
tags:
  - 主题美化
  - Sakura
keywords: LeetCode
date: 2020-08-11 20:10:14
description:
photos: https://cdn.jsdelivr.net/gh/linxuesong/cdn/img/articleCover/犬夜叉/201204113622-8-1200.jpg
---
# Hexo-Sakura博客迁移前期准备

1.将所有的博客项目文件(可以在执行hexo clean 后，这样文件少一点)上传到GitHub的仓库

这里是上传到[linxuesong](https://github.com/linxuesong) / **[linxuesong.github.io](https://github.com/linxuesong/linxuesong.github.io)**的hexo分支

下面开始迁移：

# 步骤一：本地初始化hexo博客环境

详见hexo搭建个人博客教程

要求：hexo s后可以本地看到默认页面



# 步骤二：用我们上传的博客项目文件替换初始化的默认文件

1.下载上传的所有博客项目文件

2.替换默认文件

# 步骤三：启用需插件功能

下载不同功能所需对应的hexo插件

1.本地搜索功能

```
npm install hexo-generator-json-content --save
```

2.启用自定义代码块背景

```
npm i -S hexo-prism-plugin
```

如何选用hexo-prism-plugin的代码块样式主题，可以本站搜索

3.添加RSS订阅的网站

https://blog.csdn.net/cungudafa/article/details/104320396

4.添加豆瓣hexo-douban插件生成书单、电影等页面

```
npm install hexo-douban --save    
```

然后在博客站点目录下的`node_modules`文件夹下找到`hexo-douban/lib`，文件夹下有三个js文件，分别为：`books-generator.js` 、`games-generator.js` 、`movies-generator.js`，用文本编辑器打开这三个文件，并将其文件内容末尾的代码修改为一下内容：

```js
/* 原文件内容为 layout: [`page`, `post`] ，将其修改为下面的内容*/
layout: [`douban`]
```

5.添加sitemap站点地图生成插件

用于谷歌、百度收录本网站

```
npm install hexo-generator-sitemap --save
```

