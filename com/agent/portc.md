***
## Connect to port proxy
connect to port proxy to proxy the tcp/udp connection

#### Configuration( agent@portc )
```json
{
    "portc":"connect to port proxy",                // [ "disable", "enable" ]

    "server":"port proxy address",                  // [ string ], use the remote:server when this none
    "user":"username for device",                   // [ string ], use the remote:user when this none
    "vcode":"vcode for device",                     // [ string ], use the remote:vcode when this none

    "portc_port":"port proxy port",                      // [ number ]
    "portc_intval":"check interval for pond",            // [ number ], the unit is second
    "portc_tcppond":"pond client for tcp port",          // [ nubmer ]
    "portc_udppond":"pond client for tcp port",          // [ number ]
    "portc_usetimeout":"use connection timeout time",    // [ number ], the unit is second
    "portc_nousetimeout":"idle connection timeout time", // [ number ], the unit is second

    "tcp_keepidle":"idle to keeplive",              // [ number ], The unit is seconds
    "tcp_keepintvl":"keeplive interval",            // [ number ], The unit is seconds
    "tcp_keepcnt":"keeplive failed time"            // [ number ]
}
```
Examples, show all the configure
```shell
agent@portc
{
    "portc_port":"10009",
    "portc_intval":"30",                # 30sec to check the pond already
    "portc_tcppond":"3"
    "portc_udppond":"3"
    "portc_usetimeout":"45",            # 45sec timeout to close the idle connection
    "portc_nousetimeout":"120"          # 45sec timeout to close the idle connection
}
```  
Examples, modify the portc port to 1000
```shell
agent@portc:portc_port=1000
ttrue
```  


#### **Methods**

+ `setup[]` **setup the portc client**, *succeed return ttrue, failed return tfalse, error return terror*

+ `shut[]` **shutdown the portc client**, *succeed return ttrue, failed return tfalse, error return terror*

+ `status[]` **get the portc status**, *succeed return talk to describes infomation, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "status":"current status"         // [ uping, down, online ]
                                             // uping for connecting
                                             // down for the network is down
                                             // online for the cloud is connect succeed
    }
    ```

