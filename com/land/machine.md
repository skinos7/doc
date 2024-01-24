
***
## Management of Basic Infomation
Manage gateway basic infomation

#### Configuration( land@machine )

```json
// Attributes introduction 
{
    // main attributes
    "mode":"gateway operator mode",                 // < "ap", "wisp", "nwisp", "gateway", "dgateway", "misp", "nmisp", "dmisp", "mix" >
                                                       // "ap": access point
                                                       // "wisp": 2.4G Wireless Internet Service Provider connection
                                                       // "nwisp": 5.8G Wireless Internet Service Provider connection( need the board support 5.8G wirless baseband)
                                                       // "gateway": wire WAN gateway
                                                       // "dgateway": Dual wire WAN gateway
                                                       // "misp": LTE Mobile Internet Service Provider connection( need the board support LTE baseband)
                                                       // "nmisp": Next Mobile(NR/LTE) Internet Service Provider connection( need the board support NR/LTE baseband)
                                                       // "dmisp": Dual Mobile(LTE/NR) Internet Service Provider connection( need the board support two LTE/NR baseband)
                                                       // "mix": custom mix connection from multiple internet connection
                                                     
    "name":"gateway name",                          // < string >, The name cannot contain spaces
    "mac":"gateway MAC address",                    // < mac address >
    "macid":"gateway MAC identify or serial id",    // < string >
    "language":"gateway language",                  // [ "cn", "en", "jp", ... ], language code in two letter, "cn" for Chinese, “en" for English
    // other attributes
    "cfgversion":"gateway configure version",       // [ string ]
    "gpversion":"gateway group configure version"   // [ string ]
}
```

Examples, show all basic configure
```shell
land@machine
{
    "mode":"nmisp",                              # gateway operator mode Next Mobile(LTE/NR) Internet Service Provider connection
    "name":"ASHYELF-12AAD0",                     # gateway name is ASHYELF-12AAD0
    "mac":"00:03:7F:12:AA:D0",                   # gateway MAC is 88:12:4E:20:46:B0
    "macid":"00037F12AAD0",                      # gateway serial id is 88124E2046B0
    "language":"cn",                             # gateway language is chinese
    "cfgversion":"1"                             # gateway configure version is 1(hint modify one times)
}
```  

Examples, modify the gateway name
```shell
land@machine:name=NewMachineName
ttrue
```  

Examples, show the gateway name after modified
```shell
land@machine:name
NewMachineName
```  

Examples, modify the operation mode to "mix"
```shell
land@machine:mode=mix
ttrue
```  

Examples, modify the gateway language to English
```shell
land@machine:language=en
ttrue
```  

#### **Methods**

+ `default[ [delay] ]` **default the gateway configure and restart**, *succeed return ttrue or cannot return, failed return tfalse, error return terror*   
    ```shell
    # examples, default the gateway configure and restart immediately( the call may cannot return beacuse the system restart now )
    land@machine.default
    # ---- system restart -----
    # examples, default the gateway configure and restart after 10 second( the call will be return immediately )
    land@machine.default[ 10 ]
    ttrue
    ```

+ `default_block[]` **disable all operator of default the gateway configure**, *succeed return ttrue, failed return tfalse, error return terror*   
    ```shell
    # examples, disable all operator of default the gateway configure
    land@machine.default_block
    ttrue
    # then you cannot defualt the gateway configure after land@machine.default_block
    land@machine.default
    machine.default: Operation not permitted
    ```

+ `default_unblock[]` **enable all operator of default the gateway configure**, *succeed return ttrue, failed return tfalse, error return terror*   
    ```shell
    # first, disable all operator of default the gateway configure
    land@machine.default_block
    ttrue
    # then you cannot defualt the gateway configure after land@machine.default_block
    land@machine.default
    machine.default: Operation not permitted
    # examples, enable all operator of default the gateway configure
    land@machine.default_unblock
    ttrue
    # then you can default the gateway configure
    land@machine.default
    # ---- system restart ----
    ```

+ `restart[ [delay] ]` **reboot the gateway**, *succeed return ttrue or cannot return, failed return tfalse, error return terror*   
    ```shell
    # examples, reboot the gateway immediately( the call may cannot return beacuse the system restart now )
    land@machine.restart
    ttrue
    # examples, reboot the gateway after 10 second( the call will be return immediately )
    land@machine.restart[ 10 ]
    ttrue
    ```

+ `restart_block[]` **disable all operator of reboot the gateway**, *succeed return ttrue, failed return tfalse, error return terror*   
    ```shell
    # examples, disable all operator of reboot the gateway
    land@machine.restart_block
    ttrue
    # then you cannot reboot the gateway after land@machine.restart_block
    land@machine.restart
    machine.restart: Operation not permitted
    ```

+ `restart_unblock[]` **enable all operator of reboot the gateway**, *succeed return ttrue, failed return tfalse, error return terror*   
    ```shell
    # first, disable all operator of reboot the gateway
    land@machine.restart_block
    ttrue
    # then you cannot reboot the gateway after land@machine.default_block
    land@machine.restart
    machine.restart: Operation not permitted
    # examples, enable all operator of reboot the gateway
    land@machine.restart_unblock
    ttrue
    # then you can reboot the gateway
    land@machine.restart
    # ---- system restart ----
    ```

+ `status[]` **get the gateway basic infomation**, *succeed return talk to describes basic infomation, failed return NULL, error return terror*   
    ```json
    // Attributes introduction of talk by the method return
    {
        "mode":"gateway operator mode",              // < "ap", "wisp", "nwisp", "gateway", "dgateway", "misp", "nmisp", "dmisp", "mix" >
                                                         // "ap": access point
                                                         // "wisp": 2.4G Wireless Internet Service Provider connection
                                                         // "nwisp": 5.8G Wireless Internet Service Provider connection( need the board support 5.8G wirless baseband)
                                                         // "gateway": wire WAN gateway
                                                         // "dgateway": Dual wire WAN gateway
                                                         // "misp": LTE Mobile Internet Service Provider connection( need the board support LTE baseband)
                                                         // "nmisp": Next Mobile(NR/LTE) Internet Service Provider connection( need the board support NR/LTE baseband)
                                                         // "dmisp": Dual Mobile(LTE/NR) Internet Service Provider connection( need the board support two LTE/NR baseband)
                                                         // "mix": custom mix connection from multiple internet connection
        "name":"gateway name",
        "platform":"gateway platform identify",
        "hardware":"gateway hardware identify",
        "custom":"gateway custom identify",
        "scope":"gateway scope identify",
        "version":"gateway version",
        "cfgversion":"gateway configure version",        // [ string ]
        "gpversion":"gateway group configure version",   // [ string ]
        "livetime":"system running time",                // hour:minute:second:day
        "current":"current date",                        // hour:minute:second:month:day:year
        "mac":"gateway MAC address",
        "macid":"gateway MAC identify or serial id",
        "model":"gateway model",
        "cmodel":"gateway custom model",
        "magic":"gateway magic identify"
    }    
    ```

    ```shell
    # examples, get the gateway basic infomation
    land@machine.status
    {
        "mode":"nmisp",                                   # gateway operator mode Next Mobile(NR/LTE) Internet Service Provider connection
        "name":"ASHYELF-12AAD0",                          # gateway name is ASHYELF-12AAD0
        "platform":"smtk2",                               # gateway platform identify is smtk2( hint the basic sdk is second release of smtk )
        "hardware":"mt7621",                              # gateway hardware identify is mt7621( hint the chip is MT7621 )
        "custom":"d228",                                  # gateway custom identify is d228( hint the product name is D228 )
        "scope":"std",                                    # gateway scope identify is std( hint this is a standand release for D228 )
        "version":"tiger7-20220218",                      # gateway version is tiger7-20220218( hint the version publish at 2022.02.18 )
        "cfgversion":"6",                                 # gateway cfgversion is 6, configure maybe modified 6 times
        "livetime":"00:06:35:0",                          # gateway It has been running for 6 minutes and 35 seconds
        "current":"14:54:30:05:04:2022",                  # current date is 2022.05.04, It's 14:54 and 30 seconds
        "mac":"00:03:7F:12:AA:D0",                        # gateway MAC is 00:03:7F:12:AA:D0
        "macid":"00037F12AAD0",                           # gateway serial id is 00037F12AAD0
        "model":"5228",                                   # gateway model is 5228
        "magic":"870E2935E4605D02"                        # gateway magic is 870E2935E4605D02
    }
    ```

+ `cpuinfo[]` **get the gateway CPU infomation**, *succeed return talk to describes CPU infomation, failed return NULL, error return terror*   
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
    # examples, get the gateway cpu infomation
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

+ `meminfo[]` **get the gateway memory infomation**, *succeed return talk to describes memory infomation, failed return NULL, error return terror*   
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
    # examples, get the gateway memory infomation
    land@machine.meminfo
    {
        "total":"125584",
        "free":"54076",
        "buffers":"6520",
        "cached":"22024"
    }
    ```

+ `fsinfo[]` **get the gateway filesystem infomation**, *succeed return talk to describes filesystem infomation, failed return NULL, error return terror*   
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
    # examples, get the gateway filesystem infomation
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
        "/tmp/mnt/config":                                     # configure file system
        {
            "filesystem":"/dev/mtdblock7",
            "size":"1.0M",
            "used":"200.0K",
            "available":"824.0K",
            "use":"20%"
        },
        "/tmp/mnt/internal":                                  # interval file system for fpk install
        {
            "filesystem":"/dev/mtdblock6",
            "size":"3.8M",
            "used":"260.0K",
            "available":"3.5M",
            "use":"7%"
        }
    }
    ```

+ `sginfo[]` **get the gateway storage filesystem infomation**, *succeed return talk to describes storage filesystem infomation, failed return NULL, error return terror*   
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
    # examples, get the gateway storage filesystem infomation
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

+ `esinfo[]` **get the gateway extension storage filesystem infomation**, *succeed return talk to describes extension storage filesystem infomation, failed return NULL, error return terror*   
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
    # examples, get the gateway extension storage filesystem infomation
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

+ `psinfo[]` **get the gateway process infomation**, *succeed return talk to describes process infomation, failed return NULL, error return terror*   
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
    # examples, get the gateway process infomation
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



