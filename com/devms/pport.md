***
## device port proxy management
Porxy the local port to gateway local port

#### Configuration( devms@pport )
```json
{
    "status":"disable or enable",            // [ "disable", "enable" ]
    "port":"server port",                    // [ number ]

    "port_satrt":"map port start",           // [ number ]

    "tcp_keepidle":"idle to keeplive",       // [ number ], The unit is seconds
    "tcp_keepintvl":"keeplive interval",     // [ number ], The unit is seconds
    "tcp_keepcnt":"keeplive failed time",    // [ number ]

    "rule":
    {
        "port nubmer":                           // [ number ]:{}
        {
            "macid":"gateway mac identify",            // [ string ]
            "protocol":"proxy protocol",               // [ "tcp", "udp" ]
            "local":"local address",                   // [ ip address ]
            "local_port":"local server port",          // [ number ]
            "desc":"Usage description"
        }
        // more rule
    }
}
```
Examples, show all the configure
```shell
devms@pport
{
    "status":"enable",                // Port port functon enable
    "port":"10009",                   // server port is 10009
    "dynamic_satrt":"10010",          // dynamic port start at 10010
    "static_port":"15000",            // static rule port start at 15000

    "tcp_keepidle":"20",
    "tcp_keepintvl":"10",
    "tcp_keepcnt":"3",

    "rule":
    {
        "15000":                       // map the 192.168.8.86:502 on 88124E123210 to 15000
        {
            "macid":"88124E123210",
            "protocol":"tcp",
            "local":"192.168.8.86",
            "local_port":"502"
        }
    }
}
```  
Examples, disable the port proxy
```shell
devms@pport:status=disable
ttrue
```  

#### **Methods**

+ `map[ device id, port, local ip, local port ]` **add a port map**, *succeed return tture, failed return tfalse, error return terror*

+ `unmap[ device id, port ]` **delete a port map**, *succeed return tture, failed return tfalse, error return terror*

+ `device_list[ [username] ]` **get device list**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "user name":"pond number"        [ string ]: [ number ]
        // more user ...
    }
    ```

+ `device_info[ device id ]` **get device pond number**, *succeed return string to describes, failed return NULL, error return terror*

+ `port_list[ [device id] ]` **get port list**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "port number":                    [ number ]:
        {
            "index":"port index",                    [ number ]
            "macid":"current map device",            [ string ]
            "hand_ip":"current map local ip",        [ ip address ]
            "hand_port":"current map local port",    [ port ]
            "pond":"current pond link"               [ number ]
        }
        // more port ...
    }
    ```

+ `port_info[ port number ]` **get port link list**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "index":"port index",                    [ number ]
        "macid":"current map device",            [ string ]
        "hand_ip":"current map local ip",        [ ip address ]
        "hand_port":"current map local port",    [ port ]
        "pond":"current pond link",              [ number ]
        "client ip and client port":             [ string ]:
        {
            "ip":"proxy ip",                        [ ip address ]
            "port":"proxy port",                    [ port ]
            "tx":"send bytes",                      [ number ]
            "rx":"receive bytes"                    [ number ]
        }
        // more link ...
    }
    ```


