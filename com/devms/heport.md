
***
## device he command forwarding service
all device connect to the service, this service responsible for forwarding he command with device


#### Configuration( devms@heport )

```json
// attribute introduction
{
    "status":"enable the function",                       // [ disable, enable ]
    "port":"tcp port for device connect",                 // [ number ]
    "sslport":"ssl tcp port for device connect",          // [ number ]

    "http_port":"http port for client connect",           // [ number ]
    "tcp_port":"line command port for client connect",    // [ number ]
    "https_port":"https port for client connect",         // [ number ]

    "hole_port":"network listen port", // [ number ]
    "hole2_port":"branch test port",                      // [ number ]
    "hole3_port":"master test prot",                      // [ number ]

    "talk_timeout":"timeout to disconnect",               // [ number ], The unit is seconds
    "tcp_keepidle":"idle to keeplive",                    // [ number ], The unit is seconds
    "tcp_keepintvl":"keeplive interval",                  // [ number ], The unit is seconds
    "tcp_keepcnt":"keeplive failed time"                  // [ number ]
}
```
Examples, show all the configure
```shell
devms@heport
{
    "status":"enable",
    "port":"10001",
    "sslport":"10006",

    "http_port":"10002",
    "tcp_port":"10003",
    "https_port":"10007",

    "hole_port":"10005",
    "hole2_port":"10006",
    "hole3_port":"10007",

    "talk_timeout":"25",
    "tcp_keepidle":"20",
    "tcp_keepintvl":"10",
    "tcp_keepcnt":"3"
}
```  
Examples, disable the line command port for client connect
```shell
devms@heport:tcp_port=
ttrue
```  

#### **Methods**

+ `list[]` **get all device list**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "device mac identify":{}              // [ string ]: {}
        // ... more device
    }    
    ```

+ `view[ device mac identify ]` **get device infomation**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "online":"online time",                    // [ string ], HH:MM:SS:DAY
        "fd":"file handler number",                // [ number ]
        "addr":"device connect ip",                // [ ip address ]
        "port":"device connect port",              // [ port ]
        "user":"heport control user",              // [ string ]
        "key":"heport control key"                 // [ string ]
    }
    ```

+ `listv[]` **get all device infomation**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "device mac identify":              // [ string ]: {}
        {
            // sttributes see the view interface return
        }
        // ... more device
    }
    ```

+ `knock[ device mac identify ]` **disconnect the device**, *succeed return ttrue, failed return tfalse, error return terror*



+ `client_list[]` **get all client infomation**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "file handler number":              // [ number ]: {}
        {
            "online":"online time",                    // [ string ]
            "addr":"client ip",                        // [ ip address ]
            "port":"client port"                       // [ port ]
        }
        // ... more client
    }    
    ```



+ `network_list[]` **get all network list**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "network full identify": {}             // [ string]: {}
        // ... more network
    }    
    ```

+ `network_view[ network full identify ]` **get network infomation**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "net":"network endpoint net",              // [ network address ]
        "mask":"network endpoint netmask",         // [ netmask address ]
        "master":"network master nubmer",          // [ number ]
        "branch":"network branch number",          // [ number ]
        "client":"network client number",          // [ number ]
        "leaf":"network leaf number"               // [ number ]
    }
    ```

+ `network_listv[]` **get all network infomation**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "network full identify":             // [ string]: {}
        {
            "net":"network endpoint net",              // [ network address ]
            "mask":"network endpoint netmask",         // [ netmask address ]
            "master":"network master nubmer",          // [ number ]
            "branch":"network branch number",          // [ number ]
            "client":"network client number",          // [ number ]
            "leaf":"network leaf number"               // [ number ]
        }
        // ... more network
    }
    ```

+ `network_device[ network full identify ]` **get network all device infomation**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "device mac identify":
        {
            "net":"device endpoint network address",   // [ network address ]
            "mask":"device endpoint netmask address",  // [ netmask address ]

            "ip":"device endpoint ip address",         // [ ip address ]
            "pubkey":"public key",                     // [ string ], exist when device attach

            "attach":"online time",                    // [ string ], HH:MM:SS:DAY, exist when device attach
            "idle":"idle time",                        // [ string ], HH:MM:SS:DAY, exist when device attach
            "nattype":"device nat type",               // [ "8", "4", "2", "1" ], exist when device attach
            "peer":"device ip address",                // [ ip address ], exist when device attach
            "port":"device port"                       // [ port ], exist when device attach
        }
        // ... more device
    }
    ```

+ `network_dirty[ network full identify ]` **reload the network device configure**, *succeed return ttrue, failed return tfalse, error return terror*

+ `network_knock[ network full identify ]` **clear the network and disconnect all device of network**, *succeed return ttrue, failed return tfalse, error return terror*



+ `talk[ macid, {json command} ]` **talk to peer device**, *succeed return json command return, failed return tfalse, error return terror*

+ `he[ macid, he command ]` **talk to peer device**, *succeed return he command return, failed return tfalse, error return terror*

