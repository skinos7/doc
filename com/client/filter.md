***
## 网桥过滤组件（forward@filter） 
管理本地LAN口上的网桥模式上的过滤规则

#### **配置** 
```json
{
    "ifname@lan":      // 本地网口的过滤
    {
        "status":"enable",  // 过滤功能启用(enable)或禁用(disable)
        "default":"accept",   // 默认规则, drop表示禁用访问, accept表示允许访问
        "rule":
        {
            "test1":
            {
                "src":"21.221.128.110":  // 源地址, 通常为外网IP地址或IP地址段或MAC地址, 空表示所有IP地址
                "protocol":"all":    // tcp表示TCP， udp表UDP， all所有协议
                "dest":"192.168.8.250"   // 目的地址, 通常为内网地址
                "destport":"100-400"  // 目的端口或端口段, 100-400表示100至400之间的所有端口,空表示所有端口
                "action":"accept"     // 禁止或允许访问, drop表示禁止, accept表示允许
            }
            "test2":
            {
                "src":"202.96.122.111-202.96.122.128":  // 源地址, 通常为外网的IP地址或IP地址段或MAC地址, 表示从202.96.122.111到202.96.122.128
                "protocol":"tcp":        // tcp表示TCP， udp表UDP， all所有协议
                "dest":"192.168.8.250-192.168.8.253"    // 目的地址, 通常为内网地址
                "destport":"500,400"      // 目的端口或端口段, 500,400表示500和400两个端口
                "action":"accept"      // 禁止或允许访问, drop表示禁止, accept表示允许
            }
        }
    },
    "ifname@lan2":   // 本地网口2
    {
    }
}
```  


#### **接口** 

+ `setup[]` 初始化此组件

>*成功返回ttrue, 失败返回tfalse*

+ `shut[]` 禁用此组件功能

>*成功返回ttrue, 失败返回tfalse*


