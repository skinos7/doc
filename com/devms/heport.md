
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

+ `peer[ peer ]` **set peer to talk or he**, *succeed return talk to describes, failed return NULL, error return terror*

+ `talk[ macid, {json command} ]` **talk to peer device**, *succeed return json command return, failed return tfalse, error return terror*

+ `he[ macid, he command ]` **talk to peer device**, *succeed return he command return, failed return tfalse, error return terror*

