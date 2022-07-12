***
## 本地被管理组件(agent@local) 
监听局域网的管理请求, 实现局域网批量被管理

#### **配置** 
```json
// 属性介绍
{
    "broadcast":"是否监听来自局域网的管理",  // 监听来自局域网的管理: enable为开启, disable或其它表示关闭
    "broadcast_port":"监听UDP端口",          // 默认通过22222监听来自局域网的管理
    "broadcast_group":"所属组",              // 默认属于default组
    "json":"是否启动JSON控制协议",           // enable为开启, disable或其它为关闭(不建议默认开启, 除非局域网为安全信任区域)
    "json_port":"JSON控制协议TCP端口"        // 默认为22223
}
// 示例
{
    "broadcast":"enable",            // 开启监听来自局域网的管理
    "broadcast_group":"default",     // 属于default组
    "json":"enable"                  // 启动JSON控制协议
}

```

