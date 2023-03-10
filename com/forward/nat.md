***
## Management of NAT
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
Examples, enable the second LTE firewall
```shell
forward@nat
{
    "ifname@wan":
    {
        "mode":"dnat",                        // dnat mode
        "rule":
        {
            "rdesktop":                          // map the ifname@wan 3389 to 192.168.31.230 TCP 3389
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
            "ssh":
            {
                "targetport":"22",
                "protocol":"tcp",
                "destip":"192.168.31.230",
                "destport":""
            },
            "devport":
            {
                "targetport":"10101",
                "protocol":"tcp",
                "destip":"192.168.31.230",
                "destport":""
            }
        },
        "dmzhost":""
    }
    "ifname@lte2":
    {
        "dmzhost":""
    }
}

