***
## device port proxy management
Porxy the local port to gateway local port

#### Configuration( devms@pport )
```json
{
    "status":"disable or enable",            // [ "disable", "enable" ]
    "port":"server port",                    // [ number ]
    "tcp_keepidle":"idle to keeplive",       // [ number ], The unit is seconds
    "tcp_keepintvl":"keeplive interval",     // [ number ], The unit is seconds
    "tcp_keepcnt":"keeplive failed time",    // [ number ]

    "rule":
    {
        "port nubmer":                           // [ number ]:{}
        {
            "macid":"gateway mac identify",            // [ string ]
            "pond":"how many connection",              // [ number ]
            "protocol":"proxy protocol",               // [ "tcp", "udp" ]
            "local":"local address",                   // [ ip address ]
            "local_port":"local server port"           // [ number ]
            "desc":"Usage description",
        }
        // more rule
    }
}
```
Examples, show all the configure
```shell
devms@pport
{
}
```  
Examples, enable the port proxy
```shell
devms@pport:status=enable
ttrue
```  

