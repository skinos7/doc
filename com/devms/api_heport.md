---
title: "http API for heport"
author: dimmalex@gmail.com
date: March 22, 2024
output:
    word_document:
        path: D:/tmp/api_heport_http.docx
---



## 使用HTTP(JSON)协议实时操作网关

#### 1. 通过heport接口获取设备实时操作key

每个设备上线后会随机生成一个对应的 **实时操作key**
调用 **devms@api** 组件的 **device_view** 接口获取设备基本信息, 其中名为"key"的属性值为 **实时操作key**
如果设备不在线则返回的JSON中无"key"属性
如果云平台没有设备记录则返回空

- 命令行示例, 获取云平台上设备的基本信息, 需要给出设备 **所属的用户**(ashyelf), 及 **设备macid**(88124E202B30)
```shell
ubuntu@VM-0-8-ubuntu:~$ he devms@api.device_view[ashyelf,88124E202B30]
{
    "mode":"gateway",
    "name":"V520-202B30",
    "platform":"smtk2",
    "hardware":"mt7621",
    "custom":"v520",
    "scope":"std",
    "version":"v7.4.0510",
    "livetime":"07:35:36:1",
    "current":"11:09:41:05:24:2024",
    "mac":"88:12:4E:20:2B:30",
    "macid":"88124E202B30",
    "model":"V520",
    "oem":"31232",
    "magic":"C3141B2CD2645830",
    "cfgversion":"20240452",
    "wui_port":"80",
    "telnet_port":"23",
    "ssh_port":"22",
    "local_ip":"192.168.100.1",
    "ifname":"ifname@wan",
    "extern_ip":"172.16.4.15",
    "rx_bytes":"1719399693",
    "tx_bytes":"684052224",
    "online":"03:52:18:3",
    "key":"87eee84bce24ed9eb3d9557ded972ae0"   # 实时操作key
}
```

- 命令行示例, 单独获取云平台上设备的 **实时操作key**, 同样需要给出设备 **所属的用户**, 及 **设备macid**
```shell
ubuntu@VM-0-8-ubuntu:~$ he devms@api.device_view[ashyelf,88124E202B30]:key
87eee84bce24ed9eb3d9557ded972ae0
ubuntu@VM-0-8-ubuntu:~$
```

通过 **devms@api** 组件的接口可以实现对云平台指令帐号下的很多操作, 包括对设备的增删改查, 更多接口见 **[device management API](./api_device.md)**  


#### 2. 使用实时操作key发送he指令操作网关

通过向127.0.0.1的10002的端口的/he界面POST一个JSON来向云平台提交要操作的设备及he指令

方法: POST 
URL: http://127.0.0.1:10002/he 
内容:
```json
{
    "user":"用户名",        // [ string ]
    "macid":"设备macid",    // [ string ]
    "key":"设备实时操作key", // [ string ]
    "he":"HE指令",          // [ string or json ]
    "he2":"HE指令2",        // [ string or json ], 可选多条指令
    "he3":"HE指令3",        // [ string or json ], 可选多条指令
    // ... more he command
}
```
操作成功将返回一个JSON, 内容如下:
```json
{
    "he": { /* HE指令返回 */ }
    "he2": { /* HE指令返回 */ }
    "he3": { /* HE指令返回 */ }
    // ... more he command    
    
}
```

#### 3. 示例

##### 示例查询ashyelf用户下设备88124E202B30的基本配置
提交的JSON如下
```json
{
    "user":"ashyelf",
    "macid":"88124E202B30",
    "key":"87eee84bce24ed9eb3d9557ded972ae0",
    "he":"land@machine"
}
```
命令行操作
```
ubuntu@VM-0-8-ubuntu:~$ curl -XPOST http://127.0.0.1:10002/he -d'{"user":"ashyelf","macid":"88124E202B30","key":"87eee84bce24ed9eb3d9557ded972ae0","he":"land@machine"}'
{"he":{"mode":"gateway","name":"V520-202B30","mac":"88:12:4E:20:2B:30","macid":"88124E202B30","language":"cn","version":"v7.4.0510","cfgversion":"20240452"}}
ubuntu@VM-0-8-ubuntu:~$
```
返回的JSON介绍
```json
{
    "he":
    {
        "mode":"gateway",
        "name":"V520-202B30",
        "mac":"88:12:4E:20:2B:30",
        "macid":"88124E202B30",
        "language":"cn",
        "version":"v7.4.0510",
        "cfgversion":"20240452"
    }
}
```

##### 示例查询ashyelf用户下设备88124E202B30的LTE配置

提交的JSON如下
```json
{
    "user":"ashyelf",
    "macid":"88124E202B30",
    "key":"87eee84bce24ed9eb3d9557ded972ae0",
    "he":"ifname@lte"
}
```
命令行操作
```
ubuntu@VM-0-8-ubuntu:~$ curl -XPOST http://127.0.0.1:10002/he -d'{"user":"ashyelf","macid":"88124E202B30","key":"cc4c905605566092f29f8064e6e6c996","he":"ifname@lte"}'
{"he":{"tid":"1","metric":"10","static":{"ip":"","mask":""},"dhcpc":{"static":"disable"},"ppp":{"lcp_echo_interval":"10","lcp_echo_failure":"12","txqueuelen":"1000","pppopt":"debug"},"masq":"enable","keeplive":{"type":"auto","icmp":{"dest":{"test":"8.8.8.8","test2":"114.114.114.114","test3":"223.5.5.5"},"dest-help":"google-114-ali","timeout":"10","failed":"6","interval":"2"},"dns":{"timeout":"8","failed":"6","interval":"2"},"recv":{"timeout":"20","failed":"30","packets":"1"}},"failed_timeout":"45","failed_threshold":"3","failed_threshold2":"15","failed_everytime":"37"}}
ubuntu@VM-0-8-ubuntu:~$
```
返回的JSON介绍
```json
{
    "he":
    {
        "tid":"1",
        "metric":"10",
        "static":
        {
            "ip":"",
            "mask":""
        },
        "dhcpc":
        {
            "static":"disable"
        },
        "ppp":
        {
            "lcp_echo_interval":"10",
            "lcp_echo_failure":"12",
            "txqueuelen":"1000",
            "pppopt":"debug"
        },
        "masq":"enable",
        "keeplive":
        {
            "type":"auto",
            "icmp":
            {
                "dest":
                {
                    "test":"8.8.8.8",
                    "test2":"114.114.114.114",
                    "test3":"223.5.5.5"
                },
                "dest-help":"google-114-ali",
                "timeout":"10",
                "failed":"6",
                "interval":"2"
            },
            "dns":
            {
                "timeout":"8",
                "failed":"6",
                "interval":"2"
            },
            "recv":
            {
                "timeout":"20",
                "failed":"30",
                "packets":"1"
            }
        },
        "failed_timeout":"45",
        "failed_threshold":"3",
        "failed_threshold2":"15",
        "failed_everytime":"37"
    }
}
```


##### 示例查看ashyelf用户下设备88124E202B30的互联网的状态

提交的JSON如下
```json
{
    "user":"ashyelf",
    "macid":"88124E202B30",
    "key":"cc4c905605566092f29f8064e6e6c996",
    "he":"network@frame.default"
}
```
命令行操作
```
curl -XPOST http://127.0.0.1:10002/he -d'{"user":"ashyelf","macid":"88124E202B30","key":"cc4c905605566092f29f8064e6e6c996","he":"network@frame.default"}'
{"he":{"mode":"pppoec","netdev":"ppp0","ifname":"ifname@wan","gw":"0.0.0.0","dns":"120.196.165.24","dns2":"211.136.192.6","ifdev":"vlan@wan","ontime":"41","metric":"10","status":"up","ip":"172.16.110.132","mask":"255.255.255.255","dstip":"172.16.0.1","delay":"14","livetime":"12:09:21:0","rx_bytes":"3804941417","rx_packets":"3323144","tx_bytes":"215223162","tx_packets":"1597183","mac":"88:12:4E:20:2B:36","tid":"3"}}
```
返回的JSON介绍
```json
{
    "he":
    {
        "mode":"pppoec",
        "netdev":"ppp0",
        "ifname":"ifname@wan",
        "gw":"0.0.0.0",
        "dns":"120.196.165.24",
        "dns2":"211.136.192.6",
        "ifdev":"vlan@wan",
        "ontime":"41",
        "metric":"10",
        "status":"up",
        "ip":"172.16.110.132",
        "mask":"255.255.255.255",
        "dstip":"172.16.0.1",
        "delay":"14",
        "livetime":"12:09:21:0",
        "rx_bytes":"3804941417",
        "rx_packets":"3323144",
        "tx_bytes":"215223162",
        "tx_packets":"1597183",
        "mac":"88:12:4E:20:2B:36",
        "tid":"3"
    }
}
```




##### 示例查询ashyelf用户下设备88124E202B30的2.4G SSID名称

提交的JSON如下
```json
{
    "user":"ashyelf",
    "macid":"88124E202B30",
    "key":"cc4c905605566092f29f8064e6e6c996",
    "he":"wifi@nssid:ssid"
}
```
命令行操作
```
ubuntu@VM-0-8-ubuntu:~$ curl -XPOST http://127.0.0.1:10002/he -d'{"user":"ashyelf","macid":"88124E202B30","key":"cc4c905605566092f29f8064e6e6c996","he":"wifi@nssid:ssid"}'
{"he":"V520-202B30"}
ubuntu@VM-0-8-ubuntu:~$
```
返回的JSON介绍
```json
{
    "he":"V520-202B30"
}
```


##### 示例修改ashyelf用户下设备88124E202B30的2.4G SSID名称为MyTEST

提交的JSON如下
```json
{
    "user":"ashyelf",
    "macid":"88124E202B30",
    "key":"cc4c905605566092f29f8064e6e6c996",
    "he":"wifi@nssid:ssid=MyTEST"
}
```
命令行操作
```
ubuntu@VM-0-8-ubuntu:~$ curl -XPOST http://127.0.0.1:10002/he -d'{"user":"ashyelf","macid":"88124E202B30","key":"cc4c905605566092f29f8064e6e6c996","he":"wifi@nssid:ssid=MyTEST"}'
{"he":"ttrue"}
ubuntu@VM-0-8-ubuntu:~$
```
返回的JSON介绍
```json
{
    "he":"ttrue"
}
```



#### 4. 更多操作扩展

对于提交的JSON中的he属性可以是字符串式的HE指令, 其更详细的介绍在 **[he_command.md](https://gitee.com/tiger7/doc/blob/master/use/he_command.md)**

对于提交的JSON中的he属性也可以是JSON的HE指令, 其更详细的介绍在 **[localport_protocol.md](https://gitee.com/tiger7/doc/blob/master/protocol/localport/localport_protocol.md)** 的 **JSON指令格式 --- JSON模式**

通过熟悉了以上的两份有关HE指令的格式后, 即可在 [在线组件文档](https://gitee.com/tiger7/doc/tree/master/com) 查看组件接口文件, 通过HE指令操作组件接口来实现对设备的完全控制