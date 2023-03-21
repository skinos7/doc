
***

## Management of Boot startup component
Administration of equipment initialize task
Each project can register its own startup item (either through the project production tool or directly by modifying the prj.json file), which requires the system to invoke the specified interface at boot time 

There are multiple boot levels at boot process, each of which can register boot items, listed in boot order:
    - `core`       skinos core init
    - `core2`      skinos core init
    - `network`    network frame init
    - `modem`      modem hardware init
    - `ethernet`   ethernet/switch init
    - `nradio`     wireless init
    - `aradio`     wireless init
    - `extern`     internet connect init
    - `manage`     skinos manage frame init
    - `manage2`    skinos manage frame init
    - `app`        app init
    - `app2`       app init
    - `general`    The system at this level has been booted, and all applications without startup sequence requirements should be initialized at this level 
*It is not recommended for common application developers to register extern and previous launchers*


#### Configuration( land@init )

```json
// Attributes introduction 
{
    "startup item name":                             // [ string ], you can custom the name
    {
        "level":"boot levels",                          // [ string ]
        "call":"specify component or program"           // [ string ]
    }
    // "...":{ ... }     How many boot startup items show how many properties
}
// Examples
{
    "tuisetup":                               // call the tui@telnet.setup at the app boot levels
    {
        "level":"app",
        "call":"tui@telnet.setup"
    },
    "webreset":                               // call wui@admin.reset at the general boot levels
    {
        "level":"general",
        "call":"wui@admin.reset"
    }
}
```  

#### **Methods**

+ `add[ startup item name, call, [boot level] ]` **add a boot startup task**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, add wui@admin.reset at the app boot level
    land@init.add[ webreset, wui@admin.reset, app ]
    ttrue
    # examples, add tui@ssh.setup at the default(general) boot level
    land@init.add[ sshsetup, tui@ssh.setup ]
    ttrue    
    ```

+ `delete[ startup item name ]` **delete a startup task**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, delete webreset
    land@init.delete[ webreset ]
    ttrue
    ```

+ `list[ [boot levels] ]` **list startup item at boot levels**, Not giving the specified boot level will list all registered boot items in the system, *succeed return talk to describes infomation, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "boot level":"call command",  // A start level only needs to invoke the form of an call
        "boot level":                 // A start level requires the form of calling multiple calls
        {
            "call command1":"",
            "call command2":""
            // "...":"..."     How many call at that level show how many properties
        }
         // "...":{ ... }     How many boot levels show how many properties
    }    
    ```
    ```shell
    # examples
    land@init.list
    {
        "app2":                         // boot level at app2 call agent@local.setup
        {
            "agent@local.setup":""
        },
        "app":                          // boot level at app call client@station.setup, clock@restart.setup, forward@alg.setup
        {
            "client@station.setup":"",  
            "clock@restart.setup":"",   
            "forward@alg.setup":""      
        },
        "manage":                       // boot level at manage call tui@telnet.setup, tui@ssh.setup
        {
            "tui@telnet.setup":"",      
            "tui@ssh.setup":""          
        }
    }
    ```




## 系统启动管理组件
管理系统启动项, 启动项将在系统引导时被调用

#### **启动项** 
- 每个项目可以注册自已的启动项(通过项目生产工具或直接修改prj.json文件), 即要求系统在引导时调用指定的接口
系统引导时有多个启动级别, 每个级别都可以注册启动项, 以下以引导顺序列出
    - `core`       初始化核心
    - `core2`      初始化核心
    - `network`    网络框架初始化, 本地接口等在此初始化
    - `modem`      LTE/NR基带初始化
    - `ethernet`   有线网络相关硬件初始化
    - `nradio`     无线相关硬件初始化
    - `aradio`     无线相关硬件初始化
    - `extern`     外网连接初始化, 外网连接的一些APP初始化
    - `manage`     资源管理框架初始化, 客户端管理, 网页服务器, 终端命令行在此初始化
    - `manage2`    资源管理框架初始化
    - `app`        应用初始化, 各种网络应用在此初始化
    - `app2`       应用初始化
    - `general`    此级别系统已完成引导, 所有无启动顺序要求的应用应在此初始化
*不建议普通应用开发者注册extern及以前的启动项*

#### **配置( land@init )**

```json
// 属性介绍
{
    "启动项名称":               // [ 字符串 ], 名称可自定义, 启动项名称必须在此配置中唯一
    {
        "level":"启动级别",     // [ 字符串 ]
        "call":"调用接口"       // [ 字符串 ]
    }
    // "...":{ 启动项信息 }     // 更多其它的启动项
}
// 以下为示例
{
    "mystart":                   // 启动项为mystart
    {
        "level":"app",             // 启动级别为app
        "call":"uart@gnss.setup"   // 启动GPS
    },
    "mystart2":                   // 启动项为mystart2
    {
        "level":"app2",           // 启动级别为app2
        "call":"wui@admin.setup",   // 启动web服务
    }
}
```


#### **接口**

+ `add[ 启动项名称, 调用接口, [启动级别] ]` **创建启动项**, *成功返回ttrue, 失败返回tfalse, 出错返回terror*
    ```shell
    # 示例, 创建在app启动级别时调用wui@admin.reset
    land@init.add[ webreset, wui@admin.reset, app ]
    ttrue
    # 示例, 创建在默认(general)启动级别时调用tui@ssh.setup
    land@init.add[ sshsetup, tui@ssh.setup ]
    ttrue    
    ```

+ `delete[ 启动项名称 ]` **删除启动项**, *成功返回ttrue, 失败返回tfalse, 出错返回terror*
    ```shell
    # 示例, 删除webreset启动项
    land@init.delete[ webreset ]
    ttrue
    ```

+ `list[ [启动级别] ]` **列出系统中指定启动级别的启动项**, 不给出指定启动级别将列出系统中所有注册的启动项, *成功返回如下JSON, 失败返回NULL, 出错返回terror*
    ```json
    // 属性介绍
    {
        "启动级别":"调用接口",      // 一个启动级别只需要调用一个接口的形式
        "启动级别":                  // 一个启动级别需要调用多个接口的形式
        {
            "调用接口1":"",
            "调用接口2":""
            // "...":"..."            // 更多此启动级别对应的调用接口
        }
        // "...":{ ... }              // 更多启动级别对应的启动项
    }
    ```
    ```shell
    # 示例
    land@init.list
    {
        "app2":                         // 启动级别为app2时:
        {
            "agent@local.setup":""           // 调用接口agent@lcoal.setup初始化本地被管理
        },
        "app":                          // 启动级别为app时:
        {
            "client@station.setup":"",      // 调用client@station.setup初始化客户端管理
            "clock@restart.setup":"",       // 调用clock@restart.setup初始化重启机制
            "forward@alg.setup":""          // 调用forward@alg.setup初始化ALG
        },
        "manage":                       // 启动级别为manage时:
        {
            "tui@telnet.setup":"",          // 调用tui@telnet.setup初始化TELNET服务器
            "tui@ssh.setup":""              // 调用tui@ssh.setup初始化SSH服务器
        }
    }
```



