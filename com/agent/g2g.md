***
## Connect to network proxy
connect to network proxy for gateway to gatway

#### Configuration( agent@g2g )
```json
{
    "network":"connect to network proxy",               // [ "disable", "enable" ]

    "server":"network proxy address",               // [ string ], use the remote:server when this none
    "user":"username for device",                   // [ string ], use the remote:user when this none
    "vcode":"vcode for device",                     // [ string ], use the remote:vcode when this none

    "network_port":"network listen port",                         // [ number ]
    "network_hole":"network hole port for heport to keeplive",    // [ number ]
    "network_hole2":"network p2p port",                           // [ number ]
    "network_holeout":"wait the test timeout",                    // [ number ]
    "network_id":"network identify",                              // [ string ]
    "network_net":"network address",                              // [ string ]
    "network_mask":"network mask",                                // [ string ]
    "network_icmpintval":"network icmp keeplive interval",        // [ number ], the unit is second
    "network_icmpfailed":"network icmp keeplive failed time"      // [ number ]
}
```
Examples, show all the configure
```shell
agent@network
{
    "network_port":"10004",
    "network_hole":"10005",
    "network_hole2":"10006"
    "network_holeout":"10"
}
```  
Examples, modify the network port to 7000
```shell
agent@network:network_port=7000
ttrue
```  


#### **Methods**

+ `setup[]` **setup the network client**, *succeed return ttrue, failed return tfalse, error return terror*

+ `shut[]` **shutdown the network client**, *succeed return ttrue, failed return tfalse, error return terror*

+ `status[]` **get the network client status**, *succeed return talk to describes infomation, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "status":"current status"        // [ uping, down, online ]
                                             // uping for connecting
                                             // down for the network is down
                                             // online for the cloud is connect succeed
    }
    ```

+ `master[]` **get the network client master infomation**, *succeed return talk to describes infomation, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
    }
    ```

+ `self[]` **get the network client self infomation**, *succeed return talk to describes infomation, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
    }
    ```



+ `network[ {json} ]` **update all network status**, *succeed return ttrue, failed return tfalse, error return terror*
    ```json
    // Attributes introduction of json pass to method
    {
        "device mac identify":
        {
            "type":"gateway type",                     // [ "auto", "master", "branch" ], default is "auto"
            "net":"device endpoint network address",   // [ network address ]
            "mask":"device endpoint netmask address",  // [ netmask address ]

            "ip":"device endpoint ip address",         // [ ip address ]
            "pubkey":"public key",                     // [ string ], exist when device attach

            "nattype":"device nat type",               // [ "8", "4", "2" ], exist when device attach
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

        "type":"gateway type",                     // [ "auto", "master", "branch" ], default is "auto"
        "net":"device endpoint network address",   // [ network address ]
        "mask":"device endpoint netmask address",  // [ netmask address ]

        "ip":"device endpoint ip address",         // [ ip address ]
        "pubkey":"public key",                     // [ string ], exist when device attach

        "nattype":"device nat type",               // [ "8", "4", "2" ], exist when device attach
        "peer":"device ip address",                // [ ip address ], exist when device attach
        "port":"device port"                       // [ port ], exist when device attach
    }
    ```

+ `leaf[ {json} ]` **leaf attach to network**, *succeed return ttrue, failed return tfalse, error return terror*
    ```json
    // Attributes introduction of json pass to method
    {
        "macid":"branch mac identify",             // [ string ]

        "type":"gateway type",                     // [ "auto", "master", "branch" ], default is "auto"
        "net":"device endpoint network address",   // [ network address ]
        "mask":"device endpoint netmask address",  // [ netmask address ]

        "ip":"device endpoint ip address",         // [ ip address ]
        "pubkey":"public key",                     // [ string ], exist when device attach

        "nattype":"device nat type",               // [ "8", "4", "2" ], exist when device attach
        "peer":"device ip address",                // [ ip address ], exist when device attach
        "port":"device port"                       // [ port ], exist when device attach
    }
    ```

