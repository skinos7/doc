***
## Accept local network management
Accept administrative command from the local network

#### Configuration( agent@local )
```json
{
    "broadcast":"disable or enable listen for broadcast command from the local",  // [ "disable", "enable" ]
    "broadcast_port":"broadcast port",                                            // [ number ], default is 22222
    "broadcast_group":"group name",                                               // [ string ], default is default
    "json":"disable or enable listen for JSON command from the local",            // [ "disable", "enable" ]
    "json_port":"JSON port"                                                       // [ number ], defaultis 22220
}
```
Examples, show all the configure
```shell
agent@local
{
    "broadcast":"enable",                 # listen for broadcast command from the local network
    "broadcast_port":"22222",             # broadcast port is UDP 22222
    "broadcast_group":"default",          # broadcast group is default
    "json":"disable",                     # JSON command accept is disable
    "json_port":"22220"                   # JSON command listen TCP port is 22220
}
```  
Examples, enable the JSON command accept
```shell
agent@local:json=enable
ttrue
```  


## 本地被管理组件
监听局域网的管理请求, 实现局域网批量被管理

#### **配置(agent@local)** 
```json
// 属性介绍
{
    "broadcast":"是否监听来自局域网的管理",    // [ "disable", "enable" ], enable为开启, disable或其它表示关闭
    "broadcast_port":"监听UDP端口",            // [ 数字 ], 默认为22222
    "broadcast_group":"所属组",                // [ 字符串 ], 默认为default
    "json":"是否启动JSON控制协议",             // [ "disable", "enable" ], enable为开启, disable或其它为关闭(不建议默认开启, 除非局域网为安全信任区域)
    "json_port":"JSON控制协议TCP端口"          // [ 数字 ], 默认为22220
}
```
示例, 显示所有的配置
```shell
agent@local
{
    "broadcast":"enable",            # 开启监听来自局域网的管理
    "broadcast_group":"default",     # 属于default组
    "json":"enable"                  # 启动JSON控制协议
}
```
示例, 启用JSON控制协议
```shell
agent@local:json=enable
ttrue
```  

