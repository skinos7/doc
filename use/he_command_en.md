
## Execute the HE command on the terminal to manage the gateway   
The terminal command line is used to execute the HE command to control the gateway, such as querying gateway information, setting gateway parameters, and restarting or resetting the gateway. The HE command is not only used in the terminal command line, but also supported by many control protocols

You can log in to the gateway using the HE command in several ways:   
- Telnet   
- SSH   
- TTL UART(The baud rate is usually 57600/8-data-bit/1-stop-bit/no flow control/no check)   
- RS232 UART(The baud rate is usually 57600/8-data-bit/1-stop-bit/no flow control/no check)   
- RS485 UART(The baud rate is usually 57600/8-data-bit/1-stop-bit/no flow control/no check)   

##### Telnet client use HE command   
1. First, open the **Telnet Server** in the **<System>** menu of the gateway management web page   
2. After logging in to the gateway through the Telnet client using the user name and password, you can execute the HE command on terminal   

##### SSH client use HE command   
1. First, open the **SSH Server** in the **<System>** menu of the gateway management web page   
2. After logging in to the gateway through the SSH client using the user name and password, you can execute the HE command on terminal   

##### TTL/RS232/RS485 use HE command   
1. First, modify the **Serial#TTL**/**Serial#RS232**/**Serial#485** or **UART**/**UART2**/**UART3** mode to **Command Line** in the **<Application>** menu of the gateway management web page   
2. Use the serial port tool to connect to the serial port of the gateway to execute the HE command   

After entering the terminal command line, the introduction screen is displayed as follows:   
```
               EEEEEEEEE   LL           FFFFFFFFF
               EE          LL           FF
               EE          LL           FF
               EEEEEEEEE   LL           FFFFFFFFF
               EE          LL           FF
               EE          LL           FF
        Ashy   EEEEEEEEE   LLLLLLLLLL   FF

 -----------------------------------------------------------
 Command Help
 -----------------------------------------------------------
 @ ----------------------- List all the component
 <com> ------------------- Show component configure
 <com>. ------------------ List all component interface
 <com>:<config> ---------- Get component configure attribute
 <com>:<config>=<value> -- Set component configure attribute
 -----------------------------------------------------------
 # 
```   
you have successfully logged in to the terminal command line when the command line input prompt (# ) is displayed

---

## HE Command Format

#### **HE Command Introduction**

+ Each command takes a line and ends with a CR. HE commands can be divided into three types:   
	+ **Query configuration**              Used to query the current configuration of some function components of the gateway
	+ **Modify configuration**             Used to modify the configuration of certain gateway components
	+ **Calling component method**         Used to perform some functions of the gateway component operations, such as querying status, starting, and disabling
+ The return type of the command   
	+ **Character string**         Used to represent a single piece of information(The called method returns a string of type talk t), *Prompt a new line with a # space after a newline character*
	+ **ttrue** 或 **tfalse**      ttrue indicates successful operation, tfalse indicates operation failure, *Prompt a new line with a # space after a newline character*
	+ **{JSON}**                   A JSON object that starts with {and ends with} (the called method returns a json structure of type talk_t) is used to represent some complex information., *Prompt a new line with a # space after a newline character*
	+ **Empty**                       Used to indicate that no available information is available(NULL if the called method returns null), *Prompt a new line with a # space after a newline character*

#### **Query configuration**

+ When querying all configurations of the components of the gateway, enter **component name** Press enter
Usually the return value will be a JSON
    ```shell
    # land@machine                    # Query configurations of land@machine (Basic Infomation of Gateway)
    {                                 # Return a complete JSON object
        "mode":"nmisp",                              # gateway operator mode Next Mobile(LTE/NR) Internet Service Provider connection
        "name":"ASHYELF-12AAD0",                     # gateway name is ASHYELF-12AAD0
        "mac":"00:03:7F:12:AA:D0",                   # gateway MAC is 88:12:4E:20:46:B0
        "macid":"00037F12AAD0",                      # gateway serial id is 88124E2046B0
        "language":"cn",                             # gateway language is chinese
        "cfgversion":"1"                             # gateway configure version is 1(hint modify one times)
    }
    # 
    ```   
    > See *[Management of Basic Infomation](../com/land/machine.md)* for more

+ When querying the attributes specified by the component, give the **component name:attribute path** Enter
The return value can be a string or a JSON, depending on the value of the corresponding attribute
    ```shell
    # land@machine:name              # Query the value of the name attribute under the land@machine component configuration
    A218-120108                      # Return a string
    # 
    ```   
+ When a component has many levels of attributes, **attribute path** will separate the multiple layers of **attribute names** with a **/**. The attribute path is used to locate the attributes, as follows
    ```shell
    # ifname@lan:static              # Query the value of the static attribute under the ifname@lan(LAN Network Management) component configuration
    {
        "ip":"192.168.8.1",
        "mask":"255.255.255.0"
    }
    # ifname@lan:static/ip           # Query the value of the ip attribute under the static attribute of the ifname@lan(LAN Network Management) component configuration
    192.168.8.1
    # 
    ```   
    > See *[LAN Network Management](../com/ifname/lan.md)* for more

    The above are passed by **attribute/subordinate attribute/subordinate attribute/...** This path-like way to locate multiple layer attributes

#### **Modify configuration**

+ Modifying the component configuration is similar to querying the component configuration, first giving the **component name**, then giving the **attribute path** to modify the attribute, and finally giving the **value**
    When modifying the value of the entire component:
    ```shell
    component name=value
    ```   
    When modifying the value of an entire component, usually the value must be a JSON(start with {and end with})
    **ttrue** is returned if the modification succeeds, **tfalse** is returned if the modification fails. See the following example
    ```shell
    # forward@alg               # Query the ALG configuration
    {
        "amanda":"disable",
        "ftp":"enable",
        "h323":"disable",
        "irc":"disable",
        "pptp":"enable",
        "gre":"enable",
        "rtsp":"enable",
        "sip":"enable",
        "snmp":"disable",
        "tftp":"disable",
        "udplite":"disable"
    }
    #
    # forward@alg={"amanda":"enable","ftp":"enable","h323":"enable","irc":"enable","pptp":"enable","gre":"enable""rtsp":"enable","sip":"enable","snmp":"enable","tftp":"enable","udplite":"enable"}   # Modify the entire ALG configuration
    ttrue                          # ttrue is returned, the change is successful
    # forward@alg                  # After the configuration is modified, check the configuration again
    {
        "amanda":"enable",
        "ftp":"enable",
        "h323":"enable",
        "irc":"enable",
        "pptp":"enable",
        "gre":"enable",
        "rtsp":"enable",
        "sip":"enable",
        "snmp":"enable",
        "tftp":"enable",
        "udplite":"enable"
    }
    # 
    ```   
    > See *[Management of Application Layer Gateway](../com/forward/alg.md)* for more

+ When modifying a component specified attribute:
    ```shell
    component name:attribute path=value
    ```   
    The value can be a JSON(starting with {and ending with}) or a string
    **ttrue** is returned if the modification succeeds, **tfalse** is returned if the modification fails. See the following example
    ```shell
    # gnss@nmea                               # Query the GNSS configuration
    {
        "status":"enable",
        "client":
        {
            "status":"disable",
            "proto":"tcp",
            "server":"",
            "port":"9000",
            "id":"",
            "user":"",
            "vcode":"",
            "login":"",
            "login_string":"",
            "frame_start":"disable",
            "frame_string_string":"",
            "frame_end":"disable",
            "frame_end_string":""
        },
        "client2":
        {
            "status":"disable",
            "proto":"mqtt",
            "server":"",
            "port":"1883",
            "mqtt_id":"",
            "mqtt_username":"",
            "mqtt_password":"",
            "mqtt_keepalive":"10",
            "mqtt_interval":"",
            "mqtt_publish":"",
            "mqtt_publish_qos":"",
            "mqtt_subscribe":
            {
            }
        },
        "server":
        {
            "status":"disable",
            "proto":"tcp",
            "port":"",
            "limit":"5"
        }
    }
	# gnss@nmea:client                        # Query the client attribute in GNSS configuration
    {
        "status":"disable",
        "proto":"tcp",
        "server":"",
        "port":"9000",
        "id":"",
        "user":"",
        "vcode":"",
        "login":"",
        "login_string":"",
        "frame_start":"disable",
        "frame_string_string":"",
        "frame_end":"disable",
        "frame_end_string":""
    }
	# gnss@nmea:client={"status":"enable","server":"192.168.8.250","port":"8000","interval":"30","id":"2232"}  # Modify the client attribute in gnss@nmea(GNSS configuration)
	ttrue
	# gnss@nmea:client                       # Query the result of modifying the client attributes in ugnss@nmea(GNSS configuration)
    {
        "status":"enable",
        "server":"192.168.8.250",
        "port":"8000",
        "interval":"30",
        "id":"2232"
    }
	# gnss@nmea:client/server=192.168.8.251  # Change the value of the server attribute under the gnss@nmea(GPS management)client attribute
	ttrue
	# gnss@nmea:client                       # After the configuration is modified, check the configuration again
	{
	    "status":"enable",
	    "server":"192.168.8.251",
	    "port":"8000",
	    "interval":"30",
	    "id":"2232"
	}
	# gnss@nmea                              # Query the all of GNSS configuration
    {
        "status":"enable",
        "client":
        {
            "status":"enable",
            "server":"192.168.8.251",
            "port":"8000",
            "interval":"30",
            "id":"2232"
        },
        "client2":
        {
            "status":"disable",
            "proto":"mqtt",
            "server":"",
            "port":"1883",
            "mqtt_id":"",
            "mqtt_username":"",
            "mqtt_password":"",
            "mqtt_keepalive":"10",
            "mqtt_interval":"",
            "mqtt_publish":"",
            "mqtt_publish_qos":"",
            "mqtt_subscribe":
            {
            }
        },
        "server":
        {
            "status":"disable",
            "proto":"tcp",
            "port":"",
            "limit":"5"
        }
    }
	# 
    ```   
    > See *[GNSS NEMA Protocol Management](../com/gnss/nmea.md)* for more
 
+ When modifying several specified attributes without affecting others:
    ```shell
    component name|{“attribute1”:”value1”, “attribute2”:”value2” , “attribute3”:”value3”}
    ```   
    value1, value2, value3 is usually a string
    **ttrue** is returned if the modification succeeds, **tfalse** is returned if the modification fails. See the following example
    ```shell
	# gnss@nmea:client                      # Query the client attribute in GNSS configuration
	{
	    "status":"enable",
	    "server":"192.168.8.251",
	    "port":"8000",
	    "interval":"30",
	    "id":"2232"
	}
	# gnss@nmea:client|{"status":"disable","server":"192.168.2.11","proto":"tcp"}  # Modify the several value of the client attributes of gnss@nmea(GNSS configuration)
	ttrue
	# gnss@nmea:client                      # After the configuration is modified, check the configuration again
	{
        "status":"disable",
        "server":"192.168.2.11",
        "port":"8000",
        "interval":"30",
        "id":"2232",
        "proto":"tcp"
	}
	# 
    ```   
    > See *[GNSS NEMA Protocol Management](../com/gnss/nmea.md)* for more
 
+ To clear a attribute of a component configuration, press Enter after the =:
    ```shell
    component name:attribute path=
    ```   
    **ttrue** is returned if the modification succeeds, **tfalse** is returned if the modification fails. See the following example
    ```shell
    # gnss@nmea                         # Query the all of GNSS configuration
    {
        "status":"enable",
        "client":
        {
            "status":"disable",
            "server":"192.168.2.11",
            "port":"8000",
            "interval":"30",
            "id":"2232",
            "proto":"tcp"
        },
        "client2":
        {
            "status":"disable",
            "proto":"mqtt",
            "server":"",
            "port":"1883",
            "mqtt_id":"",
            "mqtt_username":"",
            "mqtt_password":"",
            "mqtt_keepalive":"10",
            "mqtt_interval":"",
            "mqtt_publish":"",
            "mqtt_publish_qos":"",
            "mqtt_subscribe":
            {
            }
        },
        "server":
        {
            "status":"disable",
            "proto":"tcp",
            "port":"",
            "limit":"5"
        }
    }
	# gnss@nmea:client=                 # Clear the client attribute of gnss@nmea(GNSS configuration)
	ttrue
	# gnss@nmea                         # After the configuration is modified, check the configuration again
    {
        "status":"enable",
        "client2":
        {
            "status":"disable",
            "proto":"mqtt",
            "server":"",
            "port":"1883",
            "mqtt_id":"",
            "mqtt_username":"",
            "mqtt_password":"",
            "mqtt_keepalive":"10",
            "mqtt_interval":"",
            "mqtt_publish":"",
            "mqtt_publish_qos":"",
            "mqtt_subscribe":
            {
            }
        },
        "server":
        {
            "status":"disable",
            "proto":"tcp",
            "port":"",
            "limit":"5"
        }
    }
	# 
    ```   
    > See *[GNSS NEMA Protocol Management](../com/gnss/nmea.md)* for more
 


#### **Calling component method**

To call a component method, you need to give the component name and method name, parameters can also be given if any
+ When a component method is called without arguments    
    ```shell
    component name.component method
    ```   
    ```shell
    # client@station.list                     # Call the list method of client@station(Client Access) to get the current list of clients
    {
        "B4:2E:99:3F:ED:12":
        {
            "ip":"192.168.8.250",
            "device":"lan"
        }
    }
    # 
    ```   
    > See *[Management of Client Access](../com/client/station.md)* for more

+ When calling a component method with parameters
    ```shell
    component name.component method[ parameter ]
    ```   
    ```shell
    # clock@date.ntpsync[ntp1.aliyun.com]       # Call the ntpsync method of clock@date(System Date) to synchronize time by NTP with ntp1.aliyun.com
    ttrue
    # 
    ```   
    > See *[Manage System Date](../com/clock/date.md)* for more
     
+ When calling a component method with multiple parameters
    ```shell
    component name.component method[ parameter1, parameter2, parameter3, ... ]
    ```   
    ```shell
    # land@auth.add[,xiaomi,4431232]  # Call the add of land@auth to add an account with the first parameter empty (none), the second parameter xiaomi, and the third 4431232
    ttrue
    # land@auth.list                  # Call and@auth's list method to get all the current accounts
    {
        "admin":
        {
            "key":"|*|V223KJDFLKJLKJA23232323543453453452323KJKHUI2KJKHKJKJKH22232321334"
        },
        "xiaomi":
        {
            "key":"|*|V24E4555304E4455784E304530524455304E446B33515452454E6A637A52444E45"
        }
    }
    ```   
    > See *[Username/Password and Permission Management](../com/land/auth.md)* for more

+ When a component method is called to return JSON, you can ask that only the attribute values specified in the JSON be returned
    ```shell
    component name.component method:attribute path
    ```   
    ```shell
    # ifname@lte.status                        # Call the status method of ifname@lte to query the status of the first LTE connection
    {
        "mode":"dhcpc",
        "ifname":"ifname@lte",
        "netdev":"usb1",
        "gw":"10.33.13.104",
        "dns":"120.80.80.80",
        "dns2":"221.5.88.88",
        "ifdev":"modem@lte2",
        "ontime":"754",
        "metric":"10",
        "status":"up",
        "ip":"10.33.13.103",
        "mask":"255.255.255.240",
        "livetime":"05:03:36:0",
        "rx_bytes":"2681665",
        "rx_packets":"27616",
        "tx_bytes":"1433806",
        "tx_packets":"21926",
        "mac":"02:50:F4:00:00:00",
        "tid":"2",
        "devcom":"modem@device",
        "name":"Quectel-EC2X",
        "imei":"864337056708978",
        "mversion":"20CEFHLGR06A05M1G",
        "iccid":"89860121801097564807",
        "imsi":"460015356123463",
        "pcid":"184",
        "lac":"2604",
        "ci":"6DA5A09",
        "netera":"4G",
        "rsrp":"-96",
        "nettype":"FDD LTE",
        "rssi":"-66",
        "rsrq":"-9",
        "sinr":"-19",
        "band":"LTE BAND 3",
        "plmn":"46001",
        "csq":"25",
        "signal":"4",
        "operator":"ChinaUnion"
        "operator_advise":
        {
            "name":"ChinaUnion",
            "dial":"*99#",
            "apn":"3gnet"
        },
        "state":"connected"
    }
    # ifname@lte.status:ip                   # Call the status method of ifname@lte, only query the ip address in the state of the first LTE connection
    10.33.13.103
    # ifname@lte.status:operator_advise      # Call the status method of ifname@lte, only query the operator_advise in the state of the first LTE connection
    {
        "name":"ChinaUnion",
        "dial":"*99#",
        "apn":"3gnet"
    }
    # ifname@lte.status:operator_advise/apn  # Call the status method of ifname@lte, only query the APN in the state of the first LTE connection
    3gnet
    ```   
    > See *[LTE/NR Network Management](../com/ifname/lte.md)* for more



---
## Common HE Command
The following describes common HE commands, such as query LTE/NR information, GNSS information, and reset gateway commands. For more commands, see the interface documentation of each component

#### **Obtain the basic gateway configuration**   
Enter
```shell
# land@machine
```   
Return
```shell
{
    "mode":"nmisp",                              # gateway operator mode Next Mobile(LTE/NR) Internet Service Provider connection
    "name":"ASHYELF-12AAD0",                     # gateway name is ASHYELF-12AAD0
    "mac":"00:03:7F:12:AA:D0",                   # gateway MAC is 88:12:4E:20:46:B0
    "macid":"00037F12AAD0",                      # gateway serial id is 88124E2046B0
    "language":"cn",                             # gateway language is chinese
    "cfgversion":"1"                             # gateway configure version is 1(hint modify one times)
}
```   
Click [Management of Basic Infomation](../com/land/machine.md) to see more

#### **Obtain the basic gateway status**   
Enter
```shell
# land@machine.status
```   
Return
```shell
{
    "mode":"nmisp",                                   # gateway operator mode Next Mobile(NR/LTE) Internet Service Provider connection
    "name":"ASHYELF-12AAD0",                          # gateway name is ASHYELF-12AAD0
    "platform":"smtk2",                               # gateway platform identify is smtk2( hint the basic sdk is second release of smtk )
    "hardware":"mt7621",                              # gateway hardware identify is mt7621( hint the chip is MT7621 )
    "custom":"d228",                                  # gateway custom identify is d228( hint the product name is D228 )
    "scope":"std",                                    # gateway scope identify is std( hint this is a standand release for D228 )
    "version":"tiger7-20220218",                      # gateway version is tiger7-20220218( hint the version publish at 2022.02.18 )
    "livetime":"00:06:35:0",                          # gateway It has been running for 6 minutes and 35 seconds
    "current":"14:54:30:05:04:2022",                  # current date is 2022.05.04, It's 14:54 and 30 seconds
    "mac":"00:03:7F:12:AA:D0",                        # gateway MAC is 00:03:7F:12:AA:D0
    "macid":"00037F12AAD0",                           # gateway serial id is 00037F12AAD0
    "model":"5228"                                    # gateway model is 5228
}
```   
Click [Management of Basic Infomation](../com/land/machine.md) to see more



#### **Obtain LTE/NR network status information**   
Enter
```shell
# ifname@lte.status
```   
Return
```shell
{
    "mode":"dhcpc",                    # IPv4 connect mode is DHCP
    "netdev":"usb0",                   # netdev is usb0
    "gw":"10.137.89.118",              # gateway is 10.137.89.118
    "dns":"120.80.80.80",              # dns is 120.80.80.80
    "dns2":"221.5.88.88",              # backup dns is 221.5.88.88
    "status":"up",                     # connect is succeed
    "ip":"10.137.89.117",              # ip address is 10.137.89.117
    "mask":"255.255.255.252",          # network mask is 255.255.255.252
    "livetime":"00:15:50:0",           # already online 15 minute and 50 second
    "rx_bytes":"1256",                 # receive 1256 bytes
    "rx_packets":"4",                  # receive 4 packets
    "tx_bytes":"1320",                 # send 1320 bytes
    "tx_packets":"4",                  # send 4 packets
    "mac":"02:50:F4:00:00:00",         # netdev MAC address is 02:50:F4:00:00:00
    "method":"slaac",                  # IPv6 address mode is slaac
    "addr":"fe80::50:f4ff:fe00:0",     # local IPv6 address is fe80::50:f4ff:fe00:0
    "imei":"867160040494084",          # imei is 867160040494084
    "imsi":"460015356123463",          # imei is 460015356123463
    "iccid":"89860121801097564807",    # imei is 89860121801097564807
    "csq":"3",                         # CSQ nubmer is 3
    "signal":"3",                      # signal level is 3
    "state":"connect",                 # state is connect to the internet
    "plmn":"46001",                    # plmn is 46001
    "nettype":"WCDMA",                 # nettype is WCDMA
    "rssi":"-107",                     # signal intensity is -107
    "operator":"ChinaUnion",           # operator name is ChinaUnion
    "operator_advise":                 # recommended profile for ChinaUnion
    {
        "name":"ChinaUnion",               # name is ChinaUnion
        "dial":"*99#",                     # dial number is *99#
        "apn":"3gnet"                      # APN is 3gnet
    }
}
```   
Click [LTE/NR Network Management](../com/ifname/lte.md) and [LTE/NR Modem Management](../com/modem/lte.md) to see more

#### **Get the second LTE/NR network status information**   
Enter
```shell
# ifname@lte2.status
```   
Return
```shell
{
    Same as the return for ifname@lte
}
```   
Click [LTE/NR Network Management](../com/ifname/lte.md) and [LTE/NR Modem Management](../com/modem/lte.md) to see more

#### **Disconnect(Shutdown) LTE/NR network**   
Enter
```shell
# ifname@lte.shut
```   
Return
```shell
ttrue
```   
Click [LTE/NR Network Management](../com/ifname/lte.md) to see more

#### **Connect(Setup) to LTE/NR network**   
Enter
```shell
# ifname@lte.setup
```   
Return
```shell
ttrue
```   
Click [LTE/NR Network Management](../com/ifname/lte.md) to see more

#### **Modify the LTE/NR network to disabled**   
Enter
```shell
# ifname@lte:status=disable
```   
Return
```shell
ttrue
```   
Click [LTE/NR Network Management](../com/ifname/lte.md) to see more

#### **Modify the LTE/NR network to enabled**   
Enter
```shell
# ifname@lte:status=enable
```   
Return
```shell
ttrue
```   
Click [LTE/NR Network Management](../com/ifname/lte.md) to see more

#### **Modify the LTE/NR modem dail APN/Username/Password**   
Enter
```shell
# ifname@lte|{ "profile":"enable", "profile_cfg":{ "apn":"NewAPN", "user":"NewUser", "passwd":"NewPassword" } }
```   
Return
```shell
ttrue
```   
Click [LTE/NR Network Management](../com/ifname/lte.md) and [LTE/NR Modem Management](../com/modem/lte.md) to see more

#### **Enable Location function of LTE/NR modem**   
Enter
```shell
# ifname@lte:gnss=enable
```   
Return
```shell
ttrue
```   
Click [LTE/NR Network Management](../com/ifname/lte.md) and [LTE/NR Modem Management](../com/modem/lte.md) to see more



#### **Obtain client information**   
Enter
```shell
# client@station.list
```   
Return
```shell
{
    "04:CF:8C:39:91:7A":            # first client
    {
        "ip":"192.168.31.140",                        # ip is 192.168.31.140
        "name":"xiaomi-aircondition-ma2_mibt917A",    # hostname is xiaomi-aircondition-ma2_mibt917A
        "tx_bytes":"1779693",                         # sent 1779693 byte
        "rx_bytes":"1375610",                         # recived 1375610 byte
        "livetime":"14:39:34:1"                       # livetime is 1 day 14 hour 39 minute 34 second
    },
    "40:31:3C:B5:6D:4C":            # second client
    {
        "ip":"192.168.31.61",
        "name":"minij-washer-v5_mibt6D4C",
        "livetime":"14:39:26:1"
    },
    "14:13:46:C9:97:C7":            # third client
    {
        "ip":"192.168.31.9",
        "name":"",
        "livetime":"14:39:27:1"
    }
}
```   
Click [Management of Client Access](../com/client/station.md) to see more


#### **Obtain location information**   
Enter
```shell
# gnss@nmea.info
```   
Return
```shell
{
    "step":"located",                           # already located
    "utc":"7:55:22:7:12:2021",                  # UTC
    "lon":"11356.56400",
    "lat":"2240.80119",
    "longitude":"113.94273",                    # longitude is 113.94
    "latitude":"22.68001",                      # latitude is 22.68
    "speed":"0.34",
    "elv":"77.90",
    "direction":"",
    "declination":"",
    "inuse":"8"                                 # 8 sat in use
}
```   
Click [GNSS NEMA Protocol Management](../com/gnss/nmea.md) to see more


#### **Obtain the information about the gateway LAN network**   
Enter
```shell
# ifname@lan.status
```   
Return
```shell
{
    "mode":"static",                   # IPv4 connect mode is static
    "netdev":"lan",                    # netdev is lan
    "status":"up",                     # connect is succeed
    "ip":"192.168.1.1",                # ip address is 192.168.1.1
    "mask":"255.255.255.0",            # network mask is 255.255.255.0
    "livetime":"01:15:50:0",           # already online 1 hour and 15 minute and 50 second
    "rx_bytes":"1256",                 # receive 1256 bytes
    "rx_packets":"4",                  # receive 4 packets
    "tx_bytes":"1320",                 # send 1320 bytes
    "tx_packets":"4",                  # send 4 packets
    "mac":"02:50:F4:00:00:00",         # netdev MAC address is 02:50:F4:00:00:00
    "method":"slaac",                  # IPv6 address mode is slaac
    "addr":"fe80::50:f4ff:fe00:0"      # local IPv6 address is fe80::50:f4ff:fe00:0
```  
Click [LAN Network Management](../com/ifname/lan.md) to see more



#### **Reboot gateway**   
Enter
```shell
# land@machine.restart
```   
The gateway does not return any information and will restart immediately
Click [Management of Basic Infomation](../com/land/machine.md) to see more

#### **Reset gateway(restore default settings)**   
Enter
```shell
# land@machine.default
```
The gateway does not return any information and will restart and default immediately
Click [Management of Basic Infomation](../com/land/machine.md) to see more



#### **Enable GNSS function**   
Enter
```shell
# gnss@nmea:status=enable
```   
Return
```shell
ttrue
```   
Click [GNSS NEMA Protocol Management](../com/gnss/nmea.md) to see more



#### **Modify the SSID name of a wireless hotspot (2.4G)**   
Enter
```shell
# wifi@nssid:ssid=NewSSID
```   
Return
```shell
ttrue
```   
Click [2.4G SSID Management](../com/wifi/nssid.md) to see more

#### **Modify the SSID password of a wireless hotspot (2.4G)**   
Enter
```shell
# wifi@nssid:wpa_key=NewPassword
```   
Return
```shell
ttrue
```   
Click [2.4G SSID Management](../com/wifi/nssid.md) to see more

#### **Modify the SSID name and password of the wireless hotspot (2.4G)**   
Enter
```shell
# wifi@nssid|{"ssid":"NewSSID","secure":"wpapskwpa2psk","wpa_key":"NewPassword"}
```   
Return
```shell
ttrue
```   
Click [2.4G SSID Management](../com/wifi/nssid.md) to see more

#### **Modify the SSID name of a wireless hotspot (5.8G)**   
Enter
```shell
# wifi@assid:ssid=NewSSID
```   
Return
```shell
ttrue
```   
Click [5.8G SSID Management](../com/wifi/assid.md) to see more

#### **Modify the SSID password of a wireless hotspot (5.8G)**   
Enter
```shell
# wifi@assid:wpa_key=NewPassword
```   
Return
```shell
ttrue
```   
Click [5.8G SSID Management](../com/wifi/assid.md) to see more

#### **Modify the SSID name and password of the wireless hotspot (5.8G)**   
Enter
```shell
# wifi@assid|{"ssid":"NewSSID","secure":"wpapskwpa2psk","wpa_key":"NewPassword"}
```   
Return
```shell
ttrue
```   
Click [5.8G SSID Management](../com/wifi/assid.md) to see more



#### **Modify the WISP(2.4G) connect other AP**   
the gateway operation mode must be **WISP(2.4G)** or **Mix**
Enter
```shell
# ifname@wisp|{"status":"enable","peer":"NewAP","secure":"wpapskwpa2psk","wpa_key":"NewPassword"}
```   
Return
```shell
ttrue
```   
Click [WISP Network Management](../com/ifname/wisp.md) to see more

#### **Modify the WISP(2.4G) network to disabled**   
the gateway operation mode must be **WISP(2.4G)** or **Mix**
Enter
```shell
# ifname@wisp:status=disable
```   
Return
```shell
ttrue
```   
Click [WISP Network Management](../com/ifname/wisp.md) to see more

#### **Modify the WISP(2.4G) network to enabled**   
the gateway operation mode must be **WISP(2.4G)** or **Mix**
Enter
```shell
# ifname@wisp:status=enable
```   
Return
```shell
ttrue
```   
Click [WISP Network Management](../com/ifname/wisp.md) to see more

#### **Disconnect(Shutdown) WISP(2.4G) network**   
the gateway operation mode must be **WISP(2.4G)** or **Mix**
Enter
```shell
# ifname@wisp.shut
```   
Return
```shell
ttrue
```   
Click [WISP Network Management](../com/ifname/wisp.md) to see more

#### **Connect(Setup) to WISP(2.4G) network**    
the gateway operation mode must be **WISP(2.4G)** or **Mix**
Enter
```shell
# ifname@wisp.setup
```   
Return
```shell
ttrue
```   
Click [WISP Network Management](../com/ifname/wisp.md) to see more

#### **Modify the WISP(5.8G) connect other AP**   
the gateway operation mode must be **WISP(5.8G)** or **Mix** and the gateway have 5.8G radio
Enter
```shell
# ifname@wisp2|{"status":"enable","peer":"NewAP","secure":"wpapskwpa2psk","wpa_key":"NewPassword"}
```   
Return
```shell
ttrue
```   
Click [WISP Network Management](../com/ifname/wisp.md) to see more

#### **Modify the WISP(5.8G) network to disabled**   
the gateway operation mode must be **WISP(5.8G)** or **Mix** and the gateway have 5.8G radio
Enter
```shell
# ifname@wisp2:status=disable
```   
Return
```shell
ttrue
```   
Click [WISP Network Management](../com/ifname/wisp.md) to see more

#### **Modify the WISP(5.8G) network to enabled**   
the gateway operation mode must be **WISP(5.8G)** or **Mix** and the gateway have 5.8G radio
Enter
```shell
# ifname@wisp2:status=enable
```   
Return
```shell
ttrue
```   
Click [WISP Network Management](../com/ifname/wisp.md) to see more

#### **Disconnect(Shutdown) WISP(5.8G) network**   
the gateway operation mode must be **WISP(5.8G)** or **Mix** and the gateway have 5.8G radio
Enter
```shell
# ifname@wisp2.shut
```   
Return
```shell
ttrue
```   
Click [WISP Network Management](../com/ifname/wisp.md) to see more

#### **Connect(Setup) to WISP(5.8G) network**   
the gateway operation mode must be **WISP(5.8G)** or **Mix** and the gateway have 5.8G radio
Enter
```shell
# ifname@wisp2.setup
```   
Return
```shell
ttrue
```   
Click [WISP Network Management](../com/ifname/wisp.md) to see more



#### **Modify the password of the admin user**   
Enter
```shell
# land@auth.modify[,admin,OldPassword,NewPassword]
```   
Return
```shell
ttrue
```   
Click [Username/Password and Permission Management](../com/land/auth.md) to see more


#### **Add policy-based route rule for force source ip(192.168.8.2.12) route to first LTE/NR, named it senser**   
Enter
```shell
# forward@rule.add[ senser,192.168.2.12, , , , 1, 33000 ]
```   
Return
```shell
ttrue
```   
Click [Policy based routing](../com/forward/rule.md) to see more

#### **Add policy-based route rule for force all ip route to second LTE/NR, named it video**   
Enter
```shell
# forward@rule.add[ video, , , , , 2, 33000 ]
```   
Return
```shell
ttrue
```   
Click [Policy based routing](../com/forward/rule.md) to see more

#### **Delete policy-based route rule named senser**   
Enter
```shell
# forward@rule.delete[ senser ]
```   
Return
```shell
ttrue
```   
Click [Policy based routing](../com/forward/rule.md) to see more

#### **Delete policy-based route rule named video**   
Enter
```shell
# forward@rule.delete[ video ]
```   
Return
```shell
ttrue
```   
Click [Policy based routing](../com/forward/rule.md) to see more



---
##  Reference the component documentation to manage the gateway using the HE command

There are two ways to query all component documentation, Each function of the gateway can be managed through these component documents
- Access [Online component documentation](../com/) View component documentation, an online file that is dynamically added and revised as new features are developed
- Contact technical support

#### Component documentation points   
- In [Online component documentation](../com/) projects in the system are listed in the form of a directory, and each project contains component documents
- Clicking on a project to enter the project will list all the component documents under this project
- Click on the component to open the component document, which begins with a function description
- Then there is **Configuration**. Configuration is in JSON format, There are also examples of queries or modifications, The configuration can be queried or modified in the HE command
- This is usually followed by an introduction to the **Methods** of this component, There are also examples of calls, which can be called in the HE command

#### Reference document query component configuration   
The component name is given in the **Configuration**, for example [Syslog Management](../com/land/syslog.md) component name is **land@syslog**

- Enter **component name** all configurations for this component are returned, The attributes and examples of each configuration are described detailedly in **Configuration** in the component documentation
    ```shell
    # land@syslog                   # Enter component name
    {                               # Reutn a json of all the component configuration
        "status":"enable",                # enable the syslog functions
        "location":"memory",              # logs stored in memory, restart will be lost
        "type":"arch|land|default",       # log the arch, land, default log
        "level":"info",                   # log level is normal infomation
        "trace":"disable",                # disable the code information
        "size":"100",                     # log buffer is 100k
        "remote":"192.168.8.250",         # send the syslog to remote server 192.168.8.250
        "port":"514"                      # send the syslog to remote server port 514
    }
    #
    ```

- Queries the attributes specified in the component configuration, You only need to give the specified attribute with the **attribute path** after the **component name**
    ```shell
    # land@syslog:level                     # Query the value of the level attribute
    info                                    # value of level is info
    #
    ```

#### Refer to the component documentation to modify the component configuration   
Refer to [Syslog Management](../com/land/syslog.md), The attributes described in **Configuration** of the document can be modified in the terminal by **component name** followed by **attribute path** followed by **value**
- Modify the remote attribute of the land@syslog remote log server on the terminal
    ```shell
    # land@syslog:remote=192.168.8.250       # Change the value of remote to 192.168.8.250
    ttrue                                    # Return ttrue successfully
    #
    ```

- Modify multiple attributes of land@syslogd on the terminal at the same time. When modifying multiple attributes, encapsulate the attributes to be modified in JSON format. Modifying the remote and port attributes does not affect other attributes
    ```shell
    # land@syslog|{"remote":"192.168.8.251","port":"500"}    # Change the value of remote to 192.168.8.251 and value of port to 500
    ttrue                                                    # Return ttrue successfully
    #
    ```

- Set land@syslogd in the terminal. All configurations and component configurations are JSON. To modify all configurations, you must provide the same JSON
    ```shell
    # land@syslog={"status":"enable","location":"memory","type":"default|init","level":"info","trace":"disable","size":"100"}
    ttrue                                    # Return ttrue successfully
    #
    ```

#### call a component method by referring to the component documentation   
Refer to [Syslog Management](../com/land/syslog.md), Methods described in the documentation **Methods** can be calle on the terminal by **component name**.**component method**
- call the component land@syslog's show method to display the current log
    ```shell
    # land@syslog.show
    Dec 15 15:47:20 V520-12CC70 user.warn syslog: modem@lte check simcard failed 102 times
    Dec 15 15:47:25 V520-12CC70 user.warn syslog: modem@lte check simcard failed 103 times
    Dec 15 15:47:30 V520-12CC70 user.warn syslog: modem@lte check simcard failed 104 times
    Dec 15 15:47:35 V520-12CC70 user.warn syslog: modem@lte check simcard failed 105 times
    Dec 15 15:47:40 V520-12CC70 user.warn syslog: modem@lte check simcard failed 106 times
    Dec 15 15:47:45 V520-12CC70 user.warn syslog: modem@lte check simcard failed 107 times
    Dec 15 15:47:50 V520-12CC70 user.warn syslog: modem@lte check simcard failed 108 times
    Dec 15 15:47:55 V520-12CC70 user.warn syslog: modem@lte check simcard failed 109 times
    Dec 15 15:48:00 V520-12CC70 user.warn syslog: modem@lte check simcard failed 110 times
    Dec 15 15:48:05 V520-12CC70 user.warn syslog: modem@lte check simcard failed 111 times
    Dec 15 15:48:10 V520-12CC70 user.warn syslog: modem@lte check simcard failed 112 times
    Dec 15 15:48:15 V520-12CC70 user.warn syslog: modem@lte check simcard failed 113 times
    Dec 15 15:48:20 V520-12CC70 user.warn syslog: modem@lte check simcard failed 114 times
    Dec 15 15:48:25 V520-12CC70 user.warn syslog: modem@lte check simcard failed 115 times
    Dec 15 15:48:30 V520-12CC70 user.warn syslog: modem@lte check simcard failed 116 times
    Dec 15 15:48:35 V520-12CC70 user.warn syslog: modem@lte check simcard failed 117 times
    #
    ```
- Call the clear method of component land@syslog to clear all current logs
    ```shell
    # land@syslog.clear
    ttrue
    #
    ```



##  How do I access the Linux Shell command line in the terminal

If you need to enter the familiar Linux Shell environment to enter the Linux Shell command line as follows in the terminal
```shell
# elf

BusyBox v1.22.1 (2021-04-20 10:35:42 CST) built-in shell (ash)
Enter 'help' for a list of built-in commands.

~ #
```

#### Execute the HE command in the Linux Shell command line

To execute the HE command on the Shell command line, just type
```shell
he <HE command>
```   
HE commands that involve some special characters of the Shell, single quotes can be added to avoid being parsed by the Shell command line
```shell
he '<HE command>'
```   
Examples are as follows:
```shell
# elf

BusyBox v1.22.1 (2021-04-20 10:35:42 CST) built-in shell (ash)
Enter 'help' for a list of built-in commands.

~ # he 'machine'
{
    "platform":"smtk",
    "hardware":"mt7621",
    "custom":"v520",
    "scope":"donkey",
    "language":"cn",
    "macid":"88124E200030",
    "mac":"88:12:4E:20:00:30",
    "name":"V520-200030",
    "title":"V520-200030",
    "mode":"donkeycon"
}
~ # he 'machine.status'
{
    "custom":"v520",
    "version":"4.3.3w-042021",
    "publish":"042021",
    "macid":"88124E200030",
    "mac":"88:12:4E:20:00:30",
    "magic":"D7441F2CE4605020",
    "model":"V520",
    "name":"V520-200030",
    "mode":"donkeycon",
    "livetime":"00:18:28:0",
    "current":"12:11:16:04:20:2021"
}
~ #
```
