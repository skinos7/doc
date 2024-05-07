
***
## device port map API
device port map management API, depend on pport
*all methods need username*

#### **Methods**

+ `map_list[ username, device mac identify, [ protocol ] ]` **get the all map rule**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    // that save at $user/tcpamp.json(TCP) or $user/udpamp.json(udp)
    {
        "server port":                           // [ number ]:{}
        {
            "port":"server port",                     // [ number ]
            "macid":"device mac identify",            // [ string ]
            "hand_ip":"device local ip",              // [ ip address ]
            "hand_port":"device local port",          // [ number ]
            "app":"application type"                  // [ "other", "telnet", "ssh", "http" ]
        }
        // ... more map rule
    }
    ```

+ `map_add[ username, device mac identify, local_ip, local_port, [ protocol ], [ app ] ]` **add a map rule**, *succeed return ttrue, failed return tfalse, error return terror*

+ `map_delete[ username, device mac identify, port, [ protocol ] ]` **delete a map rule**, *succeed return tture, failed return tfalse, error return terror*



+ `port_map[ username, device mac identify, local_ip, local_port, [ protocol ] ]` **map a device local port to server for 300 second**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "port":"port number",                    [ number ]
        "macid":"current map device",            [ string ]
        "hand_ip":"current map local ip",        [ ip address ]
        "hand_port":"current map local port"     [ port ]
    }
    ```

+ `port_unmap[ username, device mac identify, port, [ protocol ] ]` **map a device local port to server**, *succeed return tture, failed return tfalse, error return terror*



+ `access_telnet[ username, device mac identify, local_ip, local_port ]` **map a telnet for 300 second to ttyd**, *succeed return string describe the ttyd port, failed return NULL, error return terror*

+ `access_ssh[ username, device mac identify, local_ip, local_port ]` **map a SSHf or 300 second to ttyd**, *succeed return string describe the ttyd port, failed return NULL, error return terror*



+ `ttyd_telnet[ username, port ]` **run the ttyd use telnet on a port**, *succeed return string describe the ttyd port, failed return NULL, error return terror*

+ `ttyd_ssh[ username, port ]` **run the ttyd use SSH on a port**, *succeed return string describe the ttyd port, failed return NULL, error return terror*

