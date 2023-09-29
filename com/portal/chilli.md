
***
## Management chilli portal of web page
Administration of equipment Management chilli portal web page

#### Configuration( portal@chilli )

```json
// Attributes introduction 
{
    "status":"start at system startup",                 // [ "disable", "enable" ]
    "extern":"extern ifname",                           // [ "ifname@lte", "ifname@lte2", "ifname@wan", ... ], default is the default gateway
    "local":"local ifname",                             // [ "ifname@lan", "ifname@lan2", "ifname@lan3", "wifi@nssid", "wifi@assid, "... ], default is the wifi@nssid

    "ip":"chilli interface ip address",                 // [ ip address ]
    "mask":"chilli interface netmask",                  // [ netmask ]
    "network":"chilli interface network",               // [ network ]
    "dns":"dns server",                                 // [ ip address ]
    "dns2":"dns server",                                // [ ip address ]

    "port":"chilli service port",                       // [ number ], 1-65535
    "uiport":"chilli ui port",                          // [ number ], 1-65535

    "radius_nasid":"Radius NAS Identify",               // [ string ]
    "radius_server":"Radius server",                    // [ ip address ]
    "radius_server2":"Radius server",                   // [ ip address ]
    "radius_secret":"Radius server key",                // [ string ]
    "radius_authport":"Radius auth port",               // [ number ], 1-65535
    "radius_acctport":"Radius account port",            // [ number ], 1-65535
    
    "uam_format":"UMA Portal URL",                      // [ string ]
    "uam_homepage":"UMA Homepage URL",                  // [ string ]
    "uam_secret":"UMA secret",
    "uam_allowed":"UMA allowed address",                // [ string ], Multiple addresses are separated by space
    "uam_domains":"UMA allowed domain",                 // [ string ], Multiple domains are separated by space

    "defaults_opt":"defaults custom options",            // [ string ], Multiple options are separated by semicolons
    "local_opt":"local.conf custom options"              // [ string ], Multiple options are separated by semicolons
}
```

Examples, show all the configure
```shell
portal@show
{
    "status":"enable",             # start this service at system startup
    "port":"8080"                  # service port 8080
}
```  
Examples, modify the port of portal web page server
```shell
portal@show:port=2222
ttrue
```  
Examples, disable the portal web page server
```shell
portal@show:status=disable
ttrue
```  

