***
## 端口映射组件（forward@nat） 
管理所有外部接口端口映射及DMZ主机, 此功能只会在路由模式(即网关,4G,无线互联网,宽带路由器等)下工作

#### **配置** 
```json
{
    "ifname@wan": // 有线网口的端口映射
    {
        "mode":"dnat",          // dnat表示使用DNAT, 不使用双向NAT
        "rule":
        {
            "rule1":   //规则名, 可随意命名, 但必须在此文件中唯一
            {
                "targetport":"22",     // 目标端口, 即设备要映射出去的端口
                "protocol":"tcp",  // 协议: tcp为TCP, udp为UDP, tcpudp为TCP与UDP
                "destip":"192.168.8.22", // 服务器地址， 即映射到局域网内的IP地址
                "destport":"28",   // 服务器端口, 局域网服务器的实际服务端口, 空为与目标端口相同
            }
            "rule2":  //规则名, 可随意命名, 但必须在此文件中唯一
            {
                "targetport":"33-99",//目标端口,即设备要映射出去的端口,中间有-的表示从33到99之间的端口
                "protocol":"tcpudp",  // 协议: tcp为TCP, udp为UDP, tcpudp为TCP与UDP
                "destip":"192.168.8.2",  // 服务器地址， 即映射到局域网内的IP地址
                "destport":"28-90",   // 服务器端口, 空为与目标端口相同,中间有-的表示从28到90之间的端口
            }
        }
        "dmzhost":"192.168.8.250", // DMZ主机:为IP地址, 空表示无DMZ主机, 默认所有的TCP及UDP端口(以上未指定的)都映射到些主机上
        "ttl":"fix", // TTL的设置, fix为固定所有出去的包的TTL, nomodify为不减少TTL
        "ttl_fix":"64", // ttl为fix时, 此属性指定固定TTL的的值
    }
    "ifname@lte":   // 4G的的端口映射
    {
    }
    "ifname@wisp":   // 无线互联网的端口映射
    {
    }
    "vpn@pptpc":    //PPTP客户端的端口映射
    {
    }
}
```  

