***
## FTP服务器（storage@ftp） 
管理FTP服务器

#### **配置** 
```json
{
    "status":"disable",                 // <状态>，启用为enable, 禁用为disable
    "mode":"anonymous",                 // <访问方式>, anonymous为匿名访问, user或其它或空为合法的系统用户访问
    "root":"/tmp/webpage",              // ftp可以访问的目录
    "anonymous":                        // 匿名设置部分
    {
        "path":"/tmp/webpage",             // <匿名可以访问的路径>
        "permission":"all"                 // 对共享路径的<权限>，all: 可读可写，read或其它表示可读不可写
    },
    "user":                                // 通过用户名和密码访问samba的设置
    {
        "media":                                // 某项共享目录的设置
        {
            "path":"/tmp/webpage",             // <用户可以访问的路径>
            "permission":"all",                 // 对共享路径的<权限>，all: 可读可写，read或其它表示可读不可写
            "user":                            // 用户列表
            {
                "admin":"all"                  // 单独指定用户权限<用户名>:<权限> , 权限为all可读可写，为read可读不可写, 为none或其它表示无权限
                // 更多用户权限...
            }
        },
        //...更多可访问项
    }
}
```

