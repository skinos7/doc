***
## 远程可管理的组件配置(agent@coms) 
列出哪些组件可以通过agent项目的remote组件来管理

#### **配置** 
```json
{
    "arch@device":{},          // 设备名称
    "arch@system":{},          // 设备工作模式
    "arch@reggpio":{},         // 设备LED灯及GPIO管理
    "arch@config":{},          // 设备组件配置的锁定配置
    "clock@date":{},           // 设备时间管理
    "clock@restart":{},        // 设备重启计划
    "land@hosts":{},           // 设备Hosts文件管理
    "land@message":{}          // 设备消息管理
    "land@syslog":{},          // 设备日志管理
    "tui/telnet":{},           // TELNET终端
    "tui/ssh":{},              // SSH终端
    "wui/admin":{},            // WEB管理网页
    "wifi/nssid":{},           // 无线SSID管理
    "wifi/nradio":{},          // 无线高级属性
    "ifname/wan":{},           // 有线宽带拨号
    "ifname/lte":{},           // 4G配置
    "ifname/lan":{},           // 本地LAN口
    "forward/firewell":{},     // 防火墙
    "forward/nat":{},          // 端口映射
    "forward/route":{},        // 静态路由表
    "forward/alg":{},          // 应用层网关
    "ddns/ipupdate":{},        // DDNS
    "upnp/miniupnpd":{}       // UPNP
}

```  
