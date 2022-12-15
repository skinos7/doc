***
## Management of IPSEC client
Management of IPSEC client

#### Configuration( ipsec@client )
**ipsec@client** is first ipsec client
**ipsec@client2** is second ipsec client

```json
// Attributes introduction 
{
    // common attributes
    "status":"client status",                    // [ disable, enable ]

    "extern":"extern ifname",                    // [ ifname@wan, ifname@lte, ... ], default is defdault gateway
    "local":"local ifname",                      // [ ifname@lan, ifname@lan2, ... ], default is ifname@lan

    "peer":"ipsec server address",               // [ string ]
    "peer_network":"peer network",               // [ string ], ex. 10.0.0.0/24
    "local_network":"local network",             // [ string ], ex. 192.168.8.0/24, default is ifname@lan network

    "peer_idtype":"local ID type",               // [ ip, custom, any ], ip for peer ip, custom the custom peer ID, any for any ID
    "peer_id":"local ID",                        // [ string ], valid when "peer_idtype" be "custom"
    "local_idtype":"local ID type",              // [ ip, custom, any ], ip for local ip, custom the custom local ID, any for any ID
    "local_id":"local ID",                       // [ string ], valid when "local_idtype" be "custom"

    "aggressive":"use aggressive",               // [ disable, enable ]
    "secret":"Pre-shared key",                   // [ string ]

    // ike attributes
    "ike_version":"IKE version",                 // [ ike, ikev1, ikev2 ]
    "ike_lifetime": "IKE lifetime",              // [ 60-604800 ], default is 3 hour, the unit is second
    "ike_auth":"IKE authentication type",        // [ aesxcbc, md5, sha1, sha256, sha384, sha512 ]
    "ike_encrypt":"IKE enctypt type",            // [ des, 3des, aes128, aes192, aes256 ]
    "ike_dh":"IKE DH group",                     // [ modp768, modp1024, modp1536, modp2048, modp3072, modp4096, modp8192 ]

    // ipsec attributes
    "ipsec_lifetime":"ipsec lifetime",           // [ 120-604800 ], default is 1 hour, the unit is second
    "ipsec_protocol":"ipsec secert protocol",    // [ ah, esp ]
    "ipsec_auth":"ipsec authentication type",    // [ md5, sha1 ] when "ipsec_protocol" be "ah"
    "ipsec_encrypt":"ipsec encrypt type",        // [ des, 3des, aes128, aes192, aes256 ] vaild when "ipsec_protocol" be "ah"
    "ipesc_dh": "ipsec DH group",                // [ modp768, modp1024, modp1536, modp2048, modp3072, modp4096, modp8192 ], can be space

    // dpd attributes
    "dpd":"DPD type",                            // [ disable, clear, hold, restart ]
    "dpd_delay":"DPD keeplive interval"          // [ nubmer ], the unit is second, vaild when "dpd" not be "disable", default is 30 second
    "dpd_timeout":"DPD keeplive timeout"         // [ nubmer ], the unit is second, vaild when "dpd" not be "disable", default is 30 second

}

```


