***
## Policy based routing
Management of policy based routing

#### Configuration( forward@rule )

```json
// Attributes introduction 
{
    "rule name ":                                                      // [ string ]
    {
        "markid":"select the packet use markid",                       // [ 1-4294967295 ]
                                                                            // Less than 100 is reserved for the system
                                                                            // You are advised to use more than 100 for user-defined rules
        "srcifname":"select the packet use source interface",          // [ string ], For example ifname@lan
        "src":"select the packet use source ip address",               // [ ip address ]
        "srcmask":"select the packet use source mask of ip address",   // [ netmask ]
        
        "tid":"which route table to go to",                            // [ 0-255 ]
                                                                            // 0 for local table
                                                                            // 253 for default table
                                                                            // 254 for main table
                                                                            // 255 for local table
                                                                            // Less than 100 is reserved for the system
                                                                            // You are advised to use more than 100 for user-defined rules(And avoid 253,254,255)
        "pref":"rule's priority",                                      // [ 0-4294967295 ], The smaller, the higher
                                                                            // 0 for local table priority
                                                                            // 32766 for main table priority
                                                                            // 50000 for default table priority
                                                                            // default is 40000

        "nat":"NAT address",           // Not Implemented
        "action":"processing mode",    // Not Implemented, [ prohibit, reject, unreachable]
        "cid":"Class ID"               // Not Implemented

    }
    // ...more rule
}
```

Examples, show current all of policy rule
```shell
forward@rule
{
    "myCustom1":                       # rule name is myCustom1
    {                                  # packet from ifname@lan and source address is 1.1.1.1/255.255.255.255 route to route table 101, priority is 38000
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
