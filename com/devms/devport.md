
***
## device management service   
all device connect to this service, this service responsible for communication with device   

### Configuration( devms@devport )   
```json
// attribute introduction
{
    "status":"enable the function",                       // [ disable, enable ]

    "port":"tcp port for device connected",               // [ number ]
    "sslport":"ssl tcp port for device connected",        // [ number ]

    "post_interval":"the reporting interval of gateway",  // [ number ], The unit is seconds
    "offline_timeout":"the offline timeout of gateway",   // [ number ], The unit is seconds

    "path":"directory for storing device information"     // [ string ]
}
```   
Examples, show all the configure   
```shell
devms@devport                          # input at HE terminal
{ 
    "status":"enable",                # current status is enable
    "port":"10000",                   # tcp port is 10000
    "sslport":"10005",                # ssl tcp port is 10005
    "post_interval":"10",             # client need post interval is 10 sec
    "offline_timeout":"95"            # client offline when last report before the 95 sec
}
```   
Examples, modify the client timeout to 60 sec   
```shell
devms@devport:offline_timeout=60      # input at HE terminal
ttrue                                 # modify successfully
```     

### **Methods**   
+ `path[]` **get the database directory**, *succeed return string to describes, failed return NULL, error return terror*   

+ `user_list[]` **lists all users in the server that are used to manage devices**, *succeed return talk to describes, failed return NULL, error return terror*   
    ```json
    // Attributes introduction of talk by the method return
    {
        "user name":              // [ string ]: { configure }
        {
            "comment":"user comment",                    // [ string ]
            "vcode":"device verify code",                // [ string ]
            "lang":"user language"                       // [ "cn", "en" ]
            // ... more configure, detail same user_get return
        }
        // ... more user
    }    
    ```   
    Examples, List all user   
    ```shell
    devms@devport.user_list
    {
        "okwy001":
        {
            "vcode":"",
            "lang":"en",
            "comment":""
        },
        "okwy004":
        {
            "vcode":"",
            "comment":""
        },
        "test2":
        {
            "vcode":"",
            "comment":"GatherControl"
        },
        "okwy002":
        {
            "vcode":"1234",
            "lang":"en",
            "comment":""
        }
    }
    ```   

+ `user_add[ username, password, [vcode], [lang], [comment] ]` **add a user**, *succeed return tture, failed return tfalse, error return terror*   
    Examples, add a user   
    ```shell
    devms@devport.add[ ashyelf, Z1x2c3v4b5, , en, TestUser ]
    ttrue
    ```   

+ `user_delete[ username ]` **delete a user**, *succeed return tture, failed return tfalse, error return terror*   
    Examples, delete a user   
    ```shell
    devms@devport.delete[ ashyelf ]
    ttrue
    ```   

+ `user_get[ username ]` **get user configure**, *succeed return talk to describes, failed return NULL, error return terror*   
    ```json
    // Attributes introduction of talk by the method return
    // that save at $user/config.json
    {
        "comment":"username comment",                         // [ string ]
        "vcode":"gateway connect vcode",                      // [ string ]
        "lang":"webpage username password",                   // [ "cn", "en", ... ]

        "post_interval":"The reporting interval of the own gateway",    // [ number ], the unit is second
        "offline_timeout":"the offline timeout of the own gateway",     // [ number ], the unit is second
    
        "pport":"port map function",                          // [ "enable", "disable" ]
        "network":"network to network function"               // [ "enable", "disable" ]
    }
    ```   

+ `user_set[ username, {user configure} ]` **set user configure**, *succeed return tture, failed return tfalse, error return terror*   
    ```json
    // Attributes introduction of talk by the method parameter of {user configure}
    {
        "password":"user password",                 // [ string ]
        // ... more configure, detail same "user_get" return
    }
    ```   

