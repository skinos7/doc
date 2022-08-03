***
## 默认客户端管理组件(client@default) 
此组件为客户端默认的配置, 设置后, 未指定的客户端都将已此为默认设置

#### **配置(client@default)** 
```json
{
    "ifname@lan":                  // 位于LAN口上的所有配置
    {
        // 流量控制相关
        "tc":"enable",     // enable为启用限速, disable为禁用, 出口带宽设置后才生效
        "tc_set":          // tc为enable时以下内容有效
        {
            "uprate":"",                    // 上行速率
            "downrate":""                   // 下行速率
        }
    }
}
```

