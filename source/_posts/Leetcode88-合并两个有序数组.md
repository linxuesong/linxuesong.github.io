---
title: Leetcode88. 合并两个有序数组
author: linxuesong
avatar: 'https://wx1.sinaimg.cn/large/006bYVyvgy1ftand2qurdj303c03cdfv.jpg'
authorLink: linxuesong.github.io
authorAbout: 一个好奇的人
authorDesc: 一个好奇的人
categories: 技术
comments: true
date: 2020-08-12 20:19:13
tags:
  - 数组
  - LeetCode
  - 简单
keywords: LeetCode
description:
photos: 'https://cdn.jsdelivr.net/gh/yremp/cdn@2.1.5/img/cover/(1).jpg.webp'
---
[Leetcode-88. 合并两个有序数组](https://leetcode-cn.com/problems/merge-sorted-array/)

# 1.问题描述

给你两个有序整数数组 nums1 和 nums2，请你将 nums2 合并到 nums1 中，使 nums1 成为一个有序数组。

 

说明:

初始化 nums1 和 nums2 的元素数量分别为 m 和 n 。
你可以假设 nums1 有足够的空间（空间大小大于或等于 m + n）来保存 nums2 中的元素。


示例:

输入:
nums1 = [1,2,3,0,0,0], m = 3
nums2 = [2,5,6],       n = 3

输出: [1,2,2,3,5,6]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/merge-sorted-array
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

# 2.解题思路

注：直接写最优思路了，想看思考过程的可以看最后的总结部分

数组一nums1有最后n个空余位置，利用这点

三个变量

cur1 = m-1 数组一数字的尾部
cur2 = n-1 数组二的尾部
maxV_site = m+n-1 数组一最后的尾部，存放cur1、cur2较大者

依次比较，逐个放入

# 3.实现代码

````
func merge(nums1 []int, m int, nums2 []int, n int)  {
    var(
        cur1 = m-1
        cur2 = n-1
        maxV_site = m+n-1 // 存放当前两数组的最大值应放入nums1的位置
    )
    
    for ;cur1 >= 0 && cur2 >= 0; {
        if(nums1[cur1] > nums2[cur2]) {
            nums1[maxV_site] = nums1[cur1]
            cur1--
        }else {
            nums1[maxV_site] = nums2[cur2]            
            cur2--
        }
        maxV_site--
    }
    // 一个数组遍历完了 cur2 或 cur1有一个为-1   cur1==-1 把数组二剩下的放前面    cur2==-1不用动，数组一已经在前面了
    for ; cur2 >=0; cur2-- {
        nums1[cur2] = nums2[cur2]
    }
}
````

# 4.总结

一开始想到从头遍历，比较后要插入数组二元素则让数组一的每个元素后移一位  复杂度为O(n²)

进一步想问题在要移动每一位，如果要是不移动的话直接放要把数组一的元素替代，可以把被替代的数组一元素临时暂存起来，我们想是不是只用保存一次数组一的元素就可以了呢

最终从尾部遍历，省去了进步临时保存变量的问题



题外话：思想一开始还有一个往归并排序申请O(n)空间的方式，但一想都给了空间了就没再深想下去。有了一个思路后大致想一下时间复杂度，不可取后立即斩断，集中精神想其他方法