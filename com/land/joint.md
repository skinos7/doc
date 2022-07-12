
***

## Management of joint component
Administration of equipment joint event process
Each project can register its own joint process item (either through the project production tool or directly by modifying the prj.json file), which requires the system to invoke the specified interface at joint event happen

There are multiple joint event cast when system some happened, each of which can register joint items, listed in joint event order:
- network/online
- network/offline
...


#### Configuration( land@joint )

```json
// Attributes introduction 
{
    "joint item name":                             // [ string ]
    {
        "joint":"joint event name",                     // [ string ]
        "call":"specify component or program"           // [ string ]
    }
    // "...":{ ... }     How many joint process items show how many properties
}
// Examples
{
    "online_talk_to_me":                               // call the tui@telnet.reset at the network/online joint event happened
    {
        "joint":"network/onlne",
        "call":"tui@telnet.reset"
    },
    "offline_talk_to_me":                              // call ttui@ssh.shut at the network/online joint event happened
    {
        "joint":"network/offline",
        "call":"tui@ssh.shut"
    }
}
```  

#### **Methods**

+ `add[ joint process name, call, joint event ]` **add a joint process**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, add wui@admin.reset at the network/online happened
    land@joint.add[ webreset, wui@admin.reset, network/online ]
    ttrue
    ```

+ `delete[ joint process name ]` **delete a joint process**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, delete webreset
    land@joint.delete[ webreset ]
    ttrue
    ```

+ `list[ [joint event] ]` **list joint process at joint event**, Not giving the specified joint event will list all registered joint process in the system, *succeed return talk to describes infomation, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "joint event":"call command",  // A joint event only needs to invoke the form of an call
        "joint event":                 // A joint event requires the form of calling multiple calls
        {
            "call command1":"",
            "call command2":""
            // "...":"..."     How many call at that joint event show how many properties
        }
         // "...":{ ... }     How many joint event show how many properties
    }    
    ```
    ```shell
    # examples
    land@joint.list
    {
        "network/on":                        # call client@dhcps.reset when network/on happened
        {
            "client@dhcps.reset":""
        },
        "network/off":                        # call client@dhcps.reset when network/off happened
        {
            "client@dhcps.reset":""
        },
        "network/online":                        # call client@dhcps.reset when network/online happened
        {
            "client@dhcps.reset":""
        },
        "network/offline":                        # call client@dhcps.reset when network/offline happened
        {
            "client@dhcps.reset":""
        }
    }
    ```



## 系统joint事件管理组件
管理系统joint事件处理项, joint事件处理项将在joint事件发生时被调用

#### **joint事件** 
- 每个项目可以注册自已的joint事件处理项(通过项目生产工具或直接修改prj.json文件), 即要求系统在joint事件发生时调用指定的接口
系统有很多可joint事件, 可以为每个joint事件注册处理项, 以下列出常用的joint事件：
    - `network/online`    
    - `network/offline`
    ...

#### **配置( land@joint )**

```json
// 属性介绍
{
    "joint事件处理项名称":               // [ 字符串 ], 事件处理项名称必须在此配置中唯一
    {
        "joint":"joint事件",     // [ 字符串 ]
        "call":"调用接口"        // [ 字符串 ]
    }
    // "...":{ 事件处理项信息 }         // 更多其它的事件处理项项
}
// 以下为示例
{
    "myreset":                           // 处理项名称为myreset
    {
        "joint":"network/online",             // joint事件为network/online
        "call":"uart@gnss.reset"              // 重启GPS
    },
    "myreset2":                         // 处理项名称为myreset2
    {
        "joint":"network/online",           // joint事件为network/online
        "call":"wui@admin.reset",           // 重启web服务
    }
}
```


#### **接口**

+ `add[ 事件处理项名称, 调用接口, 事件名称 ]` **创建事件处理项**, *成功返回ttrue, 失败返回tfalse, 出错返回terror*
    ```shell
    # 示例, 创建在网络上线后调用wui@admin.reset
    land@joint.add[ webreset, wui@admin.reset, network/online ]
    ttrue  
    ```

+ `delete[ 事件处理项名称 ]` **删除事件处理项**, *成功返回ttrue, 失败返回tfalse, 出错返回terror*
    ```shell
    # 示例, 删除webreset事件处理项
    land@joint.delete[ webreset ]
    ttrue
    ```

+ `list[ [事件名称] ]` **列出系统中指定事件的事件处理项**, 不给出指定事件将列出系统中所有注册的事件处理项, *成功返回如下JSON, 失败返回NULL, 出错返回terror*
    ```json
    // 属性介绍
    {
        "事件名称":"调用接口",      // 一个事件名称只需要调用一个接口的形式
        "事件名称":                  // 一个事件名称需要调用多个接口的形式
        {
            "调用接口1":"",
            "调用接口2":""
            // "...":"..."            // 更多此事件名称对应的调用接口
        }
        // "...":{ ... }              // 更多事件名称对应的事件处理项
    }
    ```
    ```shell
    # 示例
    land@joint.list
    {
        "network/on":                        # 启用新接口时调用client@dhcps.reset
        {
            "client@dhcps.reset":""
        },
        "network/off":                        # 关闭接口调用client@dhcps.reset
        {
            "client@dhcps.reset":""
        },
        "network/online":                        # 上线时调用client@dhcps.reset
        {
            "client@dhcps.reset":""
        },
        "network/offline":                        # 掉线时调用client@dhcps.reset
        {
            "client@dhcps.reset":""
        }
    }
    ```



