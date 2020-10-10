---
title: Leetcode-53. 最大子序和
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
date: 2020-08-11 20:19:50
description:
---
[Leetcode-53. 最大子序和](https://leetcode-cn.com/problems/maximum-subarray/)

# 题目描述

给定一个整数数组 nums ，找到一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。

示例:

n'j输入: [-2,1,-3,4,-1,2,1,-5,4]
输出: 6
解释: 连续子数组 [4,-1,2,1] 的和最大，为 6。
进阶:

如果你已经实现复杂度为 O(n) 的解法，尝试使用更为精妙的分治法求解。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/maximum-subarray
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。



# 解法一：暴力方法O(n²)

## 解题思路

两层遍历，外层遍历所有元素，变量start；内层遍历start~结束元素，变量end

过程中维持着tmp_sum表示start~end的子序列和

两层遍历完找到最终的result



## 实现代码

````
func maxSubArray(nums []int) int {
    length := len(nums)
    if length == 0 {
        return 0
    }

    start := 0
    end := 0
    tmp_sum := 0
    result := nums[end]
    for ; start<length; start++ {
        tmp_sum = 0
        for end=start ; end<length; end++ {
            tmp_sum += nums[end]
            if(tmp_sum > result) {
                result = tmp_sum
            }
        }
    }
    return result
}
````

# 解法二：动态规划O(n)

## 解题思路

暴力方法里有重复的子问题，数组中  和最大的连续子序列

以start=0开始包含以start=1开始的所有计算，不过多加了一个nums[0]

以start=length-1只有一个元素为最小子问题，以此叠加到start=0

1.问题定义为以start开始的数组 和最大的连续子序列

2.状态转移方程 start之前[start-1..end]的和为负数可以直接舍去


$$
f(start-1) = \begin{cases}
		nums[start], & \text{if $f(start)$ < 0}\\
		nums[start]+f(start),& \text{if $f(start)$  >= 0}
	\end{cases} 
	\\注:start数组下标从最后一位开始到0
$$
3.用一个O(n)数组保存每次状态转移时的f(start)值

4.最后max(保存数组)即为结果

## 实现代码

````
func maxSubArray(nums []int) int {
    length := len(nums)
    if length == 0 {
        return 0
    }
    // 初始化状态
    start := length-1
    sums := make([]int, length)
    sums[start] = nums[start]
    // 状态转移
    for start = length-2; start >=0; start-- {
        if sums[start+1] < 0 {
            sums[start] = nums[start]
        }else {
            sums[start] = nums[start] + sums[start+1]
        }
    }
    // 发挥保存数组中的最大值
    return max(sums)
}

func max(arr []int) int{
    max := -2147483647//int的最小值
    for i:= range arr {
        if(arr[i] > max) {
            max = arr[i]
        }
    }
    return max
}
````

# 解法三：线段树解法（更通用，待补坑）





# 总结

一开始没想暴力，但是别的双指针什么的试过了想不到更好的方法。

之后思考暴力思路不难，之后对暴力进行优化有重复子问题，进阶为动态规划。

思考：问题是整个数组的连续子序列最大化，

动态规划的问题不是一个小数组的连续子序列最大和，而是以start为结尾的连续子序列最大和

可见哪里是重复操作，可以建立状态转移方程，哪里就是要定义问题

再由保存的结果得出问题的最后结果