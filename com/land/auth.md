

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




## 帐号密码及权限管理组件
管理帐号及权限, 不建议直接修改此配置, 建议通过接口来管理

#### **配置( land@auth )** 
```json
// 属性介绍
{
    "user":                  //  帐号列表, 系统中所有的帐号都在此节点下
    {
        "帐号名":                 // [ 字符串 ]
        {
            "id":"帐号ID",        // [ 数字 ]
            "key":"密钥",         // [ 字符串 ]
            "group":         // 帐号所属组列表
            {
                "组名":"状态",    // [ 字符串 ]:[ disable, enable], enable为使能为此组成员, 其它为禁用
                // "...":"..."    // 可能的更多组
            },
            "domain":        // 针对帐号中域信息专用的存放节点
            {
                "域名":                             // [ 字符串 ]
                {
                    "key":"在此域中专门的密钥"      // [ 字符串 ], 空表示使用默认密码
                }
                // "...":{...}                      // 可能的更多域
            }
        },
        // "...":{...}       // 系统中其它的帐号
    },
    "group":                 // 组列表, 系统中所有的组都在此节点下
    {
        "组名":                   // [ 字符串 ]
        {
            "id":"组ID",          // [ 数字 ]
            "domain":             // 组下所有的域权限列表
            {
                "域名":"域名状态",  // [ 字符串 ]:[ disable, enable ], enable为使能为此域成员, 其它为禁用 
                //  "...":"..."     // 可能的更多域
            }
        },
        // "...":{...}       // 系统中其它的组
    }
}
// 示例
{
    "user":                            // 帐号列表
    {
        "admin":                       // 管理帐号, 此处为admin帐号
        {
            "id":"0",                  // 帐号ID
            "key":"E@3DLKSLKJWEWWWWW", // 默认密码, 对应的域下未设置密码时将使用此密码，以|*|V2开头的为经过加密的密码
            "group":                   // 所属组列表
            {
                "admin":"enable",      // 管理组, enable为使能为此组成员, 其它为禁用
                "web":"enable",        // WEB组
                "tui":"enable",        // 终端组
                "nas":"enable"         // 存储组
            },
            "domain":                  // 对应的域信息
            {
                "nas":                 // 存储域(nas)下的专用信息
                {
                    "key":"ADSAADFFF"  // 在存储域下专门的密码, 空表示使用默认密码
                }
            }
        },
        "nas":                         // 存储帐号
        {
            "id":"1000",
            "key":"nas",               // 默认密码
            "group":                   // 所属组列表
            {
                "nas":"enable"
            }
        }
    },
    "group":                           // 组列表
    {
        "admin":                       // 管理组
        {
            "id":"0",                  // 组ID
            "domain":                  // 所有的域权限列表
            {
                "admin":"enable"       // 管理组拥用管理员域的权限
            }
        },
        "web":                         // WEB组
        {
            "id":"1000",
            "domain":                  // 所有的域权限列表
            {
                "web":"enable"         // WEB组拥用存储域权限
            }
        },
        "tui":                         // 终端组
        {
            "id":"1001",
            "domain":                  // 所有的域权限列表
            {
                "tui":"enable"         // 终端组拥用存储域权限
            }
        },
        "nas":                         // 存储组
        {
            "id":"1002",
            "domain":                  // 所有的域权限列表
            {
                "nas":"enable"         // 存储组拥用存储域权限
            }
        }
    }
}
```  


#### **接口** 

+ `check[ [域], 帐号名, 密码 ]` **检测帐号密码是否合法**, *修改成功返回ttrue, 修改失败返回tfalse, 出错返回terror*
    ```shell
    # 示例, 检测admin帐号及密码
    land@auth.check[ ,admin, admin ]
    ttrue
    ```

+ `modify[ [域], 帐号名, 原密码, [新密码], [新帐号名] ]` **修改帐号名或密码,** 新密码及新帐号名两个参数必须给出一个, 不给出域表示修改默认域, *修改成功返回ttrue, 修改失败返回tfalse, 出错返回terror*
    ```shell
    # 示例, 修改admin用户的密码为NewPassword, 需要给出原密码, 原密码为123456
    land@auth.modify[,admin,123456,NewPassword]
    ttrue
    # 示例, 修改user1用户的密码为cf8k2sfd, 需要给出原密码, 原密码为87654
    land@auth.modify[,user1,87654,cf8k2sfd]
    ttrue
    ```

+ `add[ [域], 帐号名, [密码], [组,...] ]` **添加帐号**, 给出组将在添加新帐号同时添加进对应的组, 不给出域参数表示密码添加到默认域, *添加成功返回ttrue, 添加失败返回tfalse, 出错返回terror*
    ```shell
    # examples, add xiaomi username
    land@auth.add[ ,xiaomi, xiaomin123 ]
    ttrue
    ```
+ `delete[ 帐号, [...] ]` **删除帐号**, 可同时给出多个帐号, *修改成功返回ttrue, 修改失败返回tfalse*
    ```shell
    # examples, delete the username xiaomi
    land@auth.delete[ xiaomi ]
    ttrue
    ```

+ `list[ [组] ]` **列出系统中所有帐号或列出参数中指定组的帐号**, *成功返回JSON, 以下为JSON介绍; 失败返回NULL*
    ```json
    // 属性介绍
    {
        "帐号名":                      // [ 字符串 ]
        {
            "key":"密钥"               // [ 字符串 ]
        }
        //  "...":{...}                // 更多帐号
    }
    ```
    ```shell
    # 示列, 列出系统中所有的帐号
    land@auth.list
    {
        "admin":                       // 管理员帐号
        {
            "key":"J@#FDSSDFSDFS"      // 密钥
        },
        "nas":                         // 存储帐号
        {
            "key":"SE$*SDFSKFSDF"
        },
        "nobody":
        {
        }
    }
    ```

+ `domain[ 帐号 ]` **列出帐号所属的域**, *成功返回JSON, 以下为JSON介绍; 失败返回NULL*
    ```json
    // 属性介绍
    {
        "权限域":"是否启用",  // enable为启用, disable为禁用
        // ...                // 更多权限域
    }
    ```
    ```shell
    # 示列, 列出用户admin对应的域
    land@auth.domain[ admin ]
    {
        "admin":"enable",        // 管理员域的权限
        "wui":"enable",          // 网页管理域的权限
        "tui":"enable",          // 终端管理域的权限
        "nas":"enable"          // 存储域的权限
    }
    ```


#### 解释

+ `组件配置结构` *以上组件配置的结构方式分为三层: 帐号>组>域权限*

>+ 帐号可以同时属于多个组

>+ 组可以同时拥有多个域的权限

>+ 因三层结构相对复杂, 暂时以将组与域权限一对一对应, 即只有帐号与组， 每个组拥有一个单独的域权限

>+ 组在系统中预先内置(基于功能内置), 对应的帐号可以创建及删除, 如添加了存储功能即为存储内置了nas组, 在nas组中实现添加删除属于nas组的帐号



