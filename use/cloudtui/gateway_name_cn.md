

# 修改管理云平台上网关的名称

### 1. 登录到Ubuntu云管理的终端命令行    
- 通过SSH或其它终端工具登陆到Ubuntu   
- 执行sline进入SkinOS的终端命令行   
    ```
    ubuntu@VM-0-8-ubuntu:~$ sline
    $
    ```   

### 2. 修改指定网关对应的主机名称   
将ashyelf帐号下macid为00037F120910的网关的名称改为MyGateway   
```shell
$ devapi.device_add[ ashyelf, 00037F120910, MyGateway ]
ttrue
$
```    

**注意: 修改的此主机名称仅存在于云平台上**


**更多介绍说明见 [API接口-管理网关](../../com/devms/api_device.md)**   






