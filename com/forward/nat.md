***
## Management of System NAT/DMZ
Management of NAT to PORT map from extern inteface to local network client

#### Configuration( forward@nat )   
```json
// Attributes introduction 
{
    "extern interface name":       // [ "ifname@lte", "ifname@lte2", "ifname@wan", ... ], above rules set at this interface name
    {
        "mode":"NAT mode",               // [ "forward", "dnat" ], "forward" for bi-directional NAT, "dnat" for dest NAT
        "dmzhost":"DMZ host ip address", // [ ip address ]
        "rule":                          // nat rule settings
        {
            "rule name":                     // [ string ]:{}
            {
                "targetport":"target port",     // [ number ], the extern interface port
                                                        // single port: 8080
                                                        // multiple port: 80,8000,8080
                                                        // range of port: 80-800
                "protocol":"protocol type",     // [ "tcp", "udp", "tcpudp" ], "tcpudp" for TCP and UDP
                "destip":"destination address", // [ ip address ], the local network ip address
                "destport":"destination port"   // [ number ]
                                                        // single port: 8080
                                                        // multiple port: 80,8000,8080
                                                        // range of port: 80-800
            }
            // ... more rule
        }
    }
    // ... more extern interface name
}
```  

Examples, show all nat settings
```shell
forward@nat
{
    "ifname@wan":
    {
        "mode":"dnat",                        # dnat mode
        "rule":
        {
            "rdesktop":                       # map the ifname@wan 3389 to 192.168.31.230 TCP 3389
            {
                "targetport":"3389",
                "protocol":"tcp",
                "destip":"192.168.31.250",
                "destport":""
            }
        }
    },
    "ifname@lte":
    {
        "rule":
        {
            "ssh":                           # map the ifname@lte 22 to 192.168.31.230 22
            {
                "targetport":"22",
                "protocol":"tcp",
                "destip":"192.168.31.230",
                "destport":""
            },
            "devport":
            {
                "targetport":"10101",       # map the ifname@lte 10101 to 192.168.31.230
                "protocol":"tcp",
                "destip":"192.168.31.230",
                "destport":""
            }
        },
        "dmzhost":""
    },
    "ifname@lte2":
    {
        "dmzhost":"192.168.31.250"          # map the ifname@lte2 all protocol to 192.168.31.230
    }
}
```

Examples, add a nat rule named telnet that make ifname@lte tcp port 23 map to 23 of 192.168.31.230
```shell
forward@nat:ifname@lte/rule/telnet={"targetport":"23","protocol":"tcp","destip":"192.168.31.230","destport":"23"}
ttrue
```

Examples, add a nat rule named web that make ifname@wan tcp port 80 map to 8080 of 192.168.31.231
```shell
forward@nat:ifname@wan/rule/web={"targetport":"80","protocol":"tcp","destip":"192.168.31.231","destport":"8080"}
ttrue
```

Examples, delete the rule named web at the ifname@wan
```shell
fforward@nat:ifname@wan/rule/web=
ttrue
```

Examples, delete the rule named telnet at the ifname@lte
```shell
fforward@nat:ifname@lte/rule/telnet=
ttrue
```

Examples, modify the ifname@lte dmz host to 192.168.31.250
```shell
forward@nat:ifname@wlte/dmzhost=192.168.31.250
ttrue
```

Examples, clear the ifname@lte dmz host
```shell
forward@nat:ifname@wlte/dmzhost=
ttrue
```
