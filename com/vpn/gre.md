***
## 管理GRE隧道（vxpxn@gre）--- ###文档中vxpxn与VxPxN是需要去掉x的, 之所以加x是防敏感词检查###
管理GRE隧道

#### **配置** 
```json
{
    "status":"disable",                 // <状态>，启用为enable, 禁用为disable

    "extern":"vxpxn@l2tpc",                   // <附着接口>, 指定附着的接口, 即在此接口上建隧道, 默认为默认出口, 在VxPxN上建隧道时必须要设置此值为VxPxN接口
    "peer":"www.vxpxnserver.com",             // <对端地址>

    "localip":"192.168.111.2",              // <隧道本地地址>
    "remoteip":"192.168.111.2",             // <隧道对端地址>
    "ttl":"255",                            // <TTL>

    "masq":"enable",                        // 是否<IP伪装>: disable为禁用, enable或为空表示启用
    "defaultroute":"disable",               // 是否添加<默认路由>, enable表示添加, 默认路由为disable时route_table生效
    "route_table":                           // 自定义上线时添加的路由, 默认路由(defaultroute)为disable有效
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
    },

    "custom_dns":"disable ",      // 自定义DNS主机地址, 值为enable表示忽略DHCP对端分配的DNS, 使用下面配置的DNS主机
    "dns":"202.96.134.133",       // 自定义DNS主机地址: 合法的IP地址或为空
    "dns2":"192.168.1.254",       // 自定义备用DNS主机地址: 合法的IP地址或为空

}

```


#### **接口** 

+ `setup[]` 启动GRE连接

>*修改成功返回ttrue, 修改失败返回tfalse*

+ `shut[]` 断开GRE连接

>*添加成功返回ttrue, 添加失败返回tfalse*

+ `device[]` 显示连接对应的网络设备

>*修改成功返回字符串, 修改失败返回tfalse*

+ `status[]` 显示连接的状态

>*成功返回如下JSON, 失败返回NULL*

```json
    {
        "status":"up",                        // up表示已连接, down表示未连接, uping表示连接中
        "ifname":"vxpxn/gre",
        "device":"gre1",                      // 网络接口
        "mode":"dhcpc",                       // 拨号模式, dhcpc为自动获取
        "ip":"10.99.4.192",                   // IP地址
        "mask":"255.255.255.128",             // 子网掩码
        "gw":"10.99.4.193",                   // 网关
        "dns":"211.136.17.107",               // DNS
        "dns2":"211.136.20.203",              // DNS
        "mac":"76:C7:8C:05:39:F3",            // MAC地址
        "rx_bytes":"6864",                    // 单次增量收包字节
        "rx_packets":"65",                    // 单次增量收包数
        "tx_bytes":"7296",                    // 单次增量发包字节
        "tx_packets":"74",                    // 单次增量发包数
        "livetime":"00:04:37:0",              // 在线时长 时:分:秒:天
        "keeplive":"244"                     // 链路时延, 单位为ms 
    }
```

