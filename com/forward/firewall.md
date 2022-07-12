***
## 防火墙组件（forward@firewall） 
管理防火墙用于访止外网设备对内网的访问, 此功能只会在路由模式(即网关,4G,无线互联网,宽带路由器等)下工作

#### **配置** 
```json
{
    "ifname@wan":      // 有线网口的防火墙，只有在 网关 或 混合 工作模式下才可以查看及设置
    {
        "status":"enable",  // 防火墙功能启用(enable)或禁用(disable)
        "default":"drop",    // 默认规则, drop表示禁用访问, accept表示允许访问
        "input_icmp_through":"enable",  // 允许ICMP的访问, 为空或无表示禁止放行, enable表示允许通过
        "input_telnet_through":"enable",  // 允许Telnet的访问, 为空或无表示禁止放行, enable表示允许通过
        "input_ssh_through":"enable",  // 允许SSH的访问, 为空或无表示禁止放行, enable表示允许通过
        "input_wui_through":"enable",  // 允许WEB的访问, 为空或无表示禁止放行, enable表示允许通过

        "nat_through":"enable",  // 默认自动放开NAT映射中的规则的访问, 为空或无表示启用, disable表示禁用自动放开
        "forward_icmp_through":"enable",  // 放开ICMP的通行, 为空或无表示禁止放行, enable表示允许通过

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
    }
    "ifname@lte":   // 4G的防火墙，只有在 4G 或 混合 工作模式下才可以查看及设置
    {
    }
    "ifname@wisp":   // 无线互联网的防火墙，只有在 无线互联网 或 混合 工作模式下才可以查看及设置
    {
    }
    "vpn@pptpc":    //PPTP客户端的防火墙，只有在开启了PPTP客户端才可以查看及设置
    {
    }
}
```  


