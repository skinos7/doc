
## 组件交互结构talk_t及API说明

系统中项目的组件交互数据正常都使用JSON格式来表示, 而JSON的二进制结构即是talk_t, talk_t为一个JSON的结构化的句柄, 其对应的是HEAP中动配分配的内存, 需要动态分配及释放

此文档描述的函数接口都位于[land/talk.h](./include/land/talk.h)中, 通过包含land/skin.h即可
```c
    #include "land/skin.h"
```


#### JSON简介

talk_t是用来表示JSON结构的, JSON结构也就是由以下三种结构之间的嵌套组合而成:
- json树
    以{开头并以}结尾的JSON我们称为json树
    ```json
    json树
    {
        "attr":"value"
    }
    json树
    {
        "attr":"value",
        "attr2":"value"
    }
    json树
    {
        "attr":
        {
            "attr22":"value"
        }
    }
    json树
    {
        "attr":"value",
        "attr2":
        {
            "attr22":"value"
        }
    }
    json树
    {
    }
    ```
- 属性值对(axp)
    以"字符串"加冒号再加"字符串"的属性及值
    ```json
    属性值对
    "attr":"value"
    属性值对
    "attr":""
    ```
    以"字符串"加冒号再加json树的属性及json树的值
    ```json
    属性值对
    "attr":
    {
        "attr22":""
    }
    属性值对
    "attr":
    {
        "attr22":"",
        "attr23":""
    }
    属性值对
    "attr":
    {
        "attr22":
        {
            "attr222":"value"
        }
    }
    属性值对
    "attr":
    {
        "attr22":
        {
            "attr222":"value"
        },
        "attr23":"value"
    }
    属性值对
    "attr":
    {
    }
    ```
- 值(x), 值即是字符串, 它即可用来表示值, 也可以用来表示属性名
    即"字符串"
    ```json
    值
    "attr"
    值
    ""
    值
    "value"
    ```



#### API头文件中的介绍

[land/talk.h](./include/land/talk.h)



#### 示例1
创建一个如下json对应的talk_t结构
```c
/* 需要创建如下json结构
{
    "myname":"peng",
    "myhome":
    {
        "father":"zhou",
        "mother":"chong",
        "grandma":"duan",
        "sister":
        {
            "old":"li",
            "young":"an"
        }
    }
}
*/
talk_t create_my( void )
{
    talk_t ret;
    talk_t myhome;
    talk_t sister;
    talk_t young;
    talk_t axp;
    talk_t phrese;
    talk_t v;

    /* 创建两个json树 */
    ret = json_create( NULL );
    myhome = json_create( NULL );

    /* 在ret下创建 "myname":"peng" */
    json_set_string( ret, "myname", "peng" );

    /* 在ret下创建 "myhome":{} */
    json_set_value( ret, "myhome", myhome );

    /* 在myhome下创建 "father":"zhou" */
    json_set_string( myhome, "father", "zhou" );
    /* 以另一种方式在myhome下创建 "mother":"chong" */
    phrese = string2x( "chong" );
    axp = axp_create( "mother", NULL, phrese );
    json_attach_axp( myhome, axp );
    /* 以另一种方式在myhome下创建 "grandma":"duan" */
    axp = axp_create( "grandma", "duan", NULL );
    json_attach_axp( myhome, axp );

    /* 创建sister的json树 */
    sister = json_create( NULL );
    /* 向sister的json树中加入 "old":"li" */
    json_set_string( sister, "old", "li" );
    /* 向sister的json树中加入 "young":"an" */
    json_set_string( sister, "young", "an" );
    /* 创建 "sister":{...} 属性值对 */
    axp = axp_create( "sister", NULL, sister );
    /* 将 "sister":{...} 属性值对 加入myhome树中 */
    json_attach_axp( myhome, sister );

    /* 返回创建的整个json树 */
    return ret;
}

```

#### 示例2
基于示例1返回的ret, 我们对其做增删改查的操作
```c

/* 在myhome下增加一个brother属性值对 */
talk_t add_brother( talk_t my )
{
    talk_t myhome;
    talk_t sister;

    myhome = json_value( my, "myhome" );
    json_set_string( myhome, "brother", "zhou" );
    return my;
}

/* 删除myhome下的sister下的old属性值对 */
talk_t delete_old( talk_t my )
{
    talk_t myhome;
    talk_t sister;

    myhome = json_value( my, "myhome" );
    sister = json_value( myhome, "sister" );
    json_delete_axp( sister, "old" );
    return my;
}

/* 修改myhome下的sister下的young的值为mina */
talk_t modify_young( talk_t my )
{
    talk_t myhome;
    talk_t sister;

    myhome = json_value( my, "myhome" );
    sister = json_value( myhome, "sister" );
    json_set_string( sister, "young", "mina" );
    return my;
}

/* 遍例myhome树下的属性值对并打印其值的类型 */
talk_t list_myhome( talk_t my )
{
    talk_t myhome;
    talk_t axp;
    talk_t v;
    const char *attr;

    myhome = json_value( my, "myhome" );
    axp = NULL;
    whlie( NULL != ( axp = json_next( myhome, axp ) ) )
    {
        attr = axp_id( axp );
        v = axp_value( axp );
        if ( x_check( v ) == true )
        {
            printf( "%s 的值为一个字符串: %s\n", attr, x_text(v) );
        }
        else
        {
            if ( json_next( v, NULL ) == NULL )
            {
                printf( "%s 的值为一个空的JSON树\n", attr );
            }
            else
            {
                printf( "%s 的值为一个JSON树\n", attr );
            }
        }
    }

}

```