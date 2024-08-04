
# 终端管理命令行使用介绍   
SkinOS为一个基于Linux的操作系统, 运行于 **网关** 或 **路由器** 等终端产品中, SkinOS系统提供以下几种方式进入 **终端管理命令行**   
- 通过Telnet客户端连接网关登录后进入   
- 通过SSH客户端连接网关登录后进入   
- 通过TTL串口连接网关后进入   
- 通过RS232串口连接网关后进入   
- 通过RS485串口连接网关后进入   

**终端管理命令行** 用于执行 **HE指令**, 通过执行 **HE指令** 可以管理网关, 实现如:   
- 查询网关配置   
- 设置网关配置   
- 调用网关的接口如重启或重置网关等各种管理操作  

**HE指令** 不止是在 **终端管理命令行** 中执行, 在一些控制协议中也都支持, 通过以下几种方式连接网关 **终端管理命令行** 执行HE指令:   
- **Telnet客户端** 下使用HE指令   
    - 首先在网关 **网页管理界面** 下的 **<系统>** 下的 **<Telnet服务器>** 界面中打开 **Telnet服务器**   
    - 再通过Telnet客户端使用 **用户名** 及 **密码** 登录网关后即可进入终端命令行   
    ***注:登录用户名及密码与网页管理界面帐号一致***   
- **SSH客户端** 下使用HE指令   
    - 首先在网关 **网页管理界面** 下的 **<系统>** 下的 **<SSH服务器>** 界面中打开 **SSH服务器**   
    - 再通过SSH客户端使用 **用户名** 及 **密码** 登录后即可进入终端命令行   
    ***注:登录用户名及密码与网页管理界面帐号一致***   
- **TTL/RS232/RS485串口** 下使用HE指令   
    - 首先在网关 **网页管理界面** 下的 **<应用>** 下的 **<串口1>** 或 **<串口2>**(具体跟据需要使用的串口定)界面中启用 **状态**, 并修改 **模式** 为 **终端命令行** 模式后应用   
    - 再通过串口工具连接网关对应的串口即可进入终端命令行   
    ***注:串口默认为57600的波特率(8位数据位/1位停止位/无流控/无校检)***   

进入 **终端管理命令行** 后首先会显示简介界面, 界面如下:   
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
 $ 
```   
看到以上简介或出现$ 号命令行输入提示符即表示成功登录 **终端管理命令行**   



## HE指令格式   
在 **终端管理命令行** 输入 **HE指令** 后 **回车** 即可执行   

### **HE指令介绍**   
+ 每条指令占一行, 指令可分为三种类型:   
	+ **查询配置**               用于查询网关某些功能当前的配置   
	+ **修改配置**               用于修改网关某些功能的配置   
	+ **调用功能项的接口(API)**   用于执行网关某些功能操作, 通常如获取状态/启动/禁用/重启/重置等都属于此类型   
+ 命令的返回类型, 跟据指令类型的不同及执行的情况返回不同的类型   
	+ **字符串**               用于表示单一的信息   
	+ **ttrue** 或 **tfalse** ttrue通常用于表示操作成功, tfalse表示操作失败   
	+ **{JSON}**              用于表示一些复杂的信息, 所含多种信息, 以{开头并以}结尾的JSON对象   
	+ **空**                  用于表示未得到可用信息

### **查询配置的HE指令**   
+ 查询网关某项功能所有配置时给出功能对应的 **组件名称** 即可 
通常返回值是一个 **{JSON}**, 包括这个功能项所有的配置信息   
    ```shell
    $ land@machine                    # 终端管理命令行中查询网关基本信息(land@machine组件)所有配置
    {                                 # 返回一个完整的JSON对象
        "mode":"nmisp",                   # 工作模式
        "name":"ASHYELF-12AAD0",          # 网关名称
        "mac":"00:03:7F:12:AA:D0",        # MAC地址
        "macid":"00037F12AAD0",           # MAC ID
        "language":"cn",                  # 语言
        "cfgversion":"1"                  # 配置版本
    }
    $ 
    ```   
    > 具体网关基本信息的配置参数介绍参见 *[网关基本信息](../com/land/machine.md)*   

+ 如果只查询功能配置中的某项属性时需要给出属性, 即 **组件名称:属性路径** 即可   
返回值可以为一个 **字符串** 也可以为一个 **{JSON}**, 具体看配置对应属性的值   
    ```shell
    $ land@machine:name              # 终端管理命令行中查询网关基本信息中主机名称, 即land@machine配置中的name属性的值
    A218-120108                      # 返回一个字符串
    $ 
    ```   

+ 当功能配置的属性有很多层次时, **属性路径** 就会以 **/** 号分隔多层的属性名, 属性路径用于定位属性值, 如下:   
    ```shell
    $ ifname@lan:static              # 查终端管理命令行中询LAN口(ifname@lan)配置中的static属性的值
    {
        "ip":"192.168.8.1",
        "mask":"255.255.255.0"
    }
    $ ifname@lan:static/ip           # 终端管理命令行中查询LAN口(ifname@lan)配置中的static属性下ip属性的值
    192.168.8.1
    $ 
    ```   
    > 具体本地网络的配置参数介绍参见 *[本地网络(LAN)](../com/ifname/lan.md)*   

    以上示例通过 **属性/下级属性/下级属性/…** 这种路径式的方式来定位多次层属性值   

### **修改配置的HE指令**   
+ 修改网关某项功能的配置与查询相似，首先给出功能对应的 **组件名称**， 然后给出修改属性的 **属性路径**，最后就是给出 **值**   
    当修改整个功能项的配置时:   
    ```shell
    组件名称=值
    ```   
    修改整个功能配置的值时, 值必须为一个 **{JSON}**, 即以{开头并以}结尾   
    修改成功返回 **ttrue**, 失败返回 **tfalse**, 见以下示例   
    ```shell
    $ forward@alg               # 终端管理命令行中查询应用层网关(forward@alg)的配置
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
    $
    $ forward@alg={"amanda":"enable","ftp":"enable","h323":"enable","irc":"enable"}   # 终端管理命令行中修改整个应用层网关(forward@alg)的配置
    ttrue                          # 返回ttrue表示修改成功
    $ forward@alg                  # 修改后再次查看配置, 已发生变化
    {
        "amanda":"enable",
        "ftp":"enable",
        "h323":"enable",
        "irc":"enable"
    }
    $ 
    ```   
    > 具体应用层网关的配置参数介绍参见 *[应用层网关](../com/forward/alg.md)*   

+ 只修改功能配置指定的属性时, 给出 **组件名称** 时给出 **属性路径** :   
    ```shell
    组件名称:属性路径=值   
    ```   
    值可以为 **{JSON}**(即以{开头并以}结尾), 也可以为 **字符串**   
    而返回值如果是 **ttrue** 表示修改成功, 或是 **tfalse** 表示修改失败,见以下示列   
    ```shell
    $ gnss@nmea                               # 终端管理命令行中查询全球定位(gnss@nmea)所有配置
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
	$ gnss@nmea:client                        # 终端管理命令行中查询全球定位(gnss@nmea)配置中的client属性的值
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
	$ gnss@nmea:client={"status":"enable","server":"192.168.8.250","port":"8000","interval":"30","id":"2232"}  # 终端管理命令行中修改全球定位(gnss@nmea)配置中的client属性
	ttrue
	$ gnss@nmea:client                       # 终端管理命令行中查询全球定位(gnss@nmea)配置中client属性修改后的结果
    {
        "status":"enable",
        "server":"192.168.8.250",
        "port":"8000",
        "interval":"30",
        "id":"2232"
    }
	$ gnss@nmea:client/server=192.168.8.251  # 终端管理命令行中修改全球定位(gnss@nmea)配置中client属性下server属性的值
	ttrue
	$ gnss@nmea:client                       # 终端管理命令行中查询修改后的结果
	{
	    "status":"enable",
	    "server":"192.168.8.251",
	    "port":"8000",
	    "interval":"30",
	    "id":"2232"
	}
	$ gnss@nmea                              # 终端管理命令行中查询全球定位(gnss@nmea)所有的配置
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
	$ 
    ```   
    > 具体全球定位的配置参数介绍参见 *[全球定位](../com/gnss/nmea.md)*   
 
+ 当修改功能配置中指定的几个属性而不影响其它属性时可如下操作:   
    ```shell
    组件名称|{“属性1”:”值1”, “属性2”:”值2” , “属性3”:”值3”}   
    ```   
    值1, 值2, 值3通常为 **字符串**    
    而返回值如果是 **ttrue** 表示修改成功, 或是 **tfalse** 表示修改失败,见以下示列   
    ```shell
	$ gnss@nmea:client                      # 终端管理命令行中查询全球定位(gnss@nmea)中client属性的值
	{
	    "status":"enable",
	    "server":"192.168.8.251",
	    "port":"8000",
	    "interval":"30",
	    "id":"2232"
	}
	$ gnss@nmea:client|{"status":"disable","server":"192.168.2.11","proto":"tcp"}  # 终端管理命令行中修改全球定位(gnss@nmea)中client属性的值, 不影响其它未给出的属性
	ttrue
	$ gnss@nmea:client                      # 终端管理命令行中再次查询时指定的几项属性已改变, 未指定的属性未发生变化
	{
        "status":"disable",                 # 已修改
        "server":"192.168.2.11",            # 已修改
        "port":"8000",                      # 未变化
        "interval":"30",                    # 未变化
        "id":"2232",                        # 未变化
        "proto":"tcp"                       # 已添加
	}
	$ 
    ```   
    > 具体全球定位的配置参数介绍参见 *[全球定位](../com/gnss/nmea.md)*   
 
+ 当要清除功能配置的某个属性时可以在=号后直接回车即可:   
    ```shell
    组件名称:属性路径=   
    ```   
    而返回值如果是 **ttrue** 表示清除成功, 或是 **tfalse** 表示清除失败,见以下示列   
    ```shell
    $ gnss@nmea                         # 终端管理命令行中查询全球定位(gnss@nmea)所有的配置
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
	$ gnss@nmea:client=                 # 终端管理命令行中清除全球定位(gnss@nmea)中client属性
	ttrue
	$ gnss@nmea                         # 终端管理命令行中再次查询全球定位(gnss@nmea)所有的配置时已无client属性
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
	$ 
    ```   
    > 具体全球定位的配置参数介绍参见 *[全球定位](../com/gnss/nmea.md)*   

### **调用功能项的接口(API)的HE指令**   
调用功能项的接口(API)需要给出功能项对应的组件名称及接口名称(API), 如有参数时还需要带入参数   
+ 当调用功能项接口(API)不带参数时    
    ```shell
    组件名称.接口名称   
    ```   
    ```shell
    $ client@station.list                     # 终端管理命令行中调用终端管理(client@station)的list接口(API)获取当前客户端例表
    {
        "B4:2E:99:3F:ED:12":
        {
            "ip":"192.168.8.250",
            "device":"lan"
        }
    }
    $ 
    ```   
    > 具体终端管理的API介绍参见 *[终端管理](../com/client/station.md)*   
 
+ 当调用功能项接口(API)带参数时   
    ```shell
    组件名称.接口名称[ 参数 ]   
    ```   
    ```shell
    $ clock@date.ntpsync[ntp1.aliyun.com]       # 终端管理命令行中调用系统时间(clock@date)的ntpsync接口(API)实现与ntp1.aliyun.com的NTP对时
    ttrue
    $ 
    ```   
    > 具体时间管理的API介绍参见 *[系统时间](../com/clock/date.md)*   

+ 当调用功能项接口(API)带多个参数时   
    ```shell
    组件名称.接口名称[ 参数1, 参数2, 参数3, … ]   
    ```   
    ```shell
    $ land@auth.add[,xiaomi,4431232]  # 终端管理命令行中调用帐号密码及权限(land@auth)的add接口(API)来添加帐号, 第一个参数域为空(无), 第二个参数帐号为xiaomi, 第三个参数密码为4431232
    ttrue
    $ land@auth.list                  # 终端管理命令行中调用帐号密码及权限(land@auth)的list接口(API)来获取当前所有的帐号
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

+ 当调用的功能项接口(API)返回 **{JSON}** 时, 可以要求只返回JSON中指定的属性值   
    ```shell
    组件名称.接口名称:属性路径   
    ```   
    ```shell
    $ ifname@lte.status                     # 终端管理命令行中调用LTE/NR(4G/5G)网络(ifname@lte)的status接口获取状态
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
    $ ifname@lte.status:ip                   # 终端管理命令行中调用LTE/NR(4G/5G)网络(ifname@lte)的status接口获取状态, 并只返回状态中的ip地址
    10.33.13.103
    $ ifname@lte.status:operator_advise      # 终端管理命令行中调用LTE/NR(4G/5G)网络(ifname@lte)的status接口获取状态, 并只返回状态中有关运营商的建议配置
    {
        "name":"中国联通",
        "dial":"*99#",
        "apn":"3gnet"
    }
    $ ifname@lte.status:operator_advise/apn  # 终端管理命令行中调用LTE/NR(4G/5G)网络(ifname@lte)的status接口获取状态, 并只返回状态中有关运营商的建议的APN的配置
    3gnet
    ```   
    > 具体LTE/NR网络管理的接口(API)介绍参见 *[LTE/NR(4G/5G)网络](../com/ifname/lte.md)*   


---
# 使用终端管理命令行管理网关   

## SkinOS工作模式   
针于不同的应用场景网关可提供不同的工作方式, 网关常用的工作模式如下:   

**4G网关**: 通过3G/4G连接互联网的网关模式, 终端管理命令行中执行如下设置为此模式   
```shell
$ land@machine.mode[misp]          # 切换
ttrue
$ land@machine.restart             # 重启, 需要重启后生效
```   

**4G/5G网关**: 通过4G/5G连接互联网的网关模式, 终端管理命令行中执行如下设置为此模式   
```shell
$ land@machine.mode[nmisp]          # 切换
ttrue
$ land@machine.restart              # 重启, 需要重启后生效
```   

**4G5G猫**: 提供4G/5G猫的功能, 完成与4G/5G网络连接但不获取IP地址, 需要其它的客户端通过DHCP协议获取4G/5G的IP地址, 终端管理命令行中执行如下设置为此模式   
```shell
$ land@machine.mode[mbridge]          # 切换
ttrue
$ land@machine.restart                # 重启, 需要重启后生效
```   

**双4G/5G网关**：通过两个4G/5G连接互联网的网关模式, 只有在有两个4G/5G基带的产品上才支持, 终端管理命令行中执行如下设置为此模式   
```shell
$ land@machine.mode[dmisp]          # 切换
ttrue
$ land@machine.restart              # 重启, 需要重启后生效
```   

**有线网关**：通过有线WAN口连接互联网的网关模式, 终端管理命令行中执行如下设置为此模式    
```shell
$ land@machine.mode[gateway]          # 切换
ttrue
$ land@machine.restart                # 重启, 需要重启后生效
```   

**双WAN口网关**：通过两个有线WAN口连接互联网的网关模式, 终端管理命令行中执行如下设置为此模式   
```shell
$ land@machine.mode[dgateway]          # 切换
ttrue
$ land@machine.restart                 # 重启, 需要重启后生效
```   

**2.4G无线连网网关**：通过2.4G无线客户端连接其它WIFI网络的网关模式, 终端管理命令行中执行如下设置为此模式   
```shell
$ land@machine.mode[wisp]          # 切换
ttrue
$ land@machine.restart             # 重启, 需要重启后生效
```   

**5.8G无线连网网关**：通过5.8G无线客户端连接其它WIFI网络的网关模式, 终端管理命令行中执行如下设置为此模式   
```shell
$ land@machine.mode[nwisp]          # 切换
ttrue
$ land@machine.restart              # 重启, 需要重启后生效
```   

**无线热点**：相当于带无线功能的交换机, 此模式下默认不会分配IP地址, 通常用于放置在路由器的下一级, 终端管理命令行中执行如下设置为此模式   
```shell
$ land@machine.mode[ap]          # 切换
ttrue
$ land@machine.restart           # 重启, 需要重启后生效
```   

**混合**：此模式下可使用4G/5G、有线WAN口、无线连网三种模式中组合上网, 实现多种上网方式同时存在并相互备份或负载均衡, 终端管理命令行中执行如下设置为此模式   
```shell
$ land@machine.mode[mix]          # 切换
ttrue
$ land@machine.restart            # 重启, 需要重启后生效
```   

## 常用的功能管理   

### 4G/5G联网设置   
- **连接普通的4G(LTE)网络**   
    1. 网关插上SIM卡后   
    2. 将设备的 **工作模式** 设置为 **4G网关**, 通常4G网关默认即为此模式    
    网关就会自动通过4G(LTE)连上互联网, 不需要任何设置, 将终端设备或电脑通过有线或无线连接网关即可访问互联网   
- **连接普通的5G(NR)网络**   
    1. 网关插上SIM卡后    
    2. 将设备的 **工作模式** 设置为 **4G/5G网关**, 通常5G网关默认即为此模式     
    网关就会自动通过5G(NR)连上互联网, 不需要任何设置, 将终端设备或电脑通过有线或无线连接网关即可访问互联网   
- **[4G/5G(LTE/NR)接入虚拟专用网络(VPDN/APN)](./lte/he_lte_apn_cn.md)** 介绍使用LTE/NR接入VPDN/APN网络   
- ***[4G/5G(LTE/NR)接入自建基站网络](./lte/lte_spec_cn.md)**(编写中)* 介绍使用LTE/NR接入自建基站网络   
- ***[4G/5G(LTE/NR)双SIM卡](./lte/lte_bsim_cn.md)**(编写中)* 介绍LTE/NR双卡的使用   
- ***[4G/5G(LTE/NR)短信功能](./lte/lte_sms_cn.md)**(编写中)* 介绍LTE/NR短信的使用   
- ***[锁定SIM卡](./lte/lte_lockimsi_cn.md)**(编写中)*, 锁定后更换SIM卡无法工作   
- ***[锁定4G/5G(LTE/NR)模组](./lte/lte_lockimei_cn.md)**(编写中)*, 锁定后更换4G/5G(LTE/NR)模组无法工作   
- ***[常用模块锁定频段](./lte/lte_lockband_cn.md)**(编写中)*   
- ***[自定义指定AT指令](./lte/lte_customat_cn.md)**(编写中)*   
- ***[AT指令网络透传使用](./lte/lte_atport_cn.md)**(编写中)*, 实现一个服务器或客户端透传来自网络的AT指令到4G/5G(LTE/NR)模组中   
- ***[4G/5G(LTE/NR)定位功能及使用](./lte/lte_gnss_cn.md)**(编写中)*   

### 有线宽带联网设置   
- ***[PPPOE拨号联网](./wan/wan_pppoe_cn.md)**(编写中)*   
- ***[自动获取(DHCP)联网](./wan/wan_dhcp_cn.md)**(编写中)*   
- ***[静态地址联网](./wan/wan_static_cn.md)**(编写中)*   
- ***[纯路由模式下有线宽带联网](./wan/wan_nonat_cn.md)**(编写中)*   

### 2.4G/5.8G无线连网设置   
- ***[无线连网自动获取(DHCP)使用](./wisp/wisp_dhcp_cn.md)**(编写中)*   
- ***[无线连网静态地址使用](./wisp/wisp_static_cn.md)**(编写中)*   
- ***[无线连网PPPOE拨号使用](./wisp/wisp_pppoe_cn.md)**(编写中)*   
- ***[纯路由模式下无线连网](./wisp/wisp_nonat_cn.md)**(编写中)*   

### 使用4G/5G, 有线宽带, 2.4G/5.8G无线连网多个连接同时联网   
- ***[双4G/5G网关模式的使用](./mix-mode/dmisp_cn.md)**(编写中)*, 实现双4G/5G同时联网, 双4G/5G间实现备份或是负载均衡   
- ***[双WAN口网关模式的使用](./mix-mode/dgateway.md)**(编写中)*, 实现双WAN口连接同时联网, 双WAN口连接间实现备份或是负载均衡   
- ***[混合模式的使用](./mix-mode/mix_cn.md)**(编写中)*, 混合模式下实现多种连接同时联网, 各种连接间实现备份或是负载均衡   

### 2.4G/5.8G无线热点工作模式   
- ***[无线热点模式使用](./ap/ap_cn.md)**(编写中)*   
- ***[无线热点模式下中继其它热点](./ap/repeater_cn.md)**(编写中)*   

### 4G5G猫(Modem)工作模式   
- ***[4G5G猫(Modem)模式使用](./ap/mbridge_cn.md)**(编写中)*   

### 本地网络设置   
- ***[本地网络地址设置](./lan/lan_ip_cn.md)**(编写中)*   
- ***[本地网络设置多个地址](./lan/lan_mip_cn.md)**(编写中)*   
- ***[本地网络分配地址段(DHCP服务器)设置](./lan/dhcps_cn.md)**(编写中)*   
- ***[为终端分配(绑定)指定的IP地址](./client/bind_ip_cn.md)**(编写中)*   

### 系统管理   
- ***[修改网关的名称](./system/name_cn.md)**(编写中)*   
- ***[重启网关](./system/reboot_cn.md)**(编写中)*   
- ***[重置网关配置(恢复出厂设置)](./system/reset_cn.md)**(编写中)*   
- ***[管理网关的时间及时区](./system/date_cn.md)**(编写中)*   
- ***[开启NTP服务为本地设备授时](./system/ntps_cn.md)**(编写中)*   
- ***[网关配置备份及导入](./system/configure_cn.md)**(编写中)*   
- ***[网关固件升级](./upgrade/upgrade_cn.md)**(编写中)*   
- ***[网关网页强制升级](./upgrade/boot_web_upgrade_cn.md)**(编写中)*   
- ***[网关TFTP强制升级](./upgrade/boot_tftp_upgrade_cn.md)**(编写中)*   
- ***[管理员密码修改](./system/password_cn.md)**(编写中)*   
- ***[设置网关定时重启](./system/restart_cn.md)**(编写中)*   
- ***[Telnet服务器](./system/telnetd_cn.md)**(编写中)*   
- ***[SSH服务器](./system/sshd_cn.md)**(编写中)*   
- ***[FTP服务器](./system/ftps_cn.md)**(编写中)*   
- ***[WEB服务器(管理界面)](./system/webs_cn.md)**(编写中)*   
- ***[LED指示灯管理](./system/led_cn.md)**(编写中)*   
- ***[Hosts文件配置](./system/hosts_cn.md)**(编写中)*      
- ***[锁定网关配置](./custom/lockconfig_cn.md)**(不公开防止误操作)*, 锁定配置后不再允许用户修改网关配置       
- ***[锁定升级](./custom/lockupdate_cn.md)**(不公开防止误操作)*, 锁定升级后不再允许用户升级网关              
- ***[锁定重启](./custom/lockreboot_cn.md)**(不公开防止误操作)*, 锁定重启后不再允许用户重启网关     

### 无线热点   
- ***[无线热点名称及密码信道等设置](./wifi/ssid_cn.md)**(编写中)*   
- ***[无线热点黑白名单设置](./wifi/acl_cn.md)**(编写中)*   
- ***[中继其它热点](./wifi/sta_cn.md)**(编写中)*   

### 防火墙  
- **防火墙** 用于控制 **通过外网口访问网关或内网终端** 的权限, 跟 **访问控制** 相反, **访问控制** 则用于控制 **内网终端访问外网** 的权限   
- ***[允许外网访问网关指定的服务](./firewall/allow_access_cn.md)**(编写中)*   

### 端口映射或代理   
- ***[端口映射使用说明](./portmap/portmap_cn.md)**(编写中)*   
- ***[端口代理使用说明](./portproxy/portproxy.md)**(编写中)*

### 终端访问控制及管理   
- **访问控制** 用于控制 **内网终端访问外网** 的权限, 跟 **防火墙** 相反, **防火墙** 则用于控制 **通过外网口访问网关或内网终端** 的权限   
- 通过 ***[限制终端访问](./acl/access_control_cn.md)**(编写中)* 实现对接入终端访问互联网的目的地或内容进行管控    
- 通过 ***[限制终端上网](./acl/internet_control_cn.md)**(编写中)*  实现对客户端访问互联网的权限或时间进行管控   
- 通过 ***[上网白名单设置](./acl/access_whitelist_cn.md)**(编写中)*  实现白名单式的管控   
- 通过 ***[上网黑名单设置](./acl/access_blacklist_cn.md)**(编写中)*  实现黑名单式的管控   
- 通过 ***[为访问及上网规则添加指定时间生效](./acl/control_timer_cn.md)**(编写中)* 实现设置的规则定时生效   
- ***[为终端自定义名称](./client/bind_name_cn.md)**(编写中)*   

### 路由功能   
- ***[路由表管理](./route/route.md)**(编写中)*      
- ***[基于源地址的路由设置](./route/src_route.md)**(编写中)*      
- ***[基于端口的路由设置](./route/port_route.md)**(编写中)*      

### 调试功能   
- ***[抓包使用说明](./debug/tcpdump_cn.md)**(编写中)*   
- ***[日志的使用](./hosts/hosts.md)**(编写中)*, 可调整日志存放位置, 记录等级, 保存大小, 远程日志等      
- ***[ping连通性测试](./debug/tcpdump_cn.md)**(编写中)*   
- ***[iperf打流带宽测试](./debug/tcpdump_cn.md)**(编写中)*      
- ***[有互联网的远程协助](./debug/internet_remote_cn.md)**(编写中)*, 用于让网关接入调试云平台, 技术人员可通过调试云平台连接网关      
- ***[无互联网的远程协助](./debug/nointernet_remote_cn.md)**(编写中)*, 用于让技术人员远程连接电脑调试网关      


## VPN功能使用   
- ***[设置两台网关Wireguard实现互通示例](./sdwan/wireguard_cn.md)**(编写中)*   
- ***[L2TP客户端的使用](./sdwan/wireguard.md)**(编写中)*   
- ***[PPTP客户端的使用](./sdwan/wireguard.md)**(编写中)*   
- ***[GRE隧道的使用](./sdwan/wireguard.md)**(编写中)*   
- ***[OpenVPN客户端的使用](./sdwan/wireguard.md)**(编写中)*   
- ***[IPSEC的使用](./sdwan/wireguard.md)**(编写中)*   


## 串口功能使用   
- ***[串口透传的使用](./uart/uart_tcp_cn.md)**(编写中)*   
- ***[串口MQTT透传](./uart/uart_mqtt_cn.md)**(编写中)*   
- ***[串口Modbus透传](./lte/lte_apn_setup.md)**(编写中)*   
- ***[串口HTTP透传](./lte/lte_apn_setup.md)**(编写中)*   
- ***[串口终端命令行模式](./lte/lte_apn_setup.md)**(编写中)*, 此模式下可实现通过串口控制并管理网关   
- ***[串口外接GPS/BD模块](./lte/lte_apn_setup.md)**(编写中)*, 此模式下让外接的GPS/BD模块提示定位数据源   
- ***[本地设备获取串口数据](./lte/lte_apn_setup.md)**(编写中)*   


## 串口外接Modbus传感器   
- ***[串口Modbus主控模式下外接各种传感器](./lte/lte_apn_setup.md)**(编写中)*   
- ***[传感器信息HTTP上报](./lte/lte_apn_setup.md)**(编写中)*   
- ***[本地设备获取感器信息](./lte/lte_apn_setup.md)**(编写中)*   


## IO功能使用   
- ***[通过TCP/UDP协议远程控制IO](./lte/lte_apn_setup.md)**(编写中)*   
- ***[通过MQTT协议远程控制IO](./lte/lte_apn_setup.md)**(编写中)*   
- ***[通过短信(SMS)远程控制IO](./lte/lte_apn_setup.md)**(编写中)*   
- ***[本地设备控制IO](./lte/lte_apn_setup.md)**(编写中)*   


## 定位功能使用   
- ***[全球定位的使用](./gnss/gnss_setup_cn.md)**(编写中)*   
- ***[GPS/BD定位数据(NMEA)TCP/UDP协议上报](./gnss/gnss_tcpudp_cn.md)**(编写中)*   
- ***[GPS/BD定位信息MQTT协议上报](./gnss/gnss_mqtt_cn.md)**(编写中)*   
- ***[GPS/BD定位信息HTTP协议上报](./gnss/gnss_http_cn.md)**(编写中)*   
- ***[GPS/BD定位信息JT/T808协议上报](./gnss/gnss_jt808_cn.md)**(编写中)*   
- ***[本地设备获取GPS/BD定位信息](./gnss/gnss_tcpjson_setup.md)**(编写中)*   


## I2C功能的使用   
- ***[外接I2C显示屏](./lte/lte_apn_setup.md)**(编写中)*   
- ***[外接I2C电量板实现读取电量信息](./lte/lte_apn_setup.md)**(编写中)*   
- ***[I2C电量板的电量信息HTTP协议上报](./lte/lte_apn_setup.md)**(编写中)*    
- ***[本地设备获取I2C电量板的电量信息](./lte/lte_apn_setup.md)**(编写中)*  


## 高级应用    
- ***[本地控制网关](./lte/lte_apn_setup.md)**(编写中)*   
- ***[网关通过HTTP上报状态](./lte/lte_apn_setup.md)**(编写中)*   
- ***[通过短信控制网关](./lte/lte_apn_setup.md)**(编写中)*   
- ***[SNMP的使用及自定义OID](./lte/lte_apn_setup.md)**(编写中)*   
- ***[动态路由协议使用](./lte/lte_apn_setup.md)**(编写中)*   
- ***[高可用性(VRRP)的使用](./lte/lte_apn_setup.md)**(编写中)*   



**(编写中)的功能都已实现, 使用文档暂未上传, 如有需要可资询技术人员上传**
