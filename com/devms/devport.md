
***
## device management service
all device connect to the service, this service responsible for communication with device

#### Configuration( devms@devport )

```json
// attribute introduction
{
    "status":"enable the function",                       // [ disable, enable ]

    "port":"tcp port",                                    // [ number ]
    "path":"directory for storing device information",    // [ string ]

    "post_interval":"device report interval",             // [ number ], The unit is seconds
    "offline_timeout":"timeout to disconnect"             // [ number ], The unit is seconds
}
```
Examples, show all the configure
```shell
devms@devport
{
    "status":"enable",
    "port":"10000",                   // tcp port is 10000
    "post_interval":"10",             // client need post interval is 10 sec
    "offline_timeout":"35"            // client offline when last report before the 35 sec
}
```  
Examples, modify the client timeout to 60 sec
```shell
devms@devport:offline_timeout=60
ttrue
```  


#### **Methods**

+ `list_user[]` **get the user list of server**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "user name":              [ string ]: {}
        {
            "vcode":"device verify code"        [ string ]
        }
        // ... more user
    }    
    ```

+ `add_user[ username, password, [vcode] ]` **add a user to server**, *succeed return tture, failed return tfalse, error return terror*

+ `delete_user[ username, password ]` **delete a user from server**, *succeed return tture, failed return tfalse, error return terror*



+ `list[ username, [group] ]` **get the device list of username**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "device mac address":
        {
        }
        // ... more device
    }    
    ```

+ `add[ username, device mac identify, [comment] ]` **add a device to server**, *succeed return tture, failed return tfalse, error return terror*

+ `delete[ username, device mac identify ]` **delete a device from server**, *succeed return tture, failed return tfalse, error return terror*

