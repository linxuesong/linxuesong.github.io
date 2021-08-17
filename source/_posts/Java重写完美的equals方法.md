---
title: Java重写完美的equals方法
author: linxuesong
avatar: 'https://cdn.jsdelivr.net/gh/linxuesong/cdn/img/avatar.jpg'
authorLink: linxuesong.github.io
authorAbout: 一个好奇的人
authorDesc: 一个好奇的人
categories:
  - 技术
comments: true
tags:
  - JAVA
photos: >-
  https://cdn.jsdelivr.net/gh/linxuesong/cdn/img/articleCover/动漫风景/images (8).jpg
date: 2021-04-09 15:08:57
keywords:
description: 如何编写java类中equals方法
---

示例代码：

```
    @Override
    public boolean equals(Object otherObject) {
        // 1.判断是否引用自身，小优化可以提前避免后面的实例比较
        if(this == otherObject) {
            return true;
        }
        // 2.比较this和otherObject是否为同一个类,此处有两种选择：
        //   a. this.getClass()==otherObject.getClass(),各个子类中的语义不一致
        //   b. otherObject instanceof ClassName,各个子类中的语义一致
        if (this.getClass() != otherObject.getClass()) {
            return false;
        }
        
        // 如果步骤2中按b分支，既比较双方可以转为通用父类，则多下面一步转换
        // 按照a分支则无需此步骤
        // ClassName other = (ClassName) otherObject;
        Father other = (Father) otherObject;
        
        // 3.比较this，other的内部实例, 基本类型用==，其他类型用Objects.equals(a,b)
        return Objects.equals(this.a, other.a) && this.b == other.b;
    }
```

