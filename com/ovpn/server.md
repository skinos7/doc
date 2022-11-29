***
## Openvpn服务器管理组件
此组件为管理OpenVPN服务器

#### **配置(ovpn@server)**
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

    // 点对点服务器模式下的配置, p2p对点对点时有效
    "localip":"本地隧道地址",            // 点对点模式下有效
    "remoteip":"对端隧道地址",           // 点对点模式下有效

    // 网桥模式下配置, dev为tap时有效
    "bridgeip":"本地桥IP",
    "bridgemask":"本地桥掩码",
    "bridgestart":"分配给对端桥的启始地址",
    "bridgeend":"分配给对端桥的结束地址",

    // 子网服务器模式下的配置
    "tunnelip": "隧道子网",
    "tunnelmask": "隧道子网掩码",
    "tunneldns": "隧道子网DNS",
    "tunneldns2": "隧道子网DNS2",
    "client2client":"允放客户端相互访问", // enable为允许, disable为不允许
    "clientdup":"一个帐号多次连入"        // enable为允放, disable为不允许    
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

    "tunnelip": "10.0.0.0",            // 隧道子网为10.0.0.0
    "tunnelmask": "255.255.255.0",     // 隧道子网掩网为255.255.255.0
    "client2client":"enable",          // 允许客户端间互访
    "clientdup":"enable"               // 允许客户端重复连接
}

```


#### **接口**

+ `setup[]` 启动Openvpn服务器

>*成功返回ttrue, 失败返回tfalse*

+ `shut[]` 关闭Openvpn服务器

>*成功返回ttrue, 失败返回tfalse*

+ `status[]` 显示服务器的状态, 暂未实现

>*成功返回如下JSON, 失败返回NULL*

```json
    {
    }
```


#### **配置示例** 

```
    // 服务器配置例子
    dev tun
    port 1194
    proto udp
    ca ca.crt
    cert server.crt
    key server.key
    dh dh2048.pem
    server 10.8.0.0 255.255.255.0
    ifconfig-pool-persist ipp.txt
    keepalive 10 120
    cipher AES-256-CBC
    persist-key
    persist-tun
    script-security 2
    up /prj/openvpnd/up.sh

```


