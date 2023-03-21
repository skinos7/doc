***
## GNSS management components
Manage GNSS, nmea data can from UART, LTE

#### **configuration( gnss@nmea )**

```json
// Attribute introduction
{
    // UART configure
    "status":"GNSS status",         // [ "enable", "disable" ]

    // Client configure
    "client":                       // MQTT client example
    {
        "status":"client status",               // [ "disable", "enable" ]
        "proto":"client protocol",              // [ "tcp", "udp", "mqtt" ]
        "server":"server address",              // [ string ]
        "port":"server port",                   // [ number ]

        "interval":"send interval",             // [ number ], the unit is second, default is one second

        // above vaild when "proto" be "mqtt"
        "mqtt_id":"device identify",            // [ string ]
        "mqtt_username":"mqtt username",        // [ string ]
        "mqtt_password":"mqtt password",        // [ string ]
        "mqtt_interval":"mqtt interval",        // [ nubmer ]
        "mqtt_keepalive":"mqtt keepalive",      // [ number ]
        "mqtt_publish":"mqtt publish topic",    // [ string ]
        "mqtt_publish_qos":"mqtt publish qos",  // [ number ]
        "mqtt_subscribe":
        {
            "subscribe topic":"topic qos",      // [ string ]:[ number ]
            // "subscribe topic":"topic qos"     How many subscribe topic need setting save how many properties
        }
    },
    "client2":                      // TCP/UDP client example
    {
        "status":"client status",               // [ "disable", "enable" ]
        "proto":"client protocol",              // [ "tcp", "udp", "mqtt" ]
        "server":"server address",              // [ string ]
        "port":"server port",                   // [ number ]

        // above vaild when "proto" be "tcp" or "udp"
        "id":"custom the nmea $PAHYR",                   // [ string ]
        "user":"custom the username at nmea $PAHYR",     // [ string ]
        "vcode":"custom the vocde at nmea $PAHYR",       // [ string ]
        "interval":"send interval",                      // [ number ], default is one second
        "content":"sends the specified header"           // [ string ], "ZDA", "GGA", "GLL", "VTG", "GSA", "GSV", "RMC", "GST" ], multiple heads are divided by a semicolon
    },

    // Server configure
    "server":
    {
        "status":"server status",                        // [ "disable", "enable" ]
        "proto":"service tcp",                           // [ "tcp", "udp" ] 
        "port":"service port",                           // [ number ]
        "limit":"concurrence client",                    // [ number ]
        "id":"custom the nmea $PAHYR",                   // [ string ]
        "user":"custom the username at nmea $PAHYR",     // [ string ]
        "vcode":"custom the vocde at nmea $PAHYR",       // [ string ]
        "interval":"send interval",                      // [ number ], default is one second
        "content":"sends the specified header"           // [ string ], "ZDA", "GGA", "GLL", "VTG", "GSA", "GSV", "RMC", "GST" ], multiple heads are divided by a semicolon
    }
}

```


#### **Methods**

+ `info[]` **get the nmea location infomation**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "step":"step of location",                  // [ "setup", "search", "located" ]
        "utc":"UTC date",                           // [ string ], format is hour:minute:second:month:day:year
        "lon":"longitude",                          // [ float ], nmea format
        "lat":"latitude",                           // [ float ], nmea format
        "longitude":"longitude",                    // [ float ]
        "latitude":"latitude",                      // [ float ]
        "speed":"speed",                            // [ float ]
        "direction":"direction",
        "declination":"declination",
        "elv":"Either altitude height",             // [ float ], the unit is meter
        "inview":"Number of visible satellites",    // [ number ]
        "inuse":"Number of satellites in use"       // [ nubmer ]     
    }
    ```
    ```shell
    # examples, get the current date
    gnss@nmea.info
    {
        "step":"located",                           # already located
        "utc":"7:55:22:7:12:2021",                  # UTC
        "lon":"11356.56400",
        "lat":"2240.80119",
        "longitude":"113.94273",                    # longitude is 113.94
        "latitude":"22.68001",                      # latitude is 22.68
        "speed":"0.34",
        "elv":"77.90",
        "direction":"",
        "declination":"",
        "inuse":"8"                                 # 8 sat in use
    }
    ```

+ `status[]` **get the nmea service status**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        // source port state
        "source port":                         // [ "gnss@nmea" ]
        {
            "rx":"receive byte",                     // [ number ]
            "tx":"send byte",                        // [ nubmer ]
            "connect":"connect state"                // [ "ok" ], ok for connect suceess
        },

        // server state
        "server's client ip and port":         // [ string ], format is [server name:client ip:client port]
        {
            "rx":"receive byte",                     // [ number ]
            "tx":"send byte",                        // [ nubmer ]
            "connect":"connect state"                // [ "ok" ], ok for connect suceess
        },
        // ... more server's client 

        // client state
        "client name":                         // [ string ]
        {
            "rx":"receive byte",                     // [ number ]
            "tx":"send byte",                        // [ nubmer ]
            "connect":"connect state"                // [ "ok" ], ok for connect suceess
            "ip":"peer server ip address",           // [ ip address ]
        }
        // ... more client 
    }    
    ```
    ```shell
    # examples, get the current nmea service status
    gnss@nmea.status
    {
        "gnss@nmea":                           # receive 24921 byte from source port
        {
            "rx":"24921",
            "tx":"0",
            "connect":"ok"
        },
        "server:192.168.8.250:59894":          # first server send 10902 byte to a client( 192.168.8.250:59894 )
        {
            "rx":"0",
            "tx":"10902",
            "connect":"ok"
        },
        "client":                              # first client send 17064 byte to peer server( 192.168.8.250 )
        {
            "rx":"0",
            "tx":"17064",
            "ip":"192.168.8.250",
            "connect":"ok"
        }
    }  
    ```


