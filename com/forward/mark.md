***
## Mark the packet（forward@mark） 
mark the packet with a mark id

#### Configuration( forward@mark )

```json
// Attributes introduction
{
    "rule name ":                                                      // [ string ]
    {
        "markid":"mark the packet with this id",                       // [ 1-4294967295 ]
                                                                            // Less than 100 is reserved for the system
                                                                            // You are advised to use more than 100 for user-defined rules
        "src":"select the packet use source ip address",               // [ ip address ]
        "src":"select the packet use destination ip address",          // [ ip address ]
        "protocol":"protocol type",                                    // [ all, tcp, udp, tcpudp ], all for all protocol, tcpudp for tcp and udp        
        "srcport":"source port",                                       // [ port ], default is all source port
        "destport":"destination port"                                  // [ port ], default is all destination port
    }
    // ... more rule
}
```

Examples, show current all of mark rule
```shell
{
    
    "myCustom1":                       # rule name is myCustom1
    {                                  # mark that source address is 192.168.8.250 and destination address is 202.94.22.38 packet 300
        "markid":"300",
        "src":"192.168.8.250",
        "dest":"202.94.22.38"
    },
    "youCustom":                       # rule name is youCustom
    {                                  # mark that source address is 192.168.8.251 and tcp protocol source port is 1000-2000 and destination port is 80/8080 packet 301
        "markid":"301",               // 标记ID为102
        "src":"192.168.8.251",        // 源地址为192.168.8.251
        "protocol":"tcp",             // 协议为TCP
        "srcport":"1000-2000"         // 源端口为1000至2000之间
        "destport":"80,8080"          // 目的端口为80及8080
    }
}
```  
