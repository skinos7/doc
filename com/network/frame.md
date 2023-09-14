***
## Network frame management 
Network management framework, define local connections and external connections and data scheduling when multiple external connections coexist
The network framework defines a three-tier concept to manage network interfaces: 
- netdev, network interface of linux, such as eth1, eth2, ath0, usb0
- ifdev, abstract network devices, such as wifi@nssid, modem@lte, wifi@asta, can be divided by VLAN and combined by bridge, 
- ifname, abstract network connections


#### **configuration( network@frame )**

```json
// Attribute introduction
{
    "mode":"equipment operator mode",                // < "ap", "wisp", "nwisp", "gateway", "dgateway", "misp", "nmisp", "dmisp", "mix" >
                                                       // "ap": access point
                                                       // "wisp": 2.4G Wireless Internet Service Provider connection
                                                       // "nwisp": 5.8G Wireless Internet Service Provider connection( need the board support 5.8G wirless baseband)
                                                       // "gateway": wire WAN gateway
                                                       // "dgateway": Dual wire WAN gateway
                                                       // "misp": LTE Mobile Internet Service Provider connection( need the board support LTE baseband)
                                                       // "nmisp": Next LTE/NR Mobile Internet Service Provider connection( need the board support LTE/NR baseband)
                                                       // "dmisp": Dual LTE/NR Mobile Internet Service Provider connection( need the board support two LTE/NR baseband)
                                                       // "mix": custom mix connection from multiple internet connection
    
    "local":                            // local connections list
    {
        "ifname object":                        // [ "ifname@lan", "ifname@lan2", ... ]
        {
            "concom":"connection component",        // [ string ]
            "ifdev":"ifdev object"                  // [ string ]
        }
        //"ifname object":{ ... }     How many local connections how many properties show
    },
    "extern":                            // external connections list
    {
        "ifname object":                        // [ "ifname@wan", "ifname@wan2", "ifname@lte", "ifname@lte2", "ifname@wisp", "ifname@wisp2", ... ]
        {
            "concom":"connection component",       // [ string ]
            "ifdev":"ifdev object"                 // [ string ]
        }
        //"ifname object":{ ... }     How many external connections how many properties show
    },

    // This configuration is available only in the case of multiple external connections. It indicates how external connections cooperate when multiple external connections coexist
    "connect":
    {
        "type":"Multiple link connect type",                          // [ "hot", "cold", "dhdc", "auto" ], "hot" for backup, "dhdc" for load balancing 
        "concom":"Multiple link connection management components",    // [ string ], You can customize the data scheduling component to implement more personalized requirements

        // When type is hot, it is the main connection. When type is dbdc, it is one of the external network connections 
        "main":"ifname object of extern",          // [ "ifname@wan", "ifname@wan2", "ifname@lte", "ifname@lte2", "ifname@wisp", "ifname@wisp2", ... ] 

        // When type is hot, it is the backup connection. When type is dbdc, it is one of the external network connections 
        "back":"ifname object of extern",          // [ "ifname@wan", "ifname@wan2", "ifname@lte", "ifname@lte2", "ifname@wisp", "ifname@wisp2", ... ]

        // When type is hot, the value is ignored. If the type is dbdc, all the default route data is forwarded by the connection as soon as the connection goes online
        "king":"ifname object of extern",          // [ "ifname@wan", "ifname@wan2", "ifname@lte", "ifname@lte2", "ifname@wisp", "ifname@wisp2", ... ]

        // When type is hot, the value is ignored. If the type is dbdc, the connections only connect but on route data via it
        "reserve":"ifname object of extern",       // [ "ifname@wan", "ifname@wan2", "ifname@lte", "ifname@lte2", "ifname@wisp", "ifname@wisp2", ... ]

        // Configure parameters of the delay switchover function, only in dbdc mode, the function can control the data via low delay connection
        "delay_count":"Statistical delay times of last",   // [ number ]
        "delay_divide":"delay divide line",                // [ number ], the unit is ms
        "delay_diff":"Delay differential",                 // [ number ], the unit is ms

        // DNS custom when Multiple DNS
        "custom_dns":"Custom DNS",                       // [ "disable", "enable", "ifname@lte", "ifname@lte2", ... ]
        "dns":"Custom DNS1",                             // [ ip address ], This is valid when "custom_dns" is "enable"
        "dns2":"Custom DNS2"                             // [ ip address ], This is valid when "custom_dns" is "enable"
    }
}

// Examples use terminal command line(SSH/TELNET)
// enter
network@frame
// receive
{
    "mode":"mix",   // mix mean multiple-connect to internet
    "local":                     // only one local connection is a ifname@lan
    {
        "ifname@lan":
        {
            "concom":"ifname@ethcon",
            "ifdev":"bridge@lan"
        }
    },
    "extern":                    // three extern connections: ifname@wan, ifname@lte, ifname@wisp
    {
        "ifname@wan":
        {
            "concom":"ifname@ethcon",
            "ifdev":"ethernet@wan"
        },
        "ifname@lte":
        {
            "concom":"ifname@ltecon",
            "ifdev":"modem@lte"
        },
        "ifname@lte2":
        {
            "concom":"ifname@ltecon",
            "ifdev":"modem@lte2"
        },        "ifname@wisp":
        {
            "concom":"ifname@ethcon",
            "ifdev":"wifi@nsta"
        }
    },
    "connect": 
    {
        "type":"dbdc",                  // dhdc for load balancing 
        "main":"ifname@lte",            // load balancing at ifname@lte and ifname@lte2
        "back":"ifname@lte2",
        "king":"ifname@wan",            // all data switch to ifname@wan when ifname@wan is online
        "reserve":"ifname@wisp",        // keep the ifname@wisp online, but don't switch the internet data via it
        "delay_count":"10",             // Collect statistics on the latest 10 delays and schedule traffic based on the delay
        "delay_divide":"150", 
        "delay_diff":"100"
    }
}

// Examples use TCP JSON
// send
{ "cmd1": { "com":"network@frame" } }
// receive(Omit here)
```


#### **Methods**

+ `status[]` **show external connections status when multiple external connections coexist**, *succeed return talk to describes infomation, failed reeturn NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "ifname object":
        {
            "status":"Whether online",    // [ "down", "up" ], "up" for online, "down" for offline
            "inuse":"Whether used"        // [ "disable", "enable" ], enable for in used, disable for not used
        },
        //"ifname object":{ ... }     How many extern connections how many properties show
    }
    ```
    ```shell
    # examples, get external connections status use terminal command line(SSH/TELNET)
    # enter
    network@frame.status
    # return
    {
        "ifname@lte":                   # ifname@lte status is online and inuse current
        {
            "status":"up",
            "inuse":"enable"
        },
        "ifname@lte2":                  # ifname@lte2 status is offline and not use current
        {
            "status":"down",
            "inuse":"disable"
        }
    }

    # Examples use TCP JSON
    # send
    { "cmd1": { "com":"network@frame", "op":"status" } }
    # receive
    { "cmd1": { "ifname@lte": { "status":"up", "inuse":"enable" }, "ifname@lte2": { "status":"down", "inuse":"disable" } } }
    ```

+ `list[]` **list all connections**, *succeed return talk to describes infomation, failed reeturn NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "ifname object":"The corresponding ifdev object",      // [ string ]: [ string ]
        //"ifname object":{ ... }     How many extern connections how many properties show
    }
    ```
    ```shell
    # examples, get all connections use terminal command line(SSH/TELNET)
    # enter
    network@frame.list
    # return
    {
        "ifname@lan":"bridge@lan",              # local connection named ifname@lan
        "ifname@lte":"modem@lte",               # extern connection named ifname@lte
        "ifname@lte2":"modem@lte2"              # extern connection named ifname@lte2
    }

    # Examples use TCP JSON
    # send
    { "cmd1": { "com":"network@frame", "op":"list" } }
    # receive
    { "cmd1": { "ifname@lan":"bridge@lan", "ifname@lte":"modem@lte", "ifname@lte2":"modem@lte2" } }
    ```

+ `local[]` **list all local connections and infomation**, *succeed return talk to describes infomation, failed reeturn NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "ifname object":
        {
            "mode":"current mode",                      // [ string ], View the description of the corresponding interface
            "status":"current state",                   // [ string ], View the description of the corresponding interface
            "ifdev":"corresponding ifdev object",       // [ string ]
            "netdev":"netdev name of linux",            // [ string ]
            "ip":"IP address",                          // [ ip address ]
            "rx_bytes":"receive bytes",                 // [ number ]
            "rx_packets":"receive packets",             // [ number ]
            "tx_bytes":"tx bytes",                      // [ number ]
            "tx_packets":"tx packets",                  // [ number ]
            "mac":"MAC address"                         // [ mac address ]
            // ... many other properties show
        }
        //"ifname object":{ ... }     How many local connections how many properties show
    }
    ```
    ```shell
    # examples, get all the local connections infomation use terminal command line(SSH/TELNET)
    # enter
    network@frame.local
    # return
    {
        "ifname@lan":                           # local connection named ifname@lan
        {
            "mode":"static",
            "ifname":"ifname@lan",
            "ifdev":"bridge@lan",
            "netdev":"lan",
            "ontime":"00:00:23:0",
            "status":"up",
            "ip":"192.168.8.1",
            "mask":"255.255.255.0",
            "livetime":"02:52:37:0",
            "rx_bytes":"348892",
            "rx_packets":"5923",
            "tx_bytes":"280817",
            "tx_packets":"335",
            "mac":"00:03:7F:12:72:06"
        }
    }

    # Examples use TCP JSON
    # send
    { "cmd1": { "com":"network@frame", "op":"local" } }
    # receive(Omit here)
    ```

+ `extern[]` **list all extern connections and infomation**, *succeed return talk to describes infomation, failed reeturn NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "ifname object":
        {
            "mode":"current mode",                      // [ string ], View the description of the corresponding interface
            "status":"current state",                   // [ string ], View the description of the corresponding interface
            "ifdev":"corresponding ifdev object",       // [ string ]
            "netdev":"netdev name of linux",            // [ string ]
            "ip":"IP address",                          // [ ip address ]
            "rx_bytes":"receive bytes",                 // [ number ]
            "rx_packets":"receive packets",             // [ number ]
            "tx_bytes":"tx bytes",                      // [ number ]
            "tx_packets":"tx packets",                  // [ number ]
            "mac":"MAC address"                         // [ mac address ]
            // ... View the description of the corresponding interface
        }
        //"ifname object":{ ... }     How many extern connections how many properties show
    }
    ```
    ```shell
    # examples, get all the extern connections infomation use terminal command line(SSH/TELNET)
    # enter
    network@frame.extern
    # return
    {
        "ifname@lte":
        {
            "ifdev":"modem@lte",
            "netdev":"usb1",
            "mac":"02:50:F4:00:00:00",
            "status":"uping",
            "tid":"1",
            "method":"slaac",
            "addr":"fe80::50:f4ff:fe00:0",
            "vid":"2c7c",
            "pid":"0125",
            "name":"Quectel-EC2X",
            "devcom":"modem@device",
            "imei":"867160040494084",
            "state":"connect",
            "imsi":"460115372165490",
            "iccid":"89861120147330291660",
            "plmn":"noreg",
            "csq":"21",
            "rssi":"-71",
            "signal":"4"
        },
        "ifname@lte2":
        {
            "mode":"dhcpc",
            "ifname":"ifname@lte2",
            "netdev":"usb0",
            "gw":"10.232.185.157",
            "dns":"120.80.80.80",
            "dns2":"221.5.88.88",
            "ontime":"02:22:47:0",
            "status":"up",
            "ip":"10.232.185.158",
            "mask":"255.255.255.252",
            "delay":"205",
            "livetime":"03:02:35:0",
            "rx_bytes":"137450",
            "rx_packets":"1609",
            "tx_bytes":"162336",
            "tx_packets":"1739",
            "mac":"02:50:F4:00:00:00",
            "tid":"2",
            "method":"slaac",
            "addr":"fe80::50:f4ff:fe00:0",
            "vid":"2c7c",
            "pid":"0800",
            "name":"Quectel-RG500Q",
            "devcom":"modem@device",
            "imei":"869710030002905",
            "imsi":"460015356123463",
            "iccid":"89860121801097564807",
            "state":"connect",
            "rsrp":"-104",
            "rssi":"-72",
            "signal":"4",
            "nettype":"FDD LTE",
            "rsrq":"-15",
            "sinr":"-18.0",
            "band":"LTE BAND 8",
            "csq":"19"
        }
    }

    # Examples use TCP JSON
    # send
    { "cmd1": { "com":"network@frame", "op":"extern" } }
    # receive(Omit here)
    ```

+ `vpn[]` **list all vpn connections and infomation**, *succeed return talk to describes infomation, failed reeturn NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "ifname object":
        {
            "mode":"current mode",                      // [ string ], View the description of the corresponding interface
            "status":"current state",                   // [ string ], View the description of the corresponding interface
            "ifdev":"corresponding ifdev object",       // [ string ]
            "netdev":"netdev name of linux",            // [ string ]
            "ip":"IP address",                          // [ ip address ]
            "rx_bytes":"receive bytes",                 // [ number ]
            "rx_packets":"receive packets",             // [ number ]
            "tx_bytes":"tx bytes",                      // [ number ]
            "tx_packets":"tx packets",                  // [ number ]
            "mac":"MAC address"                         // [ mac address ]
            // ... View the description of the corresponding interface   
        }
        //"ifname object":{ ... }     How many extern connections how many properties show
    }
    ```
    ```shell
    # examples, get all the vpn connections infomation use terminal command line(SSH/TELNET)
    # enter
    network@frame.vpn
    # return(Omit here)

    # Examples use TCP JSON
    # send
    { "cmd1": { "com":"network@frame", "op":"vpn" } }
    # receive(Omit here)
    ```

+ `outer[]` **list all extern and vpn ifname and its infomation**, *succeed return talk to describes infomation, failed reeturn NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "ifname object":
        {
            "mode":"current mode",                      // [ string ], View the description of the corresponding interface
            "status":"current state",                   // [ string ], View the description of the corresponding interface
            "ifdev":"corresponding ifdev object",       // [ string ]
            "netdev":"netdev name of linux",            // [ string ]
            "ip":"IP address",                          // [ ip address ]
            "rx_bytes":"receive bytes",                 // [ number ]
            "rx_packets":"receive packets",             // [ number ]
            "tx_bytes":"tx bytes",                      // [ number ]
            "tx_packets":"tx packets",                  // [ number ]
            "mac":"MAC address"                         // [ mac address ]
            // ... View the description of the corresponding interface    
        }
        //"ifname object":{ ... }     How many extern connections how many properties show
    }
    ```
    ```shell
    # examples, get all the extern and vpn connections infomation use terminal command line(SSH/TELNET)
    # enter
    network@frame.outer
    # return(Omit here)

    # Examples use TCP JSON
    # send
    { "cmd1": { "com":"network@frame", "op":"outer" } }
    # receive(Omit here)
    ```

+ `default[]` **get current default connection and infomation**, *succeed return talk to describes infomation, failed reeturn NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "mode":"current mode",                      // [ string ], View the description of the corresponding interface
        "status":"current state",                   // [ string ], View the description of the corresponding interface
        "ifdev":"corresponding ifdev object",       // [ string ]
        "netdev":"netdev name of linux",            // [ string ]
        "ip":"IP address",                          // [ ip address ]
        "rx_bytes":"receive bytes",                 // [ number ]
        "rx_packets":"receive packets",             // [ number ]
        "tx_bytes":"tx bytes",                      // [ number ]
        "tx_packets":"tx packets",                  // [ number ]
        "mac":"MAC address"                         // [ mac address ]
        // ... View the description of the corresponding interface
    }
    ```
    ```shell
    # examples, get current default connection infomation use terminal command line(SSH/TELNET)
    # enter
    network@frame.default
    # return
    {
        "ifname":"ifname@lte2",              # current default connetion is ifname@lte2, and the above is the infomation
        "mode":"dhcpc",
        "netdev":"usb0",
        "gw":"10.232.185.157",
        "dns":"120.80.80.80",
        "dns2":"221.5.88.88",
        "ontime":"02:22:47:0",
        "status":"up",
        "ip":"10.232.185.158",
        "mask":"255.255.255.252",
        "delay":"186",
        "livetime":"03:08:57:0",
        "rx_bytes":"142658",
        "rx_packets":"1671",
        "tx_bytes":"168684",
        "tx_packets":"1808",
        "mac":"02:50:F4:00:00:00",
        "name":"Quectel-RG500Q",
        "imei":"869710030002905",
        "imsi":"460015356123463",
        "iccid":"89860121801097564807",
        "state":"connect",
        "rssi":"-75",
        "signal":"4"
    }

    # Examples use TCP JSON
    # send
    { "cmd1": { "com":"network@frame", "op":"default" } }
    # receive(Omit here)
    ```



+ `main[]` **new session immediately uses the main connection, only vaild in dbdc**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples use terminal command line(SSH/TELNET)
    # enter
    network@frame.main
    # return
    ttrue

    # examples use TCP JSON
    # send
    { "cmd1": { "com":"network@frame","op":"main" } }
    # receive
    { "cmd1":"ttrue"}
    ```

+ `back[]` **new session immediately uses the backup connection, only vaild in dbdc**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples use terminal command line(SSH/TELNET)
    # enter
    network@frame.back
    # return
    ttrue

    # examples use TCP JSON
    # send
    { "cmd1": { "com":"network@frame","op":"main" } }
    # receive
    { "cmd1":"ttrue"}
    ```

+ `both[]` **new session immediately load balance on main and back connection, only vaild in dbdc**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples use terminal command line(SSH/TELNET)
    # enter
    network@frame.both
    # return
    ttrue
    
    # examples use TCP JSON
    # send
    { "cmd1": { "com":"network@frame","op":"both" } }
    # receive
    { "cmd1":"ttrue"}
    ```

+ `manual[]` **disable automatic load balance, only vaild in dbdc**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples for terminal command line(SSH/TELNET)
    # enter
    network@frame.manual
    # return
    ttrue
    
    # examples use TCP JSON
    # send
    { "cmd1": { "com":"network@frame","op":"manual" } }
    # receive
    { "cmd1":"ttrue"}
    ```

+ `auto[]` **enable automatic load balance, only vaild in dbdc**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples use terminal command line(SSH/TELNET)
    # enter
    network@frame.auto
    # return
    ttrue
    
    # examples use TCP JSON
    # send
    { "cmd1": { "com":"network@frame","op":"auto" } }
    # receive
    { "cmd1":"ttrue"}
    ```



+ `src_main[ source ip address ]` **set new session of source ip address immediately uses the main connection, only vaild in dbdc**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, the source ip 192.168.8.222 new session route to main connection use terminal command line(SSH/TELNET)
    # enter    
    network@frame.src_main[ 192.168.8.222 ]
    # return
    ttrue

    # examples use TCP JSON
    # send
    { "cmd1": { "com":"network@frame","op":"src_main", "1":"192.168.8.222" } }
    # receive
    { "cmd1":"ttrue"}
    ```

+ `dest_main[ dest ip address ]` **set new session of dest ip address immediately uses the main connection, only vaild in dbdc**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, the dest ip 114.114.114.114 new session route to main connection use terminal command line(SSH/TELNET)
    # enter    
    network@frame.dest_main[ 114.114.114.114 ]
    # receive
    ttrue

    # examples use TCP JSON
    # send
    { "cmd1": { "com":"network@frame","op":"dest_main", "1":"114.114.114.114" } }
    # receive
    { "cmd1":"ttrue"}
    ```

+ `src_back[ source ip address ]` **set new session of source ip address immediately uses the back connection, only vaild in dbdc**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, the source ip 192.168.8.111 new session route to back connection use terminal command line(SSH/TELNET)
    # enter    
    network@frame.src_back[ 192.168.8.111 ]
    # receive
    ttrue

    # examples use TCP JSON
    # send
    { "cmd1": { "com":"network@frame","op":"src_back", "1":"192.168.8.111 " } }
    # receive
    { "cmd1":"ttrue"}
    ```

+ `dest_main[ dest ip address ]` **set new session of dest ip address immediately uses the main connection, only vaild in dbdc**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, the dest ip 114.114.115.115 new session route to back connection use terminal command line(SSH/TELNET)
    # enter    
    network@frame.dest_back[ 114.114.115.115 ]
    # receive
    ttrue

    # examples use TCP JSON
    # send
    { "cmd1": { "com":"network@frame","op":"dest_back", "1":"114.114.115.115" } }
    # receive
    { "cmd1":"ttrue"}
    ```

+ `src_both[ source ip address ]` **set new session of source ip address load balance on main and back connection, only vaild in dbdc**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, the source ip 192.168.8.123 new session load balance on main and back connection use terminal command line(SSH/TELNET)
    # enter    
    network@frame.src_both[ 192.168.8.123 ]
    # receive
    ttrue

    # examples use TCP JSON
    # send
    { "cmd1": { "com":"network@frame","op":"src_both", "1":"192.168.8.123" } }
    # receive
    { "cmd1":"ttrue"}
    ```

+ `dest_both[ dest ip address ]` **set new session of dest ip address load balance on main and back connection, only vaild in dbdc**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, the dest ip 8.8.8.8 new session load balance on main and back connection use terminal command line(SSH/TELNET)
    # enter    
    network@frame.dest_both[ 8.8.8.8 ]
    # receive
    ttrue

    # examples use TCP JSON
    # send
    { "cmd1": { "com":"network@frame","op":"dest_both", "1":"8.8.8.8" } }
    # receive
    { "cmd1":"ttrue"}
    ```


