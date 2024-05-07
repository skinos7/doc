***
## Accept remote management
connect to remote server and accept administrative json from the that

#### Configuration( agent@remote )
```json
{
    "status":"enable or disable to connect the remote",    // [ "disable", "enable" ]

    "server":"remote server address",                      // [ string ]
    "user":"username for device",                          // [ string ]
    "vcode":"vcode for device",                            // [ string ]

    "port":"remote server port",                           // [ number ]
    "path":"remote server path for post",                  // [ string ]
    "id":"identify for device",                            // [ string ]
    "resolve":"resolve the server to ip",                  // [ "disable", "enable" ]
    "con_timeout":"timeout for connect",                   // [ number ], the unit is second
    "talk_timeout":"timeout for wait ack",                 // [ number ], the unit is second

    "report":                                              // report status after connect succeed
    {
        "interval":"report interval",   // [number ], the unit is second
        "status":                       // There are which statuses are being reported, vailed when unique empty
        {
            "he command":"",                   // [ string ]: "",  string is he command
            "he command2":""                   // [ string ]: "",  string is he command
            // "...":""
        },
        "unique":"he command",          // [ string ], only report one json, Priority is higher than status
        "endnl":"end with a line"       // [ "disable", "enable" ]
    }
}
```
Examples, show all the configure
```shell
agent@remote
{
    "status":"enable",                                      # Accept remote management is enable

    "server":"devport.ashyelf.com",                         # remote server is devport.ashyelf.com
    "user":"dimmalex@gmail.com",
    "vcode":"123456",

    "port":"10000",
    "path":"/dev",
    "con_timeout":"20",                                     # connect timeout is 20 seccond
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
    }
}
```  
Examples, disable the remote client
```shell
agent@remote:status=disable
ttrue
```  


#### **Methods**

+ `setup[]` **setup the remote client**, *succeed return ttrue, failed return tfalse, error return terror*

+ `shut[]` **shutdown the remote client**, *succeed return ttrue, failed return tfalse, error return terror*

+ `status[]` **get the remote client infomation**, *succeed return talk to describes infomation, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "status":"current status",        // [ uping, down, online ]
                                             // uping for connecting
                                             // down for the network is down
                                             // online for connected
        "server":"server ip"              // [ remote ip address ]
    }
    ```
    ```shell
    # examples, get the remote client infomation
    agent@remote.status
    {
        "status":"online",                    // connect succeed
        "server":"114.132.219.158"            // remote server ip address
    }
    ```



+ `reboot[]` **reboot after 5 second and modify the remote client report interval 1 second**, *succeed return ttrue, failed return tfalse, error return terror*

+ `default[]` **default and reboot after 5 second and modify the remote client report interval 1 second**, *succeed return ttrue, failed return tfalse, error return terror*

+ `upgrade[ file ]` **upgrade the firmware from remote server**, *succeed return ttrue, failed return tfalse, error return terror*



+ `report[]` **show current report configure**, *succeed return json, failed return NULL, error return terror*
    ```shell
    # examples, show current remote client report configure
    agent@remote.report
    {
        "interval":"30",
        "status":
        {
            "gnss@nmea.info":""
        }
    }
    ```

+ `cookie[]` **show current POST cookie**, *succeed return json, failed return NULL, error return terror*
    ```shell
    # examples, show current remote client POST cookie
    agent@remote.cookie
    ```

+ `interval[ report interval ]` **modify or show the remote client report interval**, *succeed return netdev, failed return NULL, error return terror*
    ```shell
    # examples, modify the remote client report interval to 1 second
    agent@remote.interval[ 1 ]
    ttrue
    # examples, show the remote client report interval
    agent@remote.interval
    30
    ```

