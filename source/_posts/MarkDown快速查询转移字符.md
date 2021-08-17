---
title: MarkDown快速查询转移字符
author: linxuesong
avatar: 'https://cdn.jsdelivr.net/gh/linxuesong/cdn/img/avatar.jpg'
authorLink: linxuesong.github.io
authorAbout: 一个好奇的人
authorDesc: 一个好奇的人
categories:
  - 技术
comments: true
tags:
  - 资料整理
photos: >-
   https://cdn.jsdelivr.net/gh/linxuesong/cdn/img/articleCover/动漫风景/apic-in 色彩绚丽的风景动漫图片 (16).jpg
date: 2021-05-25 14:13:33
keywords:
description: markdown常用转移字符，方便书写博客文档
---

# MarkDown快速查询转移字符



# 公式块部分

举例

```
$$
dp[i]=
\begin{cases}

	计算式1 	&计算式条件  \\换行
	计算式2    &计算式条件  \\换行
\end{cases}
$$
```

详细表格

| 公式块 | \begin{cases}     内容    \end{cases}                        | 大公式表达式         |
| :----- | :----------------------------------------------------------- | :------------------- |
|        | \big                                                         | [ //比较大的左中括号 |
|        | \bigg[                                                       | //再大一点           |
|        | \Big[                                                        | //比big大一点        |
|        | \Bigg[                                                       | //比bigg大一点       |
|        | a_2  a下标2            a^3 a上标3                            | 上标下标             |
|        | \sum ：∑  \int ：∫  \oint ：∮  \prod：∏                      | 求和、求导           |
|        | \alpha： α  \beta： β  \gamma：γ  \Phi ： Φ  \Omega：Ω  \Delta： Δ  \delta： δ | 希腊字母             |





# 代码块部分



# 文本部分

<br/>

<table border="1">
  <caption>MarkDown文本转移</caption>
  <tr>
    <th style="text-align:center;">输入文本</th>
    <th style="text-align:center;">显示内容</th>
  </tr>
  <tr>
    <td style="text-align:center;">&amp;nbsp;   或者    键盘全角模式空格键</td>
    <td style="text-align:center;">空格</td>
  </tr>
  <tr>
    <td style="text-align:center;">&lt;sup&gt;xxx&lt;/sup&gt;</td>
    <td style="text-align:center;">上标</td>
  </tr>
    <tr>
    <td style="text-align:center;">&lt;sub&gt;xxx&lt;/sub&gt;</td>
    <td style="text-align:center;">下标</td>
  </tr>
    <tr>
    <td style="text-align:center;">30&amp;deg;</td>
    <td style="text-align:center;">角度符号30&deg;</td>
  </tr>
</table>

<br/>

# 表格部分

如果markdown语法对应的表格在hexo上无法显示可以直接插入html代码

```html
<table border="1">
  <caption>MarkDown文本转移</caption>
  <tr>
    <th>标题1</th>
    <th>标题2</th>
  </tr>
  <tr>
    <td>行1列1</td>
    <td>行1列2</td>
  </tr>
  <tr>
    <td>行2列1</td>
    <td>行2列2</td>
  </tr>、
</table>
```

**1.如何表格中要加入需要转移的内容可以访问https://www.sojson.com/rehtml**

**2.style="text-align:center;" 在tb、th标签中加入样式控制对齐方式**

