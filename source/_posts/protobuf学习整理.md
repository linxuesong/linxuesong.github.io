---
title: protobuf学习整理
author: linxuesong
avatar: 'https://cdn.jsdelivr.net/gh/linxuesong/cdn/img/avatar.jpg'
authorLink: linxuesong.github.io
authorAbout: 一个好奇的人
authorDesc: 一个好奇的人
categories:
  - 技术
comments: true
tags:
  - protobuf
  - go
photos: >-
  https://cdn.jsdelivr.net/gh/linxuesong/cdn/img/articleCover/鬼刃/200929110029-3-1200.jpg
date: 2021-06-03 19:53:54
keywords:
description: protobuf学习整理归纳
---

# 一、ProtoBuf简介

语言平台无关的、灵活、高效、自动化的序列化机制

类似协议：XML、JSON

区别点：<u>XML、JSON关注人类可读性，通常用于双方交互的协议；ProtoBuf更关注压缩效率、传输速度，人类可读性差(指序列化之后的文件)</u>

# 二、如何用？

## 2.1golang语言

### 2.1.0环境准备

需要如下两个工具

1.**protoc**:可以执行不同语言的api，生成不同语言版本的结构体文件

2.**protoc-gen-go**:go版本的生成程序可以生成go语言的结构体

以上工具不同版本生成的文件是不一样的，所以安需要下载指定版本

安装最新版本

```
1.安装最新的protoc-gen-go, 在gopath路径下执行如下命令
go get github.com/golang/protobuf/protoc-gen-go // protoc-gen-go会安到$gopath/bin下,如果自己下载编译，也要放到这个路径下
2.安装最新的protobuf
https://github.com/protocolbuffers/protobuf/releases //下载后解压，可以做其他的部分
```

--------------------------

安装之前的版本

```
1.安装之前版本的protoc-gen-go, 在gopath路径下执行如下命令
GIT_TAG="v1.2.0"
go get -d -u github.com/golang/protobuf/protoc-gen-go
git -C "$(go env GOPATH)"/src/github.com/golang/protobuf
checkout $GIT_TAG
go install github.com/golang/protobuf/protoc-gen-go
2.安装之前版本的protobuf
https://github.com/protocolbuffers/protobuf/releases
```

### 2.2.1准备原协议.proto文件

```
message xxx {
  // 字段规则：required -> 字段只能也必须出现 1 次
  // 字段规则：optional -> 字段可出现 0 次或1次
  // 字段规则：repeated -> 字段可出现任意多次（包括 0）
  // 类型：int32、int64、sint32、sint64、string、32-bit ....
  // 字段编号：0 ~ 536870911（除去 19000 到 19999 之间的数字）
  字段规则 类型 名称 = 字段编号;
}
```



```protobuf
// 例1: 在 xxx.proto 文件中定义 Example1 message  
// 包含五个字段，依次为string,bytes,EmbeddedMessage自定义结构体,repeatedInt32Val,repeatedStringVal
syntax = "proto3";  // protobuf版本
package user;  // 声明protobuf文件所在包，方便被其他protobuf文件导入结构体，一般放到proto/自定义包名路径下
option go_package = "github.com/xvrzhao/pb-demo/proto/user";  // 声明生成的go文件所属的包
  
import "proto/user/message.proto";  // 导入同包内的其他 proto 文件
import "proto/article/message.proto";  // 导入其他包的 proto 文件
message Example1 {
    optional string stringVal = 1;
    optional bytes bytesVal = 2;
    message EmbeddedMessage {
        int32 int32Val = 1;
        string stringVal = 2;
    }
    optional EmbeddedMessage embeddedExample1 = 3;
    repeated int32 repeatedInt32Val = 4;
    repeated string repeatedStringVal = 5;
}
```

### 2.2.3生成proto.go文件

```
protoc --go_out={输出位置} {.proto文件路径}
// 例如  protobuf包解压路径/src/protoc --go_out=. msg.proto
//protoc如果没有加入到/usr/local/bin
```

## 2.2 JAVA语言

### 2.2.3编译命令

- -I 后面是 proto 文件所在目录
- --java_out 后面是 java 文件存放地址
- 最后一行是 proto 文件名称

```
protoc -I=src/main/resource/proto --java_out=src/main/java gps_data.proto
```





```
public class Main {
    public static void main(String[] args) {
        System.out.println("===== 构建一个GPS模型开始 =====");
        GpsDataProto.gps_data.Builder gps_builder = GpsDataProto.gps_data.newBuilder();
        gps_builder.setAltitude(1);
        gps_builder.setDataTime("2017-12-17 16:21:44");
        gps_builder.setGpsStatus(1);
        gps_builder.setLat(39.123);
        gps_builder.setLon(120.112);
        gps_builder.setDirection(30.2F);
        gps_builder.setId(100L);

        GpsDataProto.gps_data gps_data = gps_builder.build();
        System.out.println(gps_data.toString());
        System.out.println("===== 构建GPS模型结束 =====");

        System.out.println("===== gps Byte 开始=====");
        for (byte b : gps_data.toByteArray()) {
            System.out.print(b);
        }
        System.out.println("\n" + "bytes长度" + gps_data.toByteString().size());
        System.out.println("===== gps Byte 结束 =====");

        System.out.println("===== 使用gps 反序列化生成对象开始 =====");
        GpsDataProto.gps_data gd = null;
        try {
            gd = GpsDataProto.gps_data.parseFrom(gps_data.toByteArray());
        } catch (InvalidProtocolBufferException e) {
            e.printStackTrace();
        }
        System.out.print(gd.toString());
        System.out.println("===== 使用gps 反序列化生成对象结束 =====");
    }
}
```



### 2.2.4常见问题

```
<dependency>
    <groupId>com.google.protobuf</groupId>
    <artifactId>protobuf-java</artifactId>
    <version>3.8.0</version>
</dependency>
```









```
Send Encrypt Format:https://im.58.com/msg/sendmsg?params=KpGqIsMkjMQ-hlsc9cr2AwXdcBcQVFgKzupEoQ9nubVvlaSyJ7hQLMsdh2CTBRoNCN2KAjsd9TY04YrxQr246CdFY3ynkdh15qSM9Msyu1o_9NmhvStJo8Ib9MGIsvpSMVTnut9W1M_D5gRidqBhMSRRWQPS_9OXZr0GUPYL6H8OU7EBnqW0vc6YOoVQAVOtrSJE0sP4gaXrHtWD09QvUnr8xcyO5blJQz5NCgRcTSEtCQl9geBnKSc5XTqSDDwyBQ5eXwOtq-ge_H-ZlGyuUgo_u-jcRIy63d7-OaZgoPrFBYztNEsZyYAE7yNn5jdOJu2T7Oazz92i5YB5x4e_O7pZv4Erm-tsoQaN10t59g4jSZr2WciigoaHnng0woIlGKHSJtleql-EKfKaW3nIePaPQWuA6H0iDFHMA_HB7IuMN_HkZ1g3o1BovuU-YvvTJwi_cVpOM6VauqAGIBtf5VEXKevq2vjfeeU7I_e1-HwZcULA2TmlC-nYNmVvchFvevOGL9bUEqHydbaEkTfVAw9hPFLQTBiTJeyjrz0r-M_TkbZlPkNeZkbhnQAktHaYN5gtMQYzRXSI7JNWNJwsjFKLHuUa9Ut0YBPFjYlpjcmd2_AiIcWGhs6JaHZMP6K2zzgI2qcxxw9Z1YMwYjmezaoLOsB6Yf5jg4UIrKHLzy70pdu-_CVi5tjKoPrVrGDnOOoTKJhpi3Ny-NztIPlwPYjJtZtZU8Y9HPHHqoRdvmk3eAKTLOLyk1u65p-4YkNCl2QksptlYVCAvrtbS94l35gRQ-lEMs4fUGgIP-jir4QjLBD101IRVg96X7e6XszNCkX_RpONx_Uh51ZaxlJ5iNG8_TCZLyuCD7EgQyPcFTmaubHmsm0HmzespMIsmkUOrEvvMbh-2wqCdV5EAJP-NjKY_HQ16DiC0u4xkV111eaAwc1HkrBlrAy7XECAa5lM1ln3fDj25gThpGpthQKVKjs39dQqC5Yc93m6tYpsZTg%3D&version=a1.0
```

