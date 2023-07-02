***
## Management of OPENVPN Server
Management of OPENVPN Server

#### Configuration( ovpns@server )
**ovpns@server** is first openvpn server

```json
// Attributes introduction 
{
    // common attributes
    "status":"server status",                      // [ disable, enable ]

    "proto":"protocol type",                       // [ tcp, udp ]
    "port":"server port",                          // [ nubmer ], default is 1194
    "topology":"topological structure",            // [ p2p, subnet ]
    "localip":"tunnel local address",              // [ ip address ], vailed when "topology" is "p2p"
    "remoteip":"tunnel peer address",              // [ ip address ], vailed when "topology" is "p2p"
    "dev":"netdev type",                           // [ tun, tap ], tun is tunnel, tap is bridge to ifname@lan

    "localip":"tunnel local address",              // [ ip address ], vailed when "topology" is "p2p"
    "remoteip":"tunnel peer address",              // [ ip address ], vailed when "topology" is "p2p"
    "bridgeip":"local bridge ip address",          // [ ip address ], vaild when "topology" is "subnet" and "dev" is "tap"
    "bridgemask":"local bridge ip mask",           // [ ip address ], vaild when "topology" is "subnet" and "dev" is "tap"
    "bridgestart":"end address assigned",          // [ ip address ], vaild when "topology" is "subnet" and "dev" is "tap"
    "bridgeend":"start address assigned",          // [ ip address ], vaild when "topology" is "subnet" and "dev" is "tap"
    "tunnelip":"local tunnel ip address",          // [ ip address ], vaild when "topology" is "subnet" and "dev" is "tun"
    "tunnelmask":"local tunnel ip mask",           // [ ip address ], vaild when "topology" is "subnet" and "dev" is "tun"
    "tunneldns":"DNS assigned for tunnel",         // [ ip address ], vaild when "topology" is "subnet" and "dev" is "tun"
    "tunneldns2":"DNS2 assigned for tunnel",       // [ ip address ], vaild when "topology" is "subnet" and "dev" is "tun"
    "client2client":"clients access each other",   // [ enable, disable ]
    "clientdup":"client connect multiple times",   // [ enable, disable ]

    // seucre attributes
    "cipher":"cipher type",                        // [ DES-CFB, DES-CBC, RC2-CBC, RC2-CFB, RC2-OFB, DES-EDE-CBC, DES-EDE3-CBC, DES-OFB, 
                                                   //   DES-EDE-CFB, DES-EDE3-CFB, DES-EDE-OFB, DES-EDE3-OFB, DESX-CBC, BF-CBC, BF-CFB, BF-OFB,
                                                   //   CAST5-CBC, CAST5-CFB, CAST5-OFB, RC2-40-CBC, RC2-64-CBC, AES-128-CBC, AES-128-OFB,
                                                   //   AES-128-CFB, AES-192-CBC, AES-192-OFB, AES-192-CFB, AES-256-CBC, AES-256-OFB, AES-256-CFB,
                                                   //   AES-128-CFB1, AES-192-CFB1, AES-256-CFB1, AES-128-CFB8, AES-192-CFB8, AES-256-CFB8,
                                                   //   DES-CFB1, DES-CFB8, DES-EDE3-CFB1, DES-EDE3-CFB8, SEED-CBC, SEED-OFB, SEED-CFB ]
    "comp_lzo":"lzo compress mode",                // [ disable, yes, no, adaptive ]
    "hmac": "HMAC signature check",                // [ disable, tls-auth, tls-crypt ], version2.3 don't supoort "tls-crypt", "tls-auth" and "tls-crypt" need server.tlskey
    "auth":"authentication type",                  // [ none, static, certificate, username ]
                                                   //    none: is disable
                                                   //    static: use static key, need server.statickey
                                                   //    certificate: use CA certificate, need ca.crt/server.crt/server.key/server.dh2048
                                                   //    username: use username and password, need ca.crt/server.dh2048
    "username":"user name",                        // [ string ], vaild when "auth" is "username"
    "password":"user password",                    // [ string ], vaild when "auth" is "username"
    
    // keeplive attributes
    "interval":"keeplive packet echo interval",    // [ number ], the unit is second
    "timeout":"keeplive packet timeout",           // [ number ], the unit is second
    "options":"openvpn original options"           // [ string ], multiple options are separated by semicolons
}

```


#### **Methods**

+ `setup[]` **setup the openvpn server**, *succeed return ttrue, failed return tfalse, error return terror*

+ `shut[]` **shutdown the openvpn server**, *succeed return ttrue, failed return tfalse, error return terror*

+ `status[]` **get the openvpn server infomation**, *succeed return talk to describes infomation, failed return NULL, error return terror*

+ `netdev[]` **get the openvpn server netdev**, *succeed return netdev, failed return NULL, error return terror*
    ```shell
    # examples, get the first openvpn server netdev
    ovpns@server.netdev
    tun0
    ```

