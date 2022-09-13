***
## 文件共享组件（storage@samba） 
此组件管理文件共享

#### **配置**  
```json
{
    "status":"disable",                    // <状态>，enable为启用, disable为禁用
    "mode":"anonymous",                    // <访问方式>, anonymous为匿名访问, user或其它或空为合法的系统用户访问
    "anonymous":                           // 匿名设置部分
    {
        "path":"/tmp/run/mountd",               // <共享路径>
        "permission":"all"                       // 对共享路径的<权限>，all: 可读可写，read或其它表示可读不可写
    },
    "user":                                // 通过用户名和密码访问samba的设置
    {
        "media":                                        // 某项共享目录的设置
        {
            "path":"/tmp/run/mountd",                   // <共享路径>
            "permission":"all",                         // 对共享路径的<权限>，all: 可读可写，read或其它表示可读不可写
            "user":                                     // 用户列表
            {
                "admin":"all"                           // 单独指定用户权限<用户名>:<权限> , 权限为all可读可写，为read可读不可写, 为none或其它表示无权限
                // 更多用户权限...
            }
        }
        //...更多可访问项
    }
}
```  

#### **接口** 
+ `passwd[]` 更新文件共享的密码, 当系统用户密码变化时应调用此接口同步文件服务器中用户对应的密码  
    >*成功返回ttrue, 失败返回tfalse* 

