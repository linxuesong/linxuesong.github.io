---
title: Hexo博客md文件插入图片（以Typora编辑器为例）
author: hojun
avatar: 'https://wx1.sinaimg.cn/large/006bYVyvgy1ftand2qurdj303c03cdfv.jpg'
authorLink: hojun.cn
authorAbout: 一个好奇的人
authorDesc: 一个好奇的人
categories: 技术
comments: true
date: 2020-07-28 14:13:54
tags:
keywords:
description:
photos: 'https://cdn.jsdelivr.net/gh/cungudafa/cdn@2.0.9/img/cover/(0).jpg.webp'
---
# Typora插入Base64图片

在Typora中插入图片常用的处理方法是：

将本地的图片地址传入
将网络上的图片地址传入
这两种方式都存在一个问题：链接不可用时，图片就展示不出来了！

## 解决方法

### 方法一

首先将图片通过在线转码工具转换成base64的编码，并用以下格式嵌入即可，格式如下：

![image] (base64)
但是由于这base64编码往往都很长，很占篇幅，因此我们可以给图片编号，并将所有的图片base64编码放在文档的最后即可，格式如下：
在插入图片的地方使用：![image] [图片编号]
在文档最后使用：[图片编号]:base64编码
这样即可完成图片的永久插入！

————————————————
版权声明：本文为CSDN博主「听雨眠_sun」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/baidu_31492511/java/article/details/90704123



### 方法二

图片素材按官方教程说法，可统一放置在source/images目录中，并以 `![](/images/image.jpg)` 方式引用

或者在 _config.yml 打开 post_asset_folder 功能，将当前文章所用的图片放置到source目录下的文章同名资源目录下，以 `![](image.jpg)` 方式引用

————————————————

作者：Wavky
链接：https://www.jianshu.com/p/925fa86ccc95
来源：简书
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。