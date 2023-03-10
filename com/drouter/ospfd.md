***
## OSPF Management
manage OSPF protocol service

#### Configuration( drouter@ospf )
```json
// Attributes introduction 
{
    "status":"OSPF status",                                  // [ "disable", "enable" ]
    "rfc1583":"OSPF status",                                 // [ "disable", "enable" ]
    "id":"OSPF Router-ID",                                   // [ string ]
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
drouter@ospfd
{
    "status":"enable",               # ripd enable
    "rfc1583":"disable",             # rfc1583 disale
    "id":"22",                       # OSPF Router-ID is 22
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
drouter@ospfd:status=disable
ttrue
```   
Examples, delete the ifname@lan
```shell
drouter@ospfd:ifname/ifname@lan=
```
Examples, add the ifname@lan
```shell
drouter@ospfd:ifname/ifname@lan=enable
```
