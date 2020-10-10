---
title: Leetcode-118. 杨辉三角
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
date: 2020-08-11 20:14:04
description:
photos:
---

#### [Leetcode-118. 杨辉三角](https://leetcode-cn.com/problems/pascals-triangle/)

# 1.0题目描述

给定一个非负整数 *numRows，*生成杨辉三角的前 *numRows* 行。

![img](https://upload.wikimedia.org/wikipedia/commons/0/0d/PascalTriangleAnimated2.gif)

在杨辉三角中，每个数是它左上方和右上方的数的和。

**示例:**

```
输入: 5
输出:
[
     [1],
    [1,1],
   [1,2,1],
  [1,3,3,1],
 [1,4,6,4,1]
]
```

# 2.0解题思路

和题目描述那个图的过程一样，比较简单

# 3.0代码

````
func generate(numRows int) [][]int {
    if(numRows <= 0) {
        return nil
    }
    first := []int{1}
    result := make([][]int, numRows)
    for i:=0; i<numRows; i++ {
        result[i] = make([]int, i+1)
    }
    result[0] = first
    for i:=1; i<numRows; i++ {
        next := make([]int, i+1)
        next[0], next[i] = 1, 1
        for j :=1; j<i; j++ {
            next[j] = result[i-1][j-1] + result[i-1][j]
        }
        result[i] = next
    }
    return result
}
````

# 4.0总结

1.第一版代码的问题，变量起名比较乱，建议修改优化一下
2.多维切片的创建，和初始化  如果不make无疑是nil
①make(\[\][\]int, x)
②for arr := range arrs
    arr:= make([]int, y)

