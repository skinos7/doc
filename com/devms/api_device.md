
***
## device management API
device management API, depend on devport and heport and pport
*all methods need username*

#### **Methods**

+ `device_list[ username, [device model] ]` **get all device list of username**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "device mac idenfify":{}                         // [ string ]:{}
        // ... more device
    }
    ```

+ `device_view[ username, device mac identify ]` **get the device infomation of username**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "mode":"gateway operator mode",                 // < "ap", "wisp", "nwisp", "gateway", "dgateway", "misp", "nmisp", "dmisp", "mix" >
                                                                // "ap": access point
                                                                // "wisp": 2.4G Wireless Internet Service Provider connection
                                                                // "nwisp": 5.8G Wireless Internet Service Provider connection( need the board support 5.8G wirless baseband)
                                                                // "gateway": wire WAN gateway
                                                                // "dgateway": Dual wire WAN gateway
                                                                // "misp": LTE Mobile Internet Service Provider connection( need the board support LTE baseband)
                                                                // "nmisp": Next Mobile(NR/LTE) Internet Service Provider connection( need the board support NR/LTE baseband)
                                                                // "dmisp": Dual Mobile(LTE/NR) Internet Service Provider connection( need the board support two LTE/NR baseband)
                                                                // "mix": custom mix connection from multiple internet connection
        "name":"gateway name",                          // [ string ], The name cannot contain spaces
        "platform":"gateway platform identify",         // [ string ]
        "hardware":"gateway hardware identify",         // [ string ]
        "custom":"gateway custom identify",             // [ string ]
        "scope":"gateway scope identify",               // [ string ]
        "version":"gateway version",                    // [ string ]
        "livetime":"gateway runtime",                   // [ string ], HH:MM:SS:Day
        "current":"gateway date",                       // [ string ], HH:MM:SS:MM:DD:YYYY
        "mac":"gateway MAC address",                    // [ mac address ]
        "macid":"device mac identify",                  // [ string ]
        "model":"gateway model",                        // [ string ]
        "cmodel":"gateway custom model",                // [ string ]
        "oem":"OEM packet size",                        // [ number ]
        "magic":"gateway magic identify",               // [ string ]
        "datecode":"gateway datecode",                  // [ string ]
        "cfgversion":"gateway configure version",       // [ string ]
        "wui_port":"gateway wui port",                  // [ number ]
        "telnet_port":"gateway telnet port",            // [ number ]
        "ssh_port":"gateway ssh port",                  // [ number ]
        "local_ip":"gateway local ip address",          // [ ip address ]

        "ifname":"extern ifname",                       // [ "ifname@lte", "ifname@lte2", "ifname@wan", "ifname@wisp", "ifname@wisp2", "ifname@lan" ]
                                                                // "ifname@lte" for LTE
                                                                // "ifname@lte2" for LTE2 or LTE/NR
                                                                // "ifname@wan" for WAN
                                                                // "ifname@wisp" for 2.4G WISP
                                                                // "ifname@wisp2" for 5.8G WISP
        "extern_ip":"extern ip address",                // [ ip address ]
        "rx_bytes":"receive bytes",                     // [ number ]
        "tx_bytes":"send bytes",                        // [ number ]
        "signal":"signal level",                        // [ "0", "1", "2", "3", "4" ], exist when "ifname" be "ifname@lte" or "ifname@lte2" or "ifname@wisp" or "ifname@wisp2"
        "operator":"operator name",                     // [ string ], exist when "ifname" be "ifname@lte" or "ifname@lte2" or "ifname@wisp" or "ifname@wisp2"
        "nettype":"lte network type",                   // [ string ], exist when "ifname" be "ifname@lte" or "ifname@lte2"

        "online":"gateway online time",                 // [ string ], HH:MM:SS:Day, exist when online
        "key":"heport control key",                     // [ string ], exist when online on heport

        "comment":"gateway comment string"              // [ string ]
    }
    ```

+ `device_listv[ username, [device model] ]` **get all device infomation of username**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "device mac idenfify":                         // [ string ]:{}
        {
            // ... see the "device_view" return
        }
        // ... more device
    }
    ```



+ `device_add[ username, device mac identify, [comment] ]` **add a device**, *succeed return tture, failed return tfalse, error return terror*

+ `device_delete[ username, device mac identify ]` **delete a device**, *succeed return tture, failed return tfalse, error return terror*



+ `device_status[ username, device mac identify ]` **get the device status**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "land@machine.status":             // machine basic information for gateway
        {
            // gateway land@machine.status return
        },
        "network@frame.default":           // internet connection information for gateway
        {
            // gateway network@frame.default return
        },
        "heport":                          // heport infomation for gateway
        {
            "online":"online time",                              // [ string ], HH:MM:SS:Day
            "fd":"file number",                                  // [ number ]
            "addr":"gateway connected ip",                       // [ ip address ]
            "port":"gateway connected port",                     // [ number ]
            "user":"heport control user",                        // [ string ]            
            "key":"control key"                                  // [ string ]
        },
        "pport":                          // pport infomation for gateway
        {
            "tcp":"tcp pond",                                    // [ number ]
            "udp":"udp pond"                                     // [ number ]
        }
    }
    ```



+ `device_get[ username, device mac identify ]` **get the device configure**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    // that save at $user/dev/$macid/config.json
    {
        "cfgversion":"gateway configure version",       // [ string ]
        "comment":"gateway comment string",             // [ string ]
        "netid":"network identify"                      // [ string ]
    }
    ```

+ `device_set[ username, device mac identify, {device configure} ]` **set the device configure**, *succeed return tture, failed return tfalse, error return terror*
    ```json
    // Attributes introduction of talk by the method parameter of {device configure}
    {
        "cfgversion":"gateway configure version",       // [ string ]
        "comment":"gateway comment string",             // [ string ]
        "netid":"network identify"                      // [ string ]
        // ... more configure, detail same device_get return
    }
    ```


