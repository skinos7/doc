

***
## Account password and permission management components
Management equipment basic infomation
Manage accounts and permissions, Modifying this configuration directly is not recommended, It is recommended to manage through the interface

#### Configuration( land@auth )

```json
// Attributes introduction 
{
    "user":        //  Account list, all accounts in the system are under this node
    {
        "account name":                  // [ string ]
        {
            "id":"account identify",     // [ number ]
            "key":"account key",         // [ string ]
            "group":                     // List of groups to which the account belongs
            {
                "group name":"belongs state"  // [ string ]: [ disable,enable ]
                // "...":"..."                // How many groups belongs show how many properties
            },
            "domain":                    // List of domains to which the account belongs
            {
                "domain name":
                {
                    "key":"In this domain specialized key"        // [ string ], an empty one represents the use of the default password
                }
                // "...":{ ... }                                  // How many domain show how many properties
            }
        },
        // "...":{...}                  // How many account show how many properties
    },
    "group":     // Group list, all groups in the system are under this node
    {
        "group name":
        {
            "id":"group identify",     // [ number ]
            "domain":                  // List of all domain permissions under the group
            {
                "domain name":"enable",    // [ string ]: [ disable, enable ]
                // "...":"..."             // How many domain show how many properties
            }
        },
        // "...":{...}                  // How many group show how many properties
    }
}
// Examples
{
    "user":
    {
        "admin":                       // account: admin
        {
            "id":"0",                  // admin account id is 0
            "key":"E@3DLKSLKJWEWWWWW", // admin default key is E@3DLKSLKJWEWWWWW
            "group":                   // admin belongs gruop: admin, web, tui, nas
            {
                "admin":"enable",
                "web":"enable",
                "tui":"enable",
                "nas":"enable"
            },
            "domain":
            {
                "nas":                 // admin key is ADSAADFFF at the nas domain
                {
                    "key":"ADSAADFFF"
                },
                "web":                 // admin key is DSDFSDFF at the web domain
                {
                    "key":"DSDFSDFF"
                }
            }
        },
        "nas":                         // account: nas
        {
            "id":"1000",               // nas account id is 1000
            "key":"nas",               // nas default key is nas
            "group":                   // admin belongs gruop: nas
            {
                "nas":"enable"
            }
        }
    },
    "group":
    {
        "admin":                       // admin group
        {
            "id":"0",                  // admin group identify is 0
            "domain":                  // admin group belongs admin domain
            {
                "admin":"enable"
            }
        },
        "web":                         // web group
        {
            "id":"1000",               // web group identify is 1000
            "domain":                  // web group belongs web domain
            {
                "web":"enable"
            }
        },
        "tui":                         // tui group
        {
            "id":"1001",               // tui group identify is 0
            "domain":                  // tui group belongs tui domain
            {
                "tui":"enable"
            }
        },
        "nas":                         // nas group
        {
            "id":"1002",               // nas group identify is 0
            "domain":                  // nas group belongs nas domain
            {
                "nas":"enable"
            }
        }
    }
}
```  


#### **Methods**

+ `check[ [domain], account, password ]` **check the username and password is legal**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, check the account admin is legal
    land@auth.check[ ,admin, admin ]
    ttrue
    ```

+ `check[ [domain], account, password, [new password], [new account] ]` **modify the username or password with original password**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, modify the admin password to 12345
    land@auth.modify[ ,admin, admin, 12345 ]
    ttrue
    # examples, modify the admin account name to user
    land@auth.modify[ ,admin, admin, , user ]
    ttrue
    ```

+ `add[ [domain], account, password ]` **add a new username**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, add xiaomi username
    land@auth.add[ ,xiaomi, xiaomin123 ]
    ttrue
    ```

+ `delete[ account[, ...] ]` **delete username**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, delete the username xiaomi
    land@auth.delete[ xiaomi ]
    ttrue
    ```

+ `list[ [group] ]` **list system username**, *succeed return talk, failed return tfalse, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "account name":                 // [ string ]
        {
            "key":"account key"         // [ string ]
        }
        // "...":{...}                  // How many account show how many properties
    }    
    ```
    ```shell
    # examples, list all admin group account
    land@auth.list[ admin ]
    {
        "admin":
        {
            "key":"admin"
        }
    }
    # examples, list all account
    land@auth.list
    {
        "admin":
        {
            "key":"admin"
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

+ `domain[ account ]` **list domain belongs of username**, *succeed return talk, failed return tfalse, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "domain name":"domain state"   // [ string ]:[ disable, enable ]
        // "...":"..."                 // How many domain show how many properties
    }    
    ```
    ```shell
    # examples, list all admin domain
    land@auth.domain[ admin ]
    {
        "admin":"enable",
        "tui":"enable",
        "nas":"enable"
    }
    ```




## ?????????????????????????????????
?????????????????????, ??????????????????????????????, ???????????????????????????

#### **??????( land@auth )** 
```json
// ????????????
{
    "user":                  //  ????????????, ??????????????????????????????????????????
    {
        "?????????":                 // [ ????????? ]
        {
            "id":"??????ID",        // [ ?????? ]
            "key":"??????",         // [ ????????? ]
            "group":         // ?????????????????????
            {
                "??????":"??????",    // [ ????????? ]:[ disable, enable], enable????????????????????????, ???????????????
                // "...":"..."    // ??????????????????
            },
            "domain":        // ?????????????????????????????????????????????
            {
                "??????":                             // [ ????????? ]
                {
                    "key":"???????????????????????????"      // [ ????????? ], ???????????????????????????
                }
                // "...":{...}                      // ??????????????????
            }
        },
        // "...":{...}       // ????????????????????????
    },
    "group":                 // ?????????, ???????????????????????????????????????
    {
        "??????":                   // [ ????????? ]
        {
            "id":"???ID",          // [ ?????? ]
            "domain":             // ??????????????????????????????
            {
                "??????":"????????????",  // [ ????????? ]:[ disable, enable ], enable????????????????????????, ??????????????? 
                //  "...":"..."     // ??????????????????
            }
        },
        // "...":{...}       // ?????????????????????
    }
}
// ??????
{
    "user":                            // ????????????
    {
        "admin":                       // ????????????, ?????????admin??????
        {
            "id":"0",                  // ??????ID
            "key":"E@3DLKSLKJWEWWWWW", // ????????????, ?????????????????????????????????????????????????????????|*|V2?????????????????????????????????
            "group":                   // ???????????????
            {
                "admin":"enable",      // ?????????, enable????????????????????????, ???????????????
                "web":"enable",        // WEB???
                "tui":"enable",        // ?????????
                "nas":"enable"         // ?????????
            },
            "domain":                  // ??????????????????
            {
                "nas":                 // ?????????(nas)??????????????????
                {
                    "key":"ADSAADFFF"  // ??????????????????????????????, ???????????????????????????
                }
            }
        },
        "nas":                         // ????????????
        {
            "id":"1000",
            "key":"nas",               // ????????????
            "group":                   // ???????????????
            {
                "nas":"enable"
            }
        }
    },
    "group":                           // ?????????
    {
        "admin":                       // ?????????
        {
            "id":"0",                  // ???ID
            "domain":                  // ????????????????????????
            {
                "admin":"enable"       // ????????????????????????????????????
            }
        },
        "web":                         // WEB???
        {
            "id":"1000",
            "domain":                  // ????????????????????????
            {
                "web":"enable"         // WEB????????????????????????
            }
        },
        "tui":                         // ?????????
        {
            "id":"1001",
            "domain":                  // ????????????????????????
            {
                "tui":"enable"         // ??????????????????????????????
            }
        },
        "nas":                         // ?????????
        {
            "id":"1002",
            "domain":                  // ????????????????????????
            {
                "nas":"enable"         // ??????????????????????????????
            }
        }
    }
}
```  


#### **??????** 

+ `check[ [???], ?????????, ?????? ]` **??????????????????????????????**, *??????????????????ttrue, ??????????????????tfalse, ????????????terror*
    ```shell
    # ??????, ??????admin???????????????
    land@auth.check[ ,admin, admin ]
    ttrue
    ```

+ `modify[ [???], ?????????, ?????????, [?????????], [????????????] ]` **????????????????????????,** ??????????????????????????????????????????????????????, ?????????????????????????????????, *??????????????????ttrue, ??????????????????tfalse, ????????????terror*
    ```shell
    # ??????, ??????admin??????????????????NewPassword, ?????????????????????, ????????????123456
    land@auth.modify[,admin,123456,NewPassword]
    ttrue
    # ??????, ??????user1??????????????????cf8k2sfd, ?????????????????????, ????????????87654
    land@auth.modify[,user1,87654,cf8k2sfd]
    ttrue
    ```

+ `add[ [???], ?????????, [??????], [???,...] ]` **????????????**, ?????????????????????????????????????????????????????????, ????????????????????????????????????????????????, *??????????????????ttrue, ??????????????????tfalse, ????????????terror*
    ```shell
    # examples, add xiaomi username
    land@auth.add[ ,xiaomi, xiaomin123 ]
    ttrue
    ```
+ `delete[ ??????, [...] ]` **????????????**, ???????????????????????????, *??????????????????ttrue, ??????????????????tfalse*
    ```shell
    # examples, delete the username xiaomi
    land@auth.delete[ xiaomi ]
    ttrue
    ```

+ `list[ [???] ]` **???????????????????????????????????????????????????????????????**, *????????????JSON, ?????????JSON??????; ????????????NULL*
    ```json
    // ????????????
    {
        "?????????":                      // [ ????????? ]
        {
            "key":"??????"               // [ ????????? ]
        }
        //  "...":{...}                // ????????????
    }
    ```
    ```shell
    # ??????, ??????????????????????????????
    land@auth.list
    {
        "admin":                       // ???????????????
        {
            "key":"J@#FDSSDFSDFS"      // ??????
        },
        "nas":                         // ????????????
        {
            "key":"SE$*SDFSKFSDF"
        },
        "nobody":
        {
        }
    }
    ```

+ `domain[ ?????? ]` **????????????????????????**, *????????????JSON, ?????????JSON??????; ????????????NULL*
    ```json
    // ????????????
    {
        "?????????":"????????????",  // enable?????????, disable?????????
        // ...                // ???????????????
    }
    ```
    ```shell
    # ??????, ????????????admin????????????
    land@auth.domain[ admin ]
    {
        "admin":"enable",        // ?????????????????????
        "wui":"enable",          // ????????????????????????
        "tui":"enable",          // ????????????????????????
        "nas":"enable"          // ??????????????????
    }
    ```


#### ??????

+ `??????????????????` *?????????????????????????????????????????????: ??????>???>?????????*

>+ ?????????????????????????????????

>+ ???????????????????????????????????????

>+ ???????????????????????????, ??????????????????????????????????????????, ???????????????????????? ???????????????????????????????????????

>+ ???????????????????????????(??????????????????), ????????????????????????????????????, ?????????????????????????????????????????????nas???, ???nas??????????????????????????????nas????????????



