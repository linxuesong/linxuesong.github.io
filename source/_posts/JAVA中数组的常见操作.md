---
title: JAVA中数组的常见操作
author: linxuesong
avatar: 'https://cdn.jsdelivr.net/gh/linxuesong/cdn/img/avatar.jpg'
authorLink: linxuesong.github.io
authorAbout: 一个好奇的人
authorDesc: 一个好奇的人
categories:
  - 技术
comments: true
tags:
  - 数组
  - JAVA
photos: >-
  https://cdn.jsdelivr.net/gh/linxuesong/cdn/img/articleCover/鬼刃/200929110029-3-1200.jpg
date: 2021-04-08 16:34:03
keywords:
description: 包含JAVA中的数组、Array、List等常用操作
---

# 一、普通数组int[]

## 深拷贝

类似C++中的数组指针，使用等号赋值只是浅拷贝，深拷贝需要用Arrays类的如下方法

```
Static type copyOf(type a[], int length) // 深拷贝出一个新的数组
Static type copyOfRange(type a[], int start, int end)
```

## 排序

```
int[] a = new int[1000];
Arrays.sort(a); // 使用优化后的快速排序方法对数组进行排序
```

## 判断是否相等

直接用等号判断是判断引用是否为同一处，如果要判断具体值要用Arrays类的如下方法

```
static boolean equals(type[] a, type[] b)
```

# 二、泛型数组列表ArrayList\<type>

## 使用

```java
// 构建
ArrayList<Empolyee> staff = new ArrayList<Employee>(); // 声明并构造
// 增删改查
staff.add(new Emplyee("xxx")); // 尾部添加元素,也可以指定位置
Employee e = staff.remove(index);// 删除下标为index的元素，之后所有元素前一
staff.set(index, e); // 将index位置元素赋值
Employee e = staff.get(index); // 取指定位置元素
// 遍历
for(Employee e : staff) {}
```

使用ArrayList存放基本类型数据需要装箱和拆箱

```
ArrayList<Integer> lst = new ArrayList<Integer>();
lst.add(3); //等价于Integer.valueOf(3)
int a = lst.get(0); //等价于lst.get(0).intValue()
```

