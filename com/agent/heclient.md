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
Example, show all the configure   
```shell
agent@heclient
{
    "status":"enable",                                      # connect to heport server is enable

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
Example, disable the he client   
```shell
agent@heclient:status=disable
ttrue
```  

#### **Methods**   

+ `setup[]` **setup the he client**, *succeed return ttrue, failed return tfalse, error return terror*   

+ `shut[]` **shutdown the he client**, *succeed return ttrue, failed return tfalse, error return terror*   

+ `status[]` **get the he client infomation**, *succeed return talk to describes infomation, failed return NULL, error return terror*   
    ```json
    // Attributes introduction of talk by the method return
    {
        "status":"current status",        // [ "uping", "down", "online", "usererror", "vcodeerror" ]
                                             // "uping" for connecting
                                             // "down" for the network is down
                                             // "online" for connected
                                             // "usererror" for username wrong
                                             // "vcodeerror" for username vcode wrong
        "server":"hepoprt server ip"      // [ ip address ]
    }
    ```   
    Example, get the he client infomation   
    ```shell
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
        "portc":"connect to server for port proxy",           // [ "disable", "enable" ]
        "portc_port":"pport server port",                     // [ number ]
        "portc_tcppond":"pond client for tcp port",           // [ nubmer ]
        "portc_udppond":"pond client for tcp port",           // [ number ]
        "portc_interval":"check interval for pond",           // [ number ], the unit is second

        "network":"network function",                         // [ "disable", "enable" ]
        "network_port":"network service port",                // [ port ]
        "network_hole":"network server keeplive port",        // [ port ]
        "network_hole2":"network server hole2 port",          // [ port ]
        "network_id":"network identify",                      // [ string ]
        "network_net":"network endpoint net",                 // [ network address ]
        "network_mask":"network endpoint netmask",            // [ network address ]
        "network_keepintval":"network keeplive interval",     // [ number ], the unit is second
        "network_keepfailed":"network keeplive failed"        // [ number ]
    }
    ```   
    Example, adjust to run the port client, disable the network client   
    ```shell
    agent@heclient.adjust[ { "portc":"enable", "network":"disable" } ]
    ttrue
    ```   

+ `network[ {json} ]` **update all network status**, *succeed return ttrue, failed return tfalse, error return terror*   
    ```json
    // Attributes introduction of json pass to method
    {
        // same "agent@g2g" component "network" method
    }
    ```   

+ `branch[ {json} ]` **branch attach to network**, *succeed return ttrue, failed return tfalse, error return terror*   
    ```json
    // Attributes introduction of json pass to method
    {
        // same "agent@g2g" component "branch" method
    }
    ```   

+ `leaf[ {json} ]` **leaf attach to network**, *succeed return ttrue, failed return tfalse, error return terror*    
    ```json
    // Attributes introduction of json pass to method
    {
        // same "agent@g2g" component "leaf" method
    }
    ```   

+ `view_master[]` **get the network client master infomation**, *succeed return talk to describes infomation, failed return NULL, error return terror*   
    ```json
    // Attributes introduction of talk by the method return
    {
        "ip":"endpoint ip address",                   // [ ip address ]
        "pubkey":"public key",                        // [ string ]
        "peer":"device ip address",                   // [ ip address ]
        "port":"device work port",                    // [ port ]
        "nattype":"device nat type",                  // [ "8", "4", "2", "1" ], exist when device attach
        "delay":"device to master delay"              // [ number ], the unit is millisecond
    }
    ```   
    Example, show current network client master infomation   
    ```shell
    agent@heclient.view_master
    {
        "ip":"172.16.0.1",
        "pubkey":"gcDBBaqpCCPyQU4imX74Re8H/k4nOArrrzpTvmghWW4=",
        "peer":"113.118.159.127",
        "port":"10004",
        "nattype":"2",
        "delay":"101"
    }
    ```   

+ `view_self[]` **get the network client self infomation**, *succeed return talk to describes infomation, failed return NULL, error return terror*   
    ```json
    // Attributes introduction of talk by the method return
    {
        "ip":"endpoint ip address",                   // [ ip address ]
        "pubkey":"public key",                        // [ string ]
        "peer":"device ip address",                   // [ ip address ]
        "port":"device work port",                    // [ port ]
        "nattype":"device nat type"                   // [ "8", "4", "2", "1" ], exist when device attach
    }
    ```   
    Example, show current network client master infomation   
    ```shell
    agent@heclient.view_self
    {
        "ip":"172.16.0.3",
        "pubkey":"/2qlyCZ+47Zk0zCXqbv71nZ4tRIkfDXm8Z5wxnTAsFc=",
        "peer":"49.7.89.183",
        "port":"44232",
        "nattype":"8"
    }
    ```   

+ `list_network[]` **get the network all endpoint infomation**, *succeed return talk to describes infomation, failed return NULL, error return terror*   
    ```json
    // Attributes introduction of talk by the method return
    {
    }
    ```   

+ `list_branch[]` **get the network all branch infomation**, *succeed return talk to describes infomation, failed return NULL, error return terror*   
    ```json
    // Attributes introduction of talk by the method return
    {
    }
    ```   

