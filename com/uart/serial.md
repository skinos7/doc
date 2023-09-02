***
## UART management components
Manage UART. Usually uart@serial is the first UART. If there are multiple UART in the system, uart@serial2 will be the second UART, and increase by degress
**UART application components**: UART implementation manager, uart@nmea, uart@dtu, uart@hetui, uart@modbus, uart@httppost, specified by "concom" in configuration 
**UART device component**: Provides UART information for UART application components, such as modem@lte and modem@lte2, "dev" is specified in the configuration 
**UART Data conversion component**: The UART application component calls the interface of the component for protocol conversion when the UART operator is connected to the data of the peer end. The component must provide the specified interface as required 

#### **configuration( uart@serial )**
**uart@serial** is first UART
**uart@serial2** is second UART

```json
// Attribute introduction
{
    // UART configure
    "status":"UART status",                                      // [ "enable", "disable" ]
    "extern":"extern ifname",                                    // [ "disable", "default", "ifname@wan", "ifname@lte", ... ],
                                                                         // "disable" or space for none
                                                                         // "default" for is defdault gateway
                                                                         // "ifname@wan", "ifname@lte", ... for specified extern interface
    
    "convert":"Whether to enable hardware function conversion",  // [ "disable", "enable" ] 
    "concom":"UART application components",                      // [ "uart@dtu", "uart@nmea", "uart@hetui", "uart@modbus" ]
                                                                        // uart@dtu is DTU mode
                                                                        // uart@nmea is GPS mode
                                                                        // uart@hetui is He command mode
                                                                        // uart@modbus is ModBus
                                                                        // uart@modbusm is ModBus Master
                                                                        // uart@httppost is HTTP POST the uart data
    "dev":"UART device component",                               // [ string ], modem@lte is LTE modem component
    "ttydev":"UART device pathname",                             // [ string ], Specify the serial device file directly

    // serial configure
    "speed":"Baud rate",            // [ "9600", "19200", "38400", "57600", "76800", "115200", "230400" ]
    "flow":"flow control",          // [ "disable", "hard", "soft" ], disable is disable, hard is hardware flow control, soft is software flow control
    "parity":"parity type",         // [ "disable", "even", "odd" ]
    "databit":"data bit",           // [ "5", "6", "7", "8" ]
    "stopbit":"stop bit",           // [ "1", "2" ]

    // This function is used to periodically send data to the serial port to activate the mechanism. After this function is enabled, data is periodically sent to the serial port. This function is valid in DTU mode
    "active":"active packet send to serial",                       // [ "disable", "enable", "idle", "timing" ]
                                                                            // disable for disable
                                                                            // enable for active once
                                                                            // idle for idle Specifies the time to send
                                                                            // timing for interval specifies the time to send
    "active_interval":"Activate packet sending interval",          // [ number ], the unit is second, vaild when "active" is idle or timing
    "active_string":"Contents of activation package",              // [ Hex data ], such as 414243 when sending ABC

    // Serial port reading parameter
    "frame_maxsize":"frame max size",                         // [ number ], frame byte
    "frame_interval":"frame interval",                        // [ number ], the unit is ms

    // Modbus configure vaild when "concom" is uart@modbus
    "modbus":
    {
        "type":"server or client",                                // [ "server", "client" ]

        "server":"server address",                                // [ string ], vaild when "type" be "client"

        "port":"modbus port",                                     // [ number ]
        "maxconn":"Maximum number of simultaneous connections",   // [ number ]
        "timeout":"Connection timeout",                           // [ number ], the unit is ms
        "retries":"retres times",                                 // [ number ]
        "pause":"The interval between requests",                  // [ number ], the unit is ms
        "wait":"Time to wait for a response"                      // [ number ], the unit is ms
    },
 
    // DTU configure vaild when "concom" is uart@dtu
    "dtu":
    {
        "client":                       // MQTT client
        {
            "status":"client status",               // [ "disable", "enable" ]
            "proto":"client protocol",              // [ "tcp", "udp", "mqtt" ]
            "server":"server address",              // [ string ]
            "port":"server port",                   // [ number ]
    
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
        "client2":                      // TCP/UDP client
        {
            "status":"client status",               // [ "disable", "enable" ]
            "proto":"client protocol",              // [ "tcp", "udp" ]
            "server":"server address",              // [ string ]
            "port":"server port",                   // [ number ]
    
            "login":"register packet",                     // [ "disable", "hex", "ascii", "mac" ]
                                                                // disable for disable register packet
                                                                // hex for hex string
                                                                // ascii for ascii string
                                                                // mac for hex device mac
            "login_string":"register packet context",      // [ string ], such as 414243 when sending ABC when "login" is hex

            "keeplive":"keeplive packet",                  // [ "disable", "idle", "timing" ]
            "keeplive_interval":"keeplive interval",       // [ number ], the unit is second
            "keeplive_string":"keeplive packet content",   // [ hex string ]
    
            "frame_start":"packet prefix",                 // [ "disable", "hex", "ascii", "mac" ]
                                                                // disable for disable packet prefix
                                                                // hex for hex string
                                                                // ascii for ascii string
                                                                // mac for hex device mac
            "frame_start_string":"packet prefix context",  // [ string ], such as 414243 when sending ABC when "frame_start" is hex
            
            "frame_end":"packet suffix",                   // [ "disable", "hex", "ascii", "mac" ]
                                                                // disable for disable packet suffix
                                                                // hex for hex string
                                                                // ascii for ascii string
                                                                // mac for hex device mac
            "frame_end_string":"packet suffix context"     // [ string ], such as 414243 when sending ABC when "frame_end" is hex
        },
        
        "server":                      // TCP/UDP server
        {
            "status":"server status",                      // [ "disable", "enable" ]
            "proto":"service tcp",                         // [ "tcp", "udp" ] 
            "port":"service port",                         // [ number ]
            "limit":"concurrence client",                  // [ number ]
    
            "login":"register packet",                     // [ "disable", "hex", "ascii", "mac" ]
                                                                // disable for disable register packet
                                                                // hex for hex string
                                                                // ascii for ascii string
                                                                // mac for hex device mac
            "login_string":"register packet context",      // [ string ], such as 414243 when sending ABC when "login" is hex
 
            "keeplive":"keeplive packet",                  // [ "disable", "idle", "timing" ]
            "keeplive_interval":"keeplive interval",       // [ number ], the unit is second
            "keeplive_string":"keeplive packet content",   // [ hex string ]
    
            "frame_start":"packet prefix",                 // [ "disable", "hex", "ascii", "mac" ]
                                                                // disable for disable packet prefix
                                                                // hex for hex string
                                                                // ascii for ascii string
                                                                // mac for hex device mac
            "frame_start_string":"packet prefix context",  // [ string ], such as 414243 when sending ABC when "frame_start" is hex
            
            "frame_end":"packet suffix",                   // [ "disable", "hex", "ascii", "mac" ]
                                                                // disable for disable packet suffix
                                                                // hex for hex string
                                                                // ascii for ascii string
                                                                // mac for hex device mac
            "frame_end_string":"packet suffix context"     // [ string ], such as 414243 when sending ABC when "frame_end" is hex
    
        }
    },

    // httppost configure vaild when "concom" is uart@httppost
    "httppost":
    {
        "server":"POST server page",                       // [ string ]
        "content":"content type value in post",            // [ string ]
        "connect_timeout":"connect timeout for post",      // [ number ], the unit is second
        "post_timeout":"post timeout"                      // [ number ], the unit is second
    }

}

```


