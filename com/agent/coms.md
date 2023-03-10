***
## Manage remotely manageable components
all remotely manageable components name save in here

#### Configuration( agent@coms )
```json
{
    "name of component":{},         // [ string ]:{}
    // "...":{}   more components
}
```  
Examples, show all the configure( list all remotely manageable components )
```shell
agent@coms
{
    "land@machine":{},     
    "land@syslog":{},
    "network@hosts":{},
    "ifname@wan":{},
    "ifname@wan2":{},
    "ifname@wisp":{},
    "ifname@wisp2":{},
    "ifname@lte":{},
    "ifname@lte2":{},
    "ifname@lan":{},
    "ifname@lan2":{},
    "wifi@nssid":{},
    "wifi@n":{},
    "wifi@assid":{},
    "wifi@a":{},
    "tui@telnet":{},
    "tui@ssh":{},
    "wui@admin":{},
    "clock@date":{},
    "clock@restart":{},
    "clock@ntps":{}
}
```  


## 存储远程可管理的组件
所有可以被远程管理的组件都存在此文件中

#### 配置( agent@coms )
```json
{
    "组件名称":{},         // [ 字符串 ]:{}
    // "...":{}   更多
}
```  
示例， 显示所有配置
```shell
agent@coms
{
    "land@machine":{},     
    "land@syslog":{},
    "network@hosts":{},
    "ifname@wan":{},
    "ifname@wan2":{},
    "ifname@wisp":{},
    "ifname@wisp2":{},
    "ifname@lte":{},
    "ifname@lte2":{},
    "ifname@lan":{},
    "ifname@lan2":{},
    "wifi@nssid":{},
    "wifi@n":{},
    "wifi@assid":{},
    "wifi@a":{},
    "tui@telnet":{},
    "tui@ssh":{},
    "wui@admin":{},
    "clock@date":{},
    "clock@restart":{},
    "clock@ntps":{}
}
```  
