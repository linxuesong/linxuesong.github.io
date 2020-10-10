title: Leetcode-581. 最短无序连续子数组
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
date: 2020-09-01 20:16:49
description:

---

[581. 最短无序连续子数组](https://leetcode-cn.com/problems/shortest-unsorted-continuous-subarray/)

# 1.0题目描述

给定一个整数数组，你需要寻找一个**连续的子数组**，如果对这个子数组进行升序排序，那么整个数组都会变为升序排序。

你找到的子数组应是**最短**的，请输出它的长度。

**示例 1:**

```
输入: [2, 6, 4, 8, 10, 9, 15]
输出: 5
解释: 你只需要对 [6, 4, 8, 10, 9] 进行升序排序，那么整个表都会变为升序排序。
```

**说明 :**

1. 输入的数组长度范围在 [1, 10,000]。
2. 输入的数组可能包含**重复**元素 ，所以**升序**的意思是**<=。**

# 2.0解题思路

最短无序数组的特征:

①数组为nums[0:i-1]     nums[i:j]   nums[j+1:n-1]

②子序列 nums[0:i-1] 和 nums[j+1:n-1]升序

③假设nums[i:j]中的最大最小值为max min，则nums[0:i-1]小于min  并且 nums[j+1:n]大于max

## 2.1思路一：暴力搜索i，j

①i从0到n-1   j从0到n-1，   

②i，j固定时判断是否满足上面条件(需要遍历整个n才能判断2.0中③)

## 2.2思路二：数组排序

我们将数组 numsnums 进行排序，记为 nums\_sortednums_sorted 。然后我们比较 numsnums 和 nums\_sortednums_sorted 的元素来决定最左边和最右边不匹配的元素。它们之间的子数组就是要求的最短无序子数组。

## 2.3思路三：对于第一个乱序不是左边界的优化

一句话概括：第一个乱序不是逆序

一开始的错误思路：正向找左边界

左边界：认为第一个乱序的位置如：1230， 0即左边界

但对于1230   -1    0之前 (1,-1)为逆序 所以   1为左边界

错误原因在于正向第一个乱序   i后面的元素和前面元素有可能逆序

第一个乱序不是第一个逆序

两种解决方法

### 2.3.1反向查找解决  巧妙但不好想

反向查找最后一个逆序对即可避免

j    <     所有j之前的数;   如果j比之前的数大就逆序

我们找到一个逆序后会找下一个逆序，知道最后一个，这样保证了所有的逆序都找了

举例：1 2 3  0    -1

从后向前  最小值初始为-1  下标也为-1

0 > -1  (0,-1)逆序  最小值为-1

3>-1 (3,-1)逆序，最小值-1

……

1>-1 (1,-1)逆序，最小值-1

举例二： -2   1   2  3  0

……

1>-1 (1,-1)逆序，最小值-1

-2 < -1     最后一个还是（1，-1）逆序，最小值-2

最后逆序的 位置是1所在的位置

### 2.3.2用第一个乱序定大致范围，再 扩大定最后范围

什么意思呢？

一句话：乱序夹的区间的最大元素，最小元素其排序后的位置即为左右边界

例：123    0   0.5   -1

乱序夹的区间  0    0.5 最大值0.5  最小值0

他们最终的位置会在123     -1中所以最短连续子序列不是0 0.5

0应当放到左边放到  1前  所以左边界为第一个元素

0.5放右边  放到-1之前  所以右边界为最后一个元素

另一种解释方式

乱序夹的范围是首尾第一个逆势拐点，范围内最大最小为a，b

a,b延申找到最后左右边界 

![](https://pic.leetcode-cn.com/5c6b77b2f1cf11fbd4607ed0b407d25e1fb76eaef1486fd3cd3292ced9829e6e-image.png)



# 实现代码

仅实现2.3.2思路代码

````go
func findUnsortedSubarray(nums []int) int {
    low := 0
    high := len(nums)-1
    for ;low < high && nums[low] <= nums[low+1]; {
        low++
    }
    for ;low < high && nums[high] >= nums[high-1]; {
        high--
    }
    // low  high  内部就乱序了
    //求其最大最小值
    if(low == high) {
        return 0
    }
    min := nums[low]
    max := nums[low]
    for low=low+1; low <= high; low++ {
        if(min > nums[low]) {
            min = nums[low]
        }
        if(max < nums[low]) {
            max = nums[low]
        }
    }
    
    //找第一个大于min的数
    left :=0
    for ; left <= low; left++ {
        if(nums[left] > min){
            break;
        }
    }
    right := len(nums)-1
   for ; right >= high ; right-- {
        if(nums[right] < max){
            break;
        }
    }
    return right -left+1
}
````

# 总结

把问题先直接想问题答案的样子，暴力搜索怎么做，慢在哪

然后在想其他方法，这道题我不会做，感觉很难，时间就画在正向遍历找边界然后一直是错误的思路，想不通。知道是错误思路却没有想到出错误痛点，一直在用不同的测试用例试找规律。

另外画图 把数组画出来，如2.3.2解释时用折线图表示趋势画出最一般的情况这样可以更清晰的思考。

收获吧？不想为了总结整理而整理

画折线图表示数组变化趋势，看简单已知如何推出答案

