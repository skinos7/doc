***

## 无线连网PPPOE拨号设置

无线连网PPPOE拨号需要以下前提:

- 有PPPOE拨号上网的无线热点, 即ADSL猫(Modem)支持WIFI热点

- 有PPPOE拨号上网的帐号跟密码

![avatar](./wisp_pppoe.jpg) 


#### 1. 切换无线连网模式

- 点击 **红框1** **系统** 菜单下的 **红框2** **设备管理** 进入 **设备管理设置界面**   

- 点击 **红框3** **工作模式** 点选 **2.4G无线连网网关**(或**5.8G无线连网网关**) 后, 提示需要重启点击 **确定** 等待网关重启完成即可   

![avatar](./wisp_mode_cn.png) 

具体切换为 **2.4G无线连网网关** 还是 **5.8G无线连网网关** 取决于要连接的SSID是 **2.4G** 的还是 **5.8G** 的热点    
在 **2.4G无线连网网关**(或**5.8G无线连网网关**) 模式下, 网关的WAN/LAN口及无线都在同一个广播域, 在使用中WAN口与LAN口无区别    


#### 2. 设置无线连网PPPOE拨号

- 将电脑通过有线接入网关来设置网关的无线连网功能( **如通过无线连接网关在设置时会出现电脑与网关的连接断开而影响设置** )    

- 点击 **红框1** **网络** 菜单下的 **红框2** **无线连网(2.4G)**(或**无线连网(5.8G)**) 进入 **无线连网(2.4G)设置界面**(或**无线连网(5.8G)设置界面**)

![avatar](./wisp_pppoe_cn.jpg) 

- 点击 **红框3** 的 **扫描** 后, 弹出当前附近的SSID列表, 点击对应SSID前 **红框A** 的 **选择** 后会将SSID信息自动填入 **红框4** 及 **红框7** 中, 然后用户只需在 **红框7** 中的 **密码** 栏填写密码即可

![avatar](./wisp_pppoe_scan_cn.jpg) 

- 也可直接在 **红框4** 中填入要连接的 **SSID名称** 并在 **红框7** 中填写对应的 **安全模式** **加密模式**及 **密码**, 必须要填写正确否则将无法连接   

- 点击 **红框8** 选择 **PPPOE宽带拨号**

- 在 **红框9** 的 **用户名** 及 **密码** 输入框中填写PPPOE拨号上网的帐号跟密码, 之后点击 **红框10** 应用即可

- 正常等待1分钟右左即可连接成功, 连接成功后在 **红框11** 将显示获取的 **IP地址**   

    - **红框5** 用于填写多个安全方式完全相同的SSID, 网关将连接他们之中的SSID   
    - **红框6** 用于锁定最强信号, 当连接的SSID有多个设备或连接多个SSID时(红框5)时必须点选   
    - **红框B** 用于当热点列表中未显示对应的SSID时可点 **重新扫描** 直到能显示需要连接的SSID   


#### 无线连网的可用性检测介绍

参见 **[4G/5G(LTE/NR)上网的可用性检测介绍](../lte/lte_apn_cn.md#4g5gltenr上网的可用性检测介绍为了ltenr网络的可靠性必须阅读)**



## 无线连网网络的相关信息

#### 查看当前无线连网网络的基本状态

在 **无线连网(2.4G)设置界面**(或**无线连网(5.8G)设置界面**) 的上面首先会显示当前无线连网的基本状态

*通过在 **管理界面** 点击 **网络** 菜单下的 **无线连网(2.4G)**(或**无线连网(5.8G)**) 进入*

![avatar](./wisp_status_cn.jpg) 

- 1为当前的 **网络状态**, 正常网关会在不同的阶段显示如下不同的状态:

    - **正在连接**, 表示正在连接

    - **连接成功**, 表示已成功连接

    - **未连接**, 连接被手动断开或暂时因为网络问题离线, 网关通常间隔一段时间会恢复

- 2为当前连接的 **SSID**

- 3为当前连接的SSID的 **信号强度**

- 4为连接成功后一直连续 **在线时长**, 重新连接时会清零

- 5为当次连接累计的 **收发字节**, 出现重新连接时会清零( MTK方案中此收发字节不统计将始终为0 )

- 6为获取到的 **IP地址**, 连接成功时才会显示

- 7为当前连接的 **BSSID**, 即连接SSID设备的MAC地址

- 8为当前连接的SSID的 **信道**

- 9为当前连接的SSID理论最大 **速率**

- 10为当前的WISP口的 **MAC地址**


### 查看当前无线连网网络的所有状态信息

在 **管理界面** 点击 **接口** 将会显示 **无线连网(2.4G)**(或**无线连网(5.8G)**) 的所有状态信息

![avatar](./wisp_interface_cn.jpg) 

**红框2** 中显示所有 **无线连网(2.4G)**(或**无线连网(5.8G)**) 的信息   