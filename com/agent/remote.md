***
## Accept remote management
connect to remote server and accept administrative command from the that

#### Configuration( agent@remote )
```json
{
    "server":"remote server address",                      // [ string ]
    "resolve":"resolve the server to ip",                  // [ "disable", "enable" ]
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
        "status":                                           // There are which statuses are being reported, vailed when unique empty
        {
            "he command":"",                                // [ string ]: "",  string is he command
            "he command2":""                                // [ string ]: "",  string is he command
            // "...":""
        },
        "unique":"he command"                               // [ string ], only report one json, Priority is higher than status
        "endnl":"end with a line"                           // [ "disable", "enable" ]
    },

    "he":"connect to remote for he command",              // [ "disable", "enable" ]
    "heport":"remote server heport port",                 // [ number ]

    // control by hport 
    "portc":"connect to remote for port port",            // [ "disable", "enable" ]
    "portcport":"remote server pport port",               // [ number ]
    "tcp_pond":"pond client for tcp port",                // [ nubmer ]
    "udp_pond":"pond client for tcp port",                // [ number ]
    "check_interval":"check interval for pond",           // [ number ], the unit is second
    // control by hport 
    "g2g":"gateway to gateway agent function",            // [ "disable", "enable" ]
    "g2gid":"g2g network identify",                           // [ string ]
    "g2gport":"g2g keeplive port",                        // [ number ]
    "g2gport2":"g2g p2p port",                            // [ number ]
    "g2g_localport":"g2g listen port",                    // [ number ]
    "g2g_interval":"g2g keeplive interval"                // [ number ], the unit is second
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
}
```  
Examples, disable the connecting remote management
```shell
agent@remote:status=disable
ttrue
```  


#### **Methods**

+ `setup[]` **setup the cloud client**, *succeed return ttrue, failed return tfalse, error return terror*

+ `shut[]` **shutdown the cloud client**, *succeed return ttrue, failed return tfalse, error return terror*

+ `adjust[ {json} ]` **adjust the cloud client**, *succeed return ttrue, failed return tfalse, error return terror*
    ```json
    // Attributes introduction of json pass to method
    {
        "portc":"connect to remote for port port",            // [ "disable", "enable" ]
        "portcport":"remote server pport port",               // [ number ]
        "tcp_pond":"pond client for tcp port",                // [ nubmer ]
        "udp_pond":"pond client for tcp port",                // [ number ]
        "check_interval":"check interval for pond",           // [ number ], the unit is second

        "g2g":"gateway to gateway agent function",            // [ "disable", "enable" ]
        "g2gid":"network identify",                           // [ string ]
        "g2gport":"g2g keeplive port",                        // [ number ]
        "g2gport2":"g2g p2p port",                            // [ number ]
        "g2g_interval":"g2g keeplive interval"                // [ number ], the unit is second
    }
    ```
    ```shell
    # examples, adjust cloud client to run the port client, disable the g2g client
    agent@remote.adjust[ { "portc":"enable", "g2g":"disable" } ]
    ttrue
    ```

+ `status[]` **get the cloud client infomation**, *succeed return talk to describes infomation, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "status":"current status",        // [ uping, down, online ]
                                             // uping for connecting
                                             // down for the network is down
                                             // online for the cloud is connect succeed
        "server":"cloud server ip",       // [ ip address ]

        "he":"current heport status",     // [ uping, down, online ]
                                             // uping for connecting
                                             // down for the network is down
                                             // online for the cloud is connect succeed

        "portc":"current pport status",   // [ uping, down, online ]
                                             // uping for connecting
                                             // down for the network is down
                                             // online for the cloud is connect succeed
        "portc_list":
        {
            "connect peer ip and port":   // [ ip:port ]:
            {
                "ip":"server ip",                   // [ ip address ]
                "port":"server port",               // [ port ]
                "hand_ip":"local connect ip",       // [ ip address ]
                "hand_port":"local connect port",   // [ port ]
                "tx":"send bytes",                  // [ number ]
                "rx":"recive bytes"                 // [ number ]
            }
            // more portc link ...
        }
    }
    ```
    ```shell
    # examples, get the cloud client infomation
    agent@remote.status
    {
        "status":"online",                    // current connect cloud succeed
        "server":"114.132.219.158",           // cloud ip address
        "he":"online",                        // he client connect cloud succeed
        "portc":"online",                     // port client connect cloud succeed
        "portc_list":                            // port client list
        {
            "111.221.192.143:42638":             // local ip and port
            {
                "ip":"114.132.219.158",              // server ip
                "tx":"72",                           // send bytes
                "rx":"0"
            },
            "111.221.192.143:42469":
            {
                "ip":"114.132.219.158",
                "tx":"72",
                "rx":"0"
            },
            "111.221.192.143:42466":
            {
                "ip":"114.132.219.158",
                "tx":"72",
                "rx":"0"
            }
        }
    }
    ```

+ `interval[ report interval ]` **modify the cloud client report interval**, *succeed return netdev, failed return NULL, error return terror*
    ```shell
    # examples, modify the cloud client interval to 1 second
    agent@remote.interval[ 1 ]
    ttrue
    ```

+ `reboot[]` **reboot after 5 second and report interval 1 second**, *succeed return netdev, failed return NULL, error return terror*

+ `default[]` **default and reboot after 5 second and report interval 1 second**, *succeed return netdev, failed return NULL, error return terror*

+ `upgrade[ file ]` **upgrade the firmware from cloud**, *succeed return ttrue, failed return tfalse, error return terror*

