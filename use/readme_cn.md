
# SkinOS的使用说明   

## 如何登录SkinOS管理界面   

### 通过有线或无线连接网关后打开浏览器    
- 在浏览器地址栏输入 **192.168.8.1** 后回车进入网关的 **登录界面**   
- 输入用户名, 默认的用户名是 **admin**   
- 输入管理密码, 默认的管理密码是 **admin**   
- 点击 **登录** 按键即可进入 **管理界面**   

![avatar](./login_cn.png)    

### 管理界面介绍   

管理界面分为六个区域, 管理界面的菜单分为十几个大类   

![avatar](./admin_cn.png)   

### 菜单简介   

**概要**: 显示网关当前的基本状态, 主要为连接状态及实时流量， 终端数量， 无线名称信道   
**效能**: CPU内存负载   
**接口**: 所有网络接口的详细信息   
**网络**: 常用的网络设置， 如4G/5G网络连网, 有线宽带上网, 无线连网上网，本地网络，路由表，端口映射，防火墙等基本的网络设置   
**VPN**: 虚拟专用网相关的设置   
**无线**: 无线热点的设置   
**终端**: 终端的管理，上网控制，访问控制，流量管理等   
**应用**: 各种应用, 固件中自带的软件或软件仓库中安装软件都将在此菜单项中显示   
**指示**: 用于指示一些信息的应用, 如LED灯, LED屏, 向摄象头叠加OSD等功能等   
**传感**: 传感器  
**系统**: 针对网关的管理配置，如升级，配置管理，密码管理等   
**调试**: 调试或开发需要用到的一些功能   
**定制开发**: 开发中需要用到的相关管理   

### 工作模式简介

针于不同的应用场景网关可提供不同的工作方式，**工作模式** 的配置在 **系统** 菜单下 **设备管理** 中, 网关常用的工作模式如下：   

 ![avatar](./mode_cn.png)   

**4G网关**: 通过3G/4G连接互联网的网关模式   
**4G/5G网关**: 通过4G/5G连接互联网的网关模式   
**4G5G猫**: 提供4G/5G猫的功能, 开机会完成与4G/5G网络连接但不获取IP地址, 需要其它的客户端通过DHCP协议获取4G/5G的IP地址   
**双4G/5G网关**：通过两个4G/5G连接互联网的网关模式, 只有在有两个4G/5G基带的产品上才支持   
**有线网关**：通过有线WAN口连接互联网的网关模式    
**双WAN口网关**：通过两个有线WAN口连接互联网的网关模式   
**2.4G无线连网网关**：通过2.4G无线客户端连接其它WIFI网络的网关模式   
**5.8G无线连网网关**：通过5.8G无线客户端连接其它WIFI网络的网关模式   
**无线热点**：相当于带无线功能的交换机, 此模式下默认不会分配IP地址, 通常用于放置在路由器的下一级   
**混合**：此模式下可使用4G/5G、有线WAN口、无线连网三种模式中组合上网, 实现多种上网方式同时存在并相互备份或负载均衡   

## 常用的功能使用说明   

### 4G/5G联网设置   

- **连接普通的4G(LTE)网络**   

    1. 网关插上SIM卡后   
    2. 将设备的 **工作模式** 设置为 **4G网关**, 4G网关默认即为此模式    
    网关就会自动通过4G(LTE)连上互联网, 不需要任何设置, 将终端设备或电脑通过有线或无线连接网关即可访问互联网   

- **连接普通的5G(NR)网络**   
    1. 网关插上SIM卡后    
    2. 将设备的 **工作模式** 设置为 **4G/5G网关**, 4G网关默认即为此模式     
    网关就会自动通过5G(NR)连上互联网, 不需要任何设置, 将终端设备或电脑通过有线或无线连接网关即可访问互联网   

- **[4G/5G(LTE/NR)接入虚拟专用网络(VPDN/APN)](./lte/lte_apn_cn.md)** 介绍使用LTE/NR接入VPDN/APN网络    
- **[4G/5G(LTE/NR)接入自建基站网络](./lte/lte_spec_cn.md)** 介绍使用LTE/NR接入自建基站网络   
- **[4G/5G(LTE/NR)双SIM卡](./lte/lte_bsim_cn.md)** 介绍LTE/NR双卡的使用   
- **[4G/5G(LTE/NR)短信功能](./lte/lte_sms_cn.md)** 介绍LTE/NR短信的使用   

- ***[4G/5G(LTE/NR)锁定SIM卡](./lte/lte_lock_cn.md)**(编写中)*, 锁SIM卡后换卡无法工作   
- ***[4G/5G(LTE/NR)锁模块](./lte/lte_lock_cn.md)**(编写中)*, 锁定模块后换模块无法工作   
- ***[4G/5G(LTE/NR)自定义指令实现锁频段](./lte/lte_lock_cn.md)**(编写中)*    
- ***[打开4G/5G(LTE/NR)定位功能及使用](./lte/lte_lock_cn.md)**(编写中)*   
- ***[打开4G/5G(LTE/NR)模组的AT指令服务器及使用](./lte/lte_lock_cn.md)**(编写中)*   

### 有线宽带联网设置   
- **[PPPOE拨号联网](./wan/wan_pppoe_cn.md)**    
- **[自动获取(DHCP)联网](./wan/wan_dhcp_cn.md)**   
- **[静态地址联网](./wan/wan_static_cn.md)**   
- **[纯路由模式下有线宽带联网](./wan/wan_nonat_cn.md)**   

### 2.4G/5.8G无线连网设置   
- **[无线连网自动获取(DHCP)使用](./wisp/wisp_dhcp_cn.md)**   
- **[无线连网静态地址使用](./wisp/wisp_static_cn.md)**   
- **[无线连网PPPOE拨号使用](./wisp/wisp_pppoe_cn.md)**    
- **[纯路由模式下无线连网](./wisp/wisp_nonat_cn.md)**   

### 使用4G/5G, 有线宽带, 2.4G/5.8G无线连网多个连接同时联网   
- **[双4G/5G网关模式的使用](./mix-mode/dmisp_cn.md)**, 实现双4G/5G同时联网, 双4G/5G间实现备份或是负载均衡       
- **[双WAN口网关模式的使用](./mix-mode/dgateway.md)**, 实现双WAN口连接同时联网, 双WAN口连接间实现备份或是负载均衡    
- **[混合模式的使用](./mix-mode/mix_cn.md)**, 混合模式下实现多种连接同时联网, 各种连接间实现备份或是负载均衡   

### 2.4G/5.8G无线热点工作模式   
- **[无线热点模式使用](./ap/ap_cn.md)**   
- **[无线热点模式下中继其它热点](./ap/repeater_cn.md)**   

### 4G5G猫(Modem)工作模式   
- **[4G5G猫(Modem)模式使用](./ap/mbridge_cn.md)**   

### 本地网络设置   
- **[本地网络地址设置](./lan/lan_ip_cn.md)**   
- **[本地网络设置多个地址](./lan/lan_mip_cn.md)**   
- **[本地网络分配地址段(DHCP服务器)设置](./lan/dhcps_cn.md)**   
- **[为终端分配指定的IP地址](./client/bind_ip_cn.md)**   

### 系统管理   
- **[修改网关的名称](./system/name_cn.md)**   
- **[重启网关](./system/reboot_cn.md)**   
- **[重置网关配置(恢复出厂设置)](./system/reset_cn.md)**   
- **[管理网关的时间及时区](./system/date_cn.md)**   
- **[开启NTP服务为本地设备授时](./system/ntps_cn.md)**   
- **[网关配置备份及导入](./system/configure_cn.md)**   
- **[网关固件升级](./upgrade/upgrade_cn.md)**   
- **[网关网页强制升级](./upgrade/boot_web_upgrade_cn.md)**   
- **[网关TFTP强制升级](./upgrade/boot_tftp_upgrade_cn.md)**   
- **[管理员密码修改](./system/password_cn.md)**   
- **[设置网关定时重启](./system/restart_cn.md)**   
- **[Telnet服务器](./system/telnetd_cn.md)**   
- **[SSH服务器](./system/sshd_cn.md)**   
- **[FTP服务器](./system/ftps_cn.md)**   
- **[WEB服务器(管理界面)](./system/webs_cn.md)**   
- **[LED指示灯管理](./system/led_cn.md)**   
- ***[Hosts文件配置](./hosts/hosts.md)**(编写中)*      
- ***[锁定网关配置](./hosts/hosts.md)**(编写中)*, 锁定配置后不再允许用户修改网关配置       
- ***[锁定升级](./hosts/hosts.md)**(编写中)*, 锁定升级后不再允许用户升级网关              
- ***[锁定重启](./hosts/hosts.md)**(编写中)*, 锁定重启后不再允许用户重启网关     

### 无线热点   
- **[无线热点名称及密码信道等设置](./wifi/ssid_cn.md)**   
- **[无线热点黑白名单设置](./wifi/acl_cn.md)**   
- **[中继其它热点](./wifi/sta_cn.md)**   

### 防火墙   
- ***[允许外网访问路由器指定的服务](./firewall/allow_access.md)***   

### 端口映射或代理   
- ***[端口映射使用说明](./portmap/portmap.md)***   
- ***[端口代理使用说明](./portproxy/portproxy.md)***

### 终端管理   
- ***[限制所有的终端访问权限](./client/acl.md)**(编写中)*      
- ***[限制指定的终端访问权限](./client/client_acl.md)**(编写中)*      
- ***[上网白名单设置](./client/black.md)**(编写中)*      
- ***[上网黑名单设置](./client/white.md)**(编写中)*      
- ***[为所有的终端设置上网权限](./client/internet.md)**(编写中)*      
- ***[为指定的终端设置上网权限](./client/client_internet.md)**(编写中)*      
- ***[让访问权限或上网权限定时生效](./client/internet.md)**(编写中)*      

### 路由功能   
- ***[路由表管理](./route/route.md)**(编写中)*      
- ***[基于源地址的路由设置](./route/src_route.md)**(编写中)*      
- ***[基于端口的路由设置](./route/port_route.md)**(编写中)*      

### 调试功能   
- **[抓包使用说明](./debug/tcpdump_cn.md)**   
- ***[日志的使用](./hosts/hosts.md)**(编写中)*, 可调整日志存放位置, 记录等级, 保存大小, 远程日志等      
- ***[ping连通性测试](./debug/tcpdump_cn.md)**(编写中)*   
- ***[iperf打流带宽测试](./debug/tcpdump_cn.md)**(编写中)*      


## VPN功能使用   
- **[设置两台网关Wireguard实现互通示例](./sdwan/wireguard_cn.md)**   
- ***[L2TP客户端的使用](./sdwan/wireguard.md)**(编写中)*   
- ***[PPTP客户端的使用](./sdwan/wireguard.md)**(编写中)*   
- ***[GRE隧道的使用](./sdwan/wireguard.md)**(编写中)*   
- ***[OpenVPN客户端的使用](./sdwan/wireguard.md)**(编写中)*   
- ***[IPSEC的使用](./sdwan/wireguard.md)**(编写中)*   


## 串口功能使用   
- ***[串口透传的使用](./lte/lte_apn_setup.md)**(编写中)*   
- ***[串口MQTT透传](./lte/lte_apn_setup.md)**(编写中)*   
- ***[串口Modbus透传](./lte/lte_apn_setup.md)**(编写中)*   
- ***[串口HTTP透传](./lte/lte_apn_setup.md)**(编写中)*   
- ***[串口终端命令行模式](./lte/lte_apn_setup.md)**(编写中)*, 此模式下可实现通过串口控制并管理网关   
- ***[串口外接GPS/BD模块](./lte/lte_apn_setup.md)**(编写中)*, 此模式下让外接的GPS/BD模块提示定位数据源   
- ***[本地设备获取串口数据](./lte/lte_apn_setup.md)**(编写中)*   


## 串口外接Modbus传感器   
- ***[串口Modbus主控模式下外接各种传感器](./lte/lte_apn_setup.md)**(编写中)*   
- ***[传感器信息HTTP上报](./lte/lte_apn_setup.md)**(编写中)*   
- ***[本地设备获取感器信息](./lte/lte_apn_setup.md)**(编写中)*   


## IO功能使用   
- ***[通过TCP/UDP协议远程控制IO](./lte/lte_apn_setup.md)**(编写中)*   
- ***[通过MQTT协议远程控制IO](./lte/lte_apn_setup.md)**(编写中)*   
- ***[通过短信(SMS)远程控制IO](./lte/lte_apn_setup.md)**(编写中)*   
- ***[本地设备控制IO](./lte/lte_apn_setup.md)**(编写中)*   


## 定位功能使用   
- ***[全球定位的使用](./lte/lte_apn_setup.md)**(编写中)*   
- ***[GPS/BD定位数据(NMEA)TCP/UDP协议上报](./lte/lte_apn_setup.md)**(编写中)*   
- ***[GPS/BD定位信息MQTT协议上报](./lte/lte_apn_setup.md)**(编写中)*   
- ***[GPS/BD定位信息HTTP协议上报](./lte/lte_apn_setup.md)**(编写中)*   
- ***[GPS/BD定位信息JT/T808协议上报](./lte/lte_apn_setup.md)**(编写中)*   
- ***[本地设备获取GPS/BD定位信息](./lte/lte_apn_setup.md)**(编写中)*   


## I2C功能的使用   
- ***[外接I2C显示屏](./lte/lte_apn_setup.md)**(编写中)*   
- ***[外接I2C电量板实现读取电量信息](./lte/lte_apn_setup.md)**(编写中)*   
- ***[I2C电量板的电量信息HTTP协议上报](./lte/lte_apn_setup.md)**(编写中)*    
- ***[本地设备获取I2C电量板的电量信息](./lte/lte_apn_setup.md)**(编写中)*  


## 高级应用    
- ***[本地控制网关](./lte/lte_apn_setup.md)**(编写中)*   
- ***[网关通过HTTP上报状态](./lte/lte_apn_setup.md)**(编写中)*   
- ***[通过短信控制网关](./lte/lte_apn_setup.md)**(编写中)*   
- ***[SNMP的使用及自定义OID](./lte/lte_apn_setup.md)**(编写中)*   
- ***[动态路由协议使用](./lte/lte_apn_setup.md)**(编写中)*   
- ***[高可用性(VRRP)的使用](./lte/lte_apn_setup.md)**(编写中)*   


## 配合摄象头的使用   
- **[将摄象头接入虚拟专用网络(VPDN/APN)的快速设置](./lte/lte_apn_ipc_cn.md)**   
- ***[通过OSD叠加网关信息到摄象机视频中](./lte/lte_apn_setup.md)**(编写中)*, 可实现将网络信息, 定位信息, 电池电量, 传感器信息叠加到摄象机视频中   
- ***[让报象机通过GB28218协议上报网关的定位数据](./lte/lte_apn_setup.md)**(编写中)*   


**(编写中)的功能都已实现, 使用文档暂未上传, 如有需要可资询技术人员上传**