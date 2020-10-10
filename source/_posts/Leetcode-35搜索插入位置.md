---
title: Leetcode-35搜索插入位置
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
date: 2020-08-11 20:19:42
description:
---
[Leetcode-35搜索插入位置](https://leetcode-cn.com/problems/search-insert-position/)

# 题目描述

给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。

你可以假设数组中无重复元素。

示例 1:

输入: [1,3,5,6], 5
输出: 2
示例 2:

输入: [1,3,5,6], 2
输出: 1
示例 3:

输入: [1,3,5,6], 7
输出: 4
示例 4:

输入: [1,3,5,6], 0
输出: 0

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/search-insert-position
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

# 解题思路

二分法很容易想到，但问题是怎么用，查找目标值是等于target，当low>high还未找到就没有

类推插入位置或匹配位置就是找顺序第一个 >=tartget 元素的位置

二分查找最后一定是left=right+1

如果left左开区间的值一直保持小于target，right右开区间一直保持大于等于target，

这样————right———————left—————

[0。。。。right]小于targrt

[left....length-1]大于等于target

即使边界时也一样



如果硬用二分查找值 < == > 三个分支匹配可看总结处理起来会很麻烦

# 实现代码

````
func searchInsert(nums []int, target int) int {
    length := len(nums)
    high := length-1
    low := 0
    for ; low <= high; {
        mid := (high-low)>>1 + low
        if(nums[mid] < target) {
            low = mid+1
        }else {
            high = mid-1
        }
    }
    return low
}
````

# 总结

这个题感觉跳出了二分查找的套路，用left、right分别表示数组不同两集合比较合适，集合交汇处就是我们要找的值

二分查找时其实也差不多

个人初始代码想到了二分但是没有想到插入位置和target的数学关系，直接用的二分查找的代码，最后把所有的可能全部考虑

代码为

````
func searchInsert(nums []int, target int) int {
    length := len(nums)
    high := length-1
    low := 0
    for ; low <= high; {
        mid := (high+low)/2
        if(nums[mid] < target) {
            low = mid+1
        }else if(nums[mid] == target) {
            return mid
        }else {
            high = mid-1
        }
    }
    // if(high == -1) {
    //     return 0
    // }else if(low == length) {
    //     return length
    // }else {
    //     return low
    // }
    return low
}
````

反思：问题的起点在于没有get到解决问题的数学关系，死板于二分查找< 、>的判断

对于该类问题  把要查找的目标    和    left、right指针的意义对应起来，

left的位置表示其左开区间即【0.。。。right】满足left=mid+1条件

right的位置表示其有开区间【right。。。length-1】满足right=mid-1条件



在边界时left=0，high=-1 时表示所有元素都满足left=mid+1条件

left=length,high=length-1时表示所有元素都满足right=mid-1条件



从算法的数学意义出发，每一个变量可以表示一类事物，掌握了和 数学的联系才能掌握算法，取代一个又一个测试用例的自己检测