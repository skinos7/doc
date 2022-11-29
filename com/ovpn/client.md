***
## OPENVPN客户端管理组件
此组件为管理OpenVPN客户端

#### **配置(openvpnc@vpn)** 

```json
// 属性介绍
{
    "status":"是否启用openvpn服务器",     // disable表示禁用, enable或为空表示启用
    "topology":"拓扑",                    // 拓扑结构，p2p为点对点, subnet为子网

    // 通用的openvpn配置
    "dev":"设备类型",                    // 接口类型, 分为tun与tap
    "proto":"协议",                      // 协议, 分为tcp或udp
    "port":"端口",                        // 默认为1194
    "cipher":"加密方式",                  // 可以为 DES-CFB, DES-CBC, RC2-CBC, RC2-CFB, RC2-OFB, DES-EDE-CBC, DES-EDE3-CBC, DES-OFB, 
                                          //        DES-EDE-CFB, DES-EDE3-CFB, DES-EDE-OFB, DES-EDE3-OFB, DESX-CBC, BF-CBC, BF-CFB, BF-OFB,
                                          //        CAST5-CBC, CAST5-CFB, CAST5-OFB, RC2-40-CBC, RC2-64-CBC, AES-128-CBC, AES-128-OFB,
                                          //        AES-128-CFB, AES-192-CBC, AES-192-OFB, AES-192-CFB, AES-256-CBC, AES-256-OFB, AES-256-CFB,
                                          //        AES-128-CFB1, AES-192-CFB1, AES-256-CFB1, AES-128-CFB8, AES-192-CFB8, AES-256-CFB8,
                                          //        DES-CFB1, DES-CFB8, DES-EDE3-CFB1, DES-EDE3-CFB8, SEED-CBC, SEED-OFB, SEED-CFB
    "comp_lzo":"压缩方式",                // disable表示禁用, yes表示启用, no表示不启用, adaptive表示自适应
    "interval":"保活包间隔",              // 秒为单位
    "timeout":"保活包超时时间",           // 秒为单位
    "options":"openvpn的其它选项",       // 多个选项以分号分隔
    "auth":"认证类型",                   // none为无, static为静态密钥, certificate为证书, username为用户密码
    "username":"用户名",                 // 认证类型为用户密码时有效
    "password":"密码",                   // 认证类型为用户密码时有效
    "hmac": "HMAC签名检查",              // disable为禁用, tls-auth为开启, 2.3版本不支持tls-crypt
    "peer":"服务器地址",                  // 可以为IP地址或域名

    // 路由相关, dev为tun时有效
    "masq":"IP伪装",                      // 启用为enable, 禁用为disable, 也叫IP共享, 即将所有从此连接出的数据的源地址通过NAT转换为本连接的地址
    "defaultroute":"默认路由",             // 是否将此连接设置为默认出口, enable为是, disable为否, disable时route_table生效
    "route_table":                        // 自定义上线时添加以下路由到此连接, 默认路由(defaultroute)为disable有效
    {
        "route1":                           // 路由项名称
        {
            "target":"目标地址",            // 可以为一个网段或一个IP地址
            "mask":"目标地址掩码",
        },
        "route2":                           // 路由项2名称
        {
            "target":"目标地址",            // 可以为一个网段或一个IP地址
            "mask":"目标地址掩码",
        }
        // ...更多路由项
    }
    "custom_dns":"disable ",         // 自定义DNS主机地址, 值为enable表示忽略对端分配的DNS, 使用下面配置的DNS主机
    "dns":"202.96.134.133",          // 自定义DNS主机地址: 合法的IP地址或为空
    "dns2":"192.168.1.254",          // 自定义备用DNS主机地址: 合法的IP地址或为空

    // 点对点客户端模式下配置, topology为p2p
    "localip":"本地隧道地址",            // 点对点模式下有效
    "remoteip":"对端隧道地址"           // 点对点模式下有效

    // 子网客户端模式下配置, topology为subnet
    // 暂无

}
// 示例
{
    "status":"enable",                 // 启用
    "topology":"subnet",               // 拓扑结构为子网
    "dev":"tun",                       // 接口类型为tun
    "proto":"udp",                     // 协议使用udp
    "port":"1194",                     // 端口为1194
    "comp_lzo":"disable",              // 禁用lzo压缩
    "interval":"10",                   // 保活包间隔为10秒
    "timeout":"120",                   // 保活包超时时间为120秒
    "auth":"certificate",              // 使用证书认证
    "hmac": "disable",                 // 禁用HMAC签名检查
    "peer":"dimmalex.wicp.net",        // 服务器地址为dimmalex.wicp.net

    "masq":"enable",                   // 开启IP伪装
    "defaultroute":"disable",           // 不将此连接设置为默认路由
    "route_table":
    {
        "route1":                           // 将目的地址为10.1.1.0/24网段的数据路由到此连接
        {
            "target":"10.1.1.0",
            "mask":"255.255.255.0"
        },
        "route2":                           // 将目的地址为10.1.2.0/24网段的数据路由到此连接
        {
            "target":"10.1.2.0",
            "mask":"255.255.255.0"
        }
    }
}

```


#### **接口** 

+ `setup[]` 启动Openvpn客户端连接

>*修改成功返回ttrue, 修改失败返回tfalse*

+ `shut[]` 断开Openvpn客户端连接

>*添加成功返回ttrue, 添加失败返回tfalse*

+ `device[]` 显示连接对应的网络设备

>*修改成功返回字符串, 修改失败返回NULL*

+ `clear_ca[]` 清除CA证书

>*成功返回ttrue, 失败返回tfalse*

+ `clear_cert[]` 清除Openvpn客户端证书

>*成功返回ttrue, 失败返回tfalse*

+ `clear_key[]` 清除Openvpn客户端密钥

>*成功返回ttrue, 失败返回tfalse*

+ `clear_tlskey[]` 清除TLS认证密钥

>*成功返回ttrue, 失败返回tfalse*

+ `clear_statickey[]` 清除静态密钥

>*成功返回ttrue, 失败返回tfalse*

+ `list_key[]` 列出Openvpn客户端所有的证书及密钥

>*成功返回如下JSON, 失败返回NULL*

```json
    {
        "cacrt":"/etc/.cfg/openvpnc/vpn.cacrt",         // CA证书位置 
        "crt":"/etc/.cfg/openvpnc/vpn.crt",             // 客户端证书
        "key":"/etc/.cfg/openvpnc/vpn.key",             // 客户端密钥
        "statickey":"/etc/.cfg/openvpnc/vpn.statickey", // 静态密钥
        "tlskey":"/etc/.cfg/openvpnc/vpn.tlskey"        // TLS认证密钥
    }
```

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
        "livetime":"00:04:37:0"              // 在线时长 时:分:秒:天
    }
```


#### **配置示例** 

```
    // 客户端配置例子
    client
    dev tun
    proto udp
    remote 1.0.0.8 1194
    resolv-retry infinite
    nobind
    persist-key
    persist-tun
    ca ca.crt
    cert client.crt
    key client.key
    cipher AES-256-CBC
    script-security 2
    up /prj/openvpnd/up.sh
```


