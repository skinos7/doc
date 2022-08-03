***
## 默认客户端管理组件（client@global） 
此组件为客户端全局配置, 设置后, 所有客户端都将会应用此设置

#### **配置(client@global)** 
```json
{
    "ifname@lan":                  // 客户端MAC
    {
        // 禁止上网相关
        "internet":"disable",  // disable为禁止联网, enable为允许上网, timer为定时上网
        "internet_timer": // 定时上网相关的时间规则, 当internet设置为timer时以下定义的时间允许上网
        {
            "rule1":
            {
                "datestart":"",  // 启始时间，YYYY[-MM[-DD[Thh[:mm[:ss]]]]]
                "datestop":"",   // 结束时间，YYYY[-MM[-DD[Thh[:mm[:ss]]]]]
                "timestart":"",  // 每天开始时间: 在启始时间与结束时间内, 每天允许上网的开始时间，hh:mm[:ss], 例如，11:22:33
                "timestop":"",   // 每天结束时间: 在启始时间与结束时间内, 每天允许上网的结束时间，11:22:33；若指定了开始时间，没指定结束时间，则结束时间为23:59:59
                "weekdays":"1,2" // 每周的星期号: 在启始时间与结束时间内, 允许上网的星期号, 0-6表示星期日、一、二、三、四、五、六, 可同时多个以逗号间隔
            },
            "rule2":   // 1月份内每周日及周六的9点半到11点半可以上网
            {
                "datestart": "2017-1-1T00:00:00",
                "datestop": "2017-2-1T00:00:00",
                "timestart": "9:30:00",
                "timestop": "11:30:00",
                "weekdays": "0,6"
            },
            "rule3":   // 2月份内每天的9点半到11点半可以上网
            {
                "datestart": "2017-2-1T00:00:00",
                "datestop": "2017-3-1T00:00:00",
                "timestart": "9:30:00",
                "timestop": "11:30:00"
            }
            //...更多规则
        },

        // 访问控制相关
        "acl":"enable",     // enable为启用访问控制, disable为禁用
        "acl_rule":         // acl为enable时以下规则有效
        {
            "rule1_xxx":
            {
                "action":"", // drop为丢弃, accept为接受, return为跳出之后的规则
                "type":"ip", // ip表示控制访问的IP地址及端口, dns表示为域名, app表示为某些应用(以后扩展用,暂不支持)
                "proto":"",  // 协议, 可以是: tcp,udp,all, type为ip时有效
                "dest":"",   // 目的地址, 可以是:
                                      // IP: 202.96.11.32
                                      // 多个IP: 2.3.1.2,4.34.2.1,72.32,192.1
                                      // IP范围: 202.96.132.11-202.96.132.20
                                      // 域名: www.baidu.com
                "destport":"",  // 目的端口，可以是：123;234-456，需proto为tcp或udp且type为ip时有效
                "datestart":"",  // 启始时间，YYYY[-MM[-DD[Thh[:mm[:ss]]]]]
                "datestop":"",   // 结束时间，YYYY[-MM[-DD[Thh[:mm[:ss]]]]]
                "timestart":"",  // 每天开始时间: 在启始时间与结束时间内, 每天生效的开始时间，hh:mm[:ss], 例如，11:22:33
                "timestop":"",   // 每天结束时间: 在启始时间与结束时间内, 每天生效的结束时间，11:22:33；若指定了开始时间，没指定结束时间，则结束时间为23:59:59
                "weekdays":"1,2" // 每周的星期号: 在启始时间与结束时间内, 生效的星期号, 0-6表示星期日、一、二、三、四、五、六, 可同时多个以逗号间隔
            },
            "rule2":      // 典型所IP及端口访问规则
            {
                "action":"drop",        // drop为丢弃
                "type":"ip",            // type为IP
                "dest": "202.22.12.40", // 指定IP
                "proto": "tcp",         // 协议, 只有为tcp或udp时destport才有效
                "destport":"800"        // 目的端口, 需proto为tcp或udp且type为ip时有效
            },
            "rule3":      // 典型的IP访问规则
            {
                "action":"drop",        // drop为丢弃, accept为接受
                "type":"ip",            // type为ip表示限制IP
                "dest": "192.168.22.3"  // 指定IP, 如为空为无此结点表示所有IP
            },
            "rule4":      // 典型的DNS访问规则
            {
                "action":"drop",        // drop为丢弃
                "type":"dns",           // type为DNS
                "dest": "www.qq.com"    // 指定DNS
            },
            "rule5":      // 曲型的APP应用访问规则
            {
                "action":"drop",    // drop为丢弃, accept为接受
                "type":"app",       // type为app表示为某些应用(以后扩展用)
                "dest": "qq"        // 指定策略
            },
            //...更多规则
        },

        // 互联网访问速率控制相关, 出口带宽, 设置了出口带宽后终端相关的流量控制才生效
        "tc_set":
        {
            "unit":"mbit",                  // 流量单位
            "uprate":"",                    // 上行速率, 单位为 mbit
            "downrate":""                   // 下行速率, 单位为 mbit
        }
    }
}
```



