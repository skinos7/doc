

***
## Username/Password and Permission Management
Manage username and permissions, modifying this configuration directly is not recommended, It is recommended to manage through the method
The configuration structure is divided into three layers
- username can belong to multiple groups
- group can have permissions of domains
- because the three-layer structure is relatively complex, the group and domain permissions are temporarily one-to-one
    > that is, there are only username and groups, and each group has a separate domain permission
- groups are pre-built in the system (built-in based on functions), and corresponding username can be created and deleted.
    > Examples storage functions are added, "nas" group are built in the storage. you can add or delete username belonging to "nas" group


#### Configuration( land@auth )

```json
// Attributes introduction 
{
    "user":        //  username list, all accounts in the system are under this node
    {
        "user name":                  // [ string ], you can custom the username
        {
            "id":"username identify",                               // [ number ]

            "key":"username password",                              // [ string ]
            "key_tok":"need check the tok when auth",               // [ "disable", "enable", string ]
                                                                            "disable", disable the key tok when login
                                                                            "enable", generate the key tok when system boot
                                                                            string , the key tok need match when login
            "key_modify":"key need modify at first login",          // [ "disable", "enable" ]
                                                                            "disable", no to prompt
                                                                            "enable", prompt to change password when key is default
            "key_check":"key need strength",                        // [ "disable", "enable" ], "enable" will check the key strength
            "key_failed_time":"Number of consecutive failures",     // [ number ], be greater than zero will work
            "key_failed_wait":"failures to block",                  // [ number ], the unit is second, delay second when consecutive login failures reach key_failed_time

            "group":                     // List of groups to which the username belongs
            {
                "group name":"belongs state"  // [ string ]: [ "disable","enable" ], "enable" for belongs, "disable" for not
                // "...":"..."                // How many groups belongs show how many properties
            },
            "domain":                    // List of all domains configure for this username
            {
                "domain name":
                {
                    "key":"In this domain specialized password"        // [ string ], an empty one represents the use of the default password
                }
                // "...":{ ... }                                  // How many domain show how many properties
            }
        },
        // "...":{...}                  // How many username show how many properties
    },
    "group":     // Group list, all groups in the system are under this node
    {
        "group name":
        {
            "id":"group identify",     // [ number ]
            "domain":                  // List of all domain permissions under the group
            {
                "domain name":"enable state"  // [ string ]: [ "disable","enable" ]
                // "...":"..."             // How many domain show how many properties
            }
        },
        // "...":{...}                  // How many group show how many properties
    }
}
```

Examples, show all the accounts configure
```shell
land@auth
{
    "user":
    {
        "admin":                       # username: admin
        {
            "id":"0",                  # admin username id is 0
            "key":"E@3DLKSLKJWEWWWWW", # admin default password is E@3DLKSLKJWEWWWWW
            "group":                   # admin belongs groups: admin, web, tui, nas
            {
                "admin":"enable",
                "web":"enable",
                "tui":"enable",
                "nas":"enable"
            },
            "domain":
            {
                "nas":                 # admin password is ADSAADFFF at the nas domain
                {
                    "key":"ADSAADFFF"
                },
                "web":                 # admin password is DSDFSDFF at the web domain
                {
                    "key":"DSDFSDFF"
                }
            }
        },
        "nas":                         # username: nas
        {
            "id":"1000",               # nas username id is 1000
            "key":"nas",               # nas default password is nas
            "group":                   # admin belongs group: nas
            {
                "nas":"enable"
            }
        }
    },
    "group":
    {
        "admin":                       # admin group
        {
            "id":"0",                  # admin group identify is 0
            "domain":                  # admin group belongs admin domain
            {
                "admin":"enable"
            }
        },
        "web":                         # web group
        {
            "id":"1000",               # web group identify is 1000
            "domain":                  # web group belongs web domain
            {
                "web":"enable"
            }
        },
        "tui":                         # tui group
        {
            "id":"1001",               # tui group identify is 0
            "domain":                  # tui group belongs tui domain
            {
                "tui":"enable"
            }
        },
        "nas":                         # nas group
        {
            "id":"1002",               # nas group identify is 0
            "domain":                  # nas group belongs nas domain
            {
                "nas":"enable"
            }
        }
    }
}
```  


#### **Methods**

+ `check[ [domain], username, password ]` **check the username and password correct**, *correct return ttrue, wrong return tfalse, error return terror*   
    ```shell
    # examples, check the username admin correct
    land@auth.check[ ,admin, admin ]
    ttrue
    # examples, check the username admin correct with wrong password
    land@auth.check[ ,admin, passwrong ]
    tfalse
    ```

+ `match[ [domain], username, encode password ]` **match the username and password correct**, *correct return ttrue, wrong return tfalse, error return terror*   
    ```shell
    # examples, check the username admin correct
    land@auth.match[ ,admin, QQWAFASDE232323R2323SDFRALLKJLJERRRzzeswe= ]
    ttrue
    # examples, check the username admin correct with wrong password
    land@auth.match[ ,admin, passwrong ]
    tfalse
    ```

+ `authenticate[ [domain], username, encode password, tok ]` **authenticate the username and password correct**, *correct return ttrue, wrong return tfalse, error return terror*   
    ```shell
    # examples, check the username admin correct
    land@auth.authenticate[ ,admin, QQWAFASDE232323R2323SDFRALLKJLJERRRzzeswe=, bas23s234sfsdfw234 ]
    ttrue
    # examples, check the username admin correct with wrong password
    land@auth.authenticate[ ,admin, passwrong, bas23s234sfsdfw234 ]
    tfalse
    ```

+ `reinitialize[ [domain], username, password, tok, [new password], [new username] ]` **reinitialize the username or password with original password**, *succeed return ttrue, failed return tfalse, error return terror*   
    ```shell
    # examples, modify the password of admin to 12345
    land@auth.reinitialize[ ,admin, QQWAFASDE232323R2323SDFRALLKJLJERRRzzeswe=, bas23s234sfsdfw234, admin ]
    ttrue
    # examples, modify the username of admin to Bob
    land@auth.reinitialize[ ,admin, QQWAFASDE232323R2323SDFRALLKJLJERRRzzeswe=, bas23s234sfsdfw234,, Bob ]
    ttrue
    ```

+ `modify[ [domain], username, password, [new password], [new username] ]` **modify the username or password with original password**, *succeed return ttrue, failed return tfalse, error return terror*   
    ```shell
    # examples, modify the password of admin to 12345
    land@auth.modify[ ,admin, admin, 12345 ]
    ttrue
    # examples, modify the username of admin to Bob
    land@auth.modify[ ,admin, 12345, , Bob ]
    ttrue
    ```

+ `add[ [domain], username, password ]` **add a new username**, *succeed return ttrue, failed return tfalse, error return terror*   
    ```shell
    # examples, add xiaomi username, the password is xiaomin123
    land@auth.add[ ,xiaomi, xiaomin123 ]
    ttrue
    ```

+ `delete[ username[, ...] ]` **delete username**, *succeed return ttrue, failed return tfalse, error return terror*   
    ```shell
    # examples, delete the username xiaomi
    land@auth.delete[ xiaomi ]
    ttrue
    # examples, delete the username Alice and Bob 
    land@auth.delete[ Alice, Bob ]
    ttrue
    ```

+ `list[ [group] ]` **list system username**, *succeed return talk, failed return tfalse, error return terror*   
    ```json
    // Attributes introduction of talk by the method return
    {
        "user name":                 // [ string ]
        {
            "key":"username password"         // [ string ]
        }
        // "...":{...}                  // How many username show how many properties
    }    
    ```

    ```shell
    # examples, list all admin group username
    land@auth.list[ admin ]
    {
        "admin":
        {
            "key":"E@3DLKSLKJWEWWWWW"
        }
    }
    # examples, list all username
    land@auth.list
    {
        "admin":
        {
            "key":"E@3DLKSLKJWEWWWWW"
        },
        "nas":
        {
            "key":"nas"
        },
        "nobody":
        {
        }
    }
    ```

+ `domain[ username ]` **list domain belongs of username**, *succeed return talk, failed return NULL*   
    ```json
    // Attributes introduction of talk by the method return
    {
        "domain name":"domain state"   // [ string ]:[ "disable", "enable" ]
        // "...":"..."                 // How many domain show how many properties
    }    
    ```

    ```shell
    # examples, list all domain of username admin
    land@auth.domain[ admin ]
    {
        "admin":"enable",
        "tui":"enable",
        "nas":"enable"
    }
    ```

+ `status[ username ]` **get username infomation**, *succeed return talk, failed return NULL*   
    ```shell
    # examples, get the admin infomation
    land@auth.status[ admin ]
    {
        "key_tok":"need check the tok when auth",               // [ "disable", "enable" ]
        "key_modify":"key need modify at first login",            // [ "disable", "enable" ]
        "key_check":"key need strength"                         // [ "disable", "enable" ]
    }
    ```

