***
## Modem AT Protocol Management
Manage agent for AT to modem

#### Configuration( modem@atport )   

```json
// Attribute introduction
{
    "status":"AT port status",     // [ "enable", "disable" ]

    // Client configure
    "client":                      // TCP/UDP client example
    {
        "status":"client status",                  // [ "disable", "enable" ]
        "proto":"client protocol",                 // [ "tcp", "udp" ]
        "server":"server address",                 // [ string ]
        "port":"server port",                      // [ number ]
        "login":"register packet",                 // [ "disable", "hex", "ascii", "mac" ]
                                                           // disable for disable register packet
                                                           // hex for hex string
                                                           // ascii for ascii string
                                                           // mac for hex device mac
        "login_string":"register packet context"   // [ string ], such as 414243 when sending ABC when "login" is hex
    },

    // Server configure
    "server":
    {
        "status":"server status",                  // [ "disable", "enable" ]
        "proto":"service tcp",                     // [ "tcp", "udp" ] 
        "port":"service port",                     // [ number ]
        "limit":"concurrence client",              // [ number ]
        "login":"register packet",                 // [ "disable", "hex", "ascii", "mac" ]
                                                           // disable for disable register packet
                                                           // hex for hex string
                                                           // ascii for ascii string
                                                           // mac for hex device mac
        "login_string":"register packet context"   // [ string ], such as 414243 when sending ABC when "login" is hex
    }
}

```

Examples, show all the AT port configure
```shell
modem@atport
{
    "status":"enable",                # enable the AT port
    "client":                         # client: connect to tcp port 9000 of 11.43.52.124
    {
        "status":"enable",
        "proto":"tcp",
        "server":"11.43.52.124",
        "port":"9000",
        "login":"disable",
        "login_string":""
    },
    "server":                         # enable the server, the server work on TCP port 6000
    {
        "status":"enable",
        "proto":"tcp",
        "port":"6000",
        "limit":"5"                   # limit the five concurrence client
    }
}
```  

Examples, disable client
```shell
modem@atport:client/status=disable
ttrue
```  

Examples, modify the server port to 8000
```shell
modem@atport:server/port=8000
ttrue
```  



#### **Methods**

+ `status[]` **get the AT port service status**, *succeed return talk to describes, failed return NULL, error return terror*   
    ```json
    // Attributes introduction of talk by the method return
    {
        // source port state
        "source port":                         // [ "modem@atport" ]
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
    # examples, get the current AT port service status
    modem@atport.status
    {
        "modem@atport":                           # receive 24921 byte from source port
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


