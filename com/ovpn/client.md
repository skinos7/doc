***
## Management of OPENVPN Client
Management of OPENVPN client

#### Configuration( ovpn@client )
**ovpn@client** is first ipsec connection
**ovpn@client2** is second ipsec connection

```json
// Attributes introduction 
{
    // common attributes
    "status":"client status",                      // [ disable, enable ]

    "extern":"extern ifname",                      // [ ifname@wan, ifname@lte, ... ], default is defdault gateway
    "peer":"openvpn server address",               // [ string ]
    "proto":"protocol type",                       // [ tcp, udp ]
    "port":"server port",                          // [ nubmer ], default is 1194
    "dev":"netdev type",                           // [ tun, tap ], tun is tunnel, tap is bridge to ifname@lan
    "topology":"topological structure",            // [ p2p, subnet ]
    "localip":"tunnel local address",              // [ ip address ], vailed when "topology" is "p2p"
    "remoteip":"tunnel peer address"               // [ ip address ], vailed when "topology" is "p2p"

    // seucre attributes
    "cipher":"cipher type",                        // [ DES-CFB, DES-CBC, RC2-CBC, RC2-CFB, RC2-OFB, DES-EDE-CBC, DES-EDE3-CBC, DES-OFB, 
                                                   //   DES-EDE-CFB, DES-EDE3-CFB, DES-EDE-OFB, DES-EDE3-OFB, DESX-CBC, BF-CBC, BF-CFB, BF-OFB,
                                                   //   CAST5-CBC, CAST5-CFB, CAST5-OFB, RC2-40-CBC, RC2-64-CBC, AES-128-CBC, AES-128-OFB,
                                                   //   AES-128-CFB, AES-192-CBC, AES-192-OFB, AES-192-CFB, AES-256-CBC, AES-256-OFB, AES-256-CFB,
                                                   //   AES-128-CFB1, AES-192-CFB1, AES-256-CFB1, AES-128-CFB8, AES-192-CFB8, AES-256-CFB8,
                                                   //   DES-CFB1, DES-CFB8, DES-EDE3-CFB1, DES-EDE3-CFB8, SEED-CBC, SEED-OFB, SEED-CFB ]
    "comp_lzo":"lzo compress mode",                // [ disable, yes, no, adaptive ]
    "hmac": "HMAC signature check",                // [ disable, tls-auth, tls-crypt ], version2.3 don't supoort "tls-crypt", "tls-auth" and "tls-crypt" need client.tlskey
    "auth":"authentication type",                  // [ none, static, certificate, username ]
                                                   //    none: is disable
                                                   //    static: use static key, need client.statickey
                                                   //    certificate: use CA certificate, need client.ca/client.crt/client.key
                                                   //    username: use username and password, need client.ca
    "username":"user name",                        // [ string ], vaild when "auth" is "username"
    "password":"user password",                    // [ string ], vaild when "auth" is "username"

    // keeplive attributes
    "interval":"keeplive packet echo interval",    // [ number ], the unit is second
    "timeout":"keeplive packet timeout",           // [ number ], the unit is second
    "options":"openvpn original options",          // [ string ], multiple options are separated by semicolons

    // route attributes, vaild when "dev" is "tun"
    "masq":"share interface address to access",    // [ disable, enable ]
    "defaultroute":"set it default route",         // [ disable, enable ]
    "route_table":                                 // you can custom the route rule on this connect, vaild when "defaultroute" is "disable"
    {
        "route rule name":                         // [ string ]
        {
            "target":"destination address",           // [ string ], ip address or network
            "mask":"destination network mask"      // [ string ]
        },
        // ...more route rule
    }
    "custom_dns":"Custom DNS",                                 // [ disable, enable ]
    "dns":"Custom DNS1",                                       // [ IP address ], This is valid when "custom_dns" is "enable"
    "dns2":"Custom DNS2"                                       // [ IP address ], This is valid when "custom_dns" is "enable"
}

```


#### **Methods**

+ `setup[]` **setup the openvpn client**, *succeed return ttrue, failed return tfalse, error return terror*

+ `shut[]` **shutdown the openvpn client**, *succeed return ttrue, failed return tfalse, error return terror*

+ `status[]` **get the openvpn client infomation**, *succeed return talk to describes infomation, failed return NULL, error return terror*
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
    # examples, get the first openvpn client infomation
    ovpn@client.status
    {
        "status":"up",                     # connect is succeed
        "netdev":"tun0",                   # netdev is tun0
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

+ `netdev[]` **get the openvpn client netdev**, *succeed return netdev, failed return NULL, error return terror*
    ```shell
    # examples, get the first openvpn client netdev
    ovpn@client.netdev
    tun0
    ```

+ `clear_ca[]` **delete openvpn client CA certificate**, *succeed return ttrue, failed return tfalse, error return terror*

+ `clear_cert[]` **delete openvpn client certificate**, *succeed return ttrue, failed return tfalse, error return terror*

+ `clear_key[]` **delete openvpn client private key**, *succeed return ttrue, failed return tfalse, error return terror*

+ `clear_statickey[]` **delete openvpn client static key**, *succeed return ttrue, failed return tfalse, error return terror*

+ `clear_tlskey[]` **delete openvpn client TLS key**, *succeed return ttrue, failed return tfalse, error return terror*

+ `list_key[]` **list openvpn client all key file**, *succeed return talk to describes infomation, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "ca":"CA certificate file pathname",
        "crt":"client certificate file pathname",
        "key":"private key file pathname",
        "statickey":"static key file pathname",
        "tlskey":"TLS key file pathname"
    }
    ```
    ```shell
    # examples, list first openvpn client all key file
    ovpn@client.list_key
    {
        "ca":"/var/.cfg/ovpn/client.cacrt",            // CA certificate
        "crt":"/var/.cfg/ovpn/client.crt",             // client certificate
        "key":"/var/.cfg/ovpn/client.key",             // private key
        "statickey":"/var/.cfg/ovpn/client.statickey", // static key
        "tlskey":"/var/.cfg/ovpn/client.tlskey"        // TLS key
    }
    ```

