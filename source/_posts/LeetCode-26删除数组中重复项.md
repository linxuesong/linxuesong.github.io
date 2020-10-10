---
title: LeetCode-26删除数组中重复项
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
# 题目描述

给定一个排序数组，你需要在 原地 删除重复出现的元素，使得每个元素只出现一次，返回移除后数组的新长度。

不要使用额外的数组空间，你必须在 原地 修改输入数组 并在使用 O(1) 额外空间的条件下完成。

 

示例 1:

给定数组 nums = [1,1,2], 

函数应该返回新的长度 2, 并且原数组 nums 的前两个元素被修改为 1, 2。 

你不需要考虑数组中超出新长度后面的元素。
示例 2:

给定 nums = [0,0,1,1,1,2,2,3,3,4],

函数应该返回新的长度 5, 并且原数组 nums 的前五个元素被修改为 0, 1, 2, 3, 4。

你不需要考虑数组中超出新长度后面的元素。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/remove-duplicates-from-sorted-array
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

# 解题思路

双指针法：存放非重复元素的指针(0开始)   寻找下一个非重复元素的指针(1开始)

寻找指针：遍历数组找到 下一个不重复元素(和已存放的元素不相等)，找到后存入非重复指针

# 代码实现

````
func removeDuplicates(nums []int) int {
    if(len(nums) == 1) {
        return 1
    }
    //bef最大不重复项  cur当前遍历元素
    bef := 0
    for cur := 1; cur < len(nums); cur++ {
        if(nums[bef] != nums[cur]) {
            bef++
            nums[bef] = nums[cur]
        }
    }    
    return bef+1  
}
````

# 总结

一开始的思路是相邻元素两两比较，不同则后续元素前移一位，数组长度减1

，时间复杂度为O(n方)。

缺点就是每次不同移动n个元素，双指针法就是一指针存放，一指针寻找，只移动一个元素，更快

