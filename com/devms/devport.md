
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

+ `path[]` **get the database directory**, *succeed return string to describes, failed return NULL, error return terror*

+ `user_list[]` **get all user**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "user name":              // [ string ]: {}
        {
            "comment":"user comment",                    // [ string ]
            "vcode":"device verify code",                // [ string ]
            "lang":"user language"                       // [ "cn", "en" ]
            // ... more configure, detail same user_get return
        }
        // ... more user
    }    
    ```

+ `user_add[ username, password, [vcode], [lang], [comment] ]` **add a user to server**, *succeed return tture, failed return tfalse, error return terror*

+ `user_delete[ username ]` **delete a user**, *succeed return tture, failed return tfalse, error return terror*

+ `user_get[ username ]` **get user configure**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    // that save at $user/config.json
    {
        "comment":"username comment",                         // [ string ]
        "vcode":"gateway connect vcode",                      // [ string ]
        "password":"username login password",                 // [ string ]
        "lang":"webpage username password",                   // [ "cn", "en", ... ]
        "post_interval":"gateway report default interval",    // [ number ], the unit is second
        "offline_timeout":"gateway timeout",                  // [ number ], the unit is second
    
        "pport":"port map function",                          // [ "enable", "disable" ]
        "g2gnet":"gateway to gateway function"                // [ "enable", "disable" ]
    }
    ```

+ `user_set[ username, {user configure} ]` **set user configure**, *succeed return tture, failed return tfalse, error return terror*
    ```json
    // Attributes introduction of talk by the method parameter of {user configure}
    {
        "old_password":"old password of the user",  // [ string ], must need
        "comment":"user comment",                   // [ string ]
        "vcode":"device verify code",               // [ string ]
        "lang":"user language"                      // [ "cn", "en" ]
        // ... more configure, detail same user_get return
    }
    ```

