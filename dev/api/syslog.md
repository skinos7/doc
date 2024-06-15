

## 日志API说明

通过此API可以向系统的syslog日志记录信息
此文档描述的函数接口都位于[land/syslog.h](./include/land/syslog.h)中, 通过包含[land/skin.h](./include/land/skin.h)即可
```c
    #include "land/skin.h"
```

#### API头文件中的介绍

[land/syslog.h](./include/land/syslog.h)



## 服务API分类

##### 打开或关闭日志API 
在组件中不建议调用
```c
/**
 * @brief 打开SYSLOG(类似于openlog)
 * @param name 指出项目名
 * @param flags 指出全局的日志的类型及日志的选项
 * @return 无*/
void syslog_open( const char *name, int flags );
/**
 * @brief 关闭LOG占用的资源
 * @return 无*/
void syslog_close( void );
```
##### 记录日志API
```c
/**
 * @brief 内部实际的日志记录函数
 * @param flags 针对本条日志的标识
 * @param filename 当前记录日志的文件名
 * @param line 当前记录日志的代码的行号
 * @param format 日志内容
 * @return 无*/
void syslog_string( unsigned int flags, const char *filename, int line, const char *format, ... );
```
##### 常用的日志记录的宏 
这些宏都是对syslog_string的封装, 使记录日志更简单, 建议使用以下宏而不是直接去调用syslog_string();

- 记录调试日志
```c
    debug( "this is a %s log, level %d", "debug", 10 );
```
- 记录提示日志
```c
    info( "this is a %s log, level %d", "info", 10 );
```
- 记录警告日志
```c
    /* 记录警告 */
    warn( "this is a %s log, level %d", "warn", 10 );
    /* 记录警告, 并附带errno变量的值*/
    warning( "this is a %s log, level %d", "warn", 10 );
```
- 记录错误日志
```c
    /* 记录错误 */
    fault( "this is a %s log, level %d", "error", 10 );
    /* 记录错误, 并附带errno变量的值*/
    faulting( "this is a %s log, level %d", "error", 10 );
```

## 日志管理
通过[land@syslog](../com/land/syslog.md)组件接口可以管理日志, 比如查看日志, 清除日志等



