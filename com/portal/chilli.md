
***
## Management chilli portal of web page
Administration of equipment Management chilli portal web page

#### Configuration( portal@chilli )

```json
// Attributes introduction 
{
    "status":"start at system startup",                 // [ "disable", "enable" ]
    "extern":"extern ifname",                           // [ "ifname@lte", "ifname@lte2", "ifname@wan", ... ], default is the default gateway
    "local":"local ifname",                             // [ "ifname@lan", "ifname@lan2", "ifname@lan3", "wifi@nssid", "wifi@assid, "... ], default is the wifi@nssid

    "ip":"chilli interface ip address",                 // [ ip address ], HS_UAMLISTEN
    "mask":"chilli interface netmask",                  // [ netmask ], HS_NETMASK
    "network":"chilli interface network",               // [ network ], HS_NETWORK
    "dns":"dns server",                                 // [ ip address ], HS_DNS1
    "dns2":"dns server",                                // [ ip address ], HS_DNS2

    "port":"chilli service port",                       // [ number ], 1-65535, HS_UAMPORT
    "uiport":"chilli ui port",                          // [ number ], 1-65535, HS_UAMUIPORT

    "radius_nasip":"Radius NAS IP",                     // [ string ]
    "radius_nasid":"Radius NAS Identify",               // [ string ], HS_NASID
    "radius_server":"Radius server",                    // [ ip address ], HS_RADIUS
    "radius_server2":"Radius server",                   // [ ip address ], HS_RADIUS2
    "radius_secret":"Radius server key",                // [ string ], HS_RADSECRET
    "radius_authport":"Radius auth port",               // [ number ], 1-65535, HS_RADAUTH
    "radius_acctport":"Radius account port",            // [ number ], 1-65535, HS_RADAUTH
    
    "uam_format":"UMA Portal URL",                      // [ string ], HS_UAMFORMAT
    "uam_homepage":"UMA Homepage URL",                  // [ string ], HS_UAMHOMEPAGE
    "uam_secret":"UMA secret",                          // [ string ], HS_UAMSECRET
    "uam_allowed":"UMA allowed address",                // [ string ], HS_UAMALLOW, Multiple addresses are separated by space
    "uam_domains":"UMA allowed domain",                 // [ string ], HS_UAMDOMAINS, Multiple domains are separated by space
    "session_timeout":"session timeout",                // [ number ]

    "defaults_opt":"defaults custom options",            // [ string ], /etc/chilli/defaults, Multiple options are separated by semicolons
    "local_opt":"local.conf custom options"              // [ string ], /etc/chilli/local.conf, Multiple options are separated by semicolons
}
```

Examples, show all the configure
```shell
portal@chilli
{
    "status":"enable",             # start this service at system startup
    "extern":"",                   # the extern interface is default internet
    "local":"wifi@nssid",          # only work on WIFI(2.4G)

    "ip":"192.168.182.1",          # chilli local ip is 192.168.182.1
    "mask":"255.255.240.0",        # chilli local netmask is 255.255.240.0
    "network":"192.168.176.0",     # chilli local network is 192.168.176.0
    "dns":"8.8.8.8",               # chilli local network dns is 8.8.8.8 and 8.8.4.4
    "dns2":"8.8.4.4",
    "port":"3990",
    "uiport":"4990",

    "radius_nasid":"dimmalex",     # Network access server identifier is dimmalex
    "radius_server":"radius.hotspotsystem.com",
    "radius_server2":"radius2.hotspotsystem.com",
    "radius_secret":"hotsys123",
    "radius_authport":"1812",
    "radius_acctport":"1813",

    "uam_format":"https://customer.hotspotsystem.com/customer/hotspotlogin.php",
    "uam_homepage":"",
    "uam_secret":"hotsys123",

    "uam_allowed":"198.241.128.0/17 66.211.128.0/17 216.113.128.0/17 70.42.128.0/17  128.242.125.0/24 216.52.17.0/24 155.136.66.34 66.4.128.0/17 66.211.128.0/17 66.235.128.0/17 88.221.136.146 195.228.254.149 195.228.254.152 193.67.130.68 213.52.172.68 www.paypal.com www.paypalobjects.com live.adyen.com checkoutshopper-live.adyen.com ocsp.int-x3.letsencrypt.org cert.int-x3.letsencrypt.org www.directebanking.com betalen.rabobank.nl ideal.ing.nl secure.simplepay.hu securepay.simplepay.hu ideal.abnamro.nl www.ing.nl api.mailgun.net gv.symcd.com cdp.rapidssl.com status.rapidssl.com crl3.digicert.com crl4.digicert.com www.hotspotsystem.com customer.hotspotsystem.com tech.hotspotsystem.com a1.hotspotsystem.com a2.hotspotsystem.com a3.hotspotsystem.com a4.hotspotsystem.com a5.hotspotsystem.com a6.hotspotsystem.com a7.hotspotsystem.com a8.hotspotsystem.com a9.hotspotsystem.com a10.hotspotsystem.com a11.hotspotsystem.com a12.hotspotsystem.com a13.hotspotsystem.com a14.hotspotsystem.com a15.hotspotsystem.com a16.hotspotsystem.com a17.hotspotsystem.com a18.hotspotsystem.com a19.hotspotsystem.com a20.hotspotsystem.com a21.hotspotsystem.com a22.hotspotsystem.com a23.hotspotsystem.com a24.hotspotsystem.com a25.hotspotsystem.com a26.hotspotsystem.com a27.hotspotsystem.com a28.hotspotsystem.com a29.hotspotsystem.com a30.hotspotsystem.com",
    "uam_domains":"paypal.com paypalobjects.com adyen.com hotspotsystem.com geotrust.com rabobank.nl ing.nl abnamro.nl triodos.nl asnbank.nl knab.nl regiobank.nl snsbank.nl vanlanschot.com bunq.com",
    
    "defaults_opt":"HS_PROVIDER=\"HotSpotSystem\"\nHS_PROVIDER_LINK=\"http://www.hotspotsystem.com/\"\nHS_UAMSERVER=\"customer.hotspotsystem.com\"\nHS_DYNIP=192.168.176.0\nHS_DYNIP_MASK=255.255.240.0",
    "local_opt":""
}
```  
Examples, modify the dns of chilli local network
```shell
portal@chilli:dns=114.114.114.114
ttrue
```  
Examples, disable the chilli portal
```shell
portal@chilli:status=disable
ttrue
```  

