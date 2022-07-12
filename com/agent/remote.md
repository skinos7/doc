***
## 远程被管理组件(agent@remote) 
与云平台连接, 实现云平台远程管理本设备

#### **配置** 
```json
// 属性介绍
{
    "status":"是否连接云服务器",    // enable为连接, disable或其它都表示为禁用
    "user":"管理帐号",             // 指明设备属性哪一个管理帐号
    "vcode":"验证码",              // 当所属帐号要求被管理设备必须给出正确的验证码时设置
    "remote":"云服务器地址",
    "remote2":"备用云服务器地址",
    "remote3":"备用云服务器地址2",
    "con_timeout":"连接最大超时",   // 秒为单位
    "talk_timeout":"交互最大超时",  // 秒为单位 
    "report":                      // 初始上报行为配置
    {
        "interval":"上报间隔",      // 秒为单位
        "status":                  // 要求上报的状态
        {
            "he指令1":"",
            "he指令2":""
        }
    }
}
// 示例
{
    "status":"disable",            // 开启连接云服务器
    "user":"dimmalex@gmail.com",   // 管理帐号为dimmalex@gmail.com
    "vcode":"111111",              // 管理帐号验证码
    "remote":"http://device.wmdevice.com:10101/dev",     //<云服务器地址>
    "remote2":"http://device2.wmdevice.com:10101/dev",   //<备用云服务器地址>
    "remote3":"http://device3.wmdevice.com:10101/dev",   //<备用云服务器地址2>
    "con_timeout":"20",            // 连接最大超时为20秒
    "talk_timeout":"40",           // 交互最大超时为40秒
    "report":                      // 初始上报行为配置
    {
        "interval":"30",           // 上报间隔为30秒
        "status":                  // 要求上报的状态
        {
            "land@machine.status":"",    // 要求上报设备基本状态信息
            "network@frame.status":""    // 要求上报设备网络状态信息
        }
    }
}
```  

