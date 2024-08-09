

# 远程访问网关的终端命令行

### 1. 登录到Ubuntu云管理的终端命令行    
- 通过SSH或其它终端工具登陆到Ubuntu   
- 执行sline进入SkinOS的终端命令行   
    ```
    ubuntu@VM-0-8-ubuntu:~$ sline
    $
    ```   

### 2. 获取网关的本地地址及Telnet的端口    
示例获取用户ashyelf下macid为88124E202B30网关的基本信息
```shell
$ devapi.device_view[ashyelf,88124E202B30]
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
返回的信息中 **local_ip** 为网关的本地地址, **telnet_port** 为telnet的端口, 示例中网关的IP为192.168.8.1, 端口为23

### 3. 将网关telnet的端口映射到云管理   
将网关网页telnet端口映射到云管理, 接以上示例中网关的IP为192.168.8.1, 端口为23   
```shell
$ devapi.port_map[ ashyelf, 88124E202B30, 192.168.8.1, 23 ]
{
    "port":"10084",
    "macid":"88124E202B30",
    "hand_ip":"192.168.8.1",
    "hand_port":"23"
}
```
返回信息中的 **port** 即是映射到云管理的端口, 示例中映射后的端口为10084   

### 4. 使用telnet客户端访问云管理对应的端口   
接以上示例使用telnet客户端访问云管理的10084即访问网关的telnet服务器, 登录后即可进入终端命令行   
**注意: 此映射如在300秒内无访问则会自动失败**


**网关管理的更多介绍说明见 [API接口-管理网关](../../com/devms/api_device.md)**   
**内网穿透接口更多介绍说明见 [API接口-内网穿透](../../com/devms/api_map.md)**   
