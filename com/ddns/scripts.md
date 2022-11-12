
***
## DDNS client agent Management
manage ddns client

#### Configuration( ddns@scripts )

```json
// Attributes introduction 
{
    "client":
    {
        "status":"client status",                                   // [ disable, enable ]
        "extern":"extern ifname",                                   // [ string ]
        "isp":"internet service provicserver address",              // [ string ]
        "domain":"domain name",                                     // [ string ]
        "username":"username",                                      // [ string ]
        "password":"password",                                      // [ string ]
        "check_interval":"check the changes interval",              // [ number ], the unit is second
        "retry_interval":"retry delay second when failed"           // [ number ], the unit is second
    },
    "client2":
    {
        "status":"client status",                                   // [ disable, enable ]
        "extern":"extern ifname",                                   // [ string ]
        "isp":"internet service provicserver address",              // [ string ]
        "domain":"domain name",                                     // [ string ]
        "username":"username",                                      // [ string ]
        "password":"password",                                      // [ string ]
        "check_interval":"check the changes interval",              // [ number ], the unit is second
        "retry_interval":"retry delay second when failed"           // [ number ], the unit is second
    }
}
```
Examples, show all the configure
```shell
ddns@scripts
{
    "client":
    {
        "status":"enable",                         # enable the ddns
        "isp":"dyn.com",                           # isp is dyn.com
        "username":"dimmalex",                     # username is dimmalex
        "password":"87654321"                      # password is 87654321
    }
}

```  
Examples, disable ddns client
```shell
ddns@scripts:client/status=disable
ttrue
```   
Examples, modify the password of client
```shell
ddns@scripts:client/password=12345678
ttrue
```  
