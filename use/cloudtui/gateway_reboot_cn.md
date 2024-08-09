

# 终端命令行重启网关

### 1. 登录到Ubuntu云管理的终端命令行    
- 通过SSH或其它终端工具登陆到Ubuntu   
- 执行sline进入SkinOS的终端命令行   
    ```
    ubuntu@VM-0-8-ubuntu:~$ sline
    $
    ```   

### 2. 交互HE指令重启指定的网关   
重启macid为00037F120910的网关   
```shell
$ hport.he[ 00037F120910, land@machine.restart[3] ]
ttrue
$
```    

### 3. 交互JSON指令重启指定的网关   
重启macid为00037F120910的网关   
```shell
$ hport.talk[ 00037F120910, { "cmd":{ "com":"land@machine", "op":"restart", "1":"3" } } ]
ttrue
$
```    


**更多介绍说明见 [API接口-管理网关](../../com/devms/api_device.md)**   



# 使用HTTP(JSON)协议重启网关

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

### 2. 与网关交互HE指令   
提交的JSON如下   
```json
{
    "user":"ashyelf",
    "macid":"88124E202B30",
    "key":"87eee84bce24ed9eb3d9557ded972ae0",
    "he":"land@machine.restart[3]"      // JSON模式下此行则是 "he":{ "com":"land@machine", "op":"restart", "1":"3" }
}
```   
命令行操作   
```
ubuntu@VM-0-8-ubuntu:~$ curl -XPOST http://127.0.0.1:10002/he -d'{"user":"ashyelf","macid":"88124E202B30","key":"87eee84bce24ed9eb3d9557ded972ae0","he":"land@machine.restart[3]"}'
{"he":"ttrue"}
ubuntu@VM-0-8-ubuntu:~$
```


