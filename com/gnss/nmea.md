***
## GNSS management components
Manage GNSS

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

