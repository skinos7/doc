***
## Accept http management   
connect to http server and accept administrative json from the that

### Configuration( agent@remote )   
```json
{
    "status":"connect the http server",                    // [ "disable", "enable" ]

    "server":"http server address",                        // [ string ]
    "user":"username for device",                          // [ string ]
    "vcode":"vcode for device",                            // [ string ]

    "port":"http server port",                             // [ number ]
    "path":"http server path for post",                    // [ string ]
    "id":"identify for device",                            // [ string ]
    "resolve":"resolve the server to ip",                  // [ "disable", "enable" ]
    "con_timeout":"timeout for connect",                   // [ number ], the unit is second
    "talk_timeout":"timeout for wait ack",                 // [ number ], the unit is second

    "report":                                              // report status after connect succeed
    {
        "interval":"report interval",          // [number ], the unit is second
        "status":                              // There are which statuses are being reported, vailed when unique empty
        {
            "he command":"",                      // [ string ]: "",  string is he command
            "he command2":""                      // [ string ]: "",  string is he command
            // ...more he command
        },
        "unique":"he command",                 // [ string ], only report one json, Priority is higher than status
        "endnl":"end with a line"              // [ "disable", "enable" ]
    }
}
```   
Example, show all the configure   
```shell
agent@remote
{
    "status":"enable",                                      # connect to http server for management is enable

    "server":"devport.ashyelf.com",                         # http server is devport.ashyelf.com
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
Example, disable the http agent   
```shell
agent@remote:status=disable
ttrue
```  

### **Methods**

+ `setup[]` **setup the http client**, *succeed return ttrue, failed return tfalse, error return terror*   

+ `shut[]` **shutdown the http client**, *succeed return ttrue, failed return tfalse, error return terror*   

+ `status[]` **get the http client infomation**, *succeed return talk to describes infomation, failed return NULL, error return terror*   
    ```json
    // Attributes introduction of talk by the method return
    {
        "status":"current status",        // [ "uping", "down", "online", "usererror", "vcodeerror" ]
                                             // "uping" for connecting
                                             // "down" for the network is down
                                             // "online" for connected
                                             // "usererror" for username wrong
                                             // "vcodeerror" for username vcode wrong
        "server":"http server ip"         // [ ip address ]
    }
    ```   
    Example, get the http client infomation   
    ```shell
    agent@remote.status
    {
        "status":"online",                    # connect succeed
        "server":"114.132.219.158"            # http server ip address
    }
    ```   

+ `report[]` **show current http client report configure**, *succeed return json, failed return NULL, error return terror*   
    ```json
    // Attributes introduction of talk by the method return
    {
        "interval":"report interval",          // [number ], the unit is second
        "status":                              // There are which statuses are being reported
        {
            "he command":"",                      // [ string ]: "",  string is he command
            "he command2":""                      // [ string ]: "",  string is he command
            // ...more he command
        }
    }
    ```   
    Example, show current http client report configure   
    ```shell
    agent@remote.report
    {
        "interval":"30",                      # report interval 30 second
        "status":
        {
            "gnss@nmea.info":""               # only report the GNSS location infomation
        }
    }
    ```   

+ `interval[ report interval ]` **modify or show the http client report interval**, *succeed return netdev, failed return NULL, error return terror*   
    Example, modify the http client report interval to 1 second   
    ```shell
    agent@remote.interval[ 1 ]
    ttrue
    ```   
    Example, show the http client report interval   
    ```
    agent@remote.interval
    30
    ```   

+ `cookie[]` **show current http client POST cookie**, *succeed return json, failed return NULL, error return terror*   

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
        "network_port":"network keeplive port",               // [ port ]
        "network_port2":"network hole2 port",                 // [ port ]
        "network_id":"network identify",                      // [ string ]
        "network_net":"network endpoint net",                 // [ network address ]
        "network_mask":"network endpoint netmask",            // [ network address ]
        "network_keepintval":"network keeplive interval",     // [ number ], the unit is second
        "network_keepfailed":"network keeplive failed"        // [ number ]
    }
    ```   
    Example, adjust to run the port client, disable the network client   
    ```shell
    agent@remote.adjust[ { "portc":"enable", "network":"disable" } ]
    ttrue
    ```   

+ `reboot[]` **reboot after 5 second and modify the http client report interval 1 second**, *succeed return ttrue, failed return tfalse, error return terror*   

+ `default[]` **default and reboot after 5 second and modify the http client report interval 1 second**, *succeed return ttrue, failed return tfalse, error return terror*   

+ `upgrade[ file ]` **upgrade the firmware from http server**, *succeed return ttrue, failed return tfalse, error return terror*   

+ `upload[]` **upload all configure to http server(Not supported yet)**, *succeed return ttrue, failed return tfalse, error return terror*   

+ `config[]` **get all configure from http server(Not supported yet)**, *succeed return ttrue, failed return tfalse, error return terror*   


