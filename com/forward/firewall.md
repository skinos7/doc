***
## Management of firewall
Management of firewall to control access from extern inteface( internet )

#### Configuration( forward@firewall )
```json
// Attributes introduction 
{
    "extern interface name":       // [ "ifname@lte", "ifname@lte2", "ifname@wan", ... ], above rules set at this interface name
    {
        "status":"disable or enable or firewall",           // [ "enable", "disable" ]
        "default":"action for default access",              // [ "drop", "accept" ]
        "input_icmp_through":"ICMP protocol access",        // [ "disable", "enable" ]
        "input_espah_through":"ESP/AH protocol access",     // [ "disable", "enable" ]
        "input_telnet_through":"telnet access",             // [ "disable", "enable" ]
        "input_ssh_through":"SSH access",                   // [ "disable", "enable" ]
        "input_wui_through":"WEB Server access",            // [ "disable", "enable" ]

        "nat_through":"NAT rule settings at forward@nat  passthrough auto",    // [ "disable", "enable" ]
        "forward_icmp_through":"ICMP protocol passthrough",                    // [ "disable", "enable" ]
        "forward_espah_through":"ESP/AH protocol passthrough",                 // [ "disable", "enable" ]

        "rule":                              // firewall rule settings
        {
            "rule name":                                   // [ string ], user can custom the rule name
            {
                "action":"drop or accept or return",                     // [ "drop", "accept", "return" ], "drop" for forbid, "accept" for pass, "return" for don't match it with after rule
                "src":"source address",                                  // [ string ]:
                                                                                  // single IP: 192.168.8.222
                                                                                  // multiple IP: 192.168.8.2,192.168.8.3,192.168.8.4
                                                                                  // range of IP: 192.168.8.2-192.168.8.4
                                                                                  // signal MAC: 00:23:43:13:34:40
                                                                                  // space for all ip address
                "protocol":"protocol type",                              // [ "tcp", "udp", "all" ]
                "dest":"destination address",                            // [ string ]:
                                                                                  // single IP: 202.96.11.32
                                                                                  // multiple IP: 2.3.1.2,4.34.2.1,72.32,192.1
                                                                                  // range of IP: 202.96.132.11-202.96.132.20
                                                                                  // space for all ip address

                "destport":"destination port"                           // [ number ]: valid when "proto" be "tcp" or "udp"
                                                                                  // single port: 8080
                                                                                  // multiple port: 80,8000,8080
                                                                                  // range of port: 80-800
                                                                                  // space for all port
            }
            // ... more rule
        }
    }
    // ... more extern interface
}
```  
Examples, show current all of firewall settings
```shell
forward@firewall
{
    "ifname@lte":                 // first LTE firewall settings
    {
        "status":"enable",             // enable the firewall
        "default":"drop",              // default action is drop
        "rule":
        {
            "pcweb":                        // rule named "pcweb", accept dest 192.168.8.222 and destport TCP 80 access
            {
                "action":"accept",
                "dest":"192.168.8.222",
                "protocol":"tcp",
                "destport":"80"
            }
        }
    },
    "ifname@lte2":              // second LTE firewall settings
    {
        "status":"disable",           // disable the firewall
        "default":"drop",
        "rule":
        {
        }
    }
}
```
Examples, enable the second LTE firewall
```shell
forward@firewall:ifname@lte2/status=enable
ttrue
```

