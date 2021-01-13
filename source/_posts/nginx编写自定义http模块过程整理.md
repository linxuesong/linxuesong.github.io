---
title: nginx编写自定义http模块过程整理
author: linxuesong
avatar: 'https://cdn.jsdelivr.net/gh/linxuesong/cdn/img/avatar.jpg'
authorLink: linxuesong.github.io
authorAbout: 一个好奇的人
authorDesc: 一个好奇的人
categories: 技术
comments: true
photos: >-
  https://cdn.jsdelivr.net/gh/linxuesong/cdn/img/articleCover/动漫女/20120Q20240-7-lp.jpg
date: 2020-12-21 17:22:22
tags: nginx
keywords:
description:
---

# 一、整体过程梳理

1.编写nginx_http_module_t变量nginx_http_hello_module

2.挂载到处理http请求过程种

3.



# 二、具体编写

我们编写过程采用总分的结构，先写整体,再具体每一个成员

## 1.定义自定义http模块变量  ngx_http_hello_module

### 1.1模板结构体ngx_http_module_t成员说明 

说明  ♥是重点变量

````
ngx_http_module_t ngx_http_hello_module {
   ngx_uint_t            ctx_index; // 该模块在当前类别(http类别，core event mail)中的排名序号 nginx框架用到
   ngx_uint_t            index;  // 该模块在所有类别模块中的排名序号   nginx框架用到
 
   ngx_uint_t            spare0;//一共四个sapre保留变量暂未用
   ngx_uint_t            spare1;
   ngx_uint_t            spare2;
   ngx_uint_t            spare3;
 
   ngx_uint_t            version; // 模块版本  包含当前变量在内之前的共7个变量可以用提供好的#define NGX_MODULE_V1去填充
 
   void                 *ctx;  // 模块的上下文结构 一个非常重要的变量,主要作用:1.设置读取配置文件完成前后的回调函数，①对不同配置值如何处理②设置该模块挂载到http流程的方式③是处理http请求并返回http响应的一个位置，可以以按阶段处理的方式挂在到http处理流程中2.设置不同级别配置项创建方法，供nginx框架遇到模块感兴趣的配置项时调用创建响应的自定义配置项信息结构体   ♥
   
    ngx_command_t        *commands; // 指令集合,当和配置文件某项匹配后 执行自定义的指令函数   主要作用:遇到配置项文件后执行自定义函数，函数可以①读取配置文件内容；②是一个处理http请求的位置，以按需分配的方式挂载到http处理流程中♥
    
    ngx_uint_t            type; //模块类型  core event  http mail ♥
 
    ngx_int_t           (*init_master)(ngx_log_t *log);  // 初始化master执行
    ngx_int_t           (*init_module)(ngx_cycle_t *cycle); // 初始化module执行
    ngx_int_t           (*init_process)(ngx_cycle_t *cycle); 
    ngx_int_t           (*init_thread)(ngx_cycle_t *cycle);
    void                (*exit_thread)(ngx_cycle_t *cycle);
    void                (*exit_process)(ngx_cycle_t *cycle);
    void                (*exit_master)(ngx_cycle_t *cycle); // 退出master执行
 
    uintptr_t             spare_hook0; // 保留字段未用,可以用提供好的#define NGX_MODULE_V1_PADDING取填充8个变量
    uintptr_t             spare_hook1;
    uintptr_t             spare_hook2;
    uintptr_t             spare_hook3;
    uintptr_t             spare_hook4;
    uintptr_t             spare_hook5;
    uintptr_t             spare_hook6;
    uintptr_t             spare_hook7;
}
````

### 1.2自定义模板变量ngx_http_hello_module

````
/*宏定义变量说明
 #define NGX_MODULE_V1          0, 0, 0, 0,NGX_DSO_ABI_COMPATIBILITY, NGX_NUMBER_MAJOR, NGX_NUMBER_MINOR   //前七个成员的初始化     
 #define NGX_MODULE_V1_PADDING  0, 0, 0, 0, 0, 0, 0, 0   //后八个成员的初始化
*/
ngx_module_t ngx_http_hello_module = {
        NGX_MODULE_V1,
        &ngx_http_hello_module_ctx,    /* module context ♥*/
        ngx_http_hello_commands,       /* module directives ♥*/
        NGX_HTTP_MODULE,               /* module type ♥*/
        NULL,                          /* init master */
        NULL,                          /* init module */
        NULL,                          /* init process */
        NULL,                          /* init thread */
        NULL,                          /* exit thread */
        NULL,                          /* exit process */
        NULL,                          /* exit master */
        NGX_MODULE_V1_PADDING
};
````

接下来对其三个♥成员进行分析，可以直接按目录跳转

## 2.ngx_http_hello_module_ctx模块上下文结构void  *ctx(实际上是一组模块处理流程的回调函数指针)

读取配置并保存到我们自己定义的结构体中

对于http模块可能的配置类别有 http、server、location三种，根据我们的需要看要定义几种，如果我们的模块只需要location的配置，对某一路由进行处理那只需要自定义保存location配置信息的结构体即可

### 2.1结构体定义如下

````c
    typedef struct {
        ngx_int_t   (*preconfiguration)(ngx_conf_t *cf); ///* 在解析http{}块内的配置项前回调 */
        ngx_int_t   (*postconfiguration)(ngx_conf_t *cf); // /* 在解析http{}块内的配置项后回调 */ ♥

        void       *(*create_main_conf)(ngx_conf_t *cf); // 创建 本模块所在的http block的配置信息结构
        char       *(*init_main_conf)(ngx_conf_t *cf, void *conf); // 初始化 本模块所在的http block配置信息结构

        void       *(*create_srv_conf)(ngx_conf_t *cf); // 创建server block的配置信息存储结构
        char       *(*merge_srv_conf)(ngx_conf_t *cf, void *prev, void *conf); // 合并不同级别的server的配置信息存储结构,可无

        void       *(*create_loc_conf)(ngx_conf_t *cf); // 创建location block的配置信息存储结构 ♥我们关心哪一个级别的配置就写哪一个级别的
        char       *(*merge_loc_conf)(ngx_conf_t *cf, void *prev, void *conf); // 合并不同级别location的,可无
    } ngx_http_module_t; 
````

### 2.2自定义变量

````
    static int ngx_hello_visited_times = 0; 

    static ngx_http_module_t ngx_http_hello_module_ctx = {
        NULL,                          /* preconfiguration */
        ngx_http_hello_init,           /* postconfiguration */ 

        NULL,                          /* create main configuration */
        NULL,                          /* init main configuration */

        NULL,                          /* create server configuration */
        NULL,                          /* merge server configuration */

        ngx_http_hello_create_loc_conf, /* create location configuration */
        NULL                            /* merge location configuration */
    };
````

### 2.3其中两个回调函数的定义

#### 2.3.1postconfiguration——ngx_http_hello_init

````
// ngx_http_hello_init 当加载完配置文件后执行 1.把当前模块加入处理流程--按处理阶段挂载  2.把配置文件中hello_string 并发送回去 处理http请求
// 这个只有当
	static ngx_int_t
    ngx_http_hello_init(ngx_conf_t *cf)
    {
        ngx_http_handler_pt        *h;
        ngx_http_core_main_conf_t  *cmcf;

        cmcf = ngx_http_conf_get_module_main_conf(cf, ngx_http_core_module);
		// 把当前模块挂载在到NGX_HTTP_CONTENT_PHASE阶段中
		// Mount the current module to NGX_ HTTP_ CONTENT_ In phase
        h = ngx_array_push(&cmcf->phases[NGX_HTTP_CONTENT_PHASE].handlers); 
        if (h == NULL) {
            return NGX_ERROR;
        }

        *h = ngx_http_hello_handler; // ♥ 对于读取的配置文件做何种处理，因为此时已经读取配置文件完了可以获取配置文件中的信息

        return NGX_OK;
    }
//
    static ngx_int_t
    ngx_http_hello_handler(ngx_http_request_t *r)
    {
        ngx_int_t    rc;
        ngx_buf_t   *b;
        ngx_chain_t  out;
        ngx_http_hello_loc_conf_t* my_conf; // 用户保存配置文件存储结构体
        u_char ngx_hello_string[1024] = {0};
        ngx_uint_t content_length = 0;

        ngx_log_error(NGX_LOG_EMERG, r->connection->log, 0, "ngx_http_hello_handler is called!");

        my_conf = ngx_http_get_module_loc_conf(r, ngx_http_hello_module); // 获取本地配置♥
        if (my_conf->hello_string.len == 0 )
        {
            ngx_log_error(NGX_LOG_EMERG, r->connection->log, 0, "hello_string is empty!");
            return NGX_DECLINED;
        }

        if (my_conf->hello_counter == NGX_CONF_UNSET
            || my_conf->hello_counter == 0)
        {
            ngx_sprintf(ngx_hello_string, "%s", my_conf->hello_string.data);
        }
        else
        {
            ngx_sprintf(ngx_hello_string, "%s Visited Times:%d", my_conf->hello_string.data, 
                ++ngx_hello_visited_times);
        }
        ngx_log_error(NGX_LOG_EMERG, r->connection->log, 0, "hello_string:%s", ngx_hello_string);
        content_length = ngx_strlen(ngx_hello_string);

        /* we response to 'GET' and 'HEAD' requests only */
        if (!(r->method & (NGX_HTTP_GET|NGX_HTTP_HEAD))) {
            return NGX_HTTP_NOT_ALLOWED;
        }

        /* discard request body, since we don't need it here */
        rc = ngx_http_discard_request_body(r); // 如果不处理http请求体需要调用discard舍弃

        if (rc != NGX_OK) {
            return rc;
        }

        /* set the 'Content-type' header */
        /*
         *r->headers_out.content_type.len = sizeof("text/html") - 1;
         *r->headers_out.content_type.data = (u_char *)"text/html";
                 */
        ngx_str_set(&r->headers_out.content_type, "text/html");

        /* send the header only, if the request type is http 'HEAD' */
        if (r->method == NGX_HTTP_HEAD) {
            r->headers_out.status = NGX_HTTP_OK;
            r->headers_out.content_length_n = content_length;

            return ngx_http_send_header(r);
        }

        /* allocate a buffer for your response body */
        b = ngx_pcalloc(r->pool, sizeof(ngx_buf_t));
        if (b == NULL) {
            return NGX_HTTP_INTERNAL_SERVER_ERROR;
        }

        /* attach this huocongqu buffer to the buffer chain */
        out.buf = b;
        out.next = NULL;

        /* adjust the pointers of the buffer */
        b->pos = ngx_hello_string; // 来自于配置文件中的hello_string
        b->last = ngx_hello_string + content_length;
        b->memory = 1;    /* this buffer is in memory */
        b->last_buf = 1;  /* this is the last buffer in the buffer chain */

        /* set the status line */
        r->headers_out.status = NGX_HTTP_OK;
        r->headers_out.content_length_n = content_length;

        /* send the headers of your response */
        rc = ngx_http_send_header(r); // 发送回http响应头

        if (rc == NGX_ERROR || rc > NGX_OK || r->header_only) {
            return rc;
        }

        /* send the buffer chain of your response */
        return ngx_http_output_filter(r, &out);
    }

````



#### 2.3.2create_loc_conf——ngx_http_hello_create_loc_conf

```
    // 只是创建一个存配置信息的结构体并初始化一些默认初始值 ，提供一个空间
    // 在读取配置文件过程中遇到location block中匹配的字符串就创建一个配置结构体(自定义的)返回
    static void *ngx_http_hello_create_loc_conf(ngx_conf_t *cf)
    {
        ngx_http_hello_loc_conf_t* local_conf = NULL;
        local_conf = ngx_pcalloc(cf->pool, sizeof(ngx_http_hello_loc_conf_t));//ngx_http_hello_loc_conf_t自己定义保存配置信息的
        if (local_conf == NULL)
        {
            return NULL;
        }

        ngx_str_null(&local_conf->hello_string); // 设置成null字符串
        local_conf->hello_counter = NGX_CONF_UNSET; // 设置成-1

        return local_conf; // 返回一个配置信息变量
    } 
    
    // 自定义配置信息结构体
    typedef struct
    {
        ngx_str_t hello_string;
        ngx_int_t hello_counter;
    }ngx_http_hello_loc_conf_t;
```

## 3. ngx_http_hello_commands  指令集合 *commands当遇到模块感兴趣的配置后做相应处理，读取配置文件保存到自定义配置信息结构体中

### 3.3.1结构体定义ngx_command_t

```
struct ngx_command_t {
    ngx_str_t             name;          // 指令名称
    ngx_uint_t            type;          // 指令所在的context和包含的参数个数
    char               *(*set)(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);     // 解析配置，并将参数存入模块配置结构体中,实现时可以调用14中预设方法
    ngx_uint_t            conf;          // 存放配置信息结构体的种类  是http、server、location哪一种，使用宏定义NGX_HTTP_LOC_CONF_OFFSET
    ngx_uint_t            offset;        // 指令参数的存储偏移量
    void                 *post;     	 // 用途归于用户使用，我们暂不使用
};



struct ngx_conf_s {
    char                 *name; // 感兴趣配置项名♥
    ngx_array_t          *args; // 保存所有的配置项的参数值   比如apps 1 2 3 那apps配置项就有3个整数型的参数♥

    ngx_cycle_t          *cycle; // 存放所有moudule模块  (模块都有自己的序号)
    ngx_pool_t           *pool; // 内存池对象用于申请内存的变量
    ngx_pool_t           *temp_pool; // 临时内存池变量
    ngx_conf_file_t      *conf_file; // 和整个配置文件绑定
    ngx_log_t            *log; // 打印日志

    void                 *ctx; // 上下文
    ngx_uint_t            module_type; // 模块类型 http core mail event
    ngx_uint_t            cmd_type; // 指令类型  ——配置项的类型  是由一个参数还是开关类型还是有2个以上参数的

    ngx_conf_handler_ptr   handler; // 匹配到响应的匹配项就执行对应的处理函数，函数一般是将配置文件中的配置项的若干变量读取出来放到自定义的配置信息结构体中 ♥
    char                 *handler_conf;
};
```



### 3.3.2自定义指令集合变量

````
// 可以看到数组有两个元素，模块感兴趣的配置是hello_string 和hello_counter
static ngx_command_t ngx_http_hello_commands[] = {
       { 
            ngx_string("hello_string"),
            NGX_HTTP_LOC_CONF|NGX_CONF_NOARGS|NGX_CONF_TAKE1, // 表示可以接收多种类型的配置项
            ngx_http_hello_string, // 函数，将配置文件中的hello_string读取出来放到自定义结构体中 注：有预定义的解题配置项值的方法14个
            NGX_HTTP_LOC_CONF_OFFSET, // 表示要存放到自定义的location配置信息保存体
            offsetof(ngx_http_hello_loc_conf_t, hello_string), // hello_string是变量名,offsetof返回其在location配置信息结构体中的偏移量
            NULL },

        { //和上面类似
            ngx_string("hello_counter"),
            NGX_HTTP_LOC_CONF|NGX_CONF_FLAG,
            ngx_http_hello_counter,
            NGX_HTTP_LOC_CONF_OFFSET,
            offsetof(ngx_http_hello_loc_conf_t, hello_counter),
            NULL },               

        ngx_null_command
    };
// 从配置文件中读取配置hello_string    
static char *  ngx_http_hello_string(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
    {
        ngx_http_hello_loc_conf_t* local_conf;

        local_conf = conf;
        char* rv = ngx_conf_set_str_slot(cf, cmd, conf); //14种预置方法之一如果配置项只有一个参数且希望string形式保存

        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0, "hello_string:%s", local_conf->hello_string.data);

        return rv;
    }    
    
// 从配置文件中读取配置hello_counter后放入到自定义配置结构体中
static char *ngx_http_hello_counter(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
    {
        ngx_http_hello_loc_conf_t* local_conf;

        local_conf = conf; // 指针传递

        char* rv = NULL;

        rv = ngx_conf_set_flag_slot(cf, cmd, conf); // 如果配置项是on或off则将变量 设置成1或0，哪一个变量在ngx_command_t中偏移量指出

        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0, "hello_counter:%d", local_conf->hello_counter);
        return rv;    
    }
    
````

# 三、从http请求通过的流程分析如何编写自定义模块

markdown如何画流程图