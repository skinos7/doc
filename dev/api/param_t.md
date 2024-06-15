
## 组件交互结构param_t及API说明

当在调用组件接口时想传入参数时需要用到, 或者在编写组件接口时解析传入的参数时用到

此文档描述的函数接口都位于[land/param.h](./include/land/param.h)中, 通过包含land/skin.h即可
```c
    #include "land/skin.h"
```


#### API头文件中的介绍

[land/param.h](./include/land/param.h)



#### 创建及释放参数结构函数
```c
/**
 * @brief 创建一个参数结构
 * @param string 此字符串会被copy到参数结构中, 字符串的格式通常是: 参数1,参数2,参数3
 * @param json 此JSON中的属性1/2/3/4/...会被copy到参数结构中
 * @return 成功返回一个参数结构, 失败返回NULL*/
param_t param_create( const char *string );
param_t param_build( talk_t json );
/**
 * @brief 释放一个参数结构
 * @param parameter 参数结构
 * @return 无返回*/
void param_free( param_t parameter );
```

#### 获取参数的个数函数
```c
/**
 * @brief 得到参数结构中的参数个数
 * @param parameter 参数结构
 * @return 成功返回参数个数, 失败返回-1 */
int param_size( param_t parameter );
```

#### 获取指定参数函数
```c
/**
 * @brief 得到参数结构中指定位置的参数, 此返回值在paramter释放后不可用
 * @param parameter 参数结构
 * @param serial 参数位置(从1开始)
 * @return 成功返回talk_t结构式的参数, 失败返回NULL */
talk_t param_talk( param_t parameter, int serial );
/**
 * @brief 得到参数结构中指定位置的参数, 此返回值在paramter释放后不可用
 * @param parameter 参数结构
 * @param serial 参数位置(从1开始)
 * @return 成功返回字符串式的参数, 失败返回NULL */
const char *param_string( param_t parameter, int serial );
```

#### 将param_t的结构化的参数转化为字符串式的表示
```c
/**
 * @brief 得到参数结构的字符串表示, 此返回值在paramter释放后不可用
 * @param parameter 参数结构
 * @return 成功返回字符串, 在对应的param_t结构释放后此返回值不可用, 失败返回NULL */
const char *param_combine( param_t parameter );
```

