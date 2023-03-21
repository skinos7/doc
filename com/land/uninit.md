
***

## Management of shutdown component
Administration of equipment shutdown task
Each project can register its own shutdown item (either through the project production tool or directly by modifying the prj.json file), which requires the system to invoke the specified interface at shutdown

There are multiple shutdown levels at shutdown process, each of which can register shutdown items, listed in shutdown order:
    - `general`    normal shutdown
    - `app2`       app shutdown
    - `app`        app shutdown
    - `manage2`    skinos manage frame shutdown
    - `manage`     skinos manage frame shutdown
    - `extern`     internet connect shutdown
    - `aradio`     wireless shutdown
    - `nradio`     wireless shutdown
    - `ethernet`   ethernet/switch shutdown
    - `modem`      modem hardware shutdown
    - `network`    network frame shutdown
    - `core2`      skinos core shutdown
    - `core`       skinos core shutdown


#### Configuration( land@uninit )

```json
// Attributes introduction 
{
    "shutdown item name":                             // [ string ], you can custom the name
    {
        "level":"shutdown levels",                      // [ string ]
        "call":"specify component or program"           // [ string ]
    }
    // "...":{ ... }     How many shutdown items show how many properties
}
// Examples
{
    "tuishutdown":                               // call the tui@telnet.shut at the app shutdown levels
    {
        "level":"app",
        "call":"tui@telnet.shut"
    },
    "sshshutdown":                               // call tui@ssh.shut at the general shutdown levels
    {
        "level":"general",
        "call":"tui@ssh.shut"
    }
}
```  

#### **Methods**

+ `add[ shutdown item name, call, [shutdown level] ]` **add a shutdown task**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, add wui@admin.shut at the app shutdown level
    land@uninit.add[ webshut, wui@admin.shut, app ]
    ttrue
    # examples, add tui@ssh.shut at the default(general) shutdown level
    land@uninit.add[ sshshut, tui@ssh.shut ]
    ttrue    
    ```

+ `delete[ shutdown item name ]` **delete a shutdown task**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, delete webshut
    land@uninit.delete[ webshut ]
    ttrue
    ```

+ `list[ [shutdown levels] ]` **list shutdown item at shutdown levels**, Not giving the specified shutdown level will list all registered shutdown items in the system, *succeed return talk to describes infomation, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "shutdown level":"call command",  // A shutdown level only needs to invoke the form of an call
        "shutdown level":                 // A shutdown level requires the form of calling multiple calls
        {
            "call command1":"",
            "call command2":""
            // "...":"..."     How many call at that level show how many properties
        }
         // "...":{ ... }     How many shutdown levels show how many properties
    }    
    ```
    ```shell
    # examples
    land@uninit.list
    {
        "app2":                         // shutdown level at app2 call agent@local.shut
        {
            "agent@local.shut":""
        },
        "app":                          // shutdown level at app call client@station.shut, clock@restart.shut, forward@alg.shut
        {
            "client@station.shut":"",  
            "clock@restart.shut":"",   
            "forward@alg.shut":""      
        },
        "manage":                       // shutdown level at manage call tui@telnet.shut, tui@ssh.shut
        {
            "tui@telnet.shut":"",      
            "tui@ssh.shut":""          
        }
    }
    ```




## 系统关机管理组件
管理系统关机项, 关机项将在系统关机时被调用

#### **关机项** 
- 每个项目可以注册自已的关机项(通过项目生产工具或直接修改prj.json文件), 即要求系统在关机时调用指定的接口
系统关机时有多个关机级别, 每个关机都可以注册关机项, 以下以引导顺序列出
    - `general`    
    - `app2`
    - `app`
    - `manage2`
    - `manage`
    - `extern`
    - `aradio`
    - `nradio`
    - `ethernet`
    - `modem`
    - `network`
    - `core2`
    - `core`

#### **配置( land@uninit )**

```json
// 属性介绍
{
    "关机项名称":               // [ 字符串 ], 关机项名称必须在此配置中唯一
    {
        "level":"关机级别",     // [ 字符串 ]
        "call":"调用接口"       // [ 字符串 ]
    }
    // "...":{ 关机项信息 }     // 更多其它的关机项
}
// 以下为示例
{
    "myshut":                   // 关机项为myshut
    {
        "level":"app",             // 关机级别为app
        "call":"uart@gnss.shut"   // 关机GPS
    },
    "myshut2":                   // 关机项为myshut2
    {
        "level":"app2",           // 关机级别为app2
        "call":"wui@admin.shut",   // 关机web服务
    }
}
```


#### **接口**

+ `add[ 关机项名称, 调用接口, [关机级别] ]` **创建关机项**, *成功返回ttrue, 失败返回tfalse, 出错返回terror*
    ```shell
    # 示例, 创建在app关机级别时调用wui@admin.shut
    land@uninit.add[ webshut, wui@admin.shut, app ]
    ttrue
    # 示例, 创建在默认(general)关机级别时调用tui@ssh.shut
    land@uninit.add[ sshshut, tui@ssh.shut ]
    ttrue    
    ```

+ `delete[ 关机项名称 ]` **删除关机项**, *成功返回ttrue, 失败返回tfalse, 出错返回terror*
    ```shell
    # 示例, 删除webshut关机项
    land@uninit.delete[ webshut ]
    ttrue
    ```

+ `list[ [关机级别] ]` **列出系统中指定关机级别的关机项**, 不给出指定关机级别将列出系统中所有注册的关机项, *成功返回如下JSON, 失败返回NULL, 出错返回terror*
    ```json
    // 属性介绍
    {
        "关机级别":"调用接口",      // 一个关机级别只需要调用一个接口的形式
        "关机级别":                  // 一个关机级别需要调用多个接口的形式
        {
            "调用接口1":"",
            "调用接口2":""
            // "...":"..."            // 更多此关机级别对应的调用接口
        }
        // "...":{ ... }              // 更多关机级别对应的关机项
    }
    ```
    ```shell
    # 示例
    land@uninit.list
    {
        "app2":                         // 关机级别为app2时:
        {
            "agent@local.shut":""           // 调用接口agent@lcoal.shut关闭本地被管理
        },
        "app":                          // 关机级别为app时:
        {
            "client@station.shut":"",      // 调用client@station.shut关闭客户端管理
            "clock@restart.shut":"",       // 调用clock@restart.shut关闭重启机制
            "forward@alg.shut":""          // 调用forward@alg.shut关闭ALG
        },
        "manage":                       // 关机级别为manage时:
        {
            "tui@telnet.shut":"",          // 调用tui@telnet.shut关闭TELNET服务器
            "tui@ssh.shut":""              // 调用tui@ssh.shut关闭SSH服务器
        }
    }
    ```



