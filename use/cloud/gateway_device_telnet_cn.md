


# 远程访问网关下设备的Telnet服务


![avatar](./gateway_device_telnet.jpg)   

###  1. 登录网关管理平台的用户帐号网页界面   

使用IE访问 **网关管理平台**(Ubuntu) 地址的9000端口即可打开对应的登录界面   
![avatar](./ashyelf_login_cn.jpg)   
- 输入刚添加的帐号: ashyelf, 及对应的密码, 点击 **红框4** 即可登录 **用户帐号网页界面**   

### 2. 进入指定网关总览界面

- 在 **网关列表界面** 点击 **红框1** 的 网关列表中对应的 **网关** 后的 **小扳手** 进入指定的 **网关总览界面**   
![avatar](./gwlist_select_cn.jpg)   
 
### 3. 远程访问网关下设备的Telnet服务

- 点击 **网关总览界面** 中的 **红框1** **Telnet** 后弹出对话框
- 在 **红框2** 的对应框中输入要访问的网关下设备的IP及Telnet的端口, 示例中访问网关下 **PLC(192.168.8.254)** 的telnet服务(23端口)   
- 点击 **红框3** 确定, 即会弹出一个网页, 里面是对应的 **PLC(192.168.8.254)** 的telnet服务      
![avatar](./gateway_device_telnetopen_cn.jpg)   

- 以下图 **红框** 即是网关下 **PLC(192.168.8.254)** 的Telnet登陆界面, 登陆后即可通过命令行操作PLC    
![avatar](./gateway_device_telnet_cn.jpg)   

