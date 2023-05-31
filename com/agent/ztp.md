***
## Zero touch provision management
Zero touch provision from dhcp, http, mail, U/TF storage

#### Configuration( agent@ztp )
```json
{
    "dhcp":"disable or enable listen for ztp from dhcp",            // [ "disable", "enable" ]
    "dhcp_cfg":
    {
    },
    "storage":"disable or enable listen for ztp from dhcp",         // [ "disable", "enable" ]
    "storage_cfg":
    {
    },
    "remote":"disable or enable listen for ztp from remote server", // [ "disable", "enable" ]
    "remote_cfg":
    {
    }
}
```
Examples, show all the configure
```shell
agent@ztp
{
}
```  
Examples, enable the JSON command accept
```shell
agent@ztp:dhcp=enable
ttrue
```  


## 零配置管理组件
管理设备是否允许被零配置

#### **配置(agent@ztp)** 
```json
// 属性介绍
{
}
```
示例, 显示所有的配置
```shell
agent@ztp
{
}
```
示例, 启用DHCP的ZTP功能
```shell
agent@ztp:dhcp=enable
ttrue
```  

