***
## Management of WireGuard Interface
Management of WireGuard Interface

#### Configuration( sdwan@wg )
**sdwan@wg** is first WireGuard Interface
**sdwan@wg2** is second WireGuard Interface

```json
// Attributes introduction 
{
    // common attributes
    "status":"client status",                    // [ disable, enable ]
    "extern":"extern ifname",                    // [ "disable", "", "ifname@wan", "ifname@lte", ... ],
                                                                // "disable" or space for none
                                                                // "" for is defdault gateway
                                                                // "ifname@wan", "ifname@lte", ... for specified extern interface

    "peer":
    {
        "public key":                                     // [ string ]
        {
            "endpoint":"peer address and port",                 // [ ip address:number ]
            "sharekey":"preshare key",                          // [ string ]
            "ips":"allowed ip or network"                       // [ network ]
            "keepalive":"persistent keepalive interval"         // [ number ], the unit is second
        }
        // ... more peer
    },

    "local":                                        // local configure for ip address
    {
        "ip":"IPv4 address",                        // < ipv4 address >
        "mask":"IPv4 netmask",                      // < ipv4 netmask >
        "ip2":"IPv4 address 2",                     // < ipv4 address >
        "mask2":"IPv4 netmask 2",                   // < ipv4 netmask >
        "ip3":"IPv4 address 3",                     // < ipv4 address >
        "mask3":"IPv4 netmask 3"                    // < ipv4 netmask >
    },
    "port":"listen port",                           // [ number ]

    "mtu":"interface MTU",                          // [ number ]

    // route attributes
    "masq":"share interface address to access",     // [ disable, enable ]
    "defaultroute":"set it default route",          // [ disable, enable ]
    "route_table":                                  // you can custom the route rule on this connect, vaild when "defaultroute" is "disable"
    {
        "route rule name":                          // [ string ]
        {
            "target":"destination address",           // [ string ], ip address or network
            "mask":"destination network mask"         // [ string ]
        }
        // ...more route rule
    },
    "gw":"default gateway",                      // [ ip address ]
    "custom_dns":"custom the dns server",        // [ disable, enable ]
    "dns":"dns address",                         // [ ip address ], vaild when "custom_dns" be "enable"
    "dns2":"backup dns address"                  // [ ip address ], vaild when "custom_dns" be "enable"
}

```


#### **Methods**

+ `setup[]` **setup the wireguard interface**, *succeed return ttrue, failed return tfalse, error return terror*

+ `shut[]` **shutdown the wireguard interface**, *succeed return ttrue, failed return tfalse, error return terror*

+ `status[]` **get the wireguard interface infomation**, *succeed return talk to describes infomation, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "status":"Current status",        // [ uping, down, up ]
                                             // uping for connecting
                                             // down for the network is down
                                             // up for the network is connect succeed
        "netdev":"netdev name",         // [ string ]
        "gw":"gateway ip address",      // [ ip address ]
        "dns":"dns ip address",         // [ ip address ]
        "dns2":"dns2 ip address",       // [ ip address ]
        "ip":"ip address",              // [ ip address ]
        "mask":"network mask",          // [ ip address ]
        "livetime":"online time",       // hour:minute:second:day
        "rx_bytes":"send bytes",        // [ number ]
        "rx_packets":"send packets",    // [ number ]
        "tx_bytes":"receive bytes",     // [ number ]
        "tx_packets":"receive packets", // [ number ]
    }
    ```
    ```shell
    # examples, get the first wiregaurd infomation
    sdwan@wg.status
    {
        "status":"up",                     # connect is succeed
        "netdev":"wg0",                    # netdev is wg0
        "ip":"192.168.10.1",               # ip address is 192.168.1.1
        "mask":"255.255.255.0",            # network mask is 255.255.255.0
        "gw":"192.168.10.254",             # gateway is 192.168.10.254
        "dns":"114.114.114.114",           # dns is 114.114.114.114
        "livetime":"01:15:50:0",           # already online 1 hour and 15 minute and 50 second
        "rx_bytes":"1256",                 # receive 1256 bytes
        "rx_packets":"4",                  # receive 4 packets
        "tx_bytes":"1320",                 # send 1320 bytes
        "tx_packets":"4"                   # send 4 packets
    }
    ```

+ `netdev[]` **get the wireguard interface netdev**, *succeed return netdev, failed return NULL, error return terror*
    ```shell
    # examples, get the first wireguard interface netdev
    sdwan@wg.netdev
    wg0
    ```

