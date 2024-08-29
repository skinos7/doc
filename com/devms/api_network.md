
## device network management API   
device network management API, depend on heport   
*all methods need username*   

#### **Methods**   

+ `network_list[ username  ]` **get the all network list of username**, *succeed return talk to describes, failed return NULL, error return terror*   
    ```json
    // Attributes introduction of talk by the method return  
    // that file save at $user/network.json
    {
        "network identify":{}                    // [ string ]: {}
        // more network...
    }
    ```   

+ `network_get[ username, network identify ]` **get the network all configure**, *succeed return talk to describes, failed return NULL, error return terror*   
    ```json
    // Attributes introduction of talk by the method return
    // that save at $user/network.json:$netid
    {
        "net":"network address",                       // [ network address ]
        "mask":"network mask",                         // [ network mask  ]
        "keepintval":"keeplive interval",              // [ number ], the unit is second
        "keepfailed":"keeplive failed times",          // [ number ]
        // ... more configure you can custom

        "device":
        {
            "device mac identify":                        // [ string ]  
            {
                "type":"gateway type",                       // [ "auto", "master", "branch" ], default is "auto"
                "ip":"gateway endpoint ip address",          // [ ip address ]
                "net":"gateway endpoint network",            // [ network ]
                "mask":"gateway endpoint netmask"            // [ netmask ]
                // more configure you can custom
            }
            // more device...
        }
    }
    ```   

+ `network_set[ username, network identify, {network configure} ]` **set the network configure**, *succeed return tture, failed return tfalse, error return terror*   
    ```json
    // Attributes introduction of talk by the method parameter of {network configure}
    // that save at $user/network.json:$netid
    {
        "net":"network address",                       // [ network address ]
        "mask":"network mask",                         // [ network mask  ]
        // ... more configure, detail same network_get return
    }
    ```   

+ `network_modify[ username, network identify, {network configure} ]` **modify the network configure**, *succeed return tture, failed return tfalse, error return terror*    
    ```json
    // Attributes introduction of talk by the method parameter of {network configure}
    // that save at $user/network.json:$netid
    {
        "net":"network address",                       // [ network address ]
        "mask":"network mask",                         // [ network mask  ]
        // ... more configure, detail same network_get return
    }
    ```   

+ `network_view[ username, network identify  ]` **get the network infomation of username**, *succeed return talk to describes, failed return NULL, error return terror*   
    ```json
    // Attributes introduction of talk by the method return  
    {
        "net":"network address",                       // [ network address ]
        "mask":"network mask",                         // [ network mask  ]
        "keepintval":"keeplive interval",              // [ number ], the unit is second
        "keepfailed":"keeplive failed times",          // [ number ]

        "master":"network master online nubmer",          // [ number ]
        "branch":"network branch online number",          // [ number ]

        "free":"network free client online number",       // [ number ]
        "limit":"network limit client online number",     // [ number ]
        "dyn":"network dyn client online number"          // [ number ]
    }
    ```   

+ `network_listv[ username  ]` **get the all network infomation of username**, *succeed return talk to describes, failed return NULL, error return terror*   
    ```json
    // Attributes introduction of talk by the method return  
    {
        "network identify":             // [ string]: {}
        {
            "net":"network address",                   // [ network address ]
            "mask":"network mask",                     // [ network mask  ]
            "keepintval":"keeplive interval",          // [ number ], the unit is second
            "keepfailed":"keeplive failed times",      // [ number ]

            "master":"network master online nubmer",          // [ number ]
            "branch":"network branch online number",          // [ number ]

            "free":"network free client online number",       // [ number ]
            "limit":"network limit client online number",     // [ number ]
            "dyn":"network dyn client online number"          // [ number ]
        }
        // ... more network
    }
    ```   

+ `network_add[ username, network identify, [network], [netmask], [keepintval], [keepfailed]` **add a network**, *succeed return tture, failed return tfalse, error return terror*   

+ `network_delete[ username, network identify ]` **delete a network**, *succeed return tture, failed return tfalse, error return terror*   

+ `network_device_list[ username, network identify  ]` **get the network device list of username**, *succeed return talk to describes, failed return NULL, error return terror*   
    ```json
    // Attributes introduction of talk by the method return  
    {
        "device mac identify":                        // [ string ]  
        {
        }
        // more device...
    }
    ```   

+ `network_device_view[ username, network identify, device mac identify  ]` **get the network device infomation of username**, *succeed return talk to describes, failed return NULL, error return terror*   
    ```json
    // Attributes introduction of talk by the method return  
    {
        "type":"gateway type",                     // [ "auto", "master", "branch" ], default is "auto"
        "net":"gateway endpoint network",          // [ network ]
        "mask":"gateway endpoint netmask",         // [ netmask ]

        "ip":"gateway endpoint ip address",        // [ ip address ]
        "pubkey":"public key",                     // [ string ], exist when device attach

        "attach":"online time",                    // [ string ], HH:MM:SS:DAY, exist when device attach
        "nattype":"device nat type",               // [ "8", "4", "2" ], exist when device attach
        "peer":"device ip address",                // [ ip address ], exist when device attach
        "port":"device port",                      // [ port ], exist when device attach

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
        "version":"gateway version",                    // [ string ]
        "livetime":"gateway runtime",                   // [ string ], HH:MM:SS:Day
        "macid":"device mac identify",                  // [ string ]
        "model":"gateway model",                        // [ string ]
        "cmodel":"gateway custom model",                // [ string ]
        "ifname":"extern ifname",                       // [ "ifname@lte", "ifname@lte2", "ifname@wan", "ifname@wisp", "ifname@wisp2", "ifname@lan" ]
                                                            // "ifname@lte" for LTE
                                                            // "ifname@lte2" for LTE2 or LTE/NR
                                                            // "ifname@wan" for WAN
                                                            // "ifname@wisp" for 2.4G WISP
                                                            // "ifname@wisp2" for 5.8G WISP
        "rx_bytes":"receive bytes",                     // [ number ]
        "tx_bytes":"send bytes",                        // [ number ]
        "signal":"signal level",                        // [ "0", "1", "2", "3", "4" ], exist when "ifname" be "ifname@lte" or "ifname@lte2" or "ifname@wisp" or "ifname@wisp2"
        "operator":"operator name",                     // [ string ], exist when "ifname" be "ifname@lte" or "ifname@lte2" or "ifname@wisp" or "ifname@wisp2"
        "nettype":"lte network type",                   // [ string ], exist when "ifname" be "ifname@lte" or "ifname@lte2"
        "key":"heport control key",                     // [ string ], exist when online on heport
        "comment":"gateway comment string"              // [ string ]
    }
    ```   

+ `network_device_listv[ username, network identify  ]` **get the all network device infomation of username**, *succeed return talk to describes, failed return NULL, error return terror*   
    ```json
    // Attributes introduction of talk by the method return  
    {
        "device mac identify":                        // [ string ]  
        {
            // ... more attrubtes, detail same network_device_view return
        }
        // more device...
    }
    ```   

+ `network_device_add[ username, network identify, device mac identify, [endpoint ip], [endpoint network], [endpoint netmask], [gateway type ]` **add a device to network**, *succeed return tture, failed return tfalse, error return terror*   

+ `network_device_delete[ username, network identify, device mac identify ]` **delete a device from network**, *succeed return tture, failed return tfalse, error return terror*   

