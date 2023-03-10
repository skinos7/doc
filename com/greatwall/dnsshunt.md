***
## Management dns shunt
Manage DNS domain shunt through this component

#### Configuration( greatwall@dnsshunt )
```json
{
    "status":"enable or disable this function",    // [ "disable", "enable" ]
    "rule":
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

