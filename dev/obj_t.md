

## 组件名称描述结构obj_t及及属性位置描述结构attr_t

- 在调用组件时, 组件的名称可以使用字符串来表达, 也可以使用obj_t结构来表示, 通过obj_t结构可以更方便的对组件名解析得到如项目名, 组件名等信息

- 在查询或是设置参数时, 属性的位置可以使用字符串来表达, 也可以使用attr_t结构来表示, 通过attr_t结构可以更方便的对多层属性描述做管理

- 此文档描述的函数接口都位于[land/path.h](./include/land/path.h)中, 通过包含land/skin.h即可
```c
    #include "land/skin.h"
```


#### API头文件中的介绍

[land/path.h](./include/land/path.h)


#### 示例
参见**操作项目配置**中的 [参考config_sget, config_sgets, config_get_string, config_gets_string, config_sgets_string及config_sset, config_ssets, config_set_string, config_sset_string, config_ssets_string的实现, 理解针对obj_t及attr_t的操作](./project_config.md#%E5%8F%82%E8%80%83config_sget-config_sgets-config_get_string-config_gets_string-config_sgets_string%E5%8F%8Aconfig_sset-config_ssets-config_set_string-config_sset_string-config_ssets_string%E7%9A%84%E5%AE%9E%E7%8E%B0-%E7%90%86%E8%A7%A3%E9%92%88%E5%AF%B9obj_t%E5%8F%8Aattr_t%E7%9A%84%E6%93%8D%E4%BD%9C)

