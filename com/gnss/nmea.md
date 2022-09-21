***
## GNSS management components
Manage GNSS, nmea data can from UART, LTE

#### **configuration( gnss@nmea )**

```json
// Attribute introduction
{
    // UART configure
    "status":"UART status",                                      // [ enable, disable ]

    // serial configure, don't use
    "speed":"Baud rate",            // [ 9600, 19200, 38400, 57600, 76800, 115200, 230400 ]
    "flow":"flow control",          // [ disable, hard, soft ], disable is disable, hard is hardware flow control, soft is software flow control
    "parity":"parity type",         // [ disable, even, odd ]
    "databit":"data bit",           // [ 5, 6, 7, 8 ]
    "stopbit":"stop bit",           // [ 1, 2 ]

    // Client configure
    "client":                       // MQTT client
    {
        "status":"client status",               // [ disable, enable ]
        "proto":"client protocol",              // [ tcp, udp, mqtt ]
        "server":"server address",              // [ string ]
        "port":"server port",                   // [ number ]

        "interval":"send interval",             // [ number ], the unit is second, default is one second

        "mqtt_id":"device identify",            // [ string ]
        "mqtt_username":"mqtt username",        // [ string ]
        "mqtt_password":"mqtt password",        // [ string ]
        "mqtt_interval":"mqtt interval",        // [ nubmer ]
        "mqtt_keepalive":"mqtt keepalive",      // [ number ]
        "mqtt_publish":"mqtt publish topic",    // [ string ]
        "mqtt_publish_qos":"mqtt publish qos",  // [ number ]
        "mqtt_subscribe":
        {
            "subscribe topic":"topic qos",
            "subscribe topic2":"topic2 qos",
            "subscribe topic3":"topic3 qos",
            // "subscribe topic":"topic qos"     How many subscribe topic need setting save how many properties
        }

    },
    "client2":                      // TCP/UDP client
    {
        "status":"client status",               // [ disable, enable ]
        "proto":"client protocol",              // [ tcp, udp ]
        "server":"server address",              // [ string ]
        "port":"server port",                   // [ number ]

        "id":"custom the nmea $PAHYR",                   // [ string ]
        "user":"custom the username at nmea $PAHYR",     // [ string ]
        "vcode":"custom the vocde at nmea $PAHYR",       // [ string ]
        "interval":"send interval",                      // [ number ], default is one second
        "content":"sends the specified header",          // [ ZDA, GGA, GLL, VTG, GSA, GSV, RMC, GST ], multiple heads are divided by a semicolon

        "login":"register packet",                     // [ disable, hex, ascii, mac ]
                                                            // disable for disable register packet
                                                            // hex for hex string
                                                            // ascii for ascii string
                                                            // mac for hex device mac
        "login_string":"register packet context",      // [ string ], such as 414243 when sending ABC when "login" is hex

        "frame_start":"packet prefix",                 // [ disable, hex, ascii, mac ]
                                                            // disable for disable packet prefix
                                                            // hex for hex string
                                                            // ascii for ascii string
                                                            // mac for hex device mac
        "frame_start_string":"packet prefix context",  // [ string ], such as 414243 when sending ABC when "frame_start" is hex
        
        "frame_end":"packet suffix",                   // [ disable, hex, ascii, mac ]
                                                            // disable for disable packet suffix
                                                            // hex for hex string
                                                            // ascii for ascii string
                                                            // mac for hex device mac
        "frame_end_string":"packet suffix context"     // [ string ], such as 414243 when sending ABC when "frame_end" is hex

    },

    // Server configure
    "server":
    {
        "status":"server status",                        // [ disable, enable ]
        "proto":"service tcp",                           // [ tcp, udp ] 
        "port":"service port",                           // [ number ]
        "limit":"concurrence client",                    // [ number ]
        "id":"custom the nmea $PAHYR",                   // [ string ]
        "user":"custom the username at nmea $PAHYR",     // [ string ]
        "vcode":"custom the vocde at nmea $PAHYR",       // [ string ]
        "interval":"send interval",                      // [ number ], default is one second
        "content":"sends the specified header",          // [ ZDA, GGA, GLL, VTG, GSA, GSV, RMC, GST ], multiple heads are divided by a semicolon

        "login":"register packet",                     // [ disable, hex, ascii, mac ]
                                                            // disable for disable register packet
                                                            // hex for hex string
                                                            // ascii for ascii string
                                                            // mac for hex device mac
        "login_string":"register packet context",      // [ string ], such as 414243 when sending ABC when "login" is hex

        "frame_start":"packet prefix",                 // [ disable, hex, ascii, mac ]
                                                            // disable for disable packet prefix
                                                            // hex for hex string
                                                            // ascii for ascii string
                                                            // mac for hex device mac
        "frame_start_string":"packet prefix context",  // [ string ], such as 414243 when sending ABC when "frame_start" is hex
        
        "frame_end":"packet suffix",                   // [ disable, hex, ascii, mac ]
                                                            // disable for disable packet suffix
                                                            // hex for hex string
                                                            // ascii for ascii string
                                                            // mac for hex device mac
        "frame_end_string":"packet suffix context"     // [ string ], such as 414243 when sending ABC when "frame_end" is hex

    }
}

```


#### **Methods**

+ `info[]` **get the nmea location infomation**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "step":"step of location",                  // [ setup, search, located ]
        "utc":"UTC date",                           // [ float ]
        "lon":"longitude",                          // [ float ]
        "lat":"latitude",                           // [ float ]
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
        "step":"located",
        "utc":"7:55:22:7:12:2021",
        "lon":"11356.56400",
        "lat":"2240.80119",
        "speed":"0.34",
        "elv":"77.90",
        "direction":"",
        "declination":"",
    }  
    ```

+ `status[]` **get the nmea service status**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "gnss@nmea":                             // source port
        {
            "rx":"receive byte",                     // [ number ]
            "tx":"send byte",                        // [ nubmer ]
            "connect":"connect state"                // [ ok ], ok for connect suceess
        },
        "server:192.168.8.250:59894":           // first server: client IP: client port
        {
            "rx":"receive byte",                     // [ number ]
            "tx":"send byte",                        // [ nubmer ]
            "connect":"connect state"                // [ ok ], ok for connect suceess
        },
        "server2:192.168.8.250:59894":          // second server: client IP: client port
        {
            "rx":"receive byte",                     // [ number ]
            "tx":"send byte",                        // [ nubmer ]
            "connect":"connect state"                // [ ok ], ok for connect suceess
        },
        "client":                               // first client
        {
            "rx":"receive byte",                     // [ number ]
            "tx":"send byte",                        // [ nubmer ]
            "connect":"connect state",                // [ ok ], ok for connect suceess
            "ip":"peer server ip address",
        },
        "client2":                               // second client
        {
            "rx":"receive byte",                     // [ number ]
            "tx":"send byte",                        // [ nubmer ]
            "connect":"connect state",                // [ ok ], ok for connect suceess
            "ip":"peer server ip address",
        }
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


