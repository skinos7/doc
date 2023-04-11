***
## RIP Management
manage RIP protocol service

#### Configuration( drouter@ripd )

```json
// Attributes introduction 
{
    "status":"RIP status",                                   // [ "disable", "enable" ]
    "password":"manage password",                            // [ string ]
    "ifname":                                                // ifname list
    {
        "ifname name":""                                     // [ "ifname@lan", "ifname@lan2", "ifname@lte", "ifname@lte2", ... ]:"",
        // ... more ifname
    }
}
```
Examples, show all the configure
```shell
drouter@ripd
{
    "status":"enable",               # ripd enable
    "password":"1212121212",         # password is 1212121212
    "ifname":                        # include the ifname@lte, ifname@wan, ifname@wan
    {
        "ifname@lte":"",
        "ifname@wan":"",
        "ifname@lan":""
    }
}
```  
Examples, disable 
```shell
drouter@ripd:status=disable
ttrue
```   
Examples, delete the ifname@lan
```shell
drouter@ripd:ifname/ifname@lan=
```
Examples, add the ifname@lan
```shell
drouter@ripd:ifname/ifname@lan=enable
```
