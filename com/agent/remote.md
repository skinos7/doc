***
## Accept remote management
connect to remote server and accept administrative command from the that

#### Configuration( agent@remote )
```json
{
    "server":"remote server address",                      // [ string ]
    "id":"identify for device",                            // [ string ]
    "user":"username for device",                          // [ string ]
    "vcode":"vcode for device",                            // [ string ]
    "con_timeout":"timeout for connect",                   // [ number ], the unit is second
    "tcp_keepidle":"idle to keeplive",                     // [ number ], The unit is seconds
    "tcp_keepintvl":"keeplive interval",                   // [ number ], The unit is seconds
    "tcp_keepcnt":"keeplive failed time",                  // [ number ]

    "status":"enable or disable to connect the remote",    // [ "disable", "enable" ]
    "port":"remote server port",                           // [ number ]
    "path":"remote server path for post",                  // [ string ]
    "talk_timeout":"timeout for wait ack",                 // [ number ], the unit is second
    "report":                                              // report status after connect succeed
    {
        "interval":"report interval",                       // [number ], the unit is second
        "status":                                           // There are which statuses are being reported
        {
            "he command":"",                                // [ string ]: "",  string is he command
            "he command2":""                                // [ string ]: "",  string is he command
            // "...":""
        }
    },

    "he":"connect to remote for he command",              // [ "disable", "enable" ]
    "heport":"remote server heport port",                 // [ number ]

    "portc":"connect to remote for port port",            // [ "disable", "enable" ]
    "portcport":"remote server pport port",               // [ number ]
    "tcp_pond":"pond client for tcp port",                // [ nubmer ]
    "udp_pond":"pond client for tcp port",                // [ nuber ]
    "check_interval":"check interval for pond",            // [ number ], the unit is second
     
}
```
Examples, show all the configure
```shell
agent@remote
{
    "server":"http.wmdevice.com",                           # remote server is http://http.wmdevice.com:10101/dev
    "user":"dimmalex@gmail.com",
    "vcode":"123456",
    "con_timeout":"20",                                     # connect timeout is 20 seccond
    "tcp_keepidle":"20",
    "tcp_keepintvl":"10",
    "tcp_keepcnt":"3"

    "status":"enable",                                      # Accept remote management is enable
    "port":"10000",
    "path":"/dev",
    "talk_timeout":"15",                                    # post json timeout is 15 seccond
    "report":
    {
        "interval":"30",                                    # report interval is 30 second
        "status":
        {
            "land@machine.status":                          # only report the machine status
            {
            }
        }
    },

    "he":"disable",
    "heport":"10001"

    "portc":"disable",
    "portcport":"10009",
    "tcp_pond":"3",
    "udp_pond":"3",
    "check_interval":"10"
}
```  
Examples, disable the connecting remote management
```shell
agent@remote:status=disable
ttrue
```  

