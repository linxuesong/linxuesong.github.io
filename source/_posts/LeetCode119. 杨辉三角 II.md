---
title: Leetcode-119.杨辉三角 II
author: linxuesong
avatar: 'https://cdn.jsdelivr.net/gh/linxuesong/cdn/img/avatar.jpg'
authorLink: linxuesong.github.io
authorAbout: 一个好奇的人
authorDesc: 一个好奇的人
categories: 技术
comments: true
tags:
  - 数组
  - LeetCode
  - 简单
keywords: LeetCode
photos: 'https://cdn.jsdelivr.net/gh/yremp/cdn@2.1.5/img/cover/(1).jpg.webp'
date: 2020-09-01 20:19:42
description:

---



#### [LeetCode119. 杨辉三角 II](https://leetcode-cn.com/problems/pascals-triangle-ii/)

# 1.0题目描述

给定一个非负索引 *k*，其中 *k* ≤ 33，返回杨辉三角的第 *k* 行。

![img](https://upload.wikimedia.org/wikipedia/commons/0/0d/PascalTriangleAnimated2.gif)

在杨辉三角中，每个数是它左上方和右上方的数的和。

**示例:**

```
输入: 3
输出: [1,3,3,1]
```

**进阶：**

你可以优化你的算法到 *O*(*k*) 空间复杂度吗？

# 2.0 题目分析

和上一题118联系一起，我们发现二维数组存杨辉三角上一层数组生成下一层数组，现在要求仅用一维数组存储

如何在一维数组的前提下，使用我们的递推公式

本层arr[i]=上一层arr[i] + 上一层arr[i-1]

# 3.0两种思路对比

## 3.1正向遍历思维

遍历时

arr[0] = arr[0]上一层

本层arr[1] = arr[1]上一层 + arr[0]上一层

本层arr[2] = arr[2]上一层+arr[1]（公式要求上一层，但这一步已经arr[1]变成本层了）

所以正向遍历思路就是保存这个上一层的arr[i]



需要变量个数分析：一次遍历要 保存本层arr[i]、用上一层arr[i-1]

保存是一个变量cur   用上一层又是一个变量pre

代码如下

````go
func getRow(rowIndex int) []int {
    ret := make([]int, rowIndex+1)
    for i := 0; i < rowIndex+1; i++ {
        pre := 0
        cur := ret[0]
        for j:=0; j < i; j++ {
            ret[j] = pre + cur
            pre,cur = cur, ret[j+1]
        }
        ret[i] = 1
    }
    return ret
}
````

进一步优化如果不用两个变量保存，而是换一种方式呢

在头部插入一个0，让数组错开一位，不存在覆盖的现象

````go
func getRow(rowIndex int) []int {
	res :=[]int{1}
	for i:=1;i<=rowIndex;i++{
		res =append([]int{0},res...)
		for j:=0;j<i;j++{
			res[j]= res[j]+res[j+1]
		}
	}
	return res
}
````

## 3.2反向遍历思维

反向遍历

arr[n-1] = arr[n-1] + arr[n-2]

arr[n-2] = arr[n-2] + arr[n-1]

···

arr[0] = 1

发现不存在本层覆盖上一层的情况

````go
func getRow(rowIndex int) []int {
    ret := make([]int, rowIndex+1)
    ret[0] = 1
    for i := 1; i < rowIndex+1; i++ {
        for j := i; j > 0; j-- {
            ret[j] = ret[j]+ ret[j-1]
        }
    }
    return ret
}
````

# 4.0总结

动态规划内存空间二维转一维的方式

如果存在状态转移时一维保存数组出现上一层把本层数据占了，两种较好的思路是：

1.从后向前遍历

2.数组头部加一个0值错开位置

这一切都是基于本层状态保存n个 上一层n-1个

