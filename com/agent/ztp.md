***
## Zero touch provision management
Zero touch provision from gather, dhcp, http, mail, U/TF storage

#### Configuration( agent@ztp )
```json
{
    "url":"disable or enable url for ztp from remote server",       // [ "disable", "enable" ]
    "url_cfg":
    {
        "location":"ZTP json url location",                              // [ string ]
        "username":"url username",                                       // [ string ]
        "password":"url password"                                        // [ string ]
    },

    "dhcp":"disable or enable listen for ztp from dhcp",            // [ "disable", "enable" ]
    "dhcp_cfg":
    {
    },

    "storage":"disable or enable search the storage for ztp",       // [ "disable", "enable" ]
    "storage_cfg":
    {
        "path":"ZTP json pathname"                                      // [ string ]
    },

    // query infomation for ztp.status return
    "query_cfg":
    {
        "query command":""                                              // [ string ]:""
        // ... more command
    }
}
```
Examples, show all the configure
```shell
agent@ztp
{
}
```  
Examples, enable the JSON command accept
```shell
agent@ztp:dhcp=enable
ttrue
```  

#### **Methods**

+ `config[ {ztp json} ]` **configure a device by ztp json or location of ztp json**, *no need to update return ttrue, failed or need to update return tfalse, error return terror*
    ```json
    // Attributes introduction of talk that pass to interface
    {
        "scope":"equipment scope identify",              // [ string ]
        "version":"equipment version",                   // [ string ]
        "zz":"firmware url",                             // [ URL ]
        "zz_username":"firmware url username",           // [ string ]
        "zz_password":"firmware url password",           // [ string ]
    
        "cfgversion":"configure version",                // [ string ]
        "tar":"configure url",                           // [ URL ]
        "tar_username":"configure url username",         // [ string ]
        "tar_password":"configure url password",         // [ string ]
    
        "oem":"oem size",                                // [ number ]
        "dtar":"oem url",                                // [ URL ]
        "dtar_username":"oem url username",              // [ string ]
        "dtar_password":"oem url username",              // [ string ]
    
        "mode":"equipment operator mode"                 // < "ap", "wisp", "nwisp", "gateway", "dgateway", "misp", "nmisp", "dmisp", "mix" >
                                                            // "ap": access point
                                                            // "wisp": 2.4G Wireless Internet Service Provider connection
                                                            // "nwisp": 5.8G Wireless Internet Service Provider connection( need the board support 5.8G wirless baseband)
                                                            // "gateway": wire WAN gateway
                                                            // "dgateway": Dual wire WAN gateway
                                                            // "misp": LTE Mobile Internet Service Provider connection( need the board support LTE baseband)
                                                            // "nmisp": Next LTE/NR Mobile Internet Service Provider connection( need the board support LTE/NR baseband)
                                                            // "dmisp": Dual LTE/NR Mobile Internet Service Provider connection( need the board support two LTE/NR baseband)
                                                            // "mix": custom mix connection from multiple internet connection
    }    
    ```
    ```shell
    # examples, configure a device by ztp json
    agent@ztp.config[ {"mode":"gateway"} ]
    ttrue
    ```
    # examples, configure a device by location of ztp json
    agent@ztp.config[ ftp://user:12345678@ftp.wmdevice.com/test/ztp.json ]
    ttrue
    ```

+ `status[ {query json} ]` **get the equipent ztp infomation**, *succeed return talk to describes basic infomation, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk that pass to interface
    {
        "query command":""                                              // [ string ]:""
        // ... more command
    }    
    // Attributes introduction of talk by the method return
    {
        "ip":"ztp ip address",                           // [ ip address ]

        "sn":"equipment serial number",                  // [ string ]
        "mac":"equipment MAC address",                   // < MAC address >

        "datacode":"equipment date of manufacture",      // [ string ]
        "model":"equipment model",                       // [ string ]
        "cmodel":"equipment custom model",               // [ string ]
        "features":"equipment features",                 // < string >
        "language":"equipment language",                 // [ cn, en, jp, ... ], language code in two letter

        "scope":"equipment scope identify",              // [ string ]
        "version":"equipment version",                   // [ string ]

        "cfgversion":"configure version",                // [ string ]

        "oem":"oem size",                                // [ number ]
        
        "mode":"equipment operator mode"              // < "ap", "wisp", "nwisp", "gateway", "dgateway", "misp", "nmisp", "dmisp", "mix" >
                                                         // "ap": access point
                                                         // "wisp": 2.4G Wireless Internet Service Provider connection
                                                         // "nwisp": 5.8G Wireless Internet Service Provider connection( need the board support 5.8G wirless baseband)
                                                         // "gateway": wire WAN gateway
                                                         // "dgateway": Dual wire WAN gateway
                                                         // "misp": LTE Mobile Internet Service Provider connection( need the board support LTE baseband)
                                                         // "nmisp": Next LTE/NR Mobile Internet Service Provider connection( need the board support LTE/NR baseband)
                                                         // "dmisp": Dual LTE/NR Mobile Internet Service Provider connection( need the board support two LTE/NR baseband)
                                                         // "mix": custom mix connection from multiple internet connection
    }    
    ```
    ```shell
    # examples, get the equipent ztp infomation
    agent@ztp.status
    {
        "mac":"00:03:7F:12:00:00",
        "model":"D218P",
        "cmodel":"ICR-W402",
        "language":"cn",
        "scope":"std",
        "version":"v7.3.0622",
        "cfgversion":"19700105",
        "mode":"wisp"
    }
    ```



