
***
## Manage skinos device at local network
Manage skonos device at the local network

#### Configuration( gather@beacon )

```json
// Attributes introduction
{
    "status":"beacon for search device",        // [ disable, enable ]
    "port":"beacon udp port",                   // [ nubmer ]
    "interval":"beacon interval",               // [ nubmer ], the unit is second
    "group":"search group name",                // [ string ], default is group of "default"
    "ip":"beacon network ip",                   // [ IP address ], default is 192.168.200.1
    "mask":"beacon network netmask",            // [ Network ], default is 255.255.255.0
    "dhcps":                                    // Assign IP addresses and some infomation to found devices
    {
        "status":"Assign IP addresses to found devices",              // [ disable, enable ]
        "startip":"IP addresses pool start",                          // [ IP address ], default is 192.168.200.2
        "endip":"IP address poll end",                                // [ IP address ], default is 192.168.200.254
        "gw":"Assign gateway to found devices",                       // [ IP address ]
        "dns":"Assign dns to found devices",                          // [ IP address ]
        "remote":"Assign remote control server to found devices"      // [ string ]
    }
}
```
Examples, show all the configure
```shell
gather@beacon
{
    "status":"enable",                     # enable the beacon for search device
    "port":"22222",                        # UDP port is 22222
    "ip":"172.32.0.1",                     # beacon network is 172.32.0.1/255.255.0.0
    "mask":"255.255.0.0",
    "dhcps":
    {
        "status":"enable",                 # enable Assign IP addresses to found devices
        "startip":"172.32.0.2",            # IP addresses pool start 172.32.0.2
        "endip":"172.32.254.254"           # IP addresses pool end 172.32.254.254
    }
}
```  
Examples, disable the beacon
```shell
gather@beacon:status=disable
true
```  

#### **Methods**

+ `list[]` **list all the found device**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "MAC Address":
        {
            "ip":"IP Address",
            "time":"found time"
        },
        "MAC Address2":
        {
            "ip":"IP Address",
            "time":"found time"
        },
        // ... more device
    }    
    ```
    ```shell
    # examples, get all the found device
    gather@beacon.list
    {
        "88124E200030":              # device is 88:12:4E:20:00:30
        {
            "time":"1608637542",     # found device at UTC 1608637542
            "ip":"192.168.200.2"     # device ip is 192.168.200.2
        },
        "00037F12CC70":              # device is 00:03:7F:12:CC:70
        {
            "time":"1608637542",     # found device at UTC 1608637542
            "ip":"192.168.200.3"     # device ip is 192.168.200.3
        }
    }  
    ```

+ `current[ <current date> ]` **set current date**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, set 11:12:23, On July 8th, in 2019
    clock@date.current[ 11:12:23:07:08:2019 ]
    true
    ```

+ `ntpsync[ [NTP Server] ]` **sync the time with NTP server**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, sync the time with time.window.com
    clock@date.ntpsync[ time.window.com ]
    true
    # examples, sync the time with NTP server in the configure
    clock@date.ntpsync
    true
    ```





***
## 局域网管理设备组件(gather@beacon)
实现局域网发现及管理设备

#### **配置** 
```json
// 属性介绍
{
    "status":"本地搜索状态",                   // enable为启动本地搜索, disable为禁用
    "device":"搜索使用的网络接口设备",          // 默认为lan, 可指定其它的接口
    "port":"搜索使用的端口",
    "interval":"搜索间隔",
    "group":"组名",                            // 只有为相同组的设备才能会搜寻到, 空表示为default组
    "ip":"本地搜索使用的IP地址"                 // 在启用本地搜索状态时会启用此IP地址
    "mask":"本地搜索使用的子网掩码"
    "dhcps":                                       // 在启用本地搜索状态时为搜寻到的设备分配地址
    {
        "status":"是否为搜索到的设备分配地址",     // enable为分配, disable为不分配
        "device":"分配的地址适用的接口",           // 分配的IP用于设备上的此接口
        "startip":"地址池的起始地址",
        "endip":"地址池的结束地址"
        "gw":"默认网关",
        "dns":"域名服务器",
        "remote":"HTTP管理服务器"
    }
}

// 示例
{
    "status":"enable",                // 启用本地搜索
    "device":"eth0",                  // 在eth0的接口上搜索
    "port":"22222",                   // 搜索使用的端口为22222
    "interval":"5",                   // 每隔5秒钟搜索一次
    "group":"default",                // 只搜索组名为default的设备
    "ip":"169.254.222.1",             // IP地址
    "mask":"255.255.0.0",             // 子网掩码
    "dhcps":
    {
        "status":"enable",             // 将为搜索到的设备分配地址
        "device":"lan:trojan",         // 分配的IP地址用于设备的lan:trojan接口
        "startip":"169.254.222.10",    // 地址池的起始地址为169.254.222.10
        "endip":"169.254.242.250",     // 地址池的结束地址为169.254.242.250
        "gw":"169.254.222.1",          // 默认网关为169.254.222.1
        "dns":"169.254.222.1"          // 域名服务为169.254.222.1
        "remote":"http://169.254.222.1:22223/dev"     // 管理服务器为http://169.254.222.1:22223/dev 
    }
}
```  


#### **接口** 

+ `talk[ 设备的IP或MAC, {请求数据}, 超时时间 ]` 向指定的设备发起JSON指令请求, 支持一次发送多条指令

>*成功返回JSON, 以下为JSON介绍; 失败返回NULL*

```json
    // 请求数据 介绍, 必须为JSON格式, 格式如下: 
    {
        "指令名称1":"字符串式指令",
        "指令名称2":                    // 有些复杂的指令需要转换为JSON式的指令格式
        {
            JSON式指令
        }
        // ...                         // 更多指令
    }
    // 返回介绍, 指令执行成功会返回一个JSON, 格式如下:
    {
        "指令名称":
        {
            JSON式指令返回
        }
        "指令名称2":"字符串式返回", // 指令的返回是字符串式还是JSON式取决于指令
       // ...                     // 更多指令
    }

    // 示列
    # gather@beacon.talk[ 192.168.8.1, {"1":"machine","2":"machine.status","3":"clock@date:timezone"}, 10 ]
    {
        "1":                              // 指令1 --- 192.168.8.1的machine指令的返回, 此指令返回一个JSON对象
        {
            "platform":"smtk",
            "hardware":"mt7621",
            "custom":"v520",
            "scope":"oali",
            "language":"cn",
            "macid":"88124E200030",
            "mac":"88:12:4E:20:00:30",
            "name":"V520-200030",
            "title":"V520-200030",
            "mode":"oalicon"
        },
        "2":                              // 指令2 --- 192.168.8.1的machine.status指令的返回, 此指令返回一个JSON对象
        {
            "custom":"v520",
            "version":"4.3.3v",
            "publish":"122120",
            "macid":"88124E200030",
            "mac":"88:12:4E:20:00:30",
            "magic":"D7441F2CE4605020",
            "model":"V520",
            "name":"V520-200030",
            "mode":"oalicon",
            "livetime":"15:43:45:0",
            "current":"19:14:15:12:22:2020"
        },
        "3":"8"                           // 指令3 --- 192.168.8.1的clock@date:timezone指令的返回, 此指令返回一个字符串表示192.168.8.1所在的时区
    }
```

+ `to[ 设备的IP或MAC, HE指令, 超时时间 ]` 要求指定的设备执行一条HE指令

>*成功返回HE指令的返回, 失败返回NULL*

```shell
    // 示列1 --- 获取192.168.8.1的设备的基本信息
    # gather@beacon.to[192.168.8.1, machine]
    {
        "platform":"smtk",
        "hardware":"mt7621",
        "custom":"v520",
        "scope":"std",
        "cfgversion":"16",
        "language":"cn",
        "macid":"88124E200030",
        "mac":"88:12:4E:20:00:30",
        "name":"V520-200030",
        "title":"V520-200030",
        "mode":"nmisp"
    }
    // 示列2 -- 获取192.168.8.1的工作模式, 工作模式在machine下的mode属性
    # gather@beacon.to[192.168.8.1, machine:mode]
    nmisp                                          // nmisp表示5G工作模式
    // 示列3 -- 获取192.168.8.1的时区, 时区在clock@date组件下的timezone属性
    # gather@beacon.to[192.168.8.1, clock@date:timezone]
    8                                              // 8表示东8区
    // 示列4 -- 设置192.168.8.1的时区为西7区, 修改clock@date组件下的timezone的值即可
    # gather@beacon.to[192.168.8.1, clock@date:timezone=-7]
    ttrue                                         // 返回ttrue表示执行成功, false表示失败, 无返回通常表示与设备连接失败
```

+ `to_extern[ 设备的IP或MAC, 超时时间 ]` 获取设备的外部连接及状态

>*成功返回JSON, 以下为JSON介绍; 失败返回NULL*

```json
    // 介绍
    {
        "外部接口1":
        {
            "status":"当前连接的状态",                // up表示已连接, down表示未连接, uping表示连接中            
            "step":"当前模块所处步骤",           // 指出当前模块处于哪一个步骤
                                                // found表示发现模块
                                                // setup表示启动模块中
                                                // checksim表示查询SIM卡中
                                                // checknet表示查询网络中
                                                // checksig表示查询信号中
                                                // ready表示模块无异常
                                                // dial表示PDP激活中
                                                // online表示上线
                                                // offline表示离线
                                                // reset表示模块重置
            "error":"出错信息",          // 模块出错时会出现此值
                                        // pin表示要求SIM卡PIN码
                                        // puk表示PIN码出错
                                        // nosim表示无SIM卡
                                        // noreg表示未注册网络
                                        // dereg表示拒绝注册网络
                                        // unreg表示未知网络
                                        // nosignal表示无信息
        },
        "外部接口2":
        {
        },
        ...                // 更多外部接口
    }

    // 示列1 --- 获取192.168.8.1的设备的所有的外部接口状态
    # gather@beacon.to_extern[ 192.168.8.1, 10 ]
    {
        "ifname@lte":                            // 第一个4G接口
        {
            "status":"up",                     // 表示网络已连接
            "step":"online",                   // 表示当前模块已上线
            "gw":"10.130.229.66",
            "dns":"202.96.134.33",
            "dns2":"202.96.128.166",
            "ip":"10.130.229.65",
            "dstip":"10.130.229.65",
            "mask":"255.255.255.252",
            "keeplive":"175",
            "rx_bytes":"242470",
            "tx_bytes":"254260",
            "imei":"867160040523965",
            "imsi":"460113366168988",
            "iccid":"89861119226037439799",
            "nettype":"FDD LTE",
            "band":"LTE BAND 1",
            "rssi":"-65",
            "signal":"4",
            "livetime":"15:50:57:0"
        },
        "ifname@lte2":                            // 第二个4G接口
        {
            "status":"uping",                     // 表示正在连接网络
            "step":"checksim",                    // 表示正在检测SIM卡
            "error":"nosim",                      // 表示无SIM卡
            "imei":"867394047122170"
        },
        "ifname@wan":                            // 有线WAN口的状态
        {
            "mac":"88:12:4E:20:00:36",
            "status":"down",                     // 表示未连接
            "mode":"dhcpc",
        }
    }
    // 示列2 -- 获到192.168.1.1的第一个4G接口的信号量
    #gather@beacon.to_extern[ 192.168.1.1 ]:ifname@lte/signal
    4                                             // 4表示4格, 即满格
    // 示列3 -- 获到192.168.1.1的第二个4G接口的状态信息
    #gather@beacon.to_extern[ 192.168.1.1 ]:ifname@lte2/status
    uping                                         // 返回uping表示正在连接
    // 示列4 -- 获到192.168.1.1的第二个4G接口的拨号进度, 接示例3, 当设备处理uping时可通过此指令进一步得到拨号程序当前的进度
    #gather@beacon.to_extern[ 192.168.1.1 ]:ifname@lte2/step
    checksim                                         // 返回checksim表示正在检测SIM卡
    // 示列5 -- 获到192.168.1.1的第二个4G接口的出错信息, 接示例4, 当设备处于检测SIM卡时, 可以通过此指令得到是否有出错信息
    #gather@beacon.to_extern[ 192.168.1.1 ]:ifname@lte2/error
    nosim                                         // 返回nosim表示无SIM卡
```

+ `list[]` 列出搜索到的设备, 只有在开启本地搜索时可用

>*成功返回JSON, 以下为JSON介绍; 失败返回NULL*

```json
    // 属性介绍
    {
        "设备MAC标识1":
        {
            "ip":"IP地址",
            "time":"发现时间"        // UTC时间
        },
        "设备MAC标识2":
        {
            "ip":"IP地址",
            "time":"发现时间"        // UTC时间
        }
        // ...                         // 更多设备MAC标识
    }

    // 示列
    {
        "88124E200030":              // 设备MAC地址为88:12:4E:20:00:30
        {
            "time":"1608637542",     // 发现设备时的UTC时间为1608637542
            "ip":"192.168.200.2"     // 设备的IP地址为192.168.200.2
        },
        "00037F12CC70":              // 设备MAC地址为00:03:7F:12:CC:70
        {
            "time":"1608637542",     // 发现设备时的UTC时间为1608637542
            "ip":"192.168.200.3"     // 设备的IP地址为192.168.200.3
        }
    }
```




