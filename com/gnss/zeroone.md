***
## 凌壹GPS协议管理组件（gnss@zeroone） 
实现从设备的GPS信号源获取GPS定义数据并通过凌壹协议发送到指定服务器

#### **配置**   
```json
{
    // 属性介绍
    "status":"凌壹客户端状态",   // disable为禁用, enable为启用
    "server":"凌壹服务器地址",   // 支持域名
    "port":"服务器端口",
    "interval":"上报间隔",       // 以秒为单位
    "deviceid":"设备ID号",
    "devicetype":"设备类型",
    "packettype":"报文类型"
}

```  

