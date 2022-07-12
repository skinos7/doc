***
## 客户端管理组件（client@station） 
此组件为管理单独的每个客户端

#### **配置(client@station)** 
```json
{
    "64:00:6A:47:66:F3":                  // 客户端MAC
    {
        "ifname":"ifname@lan",             // 指定客户端所在的接口, 省略默认为LAN
        // DHCP绑定相关
        "bindip":"192.168.8.250",          // 绑定的IP地址
        "lease":"22333",                   // 单独指定租期
        // 禁止上网相关
        "internet":"timer",  // disable为禁止联网, enable为允许上网, timer为定时上网
        "internet_timer": // 定时上网相关的时间规则, 当internet设置为timer时以下定义的时间允许上网
        {
            // 参见 client@global 配置中的internet_timer节点的说明
        },
        // 互联网访问控制相关
        "acl":"enable",     // enable为启用访问控制, disable为禁用
        "acl_rule":         // acl为enable时以下规则有效
        {
            // 参见 client@global 配置中中的acl_rule节点的说明
        },
        // 互联网访问速率控制相关
        "tc":"enable",     // enable为启用限速, disable为禁用, 出口带宽设置后才生效
        "tc_set":          // tc为enable时以下内容有效
        {
            "uprate":"",                    // 上行速率, 单位为 mbit
            "downrate":""                   // 下行速率, 单位为 mbit
        }
    },
    "AC:C1:EE:3A:3D:E0":                  // MAC
    {
        // ...
    }
}

``` 


#### **接口** 

+ `list[]` 列出所有客户端 

>*成功返回如下JSON, 失败返回NULL* 

```json
    {
        // 属性介绍
        "客户端MAC地址":
        {
            "ip":"IP地址",
            "device":"接入的网络设备",
            "ifname":"接入的网络接口",
            "ontime":"上线时系统的运行时长",      // 秒为单位
            "name":"客户端名称",
            "tx_bytes":"发送字节数",
            "rx_bytes":"接收字节数",
            "livetime":"在线时间"                // 时:分:秒:天
        }
        "客户端2MAC地址":
        {
            ...
        },
        ...                  // 更多其它客户端
        
        // 示例
        "04:CF:8C:39:91:7A":
        {
            "ip":"192.168.31.140",
            "device":"lan",
            "ifname":"ifname@lan",
            "ontime":"51",
            "name":"xiaomi-aircondition-ma2_mibt917A",
            "tx_bytes":"1779693",
            "rx_bytes":"1375610",
            "livetime":"14:39:34:1"
        },
        "40:31:3C:B5:6D:4C":
        {
            "ip":"192.168.31.61",
            "device":"lan",
            "ifname":"ifname@lan",
            "ontime":"59",
            "name":"minij-washer-v5_mibt6D4C",
            "tx_bytes":"1732003",
            "rx_bytes":"1333341",
            "livetime":"14:39:26:1"
        },
        "14:13:46:C9:97:C7":
        {
            "ip":"192.168.31.9",
            "device":"lan",
            "ifname":"ifname@lan",
            "ontime":"58",
            "name":"Skybox-Q1001-fbc6317cebd73798",
            "tx_bytes":"183198837",
            "rx_bytes":"259955379",
            "livetime":"14:39:27:1"
        }
    }
```





