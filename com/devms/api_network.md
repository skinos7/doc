
***
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

+ `network_view[ username, network identify  ]` **get the network infomation of username**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return  
    {
        "net":"gateway network",                       // [ network ]
        "mask":"gateway netmask",                      // [ netmask ]
        "keepintval":"keeplive interval",              // [ number ], the unit is second
        "keepfailed":"keeplive failed times",          // [ number ]
        "master":"network master nubmer",          // [ number ]
        "branch":"network branch number",          // [ number ]
        "free":"network free client number",       // [ number ]
        "limit":"network limit client number",     // [ number ]
        "dyn":"network dyn client number"          // [ number ]
    }
    ```

+ `network_listv[ username  ]` **get the all network infomation of username**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return  
    // that file save at $user/network.json
    {
        "network identify":             // [ string]: {}
        {
            "net":"network endpoint net",              // [ network address ]
            "mask":"network endpoint netmask",         // [ netmask address ]
            "keepintval":"keeplive interval",          // [ number ], the unit is second
            "keepfailed":"keeplive failed times",      // [ number ]
            "master":"network master nubmer",          // [ number ]
            "branch":"network branch number",          // [ number ]
            "free":"network free client number",       // [ number ]
            "limit":"network limit client number",     // [ number ]
            "dyn":"network dyn client number"          // [ number ]
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
            "id":"gateway identify",                     // [ number ]
            "type":"gateway type",                       // [ "master", "branch" ]
            "net":"gateway local network",               // [ network ]
            "mask":"gateway local netmask",              // [ netmask ]

            "ip":"device endpoint ip address",           // [ ip address ]
            "pubkey":"public key",                       // [ string ], exist when device attach

            "attach":"online time",                    // [ string ], HH:MM:SS:DAY, exist when device attach
            "nattype":"device nat type",               // [ "8", "4", "2", "1" ], exist when device attach
            "peer":"device ip address",                // [ ip address ], exist when device attach
            "port":"device port"                       // [ port ], exist when device attach

            // more see "device_view"
        }
        // more device...
    }
    ```

+ `network_device_add[ username, network identify, device mac identify, [id/ip], [local network], [local netmask], [network type ]` **add a device to network**, *succeed return tture, failed return tfalse, error return terror*

+ `network_device_delete[ username, network identify, device mac identify ]` **delete a device from network**, *succeed return tture, failed return tfalse, error return terror*

