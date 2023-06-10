***
## Management dns shunt
Manage DNS domain shunt through this component

#### Configuration( greatwall@dnsshunt )
```json
{
    "status":"enable or disable this function",    // [ "disable", "enable" ]
    "wlist":                                       // White list to resolv on main and back ifname
    {
        "DNS domain":"comment text"                             // [ string ]:[ string ]
        // "":"" ... more rule
    },
    "rule":                                        // DNS shunts list
    {
        "DNS domain":"interface name"                           // [ string ]:[ "ifname@lte", "ifname@lte2" ]
        // "":"" ... more rule
    }
}
```
Examples, show all the configure
```shell
greatwall@dnsshunt
{
    "status":"enable",                    # enable the function
    "wlist":
    {
        "findauto.oss.qxwz.com":"enable",
        "findauto.api.qxwz.com":"enable"
    },
    "rule":
    {
        "www.baidu.com":"ifname@lte2"        allocation the traffic of aceess www.baidu.com to ifname@lte2
    }
}
```  
Examples, disable this function
```shell
greatwall@dnsshunt:status=disable
ttrue
```  
Examples, add the www.qq.com access to ifname@lte
```shell
greatwall@dnsshunt:rule/www.qq.com=ifname@lte
ttrue
```  
Examples, delete the www.qq.com access allocation
```shell
greatwall@dnsshunt:rule/www.qq.com=
ttrue
```  
Examples, add the www.163.com to white list
```shell
greatwall@dnsshunt:wlist/www.163.com=enable
ttrue
```  
Examples, delete the www.163.com from white list
```shell
greatwall@dnsshunt:wlist/www.163.com=
ttrue
```  

