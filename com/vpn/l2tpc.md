***
## L2TP客户端管理组件（vpn@l2tpc） 
此组件为管理L2TP客户端:

#### **配置(ifname@l2tpc)** 
```json
{
    "status":"disable",// 是否启用L2TP客户端, disable表示禁用, enable或为空表示启用
    "server":"www.vpnserver.com",           // 对端<服务器地址>
    "port":"1701",                         // 对端<端口>
    "masq":"enable",                      // 是否<IP伪装>: 启用为enable, 禁用为disable
    "username":"XXXX",                    // <L2TP用户名>
    "password":"xxxx",                    // <L2TP密码>
    "authmode":"chap",                    // 认证模式, simple, chap, disable
    "secret":"112232",                    // 密钥
    "ppp":                   // 拨号模式为PPP时有关ppp的详细设置
    {
        "username":"XXXX",                    // <PPP用户名>
        "password":"xxxx",                    // <PPP密码>
        "lcp_echo_interval":"10",        // PPP的LCP心跳包的间隔, 以秒为单位
        "lcp_echo_failure":"12",         // PPP的LCP心跳包的最大失败次数, 通俗的说就是当心跳包在发这么多次后无回应就认为链路不可用
        "mtu":"1492",                     // 属于高级选项, PPP的最大传输单元(MTU)大小
        "mss":"1412",                     // 属于高级选项, PPP的最大分段(MSS)大小
        "custom_dns":"disable ",         // 自定义DNS主机地址, 值为enable表示忽略对端分配的DNS, 使用下面配置的DNS主机
        "dns":"202.96.134.133",          // 自定义DNS主机地址: 合法的IP地址或为空
        "dns2":"192.168.1.254",          // 自定义备用DNS主机地址: 合法的IP地址或为空
        "custom_ip":"enable|disable",      // 属于高级选项, 自定义PPP本对端地址, 值为enable表示使用下面配置的本对端地址
        "localip":"192.168.22.120",        // 属于高级选项, 本端地址, custom_ip为enable时有效
        "remoteip":"192.168.22.1",         // 属性高级选项, 对端地址, custom_ip为enable时有效
        "pppopt":"debug;mppe",             // 属于高级选项, PPP的选项, 多选项时以分号(;)分隔
        "txqueuelen":"1000"           // 发送队列
    },
    "defaultroute":"enable",                // 是否添加<默认路由>, 默认路由为disable时route_table生效
    "route_table":                        // 自定义上线时添加的路由, 默认路由(defaultroute)为disable有效
    {
        "route1":                           // 路由项名称
        {
            "target":"1.1.1.0",            // 目标地址
            "mask":"255.255.255.0",       // 目标地址掩码
        },
        "route2":                           // 路由项名称
        {
            "target":"1.1.1.0",                   // 目标地址
            "mask":"255.255.255.0",       // 目标地址掩码
        }
    }
}

```


#### **接口** 

+ `setup[]` 启动L2TP客户端连接

>*修改成功返回ttrue, 修改失败返回tfalse*

+ `shut[]` 断开L2TP客户端连接

>*添加成功返回ttrue, 添加失败返回tfalse*

+ `device[]` 显示连接对应的网络设备

>*修改成功返回字符串, 修改失败返回tfalse*

+ `status[]` 显示连接的状态

>*成功返回如下JSON, 失败返回NULL*

```json
    {
        "status":"up",                        // up表示已连接, down表示未连接, uping表示连接中
        "ip":"10.99.4.192",                   // IP地址
        "dstip":"192.168.100.1",              // <对端IP地址>
        "mask":"255.255.255.128",             // 子网掩码
        "gw":"10.99.4.193",                   // 网关
        "dns":"211.136.17.107",               // DNS
        "dns2":"211.136.20.203",              // DNS
        "mac":"76:C7:8C:05:39:F3",            // MAC地址
        "rx_bytes":"6864",                    // 收包字节
        "rx_packets":"65",                    // 收包数
        "tx_bytes":"7296",                    // 发包字节
        "tx_packets":"74",                    // 发包数
        "livetime":"00:04:37:0",              // 在线时长 时:分:秒:天
        "keeplive":"244",                     // 链路时延, 单位为ms, 只有开启ICMP链接监测才有此项信息
    }
```

