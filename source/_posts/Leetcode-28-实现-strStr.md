---
title: Leetcode-28. 实现 strStr()
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
date: 2020-08-11 20:16:50
description:
photos:
---
#### [Leetcode-28. 实现 strStr()](https://leetcode-cn.com/problems/implement-strstr/)

# 题目描述	

实现 strStr() 函数。

给定一个 haystack 字符串和一个 needle 字符串，在 haystack 字符串中找出 needle 字符串出现的第一个位置 (从0开始)。如果不存在，则返回  -1。

示例 1:

输入: haystack = "hello", needle = "ll"
输出: 2
示例 2:

输入: haystack = "aaaaa", needle = "bba"
输出: -1
说明:

当 needle 是空字符串时，我们应当返回什么值呢？这是一个在面试中很好的问题。

对于本题而言，当 needle 是空字符串时我们应当返回 0 。这与C语言的 strstr() 以及 Java的 indexOf() 定义相符。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/implement-strstr
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。



# 思路

遍历每一个haystack的字符，以此为起点和needle匹配，匹配成功，则返回遍历下标；否则返回-1

# 实现代码

````
func strStr(haystack string, needle string) int {
    hay_len := len(haystack)
    ne_len := len(needle)
    for i:=0; i < hay_len-ne_len+1; i++ {
       //判断haystack[i]开头是否和needle匹配
       if(isStrEqual(haystack[i:], needle)){
           return i
       }
    }
    return -1
}

func isStrEqual(str1 string, str2 string) bool {
    length := len(str2)
    flag := true
    for j:=0; j<length ;j++ {
        if(str1[j] != str2[j]) {
            flag = false
            break
        }
    } 
    return flag
}
````

# 总结

书写代码在一开始的时候没有注意到haystack的遍历区间是

len(haystack) - len(needle)+1，遍历到尾部是没必要且麻烦的



避免这种情况就是当我有了基本思路后，是会有好多漏洞的，实现方法要想一次最优且简洁就要把所有的测试用例列出来，不要光用脑子想，要写在纸上

然后把脑子里的思路转成代码，和用例一一对应

# 进一步的优化（未完待补坑）

上面代码的时间复杂度为O((N-L)*L)

## 优化方案一：hash省去L长度是否匹配判断

之所以复杂是因为遍历每一字符都要比较L长度判断是否匹配

这个*L可以转化为O(1)

方法就是用hash值，我们对字符进行编码，生成唯一值

这样每次判断匹配时就转化为计算hash值了

## 优化方案二：KMP字典匹配方法不用遍历源字符串每个字符了，节省时间

这个查了资料比较复杂，等以后有时间不用，挖个坑QAQ