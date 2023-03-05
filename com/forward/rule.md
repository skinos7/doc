***
## Policy based routing
Management of policy based routing

#### Configuration( forward@rule )

```json
// Attributes introduction 
{
    "rule name":                                                       // [ string ], user can custom the rule name
    {
        "markid":"select the packet use markid",                           // [ nubmer ], range of 1-4294967295
                                                                                // Less than 100 is reserved for the system
                                                                                // You are advised to use more than 100 for user-defined rules
            "srcifname":"select the packet use source interface",          // [ "ifname@lan", "ifname@lan2", ... ], ifname
            "src":"select the packet use source ip address",               // [ ip address/network ]
            "srcmask":"select the packet use source mask of ip address",   // [ netmask ], necessary when "src" be network
            "tid":"which route table to go to",                            // [ number ], range of 0-255
                                                                                // 0 for local table
                                                                                // 253 for default table
                                                                                // 254 for main table
                                                                                // 255 for local table
                                                                                // Less than 100 is reserved for the system
                                                                                // You are advised to use more than 100 for user-defined rules(And avoid 253,254,255)
            "pref":"rule's priority",                                      // [ nubmer ], range of 0-4294967295, The smaller, the higher
                                                                                // 0 for local table priority
                                                                                // 32766 for main table priority
                                                                                // 50000 for default table priority
                                                                                // default is 40000

            "nat":"NAT address",           // Not Implemented
            "action":"processing mode",    // Not Implemented, [ "prohibit", "reject", "unreachable" ]
            "cid":"Class ID"               // Not Implemented
    }
    // ... more rule
}
```
Examples, show current all of policy rule
```shell
forward@rule
{
    "myCustom1":                       # rule name is myCustom1
    {                                  # packet from ifname@lan and source address is 1.1.1.1 route to route table 101, priority is 38000
        "srcifname":"ifname@lan",
        "src":"1.1.1.1",
        "srcmask":"255.255.255.255",
        "tid":"101",
        "pref":"38000"
    },
    "youCustom":                       # rule name is youCustom
    {                                  # packet from ifname@lan and markid is 300 route to route table 102, default priority is 40000
        "srcifname":"ifname@lan",
        "markid":"300",
        "tid":"102"
    }
}
```  

#### **Methods**

+ `status[]` **get the current policy rule**, *succeed return talk to describes infomation, failed reeturn NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "rule name",                                                       // [ string ], user can custom the rule name
        {
            "markid":"select the packet use markid",                           // [ nubmer ], range of 1-4294967295
                                                                                    // Less than 100 is reserved for the system
                                                                                    // You are advised to use more than 100 for user-defined rules
                "srcifname":"select the packet use source interface",          // [ "ifname@lan", "ifname@lan2", ... ], ifname
                "src":"select the packet use source ip address",               // [ ip address/network ]
                "srcmask":"select the packet use source mask of ip address",   // [ netmask ], necessary when "src" be network
                "tid":"which route table to go to",                            // [ number ], range of 0-255
                                                                                    // 0 for local table
                                                                                    // 253 for default table
                                                                                    // 254 for main table
                                                                                    // 255 for local table
                                                                                    // Less than 100 is reserved for the system
                                                                                    // You are advised to use more than 100 for user-defined rules(And avoid 253,254,255)
                "pref":"rule's priority",                                      // [ nubmer ], range of 0-4294967295, The smaller, the higher
                                                                                    // 0 for local table priority
                                                                                    // 32766 for main table priority
                                                                                    // 50000 for default table priority
                                                                                    // default is 40000
        }
        // ... more rule
    }
    ```
    ```shell
    # examples, get the first lte network infomation
    forward@rule.status
    {
        "myCustom1":                       # rule name is myCustom1
        {                                  # packet from ifname@lan and source address is 1.1.1.1 route to route table 101, priority is 38000
            "srcifname":"ifname@lan",
            "src":"1.1.1.1",
            "srcmask":"255.255.255.255",
            "tid":"101",
            "pref":"38000"
        },
        "youCustom":                       # rule name is youCustom
        {                                  # packet from ifname@lan and markid is 300 route to route table 102, default priority is 40000
            "srcifname":"ifname@lan",
            "markid":"300",
            "tid":"102"
        }
    }
    ```

+ `add[ name, [src], [srcmask], [srcifname], [markid], tid, [pref] ]` **add policy rule**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, add a rule named senser, make that source address 192.168.2.12 route to route table 1, priority is 33000
    forward@rule.add[ senser, 192.168.2.12, , , , 1, 33000 ]
    ttrue
    # examples, add a rule named video, make all other acess route to route table 2, priority is 33300
    forward@rule.add[ video, , , , , 2, 33000 ]
    ttrue
    ```

+ `delete[]` **delete policy rule**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, delete the policy rule named video
    forward@rule.delete[ video ]
    ttrue
    # examples, delete the policy rule named senser
    forward@rule.delete[ senser ]
    ttrue
    ```

