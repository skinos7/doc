***
## 凌壹GPS协议管理组件（gnss@zeroone） 
实现从设备的GPS信号源获取GPS定义数据并通过凌壹协议发送到指定服务器

#### **配置(gnss@zeroone)**
```json
// 属性介绍
{
    "status":"凌壹客户端状态",     // [ "disable", "enable" ], disable为禁用, enable为启用
    "server":"凌壹服务器地址",     // [ string ] 支持域名
    "port":"服务器端口",           // [ number ]
    "interval":"上报间隔",         // [ number ], 以秒为单位

    "deviceid":"设备ID号",         // [ string ]
    "devicetype":"设备类型",       // [ string ]
    "packettype":"报文类型"        // [ string ]
}

```  

