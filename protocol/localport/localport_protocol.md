

## Description of the local managed protocol

The gateway can accept the management protocol from the LAN. The management protocol is usually issued by the batch management tool or other local devices. Through this protocol, the batch management tool or other devices can implement the LAN management gateway


#### Protocol Type

The communication on LAN to gateway is divided into three protocols
- **TCP(JSON) control protocol(TCP PORT:22220), It is used to send JSON commands over TCP to modify, query, or configure the gateway**
- **Local search protocol(UDP PORT:22222), Used to search for all gateways on a LAN**
- **Local query protocol(UDP PORT:22222), Used to query basic infomation for all gateways on a LAN**

![avatar](./localport_protocol.png)

---

## TCP(JSON) control protocol
Through the **TCP port 22220** to interact with the gateway JSON commands, to implement the control of the gateway, the use of TCP protocol interaction, suitable for interacting with various information

#### Enable the JSON control protocol on the gateway

The default gateway will not respond to the TCP(JSON) control protocol, you need to go to the management web page to open this protocol, *There is a security risk to open this protocol, please ensure the security of the LAN*

![avatar](./localport_jsonwui.png)   

Alternatively, open the protocol through the gateway terminal (SSH/Telnet)
```shell
# agent@local:json           # Query the status of the gateway json command
disable
# agent@local:json=enable    # Change the status of the gateway json command to Enable
ttrue
# agent@local:json           # Query the modified configuration again
enable
# 
```

#### Communication process with the gateway
 
![avatar](./localport_control.png)

- introduction of communication  
    Each interaction needs to establish a TCP connection, and then send JSON commands. After receiving JSON commands, the gateway will reply to the execution result of the JSON commands, and then close the TCP connection immediately. Therefore, each interaction needs to establish a TCP connection, also known as the **short connection**. The commands is designed as a complete JSON object, and the reply message is also a complete JSON object, and the operation of the gateway can be divided into three types of JSON instructions：
	- **Query configuration** Used to query the current configuration of some function
	- **Modify configuration** Used to modify the configuration of certain gateway components
	- **Calling component method** Used to perform some functions of the gateway component operations, such as querying status, starting, and disabling

#### JSON Command Format --- HE Command
- Wrap the HE command directly with JSON
    The following is the JSON format packaging HE command format introduction
    ```json
    {
        "cmd1":"HE Command"   // [ string ]:[ string ] 
                              // Attribute name can be arbitrarily named, Used to uniquely identify the current command in JSON
        // more command...
    }
    ```
    The gateway returns the content based on the result of the HE command. The format can be:
    - **JSON**
        ```json
        {
            "cmd1":{ JSON }
        }
        ```
    - **Character string**
        ```json
        {
            "cmd1":" STRING "
        }
        ```
    - **NULL**, Indicates that this result does not exist
        ```json
        {
            "cmd1":"NULL"
        }
        ```   
    Example 1：the HE command to query the basic configuration of the gateway is land@machine, and the corresponding json command format is
    ```json
    { "cmd1":"land@machine" }
    ```
    Example 2：the HE command to query the gateway name is land@machine:name, and the corresponding json command format is
    ```json
    { "cmd1":"land@machine:name" }
    ```
    Example 3：the HE command for querying the working mode of the gateway is land@machine:mode, and the corresponding json command format is
    ```json
    { "cmd1":"land@machine:mode" }
    ```
    Example 4：the HE command to query the LTE/NR configuration of the gateway is ifname@lte, and the corresponding json command format is
    ```json
    { "cmd1":"ifname@lte" }
    ```    
    Example 5：the HE command to query the LTE/NR status of the gateway is ifname@lte.status, and the corresponding json command format is
    ```json
    { "cmd1":"ifname@lte.status" }
    ```
    Example 6：call the ntpsync method of clock@date(System Date) to synchronize time by NTP with ntp1.aliyun.com HE command is clock@date.ntpsync[ntp1.aliyun.com], and the corresponding json command format is
    ```json
    { "cmd1":"clock@date.ntpsync[ntp1.aliyun.com]" }
    ```
    Example 7：You can also run multiple HE commands at the same time. If you restart the LTE network, run ifname@lte.shut and then ifname@lte.setup, and the corresponding json command format is
    ```json
    { "1":"ifname@lte.shut", "2":"ifname@lte.setup" }
    ```   
    **See this document for more command lines [HE command](https://github.com/skinos7/doc/blob/master/use/he_command_en.md)**


    
#### JSON Command Format --- JSON Command

- The format of the HE command for querying the gateway configuration is **Component name[:attribute/attribute/...]**
    The following is an introduction to the JSON command format
    ```json
    {
        "cmd1":   // [ string ]:{} Can be named freely, unique identification of the current command
        {
            "com":"Component name",          // [ string ]
            "ab":"attribute[/attribute/…]"   // [ string ], optional
        }
        // more...
    }
    ```
    The gateway returns the content based on the result of the JSON command. The format can be:
    - **JSON**
        ```json
        {
            "cmd1":{ JSON }
        }
        ```
    - **Character string**
        ```json
        {
            "cmd1":" STRING "
        }
        ```
    - **NULL**, Indicates that this result does not exist
        ```json
        {
            "cmd1":"NULL"
        }
        ```   
    Example 1：the HE command to query the basic configuration of the gateway is land@machine, and the corresponding json command format is
    ```json
    { "cmd1":{ "com":"land@machine" } }
    ```
    Example 2：the HE command to query the gateway name is land@machine:name, and the corresponding json command format is
    ```json
    { "cmd1": { "com":"land@machine","ab":"name" } }
    ```
    Example 3：the HE command for querying the working mode of the gateway is land@machine:mode, and the corresponding json command format is
    ```json
    { "cmd1": { "com":"land@machine","ab":"mode" } }
    ```
    Example 4：the HE command to query the LTE/NR configuration of the gateway is ifname@lte, and the corresponding json command format is
    ```json
    { "cmd1": { "com":"ifname@lte" } }
    ```    
    Example 5：the HE command to query the IP address settings of the gateway is ifname@lan:static/ip, and the corresponding json command format is
    ```json
    { "cmd1": { "com":"ifname@lan","ab":"static/ip" } }
    ```


- The format of the HE command for modifying the gateway configuration is **Component name[:attribute/attribute/...]=value**
    The following is an introduction to the JSON command format --- when the value is string
    ```json
    {
        "cmd1":   // [ string ]:{} Can be named freely, unique identification of the current command
        {
            "com":"Component name",          // [ string ]
            "ab":"attribute[/attribute/…]"   // [ string ], optional
	        "op":"=",                        // The operation is an assignment
	        "v":"value of string"            // [ string ], optional
        }
        // more...
    }
    ```
    The following is an introduction to the JSON command format --- when the value is JSON
    ```json
    {
        "cmd1":   // [ string ]:{} Can be named freely, unique identification of the current command
        {
            "com":"Component name",          // [ string ]
            "ab":"attribute[/attribute/…]"   // [ string ], optional
	        "op":"=",                        // The operation is an assignment
	        "v":{value of JSON}              // [ JSON ], optional
        }
        // more...
    }
    ```
    The gateway returns a value of ttrue on success and tfalse on failure:
    1. return ttrue
        ```json
        {
            "cmd1":"ttrue"
        }
        ```
    2. return tfalse
        ```json
        {
            "cmd1":"tfalse"
        }
        ```   
    Example 1：the HE command of the gateway language is changed to english land@machine:language=en, the corresponding JSON command format is
    ```json
    { "cmd1": { "com":"land@machine", "ab":"language", "op":"=", "v":"en" } }
    ```
    Example 2：The HE command to change the gateway name is land@machine:name=NewName, and the corresponding json command format is
    ```json
    { "cmd1": { "com":"land@machine","ab":"name", "op":"=", "v":"NewName" } }
    ```


- - The format of the HE command for calling component method of gateway is **Component name.method name[ parameter1, parameter2, parameter3, ... ]**
    The following is an introduction to the JSON command format
    ```json
    {
        "cmd1":   // [ string ]:{} Can be named freely, unique identification of the current command
        {
            "com":"Component name",    // [ string ]
	        "op":"method name",        // [ string ]
	        "1":"parameter1",               // [ string ], optional, The parameter can be a string or JSON
	        "2":"parameter2",               // [ string ], optional, The parameter can be a string or JSON
            "3":"parameter3"                // [ string ], optional, The parameter can be a string or JSON
            // "4", "5", ...
        }
        // more...
    }
    ```
    Different from those returned by the calling method, gateway return values can be divided into the following five types：
    1. Return ttrue, which is usually used to indicate that the operation succeeded
        ```json
        {
            "cmd1":"ttrue"
        }
        ```
    2. Return tfalse, which is usually used to indicate that the operation failed
        ```json
        {
            "cmd1":"tfalse"
        }
        ```
    3. Return JSON, which usually represents the return information of the operation
        ```json
        {
            "cmd1":{value of JSON}
        }
        ```
    4. Return STRING, which usually represents the return information of the operation
        ```json
        {
            "cmd1":"value of STRING"
        }
        ```
    5. NULL return. Some method do not return any information
        ```json
        {
            "cmd1":"NULL"
        }
        ```   
    Example 1：the HE command to query the basic gateway status is land@machine.status, the corresponding JSON command format is
    ```json
    { "cmd1": { "com":"land@machine", "op":"status" } }
    ```
    Example 2：The HE command to query the LTE network status of the gateway is ifname@lte.status, the corresponding JSON command format is
    ```json
    { "cmd1": { "com":"ifname@lte", "op":"status" } }
    ```
    Example 3：The HE command for querying the GPS information of the gateway is gnss@nmea.info, the corresponding JSON command format is
    ```json
    { "cmd1": { "com":"gnss@nmea", "op":"info" } }
    ```



#### **Obtain the basic gateway configuration**   
Send
```json
{
    "cmd1":
    {
        "com":"land@machine"
    }
}
```   
Receive
```json
{
    "cmd1":
    {
        "mode":"gateway",                              // operation mode
        "name":"5228-128870",                          // name is 5228-128870
        "mac":"00:03:7F:12:88:70",                     // mac 00:03:7F:12:88:70
        "macid":"00037F128870",                        // id 00037F128870
        "language":"cn",                               // language is chinese
        "cfgversion":"134"                             // configure version is 134
    }
}
```   
Click [Management of Basic Infomation](../com/land/machine.md) to see more
Test using the TCP client tool:   
![avatar](./localport_jsontest.png)

#### **Obtain the basic gateway status**   
Send
```json
{
    "cmd1":
    {
        "com":"land@machine",
        "op":"status"
    }
}
```    
Receive
```json
{
    "cmd1":
    {
        "mode":"nmisp",                    // gateway operator mode Next Mobile(NR/LTE) Internet Service Provider connection
        "name":"ASHYELF-12AAD0",           // gateway name is ASHYELF-12AAD0
        "platform":"smtk2",                // gateway platform identify is smtk2( hint the basic sdk is second release of smtk )
        "hardware":"mt7621",               // gateway hardware identify is mt7621( hint the chip is MT7621 )
        "custom":"d228",                   // gateway custom identify is d228( hint the product name is D228 )
        "scope":"std",                     // gateway scope identify is std( hint this is a standand release for D228 )
        "version":"tiger7-20220218",       // gateway version is tiger7-20220218( hint the version publish at 2022.02.18 )
        "livetime":"00:06:35:0",           // gateway It has been running for 6 minutes and 35 seconds
        "current":"14:54:30:05:04:2022",   // current date is 2022.05.04, It's 14:54 and 30 seconds
        "mac":"00:03:7F:12:AA:D0",         // gateway MAC is 00:03:7F:12:AA:D0
        "macid":"00037F12AAD0",            // gateway serial id is 00037F12AAD0
        "model":"5228"                     // gateway model is 5228
    }
}
```    
Click [Management of Basic Infomation](../com/land/machine.md) to see more



#### **Obtain LTE/NR network status information**   
Send
```json
{
    "cmd1":
    {
        "com":"ifname@lte",
        "op":"status"
    }
}
```    
Receive
```json
{
    "cmd1":
    {
        "mode":"dhcpc",                    // IPv4 connect mode is DHCP
        "netdev":"usb0",                   // netdev is usb0
        "gw":"10.137.89.118",              // gateway is 10.137.89.118
        "dns":"120.80.80.80",              // dns is 120.80.80.80
        "dns2":"221.5.88.88",              // backup dns is 221.5.88.88
        "status":"up",                     // connect is succeed
        "ip":"10.137.89.117",              // ip address is 10.137.89.117
        "mask":"255.255.255.252",          // network mask is 255.255.255.252
        "livetime":"00:15:50:0",           // already online 15 minute and 50 second
        "rx_bytes":"1256",                 // receive 1256 bytes
        "rx_packets":"4",                  // receive 4 packets
        "tx_bytes":"1320",                 // send 1320 bytes
        "tx_packets":"4",                  // send 4 packets
        "mac":"02:50:F4:00:00:00",         // netdev MAC address is 02:50:F4:00:00:00
        "method":"slaac",                  // IPv6 address mode is slaac
        "addr":"fe80::50:f4ff:fe00:0",     // local IPv6 address is fe80::50:f4ff:fe00:0
        "imei":"867160040494084",          // imei is 867160040494084
        "imsi":"460015356123463",          // imei is 460015356123463
        "iccid":"89860121801097564807",    // imei is 89860121801097564807
        "csq":"3",                         // CSQ nubmer is 3
        "signal":"3",                      // signal level is 3
        "state":"connect",                 // state is connect to the internet
        "plmn":"46001",                    // plmn is 46001
        "nettype":"WCDMA",                 // nettype is WCDMA
        "rssi":"-107",                     // signal intensity is -107
        "operator":"ChinaUnion",           // operator name is ChinaUnion
        "operator_advise":                 // recommended profile for ChinaUnion
        {
            "name":"ChinaUnion",               // name is ChinaUnion
            "dial":"*99#",                     // dial number is *99#
            "apn":"3gnet"                      // APN is 3gnet
        }
    }
}
```    
Click [LTE/NR Network Management](../com/ifname/lte.md) and [LTE/NR Modem Management](../com/modem/lte.md) to see more

#### **Get the second LTE/NR network status information**   
Send
```json
{
    "cmd1":
    {
        "com":"ifname@lte2",
        "op":"status"
    }
}
```    
Receive
```json
{
    "cmd1":
    {
        Same as the return for ifname@lte
    }
}
```    
Click [LTE/NR Network Management](../com/ifname/lte.md) and [LTE/NR Modem Management](../com/modem/lte.md) to see more

#### **Disconnect(Shutdown) LTE/NR network**   
Send
```json
{
    "cmd1":
    {
        "com":"ifname@lte",
        "op":"shut"
    }
}
```   
Receive
```json
{
    "cmd1":"ttrue"
}
```   
Click [LTE/NR Network Management](../com/ifname/lte.md) to see more

#### **Connect(Setup) to LTE/NR network**   
Send
```json
{
    "cmd1":
    {
        "com":"ifname@lte",
        "op":"setup"
    }
}
```   
Receive
```json
{
    "cmd1":"ttrue"
}
```    
Click [LTE/NR Network Management](../com/ifname/lte.md) to see more

#### **Modify the LTE/NR network to disabled**   
Send
```json
{
    "cmd1":
    {
        "com":"ifname@lte",
        "ab":"status",
        "op":"=",
        "v":"disable"
    }
}
```   
Receive
```json
{
    "cmd1":"ttrue"
}
```   
Click [LTE/NR Network Management](../com/ifname/lte.md) to see more

#### **Modify the LTE/NR network to enabled**   
Send
```json
{
    "cmd1":
    {
        "com":"ifname@lte",
        "ab":"status",
        "op":"=",
        "v":"enable"
    }
}
```   
Receive
```json
{
    "cmd1":"ttrue"
}
```    
Click [LTE/NR Network Management](../com/ifname/lte.md) to see more

#### **Modify the LTE/NR modem dail APN/Username/Password**   
Send
```json
{
    "cmd1":
    {
        "com":"ifname@lte",
        "op":"|",
        "v":
        {
            "profile":"enable",
            "profile_cfg":
            {
                "apn":"NewAPN",
                "user":"NewUser",
                "passwd":"NewPassword"
            }
        }
    }
}
```   
Receive
```json
{
    "cmd1":"ttrue"
}
```    
Click [LTE/NR Network Management](../com/ifname/lte.md) and [LTE/NR Modem Management](../com/modem/lte.md) to see more

#### **Enable Location function of LTE/NR modem**   
Send
```json
{
    "cmd1":
    {
        "com":"ifname@lte",
        "ab":"gnss",
        "op":"=",
        "v":"enable"
    }
}
```   
Receive
```json
{
    "cmd1":"ttrue"
}
```    
Click [LTE/NR Network Management](../com/ifname/lte.md) and [LTE/NR Modem Management](../com/modem/lte.md) to see more


#### **Send SMS use LTE/NR modem**   
Send
```json
{
    "cmd1":
    {
        "com":"modem@lte",
        "op":"smssend",
        "1":"+13266606322",
        "2":"that is a test SMS"
    }
}
```   
Receive
```json
{
    "cmd1":"ttrue"
}
```    
Click [LTE/NR Modem Management](../com/modem/lte.md) to see more


#### **List all SMS on LTE/NR modem**   
Send
```json
{
    "cmd1":
    {
        "com":"modem@lte",
        "op":"smslist"
    }
}
```   
Receive
```json
{
    "cmd1":
    {
        "lte.612f6C":
        {
            "id":"lte.612f6C",
            "contact":"8617688704240",
            "date":"23-12-18 22:50:01",
            "content":"看下午方便的话可以   "
        },
        "lte.Y9kWLV":
        {
            "id":"lte.Y9kWLV",
            "contact":"8617688704240",
            "date":"23-12-18 22:50:03",
            "content":"要   现的"
        },
        "lte.ovV6nw":
        {
            "id":"lte.ovV6nw",
            "contact":"8617688704240",
            "date":"23-12-18 22:49:22",
            "content":"看下午方便的话可以"
        },
        "lte.sTQ9x1":
        {
            "id":"lte.sTQ9x1",
            "contact":"8617688704240",
            "date":"23-12-18 22:51:22",
            "content":"iiik'帮"
        },
        "lte.uKyisL":
        {
            "id":"lte.uKyisL",
            "contact":"8617688704240",
            "date":"23-12-18 22:51:49",
            "content":"ss'ddd"
        }
    }
}
```    
Click [LTE/NR Modem Management](../com/modem/lte.md) to see more


#### **Delete a SMS on LTE/NR modem**   
Send
```json
{
    "cmd1":
    {
        "com":"modem@lte",
        "op":"smsdel",
        "1":"lte.612f6C"
    }
}
```   
Receive
```json
{
    "cmd1":"ttrue"
}
```    
Click [LTE/NR Modem Management](../com/modem/lte.md) to see more






#### **Obtain client information**   
Send
```json
{
    "cmd1":
    {
        "com":"client@station",
        "op":"list"
    }
}
```   
Receive
```json
{
    "cmd1":
    {
        "04:CF:8C:39:91:7A":            // first client
        {
            "ip":"192.168.31.140",                        // ip is 192.168.31.140
            "name":"xiaomi-aircondition-ma2_mibt917A",    // hostname is xiaomi-aircondition-ma2_mibt917A
            "tx_bytes":"1779693",                         // sent 1779693 byte
            "rx_bytes":"1375610",                         // recived 1375610 byte
            "livetime":"14:39:34:1"                       // livetime is 1 day 14 hour 39 minute 34 second
        },
        "40:31:3C:B5:6D:4C":            // second client
        {
            "ip":"192.168.31.61",
            "name":"minij-washer-v5_mibt6D4C",
            "livetime":"14:39:26:1"
        },
        "14:13:46:C9:97:C7":            // third client
        {
            "ip":"192.168.31.9",
            "name":"",
            "livetime":"14:39:27:1"
        }
    }
}
```    
Click [Management of Client Access](../com/client/station.md) to see more



#### **Obtain location information**   
Send
```json
{
    "cmd1":
    {
        "com":"gnss@nmea",
        "op":"info"
    }
}
```   
Receive
```json
{
    "cmd1":
    {
        "step":"located",                           // already located
        "utc":"7:55:22:7:12:2021",                  // UTC
        "lon":"11356.56400",
        "lat":"2240.80119",
        "longitude":"113.94273",                    // longitude is 113.94
        "latitude":"22.68001",                      // latitude is 22.68
        "speed":"0.34",
        "elv":"77.90",
        "direction":"",
        "declination":"",
        "inuse":"8"                                 // 8 sat in use
    }
}
```   
Click [GNSS NEMA Protocol Management](../com/gnss/nmea.md) to see more



#### **Obtain the information about the gateway LAN network**   
Send
```json
{
    "cmd1":
    {
        "com":"ifname@lan",
        "op":"status"
    }
}
```   
Receive
```json
{
    "cmd1":
    {
        "mode":"static",                   // IPv4 connect mode is static
        "netdev":"lan",                    // netdev is lan
        "status":"up",                     // connect is succeed
        "ip":"192.168.1.1",                // ip address is 192.168.1.1
        "mask":"255.255.255.0",            // network mask is 255.255.255.0
        "livetime":"01:15:50:0",           // already online 1 hour and 15 minute and 50 second
        "rx_bytes":"1256",                 // receive 1256 bytes
        "rx_packets":"4",                  // receive 4 packets
        "tx_bytes":"1320",                 // send 1320 bytes
        "tx_packets":"4",                  // send 4 packets
        "mac":"02:50:F4:00:00:00",         // netdev MAC address is 02:50:F4:00:00:00
        "method":"slaac",                  // IPv6 address mode is slaac
        "addr":"fe80::50:f4ff:fe00:0"      // local IPv6 address is fe80::50:f4ff:fe00:0
    }
}
```   
Click [LAN Network Management](../com/ifname/lan.md) to see more



#### **Reboot gateway**   
Send
```json
{
    "cmd1":
    {
        "com":"land@machine",
        "op":"restart"
    }
}
```   
The gateway does not return any information and will restart immediately
Click [Management of Basic Infomation](../com/land/machine.md) to see more

#### **Reset gateway(restore default settings)**   
Send
```json
{
    "cmd1":
    {
        "com":"land@machine",
        "op":"default"
    }
}
```   
The gateway does not return any information and will restart and default immediately
Click [Management of Basic Infomation](../com/land/machine.md) to see more



#### **Enable GNSS function**   
Send
```json
{
    "cmd1":
    {
        "com":"gnss@nmea",
        "ab":"status",
        "op":"=",
        "v":"enable"
    }
}
```   
Receive
```json
{
    "cmd1":"ttrue"
}
```    
Click [GNSS NEMA Protocol Management](../com/gnss/nmea.md) to see more



#### **Modify the SSID name of a wireless hotspot (2.4G)**   
Send
```json
{
    "cmd1":
    {
        "com":"wifi@nssid",
        "ab":"ssid",
        "op":"=",
        "v":"NewSSID"
    }
}
```   
Receive
```json
{
    "cmd1":"ttrue"
}
```    
Click [2.4G SSID Management](../com/wifi/nssid.md) to see more

#### **Modify the SSID password of a wireless hotspot (2.4G)**   
```json
{
    "cmd1":
    {
        "com":"wifi@nssid",
        "op":"|",
        "v":
        {
            "secure":"wpapskwpa2psk",
            "wpa_key":"NewPassword"
        }
    }
}
```   
Receive
```json
{
    "cmd1":"ttrue"
}
```    
Click [2.4G SSID Management](../com/wifi/nssid.md) to see more

#### **Modify the SSID name and password of the wireless hotspot (2.4G)**   
```json
{
    "cmd1":
    {
        "com":"wifi@nssid",
        "op":"|",
        "v":
        {
            "ssid":"NewSSID",
            "secure":"wpapskwpa2psk",
            "wpa_key":"NewPassword"
        }
    }
}
```   
Receive
```json
{
    "cmd1":"ttrue"
}
```    
Click [2.4G SSID Management](../com/wifi/nssid.md) to see more

#### **Modify the SSID name of a wireless hotspot (5.8G)**   
Send
```json
{
    "cmd1":
    {
        "com":"wifi@assid",
        "ab":"ssid",
        "op":"=",
        "v":"NewSSID"
    }
}
```   
Receive
```json
{
    "cmd1":"ttrue"
}
```    
Click [5.8G SSID Management](../com/wifi/assid.md) to see more

#### **Modify the SSID password of a wireless hotspot (5.8G)**   
Send
```json
{
    "cmd1":
    {
        "com":"wifi@assid",
        "op":"|",
        "v":
        {
            "secure":"wpapskwpa2psk",
            "wpa_key":"NewPassword"
        }
    }
}
```   
Receive
```json
{
    "cmd1":"ttrue"
}
```    
Click [5.8G SSID Management](../com/wifi/assid.md) to see more

#### **Modify the SSID name and password of the wireless hotspot (5.8G)**   
Send
```json
{
    "cmd1":
    {
        "com":"wifi@assid",
        "op":"|",
        "v":
        {
            "ssid":"NewSSID",
            "secure":"wpapskwpa2psk",
            "wpa_key":"NewPassword"
        }
    }
}
```   
Receive
```json
{
    "cmd1":"ttrue"
}
```    
Click [5.8G SSID Management](../com/wifi/assid.md) to see more



#### **Modify the WISP(2.4G) connect other AP**   
the gateway operation mode must be **WISP(2.4G)** or **Mix**
Send
```json
{
    "cmd1":
    {
        "com":"ifname@wisp",
        "op":"|",
        "v":
        {
            "status":"enable",
            "peer":"NewAP",
            "secure":"wpapskwpa2psk",
            "wpa_key":"NewPassword"
        }
    }
}
```   
Receive
```json
{
    "cmd1":"ttrue"
}
```    
Click [WISP Network Management](../com/ifname/wisp.md) to see more

#### **Modify the WISP(2.4G) network to disabled**   
the gateway operation mode must be **WISP(2.4G)** or **Mix**
Send
```json
{
    "cmd1":
    {
        "com":"ifname@wisp",
        "ab":"status",
        "op":"=",
        "v":"disable"
    }
}
```   
Receive
```json
{
    "cmd1":"ttrue"
}
```    
Click [WISP Network Management](../com/ifname/wisp.md) to see more

#### **Modify the WISP(2.4G) network to enabled**   
the gateway operation mode must be **WISP(2.4G)** or **Mix**
Send
```json
{
    "cmd1":
    {
        "com":"ifname@wisp",
        "ab":"status",
        "op":"=",
        "v":"enable"
    }
}
```   
Receive
```json
{
    "cmd1":"ttrue"
}
```    
Click [WISP Network Management](../com/ifname/wisp.md) to see more

#### **Disconnect(Shutdown) WISP(2.4G) network**   
the gateway operation mode must be **WISP(2.4G)** or **Mix**
Send
```json
{
    "cmd1":
    {
        "com":"ifname@wisp",
        "op":"shut"
    }
}
```   
Receive
```json
{
    "cmd1":"ttrue"
}
```   
Click [WISP Network Management](../com/ifname/wisp.md) to see more

#### **Connect(Setup) to WISP(2.4G) network**    
the gateway operation mode must be **WISP(2.4G)** or **Mix**
Send
```json
{
    "cmd1":
    {
        "com":"ifname@wisp",
        "op":"setup"
    }
}
```   
Receive
```json
{
    "cmd1":"ttrue"
}
```    
Click [WISP Network Management](../com/ifname/wisp.md) to see more

#### **Modify the WISP(5.8G) connect other AP**   
the gateway operation mode must be **WISP(5.8G)** or **Mix** and the gateway have 5.8G radio
Send
```json
{
    "cmd1":
    {
        "com":"ifname@wisp2",
        "op":"|",
        "v":
        {
            "status":"enable",
            "peer":"NewAP",
            "secure":"wpapskwpa2psk",
            "wpa_key":"NewPassword"
        }
    }
}
```   
Receive
```json
{
    "cmd1":"ttrue"
}
```    
Click [WISP Network Management](../com/ifname/wisp.md) to see more

#### **Modify the WISP(5.8G) network to disabled**   
the gateway operation mode must be **WISP(5.8G)** or **Mix** and the gateway have 5.8G radio
Send
```json
{
    "cmd1":
    {
        "com":"ifname@wisp2",
        "ab":"status",
        "op":"=",
        "v":"disable"
    }
}
```   
Receive
```json
{
    "cmd1":"ttrue"
}
```    
Click [WISP Network Management](../com/ifname/wisp.md) to see more

#### **Modify the WISP(5.8G) network to enabled**   
the gateway operation mode must be **WISP(5.8G)** or **Mix** and the gateway have 5.8G radio
Send
```json
{
    "cmd1":
    {
        "com":"ifname@wisp2",
        "ab":"status",
        "op":"=",
        "v":"enable"
    }
}
```   
Receive
```json
{
    "cmd1":"ttrue"
}
```    
Click [WISP Network Management](../com/ifname/wisp.md) to see more

#### **Disconnect(Shutdown) WISP(5.8G) network**   
the gateway operation mode must be **WISP(5.8G)** or **Mix** and the gateway have 5.8G radio
Send
```json
{
    "cmd1":
    {
        "com":"ifname@wisp2",
        "op":"shut"
    }
}
```   
Receive
```json
{
    "cmd1":"ttrue"
}
```   
Click [WISP Network Management](../com/ifname/wisp.md) to see more

#### **Connect(Setup) to WISP(5.8G) network**   
the gateway operation mode must be **WISP(5.8G)** or **Mix** and the gateway have 5.8G radio
Send
```json
{
    "cmd1":
    {
        "com":"ifname@wisp2",
        "op":"setup"
    }
}
```   
Receive
```json
{
    "cmd1":"ttrue"
}
```    
Click [WISP Network Management](../com/ifname/wisp.md) to see more



#### **Modify the password of the admin user**   
Send
```json
{
    "cmd1":
    {
        "com":"land@auth",
        "op":"modify",
        "1":"",
        "2":"admin",
        "3":"OldPassword",
        "4":"NewPassword"
    }
}
```   
Receive
```json
{
    "cmd1":"ttrue"
}
```    
Click [Username/Password and Permission Management](../com/land/auth.md) to see more



#### **Add policy-based route rule for force source ip(192.168.8.2.12) route to first LTE/NR, named it senser**   
Send
```json
{
    "cmd1":
    {
        "com":"forward@rule",
        "op":"add",                 // method is add
        "1":"senser",               // rule name is senser
        "2":"192.168.2.12",         // source ip
        "3":"",                     // mask is space
        "4":"",                     // source interface is space
        "5":"",                     // mark id is space
        "6":"1",                    // route table id
                                            // 1 is first LTE/NR
                                            // 2 is second LTE/NR
                                            // 3 is first WAN
                                            // 4 is second WAN
                                            // 5 is WISP(2.4G)
                                            // 6 is WISP(5.8G)
        "7":"33000"                 // priority, Usually the priority needs to be between 32766 and 35000
    }
}
```   
Receive
```json
{
    "cmd1":"ttrue"
}
```    
Click [Policy based routing](../com/forward/rule.md) to see more

#### **Add policy-based route rule for force all ip route to second LTE/NR, named it video**   
Send
```json
{
    "cmd1":
    {
        "com":"forward@rule",
        "op":"add",                 // method is add
        "1":"video",                // rule name is video
        "2":"",                     // source ip is space
        "3":"",                     // mask is space
        "4":"",                     // source interface is space
        "5":"",                     // mark id is space
        "6":"2",                    // route table id
                                            // 1 is first LTE/NR
                                            // 2 is second LTE/NR
                                            // 3 is first WAN
                                            // 4 is second WAN
                                            // 5 is WISP(2.4G)
                                            // 6 is WISP(5.8G)
        "7":"33000"                 // priority, Usually the priority needs to be between 32766 and 35000
    }
}
```   
```json
{
    "cmd1":"ttrue"
}
```   
Click [Policy based routing](../com/forward/rule.md) to see more

#### **Delete policy-based route rule named senser**   
Send
```json
{
    "cmd1":
    {
        "com":"forward@rule",
        "op":"delete",                 // method is delete
        "1":"senser"                    // rule name is senser
    }
}
```   
```json
{
    "cmd1":"ttrue"
}
```   
Click [Policy based routing](../com/forward/rule.md) to see more

#### **Delete policy-based route rule named video**   
Send
```json
{
    "cmd1":
    {
        "com":"forward@rule",
        "op":"delete",                 // method is delete
        "1":"video"                    // rule name is video
    }
}
```   
```json
{
    "cmd1":"ttrue"
}
```   
Click [Policy based routing](../com/forward/rule.md) to see more

#### **Add policy-based route rule for force source ip(192.168.8.2.12) route to first LTE/NR, and Add policy-based route rule for force other ip route to second LTE/NR**   
Send
```json
{
    "cmd1":
    {
        "com":"forward@rule",
        "op":"add",                 // method is add
        "1":"senser",               // rule name is senser
        "2":"192.168.2.12",         // source ip
        "3":"",                     // mask is space
        "4":"",                     // source interface is space
        "5":"",                     // mark id is space
        "6":"1",                    // route table id
                                            // 1 is first LTE/NR
                                            // 2 is second LTE/NR
                                            // 3 is first WAN
                                            // 4 is second WAN
                                            // 5 is WISP(2.4G)
                                            // 6 is WISP(5.8G)
        "7":"33000"                 // priority, Usually the priority needs to be between 32766 and 35000
    },
    "cmd2":
    {
        "com":"forward@rule",
        "op":"add",                 // method is add
        "1":"video",                // rule name is senser
        "2":"",                     // source ip is space
        "3":"",                     // mask is space
        "4":"",                     // source interface is space
        "5":"",                     // mark id is space
        "6":"2",                    // route table id
                                            // 1 is first LTE/NR
                                            // 2 is second LTE/NR
                                            // 3 is first WAN
                                            // 4 is second WAN
                                            // 5 is WISP(2.4G)
                                            // 6 is WISP(5.8G)
        "7":"33000"                 // priority, Usually the priority needs to be between 32766 and 35000
    }
}
```   
Receive
```json
{
    "cmd1":"ttrue",
    "cmd2":"ttrue"
}
```    
Click [Policy based routing](../com/forward/rule.md) to see more

#### **Delete policy-based route rule named senser and video**   
Send
```json
{
    "cmd1":
    {
        "com":"forward@rule",
        "op":"delete",                 // method is delete
        "1":"senser"                    // rule name is senser
    },
    "cmd2":
    {
        "com":"forward@rule",
        "op":"delete",                 // method is delete
        "1":"video"                    // rule name is video
    }
}
```   
Receive
```json
{
    "cmd1":"ttrue",
    "cmd2":"ttrue"
}
```   
Click [Policy based routing](../com/forward/rule.md) to see more





## Reference the component documentation to manage the gateway using the JSON command

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

- Send **component name** all configurations for this component are returned, The attributes and examples of each configuration are described detailedly in **Configuration** in the component documentation
    ```json
    {
        "cmd1":
        {
            "com":"land@syslog"
        }
    }
    ```   
    Receive, cmd1 is the land@syslog' configuration
    ```json
    {
        "cmd1":
        {
            "status":"enable",                // enable the syslog functions
            "location":"memory",              // logs stored in memory, restart will be lost
            "type":"arch|land|default",       // log the arch, land, default log
            "level":"info",                   // log level is normal infomation
            "trace":"disable",                // disable the code information
            "size":"100",                     // log buffer is 100k
            "remote":"192.168.8.250",         // send the syslog to remote server 192.168.8.250
            "port":"514"                      // send the syslog to remote server port 514
        }
    }
    ```

- Queries the attributes specified in the component configuration, You only need to give the specified attribute in **ab**
    ```json
    {
        "cmd1":
        {
            "com":"land@syslog",
            "ab":"size"
        }
    }
    ```   
    Receive, cmd1 is the land@syslog' configuration
    ```json
    {
        "cmd1":"100"
    }
    ```

#### Refer to the component documentation to modify the component configuration   
Refer to [Syslog Management](../com/land/syslog.md), The attributes described in **Configuration** of the document can be modified in the JSON command by given **ab** and **v**, with **op** be **=** or **op** be **|**
- Modify the remote attribute of the land@syslog remote log server
    ```json
    {
        "cmd1":
        {
	        "com":"land@syslog",
	        "ab":"remote",
	        "op":"=",
	        "v":"192.168.8.250"
        }
    }
    ```   
    Receive
    ```json
    {
        "cmd1":"ttrue"
    }
    ```

- Modify multiple attributes of land@syslogd on the JSON command at the same time. Modifying the remote and port attributes does not affect other attributes
    ```json
    {
        "cmd1":
        {
	        "com":"land@syslog",
	        "op":"|",
	        "v":
            {
                "remote":"192.168.8.250",
                "port":"500"
            }
        }
    }
    ```   
    Receive
    ```json
    {
        "cmd1":"ttrue"
    }
    ```

- Set land@syslogd in the JSON command. All configurations and component configurations are JSON. To modify all configurations, you must provide the same JSON
    ```json
    {
        "cmd1":
        {
	        "com":"land@syslog",
	        "op":"=",
	        "v":
            {
                "status":"enable",
                "location":"memory",
                "type":"arch|land|default",
                "level":"info",
                "trace":"disable",
                "size":"110",
                "remote":"",
                "port":"514"
            }
        }
    }
    ```   
    Receive
    ```json
    {
        "cmd1":"ttrue"
    }
    ```

#### call a component method by referring to the component documentation   
Refer to [Syslog Management](../com/land/syslog.md), Methods described in the documentation **Methods** can be calle on the JSON command by given **op**
- Call the clear method of component land@syslog to clear all current logs
    ```json
    {
        "cmd1":
        {
	        "com":"land@syslog",
	        "op":"clear"
        }
    }
    ```   
    Receive
    ```json
    {
        "cmd1":"ttrue"
    }
    ```



---
## Local search protocol
All gateways in the network are searched by broadcasting to **UDP port 22222** on the LAN

##### 1. Search gateway communication process   
![avatar](./localport_search_step.png)
Flow chart (consistent with the figure above, please ignore it if it cannot be displayed)
```flow
device=>end: 2. The gateway that belongs to the corresponding group replies the MAC address, IP address, and WEB port to UDP port 22222 whose IP address is 255.255.255.255: MAC|IP|port|
data=>operation: 1. The management tool broadcasts to UDP port 22222 whose IP address is 255.255.255.255. Character string: group name
client=>start: Begin
client->data->device
```

##### 2. Search the gateway interaction details in the network
- 1. **management tool** send the search string
    That is, broadcast the group name with seven characters default to UDP port 22222 whose IP address is 255.255.255.255. All in-network gateways can receive this string
    ```
    default
    ```
- 2. **gateway** reply
    After receiving the default string, all gateways on the network will broadcast their MAC address, IP address, and WEB port to UDP port 22222 in the format of:
    ```
    MAC|IP|PORT
    ```
- Example: if the MAC address of the gateway is 00:03:7F:12:BB:80, IP address is 192.168.8.1, and the port number of the WEB management server is 80, the reply data will contain the following 32 characters and end with 0x0 in hexadecimal:
    ```
    00037F12BB80|192.168.8.1|80
    ```

##### 3. Use the Windwos tool to test the gateway within the search network using the LAN search protocol
- On the left is the send tool, which sends UDP packets to port 22222 of 192.168.8.1. (Broadcast needs to send UDP packets to port 22222 of 255.255.255.255. This tool does not support broadcast, so unicast mode is used instead of demonstration.)
- On the right is the receiving tool, which receives the gateway reply packet on port 22222 on the current PC (192.168.8.250)
![avatar](./localport_search.png)

*Note: Using a unicast tool instead of a demonstration because a suitable broadcast tool could not be found, broadcasting the same data to UDP port 22222 during actual development would produce the same result packet*



---
## Local query protocol
In the LAN, through the **UDP port 22222** broadcast search and query information of all gateways in the network, because the use of UDP protocol, when the interaction data is too large, there will be a packet loss problem, it is not suitable to do a large amount of information interaction

##### 1. Querying the communication process of the gateway on a network
![avatar](./localport_query_step.png)
Flow chart (consistent with the figure above, please ignore it if it cannot be displayed)
```flow
device=>end: 2. The gateway that belongs to the corresponding group replies the MAC address, IP address, and WEB port to UDP port 22222 whose IP address is 255.255.255.255: MAC-HE Command1 return|HE Command2 return|HE Command3 return|...
data=>operation: 1. The management tool broadcasts to UDP port 22222 whose IP address is 255.255.255.255. Character string: group name+HE Command1|HE Command2|HE Command3|…
client=>start: Begin
client->data->device
```

##### 2. Query network gateway information communication details
- 1. **management tool** Send a query request to UDP port 22222 whose IP address is 255.255.255.255 to broadcast the group name with 7 characters default plus commas (,) and the HE command. All Intranet gateways can receive this string
    ```
    default+HE command1|HE command2|HE command3
    ```
- 2. **Gateway** reply
    ```
    MAC-HE command1 return|HE command2 return|HE command3 return
    ```
    Here are some common HE command, See this document for more [HE command](../use/he_command_en.md):
    ```
    land@machine:model           //  query the model of gateway
    land@machine:version         //  query the version of gateway
    land@machine:mode            //  query the operation mode of gateway
    ifname@lte.status:imei       //  query the LTE/NR IMEI of gateway
    ifname@lte.status:iccid      //  query the LTE/NR ICCID of gateway
    ifname@lte.status:signal     //  query the LTE/NR signal level of gateway
    ifname@lte.status:rssi       //  query the LTE/NR rssi of gateway
    ifname@lte.status:rsrp       //  query the LTE/NR rsrp of gateway
    gnss@nmea.info:step          //  query the location status of gateway
    ```

- Example
    The following information is sent to query the model and IMEI of all gateways on the LAN:
    ```
    default+land@machine:model|ifname@lte.status:imei
    ```
    For example, if the MAC address is 00:03:7F:12:3A:D0 (IP address is 192.168.8.1), the gateway model A218 responds as follows：
    ```
    00037F123AD0-A218|862107043556307
    ```
    For example, if the MAC address is 00:03:7F:13:3A:D8 (IP address is 192.168.8.1), the gateway whose model is V519 responds as follows：
    ```
    00037F133AD08-V519|86210704355692
    ```    
##### 3. Use the Windwos tool to test the gateway receiving and sending packets within the inquiry network   
- On the left, the send tool sends UDP packets to port 22222 of 192.168.8.1 to query the models and CCID numbers of all gateways on the LAN
- On the right, the receiver tool receives the reply packet from the gateway on port 22222 of the current PC (192.168.8.250). The gateway whose MAC address is 88:12:4E:30:91:A0 returns its model number to A219 and CCID number to 89860117851138508772
![avatar](./localport_query.png)

*Note: Using a unicast tool instead of a demonstration because a suitable broadcast tool could not be found, broadcasting the same data to UDP port 22222 during actual development would produce the same result packet*


