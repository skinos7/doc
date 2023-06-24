***
## Factory skinos device at local network
Factory skonos device at the local network

#### Configuration( gather@factory )
```json
// Attributes introduction
{
    "status":"beacon for search device",        // [ "disable", "enable" ]
    "port":"beacon udp port",                   // [ nubmer ]
    "interval":"beacon interval",               // [ nubmer ], the unit is second
    "group":"search group name",                // [ string ], default is group of "factory"
    "ip":"beacon network ip",                   // [ IP address ], default is 192.168.200.1
    "mask":"beacon network netmask",            // [ network mask ], default is 255.255.255.0

    "timeout":"timeout for online",                               // [ number ], defdault is 12 second
    "startip":"IP addresses pool start",                          // [ IP address ], default is 192.168.200.2
    "endip":"IP address poll end",                                // [ IP address ], default is 192.168.200.254
    "gw":"Assign gateway to found devices",                       // [ IP address ]
    "dns":"Assign dns to found devices"                           // [ IP address ]
    
    // will save to factory.txt, and pass to device that need use
    "config":
    {
        "datecode":"upgrade datecode",                   // [ string ], defualt is no modify
        "model":"upgrade model",                         // [ string ], defualt is no modify 
        "cmodel":"upgrade custom model",                 // [ string ], defualt is no modify 
        "features":"upgrade features",                   // [ string ], defualt is no modify,
        "language":"upgrade language",                   // [ string ], defualt is no modify, cn is chinese, en is engish

        "scope":"current upgrade firmware scope"         // [ string ]
        "version":"current upgrade firmware version",    // [ string ]
        "zz":"current upgrade firmware",                 // [ string ]
        "eeprom":"current upgrade eeprom",               // [ string ]

        "oem":"3345",
        "dtar":"tftp://10.0.0.3/wlinkr320.dtar",

        "cfgversion":"2232321212",
        "tar":"tftp://10.0.0.3/wlinkr320.tar",

        "test":
        {
            "ifname@lte":"enable",
            "ifname@lte2":"enable",
            "uart@serial":"enable",
            "uart@serial2":"enable",
            "arch@ethernet":"enable",
            "io@agent":"enable"
        }
    },
    "assignmac":"enable assign or not",
    "assignmac_cfg":
    {
        "start":"",
        "hops":"8"
    },
    "assignsn":"enable assign or not",
    "assignsn_cfgo":
    {
        "prefix":"",
        "start":"",
        "hops":"1"
    }
}
```
Examples, show all the configure
```shell
gather@factory
{
    "status":"enable",                     # enable the beacon for search device
    "port":"22222",                        # UDP port is 22222
    "ip":"172.32.0.1",                     # beacon network is 172.32.0.1/255.255.0.0
    "mask":"255.255.0.0",
    "dhcps":
    {
        "status":"enable",                 # enable Assign IP addresses to found devices
        "startip":"172.32.0.2",            # IP addresses pool start 172.32.0.2
        "endip":"172.32.254.254"           # IP addresses pool end 172.32.254.254
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
        }
        // ... more device
    }    
    ```
    ```shell
    # examples, get all the found device
    gather@beacon.list
    {
        "88124E200030":              # device is 88:12:4E:20:00:30
        {
            "time":"1608637542",        # found device at UTC 1608637542
            "ip":"192.168.200.2"        # device ip is 192.168.200.2
        },
        "00037F12CC70":              # device is 00:03:7F:12:CC:70
        {
            "time":"1608637542",        # found device at UTC 1608637542
            "ip":"192.168.200.3"        # device ip is 192.168.200.3
        }
    }  
    ```


