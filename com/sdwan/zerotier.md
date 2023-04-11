
***
## Management of zerotier
Administration of equipment zerotier

#### Configuration( sdwan@zerotier )

```json
// Attributes introduction 
{
    "status":"start at system startup",     // [ disable, enable ]
    "extern":"extern ifname",               // [ ifname@wan, ifname@lte, ... ], default is defdault gateway

    "secret":"secret string",               // [ string ]
    "port":"work port",                     // [ number ], default is 9993
    "network":
    {
        "network identify":"network comment"                 // [ string ]:[ string ]
        // ...more the network identify
    }
}
```

Examples, show all the configure
```shell
sdwan@zerotier
{
    "status":"enable",             # start this service at system startup

    "secret":"23238sdflkjsldf",
    "network":
    {
        "ac079f73c6ece036":                         // join the ac079f73c6ece036 and the secret is 23238sdflkjsldf
        {
        }
    }
}
```  

Examples, join a new network
```shell
sdwan@zerotier:network/b6079f73c6ecee36={}
ttrue
```  

Examples, leave a new network
```shell
sdwan@zerotier:network/b6079f73c6ecee36
ttrue
```  

Examples, disable the sdwan@zerotier
```shell
sdwan@zerotier:status=disable
ttrue
```  


