
------
## 组件交互结构path_t及API说明

FarmOS中的配置正常都是JSON格式的方式保存, 而JSON是树型结构, 在操作JSON格式的配置时需要一种寻址方式, 因此使用路径结构path_t来实现寻址, 用来表示配置的路径

此文档描述的函数接口都位于[land/path.h](./include/land/path.h)中, 通过包含land/farm.h即可
```c
    #include "land/farm.h"
```

## 路径API分类

##### 创建及释放路径结构 
```c
/**
 * @brief 创建一个路径结构
 * @param 字符串, 此字符串会被copy到路径结构中, 此字符串的格式通常是: 属性名/下层属性名/下下层属性名
 * @return 成功返回一个路径结构, 失败返回NULL*/
path_t path_create( const char *path );
/**
 * @brief 释放一个路径结构
 * @param 路径结构
 * @return 无返回*/
void path_free( path_t p );
```
##### 获到参数的个数
```c
/**
 * @brief 得到路径结构中的路径层次数
 * @param 路径结构
 * @return 成功返回层次灵敏, 失败返回-1 */
int path_level( path_t p );
```
##### 获到指定参数
```c
/**
 * @brief 得到路径结构中指定层次的路径名
 * @param p 路径结构
 * @param serial 层次数
 * @return 成功返回字符串, 失败返回NULL */
const char *path_get( path_t p, int serial );
```
##### 将path_t的结构化的参数转化为字符串式的表示
```c
/**
 * @brief 得到路径结构的字符串表示
 * @param 路径结构
 * @return 成功返回字符串, 失败返回NULL */
const char *path_string( path_t p );
```
