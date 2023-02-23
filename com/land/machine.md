
***
## Management of basic infomation component
Management equipment basic infomation

#### Configuration( land@machine )

```json
// Attributes introduction 
{
    // main attributes
    "mode":"equipment operator mode",                // < ap, wisp, nwisp, gateway, dgateway, misp, nmisp, dmisp, mix >
                                                       // ap: access point
                                                       // wisp: 2.4G Wireless Internet Service Provider connection
                                                       // nwisp: 5.8G Wireless Internet Service Provider connection( need the board support 5.8G wirless baseband)
                                                       // gateway: wire WAN gateway
                                                       // dgateway: Dual wire WAN gateway
                                                       // misp: LTE Mobile Internet Service Provider connection( need the board support LTE baseband)
                                                       // nmisp: Next LTE/NR Mobile Internet Service Provider connection( need the board support LTE/NR baseband)
                                                       // dmisp: Dual LTE/NR Mobile Internet Service Provider connection( need the board support two LTE/NR baseband)
                                                       // mix: custom mix connection from multiple internet connection
                                                     
    "copyright":"show the logo by designer",         // [ disable, enable  ]
    "name":"equipment name",                         // <string>
    "mac":"equipment MAC address",                   // < MAC address >
    "macid":"equipment MAC identify or serial id",   // < string >
    "language":"equipment language",                 // [ cn, en, jp, ... ], language code in two letter
    // other attributes
    "cfgversion":"equipent configure version",       // [ string ]
    "gpversion":"equipent group configure version"   // [ string ]
}
```
Examples, show all configure
```shell
land@machine
{
    "mode":"nmisp",                              # equipment operator mode Next LTE/NR Mobile Internet Service Provider connection
    "name":"ASHYELF-12AAD0",                     # equipment name is ASHYELF-12AAD0
    "mac":"00:03:7F:12:AA:D0",                   # equipment MAC is 88:12:4E:20:46:B0
    "macid":"00037F12AAD0",                      # equipment serial id is 88124E2046B0
    "language":"cn",                             # equipent language is chinese
    "cfgversion":"1"                             # equipent configure version is 1(hint modify one times)
}
```  
Examples, modify the machine name
```shell
land@machine:name=NewMachineName
ttrue
```  

#### **Methods**

+ `default[ [delay] ]` **default the equipent configure and restart**, *succeed return ttrue or cannot return, failed return tfalse, error return terror*
    ```shell
    # examples, default the equipent configure and restart immediately( the call may cannot return beacuse the system restart now )
    land@machine.default
    # ---- system restart -----
    # examples, default the equipent configure and restart after 10 second( the call will be return immediately )
    land@machine.default[ 10 ]
    ttrue
    ```

+ `default_block[]` **disable all operator of default the equipent configure**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, disable all operator of default the equipent configure
    land@machine.default_block
    ttrue
    # then you cannot defualt the equipent configure after land@machine.default_block
    land@machine.default
    machine.default: Operation not permitted
    ```

+ `default_unblock[]` **enable all operator of default the equipent configure**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # first, disable all operator of default the equipent configure
    land@machine.default_block
    ttrue
    # then you cannot defualt the equipent configure after land@machine.default_block
    land@machine.default
    machine.default: Operation not permitted
    # examples, enable all operator of default the equipent configure
    land@machine.default_unblock
    ttrue
    # then you can default the equipent configure
    land@machine.default
    # ---- system restart ----
    ```

+ `restart[ [delay] ]` **reboot the equipent**, *succeed return ttrue or cannot return, failed return tfalse, error return terror*
    ```shell
    # examples, reboot the equipent immediately( the call may cannot return beacuse the system restart now )
    land@machine.restart
    ttrue
    # examples, reboot the equipent after 10 second( the call will be return immediately )
    land@machine.restart[ 10 ]
    ttrue
    ```

+ `restart_block[]` **disable all operator of reboot the equipent**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, disable all operator of reboot the equipent
    land@machine.restart_block
    ttrue
    # then you cannot reboot the equipent after land@machine.restart_block
    land@machine.restart
    machine.restart: Operation not permitted
    ```

+ `restart_unblock[]` **enable all operator of reboot the equipent**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # first, disable all operator of reboot the equipent
    land@machine.restart_block
    ttrue
    # then you cannot reboot the equipent after land@machine.default_block
    land@machine.restart
    machine.restart: Operation not permitted
    # examples, enable all operator of reboot the equipent
    land@machine.restart_unblock
    ttrue
    # then you can reboot the equipent
    land@machine.restart
    # ---- system restart ----
    ```

+ `status[]` **get the equipent basic infomation**, *succeed return talk to describes basic infomation, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "mode":"equipment operator mode",               // < ap, wisp, nwisp, gateway, dgateway, misp, nmisp, dmisp, mix >
                                                          // ap: access point
                                                          // wisp: 2.4G Wireless Internet Service Provider connection
                                                          // nwisp: 5.8G Wireless Internet Service Provider connection( need the board support 5.8G wirless baseband)
                                                          // gateway: wire WAN gateway
                                                          // dgateway: Dual wire WAN gateway
                                                          // misp: LTE Mobile Internet Service Provider connection( need the board support LTE baseband)
                                                          // nmisp: Next LTE/NR Mobile Internet Service Provider connection( need the board support LTE/NR baseband)
                                                          // dmisp: Dual LTE/NR Mobile Internet Service Provider connection( need the board support two LTE/NR baseband)
                                                          // mix: custom mix connection from multiple internet connection
        "name":"equipment name",
        "platform":"equipment platform identify",
        "hardware":"equipment hardware identify",
        "custom":"equipment custom identify",
        "scope":"equipment scope identify",
        "version":"equipment version",
        "livetime":"system running time",               // hour:minute:second:day
        "current":"current date",                       // hour:minute:second:month:day:year
        "mac":"equipment MAC address",
        "macid":"equipment MAC identify or serial id",
        "model":"equipment model",
        "magic":"equipment magic identify"
    }    
    ```
    ```shell
    # examples, get the equipent basic infomation
    land@machine.status
    {
        "mode":"nmisp",                                   # equipment operator mode Next LTE/NR Mobile Internet Service Provider connection
        "name":"ASHYELF-12AAD0",                          # equipment name is ASHYELF-12AAD0
        "platform":"smtk2",                               # equipment platform identify is smtk2( hint the basic sdk is second release of smtk )
        "hardware":"mt7621",                              # equipment hardware identify is mt7621( hint the chip is MT7621 )
        "custom":"d228",                                  # equipment custom identify is d228( hint the product name is D228 )
        "scope":"std",                                    # equipment scope identify is std( hint this is a standand release for D228 )
        "version":"tiger7-20220218",                      # equipment version is tiger7-20220218( hint the version publish at 2022.02.18 )
        "livetime":"00:06:35:0",                          # equipment It has been running for 6 minutes and 35 seconds
        "current":"14:54:30:05:04:2022",                  # current date is 2022.05.04, It's 14:54 and 30 seconds
        "mac":"00:03:7F:12:AA:D0",                        # equipment MAC is 00:03:7F:12:AA:D0
        "macid":"00037F12AAD0",                           # equipment serial id is 00037F12AAD0
        "model":"5228",                                   # equipment model is 5228
        "magic":"870E2935E4605D02"                        # equipent magic is 870E2935E4605D02
    }
    ```

+ `cpuinfo[]` **get the equipent CPU infomation**, *succeed return talk to describes CPU infomation, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "cpu":
        {
            "user":"normal processes executing in user mode",
            "nice":"niced processes executing in user mode",
            "system":"processes executing in kernel mode",
            "idle":"iddling thumb",
            "iowait":"waiting for I/O to complete",
            "irq":"servicing interrupts",
            "softirq":"servicing softirqs"
        }
        //"cpu core identify":{ cpu infomation }     How many CPU cores show how many properties
    }
    ```
    ```shell
    # examples, get the equipent cpu infomation
    land@machine.cpuinfo
    {
        "cpu":                       # total CPU
        {
            "user":"389",
            "nice":"0",
            "system":"2769",
            "idle":"34014",
            "iowait":"12",
            "irq":"0",
            "softirq":"493"
        },
        "cpu0":                      # CPU core 0
        {
            "user":"142",
            "nice":"0",
            "system":"996",
            "idle":"8383",
            "iowait":"0",
            "irq":"0",
            "softirq":"13"
        },
        "cpu1":                      # CPU core 1
        {
            "user":"58",
            "nice":"0",
            "system":"396",
            "idle":"8851",
            "iowait":"0",
            "irq":"0",
            "softirq":"144"
        },
        "cpu2":                      # CPU core 2
        {
            "user":"131",
            "nice":"0",
            "system":"864",
            "idle":"8194",
            "iowait":"12",
            "irq":"0",
            "softirq":"168"
        },
        "cpu3":                      # CPU core 3
        {
            "user":"56",
            "nice":"0",
            "system":"512",
            "idle":"8584",
            "iowait":"0",
            "irq":"0",
            "softirq":"167"
        }
    }
    ```

+ `meminfo[]` **get the equipent memory infomation**, *succeed return talk to describes memory infomation, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "total":"total memory size",       // The unit is KB  
        "free":"free memory size",         // The unit is KB  
        "buffers":"buffer cache size",     // The unit is KB  
        "cached":"page cache size"         // The unit is KB  
    }
    ```
    ```shell
    # examples, get the equipent memory infomation
    land@machine.cpuinfo
    {
        "total":"125584",
        "free":"54076",
        "buffers":"6520",
        "cached":"22024"
    }
    ```

+ `fsinfo[]` **get the equipent filesystem infomation**, *succeed return talk to describes filesystem infomation, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
         // How many filesystem show how many properties
        "file system mount path":
        { 
            "filesystem":"device path",
            "size":"total szie",               // K ending mean KB, M endinf mean MB
            "used":"has been used",            // K ending mean KB, M endinf mean MB
            "available":"available size",      // K ending mean KB, M endinf mean MB
            "use":"usage rate"                 // percentage
        }
    }
    ```
    ```shell
    # examples, get the equipent filesystem infomation
    land@machine.fsinfo
    {
        "/":                                             # root file system
        {
            "filesystem":"/dev/root",
            "size":"9.5M",
            "used":"9.5M",
            "available":"0",
            "use":"100%"
        },
        "/tmp/.cfg":                                     # configure file system
        {
            "filesystem":"/dev/mtdblock7",
            "size":"1.0M",
            "used":"200.0K",
            "available":"824.0K",
            "use":"20%"
        },
        "/tmp/mnt/int":                                  # interval file system for fpk install
        {
            "filesystem":"/dev/mtdblock6",
            "size":"3.8M",
            "used":"260.0K",
            "available":"3.5M",
            "use":"7%"
        }
    }
    ```

+ `sginfo[]` **get the equipent storage filesystem infomation**, *succeed return talk to describes storage filesystem infomation, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
         // How many storage filesystem show how many properties
        "storage filesystem identify":
        { 
            "filesystem":"device path",
            "size":"total szie",               // K ending mean KB, M endinf mean MB
            "used":"has been used",            // K ending mean KB, M endinf mean MB
            "available":"available size",      // K ending mean KB, M endinf mean MB
            "use":"usage rate"                 // percentage
        }
    }
    ```
    ```shell
    # examples, get the equipent storage filesystem infomation
    land@machine.sginfo
    {
        "config":                                 # configure file system
        {
            "size":"1.0M",
            "used":"200.0K",
            "available":"824.0K",
            "use":"20%"
        },
        "int":                                    # interval file system for fpk install
        {
            "path":"/tmp/mnt/int",
            "size":"3.8M",
            "used":"260.0K",
            "available":"3.5M",
            "use":"7%"
        }
    }
    ```

+ `esinfo[]` **get the equipent extension storage filesystem infomation**, *succeed return talk to describes extension storage filesystem infomation, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
         // How many extension storage filesystem show how many properties
        "storage filesystem identify":
        { 
            "filesystem":"device path",
            "size":"total szie",               // K ending mean KB, M endinf mean MB
            "used":"has been used",            // K ending mean KB, M endinf mean MB
            "available":"available size",      // K ending mean KB, M endinf mean MB
            "use":"usage rate"                 // percentage
        }
    }
    ```
    ```shell
    # examples, get the equipent extension storage filesystem infomation
    land@machine.sginfo
    {
        "int":                                    # interval file system for fpk install
        {
            "path":"/tmp/mnt/int",
            "size":"3.8M",
            "used":"260.0K",
            "available":"3.5M",
            "use":"7%"
        }
    }
    ```

+ `psinfo[]` **get the equipent process infomation**, *succeed return talk to describes process infomation, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
         // How many process show how many properties
        "process identify":
        {
            "name":"process name",
            "state":"process state",
            "ppid":"parent process identify",
            "fdsize":"Number of file descriptor slots currently allocated",
            "vmsize":"Virtual memory usage of the entire process"
        }
    }
    ```
    ```shell
    # examples, get the equipent process infomation
    land@machine.psinfo
    {
        "1":
        {
            "name":"procd",
            "state":"S",
            "pid":"0",
            "fdsize":"32",
            "vmsize":"2736"
        },
        "2":
        {
            "name":"kthreadd",
            "state":"S",
            "pid":"0",
            "fdsize":"32"
        },
        "3":
        {
            "name":"ksoftirqd/0",
            "state":"S",
            "pid":"2",
            "fdsize":"32"
        },
        "4":
        {
            "name":"kworker/0:0",
            "state":"S",
            "pid":"2",
            "fdsize":"32"
        },
        # ......
    }
    ```



## 设备基本信息管理
管理设备基本信息

#### **配置( land@machine )**  
```json
// 属性介绍
{
    // 主要的属性
    "mode":"设备工作模式",                           // < ap, wisp, nwisp, gateway, dgateway, misp, nmisp, dmisp, mix >
                                                       // ap: 热点
                                                       // wisp: 2.4G无线连网
                                                       // nwisp: 5.8G无线连网
                                                       // gateway: 有线宽带
                                                       // dgateway: 双(WAN)有线宽带
                                                       // misp: 4G网关
                                                       // nmisp: 4G/5G网关
                                                       // dmisp: 双4G/5G网关
                                                       // mix: 可自定义的混合连网
                                                     
    "name":"设备名称",                              // <字符串>
    "mac":"设备MAC地址",                            // <MAC地址>
    "macid":"设备序列号",                           // <字符串>
    "language":"设备语言",                          // [ cn, en, jp, ... ], 两个小写字母表示的国家代号
    // 其它属性
    "cfgversion":"设备配置版本",                     // [ 字符串 ]
    "gpversion":"设备组配置版本",                    // [ 字符串 ]    
}
```
示例, 显示所有配置
```shell
land@machine
{
    "mode":"nmisp",                              # 设备工作模式为4G/5G网关
    "name":"ASHYELF-12AAD0",                     # 设备名称为ASHYELF-12AAD0
    "mac":"00:03:7F:12:AA:D0",                   # 设备MAC为00:03:7F:12:AA:D0
    "macid":"00037F12AAD0",                      # 设备序列号为00037F12AAD0
    "language":"cn",                             # 设备语言为中文
    "cfgversion":"1"                             # 设备配置版本(1暗示配置被修改过1次)
}

```  



