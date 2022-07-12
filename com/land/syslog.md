
***

## Syslog management component
Management syslog

#### Configuration( land@syslog )

```json
// Attributes introduction 
{
    "status":"syslog status",          // [ disable, enable, tui, file, both]
                                            // enable for syslog
                                            // disable for no log
                                            // tui for output to terminal
                                            // both for output to terminal and syslog
                                            // file for output to file
    "trace":"record code information", // [ disable, enable ]
    "level":"log level",               // [ verbose, debug, info, warn, fault ]
                                            // verbose for debug business data 
                                            // debug for debug code
                                            // info for normal infomation
                                            // warn for warnningr infomation
                                            // fault for error infomation
    "type":"Type of logs",             // [ default, land, arch, joint, service, gather, network, modem ]
                                            // default for default type, to which all logs of unspecified type are classified
                                            // land for skinos frame log
                                            // arch for skinos arch project log
                                            // joint for joint event log
                                            // service for service log
                                            // gather for remote control log
                                            // network for network frame log
                                            // modem for lte/nr log
                                            // Separate multiple options with ;

    "klog":"kernel log status",         // [ disable, enable ]
    "size":"log size",                  // [ number ], The unit is kbyte. logs will be overwritten when they exceed the size of the recording pool
    "location":"location of logs",      // [ memory, interval, storage, sda ]
                                            // memory for stored in the memory and will be lost upon restart
                                            // int for stored in the internal flash. Strong columns are not recommended in the internal program area, which may cause corruption  
                                            // storage for stored in external storage
                                            // sda for sda starts with a specified mount disk
                                            // stored in xxxx-syslog.txt file in the root directory when "location" is internal, storage, starts with sda

    "remote":"Remote Log server",     // [ string ], If this parameter is left blank, the remote log server is disabled
    "port":"Remote Log port"          // [ number ], default is 514
}
// Examples
{
    "status":"enable",                // enable the syslog
    "location":"memory",              // logs stored in memory
    "type":"arch|land|default",       // log the arch, land, default log
    "level":"info",                   // log level is normal infomation
    "trace":"disable",                // disable the code information
    "size":"100",                     // log buffer is 100k
    "remote":"",                      // none remote syslog server
    "port":"514"
}
```  


#### **Methods**

+ `path[]` **show log location and max size**, *succeed return talk, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "path":"log file pathname",   // [ string ]
        "size":"log file size limit"  // [ number ], the unit is Kbyte
    }    
    ```
    ```shell
    # examples, show current log file pathname and size limit
    land@syslog.path
    {
        "path":"/var/3618760113-syslog.txt",
        "size":"100"
    }
    ```

+ `clear[]` **clear the log**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples
    land@syslog.clear
    ttrue
    ```

+ `show[]` **show the log**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples
    land@syslog.show
    May 12 01:58:16 ASHYELF-12ADB0 daemon.debug modem@lte2: 6 >>66>> (AT+QNWINFO^M^M +QNWINFO: "FDD LTE","46001","LTE BAND 3",1650^M ^M OK^M )
    May 12 01:58:16 ASHYELF-12ADB0 daemon.debug modem@lte2: 6 <<< (at+qeng="servingcell"^M )
    May 12 01:58:16 ASHYELF-12ADB0 daemon.debug modem@lte2: 6 >>22>> (at+qeng="servingcell"^M)
    May 12 01:58:16 ASHYELF-12ADB0 daemon.debug modem@lte2: 6 <<< (AT+CREG?^M )
    May 12 01:58:16 ASHYELF-12ADB0 daemon.debug modem@lte2: 6 >>9>> (AT+CREG?^M)
    May 12 01:58:16 ASHYELF-12ADB0 daemon.debug modem@lte2: 6 >>48>> (AT+CREG?^M^M +CREG: 2,1,"2604","6DA5A09",7^M ^M OK^M )
    May 12 01:58:16 ASHYELF-12ADB0 daemon.debug modem@lte2: 6 <<< (AT+CSQ^M )
    May 12 01:58:16 ASHYELF-12ADB0 daemon.debug modem@lte2: 6 >>28>> (AT+CSQ^M^M +CSQ: 18,99^M ^M OK^M )    
    ttrue
    ```

+ `info[]` **record a level of info log**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples
    land@syslog.info[ "this is log for info level" ]
    ttrue
    ```

+ `warn[]` **record a level of warn log**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples
    land@syslog.info[ "this is log for warn level" ]
    ttrue
    ```

+ `fault[]` **record a level of fault log**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples
    land@syslog.info[ "this is log for fault level" ]
    ttrue
    ```



## 日志管理组件
管理系统日志，因是常用组件所以还有简称为log（即不带land@前缀）, 因系统暂无其它日志管理组件, 所以log也被指向此组件
使用log接口及libland下的syslog_string函数记录的日志都将被此组件管理

#### **配置( land@syslog )** 
```json
// 属性介绍
{
    "status":"日志的状态",         // [ disable, enable, tui, file, both ]
                                        // enable为启用
                                        // disable或其它为禁用
                                        // tui为终端打印
                                        // both为同时开启syslog及终端打印
                                        // file为输出到一个指定的文件, 此状态下location应为一个路径
    "trace":"是否记录代码信息",    // [ disable, enable ]
    "level":"日志级别",            // [ info, debug, verbose, warn, fault ]
                                        // ault为错误
                                        // warn为警告
                                        // info为通知
                                        // debug为调试
                                        // verbose为详细
    "type":"记录的日志的类型",     // [ default, land, arch, joint, service, gather, network, modem ]
                                        // default为默认类型, 所有未指定类型的日志都归类于此类
                                        // land为skinos核心日志
                                        // arch为skinos硬件架构日志
                                        // service为服务相关的日志
                                        // joint为事件相关的日志
                                        // gather为远程管理相关的日志
                                        // network为网络相关的日志
                                        // modem为LTE/NR模块相关的日志
                                        // 此处支持多选, 多个类型间以;号分隔即可
    "klog":"klog的状态",           // [ disable, enable ]
    "size":"记录池大小",           // [ number ], k为单位, 超过记录池的大小后日志会被覆盖
    "location":"记录日志的位置",   // [ memory, interval, storage, sda ]
                                        // memory为记录在内存中, 重启即丢失
                                        // int为记录在内部程序区, 强列不建议存于内部程序区, 可能导致内部程序区损坏
                                        // storage为外部存储区
                                        // sda开头则表示指定的某个挂载盘
                                        // 当为internal或storage或sda的挂载盘时, 会在根目录下以xxxx-syslog.txt文件中记录日志
    "remote":"远程日志服务器",     // [ string ], 空表示不开启远程日志服务器
    "port":"远程日志端口"          // [ number], 默认为514
}
// 示例
{
    "status":"enable",                  // 开启syslog
    "type":"land|service|joint|default",// 记录skinos核心, 服务, 事件及其它默认类型相关的日志
    "klog":"disable",                   // 禁用内核日志
    "level":"info",                     // 只记录通知级别的日志
    "trace":"enable",                   // 记录代码位置及进程ID
    "size":"20",                        // 记录池为20k
    "remote":"192.168.8.250",           // 远程日志服务器地址为192.168.8.250
    "port":"514"                        // 远程日志服务器的端口为514
}
```  


#### **接口** 

+ `path[]` **获到日志位置及大小限制**, *成功返回talk, 失败返回NULL, 出错返回terror*
    ```json
    // 属性介绍
    {
        "path":"日志文件存储位置",   // [ string ]
        "size":"日志文件大小限制"    // [ number ], 单位为kbyte
    }    
    ```
    ```shell
    # 示例
    land@syslog.path
    {
        "path":"/var/3618760113-syslog.txt", # 日志文件位于/var/3618760113-syslog.txt
        "size":"100"                         # 日志大小限制是100k
    }
    ```

+ `clear[]` **清除所有日志**, *成功返回ttrue, 失败返回tfalse, 出错返回terror*
    ```shell
    # 示例
    land@syslog.clear
    ttrue
    ```

+ `show[]` **显示所有日志**, *成功返回ttrue, 失败返回tfalse, 出错返回terror*
    ```shell
    # 示例
    land@syslog.show
    May 12 01:58:16 ASHYELF-12ADB0 daemon.debug modem@lte2: 6 >>66>> (AT+QNWINFO^M^M +QNWINFO: "FDD LTE","46001","LTE BAND 3",1650^M ^M OK^M )
    May 12 01:58:16 ASHYELF-12ADB0 daemon.debug modem@lte2: 6 <<< (at+qeng="servingcell"^M )
    May 12 01:58:16 ASHYELF-12ADB0 daemon.debug modem@lte2: 6 >>22>> (at+qeng="servingcell"^M)
    May 12 01:58:16 ASHYELF-12ADB0 daemon.debug modem@lte2: 6 <<< (AT+CREG?^M )
    May 12 01:58:16 ASHYELF-12ADB0 daemon.debug modem@lte2: 6 >>9>> (AT+CREG?^M)
    May 12 01:58:16 ASHYELF-12ADB0 daemon.debug modem@lte2: 6 >>48>> (AT+CREG?^M^M +CREG: 2,1,"2604","6DA5A09",7^M ^M OK^M )
    May 12 01:58:16 ASHYELF-12ADB0 daemon.debug modem@lte2: 6 <<< (AT+CSQ^M )
    May 12 01:58:16 ASHYELF-12ADB0 daemon.debug modem@lte2: 6 >>28>> (AT+CSQ^M^M +CSQ: 18,99^M ^M OK^M )    
    ttrue
    ```

+ `info[]` **记录一条通知日志**, *成功返回ttrue, 失败返回tfalse, 出错返回terror*
    ```shell
    # 示例
    land@syslog.info[ "this is log for info level" ]
    ttrue
    ```

+ `warn[]` **记录一条警告日志**, *成功返回ttrue, 失败返回tfalse, 出错返回terror*
    ```shell
    # 示例
    land@syslog.info[ "this is log for warn level" ]
    ttrue
    ```

+ `fault[]` **记录一条错误日志**, *成功返回ttrue, 失败返回tfalse, 出错返回terror*
    ```shell
    # 示例
    land@syslog.info[ "this is log for fault level" ]
    ttrue
    ```

