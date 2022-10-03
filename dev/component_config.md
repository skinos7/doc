
## 管理组件配置

在项目中的程序(组件/可执行程序/共享库)中可基于已有的组件来开发, 通过修改组件配置对组件进行管理

![avatar](./项目及组件开发介绍-管理组件配置.png)



管理其它组件配置时需要事先了解以下文档:

- 管理组件配置的API(本文档介绍)

- 组件名称及其提供的配置
	比如LTE的网络功能对应的组件是ifname@lte组件, 设备基本信息是land@machine, GPS是uart@gnss, 以及这些组件提供的配置
	这部分见[readme](../../readme.md)最后部分的 **系统中常用的组件配置及组件接口**, 点击对应的链接即可查看到对应的组件接口文档, 组件接口文档中有对应的组件配置

- 管理组件配置时需要用到的交互结构, 可参见如下:

	[应用程序开发-组件交互结构talk_t](./应用程序开发-组件交互结构talk_t.md)

	[应用程序开发-组件交互结构obj_t](./应用程序开发-组件交互结构obj_t.md)
    
	[应用程序开发-组件交互结构path_t](./应用程序开发-组件交互结构path_t.md)


------
## 管理组件配置API说明
系统中项目的组件通常会向外提供组件配置, 组件配置通常是组件的 **_get()/_set()** 函数来实现, 而读写这些组件配置来将会最终调用到组件的这两个函数来完成对组件配置的管理

此文档描述的函数接口都位于[land/com.h](./include/land/com.h)中, 通过包含[land/farm.h](./include/land/farm.h)即可
```c
#include "land/farm.h"
```

## 管理组件配置API分类

#### 组件配置查询接口用于查询组件配置
常用的函数有以下几个:

```c
/**
 * @brief 获取组件配置参数
 * @param com 组件名
 * @param path 属性路径
 * @param buffer 字符串值的存放位置
 * @param buflen 字符串值的存放位置的大小
 * @return 返回组件参数的值 */
talk_t       com_get( obj_t obj, path_t path );
const char  *com_gets( obj_t obj, path_t path, char *buffer, int buflen );
talk_t       com_sget( const char *obj, const char *path );
const char  *com_sgets( const char *obj, const char *path, char *buffer, int buflen );
```

#### 组件配置设置接口用于设置组件配置
常用的函数有以下几个:

```c
/**
 * @brief 设置组件配置参数
 * @param com 组件名
 * @param path 属性路径
 * @param value 值
 * @return 设置成功返回true, 失败返回false */
boole com_set( obj_t obj, path_t path, talk_t value );
boole com_sets( obj_t obj, path_t path, const char *value );
boole com_sset( const char *obj, const char *path, talk_t value );
boole com_ssets( const char *obj, const char *path, const char *value );
```



------


## 组件配置操作API示例

#### 读取组件配置

基于传入参数及返回值的类型不同分为不同的函数, 传入两个参数: 组件名称, 属性路径, 返回: 值

- talk_t com_sget( const char *obj, const char *path );
obj为组件名称的字符串, path为属性路径的字符串, 成功返回为值的talk_t结构, 失败返回NULL

示例:
```c
    talk_t ret;
    const char *name;

    /* 获取设备的名称, 即获取land@machine组件配置中name属性的值 */
    ret = com_sget( "land@machine", "name" );
    /* 将返回的JSON结构转换为字符串 */
    name = phrase_string( ret );
    /* 打印转换后的字符串 */
    printf( "machine name is %s\n", name );
    /* 释放返回的值的空间 */
    talk_free( ret );
```

- const char  *com_sgets( const char *obj, const char *path, char *buffer, int buflen ); 
obj为组件名称的字符串, path为属性路径的字符串, 成换返回的是字符串类似的值, 并且如buffer及buflen指出缓存区则还会将字符串的值存入到此缓存区, 失败返回NULL

示例:
```c
    const char *ptr;
    char name[64];
    /* 获到设备的名称, 即获到land@machine组件配置中name属性的值, 并存入name数组中 */
    ptr = com_sgets( "land@machine", "name", name, sizeof(name) );
    printf( "machine name is %s\n", ptr );
```


- const char  *com_gets( obj_t obj, path_t path, char *buffer, int buflen );
obj为组件名称的结构, path为属性路径的结构,  成换返回的是字符串类似的值, 并且如buffer及buflen指出缓存区则还会将字符串的值存入到此缓存区, 失败返回NULL

- talk_t com_get( obj_t obj, path_t path );
obj为组件名称的结构, path为属性路径的结构, 成功返回为值的talk_t结构, 失败返回NULL

示例: 通过com_gets/com_sget/com_sget的实现熟悉com_get的用法: 
```c
talk_t com_sget( const char *obj, const char *path )
{
    path_t p;
    obj_t o;
    talk_t ret;

    /* 将字符串式的组件名称转换为结构化表示 */
    o = obj_create( obj );
    /* 将字符串式的属性路径转换为结构化表示 */
    p = path_create( path );
    /* 调用com_get获取组件配置对应的属性值, 当p为NULL时将会获取整个组件配置 */
    ret = com_get( o, p );
    /* 释放转换后的结构 */
    obj_free( o );
    path_free( p );
    /* 返回获取的值 */
    return ret;
}
const char *com_gets( obj_t obj, path_t path, char *buffer, int buflen )
{
    talk_t info;
    char *str;
    char *ret;
    int len;
    static char string[TEXTLINE_SIZE];
    
    info = com_get( obj, path );
    if ( info == NULL )
    {
        errno = EINVAL;
        return NULL;
    }
    str = talk2string( info );
    if ( str == NULL )
    {
        talk_free( info );
        return NULL;
    }
    talk_free( info );
    ret = string;
    len = sizeof(string);
    if ( buffer != NULL && buflen > 0 )
    {
        ret = buffer;
        len = buflen;
    }
    strncpy( ret, str, len-1 );
    ret[len-1] ='\0';
    free( str );
    return ret;
}
const char *com_sgets( const char *obj, const char *path, char *buffer, int buflen )
{
    obj_t o;
    path_t p;
    const char *ret;

    o = obj_create( obj );
    p = path_create( path );
    ret = com_gets( o, p, buffer, buflen );
    obj_free( o );
    path_free( p );
    return ret;
}

```


#### 修改组件配置

设置组件配置函数基于传入参数的类型不同也分为不同的函数, 传入两个参数: 组件名称, 属性路径, 值
以下函数中当属性路径为空即表示设置整个组件的配置, 这时值就必须为一个完整的JSON对象

- boole com_ssets( const char *obj, const char *path, const char *value );
obj为组件名称的字符串, path为配置路径的字符串, 成功返回为值的talk_t结构, 失败返回NULL

示例:
```c
    /* 设置设备的名称, 即设置land@machine组件配置中name属性的值 */
    if ( com_ssets( "land@machine", "name", "myMachine" ) == true )
    {
        printf( "set the machine name %s succeed\n", "myMachine" );
    }
```

- boole com_sset( const char *obj, const char *path, talk_t value );
obj为组件名称的字符串, path为属性路径的字符串, 成换返回的是字符串类似的值, 并且如buffer及buflen指出缓存区则还会将字符串的值存入到此缓存区, 失败返回NULL


- boole com_sets( obj_t obj, path_t path, const char *value );
obj为组件名称的结构, path为属性路径的结构,  成换返回的是字符串类似的值, 并且如buffer及buflen指出缓存区则还会将字符串的值存入到此缓存区, 失败返回NULL

- boole com_set( obj_t obj, path_t path, talk_t value );
obj为组件名称的结构, path为属性路径的结构, 成功返回为值的talk_t结构, 失败返回NULL

示例: com_sset/com_sets/com_ssets的实现熟悉com_set的用法: 
```c
boole com_sset( const char *obj, const char *path, talk_t value )
{
    path_t p;
    obj_t o;
    boole ret;

    /* 将字符串式的组件名称转换为结构化表示 */
    o = obj_create( obj );
    /* 将字符串式的属性路径转换为结构化表示 */
    p = path_create( path );
    /* 调用com_set设置组件配置对应的属性值, p为NULL时表示将value作为整个组件配置的值 */
    ret = com_set( o, p, value );
    /* 释放转换后的结构 */
    obj_free( o );
    path_free( p );
    /* 返回调用com_set时返回的值 */    
    return ret;
}
boole com_sets( obj_t obj, path_t path, const char *value )
{
    boole ret;
    talk_t info;

    info = string2talk( value );
    ret = com_set( obj, path, info );
    talk_free( info );
    return ret;
}
boole com_ssets( const char *obj, const char *path, const char *value )
{
    path_t p;
    obj_t o;
    talk_t info;
    boole ret;

    o = obj_create( obj );
    p = path_create( path );
    info = string2talk( value );
    ret = com_set( o, p, info );
    talk_free( info );
    obj_free( o );
    path_free( p );
    return ret;
}

```
