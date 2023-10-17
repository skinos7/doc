***
## 缓存并POST定位数据管理（gnss@bufpost） 
POST定位数据到指定的服务器, 并在POST失败或无网络时自动存储到本地

#### 配置( gnss@bufpost )

```json
// 属性介绍
{
    "status":"状态",                   // [ "disable", "enable" ], disable为禁用, enable为启用

    "con_timeout":"连接超时",                  // [ string ]
    "talk_timeout":"POST后等待回复超时",       // [ number ], 以秒为单位
    "post_interval":"上报间隔",                // [ number ], 以秒为单位
    "buf_interval":"存储间隔",                 // [ number ], 以秒为单位

    "remote":"URL",                // [ string ]
    "id":"设备ID号",               // [ string ]
    "user":"用户名",               // [ string ]
    "vcode":"密码"                 // [ string ]
}

```  

