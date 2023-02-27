***
## Management of client access
Management of specified client access

#### Configuration( client@station )

```json
// Attributes introduction 
{
    "client MAC address":                  // [ MAC address ]
    {
        "ifname":"specify on interface name",                 // [ string ], defdault the ifname@lan
        "name":"specify hostname",                            // [ string ]
        "bindip":"specify ip address on dhcp assignment",     // [ string ]
        "lease":"specify lease on dhcp assignment",           // [ number ]

        // access internet privilege
        "internet":"disable or enable or regular internet access",  // [ "enable", "disable", "timer" ], timer for regular internet access
        "internet_timer":                                           // regular internet access rule, valid when "internet" be "timer"
        {
            "rule name",                                                 // [ string ], user can custom the rule name
            {
                "datestart":"starting date",                             // [ string ], format is YYYY-MM-DD
                "datestop":"ending date",                                // [ string ], format is YYYY-MM-DD
                "timestart":"start time of day",                         // [ string ], format is hh-mm-ss
                "timestop":"end time of day",                            // [ string ], format is hh-mm-ss
                "weekdays":"designated week number"                      // [ string ], format is w1,w2,w3, 0 for Sunday
            }
            // more rule
        },

        // access control list
        "acl":"enable or disable access control list",                   // [ "disable", "enable" ]
        "acl_rule":                                                 // access control list, valid when "acl" be "enable"
        {
            "rule name",                                                 // [ string ], user can custom the rule name
            {
                "action":"drop or accetp or return",                     // [ drop, accept, return ], drop for forbid, accept for pass, return for don't match it with after rule
                "type":"rule type",                                      // [ ip, dns, key, app ], ip for internet ip/port, dns for domain, key for keyword, app for applications
                "proto":"protocol type",                                 // [ tcp, udp, all ], valid when "type" be "ip"
                "dest":"internet destination address",                   // [ string ]:
                                                                                  // single IP: 202.96.11.32
                                                                                  // multiple IP: 2.3.1.2,4.34.2.1,72.32,192.1
                                                                                  // range of IP: 202.96.132.11-202.96.132.20
                                                                                  // domain: www.baidu.com
                                                                                  // key: huawei
                "datestart":"starting date",                             // [ string ], format is YYYY-MM-DD
                "datestop":"ending date",                                // [ string ], format is YYYY-MM-DD
                "timestart":"start time of day",                         // [ string ], format is hh-mm-ss
                "timestop":"end time of day",                            // [ string ], format is hh-mm-ss
                "weekdays":"designated week number"                      // [ string ], format is w1,w2,w3, 0 for Sunday
            }
            // more rule
        }

        // bandwidth control
        "tc":"enable or disable bandwidth control",                  // [ disable, enable ]
        "tc_set":                                                    // bandwidth control settings, valid when "tc" be "enable"
        {
            "uprate":"upload rate limit",                            // [ number ], the unit is mbit
            "downrate":"download rate limit"                         // [ number ], the unit is mbit
        }
    }
    // more mac rule
}

``` 


#### **接口** 

+ `list[]` 列出所有客户端 

>*成功返回如下JSON, 失败返回NULL* 

```json
    {
        // 属性介绍
        "客户端MAC地址":
        {
            "ip":"IP地址",
            "device":"接入的网络设备",
            "ifname":"接入的网络接口",
            "ontime":"上线时系统的运行时长",      // 秒为单位
            "name":"客户端名称",
            "tx_bytes":"发送字节数",
            "rx_bytes":"接收字节数",
            "livetime":"在线时间"                // 时:分:秒:天
        }
        "客户端2MAC地址":
        {
            ...
        },
        ...                  // 更多其它客户端
        
        // 示例
        "04:CF:8C:39:91:7A":
        {
            "ip":"192.168.31.140",
            "device":"lan",
            "ifname":"ifname@lan",
            "ontime":"51",
            "name":"xiaomi-aircondition-ma2_mibt917A",
            "tx_bytes":"1779693",
            "rx_bytes":"1375610",
            "livetime":"14:39:34:1"
        },
        "40:31:3C:B5:6D:4C":
        {
            "ip":"192.168.31.61",
            "device":"lan",
            "ifname":"ifname@lan",
            "ontime":"59",
            "name":"minij-washer-v5_mibt6D4C",
            "tx_bytes":"1732003",
            "rx_bytes":"1333341",
            "livetime":"14:39:26:1"
        },
        "14:13:46:C9:97:C7":
        {
            "ip":"192.168.31.9",
            "device":"lan",
            "ifname":"ifname@lan",
            "ontime":"58",
            "name":"Skybox-Q1001-fbc6317cebd73798",
            "tx_bytes":"183198837",
            "rx_bytes":"259955379",
            "livetime":"14:39:27:1"
        }
    }
```





