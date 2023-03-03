***
## filter network bridge packet
filter the packet on local network bridge

#### Configuration( client@filter )
```json
{
    "interface name":       // [ "ifname@lan", "ifname@lan2", "ifname@lan3", ... ], the ifname must be network birdge, above filter rules set at this interface name
    {
        "status":"filter function state",        // [ "disable", "enable" ]
        "default":"default action for packet",   // [ "drop", "accept" ]

        // custom filter rule in rule json
        "rule":
        {
            "rule name ":                      // [ string ]
            {
                "action":"drop or accetp or return",      // [ drop, accept, return ], drop for forbid, accept for pass, return for don't match it with after rule
                "src":"source address":                   // [ ip/mac address ]:
                                                                // space for all ip address
                                                                // single IP: 202.96.11.32
                                                                // mac: 00:03:7F:23:b3:40
                "protocol":"packet protocol",            // [ "tcp", "udp", "all" ]
                "dest":"dest address",                   // [ ip/mac address ]
                                                                // space for all ip address
                                                                // single IP: 202.96.11.32
                                                                // mac: 00:03:7F:23:b3:40
                "destport":"dest port"                   // [ port ]:
                                                                // space for all port
                                                                // single port: 8000
            }
            // more rule
        }
    }
    // more local interfade name
}
```  
Examples, show all the configure
```shell
client@filter
{
    "ifname@lan":                             // ifname@lan bridge filter settings
    {
        "status":"enable",                        // filter function is enable
        "rule":                                   // filter rule list
        {
            "xradar":                                 // filter rule name is xradar, source ip address is 192.168.0.200 will be drop
            {
                "src":"192.168.0.200",
                "action":"drop"
            },
            "xradar2":                                // filter rule name is xradar2, source ip address is 192.168.2.200 will be drop
            {
                "src":"192.168.2.200",
                "action":"drop"
            },
            "xcan":                                   // filter rule name is xcan, dest ip address is 192.168.4.200 will be drop
            {
                "dest":"192.168.4.200",
                "action":"drop"
            }
        }
    }
}
```  
Examples, disable the filter function of ifname@lan
```shell
client@filter:ifname@lan/status=disable
ttrue
```  


