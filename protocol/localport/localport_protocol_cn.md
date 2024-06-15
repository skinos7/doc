

## 本地被管理协议说明

网关可接受来自局域网的管理协议, 管理协议通常由批量管理工具或本地的其它设备发出, 通过此协议批量管理工具或其它设备可以实现局域网管理网关



#### 协议分类

在局域网与网关通信分为三种协议
- **TCP(JSON)控制协议(端口22220), 用于通过TCP发送JSON指令管理网关**
- **局域网搜索协议(UDP端口22222), 用于在局域网内搜索所有的网关**
- **局域网查询协议(UDP端口22222), 用于在局域网内搜索所有的网关并查询所有网关的信息(不常用)**

![avatar](./localport_protocol.png)

---

## TCP(JSON)控制协议
通过 **TCP端口22220** 与网关交互JSON指令， 实现对网关的控制, 使用TCP协议交互, 适合交互各种信息

#### 在网关上开启JSON控制协议

默认网关不会响应TCP(JSON)控制协议, 需要进入管理网页打开此协议, *打开此协议会存在安全风险，请确保局域网安全*
![avatar](./localport_jsonwui.png)   


#### 与网关的交互流程
- 如下图所示  
![avatar](./localport_control.png)
- 交互简介  
    每一次的交互都需要建立TCP连接, 然后再发送JSON指令, 网关收到JSON指令将会回复JSON指令的执行结果, 之后将立即关闭TCP连接, 因此, 每一次交互都需要建立一个TCP连接, 也称之为**短连接**, 为保证指令的完整性, 指令被设计成一个完整的JSON对象, 同样回复信息也是一个完整的JSON对象, 对于网关的操作可以分为三种JSON指令：
	1. 查询配置：用于查询网关的配置
	2. 修改配置：用于修改网关的配置
	3. 调用功能接口(API)：用于获取或修改网关的状态等

#### JSON指令格式 --- HE指令模式
- 直接使用JSON包装HE指令
    以下是JSON格式包装HE指令格式介绍
    ```json
    {
        "cmd1":"HE指令"   // [ 字符串 ]:[ 字符串 ] 属性名可随意命名, 用于在JSON中唯一的标识当前指令, 由此可实现在一个交互中多个指令, 网关回复时也以此指令命名标识其回复
        // 更多指令...
    }
    ```
    网关跟据HE指令执行的结果返回内容, 格式可为:
    1. 一个JSON
        ```json
        {
            "cmd1":{JSON格式的配置内容}
        }
        ```
    2. 一个字符串
        ```json
        {
            "cmd1":"属性值"
        }
        ```
    3. 空, 表示不存在此项配置
        ```json
        {
            "cmd1":"NULL"
        }
        ```
    例1：如查询网关的基本配置的HE指令为 land@machine, 对应的json指令格式为
    ```json
    { "cmd1":"land@machine" }
    ```
    例2：如查询网关名称的HE指令为 land@machine:name, 对应的json指令格式为
    ```json
    { "cmd1":"land@machine:name" }
    ```
    例2：如查询网关工作模式的HE指令为 land@machine:mode, 对应的json指令格式为
    ```json
    { "cmd1":"land@machine:mode" }
    ```
    例3：如查询网关LTE/NR(4G/5G)网络的配置的HE指令为 ifname@lte, 对应的json指令格式为
    ```json
    { "cmd1":"ifname@lte" }
    ```    
    例4：如查询网关LTE/NR(4G/5G)网络的状态的HE指令为 ifname@lte.status, 对应的json指令格式为
    ```json
    { "cmd1":"ifname@lte.status" }
    ```
    例5：如调用clock@date(系统时间)的ntpsync方法实现与ntp1.aliyun.com的NTP对时的HE指令为clock@date.ntpsync[ntp1.aliyun.com], 对应的json指令格式为
    ```json
    { "cmd1":"clock@date.ntpsync[ntp1.aliyun.com]" }
    ```
    例6：也可以同时执行多条HE指令, 如果重启一下LTE/NR(4G/5G)网络先执行ifname@lte.shut再执行ifname@lte.setup, 对应的json指令格式为
    ```json
    { "cmd1":"ifname@lte.shut", "cmd2":"ifname@lte.setup" }
    ```
    *更多HE终端指令介绍见此文档 [HE指令介绍](../../use/he/he_command_cn.md)*

    
#### JSON指令格式 --- JSON模式

- 查询网关配置交互格式介绍, 查询网关配置的终端指令格式为 ***组件名称[:属性/属性/...]***
    以下是JSON指令格式介绍
    ```json
    {
        "cmd1":   // [ 字符串 ]:{} 可随意命名, 用于在JSON中唯一的标识当前指令, 由此可实现在一个交互中多个指令, 网关回复时也以此指令命名标识其回复
        {
            "com":"组件名称",       // [ 字符串 ], 组件名称用于指定网关的功能项, 如agent@remote为网关的远程管理, land@machine为网关的基本配置
            "ab":"属性[/属性/…]"    // [ 字符串 ], 可选, 组件名称对应的功能项的配置都是一个完整的JSON, 通过此属性可只查询指定的属性, 无表示查询组件名称对应功能项所有配置
        }
        // 更多指令...
    }
    ```
    跟据网关的实际配置返回值的格式可为：
    1. 一个JSON
        ```json
        {
            "cmd1":{JSON格式的配置内容}
        }
        ```
    2. 一个字符串， 查询时"ab"有指定属性
        ```json
        {
            "cmd1":"属性值"
        }
        ```
    3. 空, 表示不存在此项配置
        ```json
        {
            "cmd1":"NULL"
        }
        ```
    例1：如查询网关的基本配置的HE指令为 land@machine , 对应的json指令格式为
    ```json
    { "cmd1": { "com":"land@machine" } }
    ```
    例2：如查询网关名称的HE指令为 land@machine:name , 对应的json指令格式为
    ```json
    { "cmd1": { "com":"land@machine","ab":"name" } }
    ```
    例2：如查询网关工作模式的HE指令为 land@machine:mode , 对应的json指令格式为
    ```json
    { "cmd1": { "com":"land@machine","ab":"mode" } }
    ```
    例3：如查询网关LTE/NR(4G/5G)网络的配置的HE指令为 ifname@lte , 对应的json指令格式为
    ```json
    { "cmd1": { "com":"ifname@lte" } }
    ```

- 修改网关配置交互格式介绍, 修改网关配置的HE指令格式为 ***组件名称[:属性/属性/...]=值***
    以下是JSON指令格式介绍 --- 当值为字符串时
    ```json
    {
        "cmd1": // [ 字符串 ]:{} 可随意命名, 用于在JSON中唯一的标识当前指令, 由此可实现在一个交互中多个指令, 网关回复时也以此指令命名标识其回复
        {
            "com":"组件名称",       // [ 字符串 ], 组件名称用于指定网关的功能项, 如agent@remote为网关的远程管理, land@machine为网关的基本配置
            "ab":"属性[/属性/…]",   // [ 字符串 ], 可选, 组件名称对应的功能项的配置都是一个完整的JSON, 通过此属性可只查询指定的属性, 无表示查询组件名称对应功能项所有配置
	        "op":"=",              // 指定操作为赋值
	        "v":"值"               // [ 字符串 ]
        }
    }
    ```
    以下是JSON指令格式介绍 --- 当值为JSON对象时
    ```json
    {
        "cmd1":                    // [ 字符串 ]:{} 可随意命名, 用于在JSON中唯一的标识当前指令, 由此可实现在一个交互中多个指令, 网关回复时也以此指令命名标识其回复
        {
            "com":"组件名称",       // [ 字符串 ], 组件名称用于指定网关的功能项, 如agent@remote为网关的远程管理, land@machine为网关的基本配置
            "ab":"属性[/属性/…]",   // [ 字符串 ], 可选, 组件名称对应的功能项的配置都是一个完整的JSON, 通过此属性可只查询指定的属性, 无表示查询组件名称对应功能项所有配置
	        "op":"=",              // 指定操作为赋值
	        "v":{JSON格式的值}      // [ JSON ]
        }
    }
    ```
    网关返回值成功为ttrue, 失败时为tfalse：
    1. 返回ttrue
        ```json
        {
            "cmd1":"ttrue"
        }
        ```
    2. 返回tfalse
        ```json
        {
            "cmd1":"tfalse"
        }
        ```
    例1：如修改网关语言的HE指令为 land@machine:language=en , 对应的json指令格式为
    ```json
    { "cmd1": { "com":"land@machine", "ab":"language", "op":"=", "v":"en" } }
    ```
    例2：如修改网关名称的HE指令为 land@machine:name=NewName , 对应的json指令格式为
    ```json
    { "cmd1": { "com":"land@machine","ab":"name", "op":"=", "v":"NewName" } }
    ```


- 调用网关接口交互格式介绍, 调用网关接口的HE指令格式为 ***组件名称.接口名称[ 参数1, 参数2, 参数3 ]***
    以下是JSON指令格式介绍
    ```json
    {
        "cmd1": // [ 字符串 ]:{} 可随意命名, 用于在JSON中唯一的标识当前指令, 由此可实现在一个交互中多个指令, 网关回复时也以此指令命名标识其回复
        {
            "com":"组件名称",       // [ 字符串 ], 组件名称用于指定网关的功能项，如ifname@lte为网关的LTE网络, network@frame为网关的网络连接框架
	        "op":"接口名称",        // [ 字符串 ]，指定调用组件什么接口, 不通的接口有不同的功能, 如ifname@lte的status接口返回LTE网络状态, ifname@lte的shut接口表示断开LTE的连接
	        "1":"参数1",            // [ 字符串 ]，可选, 参数可为字符串(即引号开头及引号结尾), 也可以为JSON(即{开头}结尾)
	        "2":"参数2",            // [ 字符串 ]，可选, 参数可为字符串(即引号开头及引号结尾), 也可以为JSON(即{开头}结尾)
            "3":"参数3"             // [ 字符串 ]，可选, 参数可为字符串(即引号开头及引号结尾), 也可以为JSON(即{开头}结尾)
        }
    }
    ```
    跟据调用接口不同, 网关返回值可分为以下五种：
    1. 返回ttrue, 通常用于表示操作成功
        ```json
        {
            "cmd1":"ttrue"
        }
        ```
    2. 返回tfalse, 通常用于表示操作失败
        ```json
        {
            "cmd1":"tfalse"
        }
        ```
    3. 返回JSON, 通常表示操作的返回信息
        ```json
        {
            "cmd1":{返回JSON内容}
        }
        ```
    4. 返回字符串, 通常表示操作的返回信息
        ```json
        {
            "cmd1":"返回字符串内容"
        }
        ```
    5. 无返回, 有的接口不返回任何信息
        ```json
        {
            "cmd1":"NULL"
        }
        ```
    例1：如获取网关基本状态的HE指令为 land@machine.status , 对应的json指令格式为
    ```json
    { "cmd1": { "com":"land@machine", "op":"status" } }
    ```
    例2：如获取网关LTE/NR(4G/5G)网络状态的HE指令为 ifname@lte.status , 对应的json指令格式为
    ```json
    { "cmd1": { "com":"ifname@lte", "op":"status" } }
    ```
    例3：如查询网关定位信息的HE指令为 gnss@nmea.info , 对应的json指令格式为
    ```json
    { "cmd1": { "com":"gnss@nmea", "op":"info" } }
    ```



#### 示例-获取网关基本信息配置
- 网关基本信息在land@machine组件的配置中, 发送查询land@machine配置指令即可(在终端中的命令为land@machine), 点击 [设备基本信息](../../com/land/machine.md) 查看有关配置的介绍
```json
{
    "cmd1":
    {
        "com":"land@machine"
    }
}
```
- 网关返回示例
```json
{
    "cmd1":
    {
        "mode":"gateway",                              // 网关工作模式为宽带路由
        "name":"5228-128870",                          // 网关名称为5228-128870
        "mac":"00:03:7F:12:88:70",                     // 网关MAC为00:03:7F:12:88:70
        "macid":"00037F128870",                        // 网关ID为00037F128870
        "language":"cn",                               // 网关语言为chinese
        "cfgversion":"134"                             // 网关配置版本为134(暗示网关配置被修改过134次)
    }
}
```
使用TCP客户端工具测试:   
![avatar](./localport_jsontest.png)

#### 示例-获取网关基本状态
- 网关基本状态由land@machine组件的status接口返回, 发送调用land@machine组件status方法指令即可(在终端中的命令为land@machine.status), 点击 [设备基本信息](../../com/land/machine.md) 查看有关status接口的介绍
```json
{
    "cmd1":
    {
        "com":"land@machine",
        "op":"status"
    }
}
```
- 网关返回
```json
{
    "cmd1":
    {
        "mode":"gateway",                     // 网关工作模式为宽带路由
        "name":"5228-128870",                 // 网关名称为5228-128870
        "platform":"smtk2",
        "hardware":"mt7621",
        "custom":"d228",                      // 产品编号
        "scope":"std",
        "version":"v7.2.1231",                // 软件版本
        "livetime":"12:06:00:2",              // 在线时长  时：分：秒：天
        "current":"15:36:52:03:02:2023",      // 当前时间  时:分:秒:月:日:年
        "mac":"00:03:7F:12:88:70",            // 网关MAC为00:03:7F:12:88:70
        "macid":"00037F128870",
        "model":"5228",                       // 产品型号
        "cmodel":"",
        "magic":"0E82CEC20232FFFF",
        "cfgversion":"134"                    // 网关配置版本为134(暗示网关配置被修改过134次)
    }
}
```



#### 示例-获取LTE/NR(4G/5G)网络状态信息
- LTE/NR(4G/5G)状态信息由ifname@lte的status接口返回, 点击 [LTE/NR(4G/5G)网络](../../com/ifname/lte.md) 及 [LTE/NR(4G/5G)基带](../../com/modem/lte.md) 查看有关status接口的介绍
```json
{
    "cmd1":
    {
        "com":"ifname@lte",
        "op":"status"
    }
}
```
- 网关返回
```json
{
    "cmd1":
    {
        "mode":"dhcpc",                    // IPv4的连接模式为DHCP
        "netdev":"usb0",                   // 网络设备为usb0
        "gw":"10.137.89.118",              // 网关为10.137.89.118, 只有连接成功后才出现
        "dns":"120.80.80.80",              // DNS为120.80.80.80,, 只有连接成功后才出现
        "dns2":"221.5.88.88",              // 备用DNS为221.5.88.88, 只有连接成功后才出现
        "status":"up",                     // "up"表示连接成功
                                                 // [ "setup", "register", "ready", "nodevice", "reset", "down", "up" ]
                                                 // "setup" 为正在初始化模块
                                                 // "register" 为正在注册网络
                                                 // "ready" 为链路正常准备发起连网, 此状态暗示信号/网络/SIM卡都已检测到
                                                 // "nodevice" 为没有找到对应的LTE模组
                                                 // "reset" 为正在重置LTE模组
                                                 // "down" 为网络未连接
                                                 // "up" 为连接成功
        "ip":"10.137.89.117",              // IP地址为10.137.89.117, 只有连接成功后才出现
        "mask":"255.255.255.252",          // 掩码为255.255.255.252, 只有连接成功后才出现
        "livetime":"00:15:50:0",           // 表示已上线15分钟50秒, 只有连接成功后才出现
        "rx_bytes":"1256",                 // 收到了1256字节, 只有连接成功后才出现
        "rx_packets":"4",                  // 收到了4包, 只有连接成功后才出现
        "tx_bytes":"1320",                 // 发送了1320字节, 只有连接成功后才出现
        "tx_packets":"4",                  // 发送了4包, 只有连接成功后才出现
        "mac":"02:50:F4:00:00:00",         // MAC地址为02:50:F4:00:00:00
        "method":"slaac",                  // IPv6地址模式为slaac
        "addr":"fe80::50:f4ff:fe00:0",     // IPv6的地址为fe80::50:f4ff:fe00:0
        "imei":"867160040494084",          // IMEI号为867160040494084
        "imsi":"460015356123463",          // IMSI为460015356123463
        "iccid":"89860121801097564807",    // SIM卡的ICCID为89860121801097564807
                                                 // [ number, "nosim", "pin", "puk" ]
                                                 // 数字为SIM卡的ICCID号
                                                 // "nosim" 为未找到SIM卡
                                                 // "pin" 为SIM卡需要PIN码
                                                 // "puk" 为SIM卡PIN码错误

        "csq":"14",                        // CSQ为14
        "signal":"3",                      // 信号格数为3格
                                                 // [ "0", "1", "2", "3", "4" ],
                                                 // "0" 为无信号
                                                 // "1" 为一格信号, 为最弱的信号
                                                 // "4" 为四格信号, 为最强的信号
        "plmn":"46001",                    // PLMN为46001
        "nettype":"WCDMA",                 // 网络制式为WCDMA
        "rssi":"-107",                     // 信号强度为-107
        "operator":"中国联通",              // 运营商的名称为中国联通
        "operator_advise":                 // 针对 中国联通 建议的配置
        {
            "dial":"*99#",                    // 拨号号码为*99#
            "apn":"3gnet"                     // APN为3gnet
        }
    }
}
```



#### 示例-断开LTE/NR(4G/5G)网络, 必须要有LTE/NR(4G/5G)网络的工作模式下才有效(如在4G/5G路由器或混合模式下)
- 断开LTE网络连接调用ifname@lte组件的shut接口(在终端中的命令为ifname@lte.shut), 点击 [LTE/NR(4G/5G)网络](../../com/ifname/lte.md) 查看shut接口介绍
```json
{
    "cmd1":
    {
        "com":"ifname@lte",             // LTE网络组件
        "op":"shut"                     // 调用shut接口断开
    }
}
```
***注意, 实际发送时不允许包含注解***
- 网关返回
```json
{
    "cmd1":"ttrue"
}
```

#### 示例-发起LTE/NR(4G/5G)连网, 必须要有LTE/NR(4G/5G)网络的工作模式下才有效(如在4G/5G路由器或混合模式下)
- 启用LTE/NR(4G/5G)连网调用ifname@lte组件的setup接口(在终端中的命令为ifname@lte.setup), 点击 [LTE/NR(4G/5G)网络](../../com/ifname/lte.md) 查看setup接口介绍
```json
{
    "cmd1":
    {
        "com":"ifname@lte",              // LTE网络组件
        "op":"setup"                    // 调用setup接口发起连接
    }
}
```
***注意, 实际发送时不允许包含注解***
- 网关返回
```json
{
    "cmd1":"ttrue"
}
```



#### 示例-设置禁用LTE/NR(4G/5G)网络(禁用后重启后也会保持禁用), 将改变网关的配置不建议频繁使用
- 设置禁用LTE/NR(4G/5G)网络即是将ifname@lte配置中的status属性改为disable即可(在终端中的命令为ifname@lte:status=disable), 点击 [LTE/NR(4G/5G)网络](../../com/ifname/lte.md) 查看配置介绍
```json
{
    "cmd1":
    {
        "com":"ifname@lte",             // LTE网络组件
        "ab":"status",                  // 指定修改status属性
        "op":"=",                       // 赋值操作
        "v":"disable"                   // 将status属性的值改为disable即禁用
    }
}
```
***注意, 实际发送时不允许包含注解***
- 网关返回
```json
{
    "cmd1":"ttrue"
}
```

#### 示例-设置启用LTE/NR(4G/5G)连网(启用后重启后也会保持启用), 将改变网关的配置不建议频繁使用
- 设置启用LTE/NR(4G/5G)网络即是将ifname@lte配置中的status属性改为enable即可(在终端中的命令为ifname@lte:status=enable), 点击 [LTE/NR(4G/5G)网络](../../com/ifname/lte.md) 查看配置介绍
```json
{
    "cmd1":
    {
        "com":"ifname@lte",             // LTE网络组件
        "ab":"status",                  // 指定修改status属性
        "op":"=",                       // 赋值操作
        "v":"enable"                    // 将status属性的值改为enable即启用
    }
}
```
***注意, 实际发送时不允许包含注解***
- 网关返回
```json
{
    "cmd1":"ttrue"
}
```


#### 示例-设置LTE/NR(4G/5G)网络的拨号APN相关的配置
- 修改ifname@lte的配置即可, 修改APN需要先打开APN自定义, 然后设置APN相关的信息, 整个指令需要修改多项属性值, 点击 [LTE/NR(4G/5G)网络](../../com/ifname/lte.md) 及 [LTE/NR(4G/5G)基带](../../com/modem/lte.md) 相关的配置介绍
```json
{
    "cmd1":
    {
        "com":"ifname@lte",            // LTE网络
        "op":"|",                      // 或操作, 即只修改以下给出的属性的值, ifname@lte组件配置中其它未在v中给出的属性保留原来的值(如果op的值为=号将会删除其它的属性)
        "v":
        {
            "profile":"enable",        // 打开APN自定义
            "profile_cfg":             // 自定义APN的信息
            {
                "dial":"*99#",          // 拨号号码
                "apn":"NewAPN",         // APN
                "user":"ctnet",         // 用户名
                "passwd":"234352"       // 密码
            }
        }
    }
}
```
***注意, 实际发送时不允许包含注解***
- 网关返回
```json
{
    "cmd1":"ttrue"
}
```


#### 示例-获取第二个LTE/NR(4G/5G)网络状态信息(对于双模块网关)
- 第二个LTE/NR状态信息由ifname@lte2的status接口返回(在终端中的命令为ifname@lte2.status), 点击[LTE/NR(4G/5G)网络](../../com/ifname/lte.md)及[LTE/NR(4G/5G)基带](../../com/modem/lte.md)查看有关status接口的介绍
```json
{
    "cmd1":
    {
        "com":"ifname@lte2",
        "op":"status"
    }
}
```
- 网关返回
```json
{
    "cmd1":
    {
        ... // 内容与 6 相同
    }
}
```



#### 示例-使用第一个LTE/NR(4G/5G)模块发送短信
- 第一个LTE/NR的模块为modem@lte, 点击[LTE/NR(4G/5G)基带](../../com/modem/lte.md)查看有关smssend接口的介绍
```json
{
    "cmd1":
    {
        "com":"modem@lte",
        "op":"smssend",
        "1":"+13266606322",
        "2":"这是一个测试短信"
    }
}
```   
- 网关返回
```json
{
    "cmd1":"ttrue"
}
```    


#### 示例-获取第一个LTE/NR(4G/5G)模块的所有短信
- 第一个LTE/NR的模块为modem@lte, 点击[LTE/NR(4G/5G)基带](../../com/modem/lte.md)查看有关smslist接口的介绍
```json
{
    "cmd1":
    {
        "com":"modem@lte",
        "op":"smslist"
    }
}
```   
- 网关返回
```json
{
    "cmd1":
    {
        "lte.612f6C":
        {
            "id":"lte.612f6C",
            "contact":"8617688704240",
            "date":"23-12-18 22:50:01",
            "content":"看下午方便的话可以   "
        },
        "lte.Y9kWLV":
        {
            "id":"lte.Y9kWLV",
            "contact":"8617688704240",
            "date":"23-12-18 22:50:03",
            "content":"要   现的"
        },
        "lte.ovV6nw":
        {
            "id":"lte.ovV6nw",
            "contact":"8617688704240",
            "date":"23-12-18 22:49:22",
            "content":"看下午方便的话可以"
        },
        "lte.sTQ9x1":
        {
            "id":"lte.sTQ9x1",
            "contact":"8617688704240",
            "date":"23-12-18 22:51:22",
            "content":"iiik'帮"
        },
        "lte.uKyisL":
        {
            "id":"lte.uKyisL",
            "contact":"8617688704240",
            "date":"23-12-18 22:51:49",
            "content":"ss'ddd"
        }
    }
}
```    


#### 示例-删除一条短信
- 第一个LTE/NR的模块为modem@lte, 给出短信的id号即可删除对应的短信, 点击[LTE/NR(4G/5G)基带](../../com/modem/lte.md)查看有关smslist接口的介绍
```json
{
    "cmd1":
    {
        "com":"modem@lte",
        "op":"smsdel",
        "1":"lte.612f6C"
    }
}
```   
- 网关返回
```json
{
    "cmd1":"ttrue"
}
```    





#### 示例-获取网关的客户端信息
- 网关上的客户端信息由client@station组件的list接口返回(在终端中的命令为client@station.list), 点击 [终端管理](../../com/client/station.md) 查看有关list接口的介绍
```json
{
    "cmd1":
    {
        "com":"client@station",
        "op":"list"
    }
}
```
- 网关返回
```json
{
    "cmd1":
    {
        "00:E0:4C:68:2A:8B":                           // 客户端MAC地址
        {
            "ip":"192.168.1.250",                        // IP地址
            "netdev":"lan",                              // 接入的网络接口
            "ifname":"ifname@lan",                       // 接入的网络连接
            "livetime":"00:40:25:0"                      // 连接时间
        },
        "FC:87:43:DC:6F:B4":                          // 客户端MAC地址
        {
            "ip":"192.168.1.248",                        // IP地址
            "netdev":"lan",                              // 接入的网络接口
            "ifname":"ifname@lan",                       // 接入的网络连接
            "livetime":"00:40:11:0",                     // 连接时间
            "ifdev":"wifi@assid",                        // 接入的连接网关
            "rssi":"-73",                                // 信号强度, 只有连接网关热点的设备才有此属性
            "name":"HUAWEI_P30_Pro-9f13d2ee6f",          // 客户端名称
            "tx_bytes":"610528",                         // 发送字节
            "rx_bytes":"1653658"                         // 接收字节
        }
    }
}
```





#### 示例-获取全球定位信息(对应的网关必须有全球定位功能并且配置正确)
- 定位信息由gnss@nmea组件的info接口返回(在终端中的命令为gnss@nmea.info), 点击 [全球定位](../../com/gnss/nmea.md) 查看有关info接口的介绍
```json
{
    "cmd1":
    {
        "com":"gnss@nmea",
        "op":"info"
    }
}
```
- 网关返回
```json
{
    "cmd1":
    {
        "step":"located",                           // 表示已定位到
                                                          // [ "setup", "search", "located" ]
                                                          // "setup" 为初始化中
                                                          // "search" 为搜索中
                                                          // "located" 为已定位到
        "utc":"7:55:22:7:12:2021",                  // UTC时间
        "lon":"11356.56400",                        // 经度为11356.56400, 已定位到后才出现
        "lat":"2240.80119",                         // 纬度为2240.80119, 已定位到后才出现
        "longitude":"113.94273",                    // 经度(十进制), 已定位到后才出现
        "latitude":"22.68001",                      // 纬度(十进制), 已定位到后才出现
        "speed":"0.34",                             // 速度, 已定位到后才出现
        "elv":"77.90",                              // 高度为77.90, 单位为米, 已定位到后才出现
        "direction":"",
        "declination":"",
        "inuse":"5"                                 // 可使用的卫星数为5个
    }
}
```



#### 示例-获取网关本地网络(LAN)状态信息
- 网关LAN口信息由ifname@lan组件的status接口返回(在终端中的命令为ifname@lan.status), 点击查看 [本地网络(LAN)](../../com/ifname/lan.md) 查看有关status接口的介绍
```json
{
    "cmd1":
    {
        "com":"ifname@lan",
        "op":"status"
    }
}
```
- 网关返回
```json
{
    "cmd1":
    {
        "mode":"static",                   // IPv4的连接模式为静态设置
        "netdev":"lan",                    // 网络设备为lan
        "status":"up",                     // 接口已上线
        "ip":"192.168.8.1",                // IP地址为192.168.8.1
        "mask":"255.255.255.0",            // 掩码为255.255.255.0
        "livetime":"01:15:50:0",           // 已上线1小时15分钟50秒
        "rx_bytes":"1256",                 // 接收了1256字节
        "rx_packets":"4",                  // 接收了4包
        "tx_bytes":"1320",                 // 发送了1320字节
        "tx_packets":"4",                  // 发送了4包
        "mac":"02:50:F4:00:00:00",         // MAC地址为02:50:F4:00:00:00
        "method":"slaac",                  // IPv6地址模式为slaac
        "addr":"fe80::50:f4ff:fe00:0"      // 本地IPv6地址为fe80::50:f4ff:fe00:0
    }
}
```




#### 示例-重启网关
- 对应终端中的命令land@machine.restart, 点击 [设备基本信息](../../com/land/machine.md) 查看有关restart接口的介绍
```json
{
    "cmd1":
    {
        "com":"land@machine",
        "op":"restart"
    }
}
```
- 网关返回如下后将会在3至15秒内重启
```json
{
    "cmd1":"ttrue"
}
```

#### 示例-重置网关(恢复默认设置)
- 对应终端中的命令land@machine.default, 点击查看 [设备基本信息](../../com/land/machine.md) 查看有关default接口的介绍
```json
{
    "cmd1":
    {
        "com":"land@machine",
        "op":"default"
    }
}
```
- 网关返回如下后将会在3至15秒内重启
```json
{
    "cmd1":"ttrue"
}
```

#### 示例-修改网关admin用户的密码
- 用户及密码管理在land@auth组件中, 修改密码使用modify的接口, 以下示例修改用户名admin的密码为123456, 点击 [用户名密码及权限](../../com/land/auth.md) 查看modify接口介绍
```json
{
    "cmd1":
    {
        "com":"land@auth",             // 帐号密码及权限管理组件
        "op":"modify",                 // 调用修改接口
        "1":"",                        // 要修改的域, 空为默认所有域
        "2":"admin",                   // 要修改的用户名
        "3":"admin",                   // 原密码
        "4":"123456"                   // 新密码
    }
}
```
***注意, 实际发送时不允许包含注解***
- 网关返回
```json
{
    "cmd1":"ttrue"
}
```







#### 示例-修改2.4G无线热点的SSID名称
- 2.4G无线热点的配置在组件wifi@nssid中, ssid属性的值为SSID名称, 以下示例修改SSID名称为NewSSID(在终端中的命令为wifi@nssid:ssid=NewSSID), 点击 [2.4G热点](../../com/wifi/nssid.md) 查看配置介绍
```json
{
    "cmd1":
    {
        "com":"wifi@nssid",
        "ab":"ssid",
        "op":"=",
        "v":"NewSSID"
    }
}
```
- 网关返回
```json
{
    "cmd1":"ttrue"
}
```

#### 示例-同时修改2.4G无线热点的SSID名称及密码
- 同时修改两个及以上的属性需要使用**或操作**, 以下示例修改SSID名称为NewSSID并将密码修改为NewPassword(在终端中的命令为wifi@nssid|{"ssid":"NewSSID","secure":"wpapskwpa2psk","wpa_key":"NewPassword"}), 点击 [2.4G热点](../../com/wifi/nssid.md) 查看配置介绍
```json
{
    "cmd1":
    {
        "com":"wifi@nssid",            // 2.4G无线热点组件
        "op":"|",                      // 或操作, 即只修改以下给出的属性的值, wifi@nssid组件配置中其它未在v中给出的属性保留原来的值(如果op的值为=号将会删除其它的属性)
        "v":
        {
            "ssid":"NewSSID",          // SSID的名称改为NewSSID
            "secure":"wpapskwpa2psk",  // 安全方式改为WPA自动
            "wpa_key":"NewPassword"    // WPA的密码改为NewPassword
        }
    }
}
```
***注意, 实际发送时不允许包含注解***
- 网关返回
```json
{
    "cmd1":"ttrue"
}
```

#### 示例-同时修改5.8G无线热点的SSID名称及密码
- 5.8G无线热点配置在组件wifi@assid中, 以下示例修改SSID名称为NewSSID-5G并将密码修改为NewPassword(在终端中的命令为wifi@assid|{"ssid":"NewSSID-5G","secure":"wpapskwpa2psk","wpa_key":"NewPassword"}), 点击 [5.8G热点](../../com/wifi/assid.md) 查看配置介绍
```json
{
    "cmd1":
    {
        "com":"wifi@assid",            // 5.8G无线热点组件
        "op":"|",                      // 或操作, 即只修改以下给出的属性的值, wifi@assid组件配置中其它未在v中给出的属性保留原来的值(如果op的值为=号将会删除其它的属性)
        "v":
        {
            "ssid":"NewSSID-5G",          // SSID的名称改为NewSSID-5G
            "secure":"wpapskwpa2psk",  // 安全方式改为WPA自动
            "wpa_key":"NewPassword"    // WPA的密码改为NewPassword
        }
    }
}
```
***注意, 实际发送时不允许包含注解***
- 网关返回
```json
{
    "cmd1":"ttrue"
}
```







#### 示例-设置2.4G无线连网连接指定的SSID, 必须要有WISP接口的工作模式下才有效(如在2.4G无线连网或混合模式下)
- 2.4G无线连网配置在组件ifname@wisp中, 设置2.4G无线连网需要同时修改两个以上的属性, 因此使用**或操作**, 以下示例设置连接SSID为CMCC密码为CMCC@passwd的2.4G网络(在终端的命令为ifname@wisp|{"peer":"CMCC","secure":"wpapskwpa2psk","wpa_key":"CMCC@passwd"}), 点击 [无线连网(WISP)](../../com/ifname/wisp.md) 查看配置介绍
```json
{
    "cmd1":
    {
        "com":"ifname@wisp",            // 2.4G无线连网组件
        "op":"|",                       // 或操作, 即只修改以下给出的属性的值, ifname@wisp组件配置中其它未在v中给出的属性保留原来的值(如果op的值为=号将会删除其它的属性)
        "v":
        {
            "status":"enable",          // 启用此连接
            "peer":"CMCC",              // 连接的SSID为CMCC
            "secure":"wpapskwpa2psk",   // 安全方式改为WPA自动
            "wpa_key":"CMCC@passwd"     // WPA的密码改为CMCC@passwd
        }
    }
}
```
***注意, 实际发送时不允许包含注解***
- 网关返回
```json
{
    "cmd1":"ttrue"
}
```

#### 示例-设置禁用2.4G无线连网, 必须要有WISP接口的工作模式下才有效(如在2.4G无线连网或混合模式下)
- 2.4G无线连网配置在组件ifname@wisp中, 修改status属性改为disable即可(在终端中的命令为ifname@wisp:status=disable), 点击 [无线连网(WISP)](../../com/ifname/wisp.md) 查看配置介绍
```json
{
    "cmd1":
    {
        "com":"ifname@wisp",            // 2.4G无线连网组件
        "ab":"status",                  // 指定修改status属性
        "op":"=",                       // 赋值操作
        "v":"disable"                   // 将status属性的值改为disable即禁用
    }
}
```
***注意, 实际发送时不允许包含注解***
- 网关返回
```json
{
    "cmd1":"ttrue"
}
```

#### 示例-断开2.4G无线连网, 必须要有WISP接口的工作模式下才有效(如在2.4G无线连网或混合模式下)
- 断开2.4G无线连接调用ifname@wisp的shut接口(在终端中的命令为ifname@wisp.shut), 点击 [无线连网(WISP)](../../com/ifname/wisp.md) 查看shut接口介绍
```json
{
    "cmd1":
    {
        "com":"ifname@wisp",            // 2.4G无线连网组件
        "op":"shut"                     // 调用shut接口断开2.4G无线连网
    }
}
```
***注意, 实际发送时不允许包含注解***
- 网关返回
```json
{
    "cmd1":"ttrue"
}
```

#### 示例-发起2.4G无线连网, 必须有WISP接口的工作模式下才有效(如在2.4G无线连网或混合模式下)， 并已配置好相关的2.4G无线连网的参数且被断开过
- 发起2.4G无线连网调用ifname@wisp的setup接口(在终端中的命令为ifname@wisp.setup), 点击 [无线连网(WISP)](../../com/ifname/wisp.md) 查看setup接口介绍
```json
{
    "cmd1":
    {
        "com":"ifname@wisp",            // 2.4G无线连网组件
        "op":"setup"                    // 调用setup接口让2.4G无线连网发起连接
    }
}
```
***注意, 实际发送时不允许包含注解***
- 网关返回
```json
{
    "cmd1":"ttrue"
}
```





#### 示例-设置5.8G无线连网连接指定的SSID, 必须要有WISP2接口的工作模式下才有效(如在5.8G无线连网或混合模式下)
- 5.8G无线连网配置在组件ifname@wisp2中, 以下示例设置连接SSID为CMCC-5G密码为CMCC@passwd的5.8G网络(在终端中的命令为ifname@wisp2|{"peer":"CMCC-5G","secure":"wpapskwpa2psk","wpa_key":"CMCC@passwd"}), 点击 [无线连网(WISP)](../../com/ifname/wisp.md) 查看配置介绍
```json
{
    "cmd1":
    {
        "com":"ifname@wisp2",            // 5.8G无线连网组件
        "op":"|",                        // 或操作, 即只修改以下给出的属性的值, ifname@wisp组件配置中其它未在v中给出的属性保留原来的值(如果op的值为=号将会删除其它的属性)
        "v":
        {
            "status":"enable",           // 启用此连接
            "peer":"CMCC-5G",            // 连接的SSID为CMCC-5G
            "secure":"wpapskwpa2psk",    // 安全方式改为WPA自动
            "wpa_key":"CMCC@passwd"      // WPA的密码改为CMCC@passwd
        }
    }
}
```
***注意, 实际发送时不允许包含注解***
- 网关返回
```json
{
    "cmd1":"ttrue"
}
```

#### 示例-设置禁用5.8G无线连网, 必须要有WISP2接口的工作模式下才有效(如在5.8G无线连网或混合模式下)
- 5.8G无线连网配置在组件ifname@wisp2中, 修改status属性改为disable即可(在终端中的命令为ifname@wisp2:status=disable), 点击 [无线连网(WISP)](../../com/ifname/wisp.md) 查看配置介绍
```json
{
    "cmd1":
    {
        "com":"ifname@wisp2",            // 5.8G无线连网组件
        "ab":"status",                   // 指定修改status属性
        "op":"=",                        // 赋值操作
        "v":"disable"                    // 将status属性的值改为disable即禁用
    }
}
```
***注意, 实际发送时不允许包含注解***
- 网关返回
```json
{
    "cmd1":"ttrue"
}
```

#### 示例-断开5.8G无线连网, 必须要有WISP2接口的工作模式下才有效(如在5.8G无线连网或混合模式下)
- 5.8G无线连网管理在组件ifname@wisp2中, 断开5.8G无线连接调用shut接口(在终端中的命令为ifname@wisp2.shut), 点击 [无线连网(WISP)](../../com/ifname/wisp.md) 查看shut接口介绍
```json
{
    "cmd1":
    {
        "com":"ifname@wisp2",            // 5.8G无线连网组件
        "op":"shut"                      // 调用shut接口断开5.8G无线连网
    }
}
```
***注意, 实际发送时不允许包含注解***
- 网关返回
```json
{
    "cmd1":"ttrue"
}
```

#### 示例-发起5.8G无线连网, 必须有WISP2接口的工作模式下才有效(如在5.8G无线连网或混合模式下)， 并已配置好相关的5.8G无线连网的参数且被断开
- 5.8G无线连网管理在组件ifname@wisp2中, 发起5.8G无线连网调用setup接口(在终端中的命令为ifname@wisp2.setup), 点击 [无线连网(WISP)](../../com/ifname/wisp.md) 查看setup接口介绍
```json
{
    "cmd1":
    {
        "com":"ifname@wisp2",            // 5.8G无线连网组件
        "op":"setup"                     // 调用setup接口让5.8G无线连网发起连接
    }
}
```
***注意, 实际发送时不允许包含注解***
- 网关返回
```json
{
    "cmd1":"ttrue"
}
```






#### 示例-添加新策略路由, 指定源地址为192.168.2.12走第一个LTE
- 策略路由管理在组件forward@rule中, 添加策略路由由add接口操作, 点击 [Policy based routing](../../com/forward/rule.md) 查看接口add相关介绍
```json
{
    "cmd1":
    {
        "com":"forward@rule",             // 策略路由组件
        "op":"add",                       // 调用add接口添加规则, 此规则的名称为senser, 此规则要求源地址为192.168.2.12的数据走第一个LTE
        "1":"senser",                         // 规则名称
        "2":"192.168.2.12",                   // 源地址
        "3":"",                               // 掩码
        "4":"",                               // 源接口名称
        "5":"",                               // mark id
        "6":"1",                              // 指定路由表, 1通常为第一个LTE, 2通常为第二个LTE, 3通常为有线宽带， 4为第二个有线宽带, 5为2.4G无线连网, 6为5.8G无线连网
        "7":"33000"                           // 优先级, 通常优先级需在32766至35000之间
    }
}
```
***注意, 实际发送时不允许包含注解***
- 网关返回
```json
{
    "cmd1":"ttrue"
}
```
#### 示例-添加新策略路由, 指定所有数据走第二个LTE
```json
{
    "cmd1":
    {
        "com":"forward@rule",             // 策略路由组件
        "op":"add",                       // 调用add接口添加规则, 此规则的名称为video, 此规则要求所有的数据走第二个LTE
        "1":"video",                         // 规则名称
        "2":"",                              // 源地址
        "3":"",                              // 掩码
        "4":"",                              // 源接口名称
        "5":"",                              // mark id
        "6":"2",                             // 指定路由表, 1通常为第一个LTE, 2通常为第二个LTE, 3通常为有线宽带， 4为第二个有线宽带, 5为2.4G无线连网, 6为5.8G无线连网
        "7":"33300"                          // 优先级, 通常优先级需在32766至35000之间
    }
}
```
***注意, 实际发送时不允许包含注解***
- 网关返回
```json
{
    "cmd1":"ttrue"
}
```
#### 示例-删除原设置的名为video的策略路由规则
- 删除策略路由由delete接口操作, 
```json
{
    "cmd1":
    {
        "com":"forward@rule",             // 策略路由组件
        "op":"delete",                    // 调用delete接口添加规则, 此规则的名称为video
        "1":"video"                          // 规则名称
    }
}
```
***注意, 实际发送时不允许包含注解***
- 网关返回
```json
{
    "cmd1":"ttrue"
}
```
#### 示例-同时添加两条策略路由, 指定源地址为192.168.2.12走第一个LTE, 并指定其它所有数据走第二个LTE
```json
{
    "cmd1":
    {
        "com":"forward@rule",             // 策略路由组件
        "op":"add",                       // 调用add接口添加规则, 此规则的名称为senser, 此规则要求源地址为192.168.2.12的数据走第一个LTE
        "1":"senser",                         // 规则名称
        "2":"192.168.2.12",                   // 源地址
        "3":"",                               // 掩码
        "4":"",                               // 源接口名称
        "5":"",                               // mark id
        "6":"1",                              // 指定路由表, 1通常为第一个LTE, 2通常为第二个LTE, 3通常为有线宽带， 4为第二个有线宽带, 5为2.4G无线连网, 6为5.8G无线连网
        "7":"33000"                           // 优先级, 通常优先级需在32766至35000之间
    },
    "cmd2":
    {
        "com":"forward@rule",             // 策略路由组件
        "op":"add",                       // 调用add接口添加规则, 此规则的名称为video, 此规则要求所有的数据走第二个LTE
        "1":"video",                         // 规则名称
        "2":"",                              // 源地址
        "3":"",                              // 掩码
        "4":"",                              // 源接口名称
        "5":"",                              // mark id
        "6":"2",                             // 指定路由表, 1通常为第一个LTE, 2通常为第二个LTE, 3通常为有线宽带， 4为第二个有线宽带, 5为2.4G无线连网, 6为5.8G无线连网
        "7":"33300"                          // 优先级, 通常优先级需在32766至35000之间
    }
}
```
***注意, 实际发送时不允许包含注解***
- 网关返回
```json
{
    "cmd1":"ttrue",
    "cmd2":"ttrue"
}
```
#### 示例-删除原添加的名为senser及名为video的策略路由规则

```json
{
    "cmd1":
    {
        "com":"forward@rule",             // 策略路由组件
        "op":"delete",                    // 调用delete接口添加规则, 此规则的名称为video
        "1":"senser"                          // 规则名称
    },
    "cmd2":
    {
        "com":"forward@rule",             // 策略路由组件
        "op":"delete",                    // 调用delete接口添加规则, 此规则的名称为video
        "1":"video"                          // 规则名称
    }
}
```
***注意, 实际发送时不允许包含注解***
- 网关返回
```json
{
    "cmd1":"ttrue",
    "cmd2":"ttrue"
}
```



## 对照组件文档使用TCP(JSON)协议管理

有两种方式可以查询到所有组件文档, 通过这些组件文档可以管理到网关的每一个功能
- 访问 [在线组件文档](../../com/) 查看组件文档, 此在线文件会随着开发新的功能动态增加及修订
- 资询技术支持人员

#### 组件文档要点

- 在 [在线组件文档](../../com/) 中首先以行的形式列出了系统中常用的项目, 每个项目下包含了组件文档
- 点击项目进入项目中, 会以行的形式列出此项目下所有的组件文档
- 点击组件打开组件文档, 组件文件首先是抬头, 抬头是组件名称介绍
- 组件文档首先是介绍此组件的功能, 然后就是 **Configuration**, 配置是JSON格式, 可以在JSON控制协议或命令行中查询或修改这些配置, 通常文档中会给出修改及查询示例
- 组件文档 **Configuration** 之后通常是介绍此组件的 **Methods**, 可以在JSON控制协议或命令行中调用这些方法

#### 对照功能组件文档查询组件配置

在组件文档的抬头中会指出组件名, 比如 [日志管理](../../com/land/syslog.md) 的组件名为 **land@syslog**

- 发送JOSN查询指令, 对应的HE指令为land@syslog
```json
{
    "cmd1":
    {
        "com":"land@syslog"
    }
}
```

网关将返回如下, cmd1的属性即是land@syslog的配置
```json
{
    "cmd1":
    {
        "status":"enable",               // 开启syslog
        "type":"init|serv|joint|default",// 记录启动项及关机项, 服务, 事件及其它默认类型相关的日志
        "level":"info",                  // 只记录通知级别的日志
        "trace":"enable",                // 记录代码位置及进程ID
        "size":"20",                     // 记录池为20k
        "remote":"192.168.8.100",        // 远程日志服务器地址为192.168.8.100
        "port":"514"                     // 远程日志服务器的端口为514
    }
}
```

- 也可以在发送JOSN指令中查询组件配置中指定的属性, 只需要增加 **ab**属性, 在 **ab** 属性的值中给出指定的属性
```json
{
    "cmd1":
    {
        "com":"land@syslog",
        "ab":"size"
    }
}
```

网关将返回如下, cmd1的属性值即是land@syslog配置下size属性的值
```json
{
    "cmd1":"100"
}
```

#### 对照组件文档修改组件配置

接以上 [日志管理](../../com/land/syslog.md) 的组件文档, 在文档的 **Configuration** 中描述属性可以在JOSN指令协议中修改
- 通过JSON指令协议修改land@syslog的远程日志服务器(remote属性值)为192.168.8.230
    ```json
    {
        "cmd1":
        {
	        "com":"land@syslog",
	        "ab":"remote",
	        "op":"=",
	        "v":"192.168.8.230"
        }
    }
    ```

    网关将返回如下, cmd1的属性值指示是否成功, 成功返厍ttrue, 失败返回tfalse
    ```json
    {
        "cmd1":"ttrue"
    }
    ```

- 通过JSON指令协议同时修改land@syslog的多个属性值, 以下同时修改remote及port两个属性, 并不对其它的属性产生任何影响
    ```json
    {
        "cmd1":
        {
	        "com":"land@syslog",
	        "op":"|",
	        "v":
            {
                "remote":"192.168.8.231",
                "port":"510"
            }
        }
    }
    ```

    网关将返回如下, cmd1的属性值指示是否成功, 成功返厍ttrue, 失败返回tfalse
    ```json
    {
        "cmd1":"ttrue"
    }
    ```

- 通过JSON指令协议修改land@syslog的所有配置, 组件配置都是一个JSON, 如要修改所有的配置必须同样的给出一个JSON
    ```json
    {
        "cmd1":
        {
	        "com":"land@syslog",
	        "op":"=",
	        "v":
            {
                "status":"enable",
                "location":"memory",
                "type":"arch|land|default",
                "level":"info",
                "trace":"disable",
                "size":"110",
                "remote":"",
                "port":"514"
            }
        }
    }
    ```

    网关将返回如下, cmd1的属性值指示是否成功, 成功返厍ttrue, 失败返回tfalse
    ```json
    {
        "cmd1":"ttrue"
    }
    ```

#### 对照组件文档调用组件接口

接以上 [日志管理](../../com/land/syslog.md) 的组件文档, 在文档的 **Methods** 中描述接口(API)都可以在JSON指令协议中调用
- 在JSON指令协议中调用组件land@syslog的clear接口清除日志
    ```json
    {
        "cmd1":
        {
	        "com":"land@syslog",
	        "op":"clear"
        }
    }
    ```

    网关将返回如下, cmd1的属性值指示是否成功, 成功返厍ttrue, 失败返回tfalse
    ```json
    {
        "cmd1":"ttrue"
    }
    ```
