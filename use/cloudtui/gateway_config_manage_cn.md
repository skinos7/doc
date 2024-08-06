
# 远程实时管理网关配置   
远程实时管理网关需要网关接入云管理, 如果网关不在线则无法管理   



## 终端命令行管理   
终端命令行远程管理网关通过与网关交互 **HE指令** 或是 **JSON指令** 来实现
- **HE指令**, 简单方便, 一次只能一个操作, 如果指令中包含有特殊字符可能无法远程传递, 这些指令可以也可以在网关本地的终端管理命令行中直接执行   
- **JSON指令**, 相对HE指令更复杂, 可以一次交互多个操作, 并且使用一些特殊字符时只有JSON指令才能支持   

### 与网关交互HE指令   
指令格式: **hport.he[ 网关macid, HE指令 ]**   
以下示例与macid为00037F120910的网关远程交互 **HE指令** 

- 查询网关的配置, 示例查询网关基本配置, 即查询网关组件 **land@machine** 的配置   
    ```shell
    $ hport.he[ 00037F120910, land@machine ]
    {
        "mode":"gateway",
        "name":"LTE&NR-Gateway",
        "broken":"disable",
        "mac":"00:03:7F:12:09:10",
        "macid":"00037F120910",
        "language":"cn",
        "version":"v7.4.0710",
        "cfgversion":"20240585"
    }
    $
    ```   
- 修改网关配置, 示例修改网关的名称为MyGateway   
    ```shell
    $ hport.he[ 00037F120910, land@machine:name=MyGateway ]
    ttrue
    $
    ```  
- 调用网关接口, 示例获取网关基本状态, 即调用组件 **land@machine** 的 **status** 接口    
    ```shell
    $ hport.he[ 00037F120910, land@machine.status ]
    {
        "mode":"gateway",
        "name":"MyGateway",
        "broken":"disable",
        "platform":"smtk2",
        "hardware":"mt7621",
        "custom":"d228",
        "scope":"std",
        "version":"v7.4.0710",
        "livetime":"18:19:20:1",
        "current":"19:58:16:08:06:2024",
        "mac":"00:03:7F:12:09:10",
        "macid":"00037F120910",
        "model":"5228",
        "magic":"0D8339C20232FFFF",
        "cfgversion":"20240587",
        "wui_port":"8888",
        "telnet_port":"2323",
        "ssh_port":"22",
        "local_ip":"192.168.31.254"
    }
    $
    ```  
更多的HE指令参见网关的 **[终端管理命令行使用介绍](../tui_use_cn.md)**   
此文档中介绍的管理用的 **HE指令** 都可以通过上面的方式来远程让网关执行, 从而实现远程管理   
更多hport命令介绍说明见 **[实时管理](../..//com/devms/heport.md)**

### 与网关交互JSON指令   
指令格式: **hport.talk[ 网关macid, {JSON指令} ]**   
以下示例与macid为00037F120910的网关远程交互 **JSON指令** 

- 查询网关的配置, 示例查询网关基本配置, 即查询网关组件 **land@machine** 的配置   
    ```shell
    $ hport.talk[ 00037F120910, {"cmd":"land@machine"} ]
    {
        "cmd":
        {
            "mode":"gateway",
            "name":"LTE&NR-Gateway",
            "broken":"disable",
            "mac":"00:03:7F:12:09:10",
            "macid":"00037F120910",
            "language":"cn",
            "version":"v7.4.0710",
            "cfgversion":"20240585"
        }
    }
    $
    ```   
- 修改网关配置, 示例修改网关的名称为MyGateway   
    ```shell
    $ hport.talk[ 00037F120910, {"cmd":{ "com":"land@machine", "op":"=", "ab":"name", "v":"MyGateway" }} ]
    {
        "cmd":"ttrue"
    }
    $
    ```  
- 调用网关接口, 示例获取网关基本状态, 即调用组件 **land@machine** 的 **status** 接口    
    ```shell
    $ hport.talk[ 00037F120910, {"cmd":{ "com":"land@machine", "op":"status" }} ]
    {
        "cmd":
        {
            "mode":"gateway",
            "name":"MyGateway",
            "broken":"disable",
            "platform":"smtk2",
            "hardware":"mt7621",
            "custom":"d228",
            "scope":"std",
            "version":"v7.4.0710",
            "livetime":"18:19:20:1",
            "current":"19:58:16:08:06:2024",
            "mac":"00:03:7F:12:09:10",
            "macid":"00037F120910",
            "model":"5228",
            "magic":"0D8339C20232FFFF",
            "cfgversion":"20240587",
            "wui_port":"8888",
            "telnet_port":"2323",
            "ssh_port":"22",
            "local_ip":"192.168.31.254"
        }
    }
    $
    ```  
更多的JSON指令参见网关的 **[本地被管理协议说明](../../protocol/localport/localport_protocol_cn.md)** 中介绍的 **JSON指令格式**, 所有的HE指令都可以用JSON指令格式来封装   
更多hport命令介绍说明见 **[实时管理](../..//com/devms/heport.md)**



## 使用HTTP(JSON)协议管理   
通过HTTP(JSON)协议也可以交互 **HE指令** 或 **JSON指令**   
实现方式即通过向云管理指定的端口POST一个JSON, JSON中有网关macid及实时操作key即可远程让网关执行JSON指令   
因为通过此协议管理网关需要先知道网关的 **实时操作key**   

### 1. 首先通过heport接口获取设备实时操作key   
每个设备上线后会随机生成一个对应的 **实时操作key**   
调用 **devms@api** 组件的 **device_view** 接口获取设备基本信息, 其中名为"key"的属性值为 **实时操作key**   
如果设备不在线则返回的JSON中无"key"属性   
如果云平台没有设备记录则返回空   
- 命令行示例, 获取云平台上设备的基本信息, 需要给出设备 **所属的用户**(ashyelf), 及 **设备macid**(88124E202B30)   
    ```shell
    ubuntu@VM-0-8-ubuntu:~$ he devapi.device_view[ashyelf,88124E202B30]
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

### 2. 然后使用实时操作key发送HE指令管理网关   
通过向127.0.0.1的10002的端口的/he界面POST一个JSON来向云平台提交要操作的设备及he指令   
方法: POST   
URL: http://127.0.0.1:10002/he   
内容:   
```json
{
    "user":"用户名",        // [ string ]
    "macid":"设备macid",    // [ string ]
    "key":"设备实时操作key", // [ string ]
    "he":"HE指令",          // [ string ]   
    "he2":"HE指令2",        // [ string ], 可选多条指令
    "he3":"HE指令3",        // [ string ], 可选多条指令
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

### 3. 也可以使用实时操作key发送JSON模式的指令管理网关   
通过向127.0.0.1的10002的端口的/he界面POST一个JSON来向云平台提交要操作的设备及he指令   
方法: POST   
URL: http://127.0.0.1:10002/he   
内容:   
```json
{
    "user":"用户名",        // [ string ]
    "macid":"设备macid",    // [ string ]
    "key":"设备实时操作key", // [ string ]
    "he":{},               // [ json ], JSON模式  
    "he2":{},              // [ json ], JSON模式, 可选多条指令  
    "he3":{},              // [ json ], JSON模式, 可选多条指令  
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

### 4. 示例与网关交互HE指令   

#### 示例查询ashyelf用户下设备88124E202B30的基本配置   
提交的JSON如下   
```json
{
    "user":"ashyelf",
    "macid":"88124E202B30",
    "key":"87eee84bce24ed9eb3d9557ded972ae0",
    "he":"land@machine"      // JSON模式下此行则是 "he":{ "com":"land@machine" }
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

#### 示例查询ashyelf用户下设备88124E202B30的LTE配置   
提交的JSON如下   
```json
{
    "user":"ashyelf",
    "macid":"88124E202B30",
    "key":"87eee84bce24ed9eb3d9557ded972ae0",
    "he":"ifname@lte"      // JSON模式下此行则是 "he":{ "com":"ifname@lte" }
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

#### 示例查看ashyelf用户下设备88124E202B30的互联网的状态

提交的JSON如下
```json
{
    "user":"ashyelf",
    "macid":"88124E202B30",
    "key":"cc4c905605566092f29f8064e6e6c996",
    "he":"network@frame.default"      // JSON模式下此行则是 "he":{ "com":"network@frame", "op":"default" }
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

#### 示例查询ashyelf用户下设备88124E202B30的2.4G SSID名称   
提交的JSON如下   
```json
{
    "user":"ashyelf",
    "macid":"88124E202B30",
    "key":"cc4c905605566092f29f8064e6e6c996",
    "he":"wifi@nssid:ssid"      // JSON模式下此行则是 "he":{ "com":"wifi@nssid", "ab":"ssid" }
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

#### 示例修改ashyelf用户下设备88124E202B30的2.4G SSID名称为MyTEST   
提交的JSON如下   
```json
{
    "user":"ashyelf",
    "macid":"88124E202B30",
    "key":"cc4c905605566092f29f8064e6e6c996",
    "he":"wifi@nssid:ssid=MyTEST"      // JSON模式下此行则是 "he":{ "com":"wifi@nssid", "ab":"ssid", "op":"=", "v":"MyTEST" }
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





