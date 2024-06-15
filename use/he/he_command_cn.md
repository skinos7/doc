
## 通过终端命令行执行HE指令管理网关   
终端命令行用于执行HE指令， 通过HE指令可以控制网关， 实现如：查询网关信息、设置网关参数、重启或重置网关等各种操作, HE指令不止使用于终端命令行中, 在很多控制协议中也都支持

可通过几种方式登录网关使用HE指令:
- 通过Telnet客户端连接网关登录后使用
- 通过SSH客户端连接网关登录后使用
- 通过TTL串口连接网关后使用
- 通过RS232串口连接网关后使用
- 通过RS485串口连接网关后使用

##### Telnet客户端下使用HE指令   
1. 首先在网关管理网页下的 **<系统>** 下的 **<Telnet服务器>** 界面中打开 **Telnet服务器**
2. 通过Telnet客户端使用 用户名 及 密码 登录网关后即可进入终端界面

##### SSH客户端下使用HE指令   
1. 首先在网关管理网页下的 **<系统>** 下的 **<SSH服务器>** 界面中打开 **SSH服务器**
2. 通过SSH客户端使用 用户名 及 密码 登录后即可进入终端界面

##### TTL/RS232/RS485串口下使用HE指令   
1. 首先在网关管理网页下的 **<应用>** 下的 **<串口1>** 或 **<串口2>**(具体跟据你使用的串口定) 界面中启用 **状态**, 并修改 **模式** 为 **终端命令行** 模式后后应用
2. 通过串口工具连接网关对应的串口即可进入终端界面
 *注:串口默认为57600的波特率（8位数据位/1位停止位/无流控/无校检）*

进入终端命令行后首先会显示简介界面, 界面如下：
```
               EEEEEEEEE   LL           FFFFFFFFF
               EE          LL           FF
               EE          LL           FF
               EEEEEEEEE   LL           FFFFFFFFF
               EE          LL           FF
               EE          LL           FF
        Ashy   EEEEEEEEE   LLLLLLLLLL   FF

 -----------------------------------------------------------
 Command Help
 -----------------------------------------------------------
 @ ----------------------- List all the component
 <com> ------------------- Show component configure
 <com>. ------------------ List all component interface
 <com>:<config> ---------- Get component configure attribute
 <com>:<config>=<value> -- Set component configure attribute
 -----------------------------------------------------------
 # 
```
看到以上简介或出现# 号命令行输入提示符即表示成功登录终端命令行



---
## HE指令格式

#### **HE指令介绍**   
+ 每条命令占一行, 以回车结尾, 终端命令可分为三种类型:
	+ **查询配置**               用于查询网关某些功能当前的一些配置信息
	+ **修改配置**               用于修改网关某些功能的配置
	+ **调用功能项的接口(API)**   用于执行网关某些功能操作, 通常如获取状态/启动/禁用等都属于此类型
+ 命令的返回类型
	+ **字符串**               用于表示单一的信息(被调用的接口返回talk_t类型的字符串), *以换行符结尾后并以#加一个空格在新行提示*
	+ **ttrue** 或 **tfalse** ttrue通常用于表示操作成功, tfalse表示操作失败, *以换行符结尾后并以#加一个空格在新行提示*
	+ **{JSON}**              用于表示一些复杂的信息, 所含多种信息, 以{开头并以}结尾的JSON对象(被调用的接口返回talk_t类型的json结构), *以换行符结尾后并以#加一个空格在新行提示*
	+ **空**                  用于表示未得到可用信息(被调用的接口返回NULL时为空), *以换行符结尾后并以#加一个空格在新行提示*

#### **查询配置**   
+ 查询网关某项功能的所有配置时给出功能对应的 **组件名称** 回车即可
通常返回值是一个JSON
    ```shell
    # land@machine                    # 查询设备基本信息(land@machine组件)的所有配置
    {                                 # 返回一个完整的JSON对象
        "mode":"nmisp",                   # 工作模式
        "name":"ASHYELF-12AAD0",          # 网关名称
        "mac":"00:03:7F:12:AA:D0",        # MAC地址
        "macid":"00037F12AAD0",           # MAC ID
        "language":"cn",                  # 语言
        "cfgversion":"1"                  # 配置版本
    }
    # 
    ```   
    > 具体设备基本信息的配置参数介绍参见 *[设备基本信息](../com/land/machine.md)*

+ 如果只查询功能配置中的某项属性时需要给出属性, 即 **组件名称:属性路径** 回车即可
返回值可以为一个字符串也可以为一个JSON, 具体看对应的属性的值
    ```shell
    # land@machine:name              # 查询设备基本信息中主机名称, 即land@machine配置中的name属性的值
    A218-120108                      # 返回一个字符串
    # 
    ```   

+ 当功能配置的属性有很多层次时, **属性路径** 就会以 **/** 号分隔多层的属性名, 属性路径用于定位属性, 如下
    ```shell
    # ifname@lan:static              # 查询LAN口(ifname@lan)配置中的static属性的值
    {
        "ip":"192.168.8.1",
        "mask":"255.255.255.0"
    }
    # ifname@lan:static/ip           # 查询LAN口(ifname@lan)配置中的static属性下ip属性的值
    192.168.8.1
    # 
    ```   
    > 具体本地网络的配置参数介绍参见 *[本地网络(LAN)](../com/ifname/lan.md)*

    以上示例通过 **属性/下级属性/下级属性/…** 这种路径式的方式来定位多次层属性

#### **修改配置**   
+ 修改网关某项功能的配置与查询相似，首先给出功能对应的 **组件名称**， 然后给出修改属性的 **属性路径**，最后就是给出 **值**
    当修改整个功能的配置时:
    ```shell
    组件名称=值
    ```   
    修改整个功能配置的值时, 值必须为一个JSON(即以{开头并以}结尾)
    修改成功返回 **ttrue**, 失败返回 **tfalse**, 见以下示例
    ```shell
    # forward@alg               # 查询应用层网关(forward@alg)的配置
    {
        "amanda":"disable",
        "ftp":"enable",
        "h323":"disable",
        "irc":"disable",
        "pptp":"enable",
        "gre":"enable",
        "rtsp":"enable",
        "sip":"enable",
        "snmp":"disable",
        "tftp":"disable",
        "udplite":"disable"
    }
    #
    # forward@alg={"amanda":"enable","ftp":"enable","h323":"enable","irc":"enable"}   # 修改整个应用层网关(forward@alg)的配置
    ttrue                          # 返回ttrue表示修改成功
    # forward@alg                  # 修改后再次查看配置, 已发生变化
    {
        "amanda":"enable",
        "ftp":"enable",
        "h323":"enable",
        "irc":"enable"
    }
    # 
    ```   
    > 具体应用层网关的配置参数介绍参见 *[应用层网关](../com/forward/alg.md)*

+ 只修改功能配置指定的属性时, 给出 **组件名称** 时给出 **属性路径** :
    ```shell
    组件名称:属性路径=值
    ```   
    值可以为一个JSON(即以{开头并以}结尾), 也可以为一个字符串
    而返回值如果是 **ttrue** 表示修改成功, 或是 **tfalse** 表示修改失败,见以下示列
    ```shell
    # gnss@nmea                               # 查询全球定位(gnss@nmea)所有的配置
    {
        "status":"enable",
        "client":
        {
            "status":"disable",
            "proto":"tcp",
            "server":"",
            "port":"9000",
            "id":"",
            "user":"",
            "vcode":"",
            "login":"",
            "login_string":"",
            "frame_start":"disable",
            "frame_string_string":"",
            "frame_end":"disable",
            "frame_end_string":""
        },
        "client2":
        {
            "status":"disable",
            "proto":"mqtt",
            "server":"",
            "port":"1883",
            "mqtt_id":"",
            "mqtt_username":"",
            "mqtt_password":"",
            "mqtt_keepalive":"10",
            "mqtt_interval":"",
            "mqtt_publish":"",
            "mqtt_publish_qos":"",
            "mqtt_subscribe":
            {
            }
        },
        "server":
        {
            "status":"disable",
            "proto":"tcp",
            "port":"",
            "limit":"5"
        }
    }
	# gnss@nmea:client                        # 查询全球定位(gnss@nmea)配置中的client属性的值
    {
        "status":"disable",
        "proto":"tcp",
        "server":"",
        "port":"9000",
        "id":"",
        "user":"",
        "vcode":"",
        "login":"",
        "login_string":"",
        "frame_start":"disable",
        "frame_string_string":"",
        "frame_end":"disable",
        "frame_end_string":""
    }
	# gnss@nmea:client={"status":"enable","server":"192.168.8.250","port":"8000","interval":"30","id":"2232"}  # 修改全球定位(gnss@nmea)配置中的client属性
	ttrue
	# gnss@nmea:client                       # 查询全球定位(gnss@nmea)配置中client属性修改后的结果
    {
        "status":"enable",
        "server":"192.168.8.250",
        "port":"8000",
        "interval":"30",
        "id":"2232"
    }
	# gnss@nmea:client/server=192.168.8.251  # 修改全球定位(gnss@nmea)配置中client属性下server属性的值
	ttrue
	# gnss@nmea:client                       # 查询修改后的结果
	{
	    "status":"enable",
	    "server":"192.168.8.251",
	    "port":"8000",
	    "interval":"30",
	    "id":"2232"
	}
	# gnss@nmea                              # 查询全球定位(gnss@nmea)所有的配置
    {
        "status":"enable",
        "client":
        {
            "status":"enable",
            "server":"192.168.8.251",
            "port":"8000",
            "interval":"30",
            "id":"2232"
        },
        "client2":
        {
            "status":"disable",
            "proto":"mqtt",
            "server":"",
            "port":"1883",
            "mqtt_id":"",
            "mqtt_username":"",
            "mqtt_password":"",
            "mqtt_keepalive":"10",
            "mqtt_interval":"",
            "mqtt_publish":"",
            "mqtt_publish_qos":"",
            "mqtt_subscribe":
            {
            }
        },
        "server":
        {
            "status":"disable",
            "proto":"tcp",
            "port":"",
            "limit":"5"
        }
    }
	# 
    ```   
    > 具体全球定位的配置参数介绍参见 *[全球定位](../com/gnss/nmea.md)*
 
+ 当修改功能配置中指定的几个属性而不影响其它属性时:
    ```shell
    组件名称|{“属性1”:”值1”, “属性2”:”值2” , “属性3”:”值3”}
    ```   
    值1, 值2, 值3通常为一个字符串
    而返回值如果是 **ttrue** 表示修改成功, 或是 **tfalse** 表示修改失败,见以下示列
    ```shell
	# gnss@nmea:client                      # 查询全球定位(gnss@nmea)中client属性的值
	{
	    "status":"enable",
	    "server":"192.168.8.251",
	    "port":"8000",
	    "interval":"30",
	    "id":"2232"
	}
	# gnss@nmea:client|{"status":"disable","server":"192.168.2.11","proto":"tcp"}  # 修改全球定位(gnss@nmea)中client属性的值, 但不影响其它未给出的属性
	ttrue
	# gnss@nmea:client                      # 再次查询时指定的几项属性已改变, 未指定的属性未发生变化
	{
        "status":"disable",                 # 已修改
        "server":"192.168.2.11",            # 已修改
        "port":"8000",                      # 未变化
        "interval":"30",                    # 未变化
        "id":"2232",                        # 未变化
        "proto":"tcp"                       # 已添加
	}
	# 
    ```   
    > 具体全球定位的配置参数介绍参见 *[全球定位](../com/gnss/nmea.md)*
 
+ 当要清除功能配置的某个属性时可以在=号后直接回车即可:
    ```shell
    组件名称:属性路径=
    ```   
    而返回值如果是 **ttrue** 表示清除成功, 或是 **tfalse** 表示清除失败,见以下示列
    ```shell
    # gnss@nmea                         # 查询全球定位(gnss@nmea)所有的配置
    {
        "status":"enable",
        "client":
        {
            "status":"disable",
            "server":"192.168.2.11",
            "port":"8000",
            "interval":"30",
            "id":"2232",
            "proto":"tcp"
        },
        "client2":
        {
            "status":"disable",
            "proto":"mqtt",
            "server":"",
            "port":"1883",
            "mqtt_id":"",
            "mqtt_username":"",
            "mqtt_password":"",
            "mqtt_keepalive":"10",
            "mqtt_interval":"",
            "mqtt_publish":"",
            "mqtt_publish_qos":"",
            "mqtt_subscribe":
            {
            }
        },
        "server":
        {
            "status":"disable",
            "proto":"tcp",
            "port":"",
            "limit":"5"
        }
    }
	# gnss@nmea:client=                 # 清除全球定位(gnss@nmea)中client属性
	ttrue
	# gnss@nmea                         # 再次查询全球定位(gnss@nmea)所有的配置时已无client属性
    {
        "status":"enable",
        "client2":
        {
            "status":"disable",
            "proto":"mqtt",
            "server":"",
            "port":"1883",
            "mqtt_id":"",
            "mqtt_username":"",
            "mqtt_password":"",
            "mqtt_keepalive":"10",
            "mqtt_interval":"",
            "mqtt_publish":"",
            "mqtt_publish_qos":"",
            "mqtt_subscribe":
            {
            }
        },
        "server":
        {
            "status":"disable",
            "proto":"tcp",
            "port":"",
            "limit":"5"
        }
    }
	# 
    ```   
    > 具体全球定位的配置参数介绍参见 *[全球定位](../com/gnss/nmea.md)*


#### **调用功能项的接口(API)**   

调用功能项的接口(API)需要给出功能项对应的组件名称及接口名称(API), 如有参数时还需要带入参数

+ 当调用功能项接口(API)不带参数时    
    ```shell
    组件名称.接口名称
    ```   
    ```shell
    # client@station.list                     # 调用终端管理(client@station)的list接口(API)获取当前客户端例表
    {
        "B4:2E:99:3F:ED:12":
        {
            "ip":"192.168.8.250",
            "device":"lan"
        }
    }
    # 
    ```   
    > 具体终端管理的API介绍参见 *[终端管理](../com/client/station.md)*
 
+ 当调用功能项接口(API)带参数时
    ```shell
    组件名称.接口名称[ 参数 ]
    ```   
    ```shell
    # clock@date.ntpsync[ntp1.aliyun.com]       # 调用系统时间(clock@date)的ntpsync接口(API)实现与ntp1.aliyun.com的NTP对时
    ttrue
    # 
    ```   
    > 具体时间管理的API介绍参见 *[系统时间](../com/clock/date.md)*

+ 当调用功能项接口(API)带多个参数时
    ```shell
    组件名称.接口名称[ 参数1, 参数2, 参数3, … ]
    ```   
    ```shell
    # land@auth.add[,xiaomi,4431232]  # 调用帐号密码及权限(land@auth)的add接口(API)来添加帐号, 第一个参数域为空(无), 第二个参数帐号为xiaomi, 第三个参数密码为4431232
    ttrue
    # land@auth.list                  # 调用帐号密码及权限(land@auth)的list接口(API)来获取当前所有的帐号
    {
        "admin":
        {
            "key":"|*|V223KJDFLKJLKJA23232323543453453452323KJKHUI2KJKHKJKJKH22232321334"
        },
        "xiaomi":
        {
            "key":"|*|V24E4555304E4455784E304530524455304E446B33515452454E6A637A52444E45"
        }
    }
    ```   
    > 具体用户管理的接口介绍参见 *[用户名密码及权限](../com/land/auth.md)*

+ 当调用的功能项接口(API)返回JSON时, 可以要求只返回JSON中指定的属性值
    ```shell
    组件名称.接口名称:属性路径
    ```   
    ```shell
    # ifname@lte.status                     # 调用LTE/NR(4G/5G)网络(ifname@lte)的status接口获取状态
    {
        "mode":"dhcpc",
        "ifname":"ifname@lte",
        "netdev":"usb1",
        "gw":"10.33.13.104",
        "dns":"120.80.80.80",
        "dns2":"221.5.88.88",
        "ifdev":"modem@lte2",
        "ontime":"754",
        "metric":"10",
        "status":"up",
        "ip":"10.33.13.103",
        "mask":"255.255.255.240",
        "livetime":"05:03:36:0",
        "rx_bytes":"2681665",
        "rx_packets":"27616",
        "tx_bytes":"1433806",
        "tx_packets":"21926",
        "mac":"02:50:F4:00:00:00",
        "tid":"2",
        "devcom":"modem@device",
        "name":"Quectel-EC2X",
        "imei":"864337056708978",
        "mversion":"20CEFHLGR06A05M1G",
        "iccid":"89860121801097564807",
        "imsi":"460015356123463",
        "pcid":"184",
        "lac":"2604",
        "ci":"6DA5A09",
        "netera":"4G",
        "rsrp":"-96",
        "nettype":"FDD LTE",
        "rssi":"-66",
        "rsrq":"-9",
        "sinr":"-19",
        "band":"LTE BAND 3",
        "plmn":"46001",
        "csq":"25",
        "signal":"4",
        "operator":"中国联通"
        "operator_advise":
        {
            "name":"中国联通",
            "dial":"*99#",
            "apn":"3gnet"
        },
        "state":"connected"
    }
    # ifname@lte.status:ip                   # 调用LTE/NR(4G/5G)网络(ifname@lte)的status接口获取状态, 并要求只返回状态中的ip地址
    10.33.13.103
    # ifname@lte.status:operator_advise      # 调用LTE/NR(4G/5G)网络(ifname@lte)的status接口获取状态, 并要求只返回状态中有关运营商的建议配置
    {
        "name":"中国联通",
        "dial":"*99#",
        "apn":"3gnet"
    }
    # ifname@lte.status:operator_advise/apn  # 调用LTE/NR(4G/5G)网络(ifname@lte)的status接口获取状态, 并要求只返回状态中有关运营商的建议的APN的配置
    3gnet
    ```   
    > 具体LTE/NR网络管理的接口(API)介绍参见 *[LTE/NR(4G/5G)网络](../com/ifname/lte.md)*



---

## 常用的HE指令
以下介绍常用的HE指令， 如查询LTE/NR信息， 全球定位及重置网关等指令，更多指令可参看各个功能组件的接口文档

#### **获取网关基本配置**   
输入
```shell
# land@machine
```   
返回
```shell
{
    "mode":"misp",                        # 工作模式
                                            #    gateway为网关
                                            #    ap为热点
                                            #    bridge为桥
                                            #    repeater为中继
                                            #    wisp为WISP
                                            #    misp为4G
                                            #    mix为混合模式
    "name":"D218-123310",                # 设备名
    "macid":"00037F123310",              # MAC号
    "mac":"00:03:7F:12:33:10",           # MAC地址
    "language":"cn",                     # 语言
    "gpversion":"v4.3.2",                # 组配置版本
    "cfgversion":"44"                    # 配置版本
}
```   
点击 [设备基本信息](../com/land/machine.md) 查看更多

#### **获取网关基本状态**   
输入
```shell
# 调用land@machine组件的status接口
# land@machine.status
```   
返回
```shell
{
    "platform":"smtk",                   # 平台编号
    "hardware":"mt7628",                 # 芯片编号
    "custom":"d218",                     # 产品编号
    "scope":"std",                       # 定制编号
    "version":"4.3.3d",                  # 版本号
    "macid":"00037F123310",              # MAC号
    "mac":"00:03:7F:12:33:10",           # MAC地址
    "magic":"23571121DF68ACC3",
    "model":"D218",                      # 产品型号
    "mode":"misp"                        # 工作模式
    "livetime":"00:01:18:0",             # 在线时长: 时：分：秒：天
    "current":"01:41:15:01:01:2016"      # 当前时间  时:分:秒:月:日:年
}
```   
点击 [设备基本信息](../com/land/machine.md) 查看更多


#### **获取LTE/NR(4G/5G)网络状态**   
输入
```shell
// 调用ifname@lte组件的status接口
# ifname@lte.status
```   
返回
```shell
{
    "mode":"dhcpc",                    # 拨号模式, dhcpc为自动获取, ppp为PPP拨号, static为静态IP
    "netdev":"usb0",                   # netdev is usb0
    "gw":"10.137.89.118",              # 网关
    "dns":"120.80.80.80",              # DNS
    "dns2":"221.5.88.88",              # DNS
    "status":"up",                     # up表示已连接, down表示未连接, uping表示连接中
    "ip":"10.137.89.117",              # IP地址
    "mask":"255.255.255.252",          # 子网掩码
    "livetime":"00:15:50:0",           # 在线时长 时:分:秒:天
    "rx_bytes":"1256",                 # 收包字节
    "rx_packets":"4",                  # 收包数
    "tx_bytes":"1320",                 # 发包字节
    "tx_packets":"4",                  # 发包数
    "mac":"02:50:F4:00:00:00",         # MAC地址
    "imei":"867160040494084",          # IMEI号
    "imsi":"460015356123463",          # IMSI号
    "iccid":"89860121801097564807",    # ICCID号
    "csq":"3",                         # CSQ
    "signal":"3",                      # 信号格数(1-4格), 1表示一格, 2表示两格, 3表示三格, 4表示四格, 0或空表示无信号
    "state":"connect",                 #  当前LTE模块状态
    "plmn":"46001",
    "nettype":"WCDMA",                 # 网络类型
    "rssi":"-107",                     # 信号强度, dBm值
    "operator":"中国联通"               # 运营商名称
}
```   
点击查看 [(LTE/NR(4G/5G)网络)](../com/ifname/lte.md) 及 [LTE/NR(4G/5G)基带](../com/modem/lte.md) 介绍

#### **获取第二个LTE/NR(4G/5G)网络状态**   
输入
```shell
// 调用ifname@lte2组件的status接口
# ifname@lte2.status
```   
返回
```shell
{
    与 ifname@lte.status 的返回相同
}
```   
点击查看 [(LTE/NR(4G/5G)网络)](../com/ifname/lte.md) 及 [LTE/NR(4G/5G)基带](../com/modem/lte.md) 介绍


#### **获取客户端信息**   
输入
```shell
// 调用client@station组件的list接口
# client@station.list
```   
返回
```shell
{
    "00:E0:4C:68:2A:8B":                           # 客户端MAC地址
    {
        "ip":"192.168.1.250",                        # IP地址
        "device":"lan",                              # 接入的网络接口
        "ifname":"ifname@lan",                       # 接入的网络连接
        "ontime":"25172",                            # 上线时网关的启动秒数
        "livetime":"00:40:25:0"                      # 连接时间
    },
    "FC:87:43:DC:6F:B4":                          # 客户端MAC地址
    {
        "ip":"192.168.1.248",                        # IP地址
        "device":"lan",                              # 接入的网络接口
        "ifname":"ifname@lan",                       # 接入的网络连接
        "ontime":"25186",                            # 上线时网关的启动秒数
        "livetime":"00:40:11:0",                     # 连接时间
        "ifdev":"wifi@assid",                        # 接入的连接设备
        "rssi":"-73",                                # 信号强度, 只有连接设备为热点类设备才有此属性
        "name":"HUAWEI_P30_Pro-9f13d2ee6f",          # 客户端名称
        "tx_bytes":"610528",                         # 发送字节
        "rx_bytes":"1653658"                         # 接收字节
    }
}
```   
点击查看 [终端管理](../com/client/station.md) 介绍

#### **获取定位信息**   
输入
```shell
// 调用gnss@nmea组件的info接口
# gnss@nmea.info
```
返回
```shell
{
    "step":"search",       # GPS定位步骤, notty无端口, search搜索信号中, located已定位
    "utc":"",              # nmea的UTC格式
    "lon":"",              # 经度
    "lat":"",              # 纬度
    "speed":"",            # 速度
    "direction":"",        # 方向
    "declination":"",
    "elv":"",              # 海拨高度, 米为单位
    "sat":""               # 卫星数
}
```   
点击查看 [全球定位](../com/gnss/nmea.md) 介绍


#### **获取LAN口信息**   
输入
```shell
// 调用ifname@lan组件的status接口
# ifname@lan.status
```   
返回
```shell
{
    "status":"up",                        # up表示已连接, down表示未连接, uping表示连接中
    "mode":"static",                      # IP模式, dhcpc为自动获取, static为静态IP
    "ip":"192.168.1.1",                   # IP地址
    "mask":"255.255.255.0",               # 子网掩码
    "mac":"76:C7:8C:05:39:F3",            # MAC地址
    "rx_bytes":"6864",                    # 增量收包字节
    "rx_packets":"65",                    # 增量收包数
    "tx_bytes":"7296",                    # 增量发包字节
    "tx_packets":"74",                    # 增量发包数
    "livetime":"00:04:37:0"               # 在线时长 时:分:秒:天
}
```   
点击查看 [本地网络(LAN)](../com/ifname/lan.md) 介绍

#### **重启网关**   
输入
```shell
// 调用land@machine组件的restart接口
# land@machine.restart
```   
网关不返回任何信息， 将会立即重启
点击查看 [设备基本信息](../com/land/machine.md) 介绍

#### **重置网关(恢复默认设置)**   
输入
```shell
// 调用land@machine组件的default接口
# land@machine.default
```   
网关不返回任何信息， 将会立即重启并重置所有配置
点击查看 [设备基本信息](../com/land/machine.md) 介绍


#### **修改LTE/NR(4G/5G)的APN**   
输入
```shell
// 修改ifname@lte组件配置的属性下的profile属性的值为enable(表示自定义APN), 并且在profile_cfg下的apn属性的值中给出APN, 以下就是修改APN为MyCustomAPN
# ifname@lte|{"profile":"enable","profile_cfg":{"apn":"MyCustomAPN"}}
```   
返回
```shell
ttrue
```   
点击查看 [LTE/NR(4G/5G)网络](../com/ifname/lte.md) 及 [LTE/NR(4G/5G)基带](../com/modem/lte.md) 介绍

#### **开启LTE/NR(4G/5G)的定位功能**   
输入
```shell
// 修改ifname@lte组件配置的gnss的值为enable
# ifname@lte:gnss=enable
```   
返回
```shell
ttrue
```   
点击查看 [LTE/NR(4G/5G)网络](../com/ifname/lte.md) 及 [LTE/NR(4G/5G)基带](../com/modem/lte.md) 介绍

#### **开启全球定位功能**   
输入
```shell
// 修改gnss@nmea组件配置的status的值为enable
# gnss@nmea:status=enable
```   
返回
```shell
ttrue
```   
点击查看 [全球定位](../com/gnss/nmea.md) 介绍

#### **修改无线2.4G热点的SSID名称**   
输入
```shell
// 修改wifi@nssid组件配置的ssid的值为NewSSID
# wifi@nssid:ssid=NewSSID
```   
返回
```shell
ttrue
```   
点击查看 [2.4G热点](../com/wifi/nssid.md) 介绍

#### **修改无线2.4G热点的密码**   
输入
```shell
// 修改wifi@nssid组件配置的wpa_key的值为NewPassword
# wifi@nssid:wpa_key=NewPassword
```   
返回
```shell
ttrue
```   
点击查看 [2.4G热点](../com/wifi/nssid.md) 介绍

#### **同时修改无线2.4G热点的SSID名称及密码**   
输入
```shell
// 修改wifi@nssid组件的配置中的ssid, secure及wpa_key三个属性的值 
# wifi@nssid|{"ssid":"NewSSID","secure":"wpapskwpa2psk","wpa_key":"NewPassword"}
```
返回
```shell
ttrue
```   
点击查看 [2.4G热点](../com/wifi/nssid.md) 介绍

#### **修改无线5.8G热点的SSID名称**   
输入
```shell
// 修改wifi@assid组件配置的ssid的值为NewSSID
# wifi@assid:ssid=NewSSID
```   
返回
```shell
ttrue
```   
点击查看 [5.8G热点](../com/wifi/assid.md) 介绍

#### **修改无线5.8G热点的密码**   
输入
```shell
// 修改wifi@assid组件配置的wpa_key的值为NewPassword
# wifi@assid:wpa_key=NewPassword
```   
返回
```shell
ttrue
```   
点击查看 [5.8G热点](../com/wifi/assid.md) 介绍

#### **同时修改无线5.8G热点的SSID名称及密码**   
输入
```shell
// 修改wifi@assid组件的配置中的ssid, secure及wpa_key三个属性的值 
# wifi@assid|{"ssid":"NewSSID","secure":"wpapskwpa2psk","wpa_key":"NewPassword"}
```   
返回
```shell
ttrue
```   
点击查看 [5.8G热点](../com/wifi/assid.md) 介绍


#### **修改admin用户的密码**   
输入
```shell
// 调用land@auth的modify接口, 参数1域表示为空, 参数2用户名为admin, 参数3原密码为admin, 参数4新密码为NewPassword
# land@auth.modify[,admin,admin,NewPassword]
```   
返回
```shell
ttrue
```   
点击查看 [用户名密码及权限](../com/land/auth.md) 介绍



---
##  参照功能组件文档使用HE指令管理网关

有两种方式可以查询所有组件文档, 通过这些组件文档可以管理网关的每一个功能
- 访问 [在线组件文档](../com/) 查看组件文档, 此在线文件会随着开发新的功能动态增加及修订
- 资询技术支持人员

#### 组件文档要点

- 在 [在线组件文档](../com/) 中以目录的形式列出了系统中常用的项目, 每个项目下包含了组件文档
- 点击项目进入项目中, 会以行的形式列出此项目下所有的组件文档
- 点击组件打开组件文档, 文件开始是功能介绍
- 然后就是 **Configuration**, 配置是JSON格式, 其中还有查询或修改的示例, 可以在HE指令中查询或修改这些配置
- 之后通常是介绍此组件的 **Methods**, 即接口(API), 其中还有调用的示例, 可以在HE指令中调用这些接口

#### 参照功能组件文档查询组件配置

在组件 **Configuration** 中会给出组件名, 比如 [日志管理](../com/land/syslog.md) 的组件名为 **land@syslog**

- 在终端中输入 **组件名** 回车即会返回此组件的所有配置, 而在组件文档中的 **Configuration** 中会详细介绍每个配置的属性及示例
    ```shell
    # land@syslog                             # 输入组件名
    {                                         # 返回一个JSON, JSON中为组件所有的配置
        "status":"enable",                # 开启syslog
        "type":"init|serv|joint|default", # 记录启动项及关机项, 服务, 事件及其它默认类型相关的日志
        "level":"info",                   # 只记录通知级别的日志
        "trace":"enable",                 # 记录代码位置及进程ID
        "size":"20",                      # 记录池为20k
        "remote":"192.168.8.100",         # 远程日志服务器地址为192.168.8.100
        "port":"514"                      # 远程日志服务器的端口为514
    }
    #
    ```

- 也可以在终端中查询组件配置中指定的属性, 只需要在 **组件名** 后以 **:属性** 给出指定的属性
    ```shell
    # land@syslog:level                     # 查询日志管理组中的level的属性的值
    info                                    # level属性的值为info
    #
    ```

#### 参照功能组件文档修改组件配置

接以上 [日志管理](../com/land/syslog.md) 的组件文档, 在文档的 **Configuration** 中描述属性可以在终端中通过 **组件名** 后加 **:属性** 加 **=值** 来修改
- 在终端中修改land@syslog的远程日志服务器remote属性
    ```shell
    # land@syslog:remote=192.168.8.250       # 将land@syslog的远程日志服务器改为192.168.8.250
    ttrue                                    # ttrue表示修改成功, 如返回tfalse表示修改失败
    #
    ```

- 在终端中同时修改land@syslogd的多个属性, 同时修改多个属性时必须以JSON的格式封装需要修改的属性, 以下同时修改remote及port两个属性, 并不对其它的属性产生任何影响
    ```shell
    # land@syslog|{"remote":"192.168.8.251","port":"500"}    # 修改land@syslog的remote为192.168.8.251, 并且修改port为500
    ttrue                                                    # ttrue表示修改成功, 如返回tfalse表示修改失败
    #
    ```

- 在终端中设置land@syslogd所有的配置, 组件配置都是一个JSON, 如要修改所有的配置必须同样的给出一个JSON
    ```shell
    # land@syslog={"status":"enable","location":"memory","type":"default|init","level":"info","trace":"disable","size":"100"}            # 设置land@syslog所有的配置
    ttrue                                    # ttrue表示修改成功, 如返回tfalse表示修改失败
    #
    ```

#### 参照功能组件文档调用组件接口

接以上 [日志管理](../com/land/syslog.md) 的组件文档, 在文档 **Methods** 中描述的接口都可以在终端中通过 **组件名** 后加 **.接口** 来调用
- 在终端中调用组件land@syslog的show接口显示当前日志
    ```shell
    # land@syslog.show
    Dec 15 15:47:20 V520-12CC70 user.warn syslog: modem@lte check simcard failed 102 times
    Dec 15 15:47:25 V520-12CC70 user.warn syslog: modem@lte check simcard failed 103 times
    Dec 15 15:47:30 V520-12CC70 user.warn syslog: modem@lte check simcard failed 104 times
    Dec 15 15:47:35 V520-12CC70 user.warn syslog: modem@lte check simcard failed 105 times
    Dec 15 15:47:40 V520-12CC70 user.warn syslog: modem@lte check simcard failed 106 times
    Dec 15 15:47:45 V520-12CC70 user.warn syslog: modem@lte check simcard failed 107 times
    Dec 15 15:47:50 V520-12CC70 user.warn syslog: modem@lte check simcard failed 108 times
    Dec 15 15:47:55 V520-12CC70 user.warn syslog: modem@lte check simcard failed 109 times
    Dec 15 15:48:00 V520-12CC70 user.warn syslog: modem@lte check simcard failed 110 times
    Dec 15 15:48:05 V520-12CC70 user.warn syslog: modem@lte check simcard failed 111 times
    Dec 15 15:48:10 V520-12CC70 user.warn syslog: modem@lte check simcard failed 112 times
    Dec 15 15:48:15 V520-12CC70 user.warn syslog: modem@lte check simcard failed 113 times
    Dec 15 15:48:20 V520-12CC70 user.warn syslog: modem@lte check simcard failed 114 times
    Dec 15 15:48:25 V520-12CC70 user.warn syslog: modem@lte check simcard failed 115 times
    Dec 15 15:48:30 V520-12CC70 user.warn syslog: modem@lte check simcard failed 116 times
    Dec 15 15:48:35 V520-12CC70 user.warn syslog: modem@lte check simcard failed 117 times
    #
    ```
- 在终端中调用组件land@syslog的clear接口清除当前所有日志
    ```shell
    # land@syslog.clear
    ttrue
    #
    ```


##  在终端中如何进入Linux的Shell命令行

如果需要进一步的操作Linux系统, 进入熟悉的Linux Shell环境可以在终端中输入如下进入Linux Shell命令行
```shell
# elf

BusyBox v1.22.1 (2021-04-20 10:35:42 CST) built-in shell (ash)
Enter 'help' for a list of built-in commands.

~ #
```

#### 在Linux Shell命令行中执行HE指令

在Shell命令行中偶尔需要执行HE指令, 只要输入
```shell
he <HE指令>
```

即可, HE指令的格式与终端中的一致
而对于比较复杂的HE指令因涉及Shell的一些专用字符, 为了不被Shell命令行解析可加入单引号
```shell
he '<HE指令>'
```

示例如下:
```shell
# elf

BusyBox v1.22.1 (2021-04-20 10:35:42 CST) built-in shell (ash)
Enter 'help' for a list of built-in commands.

~ # he 'machine'
{
    "platform":"smtk",
    "hardware":"mt7621",
    "custom":"v520",
    "scope":"donkey",
    "language":"cn",
    "macid":"88124E200030",
    "mac":"88:12:4E:20:00:30",
    "name":"V520-200030",
    "title":"V520-200030",
    "mode":"donkeycon"
}
~ # he 'machine.status'
{
    "custom":"v520",
    "version":"4.3.3w-042021",
    "publish":"042021",
    "macid":"88124E200030",
    "mac":"88:12:4E:20:00:30",
    "magic":"D7441F2CE4605020",
    "model":"V520",
    "name":"V520-200030",
    "mode":"donkeycon",
    "livetime":"00:18:28:0",
    "current":"12:11:16:04:20:2021"
}
~ #
```
