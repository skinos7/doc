
***
## device he command management service
all device connect to the service, this service responsible for forwarding with device use he command

#### Configuration( devms@heport )

```json
// attribute introduction
{
    "status":"enable the function",                       // [ disable, enable ]
    "port":"tcp port for device connect",                 // [ number ]
    "control_port":"http port for client connect",        // [ number ]
    "debug_port":"line command port for client connect",  // [ number ]

    "hole_port":"gateway to gateway listen port",         // [ number ]
    "hole2_port":"branch test port",                      // [ number ]
    "hole3_port":"master test prot",                      // [ number ]

    "tcp_keepidle":"idle to keeplive",                    // [ number ], The unit is seconds
    "tcp_keepintvl":"keeplive interval",                  // [ number ], The unit is seconds
    "tcp_keepcnt":"keeplive failed time",                 // [ number ]

    "talk_timeout":"timeout to disconnect"                // [ number ], The unit is seconds
}
```
Examples, show all the configure
```shell
devms@heport
{
    "status":"enable",
    "port":"10001",
    "control_port":"10002",
    "debug_port":"10003"

    "hole_port":"10004",
    "hole2_port":"10005",
    "hole3_port":"10006",

    "tcp_keepidle":"20",
    "tcp_keepintvl":"10",
    "tcp_keepcnt":"3",
    "talk_timeout":"25"
}
```  
Examples, disable the line command port for client connect
```shell
devms@heport:debug_port=
ttrue
```  

#### **Methods**

+ `client_list[]` **get all client list**, *succeed return talk to describes, failed return NULL, error return terror*
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

+ `device_list[]` **get all gateway list**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "gateway mac identify":              // [ number ]: {}
        {
            "online":"online time",                    // [ string ]
            "fd":"file handler number",                // [ number ]
            "addr":"gateway connect ip",               // [ ip address ]
            "port":"gateway connect port",              // [ port ]
            "user":"gateway username",                 // [ string ]
            "key":"heport control key"                 // [ string ]
        }
        // ... more gateway
    }    
    ```

+ `talk[ macid, {json command} ]` **talk to peer device**, *succeed return json command return, failed return tfalse, error return terror*

+ `he[ macid, he command ]` **talk to peer device**, *succeed return he command return, failed return tfalse, error return terror*

