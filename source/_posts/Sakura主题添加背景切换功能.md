---
title: Sakura主题添加背景切换功能
author: linxuesong
avatar: 'https://wx1.sinaimg.cn/large/006bYVyvgy1ftand2qurdj303c03cdfv.jpg'
authorLink: linxuesong.github.io
authorAbout: 一个好奇的人
authorDesc: 一个好奇的人
categories: 技术
comments: true
date: 2020-12-16 17:23:02
tags:
keywords:
description:
photos:
---

参考博客:https://cuitianyu.site/Sakura-config-home-20200901.html

# 恢复切换主题背景功能

该功能的前端展示在hexo版本的sakura主题作者删除了,但是js和css代码没有删除，如果要恢复只需重新引用这部分js和css代码即可

## 1.从博客根目录themes/sakura/layout/layout.ejs的\<body>中添加

````
  <!-- 实现换肤功能 -->
  <%- partial('_partial/skin-list') %> 
  <%- partial('_partial/skin-btn', null, {cache: !config.relative_link}) %>
  <%- partial('_partial/mheader', null, {cache: !config.relative_link}) %>
  <%- partial('_partial/aplayer', null, {cache: !config.relative_link}) %> 
</body>
</html>
````

## 2.在themes/Sakura/layout/_partial文件夹下依次新建skin-btn.ejs和skin-list.ejs

skin-btn.ejs的内容为：

````
<div class="changeSkin-gear no-select">
  <div class="keys" id="setbtn"> 
   <span id="open-skinMenu"> 切换主题 | SCHEME TOOL  
     <i class="iconfont icon-gear inline-block rotating"></i> 
   </span>
  </div>
</div>

````

`skin-list.ejs`的内容为：

```
<div class="skin-menu no-select" id="mainskin" style="position: fixed">
 <div class="theme-controls row-container">
  <ul class="menu-list">
   <li id="white-bg"> <i class="fa fa-television" aria-hidden="true"></i></li>
   <li id="sakura-bg"> <i class="iconfont icon-sakura"></i></li>
   <li id="gribs-bg"> <i class="fa fa-slack" aria-hidden="true"></i></li>
   <li id="KAdots-bg"> <i class="iconfont icon-dots"></i></li>
   <li id="totem-bg"> <i class="fa fa-optin-monster" aria-hidden="true"></i></li>
   <li id="pixiv-bg"> <i class="iconfont icon-pixiv"></i></li>
   <li id="bing-bg"> <i class="iconfont icon-bing"></i></li>
   <li id="dark-bg"> <i class="fa fa-moon-o" aria-hidden="true"></i></li>
  </ul>
 </div>
</div>
<canvas id="night-mode-cover"></canvas>

```

到目前位置我们可以在右下角看到前端切换背景的控制面板

## 3.背景图片可以在themes/Sakura/source/js/sakura-app.js中更换，其位置为：

````
  changeBG('#sakura-bg', 'https://cdn.jsdelivr.net/gh/honjun/cdn@1.6/img/themebg/sakura.png')
  changeBG('#gribs-bg', 'https://cdn.jsdelivr.net/gh/honjun/cdn@1.6/img/themebg/plaid.jpg')
  changeBG('#pixiv-bg', 'https://cdn.jsdelivr.net/gh/honjun/cdn@1.6/img/themebg/star.png')
  changeBG('#KAdots-bg', 'https://cdn.jsdelivr.net/gh/honjun/cdn@1.6/img/themebg/point.png')
  changeBG('#totem-bg', 'https://cdn.jsdelivr.net/gh/honjun/cdn@1.6/img/themebg/little-monster.png')
  changeBGnoTrans('#bing-bg', 'https://api.shino.cc/bing/')
  $('.skin-menu #white-bg').click(function () {
    mashiro_global.variables.skinSecter = false
    mashiro_global.variables.isNight = false
    $('#night-mode-cover').css('visibility', 'hidden')
    $('body').css('background-image', 'none')
    $('.blank').css('background-color', 'rgba(255,255,255,.0)')
    $('.pattern-center-sakura').removeClass('pattern-center-sakura').addClass('pattern-center')
    $('.headertop-bar-sakura').removeClass('headertop-bar-sakura').addClass('headertop-bar')
    $('#banner_wave_1').removeClass('banner_wave_hide_fit_skin')
    $('#banner_wave_2').removeClass('banner_wave_hide_fit_skin')
    closeSkinMenu()
    setCookie('bgImgSetting', '', 30)
  })
  $('.skin-menu #dark-bg').click(function () {
    mashiro_global.variables.skinSecter = true
    mashiro_global.variables.isNight = true
    $('body').css('background-image', 'url(https://cdn.jsdelivr.net/gh/honjun/cdn@1.6/img/other/starry_sky.png)')
    $('.blank').css('background-color', 'rgba(255,255,255,.8)')
    $('#night-mode-cover').css('visibility', 'visible')
    $('.pattern-center').removeClass('pattern-center').addClass('pattern-center-sakura')
    $('.headertop-bar').removeClass('headertop-bar').addClass('headertop-bar-sakura')
    $('#banner_wave_1').addClass('banner_wave_hide_fit_skin')
````

替换其中所有图片的url即可完成更换。