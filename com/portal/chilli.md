***
## chilli组件（portal@chilli)  
管理chilli的组件

#### **配置** 
```json
// 属性介绍
{
    "status":"状态",                     // enable为启用, disable为关闭
    "local":"指定工作的本地接口",        // 如ifname@lan表示LAN口
    "port":"端口",
    "uiport":"UI端口", 
    "listen":"工作的本地地址",
    "net":"网段",
    "mask":"子网掩码",
    "dns":"指定DNS",
    "dns2":"指定备用DNS",
    "radius_server":"Radius服务器",
    "radius_server2":"备用Radius服务器",
    "radius_secret":"Radius服务器密钥",
    "radius_authport":"Radius认证端口",
    "radius_acctport":"Radius计费端口",
    "radius_nasid":"Radius NAS标识",
    "uam_format":"UMA Portal地址",
    "uam_secret":"UMA密钥",
    "uam_allowed":"UMA允许地址",         // 多个以逗号分隔
    "uam_domains":"UMA允许域名",         // 多个以逗号分隔
    "uam_aliasname":"UMA别名",
    "www_dir":"本地网页目录",
    "local_opt":"local.conf自定义选项",   // 多个以分号分隔, 优先级高于之上参数的值
}
// 示例
{
    "status":"disable",
    "local":"ifname@lan",
    "port":"3990",
    "uiport":"4990",
    "listen":"10.1.0.1",
    "net":"10.1.0.0",
    "mask":"255.255.255.0",
    "dns":"",
    "dns2":"",
    "radius_server":"",
    "radius_server2":"",
    "radius_secret":"",
    "radius_authport":"1812",
    "radius_acctport":"1813",
    "radius_nasid":"nas01",
    "uam_format":"",
    "uam_secret":"",
    "uam_allowed":"",
    "uam_domains":"",
    "uam_aliasname":"chilli",
    "hs_opt":"",
    "main_opt":"",
    "local_opt":"",
    "www_dir":"/mnt/interval/chilli.www"       // 本地网页目录位于/mnt/interval/chilli.www
}
```  

