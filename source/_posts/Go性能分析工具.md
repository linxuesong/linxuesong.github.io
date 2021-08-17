---
title: Go性能分析工具
author: linxuesong
avatar: 'https://cdn.jsdelivr.net/gh/linxuesong/cdn/img/avatar.jpg'
authorLink: linxuesong.github.io
authorAbout: 一个好奇的人
authorDesc: 一个好奇的人
categories:
  - 技术
comments: true
tags:
  - Golang
photos: >-
  https://cdn.jsdelivr.net/gh/linxuesong/cdn/img/articleCover/鬼刃/200929110029-3-1200.jpg
date: 2021-06-17 20:42:37
keywords:
description: 本片文章介绍如何对go程序进行分析，如程序长耗时所在位置、程序协程调度信息、内存使用情况、火焰图等等，主要介绍两个工具trace和pprof
---

一、GODEBUG参数
特别方便，无需下载第三方工具，无需修改程序 代码

分析协程调度情况

https://segmentfault.com/a/1190000020108079

# 二、Trace

## 特点

无需下载第三方工具，需要修改程序代码

https://segmentfault.com/a/1190000019736288

## 如何用

修改代码,加入trace

```
import (
	"os"
	"runtime/trace"
)

func main() {
	trace.Start(os.Stderr)
	defer trace.Stop() //一定要这一行执行后才会有trace文件

	ch := make(chan string)
	go func() {
		ch <- "EDDYCJY"
	}()

	<-ch
}
```

生成跟踪文件：

```go
$ go run main.go 2> trace.out // 	运行生成追踪文件
```

分析追踪文件

```
$ go tool trace trace.out // 	会启动浏览器，展示网页版分析报告
```

分析结果说明

![image-20210621110611559](/Users/linxuesong/Library/Application Support/typora-user-images/image-20210621110611559.png)





## 栗子

分析结果

#### 实例1: 如何分析程序耗时时间长---Scheduler latency profile-调度延迟概况

多协程生成随机数据，随机数据做参数访问

```
var wg sync.WaitGroup // main等待所有goroutine结束

func CallGetUserInfoDbatchGoVersion() {
	rand.Seed(time.Now().UnixNano()) // 使用rand生成随机种子，**之后性能分析我们会发现这个地方有问题**
	uidcnt := rand.Intn(50)  // 使用随机种子生成50以内随机数   **之后性能分析我们会发现这个地方有问题**
  SCFCALL(uidcnt) // 使用生成的随机数做参数远程调用，具体处理逻辑忽略
}

func main() {
		for j:=0;j<100;j++ {
			wg.Add(1)
			go CallGetUserInfoDbatchGoVersion() // 开启多goroutine
		}
		wg.Wait()
	log.Println("执行完毕")
}
```

对上面代码加上trace的分析

```
import "runtime/trace"

var wg sync.WaitGroup // main等待所有goroutine结束

func CallGetUserInfoDbatchGoVersion() {
	rand.Seed(time.Now().UnixNano()) // 使用rand生成随机种子，**之后性能分析我们会发现这个地方有问题**
	uidcnt := rand.Intn(50)  // 使用随机种子生成50以内随机数
  SCFCALL(uidcnt) // 使用生成的随机数做参数远程调用，具体处理逻辑忽略
}

func main() {
	trace.Start(f)
	defer trace.Stop() // 注意一定要执行了trace.Stop之后才会生成分析报告

		for j:=0;j<100;j++ {
			wg.Add(1)
			go CallGetUserInfoDbatchGoVersion() // 开启多goroutine
		}
		wg.Wait()
	log.Println("执行完毕")
}
```

结果报告中“Scheduler latency profile-调度延迟概况”如下

![image-20210621110812103](https://raw.githubusercontent.com/linxuesong/TyporaPictures/master/img/image-20210621110812103.png)



可以看到锁耗时占用到了77%，看调用来自Seed(*Rand),定位到耗时函数的位置后，分析这个函数

```
func Seed(seed int64) { globalRand.Seed(seed) } // 使用了全局对象globalRand，这个对象是lockedSource，每次使用前会加锁，导致每个go routin竞争锁
func Intn(n int) int { return globalRand.Intn(n) } // 使用全局对象，多routine会有所得竞争
```

解决方案:正对每个go routine生成单独的Rand对象rngSource

```
func CallGetUserInfoDbatchGoVersion() {
	r := rand.New(rand.NewSource(time.Now().UnixNano()))	 //   全局对象替换成创建本地对象
	uidcnt := r.Intn(50)  // 使用随机种子生成50以内随机数      //   全局对象替换成本地对象
  SCFCALL(uidcnt) // 使用生成的随机数做参数远程调用，具体处理逻辑忽略
}
```

修改后的性能分析截图--整体耗时缩短，而且不会在随机数这里有长耗时：

![image-20210621142726349](https://raw.githubusercontent.com/linxuesong/TyporaPictures/master/img/image-20210621142726349.png)

# 三、PProf

需要下载第三方工具，需要修改程序代码

https://segmentfault.com/a/1190000016412013

使用举例

```

```

分析结果
