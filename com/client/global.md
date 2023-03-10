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
                                                                            // "timer" for regular internet access
                                                                            // "disable" for forbid internet access
                                                                            // "enable" for allow internet access
                                                                            // space for no settings
        "internet_timer":                                           // regular internet access rule, valid when "internet" be "timer"
        {
            "rule name":                                                 // [ string ], user can custom the rule name, match this rule can access internet
            {
                "source":"local source address",                         // [ string ]:
                                                                                  // single IP: 192.168.8.222
                                                                                  // multiple IP: 192.168.8.2,192.168.8.3,192.168.8.4
                                                                                  // range of IP: 192.168.8.2-192.168.8.4
                                                                                  // signal MAC: 00:23:43:13:34:40
                                                                                  // space for all ip address
                "datestart":"starting date",                             // [ string ], format is YYYY-MM-DD
                "datestop":"ending date",                                // [ string ], format is YYYY-MM-DD
                "timestart":"start time of day",                         // [ string ], format is hh-mm-ss
                "timestop":"end time of day",                            // [ string ], format is hh-mm-ss
                "weekdays":"designated week number"                      // [ string ], format is w1,w2,w3, 0 for Sunday
            }
            // ... more rule
        },

        // access control list
        "acl":"enable or disable the access control list",          // [ "disable", "enable" ]
        "acl_rule":                                                 // access control list, valid when "acl" be "enable"
        {
            "rule name":                                                 // [ string ], user can custom the rule name
            {
                "action":"drop or accept or return",                     // [ "drop", "accept", "return" ], "drop" for forbid, "accept" for pass, "return" for don't match it with after rule
                "source":"local source address",                         // [ string ]:
                                                                                  // single IP: 192.168.8.222
                                                                                  // multiple IP: 192.168.8.2,192.168.8.3,192.168.8.4
                                                                                  // range of IP: 192.168.8.2-192.168.8.4
                                                                                  // signal MAC: 00:23:43:13:34:40
                                                                                  // space for all ip address
                "proto":"protocol type",                                 // [ "domain", "key", "tcp", "udp", "all", "layer7" ]
                "dest":"internet destination address",                   // [ string ]:
                                                                                  // single IP: 202.96.11.32, vaild when "proto" be "tcp" or "udp" or "all"
                                                                                  // multiple IP: 2.3.1.2,4.34.2.1,72.32,192.1, vaild when "proto" be "tcp" or "udp" or "all"
                                                                                  // range of IP: 202.96.132.11-202.96.132.20, vaild when "proto" be "tcp" or "udp" or "all"
                                                                                  // space for all ip address, vaild when "proto" be "tcp" or "udp" or "all"
                                                                                  // domain: www.baidu.com, vaild when "proto" be "domain"
                                                                                  // key: baidu, vaild when "proto" be "key"
                                                                                  // layer7: Future expansion, vaild when "proto" be "layer7"

                "destport":"internet destination port",                  // [ number ]: valid when "proto" be "tcp" or "udp"
                                                                                  // single port: 8080
                                                                                  // multiple port: 80,8000,8080
                                                                                  // range of port: 80-800
                                                                                  // space for all port
                "key":"keyword",                                         // [ string ], valid when "proto" be "tcp" or "udp" or "all"

                "datestart":"starting date",                             // [ string ], format is YYYY-MM-DD
                "datestop":"ending date",                                // [ string ], format is YYYY-MM-DD
                "timestart":"start time of day",                         // [ string ], format is hh-mm-ss
                "timestop":"end time of day",                            // [ string ], format is hh-mm-ss
                "weekdays":"designated week number"                      // [ string ], format is 1,2,3,..., 0 for Sunday
            }
            // ... more rule
        },

        // limit send packet rate
        "limit":"enable or disable limit packet send rate",         // [ "disable", "enable" ]
        "limit_rule":                                               // limit send packet rate control list, valid when "limit" be "enable"
        {
            "rule name":                                                 // [ string ], user can custom the rule name
            {
                "source":"local source address",                         // [ string ]:
                                                                                  // single IP: 192.168.8.222
                                                                                  // multiple IP: 192.168.8.2,192.168.8.3,192.168.8.4
                                                                                  // range of IP: 192.168.8.2-192.168.8.4
                                                                                  // signal MAC: 00:23:43:13:34:40
                                                                                  // space for all ip address
                "dest":"internet destination address",                   // [ string ]:
                                                                                  // single IP: 202.96.11.32
                                                                                  // multiple IP: 2.3.1.2,4.34.2.1,72.32,192.1
                                                                                  // range of IP: 202.96.132.11-202.96.132.20
                                                                                  // space for all ip address
                "proto":"protocol type",                                 // [ "tcp", "udp", "all" ]
                "destport":"internet destination port",                  // [ number ]: valid when "proto" be "tcp" or "udp"
                                                                                  // single port: 8080
                                                                                  // multiple port: 80,8000,8080
                                                                                  // range of port: 80-800
                                                                                  // space for all port

                "limit":"packets sent per second",                       // [ number ]
                "burst":"burst packets per second"                       // [ number ]
            }
            // ... more rule
        },

        // filter function on ifname
        "filter":"functions state",                                // [ "disable", "accept", "drop" ], "disable" for disable the function, "accept" for accept all packet defualt, "drop" for drop all packet default
        "filter_rule":                                             // filter network bridge packet, valid when "filter" be "accept" or "drop"
        {
            "rule name":                                                 // [ string ], user can custom the rule name
            {
                "action":"drop or accept",                               // [ "drop", "accept" ], "drop" for forbid, "accept" for pass
                "source":"local source address",                         // [ ip address ], only support single IP
                "dest":"internet destination address",                   // [ ip address ], only support single IP
                "proto":"protocol type",                                 // [ "tcp", "udp", "all" ]                                
                "destport":"internet destination port"                   // [ number ], valid when "proto" be "tcp" or "udp", only support single port: 8080
            }
            // ... more rule
        }

    }
}
```
Examples, show current all of global settings
```shell
client@global
{
    "ifname@lan":
    {
        "internet":"timer",                   // timer to access internet
        "internet_timer":
        {
            "date":                                // all client during 05:30 to 23:59:59 can access internet
            {
                "source":"",
                "datestart":"",
                "datestop":"",
                "timestart":"05:30:00",
                "timestop":"23:59:59",
                "weekdays":"1,2,3,4,5,6,7"
            },
            "night":                              // all client during 00:00 to 03:59:59 can access internet
            {
                "source":"",
                "datestart":"",
                "datestop":"",
                "timestart":"00:00:00",
                "timestop":"03:59:59",
                "weekdays":"1,2,3,4,5,6,7"
            }
        },
        "acl":"enable",                      // enable access control list
        "acl_rule":
        {
            "dis163":                             // all client cannot access domain www.163.com at all time
            {
                "source":"",
                "proto":"domain",
                "action":"drop",
                "dest":"www.163.com",
                "destport":"",
                "datestart":"",
                "datestop":"",
                "timestart":"00:00:00",
                "timestop":"23:59:59",
                "weekdays":"1,2,3,4,5,6,7"
            }
        }
    }
}        
```
Examples, add a acl rule named "disqq"
```shell
client@global:ifname@lan/acl_rule/disqq={"proto":"domain","dest":"www.qq.com","action":"drop"}
ttrue
```
Examples, delete a acl rule named "disqq"
```shell
client@global:ifname@lan/acl_rule/disqq=
ttrue
```


