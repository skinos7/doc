
***
## user management API
user management API, depend on devport
*all methods need username*

#### **Methods**

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
        "network":"network function"                          // [ "enable", "disable" ]
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

