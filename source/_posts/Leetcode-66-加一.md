---
title: Leetcode-66. 加一
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
date: 2020-08-12 17:16:49
description:
---
[Leetcode-66. 加一](https://leetcode-cn.com/problems/plus-one/)

# 1.0题目描述

给定一个由整数组成的非空数组所表示的非负整数，在该数的基础上加一。

最高位数字存放在数组的首位， 数组中每个元素只存储单个数字。

你可以假设除了整数 0 之外，这个整数不会以零开头。

示例 1:

输入: [1,2,3]
输出: [1,2,4]
解释: 输入数组表示数字 123。
示例 2:

输入: [4,3,2,1]
输出: [4,3,2,2]
解释: 输入数组表示数字 4321。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/plus-one
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

# 2.0解题思路

这道题比较简单，从后向前遍历找到第一个非9数字，记下标为not9first，该下标之后所有数全为0，本下标元素值+1 对异常情况值溢出做特殊处理

# 3.0实现代码

````
func plusOne(digits []int) []int {
    oldLen := len(digits)
    not9first := oldLen-1 // 从后向前非9的第一个数
    for ; not9first >= 0 && digits[not9first] == 9; not9first-- {
        digits[not9first] = 0 // 是9就成0
    }
    if(not9first != -1) { // 加完没溢出
        digits[not9first] += 1
    }else { // 加完溢出
        digits = append([]int{1}, digits...) // 首部赋值1
    }
    return digits
}
````

