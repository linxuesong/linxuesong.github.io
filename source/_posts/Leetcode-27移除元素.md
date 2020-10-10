---
title: Leetcode-27移除元素
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
date: 2020-08-11 20:16:49
description:
---
Leetcode-27移除元素

# 题目描述

给你一个数组 nums 和一个值 val，你需要 原地 移除所有数值等于 val 的元素，并返回移除后数组的新长度。

不要使用额外的数组空间，你必须仅使用 O(1) 额外空间并 原地 修改输入数组。

元素的顺序可以改变。你不需要考虑数组中超出新长度后面的元素。

 

示例 1:

给定 nums = [3,2,2,3], val = 3,

函数应该返回新的长度 2, 并且 nums 中的前两个元素均为 2。

你不需要考虑数组中超出新长度后面的元素。
示例 2:

给定 nums = [0,1,2,2,3,0,4,2], val = 2,

函数应该返回新的长度 5, 并且 nums 中的前五个元素为 0, 1, 3, 0, 4。

注意这五个元素可为任意顺序。

你不需要考虑数组中超出新长度后面的元素。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/remove-element
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

# 解题思路

双指针法：先找到非target元素，放入到开始位置newLen，newLen++等待存放 下一个非target元素



# 代码实现

```
func removeElement(nums []int, val int) int {
    length := len(nums)
    newLen := 0
    for i := 0; i < length; i++ {
        if(nums[i] != val) {
            nums[newLen] = nums[i]
        }
    }

    return length
}
```







# 反思

自己做这道题的想法是类似快速排序，左边找target 右边找非target，然后交换，最后直到相遇

代码如下：

````
func removeElement(nums []int, val int) int {
    length := len(nums)
    var s = 0
    var e = length - 1 
    for ; s <= e;  {
        for ;  s<=e && nums[e] == val; e--{
            length--
        }
        
        for ;  s<=e&&nums[s] != val ; s++{
        }
        if(s < e) {
            var tmp = nums[e]
            nums[e] = nums[s]
            nums[s] = tmp
        }
    }
    return length
}
````

但在写代码的过程中在s、e的比较上花了很长时间，常常遇到很多逻辑上的错误，下面是一次次试错后未简化的代码：

````
func removeElement(nums []int, val int) int {
    length := len(nums)
     var s = 0
     var e = length - 1 
    if(length == 0){
                return 0
    }

    for ; s < e;  {
        for ; nums[e] == val && s<e; e--{
            length--
        }
        
        for ; nums[s] != val && s<e; s++{
        }
        if(s!=e) {
            var tmp = nums[e]
            nums[e] = nums[s]
            nums[s] = tmp
        }
    }
    if(nums[s] == val) {
        length--
    }
    return length
}
````

对比可以看出逻辑很混乱，之所以出现这样的情况是因为没有很好的模板思路去解题，有了大致思路不准备细节就开始写，最后以致写出低质量代码。

# 总结

1.双指针法 一个指针用来存放最后的结果，另一个用来寻找要操作的元素下标，O(n)时间解决问题

2.双向指针循环的结束条件可以是 s<e也可以是s<=e  

但是s<=e要写在前面如 s<=e && nums[e] == val，否则数组越界

s<e适合终止位置要存放特定元素

s<=e适合从头找到尾，处理所有元素而非单一元素