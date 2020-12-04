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
photos:
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