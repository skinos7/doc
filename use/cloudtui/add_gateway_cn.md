

# 将网关接入云管理

## 首先在云管理中添加用户帐号   
- 如果无 **管理员网页界面** 的访问权限则需要与 **云管理** 的管理员申请用户帐号   
- 如果有 **管理员网页界面** 的帐号及密码则可参见 **[用户帐号的添加](./add_user_cn.md)** 来添加用户帐号  

## 然后设置网关接入云管理指定用户帐号   
通过登录网关的 **终端管理命令行** 设置
1. 设置网关要接连接的 **服务器** 及 **用户帐号** , 并启用 **远程HTTP代理**   
```shell
$ set agent@remote            # 要求修改4G网络
{
    ... # 显示当前4G网络的配置
}
agent@remote:                 # 开始修改提示  
agent@remote: server=debug.ashyelf.com           # 修改服务器地址为 debug.ashyelf.com
agent@remote: user=ashyelf                       # 修改用户帐号为 ashyelf
agent@remote: status=enable                      # 启用远程HTTP代理去连接服务器
agent@remote: reslove=enable                     # 要求将服务器地址解析为IP地址使用, 防止网站未备案导致的域名劫持
$ agent@remote: s             # 设置以上所有的修改
ttrue                         # 返回ttrue表示设置成功
$ agent@remote.status         # 等待个十几秒后网关将成功连接后查询HTTP代理的连接状态
{
    "status":"online",               # 表示已在线
    "server":"114.132.219.158"       # 服务器地址的IP地址
}
$ 
```   
- 也可使用 **HE指令** 一次完成以上所有设置   
```shell
$ agent@remote|{"server":"debug.ashyelf.com","user":"ashyelf","status":"enable","reslove":"enable"}
ttrue
```   
2. 设置网关启用 **远程HE代理**   
```shell
$ agent@heclient:status=enable     # 启用远程HE代理去连接服务器
$ agent@heclient.status            # 等待个十几秒后网关将成功连接后查询HE代理的连接状态
{
    "status":"online",               # 表示已在线
    "server":"114.132.219.158"       # 服务器地址的IP地址
}
$ 
```   

**更多参数说明见 [远程HTTP代理](../../com/agent/remote.md), [远程HE代理](../../com/agent/heclient.md)**   


## 登录云管理的命令行查看网关是否已接入   
通过SSH或其它终端工具登陆到Ubuntu, 执行sline进入SkinOS的终端命令行   
```
ubuntu@VM-0-8-ubuntu:~$ sline
$
```   
### 云管理的命令行查看网关列表
```shell
$ devapi.device_listv[ashyelf]
{
    "00037F120910":
    {
        "mode":"gateway",
        "name":"MyGateway",
        "broken":"disable",
        "platform":"smtk2",
        "hardware":"mt7621",
        "custom":"d228",
        "scope":"std",
        "version":"v7.4.0610",
        "livetime":"09:08:08:2",
        "current":"02:04:55:08:04:2024",
        "mac":"00:03:7F:12:09:10",
        "macid":"00037F120910",
        "model":"5228",
        "magic":"0D8339C20232FFFF",
        "cfgversion":"20240585",
        "wui_port":"8888",
        "telnet_port":"2323",
        "ssh_port":"22",
        "local_ip":"192.168.31.254",
        "ifname":"ifname@wan",
        "extern_ip":"111.221.193.120",
        "rx_bytes":"20144422893",
        "tx_bytes":"14270927555",
        "online":"09:51:52:15",
        "key":"9dbf91fcec11dafcf9dc3e2591ad1b74"
    },
    "88124E202B30":
    {
        "mode":"gateway",
        "name":"V520-202B30",
        "platform":"smtk2",
        "hardware":"mt7621",
        "custom":"v520",
        "scope":"std",
        "version":"v7.4.0603",
        "mac":"88:12:4E:20:2B:30",
        "macid":"88124E202B30",
        "model":"V520",
        "oem":"31232",
        "magic":"C3141B2CD2645830",
        "wui_port":"80",
        "telnet_port":"23",
        "ssh_port":"22",
        "local_ip":"192.168.100.1",
        "comment":"陪测"
    }
}
ubuntu@VM-0-8-ubuntu:~$
```

#### 2. 云管理的命令行查看指定网关的状态信息   
```shell
$ devapi.device_status[ashyelf,00037F120910]
{
    "land@machine.status":
    {
        "mode":"gateway",
        "name":"MyGateway",
        "broken":"disable",
        "platform":"smtk2",
        "hardware":"mt7621",
        "custom":"d228",
        "scope":"std",
        "version":"v7.4.0710",
        "livetime":"13:13:38:0",
        "current":"14:52:32:08:05:2024",
        "mac":"00:03:7F:12:09:10",
        "macid":"00037F120910",
        "model":"5228",
        "magic":"0D8339C20232FFFF",
        "cfgversion":"20240585",
        "wui_port":"8888",
        "telnet_port":"2323",
        "ssh_port":"22",
        "local_ip":"192.168.31.254"
    },
    "network@frame.default":
    {
        "mode":"pppoec",
        "netdev":"ppp0",
        "ifname":"ifname@wan",
        "gw":"0.0.0.0",
        "dns":"211.148.192.141",
        "dns2":"211.148.192.151",
        "ifdev":"vlan@wan",
        "ontime":"42",
        "metric":"10",
        "status":"up",
        "ip":"111.221.193.120",
        "mask":"255.255.255.255",
        "dstip":"111.221.192.1",
        "delay":"2",
        "livetime":"13:12:56:0",
        "rx_bytes":"4929145891",
        "rx_packets":"4651827",
        "tx_bytes":"2907057001",
        "tx_packets":"3755215",
        "mac":"00:03:7F:12:09:16",
        "tid":"3"
    },
    "heport":
    {
        "online":"03:26:00:0",
        "fd":"21",
        "addr":"252.127.0.0",
        "port":"35574",
        "user":"ashyelf",
        "key":"14c311b7c9fae373ac7042e5d7d1268c"
    },
    "pport":
    {
        "tcp":"1",
        "udp":"0"
    }
}
$
```   

**更多介绍说明见 [API接口-管理网关](../../com/devms/api_device.md)**   

