***
## device port proxy management
Porxy the local port to device local port

#### Configuration( devms@pport )
```json
{
    "status":"disable or enable",            // [ "disable", "enable" ]
    "port":"server port",                    // [ number ]

    "port_satrt":"map port start",           // [ number ]

    "keeplive":"nouse idle to keeplive",     // [ number ], The unit is seconds
    "timeout":"use connect timeout to close",// [ number ], The unit is seconds
    "tcp_keepidle":"idle to keeplive",       // [ number ], The unit is seconds
    "tcp_keepintvl":"keeplive interval",     // [ number ], The unit is seconds
    "tcp_keepcnt":"keeplive failed time",    // [ number ]

    "rule at the tcpmap.cfg and udpmap.cfg of user directory":
    {
        "port nubmer":                           // [ number ]:{}
        {
            "macid":"device mac identify",           // [ string ]
            "hand_ip":"local address",                // [ ip address ]
            "hand_port":"local server port"           // [ number ]
        }
        // more rule
    }
}
```
Examples, show all the configure
```shell
devms@pport
{
    "status":"enable",                # port map port functon enable
    "port":"10009",                   # server port is 10009
    "satrt_port":"10010",             # port start at 10010

    "keeplive":"20",                  # 20sec send the keeplive to idle connection
    "timeout":"120",                  # 120sec no date to close for use connection
    "tcp_keepidle":"20",
    "tcp_keepintvl":"10",
    "tcp_keepcnt":"3"
}
```  
Examples, disable the port proxy
```shell
devms@pport:status=disable
ttrue
```  

#### **Methods**

+ `list[]` **get all device list**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "device mac identify":{}       // [ string ]: {}
        // ... more device
    }
    ```

+ `view[ device mac identify ]` **get device pond number**, *succeed return string to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "tcp":"tcp pond",             // [ number ]
        "udp":"udp pond"              // [ number ]
    }    
    ```

+ `listv[]` **get all device pond number**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "device mac identify":       // [ string ]: {}
        {
            "tcp":"tcp pond",             // [ number ]
            "udp":"udp pond"              // [ number ]
        }
        // ... more device
    }
    ```



+ `port_list[ [device mac identify], [ protocol ] ]` **get all port map list**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "port number":"port index"             //  [ number ]: [ number ]
        // more port ...
    }
    ```

+ `port_view[ port number, [ protocol ] ]` **get port infomation**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "index":"port index",                  //  [ number ]
        "macid":"current map device",          //  [ string ]
        "hand_ip":"current map local ip",      //  [ ip address ]
        "hand_port":"current map local port",  //  [ port ]
        "pond":"current pond link"             //  [ number ]       
    }
    ```

+ `port_listv[ [device mac identify], [ protocol ] ]` **get all port map infomation**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "port number":                    [ number ]: {}
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



+ `port_conn[ port number, [ protocol ] ]` **get port connection list**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "index":"port index",                    [ number ]
        "macid":"current map device",            [ string ]
        "hand_ip":"current map local ip",        [ ip address ]
        "hand_port":"current map local port",    [ port ]
        "pond":
        {
            "client ip and client port":"file descriptor"     // [ ip address:port ]:[ number ]
            // more pond connection
        },
        "reserve":
        {
            "client ip and client port":"file descriptor"     // [ ip address:port ]:[ number ]
            // more reserve connection
        },
        "client ip and client port":             [ ip address:port ]: {}
        {
            "ip":"proxy ip",                        [ ip address ]
            "port":"proxy port",                    [ port ]
            "tx":"send bytes",                      [ number ]
            "rx":"receive bytes",                   [ number ]
            "last":"last active uptime"             [ number ]
        }
        // more proxy connection ...
    }
    ```



+ `port_map[ device mac identify, port, local ip, local port, [ protocol ], [ timeout ] ]` **add a port map**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "port":"port number",                    [ number ]
        "macid":"current map device",            [ string ]
        "hand_ip":"current map local ip",        [ ip address ]
        "hand_port":"current map local port"     [ port ]
    }
    ```

+ `port_unmap[ [device mac identify], [port], [ protocol ] ]` **delete a port map**, *succeed return tture, failed return tfalse, error return terror*


