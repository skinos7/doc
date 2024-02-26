***
## Factory skinos device at local network
Factory skonos device at the local network

#### Configuration( gather@factory )
```json
// Attributes introduction
{
    "status":"beacon for search skinos agent",  // [ "disable", "enable" ]
    "port":"beacon udp port",                   // [ nubmer ]
    "interval":"beacon interval",               // [ nubmer ], the unit is second
    "group":"search group name",                // [ string ], default is group of "default"
    "ip":"beacon network ip",                   // [ IP address ], default is 192.168.200.1
    "mask":"beacon network netmask",            // [ network mask ], default is 255.255.255.0

    "timeout":"timeout for online",                               // [ number ], defdault is 12 second
    "startip":"IP addresses pool start",                          // [ IP address ], default is 192.168.200.2
    "endip":"IP address poll end",                                // [ IP address ], default is 192.168.200.254
    "gw":"Assign gateway to found devices",                       // [ IP address ]
    "dns":"Assign dns to found devices"                           // [ IP address ]

    "location":"location of firmware",          // [ "memory", "interval", "storage", "sdaxxx" ]
                                                    // "memory" for stored in the memory and will be lost upon restart
                                                    // "interval" for stored in the internal flash. Strong columns are not recommended in the internal program area, which may cause corruption  
                                                    // "storage" for stored in external storage
                                                    // "sdaxxx" for sda starts with a specified mount disk
                                                    // stored in xxxx-syslog.txt file in the root directory when "location" is internal, storage, starts with sda
    "sync":"sync the configure and firmware function",   // [ "disable", "enable" ]
    "sync_cfg":                                          // configure and firmware 
    {
        "datecode":"upgrade datecode",                       // [ string ], defualt is no modify
        "model":"upgrade model",                             // [ string ], defualt is no modify 
        "cmodel":"upgrade custom model",                     // [ string ], defualt is no modify 
        "features":"upgrade features",                       // [ string ], defualt is no modify,
        "language":"upgrade language",                       // [ string ], defualt is no modify, cn is chinese, en is engish

        "scope":"current upgrade firmware scope"             // [ string ]
        "version":"current upgrade firmware version",        // [ string ]
        "zz":"current upgrade firmware",                     // [ string ]
        "eeprom":"current upgrade eeprom",                   // [ string ]

        "oem":"oem file size",                               // [ string ]
        "dtar":"oem file url location",                      // [ string ]

        "cfgversion":"configure version",                    // [ string ]
        "tar":"configure file url location"                  // [ string ]
    },

    "check":"check the client value",                 // [ "disable", "enable" ]
    "check_cfg":                                      // need check some item
    {
        "query command":"need or not"                        // [ string ]:[ "disable", "enable" ]
        // ... more query command
    },

    "assignmac":"assign mac function",                   // [ "disable", "enable" ]
    "assignmac_cfg":                                     // assign mac configure
    {
        "start":"start mac",                                 // [ start mac string ]
        "hops":"how many one jump"                           // [ number ]
    },

    "assignsn":"assign serial number function",          // [ "disable", "enable" ]
    "assignsn_cfg":                                      // assign serial number configure
    {
        "prefix":"serial number prefix",                     // [ string ]
        "start":"serial nubmer start",                       // [ number ]
        "hops":"how many one jump"                           // [ number ]
    }
}
```
Examples, show all the configure
```shell
gather@factory
{
    "status":"enable"
    "port":"22222",
    "interval":"5",
    "group":"factory",
    "ip":"172.16.0.1",
    "mask":"255.255.0.0",

    "timeout":"15",
    "startip":"172.16.0.2",
    "endip":"172.16.254.254",
    "gw":"172.16.0.1",
    "dns":"172.16.0.1",
    
    "sync":"enable",
    "sync_cfg":
    {
        "datecode":"20230616",
        "model":"3218",
        "cmodel":"WL-R320",
        "features":"g",
        "language":"en",

        "scope":"std",
        "version":"v7.3.0620",
        "zz":"tftp://172.16.0.1/mt7628_r600_std_v7.3.0620_wlinkr320.zz",
        "eeprom":"tftp://172.16.0.1/mt7628_r600_std_v7.3.0620.art",

        "oem":"1341",
        "dtar":"tftp://172.16.0.1/mt7628_r600_std_v7.3.0620.dtar",

        "cfgversion":"skinos23231-202321922323",
        "tar":"tftp://172.16.0.1/mt7628_r600_std_v7.3.0620.tar"
    },
    "check":"enable",
    "check_cfg":                                     // need check some item
    {
        "ifname@lte.status:imei":"enable",           // check the LTE IMIE
        "ifname@lte.status:iccid":"disable",         // don't check the LTE SIMCARD
        "ifname@lte.status:ip":"disable",            // don't check the LTE online
        "ifname@lte2.status:imei":"disable",         // don't check the LTE2 IMEI
        "ifname@lte2.status:iccid":"disable",        // don't check the LTE2 SIMCARD
        "ifname@lte2.status:ip":"disable",           // don't check the LTE2 online
        "land@machine.status:factory_mode":"enable"  // check the board on factory mode
    },
    "assignmac":"enable",
    "assignmac_cfg":
    {
        "start":"88:12:4E:30:43:00",
        "hops":"8"
    },
    "assignsn":"enable",
    "assignsn_cfg":
    {
        "prefix":"E3218R600202309",
        "start":"0001",
        "hops":"1"
    }
}
```  
Examples, disable the factory
```shell
gather@factory:status=disable
ttrue
```  

#### **Methods**

+ `list[]` **list all the found device**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "MAC Address":              [ mac address ]:{}
        {
            "ip":"IP Address",           [ ip address ]
            "time":"found time"          [ number ] UTC count nubmer

            "datecode":"upgrade datecode",                       // [ string ], defualt is no modify
            "model":"upgrade model",                             // [ string ], defualt is no modify 
            "cmodel":"upgrade custom model",                     // [ string ], defualt is no modify 
            "features":"upgrade features",                       // [ string ], defualt is no modify,
            "language":"upgrade language",                       // [ string ], defualt is no modify, cn is chinese, en is engish

            "scope":"current upgrade firmware scope"             // [ string ]
            "version":"current upgrade firmware version",        // [ string ]
            "oem":"oem file size",                               // [ string ]
            "cfgversion":"configure version"                     // [ string ]
        }
        // ... more device
    }    
    ```
    ```shell
    # examples, get all the found device
    gather@factory.list
    {
        "88124E200030":              # device is 88:12:4E:20:00:30
        {
            "time":"1608637542",        # found device at UTC 1608637542
            "ip":"192.168.200.2"        # device ip is 192.168.200.2
            "datecode":"20230616",
            "model":"3218",
            "cmodel":"WL-R320",
            "features":"g",
            "language":"en",

            "scope":"std",
            "version":"v7.3.0620",
            "oem":"1341",
            "cfgversion":"skinos23231-202321922323"
        },
        "00037F12CC70":              # device is 00:03:7F:12:CC:70
        {
            "time":"1608637542",        # found device at UTC 1608637542
            "ip":"192.168.200.3"        # device ip is 192.168.200.3
            "datecode":"20230616",
            "model":"3218",
            "cmodel":"WL-R320",
            "features":"g",
            "language":"en",

            "scope":"std",
            "version":"v7.3.0620",
            "oem":"1341",
            "cfgversion":"skinos23231-202321922323"
        }
    }  
    ```


+ `import_zz[ firmware filename ]` **import the firmware to synchronization**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, import firmware mt7628_d218_std_v7.2.0923.zz
    gather@factory.import_zz[ mt7628_d218_std_v7.2.0923.zz ]
    ttrue
    ```

+ `import_eeprom[ eerpom filename ]` **import the eeprom to synchronization**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, import eeprom file mt7628_d218_std_v7.2.0923.art
    gather@factory.import_eeprom[ mt7628_d218_std_v7.2.0923.art ]
    ttrue
    ```

+ `import_dtar[ default configure filename ]` **import the default configure to synchronization**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, import default configure file mt7628_d218_std_v7.2.0923.dtar
    gather@factory.import_dtar[ mt7628_d218_std_v7.2.0923.dtar ]
    ttrue
    ```

+ `import_tar[ configure filename ]` **import the configure to synchronization**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, import configure file skinos23231-202321922323.tar
    gather@factory.import_tar[ skinos23231-202321922323.dtar ]
    ttrue
    ```

