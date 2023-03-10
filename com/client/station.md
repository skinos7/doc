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
            "rule name":                                                 // [ string ], user can custom the rule name
            {
                "datestart":"starting date",                             // [ string ], format is YYYY-MM-DD
                "datestop":"ending date",                                // [ string ], format is YYYY-MM-DD
                "timestart":"start time of day",                         // [ string ], format is hh-mm-ss
                "timestop":"end time of day",                            // [ string ], format is hh-mm-ss
                "weekdays":"designated week number"                      // [ string ], format is 1,2,3,..., 0 for Sunday
            }
            // more rule
        },

        // access control list
        "acl":"enable or disable access control list",                   // [ "disable", "enable" ]
        "acl_rule":                                                 // access control list, valid when "acl" be "enable"
        {
            "rule name":                                                 // [ string ], user can custom the rule name
            {
                "action":"drop or accetp or return",                     // [ "drop", "accept", "return" ], "drop" for forbid, "accept" for pass, "return" for don't match it with after rule
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
            // more rule
        },

        // bandwidth control
        "tc":"enable or disable bandwidth control",                  // [ "disable", "enable" ]
        "tc_set":                                                    // bandwidth control settings, valid when "tc" be "enable"
        {
            "uprate":"upload rate limit",                            // [ number ], the unit is mbit
            "downrate":"download rate limit"                         // [ number ], the unit is mbit
        }
    }
    // more mac rule
}
``` 


#### **Methods**

+ `list[]` **list all client infomation**, *succeed return talk to describes infomation, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "client mac address":               // [ MAC address ]
        {
            "ip":"ip address",                  // [ IP address ]
            "ifname":"connected ifname",        // [ "ifname@lan", "ifname@lan2", ... ]
            "name":"client name",               // [ string ]
            "tx_bytes":"bytes of send",         // [ number ]
            "rx_bytes":"bytes recvice",         // [ number ]
            "livetime":"connected time",        // [ string ], format is hour:minute:second:day
        }
        // ... more client
    }
    ```
    ```shell
    # examples, list all client
    client@station.list
    {
        "04:CF:8C:39:91:7A":            # first client
        {
            "ip":"192.168.31.140",
            "name":"xiaomi-aircondition-ma2_mibt917A",
            "tx_bytes":"1779693",
            "rx_bytes":"1375610",
            "livetime":"14:39:34:1"
        },
        "40:31:3C:B5:6D:4C":            # second client
        {
            "ip":"192.168.31.61",
            "name":"minij-washer-v5_mibt6D4C",
            "livetime":"14:39:26:1"
        },
        "14:13:46:C9:97:C7":            # third client
        {
            "ip":"192.168.31.9",
            "name":"",
            "livetime":"14:39:27:1"
        }
    }
    ```





