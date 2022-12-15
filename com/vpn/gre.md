***
## Management of GRE tunnel
Management of GRE tunnel

#### Configuration( vpn@gre )
**vpn@gre** is first GRE tunnel
**vpn@gre2** is second GRE tunnel

#### **配置** 
```json
{
    "status":"client status",                    // [ disable, enable ]

    "extern":"extern ifname",                    // [ ifname@wan, ifname@lte, ... ], default is defdault gateway
    "peer":"gre tunnel peer address",            // [ string ]

    "localip":"gre tunnel local address",        // [ ip address ]
    "remoteip":"gre tunnel remote address",      // [ ip address ]
    "ttl":"gre tunnel ttl",                      // [ number ]

    "masq":"share the interface IPv4 address",   // [ disable, enable ]
    "defaultroute":"set it defualt route",       // [ disable, enable ]
    "route_table":                               // route table when online, this valid when "defaultroute" be "disable"
    {
        "route rule name":                            // [ string ]
        {
            "target":"target host or network",        // [ ip address ]
            "mask":"target network mask"              // [ netmask ]
        }
        // ... more route rule
    },

    "custom_dns":"custom the dns server",        // [ disable, enable ]
    "dns":"dns address",                         // [ ip address ], vaild when "custom_dns" be "enable"
    "dns2":"backup dns address"                  // [ ip address ], vaild when "custom_dns" be "enable"

}

```

