
1. 简介
    <L2TP服务器>, 管理L2TP服务器的连接

2. 配置 
    通过vpn/l2tpd管理
    {
        "status":"enable|disable",              // <状态>: 启用/禁用
        "port":"1701",                         // 服务<端口>
        "localip":"192.168.100.1",             // <服务器IP地址>
        "ipstart":"192.168.100.50",             // 地址池<起始地址>
        "ipend":"192.168.100.200",             // 地址池<结束地址>
        "pppopt":"require-mschap-v2;require-chap" // 自定义的<PPP的选项>
    }

3. 命令

