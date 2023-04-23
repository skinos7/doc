
***
## Management of ZeroTier Interface
Management of ZeroTier Interface

#### Configuration( sdwan@zt )
**sdwan@zt** is first ZeroTier Interface
**sdwan@zt2** is second ZeroTier Interface

```json
// Attributes introduction 
{
    "status":"start at system startup",     // [ "disable", "enable" ]
    "extern":"extern ifname",               // [ "disable", "", "ifname@wan", "ifname@lte", ... ],
                                                                // "disable" or space for none
                                                                // "" for is defdault gateway
                                                                // "ifname@wan", "ifname@lte", ... for specified extern interface

    "identify":"network identify",          // [ string ]

    // route attributes
    "masq":"share interface address to access",     // [ disable, enable ]
    "defaultroute":"set it default route",          // [ disable, enable ]
    "route_table":                                  // you can custom the route rule on this connect, vaild when "defaultroute" is "disable"
    {
        "route rule name":                          // [ string ]
        {
            "target":"destination address",           // [ string ], ip address or network
            "mask":"destination network mask"         // [ string ]
        }
        // ...more route rule
    },
    "gw":"default gateway",                      // [ ip address ]
    "custom_dns":"custom the dns server",        // [ disable, enable ]
    "dns":"dns address",                         // [ ip address ], vaild when "custom_dns" be "enable"
    "dns2":"backup dns address"                  // [ ip address ], vaild when "custom_dns" be "enable"
}
```

Examples, show all the configure
```shell
sdwan@zt
{
    "status":"enable",                 // start this service at system startup
    "identify":"ac079f73c6ece036"      // join the ac079f73c6ece036
}
```  

Examples, modify the network identify for join
```shell
sdwan@zt:identify=b6079f73c6ecee36
ttrue
```  

Examples, disable the sdwan@zt
```shell
sdwan@zt:status=disable
ttrue
```  

