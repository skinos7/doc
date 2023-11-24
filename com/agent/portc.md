***
## Port proxy client management
Connect to the port proxy for proxy some local port server

#### Configuration( agent@portc )
```json
{
    "status":"disable or enable",            // [ "disable", "enable" ]
    "rule":
    {
        "rule name":                               // [ string ]:{}
        {
            "pond":"how many connection",              // [ number ]
            "port":"Request external port",            // [ number ]
            "protocol":"proxy protocol",               // [ "tcp", "udp" ]
            "proxy":"proxy address",                   // [ string ]
            "proxy_port":"proxy listener port",        // [ number ]
            "local":"local address",                   // [ string ]
            "local_port":"local server port"           // [ number ]
        }
        // more rule
    }
}
```
Examples, show all the configure
```shell
agent@portc
{
}
```  
Examples, enable the port proxy client
```shell
agent@portc:status=enable
ttrue
```  

