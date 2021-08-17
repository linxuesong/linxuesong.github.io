---
title: golang包管理工具介绍
author: linxuesong
avatar: 'https://cdn.jsdelivr.net/gh/linxuesong/cdn/img/avatar.jpg'
authorLink: linxuesong.github.io
authorAbout: 一个好奇的人
authorDesc: 一个好奇的人
categories:
  - 技术
comments: true
tags:
  - Go
  - 包管理工具
photos: >-
  https://cdn.jsdelivr.net/gh/linxuesong/cdn/img/articleCover/动漫风景/apic-in 色彩绚丽的风景动漫图片 (15).jpg
date: 2021-03-31 19:34:09
keywords:
description:
---

参考博客

[Go 包管理工具 govendor 使用指南]: https://blog.csdn.net/zyx6a/article/details/104080665
[go mod使用]: https://www.jianshu.com/p/760c97ff644c

Go管理工具的使用

# 0.没有包管理工具的情况

## 0.1寻找依赖的路径：

1⃣️在GOROOT目录下查找

2⃣️在GOPATH/src下面查找包

## 0.2获取依赖

```
go get 依赖地址 // 依赖包会存放到gopath下面两个位置，pkg里面.a文件和src下面的.go文件
```



# 1.govendor

## 1.1管理方式

寻找依赖的路径：

1⃣️在$GOPATH/src/当前包文件/vendor目录

2⃣️向当前包目录的上级目录查找知道找到src下的vendor

3⃣️在GOROOT目录下查找

4⃣️在GOPATH下面查找包

## 1.2安装

```
go get -u github.com/kardianos/govendor
```

安装完成后为方便使用加入到环境变量

```
export PATH="$GOPATH/bin:$PATH"
```

## 1.3使用

0⃣️如果不是从git上拉取已有vendor.json的项目，而是**本地新建项目**，则要初始化本地项目

初始化项目目录，生成vendor目录和vendor.json文件

```
govendor init
```

1⃣️下载项目依赖，这里以引入

[Echo框架]: https://github.com/labstack/echo

依赖为例

从远程拉去下来依赖并放入当前vendor文件夹，记录到vendor.json,在gopath下不会有依赖包

```
govendor fetch "包链接"
// 举例：govendor fetch "github.com/labstack/echo/..."  //这里三个点表示文件夹下的所有文件，或者echo后面不要有斜杠，标识拉取项目
```

🐻踩坑：i.对于无法从网上下载下里的包，只能从git上自己手动下载，放到vendor下面 ii.有时需要加上三个点标识所有文件，不然会下载下一个空文件夹

2⃣️提交到**git上只需要提交vendor.json**即可,不需要把所有的vendor依赖文件夹提交上去

从git上拉起他人项目，项目中含有vendor.json文件，通过如下命令安装依赖包

```
govendor sync
```

## 1.4其他

常用命令

```
govendor list // 列出代码中所有被引用到的包及其状态
```

```
govendor fetch // 从远程仓库添加或更新某个包
```

| 子命令  | 功能                                   |
| ------- | -------------------------------------- |
| init    | 初始化一个新项目，生成vendor文件夹     |
| list    | 根据当前项目文件的import列出所有依赖包 |
| add     |                                        |
| update  |                                        |
| remove  |                                        |
| status  |                                        |
| fetch   | 从远程仓库拉取依赖包                   |
| sync    |                                        |
| migrate |                                        |
| get     |                                        |
| license |                                        |
| shell   |                                        |

状态参数

| 状态      | 缩写 | 含义                                                 |
| --------- | ---- | ---------------------------------------------------- |
| +local    | l    | 本地包，即项目内部编写的包                           |
| +external | e    | 外部包，即在 `GOPATH` 中、却不在项目 `vendor` 目录   |
| +vendor   | v    | 已在 `vendor` 目录下的包                             |
| +std      | s    | 标准库里的包                                         |
| +excluded | x    | 明确被排除的外部包                                   |
| +unused   | u    | 未使用的包，即在 `vendor` 目录下，但项目中并未引用到 |
| +missing  | m    | 被引用了但却找不到的包                               |
| +program  | p    | 主程序包，即可被编译为执行文件的包                   |
| +outside  |      | 相当于状态为 `+external +missing`                    |
| +all      |      | 所有包                                               |

支持状态参数的子命令有：`list`、`add`、`update`、`remove`、`fetch`

# 2.gomod

前沿:go1.13版本会默认开启mod，1.11版本后才支持mod

## 2.0前期准备,设置go环境参数使其支持mod

```
go env -w GO111MODULE=on // 启用go mod，之后可以用go env 命令展示一下go的配置
```

## 2.1管理方式

模块:多个包package的集合

当`GO111MODULE`=`on`时，那么就会使用`modules`功能:这种模式下，`$GOPATH`不再作为build时导入的角色，依赖包会存放在`$GOPATH/pkg/mod`目录下。工程中的依赖包也会从此目录下查找.

## 2.2初始化一个新项目

```
go mod init <项目名> //项目名不填写则是gopath/src后的相对路径名，填的话一般为github.com/your name/project name
```

## 2.3添加依赖

### a.先编写程序improt依赖包

其实当go run执行时会自动下载依赖包，当然也可以不运行而是只去下载依赖包

### b.下载依赖包

```
go mod tidy 	// 检测并下载本项目的module所依赖的文件，同时会移除不需要的模块
```

依赖包的存放位置是$GoPath/pkg/mod/

### C.修改go.mod文件可以使用其他依赖路径如：for的仓库、本地的拷贝

例如go.mod的内容乳腺癌

```
replace example.com/project/foo => ../foo
```

### d.go.mod文件的介绍

go.mod 提供了module, require、replace和exclude 四个命令

- `module` 语句指定包的名字（路径）
- `require` 语句指定的依赖项模块
- `replace` 语句可以替换依赖项模块
- `exclude` 语句可以忽略依赖项模块

## 2.4其他命令

| 命令     | 描述                          |
| -------- | ----------------------------- |
| vendor   | 将依赖复制到vendor下          |
| graph    | 打印模块依赖图                |
| verify   | 验证依赖是否正确              |
| edit     | 编辑go.mod文件                |
| download | 下载私有仓库的依赖到本地cache |

🐻在国内访问`golang.org/x`的各个包都需要翻墙，你可以在`go.mod`中使用`replace`替换成github上对应的库。形式如下：

```
replace (
	golang.org/x/crypto v0.0.0-20180820150726-614d502a4dac => github.com/golang/crypto v0.0.0-20180820150726-614d502a4dac
	golang.org/x/net v0.0.0-20180821023952-922f4815f713 => github.com/golang/net v0.0.0-20180826012351-8a410e7b638d
	golang.org/x/text v0.3.0 => github.com/golang/text v0.3.0
)
```

