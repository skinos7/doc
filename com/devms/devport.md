
***
## device management service
all device connect to the service, this service responsible for communication with device

#### Configuration( devms@devport )

```json
// attribute introduction
{
    "status":"enable the function",                       // [ disable, enable ]
    "port":"tcp port",                                    // [ number ]
    "timeout":"timeout to disconnect",                    // [ number ], The unit is seconds
    "path":"directory for storing device information"     // [ string ]
}
```

#### **Methods**

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

+ `offline_list[ username, [group] ]` **get the device list of username**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "device mac address":
        {
        }
        // ... more device
    }    
    ```

+ `online_list[ username, [group] ]` **get the online device list of username**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "device mac address":
        {
        }
        // ... more device
    }    
    ```

