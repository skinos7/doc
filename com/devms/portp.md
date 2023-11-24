***
## Port proxy management
Porxy the local port to gateway local port

#### Configuration( devms@portp )
```json
{
    "status":"disable or enable",            // [ "disable", "enable" ]
    "port":"server port",                    // [ number ]
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
devms@portp
{
}
```  
Examples, enable the port proxy
```shell
devms@portp:status=enable
ttrue
```  

