***
## Zero touch test management
Zero touch test from local broacast

#### Configuration( agent@test )
```json
{
    "ifname@lte":"need test or not",
    "ifname@lte2":"need test or not",
    "uart@serial":"need test or not",
    "uart@serial2":"need test or not",
    "gnss@nmea":"need test or not",
    "arch@gpio":"need test or not"
}
```
Examples, show all the configure
```shell
agent@test
{
}
```  
Examples, disable the LTE1 test
```shell
agent@test:ifname@lte=disable
ttrue
```  

#### **Methods**

+ `info[]` **start test**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "ifname@lte":
        {
        },
        "ifname@lte2":
        {
        },
        "uart@serial":
        {
        },
        "uart@serial2":
        {
        },
        "gnss@nmea":
        {
        },
        "arch@gpio":
        {
        }
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


