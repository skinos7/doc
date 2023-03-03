***
## Management of global access
Management of global local interface name client access

#### Configuration( client@global )

```json
// Attributes introduction 
{
    "interface name":       // [ "ifname@lan", "ifname@lan2", "ifname@lan3", ... ], above rules set at this interface name
    {
        // access internet privilege
        "internet":"disable or enable or regular internet access",  // [ "enable", "disable" ,"timer" ]
                                                                            // timer for regular internet access
                                                                            // disable for forbid internet access
                                                                            // enable for allow internet access
                                                                            // no settings for do nothing
        "internet_timer":                                           // regular internet access rule, valid when "internet" be "timer"
        {
            "rule name":                                                 // [ string ], user can custom the rule name, match this rule can acess
            {
                "source":"local source address",                         // [ string ]:
                                                                                  // single IP: 192.168.8.222
                                                                                  // multiple IP: 192.168.8.2,192.168.8.3,192.168.8.4
                                                                                  // range of IP: 192.168.8.2-192.168.8.4
                                                                                  // signal MAC: 00:23:43:13:34:40
                "datestart":"starting date",                             // [ string ], format is YYYY-MM-DD
                "datestop":"ending date",                                // [ string ], format is YYYY-MM-DD
                "timestart":"start time of day",                         // [ string ], format is hh-mm-ss
                "timestop":"end time of day",                            // [ string ], format is hh-mm-ss
                "weekdays":"designated week number"                      // [ string ], format is w1,w2,w3, 0 for Sunday
            }
            // more rule
        },

        // access control list
        "acl":"enable or disable",                                  // [ disable, enable ]
        "acl_rule":                                                 // access control list, valid when "acl" be "enable"
        {
            "rule name":                                                 // [ string ], user can custom the rule name
            {
                "action":"drop or accept or return",                     // [ drop, accept, return ], drop for forbid, accept for pass, return for don't match it with after rule
                "source":"local source address",                         // [ string ]:
                                                                                  // single IP: 192.168.8.222
                                                                                  // multiple IP: 192.168.8.2,192.168.8.3,192.168.8.4
                                                                                  // range of IP: 192.168.8.2-192.168.8.4
                                                                                  // signal MAC: 00:23:43:13:34:40
                "proto":"protocol type",                                 // [ domain, key, tcp, udp, all ]
                "dest":"internet destination address",                   // [ string ]:
                                                                                  // single IP: 202.96.11.32
                                                                                  // multiple IP: 2.3.1.2,4.34.2.1,72.32,192.1
                                                                                  // range of IP: 202.96.132.11-202.96.132.20
                                                                                  // domain: www.baidu.com
                                                                                  // key: baidu
                "destport":"internet destination port",                  // [ number ]: valid when "proto" be "tcp" or "udp"
                                                                                  // single port: 8080
                                                                                  // multiple port: 80,8000,8080
                                                                                  // range of port: 80-800
                "key":"keyword",                                         // [ string ], valid when "proto" be "tcp" or "udp" or "all"

                "datestart":"starting date",                             // [ string ], format is YYYY-MM-DD
                "datestop":"ending date",                                // [ string ], format is YYYY-MM-DD
                "timestart":"start time of day",                         // [ string ], format is hh-mm-ss
                "timestop":"end time of day",                            // [ string ], format is hh-mm-ss
                "weekdays":"designated week number"                      // [ string ], format is w1,w2,w3, 0 for Sunday
            }
            // more rule
        },

        // limit send packet rate
        "limit":"enable or disable",                                  // [ disable, enable ]
        "limit_rule":                                                 // limit send packet rate control list, valid when "limit" be "enable"
        {
            "rule name":                                                 // [ string ], user can custom the rule name
            {
                "source":"local source address",                         // [ string ]:
                                                                                  // single IP: 192.168.8.222
                                                                                  // multiple IP: 192.168.8.2,192.168.8.3,192.168.8.4
                                                                                  // range of IP: 192.168.8.2-192.168.8.4
                                                                                  // signal MAC: 00:23:43:13:34:40
                "dest":"internet destination address",                   // [ string ]:
                                                                                  // single IP: 202.96.11.32
                                                                                  // multiple IP: 2.3.1.2,4.34.2.1,72.32,192.1
                                                                                  // range of IP: 202.96.132.11-202.96.132.20
                "proto":"protocol type",                                 // [ tcp, udp, all ]                                
                "destport":"internet destination port",                  // [ number ]: valid when "proto" be "tcp" or "udp"
                                                                                  // single port: 8080
                                                                                  // multiple port: 80,8000,8080
                                                                                  // range of port: 80-800

                "limit":"Packets sent per second",                       // [ number ]
                "burst":"Burst packets per second"                       // [ number ]
            }
            // more rule
        },

        // limit send packet rate
        "filter":"disable or accept all packet or drop all packet",      // [ disable, accept, drop ]
        "filter_rule":                                                   // filter network bridge packet, valid when "filter" be "enable"
        {
            "rule name":                                                 // [ string ], user can custom the rule name
            {
                "action":"drop or accept",                               // [ drop, accept ], drop for forbid, accept for pass
                "source":"local source address",                         // [ string ], only support single IP
                "dest":"internet destination address",                   // [ string ], only support single IP

                "proto":"protocol type",                                 // [ tcp, udp, all ]                                
                "destport":"internet destination port"                   // [ number ], valid when "proto" be "tcp" or "udp", only support single port: 8080
            }
            // more rule
        }

    }
}
```



