***
## Custom routes table management
Management of custom routes table

#### Configuration( forward@routes )
```json
// Attributes introduction 
{
    "rule name":        // [ string ], user can custom the rule name
    {
        "tid":"which route table to go to",                            // [ number ], range of 0-255
                                                                                // 0 for local table
                                                                                // 253 for default table
                                                                                // 254 for main table
                                                                                // 255 for local table
                                                                                // Less than 100 is reserved for the system
                                                                                // You are advised to use more than 100 for user-defined rules(And avoid 253,254,255)

        "target":"select the packet use source ip address",            // [ ip address, network ]
        "mask":"select the packet use source mask of ip address",      // [ netmask ], necessary when "target" be network
        "gw":"gateway ip address",                                     // [ ip address ]
        "metric":"route hop",                                          // [ number ]
        "ifname":"select the packet output interface",                 // [ "ifname@lan", "ifname@lan2", ... ], interface name
    }
    // ... more rule
}
```
Examples, show current all of custom routes rule
```shell
forward@routes
{
    "myCustomRule1":    # first rule name is "myCustomRule1"
    {                      # add the route rule to tid 101, make dest 192.168.0.0/255.255.255.0 to ifname@wan's 192.168.8.2, mark the metric be 2
        "tid":"101",
        "target":"192.168.0.0",
        "mask":"255.255.255.0",
        "gw":"192.168.8.2",
        "metric":"2",
        "ifname":"ifname@wan"
    }
    "youCustomRule":    # second rule name is "youCustomRule"
    {                      # add the route rule to tid 102, make all access to ifname@lan's 192.168.9.2
        "tid":"102",
        "gw":"192.168.9.2",
        "ifname":"ifname@lan"
    }
}
```  


#### **Methods**

+ `status[]` **get the current custom routes rule**, *succeed return talk to describes infomation, failed reeturn NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "rule name":        // [ string ], user custom the rule name
        {
            "tid":"which route table to go to",                            // [ number ], range of 0-255
                                                                                    // 0 for local table
                                                                                    // 253 for default table
                                                                                    // 254 for main table
                                                                                    // 255 for local table
                                                                                    // Less than 100 is reserved for the system
                                                                                    // You are advised to use more than 100 for user-defined rules(And avoid 253,254,255)
    
            "target":"select the packet use source ip address",            // [ ip address, network ]
            "mask":"select the packet use source mask of ip address",      // [ netmask ], necessary when "target" be network
            "gw":"gateway ip address",                                     // [ ip address ]
            "metric":"route hop",                                          // [ number ]
            "ifname":"select the packet output interface",                 // [ "ifname@lan", "ifname@lan2", ... ], interface name
        }
        // ... more rule
    }
    ```
    ```shell
    # examples, get the current custom routes rule
    forward@routes
    {
        "myCustomRule1":    # first rule name is "myCustomRule1"
        {                      # add the route rule to tid 101, make dest 192.168.0.0/255.255.255.0 to ifname@wan's 192.168.8.2, mark the metric be 2
            "tid":"101",
            "target":"192.168.0.0",
            "mask":"255.255.255.0",
            "gw":"192.168.8.2",
            "metric":"2",
            "ifname":"ifname@wan"
        }
        "youCustomRule":    # second rule name is "youCustomRule"
        {                      # add the route rule to tid 102, make all access to ifname@lan's 192.168.9.2
            "tid":"102",
            "gw":"192.168.9.2",
            "ifname":"ifname@lan"
        }
    }
    ```

+ `add[ name, tid, [target], [mask], [gateway], [ifname], [metric] ]` **add custom routes rule**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, add a rule named office1 to table 105, make that address 192.168.2.12 route to ifname@lan's 192.168.9.40
    forward@routes.add[ office1, 105, 192.168.2.12, 255.255.255.0, 192.168.9.40, ifname@lan, ]
    ttrue
    # examples, add a rule named office2 to table 105, make that all ddress route to ifname@lan's 192.168.9.41
    forward@routes.add[ office2, 105, , , 192.168.9.41, ifname@lan, ]
    ttrue
    ```

+ `delete[ name ]` **delete custom routes table rule**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, delete the custom route named office2
    forward@routes.delete[ office2 ]
    ttrue
    # examples, delete the custom route named office1
    forward@routes.delete[ office1 ]
    ttrue
    ```

