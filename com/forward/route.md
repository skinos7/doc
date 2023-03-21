***
## Route table management
Management of routes table

#### Configuration( forward@route )
```json
// Attributes introduction 
{
    "rule name":        // [ string ], user can custom the rule name
    {
        "target":"select the packet use source ip address",            // [ ip address, network ]
        "mask":"select the packet use source mask of ip address",      // [ netmask ], necessary when "target" be network
        "gw":"gateway ip address",                                     // [ ip address ]
        "metric":"route hop",                                          // [ number ]
        "ifname":"select the packet output interface",                 // [ "ifname@lan", "ifname@lan2", "ifname@wan", "ifname@lte", ... ], interface name
    }
    // ... more rule
}
```
Examples, show current all of route rule
```shell
forward@route
{
    "myCustomRule1":    # first rule name is "myCustomRule1"
    {                      # make dest 192.168.1.0/255.255.255.0 to ifname@wan's 192.168.8.22, mark the metric be 2
        "target":"192.168.1.0",
        "mask":"255.255.255.0",
        "gw":"192.168.8.22",
        "metric":"2",
        "ifname":"ifname@wan"
    }
    "youCustomRule":    # second rule name is "youCustomRule"
    {                      # make all access to ifname@lan's 192.168.9.22
        "gw":"192.168.9.22",
        "ifname":"ifname@lan"
    }
}
```  


#### **Methods**

+ `status[]` **get the current route rule**, *succeed return talk to describes infomation, failed reeturn NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "rule name":        // [ string ], user custom the rule name, the system rule start with "~"
        {
            "target":"select the packet use source ip address",            // [ ip address, network ]
            "mask":"select the packet use source mask of ip address",      // [ netmask ], necessary when "target" be network
            "gw":"gateway ip address",                                     // [ ip address ]
            "metric":"route hop",                                          // [ number ]
            "ifname":"select the packet output interface",                 // [ "ifname@lan", "ifname@lan2", ... ], interface name
            "netdev":"network device",                                     // [ string ]
            "flags":"rule flags",                                          // [ string ]
            "metric":"route hop",                                          // [ number ]
            "ref":"reference number",                                      // [ nubmer ]
            "use":"use number",                                            // [ number ]
            "status":"rule state"                                          // [ "up", "down" ], "up" for enable, "down" for disable
        }
        // ... more rule
    }
    ```
    ```shell
    # examples, get the current route rule
    forward@route
    {
        "myCustomRoute1":             // this is user add rule named "myCustomRoute1"
        {
            "target":"192.168.0.0",
            "mask":"255.255.255.0",
            "gw":"192.168.8.2",
            "metric":"2",
            "ifname":"ifname@wan",
            "device":"eth0.2",
            "flags":"1",
            "metric":"2",
            "ref":"0",
            "use":"0",
            "status":"up"
        },
        "~auto1":                    // this is system rule
        {
            "target":"127.0.0.1",
            "mask":"255.255.255.0",
            "gw":"0.0.0.0",
            "device":"lo",
            "flags":"1",
            "metric":"0",
            "ref":"0",
            "use":"0",
            "status":"up"
        }
    }
    ```

+ `add[ name, [target], [mask], [gateway], [ifname], [metric] ]` **add route rule**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, add a rule named office1, make that address 192.168.2.12 route to ifname@lan's 192.168.9.40
    forward@route.add[ office1, 192.168.2.12, 255.255.255.0, 192.168.9.40, ifname@lan, ]
    ttrue
    # examples, add a rule named office2, make that all ddress route to ifname@lan's 192.168.9.41
    forward@route.add[ office2, , , 192.168.9.41, ifname@lan, ]
    ttrue
    ```

+ `delete[ name ]` **delete route rule**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, delete the custom route named office2
    forward@route.delete[ office2 ]
    ttrue
    # examples, delete the custom route named office1
    forward@route.delete[ office1 ]
    ttrue
    ```

