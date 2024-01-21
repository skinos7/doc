
***
## device port API
component name is devport, user use the component methods to get the gateway report infomation
*all methods need username*

#### **Methods**

+ `list[ username, [gateway model] ]` **get the gateway list of username**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "gateway mac idenfify":                         // [ string ]:{}
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
            "mac":"gateway MAC address",                    // [ mac address ]
            "macid":"gateway MAC identify or serial id",    // [ string ]
            "model":"gateway model",                        // [ string ]
            "cmodel":"gateway custom model",                // [ string ]
            "oem":"OEM packet size",                        // [ number ]
            "magic":"gateway magic identify"                // [ string ]
            "datecode":"gateway datecode",                  // [ string ]
            "cfgversion":"gateway configure version",       // [ string ]
            "wui_port":"gateway wui port",                  // [ number ]
            "telnet_port":"gateway telnet port",            // [ number ]
            "ssh_port":"gateway ssh port",                  // [ number ]
            "local_ip":"gateway local ip address",          // [ ip address ]
            "comment":"gateway comment string",             // [ string ]
            "heport":                                       // heport information
            {
                "online":"online time",                              // [ string ], HH:MM:SS:Day
                "fd":"file number",                                  // [ number ]
                "addr":"gateway connected ip",                       // [ ip address ]
                "port":"gateway connected port",                     // [ number ]
                "key":"control key"                                  // [ string ]
            }
        }
        // ... more gateway
    }
    ```

+ `add[ username, gateway mac identify, [comment] ]` **add a gateway**, *succeed return tture, failed return tfalse, error return terror*

+ `delete[ username, gateway mac identify ]` **delete a gateway**, *succeed return tture, failed return tfalse, error return terror*

+ `status[ username, gateway mac identify ]` **get the gateway information**, *succeed return talk to describes, failed return NULL, error return terror*
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
            "key":"control key"                                  // [ string ]
        },
        "pport":"port proxy connection"    // [ number ]
    }
    ```

+ `getconfig[ username, gateway mac identify ]` **get the gateway basic configure**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    // that save at $user/dev/$macid/config.json
    {
        "cfgversion":"gateway configure version",       // [ string ]
        "comment":"gateway comment string"              // [ string ]
        "g2gid":"gateway to gateway identify"           // [ string ]
    }
    ```
+ `setconfig[ username, gateway mac identify, {gateway configure} ]` **set the gateway basic configure**, *succeed return tture, failed return tfalse, error return terror*
    ```json
    // Attributes introduction of talk by the method parameter of {gateway configure}
    {
        "cfgversion":"gateway configure version",       // [ string ]
        "comment":"gateway comment string"              // [ string ]
        "g2gid":"gateway to gateway identify"           // [ string ]
        // ... more configure, detail same getconfig return
    }
    ```



+ `map[ username, gateway mac identify, local_ip, local_port, [ protocol ] ]` **map a gateway local port to server**, *succeed return string describe the server port, failed return tfalse, error return terror*

+ `unmap[ username, gateway mac identify, port, [ protocol ] ]` **map a gateway local port to server**, *succeed return tture, failed return tfalse, error return terror*

+ `map_list[ username, gateway mac identify, [ protocol ] ]` **get the all map rule**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    // that save at $user/tcpamp.json(TCP) or $user/udpamp.json(udp)
    {
        "server port":                           // [ number ]:{}
        {
            "port":"server port",                     // [ number ]
            "macid":"gateway mac identify",           // [ string ]
            "hand_ip":"gateway local ip",             // [ ip address ]
            "hand_port":"gateway local port",         // [ number ]
            "app":"application type"                  // [ "other", "telnet", "ssh", "http" ]
        }
        // ... more map rule
    }
    ```

+ `map_add[ username, gateway mac identify, local_ip, local_port, [ protocol ], [ app ] ]` **add a map rule**, *succeed return ttrue, failed return tfalse, error return terror*

+ `unmap_delete[ username, gateway mac identify, port, [ protocol ] ]` **delete a map rule**, *succeed return tture, failed return tfalse, error return terror*

+ `ttyd_telnet[ username, port ]` **run the ttyd use telnet on a port**, *succeed return tture, failed return tfalse, error return terror*

+ `ttyd_ssh[ username, port ]` **run the ttyd use SSH on a port**, *succeed return tture, failed return tfalse, error return terror*

+ `access_telnet[ username, gateway mac identify, local_ip, local_port ]` **map a telnet to ttyd**, *succeed return string describe the server port, failed return tfalse, error return terror*

+ `access_ssh[ username, gateway mac identify, local_ip, local_port ]` **map a SSH to ttyd**, *succeed return string describe the server port, failed return tfalse, error return terror*



+ `firmware_list[ username ]` **get the gateway firmwre list of username**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    // that file save at $user/firmware
    {
        "firmware file name":                        // [ string ]:{}
        {
            "dir":"firmware directory",                   // [ string ]
            "custom":"firmware custom identify",          // [ string ]
            "scope":"firmware scope identify",            // [ string ]
            "version":"firmware version",                 // [ string ]
            "zz":"firmware file name"                     // [ string ]
        }
        // ... more firmware
    }    
    ```

+ `firmware_add[ username, pathname ]` **add a firmware file**, *succeed return tture, failed return tfalse, error return terror*

+ `firmware_delete[ username, pathname ]` **delete a firmware**, *succeed return tture, failed return tfalse, error return terror*



+ `g2g_list[ username ]` **get the g2g network list of username**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return  
    // that file save at $user/g2gnet.json
    {
        "g2g network identify":                    // [ string ]:
        {
            "net":"gateway network",                       // [ network ]
            "mask":"gateway netmask",                      // [ netmask ]
            "gateway":                                     // gateway settings here
            {
                "gateway macid":                                 // [ string ]  
                {
                    "id":"gateway identify",                     // [ number ]
                    "master":"Traffic transfer station",         // [ "disable", "enable" ]
                    "net":"gateway local network",               // [ network ]
                    "mask":"gateway local netmask"               // [ netmask ]
                }
                // more gateway...
            }
        }
        // more g2g network...
    }
    ```

+ `g2g_add[ username, g2g network identify ]` **add a g2g network**, *succeed return tture, failed return tfalse, error return terror*

+ `g2g_delete[ username, g2g network identify ]` **delete a g2g network**, *succeed return tture, failed return tfalse, error return terror*


