***
## Accept heport management
connect to heport server and accept administrative line from the that

#### Configuration( agent@heclient )
```json
{
    "status":"connect to heport server for he command",    // [ "disable", "enable" ]

    "server":"heport server address",                      // [ string ], use the remote:server when this none
    "user":"username for device",                          // [ string ], use the remote:user when this none
    "vcode":"vcode for device",                            // [ string ], use the remote:vcode when this none

    "port":"heport server port",                           // [ number ]
    "con_timeout":"connect to heport server timeout",      // [ number ]
    "keep_intval":"heport server keeplive interval",       // [ number ], the unit is second
    "keep_failed":"heport server keeplive failed time",    // [ number ]

    "tcp_keepidle":"idle to keeplive",                     // [ number ], The unit is seconds
    "tcp_keepintvl":"keeplive interval",                   // [ number ], The unit is seconds
    "tcp_keepcnt":"keeplive failed time"                   // [ number ]
}
```
Examples, show all the configure
```shell
agent@heclient
{
    "status":"enable",                                      # Accept remote management is enable

    "server":"devport.ashyelf.com",                         # heport server is devport.ashyelf.com
    "user":"dimmalex@gmail.com",
    "vcode":"123456",

    "port":"10006",
    "con_timeout":"20",                                     # connect timeout is 20 seccond
    "keep_intval":"20",
    "keep_failed":"3",

    "tcp_keepidle":"20",
    "tcp_keepintvl":"10",
    "tcp_keepcnt":"3"
}
```  
Examples, disable the he client
```shell
agent@heclient:status=disable
ttrue
```  


#### **Methods**

+ `setup[]` **setup the he client**, *succeed return ttrue, failed return tfalse, error return terror*

+ `shut[]` **shutdown the  client**, *succeed return ttrue, failed return tfalse, error return terror*

+ `status[]` **get the he client infomation**, *succeed return talk to describes infomation, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {

        "status":"current heport status",     // [ uping, down, online ]
                                                 // uping for connecting
                                                 // down for the network is down
                                                 // online for connected
        "server":"server ip"                  // [ heport ip address ]
    }
    ```
    ```shell
    # examples, get the he client infomation
    agent@heclient.status
    {
        "status":"online",                    // connect succeed
        "server":"114.132.219.158"            // heport server ip address
    }
    ```



+ `adjust[ {json} ]` **adjust the other client**, *succeed return ttrue, failed return tfalse, error return terror*
    ```json
    // Attributes introduction of json pass to method
    {
        "portc":"connect to remote for port port",            // [ "disable", "enable" ]
        "portc_port":"remote server pport port",              // [ number ]
        "portc_tcppond":"pond client for tcp port",           // [ nubmer ]
        "portc_udppond":"pond client for tcp port",           // [ number ]
        "portc_interval":"check interval for pond",           // [ number ], the unit is second

        "network":"network function",                         // [ "disable", "enable" ]
        "network_port":"network keeplive port",               // [ port ]
        "network_port2":"network hole2 port",                 // [ port ]
        "network_id":"network identify",                      // [ string ]
        "network_net":"network endpoint net",                 // [ network address ]
        "network_mask":"network endpoint netmask",            // [ network address ]
        "network_keeplive":"network keeplive interval",       // [ number ], the unit is second
    }
    ```
    ```shell
    # examples, adjust to run the port client, disable the network client
    agent@heclient.adjust[ { "portc":"enable", "network":"disable" } ]
    ttrue
    ```



+ `network[ {json} ]` **update all network status**, *succeed return ttrue, failed return tfalse, error return terror*
    ```json
    // Attributes introduction of json pass to method
    {
        "device mac identify":
        {
            "net":"device endpoint network address",   // [ network address ]
            "mask":"device endpoint netmask address",  // [ netmask address ]

            "ip":"device endpoint ip address",         // [ ip address ]
            "pubkey":"public key",                     // [ string ], exist when device connected

            "nattype":"device nat type",               // [ "8", "4", "2", "1" ], exist when device attach
            "peer":"device ip address",                // [ ip address ], exist when device attach
            "port":"device port"                       // [ port ], exist when device attach
        }
        // ... more device
    }
    ```

+ `branch[ {json} ]` **branch attach to network**, *succeed return ttrue, failed return tfalse, error return terror*
    ```json
    // Attributes introduction of json pass to method
    {
        "macid":"branch mac identify",             // [ string ]

        "ip":"device endpoint ip address",         // [ ip address ]
        "pubkey":"public key",                     // [ string ]

        "net":"device endpoint network address",   // [ network address ]
        "mask":"device endpoint netmask address",  // [ netmask address ]

        "nattype":"device nat type",               // [ "8", "4", "2", "1" ]
        "peer":"device ip address",                // [ ip address ]
        "port":"device port"                       // [ port ]
    }
    ```

+ `leaf[ {json} ]` **leaf attach to network**, *succeed return ttrue, failed return tfalse, error return terror*
    ```json
    // Attributes introduction of json pass to method
    {
        "macid":"branch mac identify",             // [ string ]

        "ip":"device endpoint ip address",         // [ ip address ]
        "pubkey":"public key",                     // [ string ]

        "net":"device endpoint network address",   // [ network address ]
        "mask":"device endpoint netmask address",  // [ netmask address ]

        "nattype":"device nat type",               // [ "8", "4", "2", "1" ]
        "peer":"device ip address",                // [ ip address ]
        "port":"device port"                       // [ port ]
    }
    ```

