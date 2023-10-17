
***
## IO Management Agent
manage IO

#### Configuration( io@agent )   

```json
// Attributes introduction 
{
    // IO Initial Configuration, set the IO state at the system boot
    "init":
    {
        "io number":"IO state"        // [ "g1", "g2", "g3", "g4", "g5", "g6", ... ]: [ "10", "11", "00", ... ]
                                        // io number can be "g1", "g2", "g3", "g4", "g5", "g6", "g7", "g8", ...
                                        // IO state can be: "10" for output low
                                        //                  "11" for output high
                                        //                  "00" for input mode
                                        //                  "2-100-200" for output timer, 100ms high, 200ms low
        // ... more io state init
    },

    // IO SMS Configuration
    "sms":
    {
        "status":"sms trigger status",          // [ "disable", "enable" ]
        "device":"LTE device name",             // [ "modem@lte", "modem@lte2", "modem@lte3", ... ]
        "contact":"contact number",             // [ phone number ]
        "contact2":"contact number",            // [ phone number ]
        "contact3":"contact number"             // [ phone number ]
    },

    // first client, default is TCP/UDP client configure
    "client":
    {
        "status":"client status",               // [ "disable", "enable" ]
        "proto":"client protocol",              // [ "tcp", "udp" ]
        "server":"server address",              // [ string ]
        "port":"server port",                   // [ number ]
        "interval":"connect failed interval",   // [ number ], the unit is second

        "id":"custom the identify",             // [ string ]
        "user":"custom the username",           // [ string ]
        "vcode":"custom the vocde"              // [ string ]
    },
    // second client, default is MQTT Client configure
    "client2":
    {
        "status":"client status",               // [ "disable", "enable" ]
        "proto":"client protocol",              // [ "tcp", "udp", "mqtt" ]
        "server":"server address",              // [ string ]
        "port":"server port",                   // [ number ]

        "mqtt_id":"device identify",            // [ string ]
        "mqtt_username":"mqtt username",        // [ string ]
        "mqtt_password":"mqtt password",        // [ string ]
        "mqtt_interval":"mqtt connect interval",// [ nubmer ], the unit is second
        "mqtt_keepalive":"mqtt keepalive",      // [ number ], the unit is second
        "mqtt_publish":"mqtt publish topic",    // [ string ]
        "mqtt_publish_qos":"mqtt publish qos",  // [ number ]
        "mqtt_subscribe":
        {
            "subscribe topic":"topic qos",
            "subscribe topic2":"topic2 qos",
            "subscribe topic3":"topic3 qos",
            // "subscribe topic":"topic qos"     How many subscribe topic need setting save how many properties
        }

    }

}
```

Examples, show all the io agnet configure
```shell
io@agent
{
    "init":
    {
        "g1":"10",               # init the g1 output low
        "g2":"11",               # init the g2 output high
        "g3":"00",               # init the g3 input mode
        "g4":"2 200 300"         # init the g4 output timer, 200ms high, 300ms low
    },
    "client":
    {
        "status":"enable",           # enable the tcp/udp client
        "proto":"tcp",               # protocol is tcp
        "server":"io.wmdevice.com",  # sever is io.wmdevice.com
        "port":"9000",               # port is 9000
        "id":"B3223",                # id is B3223, when no settings default is device MAC
        "user":"dimmalex",           # mqtt username is dimmalex
        "vcode":"0815"               # mqtt pasword is 0815
    },
    "client2":
    {
        "status":"enable",            # enable the mqtt client
        "proto":"mqtt",               # protocol is mqtt
        "server":"mqtt.wmdevice.com", # server is mqtt.wmdevice.com
        "port":"1883",                # port is 1883
        "mqtt_id":"",                 # default is device MAC
        "mqtt_username":"dimmalex",   # mqtt username is dimmalex
        "mqtt_password":"0815",       # mqtt pasword is 0815
        "mqtt_keepalive":"10",        # mqtt keeplive is 10 sec
        "mqtt_interval":"5",          # mqtt connect interval is 5 sec
        "mqtt_publish":"d218/io",     # mqtt publish topic is d218/io
        "mqtt_publish_qos":"1",       # mqtt publish qos is 1
        "mqtt_subscribe":
        {
            "d218/order":"2",         # mqtt subscribe d218/order topic, qos is 2
            "route/order":"2"         # mqtt also subscribe route/order topic, qos is 2
        }
    }
}
```  

Examples, disable mqtt client
```shell
io@agent:client2/status=disable
ttrue
```  

Examples, modify the tcp/udp client server
```shell
io@agent:client/server=new.wmdevice.com
ttrue
```  



#### **Methods**

+ `status[]` **get the io agent status**, *succeed return talk to describes infomation, failed reeturn NULL, error return terror*   
    ```json
    // Attributes introduction of talk by the method return
    {
        "state":"current all IO state", // [ string ]
                                            // format is g1=xx;g2=xx;g3=xx;...
                                            // xx is the state, can be 00 for input low
                                                            //  can be 01 for input high
                                                            //  can be 10 for output low
                                                            //  can be 11 for output high
                                                            //  can be 2 for output timer

        // first client, default is TCP/UDP client status
        "client":
        {
            "ip":"server IP",           // [ ip address ]
            "connect":"connect state",  // [ ok ], If the value is ok, it indicates success
            "rx":"recvice byte",        // [ number ]
            "tx":"send byte"            // [ nubmer ]
        },
        // second client, default is MQTT client status
        "client2":
        {
            "ip":"server IP",           // [ ip address ]
            "connect":"connect state",  // [ ok ], If the value is ok, it indicates success
            "rx":"recvice byte",        // [ number ]
            "tx":"send byte"            // [ nubmer ]
        }
    }
    ```

    ```shell
    # examples, get the io agent status
    io@agent.status
    {
        "state":"g1=11;g2=10;g3=01;g4=00;g5=2", # g1 is output high
                                                # g2 is output low
                                                # g3 is input high
                                                # g4 is input low
                                                # g5 is timer output

        "client":  # first client(TCP/UDP) connect succeed, ip is 11.25.53.80, send 977 byte, recive 3498 byte
        {
            "ip":"11.25.53.80",
            "connect":"ok",
            "rx":"3498", 
            "tx":"977"
        },

        "client2":  # first client(TCP/UDP) connect failed or connecting, ip is 11.25.53.88
        {
            "ip":"11.25.53.88"
        }
    }
    ```

+ `modify[ modify io state ]` **modify the io state**, *succeed return talk to describes state after modify, failed return NULL, error return terror*   
    ```json
    // Attributes introduction of talk by the method return
    {
        "state":"current all IO state", // [ string ]
                                            // format is g1=xx;g2=xx;g3=xx;...
                                            // xx is the state, can be 00 for input low
                                                            //  can be 01 for input high
                                                            //  can be 10 for output low
                                                            //  can be 11 for output high
                                                            //  can be 2 for output timer
    }
    ```

    ```shell
    # examples, modify the g1 input, g2 output high, g2 output low
    io@agent.modify[ g1=00;g2=11;g3=10 ]
    {
        "state":"g1=00;g2=11;g3=11;g4=00;g5=2", # g1 is input mode
                                                # g2 is output high
                                                # g3 is input low
                                                # g4 is input low
                                                # g5 is timer output
    }
    ```

    ```shell
    # examples, modify the g1 output high
    io@agent.modify[ g1=11 ]
    {
        "state":"g1=11;g2=11;g3=11;g4=00;g5=2", # g1 is ouput high
                                                # g2 is output high
                                                # g3 is input low
                                                # g4 is input low
                                                # g5 is timer output
    }
    ```

    ```shell
    # examples, modify the g1 output timer for 200ms high, 500ms low
    io@agent.modify[ g1=2-200-500 ]
    {
        "state":"g1=2;g2=11;g3=11;g4=00;g5=2",  # g1 is ouput timer
                                                # g2 is output high
                                                # g3 is input low
                                                # g4 is input low
                                                # g5 is timer output
    }
    ```
