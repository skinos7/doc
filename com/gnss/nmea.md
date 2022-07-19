***
## GNSS management components
Manage GNSS

#### **configuration( gnss@nmea )**

```json
// Attribute introduction
{
    // UART configure
    "status":"UART status",                                      // [ enable, disable ]

    // serial configure
    "speed":"Baud rate",            // [ 9600, 19200, 38400, 57600, 76800, 115200, 230400 ]
    "flow":"flow control",          // [ disable, hard, soft ], disable is disable, hard is hardware flow control, soft is software flow control
    "parity":"parity type",         // [ disable, even, odd ]
    "databit":"data bit",           // [ 5, 6, 7, 8 ]
    "stopbit":"stop bit",           // [ 1, 2 ]

    "client":
    {
        "status":"client status",               // [ disable, enable ]
        "proto":"client protocol",              // [ tcp, udp ]
        "server":"server address",              // [ string ]
        "port":"server port",                   // [ number ]

        "login":"register packet",                // [ disable, hex, ascii, mac ]
                                                            // disable for disable register packet
                                                            // hex for hex string
                                                            // ascii for ascii string
                                                            // mac for hex device mac
        "login_string":"register packet context", // [ string ], such as 414243 when sending ABC when "login" is hex

        "frame_start":"disable|hex|ascii|mac",     // <包前缀> 分为disable(禁用), hex为十六制, ascii为字符式, mac使用十六制进的mac地址为包后缀
        "frame_start_string":"",  //  <包前缀内容>  十六进制的数据, 如发送ABC时填写414243 , 为<包前缀>为enable时必填
        "frame_end":"disable|hex|ascii|mac", //  <包后缀> 分为disable(禁用), hex为十六制, ascii为字符式, mac使用十六制进的mac地址为包后缀
        "frame_end_string":"",    // <包后缀内容>  十六进制的数据, 如发送ABC时填写414243 , 为<包后缀>为enable时必填

        "id":"",
        "user":"",
        "vcode":"",

        "mqtt_id":"设备ID号",
        "mqtt_username":"管理帐号",
        "mqtt_password":"密码",
        "mqtt_interval":"mqtt interval",
        "mqtt_keepalive":"mqtt keepalive",
        "mqtt_publish":"mqtt publish topic",
        "mqtt_publish_qos":"mqtt publish qos",
        "mqtt_subscribe":
        {
            "subscribe topic":"topic qos",
            "subscribe topic2":"topic2 qos",
            "subscribe topic3":"topic3 qos",
            // "subscribe topic":"topic qos"     How many subscribe topic need setting save how many properties
        }

    },
    "client2":
    {
        "status":"client status",               // [ disable, enable ]
        "proto":"client protocol",              // [ tcp, udp ]
        "server":"server address",              // [ string ]
        "port":"server port",                   // [ number ]

        "login":"register packet",                // [ disable, hex, ascii, mac ]
                                                            // disable for disable register packet
                                                            // hex for hex string
                                                            // ascii for ascii string
                                                            // mac for hex device mac
        "login_string":"register packet context", // [ string ], such as 414243 when sending ABC when "login" is hex

        "frame_start":"disable|hex|ascii|mac",     // <包前缀> 分为disable(禁用), hex为十六制, ascii为字符式, mac使用十六制进的mac地址为包后缀
        "frame_start_string":"",  //  <包前缀内容>  十六进制的数据, 如发送ABC时填写414243 , 为<包前缀>为enable时必填
        "frame_end":"disable|hex|ascii|mac", //  <包后缀> 分为disable(禁用), hex为十六制, ascii为字符式, mac使用十六制进的mac地址为包后缀
        "frame_end_string":"",    // <包后缀内容>  十六进制的数据, 如发送ABC时填写414243 , 为<包后缀>为enable时必填

    },
    "client3":
    {
        "status":"client status",               // [ disable, enable ]
        "proto":"client protocol",              // [ tcp, udp ]
        "server":"server address",              // [ string ]
        "port":"server port",                   // [ number ]

        "login":"register packet",                // [ disable, hex, ascii, mac ]
                                                            // disable for disable register packet
                                                            // hex for hex string
                                                            // ascii for ascii string
                                                            // mac for hex device mac
        "login_string":"register packet context", // [ string ], such as 414243 when sending ABC when "login" is hex

        "frame_start":"disable|hex|ascii|mac",     // <包前缀> 分为disable(禁用), hex为十六制, ascii为字符式, mac使用十六制进的mac地址为包后缀
        "frame_start_string":"",  //  <包前缀内容>  十六进制的数据, 如发送ABC时填写414243 , 为<包前缀>为enable时必填
        "frame_end":"disable|hex|ascii|mac", //  <包后缀> 分为disable(禁用), hex为十六制, ascii为字符式, mac使用十六制进的mac地址为包后缀
        "frame_end_string":"",    // <包后缀内容>  十六进制的数据, 如发送ABC时填写414243 , 为<包后缀>为enable时必填

    },
    "server":
    {
        "status":"disable",
        "proto":"tcp",
        "port":"",
        "limit":"",

        "login":"register packet",                // [ disable, hex, ascii, mac ]
                                                            // disable for disable register packet
                                                            // hex for hex string
                                                            // ascii for ascii string
                                                            // mac for hex device mac
        "login_string":"register packet context", // [ string ], such as 414243 when sending ABC when "login" is hex

        "frame_start":"disable|hex|ascii|mac",     // <包前缀> 分为disable(禁用), hex为十六制, ascii为字符式, mac使用十六制进的mac地址为包后缀
        "frame_start_string":"",  //  <包前缀内容>  十六进制的数据, 如发送ABC时填写414243 , 为<包前缀>为enable时必填
        "frame_end":"disable|hex|ascii|mac", //  <包后缀> 分为disable(禁用), hex为十六制, ascii为字符式, mac使用十六制进的mac地址为包后缀
        "frame_end_string":"",    // <包后缀内容>  十六进制的数据, 如发送ABC时填写414243 , 为<包后缀>为enable时必填
    }

}

```

