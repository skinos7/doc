***
## IPSEC客户端管理组件(ipsec@strongswan)
此组件为管理IPSEC:

#### **配置(ipsec@strongswan)** 
```json
{
    "status":"状态",                    // enable为启用IPSEC, disable及其它为禁用

    "ike_proposals":                    // IKE所有安全提议
    {
        "proposal":                            // IKE安全提议名称, 以字符或数字组成并以字符开头, 为自定义名称
        {
            "auth":"验证算法",                 // aesxcbc, md5, sha1, sha256, sha384, sha512
            "encrypt":"加密算法",              // des, 3des, aes128, aes192, aes256
            "dh":"DH组"                        // modp768, modp1024, modp1536, modp2048, modp3072, modp4096, modp8192
        }
        "proposal2":                           // IKE安全提议名称, 以字符或数字组成并以字符开头, 为自定义名称
        {
            /* 同以上 */
        }
        // ... 更多IKE安全提议
    },
    "ike":                              // IKE的所有策略
    {
        "policy":                       // IKE策略名称, 以字符或数字组成并以字符开头, 为自定义名称
        {
            "keyexchange":"IKE版本",        // 可为 ike, ikev1, ikev2
            "aggressive":"协商模式",        // yes为野蛮模式,  空或为no为主模式
            "localid_type":"本地ID类型",    // 为ip表示使用本地IP地址, name表示为自定义一个ID(为localid的值)
            "localid":"本地ID",             // localid_type为name时有效, 为自定义的本地ID
            "peerid_type":"对端ID类型",     // 为ip表示使用对端IP地址, any表示任意对端ID, name表示为自定义一个ID(为peerid的值)
            "peerid":"对端ID",              // peerid_type为name时有效, 为自定义的对端ID
            "proposal":"IKE安全提议",       // 为ike_proposals下的IKE安全提议名称
            "proposal2":"IKE安全提议",      // 为ike_proposals下的IKE安全提议名称
            "proposal3":"IKE安全提议",      // 为ike_proposals下的IKE安全提议名称
            "proposal4":"IKE安全提议",      // 为ike_proposals下的IKE安全提议名称
            "secret":"预共享密钥",
            "lifetime": "生存时间",         // 秒为单位, 可取值为60到604800之间, 默认值为3个小时
            "dpd":"DPD检测开启",            // none表示禁用, clear表示启用, hold, restart, 默认值为none
            "dpddelay":"DPD检测周期"        // 秒为单位, DPD检测开启(dpd)的值不为 none时，此项才有效，默认值为30秒
        },
        "policy2":                       // IKE策略名称, 以字符或数字组成并以字符开头, 为自定义名称
        {
            /* 同以上 */
        }
        // ... 更多IKE策略
    },

    "ipsec_proposals":                  // IPSec所有安全提议
    {
        "proposal":                            // IPSEC安全提议名称, 以字符或数字组成并以字符开头, 为自定义名称
        {
            "protocol":"安全协议",             // 值可为ah或esp
            "auth":"验证算法",                 // 当 protocol 为 ah 时可选 md5, sha1，当协议为esp时可选aesxcbc, md5, sha1
            "encrypt": "加密算法",             // 当 protocl 为esp时，此项才有效, 可选 des, 3des, aes128, aes192, aes256
            "dh": ""                           // 此项可以为空, 可选 modp768, modp1024, modp1536, modp2048, modp3072, modp4096, modp8192 暂时无法测试
        },
        "proposal2":                           // IPSEC安全提议名称, 以字符或数字组成并以字符开头, 为自定义名称
        {
            /* 同以上 */
        }
        // ... 更多IPSEC安全提议
    },
    "ipsec":                            // IPSec的所有策略
    {
        "policy":                       // IPSEC策略名称, 以字符或数字组成并以字符开头, 为自定义名称
        {
            "extern":"出口网口",            // 选取一个网络接口, 例如ifname@wan表示有线WAN, ifname@lte表示LTE
            "local":"本地接口",             // 默认为ifname@lan即本地网口

            "status":"状态",                  // ignore(禁用) / add / route / start(启用), 默认值为start
            "peer":"对端网关",              // 如: 120.78.216.87, 即IPSEC的对端地址
            "peersubnet":"对端子网范围",    // 如: 10.0.0.0/24, 即IPSEC对端的内网网段
            "localsubnet":"本地子网范围",   // 如: 192.168.2.0/24, 即本地内网网段, 默认可通过 本地接口(local) 获取
            "lifetime":"生存时间",          // 秒为单位, 范围为120到604800, 默认值为1小时
            "ike":"IKE策略",                // 值为 ike 下的 IKE策略名称
            "proposal":"IPSEC安全提议",     // 为ipsec_proposals下的IPSEC安全提议名称
            "proposal2":"IPSEC安全提议",    // 为ipsec_proposals下的IPSEC安全提议名称
            "proposal3":"IPSEC安全提议",    // 为ipsec_proposals下的IPSEC安全提议名称
            "proposal4":"ISEC安全提议"      // 为ipsec_proposals下的IPSEC安全提议名称
        },
        "policy2":                      // IPSEC策略名称, 以字符或数字组成并以字符开头, 为自定义名称
        {
            /* 同以上 */
        }
        // ... 更多IPSEC策略
    }
}

```


#### **接口** 

+ `setup[]` 启动IPSEC

>*修改成功返回ttrue, 修改失败返回tfalse*

+ `shut[]` 关闭IPSEC

>*添加成功返回ttrue, 添加失败返回tfalse*

+ `status[]` 显示IPSEC的状态

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

