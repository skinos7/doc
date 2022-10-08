
## 操作项目配置

SkinOS中对于配置的存储有专门的机制, 所有的配置信息都是以  **项目名@配置名称**  为一个JSON的方式来存储在对应的项目中

- 在程序中通过给出**项目名@配置名称**使用config_get/config_set系列的函数操作项目配置
- 在终端中给出**项目名@配置名称**使用he指令也可以操作项目配置（同名组件未实现_get/_set函数时）
- 在远程调用中给出**项目名@配置名称**使用JSON指令也可以操作项目配置（同名组件未实现_get/_set函数时）
- 在开发中给出**项目名@配置名称**使用sget/sset系列函数也可以操作项目配置（同名组件未实现_get/_set函数时）



## 项目配置与组件配置的关系

##### 示例, 如在verify项目下有unicom.cfg的JSON文件, 并且verify项目下无同名的unicom组件或有unicom组件但未实现_get/_set函数
 - 编程中通过config_get/config_set系统函数给出verify@unicom可操作对应的unicom.cfg中的JSON配置
 - 在终端通过he指令给出verify@unicom可操作对应的unicom.cfg中的JSON配置
 - 远程通过JSON指令给出verify@unicom可操作对应的unicom.cfg中的JSON配置
 - 编程中通过sget/sset系列函数给出verify@unicom可操作对应的unicom.cfg中的JSON配置
 - 即verify@unicom为**项目配置**

##### 示例, 如在verify项目下有telecom4g.cfg的JSON文件, 并且verify项目下有同名的telecom4g组件, telecom4g组件也实现了_get/_set函数
 - 编程中通过config_get/config_set系统函数给出verify@telecom4g可操作对应的telecom4.cfg中的JSON配置
 - 在终端通过he指令给出verify@telecom4g操作对应的JSON配置时将调用verify项目下telecom4g组件的_get/_set函数
 - 远程通过JSON指令给出verify@unicom可操作对应的JSON配置时将调用verify项目下telecom4g组件的_get/_set函数
 - 编程中通过sget/sset系列函数给出verify@unicom可操作对应的JSON配置将调用verify项目下telecom4g组件的_get/_set函数
 - 即verify@telecom4g为**组件配置**


## 操作项目配置时需要用到的交互结构
 - [项目及组件开发-组件交互结构talk_t](./talk_t.md)
 - [项目及组件开发-寻址结构obj_t/attr_t](./obj_t.md)



## 项目配置操作API说明

此文档描述的函数接口都位于[land/config.h](./include/land/config.h)中, 通过包含[land/skin.h](./include/land/skinhead.h)即可
```c
    #include "land/skin.h"
```


## API头文件中的介绍

[land/config.h](./include/land/config.h)


## 项目配置操作API分类

##### 获取项目配置

```c
/**
 * @brief 获取对象的配置
 * @param com 项目配置名称
 * @param attr 属性路径
 * @param buffer 存储获取到的字符串返回值存放位置
 * @param buflen 描述参数buffer的大小
 * @return 成功返回值, 失败返回NULL, 出错还可能返回TALK_EJSON/TALK_EPERM/TALK_EINVAL等错误值 */
talk_t      config_get( obj_t com, attr_t attr );
talk_t      config_sget( const char *com, attr_t attr );
talk_t      config_sgets( const char *com, const char *attr, ... );
const char *config_get_string( char *buffer, int buflen, obj_t com, attr_t attr );
const char *config_gets_string( char *buffer, int buflen, obj_t com, const char *attr, ... );
const char *config_sgets_string( char *buffer, int buflen, const char *com, const char *attr, ... );
```

##### 设置项目配置
```c
/**
 * @brief 设置对象配置
 * @param com 项目配置名称
 * @param attr 属性路径
 * @param value 值(树结构式或字符串), 指出修改为此值
 * @return 修改成功返回true, 修改失败返回false */
boole config_set( obj_t com, talk_t value, attr_t attr );
boole config_sset( const char *com, talk_t value, attr_t attr );
boole config_ssets( const char *com, talk_t value, const char *attr, ... );
boole config_set_string( obj_t com, const char *value, attr_t attr );
boole config_sset_string( const char *com, const char *value, attr_t attr );
boole config_ssets_string( const char *com, const char *value, const char *attr, ... );
```

##### 列出所有的项目配置
```c
/**
 * @brief 列出项目下所有的配置
 * @param project 项目名
 * @return 返回项目下所有配置 */
talk_t config_list(   const char *project );
```

##### 获取项目配置存放的目录
```c
/**
 * @brief 得到项目的配置
 * @param buffer 缓冲区
 * @param buflen 缓冲区大小
 * @param project 项目名
 * @param oscformat 配置文件名
 * @return 项目配置路径 */
const char *config_path( char *buffer, int buflen, const char *project, const char *oscformat, ... );
```


## 项目配置操作API示例

- 读取并打印LTE的网络设置
```c
    talk_t cfg;

    /* 读取ifname@lte的配置 */
    cfg = config_sget( "ifname@lte", NULL );
    /* 打印整个ifname@lte的配置 */
    talk_print( cfg );

    /* 使用完后必须要释放对应的结构 */
    talk_free( cfg );
```
- 读取并打印LTE的模块的APN设置(使用config_sgets_string接口)
```c
    const char *apn；
    char buffer[256];

    /* 读取modem@lte的配置中的profile_cfg属性下的apn属性的值 */
    apn = config_sgets_string( buffer, sizeof(buffer), "modem@lte", "profile_cfg/apn" );
    if ( apn != NULL && *apn != '\0' )
    {
        /* 打印获取到的APN */
        printf( "LTE APN is %s\n", apn );
    }
    else
    {
        printf( "LTE APN is NONE\n" );
    }
```
- 读取并打印LTE的模块的APN设置(使用config_sget接口)
```c
    talk_t cfg;
    talk_t oper;
    const char *apn

    /* 读取modem@lte的配置 */
    cfg = config_sgetg( "modem@lte", NULL );
    /* 获取modem@lte下属性为profile_cfg的JSON树 */
    oper = json_value( cfg, "profile_cfg" );
    /* 获取profile_cfg的JSON树下属性为apn的值 */
    apn = json_string( oper, "apn" );
    if ( apn != NULL && *apn != '\0' )
    {
        /* 打印获取到的APN */
        printf( "LTE APN is %s\n", apn );
    }
    else
    {
        printf( "LTE APN is NONE\n" );
    }
    /* 使用完后必须要释放对应的结构 */
    talk_free( cfg );
```

- 编写设置LTE的APN为1234(使用config_ssets_string接口)
```c
    /* 直接个修改modem@lte中profile_cfg/apn属性的值为1234, 即设置apn为1234 */
    if ( config_ssets_string( "modem@lte", "1234", "profile_cfg/apn" ) == false )
    {
        printf( "Setting the LTE APN failed\n" );
        return;
    }
    /* 直接修改modem@lte中profile属性的值为enable, 即启用profile功能 */
    if ( config_ssets_string( "modem@lte", "enable", "profile" ) == true )
    {
        printf( "Setting the LTE APN succeed\n" );
    }
    else
    {
        printf( "Setting the LTE APN failed\n" );
    }
```

- 编写设置LTE的APN为1234(使用confg_sset接口)
```c
    talk_t cfg;
    talk_t oper;

    /* 读取modem@lte的配置 */
    cfg = config_sget( "modem@lte", NULL );
    /* 获取modem@lte下属性为profile_cfg的JSON树 */
    oper = json_value( cfg, "profile_cfg" );
    /* 如果modem@lte下无profile_cfg的JSON树 */
    if ( oper == NULL )
    {
        /* 创建一个JSON树 */
        oper = json_create(NULL);
        /* 将创建的JSON树作为profile_cfg属性的值添加到modem@lte的配置中 */
        json_set_value( cfg, "profile_cfg", oper );
    }
    /* 在profile_cfg JSON树下增加apn属性, 值为1234 */
    json_set_string( oper, "apn", "1234" );
    /* 将modem@lte配置中的自定义APN的功能打开, 即设置modem@lte下的profile属性的值为enable */
    json_set_string( cfg, "profile", "enable" );

    /* 将修改后的modem@lte配置保存到系统中 */
    if ( confg_sset( "modem@lte", cfg, NULL ) == true )
    {
        printf( "Setting the LTE APN succeed\n" );
    }
    else
    {
        printf( "Setting the LTE APN failed\n" );
    }

    /* 使用完后必须要释放对应的结构 */
    talk_free( cfg );
```


## 参考config_sget, config_sgets, config_get_string, config_gets_string, config_sgets_string及config_sset, config_ssets, config_set_string, config_sset_string, config_ssets_string的实现, 理解针对obj_t及attr_t的操作

```c
talk_t      config_sget( const char *com, attr_t attr )
{
    obj_t o;
    talk_t ret;

    o = obj_create( com );
    ret = config_get( o, attr );
    obj_free( o );
    return ret;
}
talk_t      config_sgets( const char *com, const char *attr, ... )
{
    obj_t o;
    attr_t a;
    talk_t ret;
    va_list arglist;
    char attrs[PATH_MAX];

    o = obj_create( com );
    if ( attr != NULL )
    {
        va_start( arglist, attr );
        vsnprintf( attrs, sizeof(attrs), attr, arglist );
        va_end( arglist );
		a = attr_create( attrs );
    }
	else
	{
		a = NULL;
	}
    ret = config_get( o, a );
    obj_free( o );
    attr_free( a );
    return ret;
}
const char *config_get_string( char *buffer, int buflen, obj_t com, attr_t attr )
{
    char *str;
    talk_t info;
    static char string[LINE_MAX];
    
    info = config_get( com, attr );
    if ( info == NULL )
    {
        return NULL;
    }
    str = talk2string( info );
    if ( str == NULL )
    {
        talk_free( info );
		errno = ENOMSG;
        return NULL;
    }
    talk_free( info );
    if ( buffer == NULL || buflen <= 0 )
    {
        buffer = string;
        buflen = sizeof(string);
    }
    strncpy( buffer, str, buflen-1 );
    buffer[buflen-1] ='\0';
    efree( str );
    return buffer;
}
const char *config_gets_string( char *buffer, int buflen, obj_t com, const char *attr, ... )
{
    attr_t a;
    const char *ret;
    va_list arglist;
    char attrs[PATH_MAX];

    if ( attr != NULL )
    {
        va_start( arglist, attr );
        vsnprintf( attrs, sizeof(attrs), attr, arglist );
        va_end( arglist );
		a = attr_create( attrs );
    }
	else
	{
		a = NULL;
	}
    ret = config_get_string( buffer, buflen, com, a );
    attr_free( a );
    return ret;
}
const char *config_sgets_string( char *buffer, int buflen, const char *com, const char *attr, ... )
{
    obj_t o;
    attr_t a;
    const char *ret;
    va_list arglist;
    char attrs[PATH_MAX];

    o = obj_create( com );
    if ( attr != NULL )
    {
        va_start( arglist, attr );
        vsnprintf( attrs, sizeof(attrs), attr, arglist );
        va_end( arglist );
		a = attr_create( attrs );
    }
	else
	{
		a = NULL;
	}
    ret = config_get_string( buffer, buflen, o, a );
    obj_free( o );
    attr_free( a );
    return ret;
}

boole config_sset( const char *com, talk_t value, attr_t attr )
{
    obj_t o;
    boole ret;

    o = obj_create( com );
    ret = config_set( o, value, attr );
    obj_free( o );
    return ret;
}
boole config_ssets( const char *com, talk_t value, const char *attr, ... )
{
    obj_t o;
    attr_t a;
    boole ret;
    va_list arglist;
    char attrs[PATH_MAX];

    o = obj_create( com );
    if ( attr != NULL )
    {
        va_start( arglist, attr );
        vsnprintf( attrs, sizeof(attrs), attr, arglist );
        va_end( arglist );
		a = attr_create( attrs );
    }
	else
	{
		a = NULL;
	}
    ret = config_set( o, value, a );
    obj_free( o );
    attr_free( a );
    return ret;
}
boole config_set_string( obj_t com, const char *value, attr_t attr )
{
	talk_t v;
	boole ret;

	v = string2x( value );
	ret = config_set( com, v, attr );
	talk_free( v );
	return ret;
}
boole config_sset_string( const char *com, const char *value, attr_t attr )
{
	talk_t v;
	boole ret;

	v = string2x( value );
	ret = config_sset( com, v, attr );
	talk_free( v );
	return ret;
}
boole config_ssets_string( const char *com, const char *value, const char *attr, ... )
{
	talk_t v;
    attr_t a;
	boole ret;
    va_list arglist;
    char attrs[PATH_MAX];

	v = string2x( value );
    if ( attr != NULL )
    {
        va_start( arglist, attr );
        vsnprintf( attrs, sizeof(attrs), attr, arglist );
        va_end( arglist );
		a = attr_create( attrs );
    }
	else
	{
		a = NULL;
	}
	ret = config_sset( com, v, a );
	talk_free( v );
    attr_free( a );
	return ret;
}

```
