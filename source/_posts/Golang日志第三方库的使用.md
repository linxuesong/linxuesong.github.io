---
title: Golang日志第三方库的使用
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
  https://cdn.jsdelivr.net/gh/linxuesong/cdn/img/articleCover/动漫风景/images.jpg
date: 2021-05-20 10:44:05
keywords:
description: 介绍go的第三方日志库，包括使用推荐和介绍以及简单的使用实例
---

# 1.第三方日志库的对比

# 2.Zap

## 2.1简单实例-会把日志打印到控制台

```
//1.快速创建Zap.logger的方法，使用预先写好的配置创建日志变量
//NewExample(Option...)
//NewDevelopment(Option...)
//NewProduction
logger, _ := zap.NewProduction() 

defer logger.Sync() // flushes buffer, if any
//2.创建日志对象后可以打印日志了，有两种打印日志的方式
//2.1效率低一点，但自由度更高
sugar := logger.Sugar()
sugar.Infow("failed to fetch URL",
  // Structured context as loosely typed key-value pairs.
  "url", url,
  "attempt", 3,
  "backoff", time.Second,
)
sugar.Infof("Failed to fetch URL: %s", url)
//2.2效率高一点，要指定类型
defer logger.Sync()
logger.Info("failed to fetch URL",
  // Structured context as strongly typed Field values.
  zap.String("url", url),
  zap.Int("attempt", 3),
  zap.Duration("backoff", time.Second),
)

```



## 2.2定义自己的logger-打印到指定文件

```
//使用zap.New创建自定义的日志变量
//func New(core zapcore.Core, options ...Option) *Logger


//zapcore.Core可以使用zapcore.NewCore，如果需要不同级别日志输出到不同文件使用zapcore.NewTee(Core...)放入多个core
需要需要三个配置
//  Encoder编码器(日志格式)：可以使用预先设置的配置  zapcore.NewJSONEncoder(zap.NewProductionEncoderConfig()),除此之外还有zapcore.NewConsoleEncoder(EncoderConfig)等配置
//  WriterSyncer(日志输出位置):zapcore.AddSync(io.Writer)将打开的文件传入
//  LogLevel(哪些日志级别的日志将被打印): 可以直接使用提供好的日志级别，也可以定制zap.LevelEnablerFunc(func(lvl zapcore.Level) bool) 传入一个函数返回bool用于判断日志级别是否需要被打印

//1.创建Encode日志格式
	encoder := zapcore.NewConsoleEncoder(zapcore.EncoderConfig{
		MessageKey:  "msg",
		LevelKey:    "level",
		EncodeLevel: zapcore.CapitalLevelEncoder,
		TimeKey:     "ts",
		EncodeTime: func(t time.Time, enc zapcore.PrimitiveArrayEncoder) {
			enc.AppendString(fmt.Sprintf("%d%02d%02d_%02d%02d%02d", t.Year(), t.Month(), t.Day(), t.Hour(), t.Minute(), t.Second()))
		},
		CallerKey:    "file",
		EncodeCaller: zapcore.ShortCallerEncoder,
		EncodeDuration: func(d time.Duration, enc zapcore.PrimitiveArrayEncoder) {
			enc.AppendInt64(int64(d) / 1000000)
		},
	})
//2.创建writer日志输出位置
	  file, err := os.OpenFile(logPath, os.O_CREATE|os.O_APPEND|os.O_RDWR, 0744)
	  if err != nil {
		  return 	fmt.Errorf("log file open file ,err:%v", err)
	  }
    writer := apcore.AddSync(writer)
//3.创建logLevel日志输出范围

	// 实现判断日志等级的interface (其实 zapcore.*Level 自身就是 interface)，创建出的level等价于zapcore.InfoLevel
	level := zap.LevelEnablerFunc(func(lvl zapcore.Level) bool {
		return lvl >= zapcore.InfoLevel
	})


	// 4.创建具体core
		zapcore.NewCore(encoder, writer, level)
		
		// 如果要是不同级别日志放到不同文件，用NewTee
    // core := zapcore.NewTee(
    //   zapcore.NewCore(encoder, writer, level),
    //   zapcore.NewCore(encoder2, writer2, level2)
    // )
// 创建logger，可以加入可选项
	logger = zap.New(core, zap.AddCaller()) // 需要传入 zap.AddCaller() 才会显示打日志点的文件名和行数
```



# 3.文件日志切割第三方库

| 仓库                                                         |                    |      |
| ------------------------------------------------------------ | ------------------ | ---- |
| [natefinch](https://github.com/natefinch)/**[lumberjack](https://github.com/natefinch/lumberjack)** | 按文件大小自动切割 |      |
| [lestrrat-go](https://github.com/lestrrat-go)/**[file-rotatelogs](https://github.com/lestrrat-go/file-rotatelogs)** | 按找时间自动切割   |      |
|                                                              |                    |      |

```
	/* 日志轮转相关函数
	Filename: 日志文件的位置
	MaxSize：在进行切割之前，日志文件的最大大小（以MB为单位）
	MaxBackups：保留旧文件的最大个数
	MaxAges：保留旧文件的最大天数
	Compress：是否压缩/归档旧文件
	*/
	writer := &lumberjack.Logger{
		Filename:   logPath,
		MaxSize:    100,
		MaxBackups: 5,
		MaxAge:     5,
		Compress:   false,
	}
```



```
	/* 日志轮转相关函数
	`WithLinkName` 为最新的日志建立软连接
	`WithRotationTime` 设置日志分割的时间，隔多久分割一次
	WithMaxAge 和 WithRotationCount二者只能设置一个
	`WithMaxAge` 设置文件清理前的最长保存时间
	`WithRotationCount` 设置文件清理前最多保存的个数
	*/
	writer, err := rotatelogs.New(
		logPath+".%Y-%m-%d-%H:%M",
		rotatelogs.WithLinkName(logPath),
		rotatelogs.WithMaxAge(time.Duration(24)*time.Hour),
		rotatelogs.WithRotationTime(time.Duration(60)*time.Hour),
	)
```

