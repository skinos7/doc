***
## Accept remote management
connect to remote server and accept administrative command from the that

#### Configuration( agent@remote )
```json
{
    "status":"enable or disable to connect the remote",    // [ "disable", "enable" ]
    "id":"identify for device",                            // [ string ]
    "user":"username for device",                          // [ string ]
    "vcode":"vcode for device",                            // [ string ]
    "remote":"remote server address",                      // [ string ]
    "remote2":"remote server address2",                    // [ string ]
    "remote3":"remote server address3",                    // [ string ]
    "con_timeout":"timeout for connect",                   // [ number ], the unit is second
    "talk_timeout":"timeout for wait ack",                 // [ number ], the unit is second
    "report":                                              // report status after connect succeed
    {
        "interval":"report interval",                       // [number ], the unit is second
        "status":                                           // There are which statuses are being reported
        {
            "he command":"",                                // [ string ]: "",  string is he command
            "he command2":""                                // [ string ]: "",  string is he command
            // "...":""
        }
    }
}
```
Examples, show all the configure
```shell
agent@remote
{
    "status":"enable",                                      # Accept remote management is enable
    "remote":"http://http.wmdevice.com:10101/dev",          # remote server is http://http.wmdevice.com:10101/dev
    "con_timeout":"20",                                     # connect timeout is 20 seccond
    "talk_timeout":"40",                                    # post json timeout is 40 seccond
    "report":
    {
        "interval":"30",                                    # report interval is 30 second
        "status":
        {
            "land@machine.status":                          # only report the machine status
            {
            }
        }
    }
}
```  
Examples, disable the accept remote management
```shell
agent@remote:status=disable
ttrue
```  


## 远程被管理组件(agent@remote) 
与云平台连接, 实现云平台远程管理本设备

#### **配置** 
```json
// 属性介绍
{
    "status":"是否连接云服务器",    // [ "disable", "enable" ], enable为开启, disable或其它表示关闭
    "id":"设备ID",                  // [ 字符串 ], 指明设备唯一的标识
    "user":"管理帐号",              // [ 字符串 ], 指明设备属性哪一个管理帐号
    "vcode":"验证码",               // [ 字符串 ], 当所属帐号要求被管理设备必须给出正确的验证码时设置
    "remote":"云服务器地址",        // [ 字符串 ]
    "remote2":"备用云服务器地址",   // [ 字符串 ]
    "remote3":"备用云服务器地址2",  // [ 字符串 ]
    "con_timeout":"连接最大超时",   // [ 数字 ], 秒为单位
    "talk_timeout":"交互最大超时",  // [ 数字 ], 秒为单位 
    "report":                       // 初始上报行为配置
    {
        "interval":"上报间隔",      // 秒为单位
        "status":                   // 要求上报的状态
        {
            "he指令1":"",           // [ 字符串 ]:"",
            "he指令2":""            // [ 字符串 ]:""
            // "更多he指令":""
        }
    }
}
```
示例, 显示所有配置
```shell
agent@remote
{
    "status":"disable",                                 # 开启连接云服务器
    "user":"dimmalex@gmail.com",                        # 管理帐号为dimmalex@gmail.com
    "vcode":"111111",                                   # 管理帐号验证码
    "remote":"http://device.wmdevice.com:10101/dev",    # <云服务器地址>
    "remote2":"http://device2.wmdevice.com:10101/dev",  # <备用云服务器地址>
    "remote3":"http://device3.wmdevice.com:10101/dev",  # <备用云服务器地址2>
    "con_timeout":"20",                                 # 连接最大超时为20秒
    "talk_timeout":"40",                                # POST JSON最大超时为40秒
    "report":                      # 初始上报行为配置
    {
        "interval":"30",           # 上报间隔为30秒
        "status":                  # 要求上报的状态
        {
            "land@machine.status":"",    # 要求上报设备基本状态信息
            "network@frame.status":""    # 要求上报设备网络状态信息
        }
    }
}
```  
示例, 禁用远程管理
```shell
agent@remote:status=disable
ttrue
```  

