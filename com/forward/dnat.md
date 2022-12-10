***
## Management of destination NAT
Management of destination NAT to proxy internet port for local network client

#### Configuration( forward@dnat )

```json
// Attributes introduction 
{
    "rule name":                     // [ string ]
    {
        "destip":"internet server ip address",         // [ ip address ]
        "destport":"internet server port",             // [ port ], supoprt single port and range of port(ex. 80-100)
        "protocol":"protocol type",                    // [ tcp, udp, tcpudp ], tcpudp for tcp and udp
        "targetport":"local proxy port"                // [ port ]
    }

}
```

Examples, show current all of dnat rule
```shell
forward@dnat
{
    "proxy1":                          # rule name is proxy1
    {
        "destip":"29.23.11.35",        # internet server ip is 29.23.11.35
        "destport":"90",               # internet server port is start 28, end at 90 
        "protocol":"tcpudp",           # proxy tcp and udp
        "targetport":"100"             # proxy the server on port 100 at local interface
    }
}
```



