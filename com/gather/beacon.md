***
## Manage skinos device at local network
Manage skonos device at the local network

#### Configuration( gather@beacon )
```json
// Attributes introduction
{
    "status":"beacon for search device",        // [ "disable", "enable" ]
    "port":"beacon udp port",                   // [ nubmer ]
    "interval":"beacon interval",               // [ nubmer ], the unit is second
    "group":"search group name",                // [ string ], default is group of "default"
    "ip":"beacon network ip",                   // [ IP address ], default is 192.168.200.1
    "mask":"beacon network netmask",            // [ network mask ], default is 255.255.255.0
    "dhcps":                                                 // Assign IP addresses and some infomation to found devices
    {
        "status":"Assign IP addresses to found devices",              // [ "disable", "enable" ]
        "startip":"IP addresses pool start",                          // [ IP address ], default is 192.168.200.2
        "endip":"IP address poll end",                                // [ IP address ], default is 192.168.200.254
        "gw":"Assign gateway to found devices",                       // [ IP address ]
        "dns":"Assign dns to found devices",                          // [ IP address ]
        "remote":"Assign remote control server to found devices"      // [ string ]
    }
}
```
Examples, show all the configure
```shell
gather@beacon
{
    "status":"enable",                     # enable the beacon for search device
    "port":"22222",                        # UDP port is 22222
    "ip":"172.32.0.1",                     # beacon network is 172.32.0.1/255.255.0.0
    "mask":"255.255.0.0",
    "dhcps":
    {
        "status":"enable",                 # enable Assign IP addresses to found devices
        "startip":"172.32.0.2",            # IP addresses pool start 172.32.0.2
        "endip":"172.32.254.254"           # IP addresses pool end 172.32.254.254
    }
}
```  
Examples, disable the beacon
```shell
gather@beacon:status=disable
ttrue
```  

#### **Methods**

+ `list[]` **list all the found device**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "MAC Address":              [ mac address ]:{}
        {
            "ip":"IP Address",           [ ip address ]
            "time":"found time"          [ number ] UTC count nubmer
        }
        // ... more device
    }    
    ```
    ```shell
    # examples, get all the found device
    gather@beacon.list
    {
        "88124E200030":              # device is 88:12:4E:20:00:30
        {
            "time":"1608637542",        # found device at UTC 1608637542
            "ip":"192.168.200.2"        # device ip is 192.168.200.2
        },
        "00037F12CC70":              # device is 00:03:7F:12:CC:70
        {
            "time":"1608637542",        # found device at UTC 1608637542
            "ip":"192.168.200.3"        # device ip is 192.168.200.3
        }
    }  
    ```

+ `peer[ [MAC/IP] ]` **set talk device**, *succeed return ttrue, failed return tfalse, error return terror, no paramter return current device*
    ```shell
    # examples, set 88124E231210 to talk
    gather@beacon.peer[ 88124E231210 ]
    true
    # examples, show current talk device
    gather@beacon.peer
    88124E231210    
    ```

+ `talk[ [MAC/IP], {talk he command}, [timeout] ]` **talk to other skinos device**, *succeed return talk, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk he command that need delivery to this interface
    {
        "command identify":"he command in string style",   // [ string ]: [ string ]
        "command identify2":                               // [ string ]: [ json ]
        {
            json style
        }
        // ...more command
    }
    // Attributes introduction of talk by the method return
    {
        "command identify":
        {
            json style for command return
        },
        "command identify2":"string style for command return"
        // ...more command return
    }
    ```
    Examples, talk to 172.32.0.3 for machine configure and machine.status and time zone
    ```shell
    # gather@beacon.talk[ 172.32.0.3, {"1":"machine","2":"machine.status","3":"clock@date:timezone"}, 10 ]
    {
        "1":                              # return for machine configure
        {
            "mode":"misp",
            "name":"ASHYELF-122220",
            "mac":"00:03:7F:12:22:20",
            "macid":"00037F122220",
            "language":"en"
        },
        "2":                              # return for machine.status result
        {
            "mode":"misp",
            "name":"ASHYELF-122220",
            "platform":"smtk2",
            "hardware":"mt7628",
            "custom":"d218",
            "scope":"std",
            "version":"v7.2.0916",
            "livetime":"00:04:23:0",
            "current":"11:20:26:09:18:2022",
            "mac":"00:03:7F:12:22:20",
            "macid":"00037F122220",
            "model":"3218",
            "magic":"373239170121132E"
        },
        "3":"8"                           # return for timezone
    }
    ```

+ `he[ [MAC/IP], he command, [timeout] ]` **talk to other skinos device**, *succeed return talk, failed return NULL, error return terror*
    ```shell
    # Examples, talk to 172.32.0.3, get the machine configure
    gather@beacon.he[172.32.0.3, machine ]
    {
        "mode":"misp",
        "name":"ASHYELF-122220",
        "mac":"00:03:7F:12:22:20",
        "macid":"00037F122220",
        "language":"en"
    }
    # Examples, talk to 172.32.0.3, Determines whether the component ifname@lte exists
    gather@beacon.he[172.32.0.3, .ifname@lte ]
    true
    ```




