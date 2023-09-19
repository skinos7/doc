
***
## Management portal of web page
Administration of equipment Management portal web page

#### Configuration( portal@show )

```json
// Attributes introduction 
{
    "status":"start at system startup",                 // [ "disable", "enable" ]
    "extern":"extern ifname",                           // [ "ifname@lte", "ifname@lte2", "ifname@wan", ... ], default is the default gateway
    "local":"local ifname",                             // [ "ifname@lan", "ifname@lan2", "ifname@lan3", ... ], default is the ifname@lan

    "port":"service port",                              // [ number ], 1-65535, default is 80
    "sslport":"https port",                             // [ number ], 1-65535, default is 443

    "redirect_page":"auth ok to redirect URL",          // [ string ]
    "ignore_ethernet":"ignore or not",                  // [ "disable", "enable" ]
    "login_timeout":"timeout to need auth again",       // [ number ], the unit is second
    "idle_timeout":"idle timeout to need auth again",   // [ number ], the unit is second

    "white_client":"mac or ip to ignore to auth",       // [ string ], ip or mac, gap use ;
    "white_address":"interval to ignore to auth"        // [ string ], ip, gap use ;

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


