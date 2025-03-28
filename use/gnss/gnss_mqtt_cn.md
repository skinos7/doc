
## 定位功能信号源的设置  

### 定位信号源分类   
网关可以支持两种GPS/北斗的信号源, 跟据网关产品的型号不同有不同的信号源方式, 具体可以询问售前工程师, 以下是两种信号源的介绍   
1. 通过自带GPS/北斗功能的 **LTE/NR模组** 来获取定位信号源
2. 通过串口上外接 **GPS/北斗功能模块** 来获取定位信号源   

**注意: *通过自带GPS/北斗功能的LTE/NR模组来获取定位信号源* 及 *通过串口上外接GPS/北斗功能模块来获取定位信号源* 只能二选一进行设置, 不能两个都设置**   

### 通过自带GPS/北斗功能的LTE/NR模组来获取定位信号源的设置   
一些LTE/NR的4G/5G模组会带有定位功能, 可以向网关吐出定位信号源, 因此当网关产品对应的型号使用了这种模组即可通过它来获得定位信号源   
当确认网关产品对应的模组带有定位功能后通过网关的 **网页管理界面** 设置如下即可打开定位功能   
![avatar](./gnss_from_lte.png)   
- 通过依次点击 **红框1**, **红框2** 进入 **4G网络设置界面**   
    注意有的网关产品有多个LTE/NR的4G/5G模组, 请确认设置的是对应的4G/5G模组, 示例中设置的是第一个4G(LTE)模组   
- 点击 **红框3** 打开模组的 **定位功能**   
- 点击 **红框4** 应用即可   

### 通过串口上外接GPS/北斗功能模块来获取定位信号源的设置   
网关产品支持串口(TTL)时, 也可通过在串口上外接定位模块来获取定位信号源, 使用网关产品的串口连接好对应的定位模块后即可通过以下设置来打开定位功能   
***关于如何将定位模块连接网关产品的串口可询问售前工程师***   
![avatar](./gnss_from_uart.png)   
- 通过依次点击 **红框1**, **红框2** 进入指定的 **串口设置界面**  
    注意网关产品通常会有多个串口, 请确认设置的是定位模块所连接的那个串口, 示例中定位模块是接在第一个串口   
- 点击 **红框3** 打开串口功能   
- 点击 **红框4** 选择串口的模式为GPS定位   
- 点击 **红框5** 选择定位模块的波特率, 大部分定位模块的默认波特率为9600   
- 点击 **红框6** 应用即可  

**注意: *通过自带GPS/北斗功能的LTE/NR模组来获取定位信号源* 及 *通通过串口上外接GPS/北斗功能模块来获取定位信号源* 只能二选一设置, 不能两个都设置**

### 确认是否已定位   
基于以上 **通过自带GPS/北斗功能的LTE/NR模组来获取定位信号源** 或 **通过串口上外接GPS/北斗功能模块来获取定位信号源** 的设置后, 打开以下界面即可查看到定位信息   
![avatar](./gnss_view.png)   
- 通过依次点击 **红框1**, **红框2** 进入指定的 **全球定位设置界面**   
- 点击 **红框3** 打开全球定位功能   
- 点击 **红框4** 应用后等待一到两分钟后即可   
- 当网关识别到定位模块后会在 **红框6** 的UTC后看到 **UTC时间**   
- 当定位模块定位后会在 **红框7** 中看到定位的 **经纬度**, 此时点击 **红框8** 的 **地图预览** 即可在地图上查看定位的位置   
- **红框5** 会显示当前的定位信号源   

#### 常见故障:   
1. **红框5** 显示 **无** 定位信号源, 这种情况通常是没有 *通过自带GPS/北斗功能的LTE/NR模组来获取定位信号源* 或 *通过串口上外接GPS/北斗功能模块来获取定位信号源* 来设置定位信号源
2. **红框6** 无显示, 这种情况通常是网关与定位模组的连接有问题, 网关无法正常获取到定位模组的定位信号源
3. **红框5** 正确显示定位信号源并且 **红框6** 显示有日期(日期可能不正确但有显示日期)但无正确的经纬度 都表示网关可以正常获取到定位模块的数据, 只是定位模块无法定位, 此时应检查定位模块的天线是否直对天空或更换可定位的定位模块

## 通过MQTT协议向MQTT服务器定时发送JSON格式的定位信息

1. 在有公网地址的Linux上安装MQTT服务器
```
ubuntu@VM-0-8-ubuntu:~$ sudo apt-get install mosquitto
```
2. 安装MQTT客户端工具用于模拟客户端订阅定位信息
```
ubuntu@VM-0-8-ubuntu:~$ sudo apt-get install mosquitto-clients
```
4. 手动运行MQTT服务器
```
ubuntu@VM-0-8-ubuntu:~$ sudo /etc/init.d/mosquitto stop
Stopping mosquitto (via systemctl): mosquitto.service

ubuntu@VM-0-8-ubuntu:~$ sudo mosquitto -c /etc/mosquitto/mosquitto.conf -v
[4396260.896039]~DLT~1887371~INFO     ~FIFO /tmp/dlt cannot be opened. Retrying later...
```
5. 新开一个命令行订阅网关向MQTT服务器发送的主题(该主题的信息为定位信息)
```
ubuntu@VM-0-8-ubuntu:~$ mosquitto_sub -v -t "gatewayGNNS" -h 222.248.230.163 -p 1883
```
![avatar](./gnss_tcp_mqtt.png) 

- 首先 **红框7** 手动运行MQTT服务器
- 再在 **红框8** 订阅网关向MQTT服务器发送的主题
- 再在依次点击 **红框1**, **红框2** 进入指定的 **全球定位设置界面** 设置通过MQTT协议发布定位信息
- 点击 **红框3** 打开客户端功能
- 在 **红框4** 中选择协议, 此示例为MQTT协议
- 在 **红框4** 中输入MQTT服务器及端口
- 在 **红框5** 中输入发布的主题
- 点击 **红框6** 应用即可
- 然后就可以在 **红框9** 中看到网关发布的定位数据, 此数据为一个JSON格式的数据, 属性介绍如下
```json
{
    "step":"step of location",                  // [ "setup", "search", "located" ]
    "utc":"UTC date",                           // [ string ], format is hour:minute:second:month:day:year
    "lon":"longitude",                          // [ float ], nmea format
    "lat":"latitude",                           // [ float ], nmea format
    "longitude":"longitude",                    // [ float ]
    "latitude":"latitude",                      // [ float ]
    "speed":"speed",                            // [ float ]
    "direction":"direction",
    "declination":"declination",
    "elv":"Either altitude height",             // [ float ], the unit is meter
    "inview":"Number of visible satellites",    // [ number ]
    "inuse":"Number of satellites in use"       // [ nubmer ]     
}
```
*进一步的信息可见 [GNSS NEMA Protocol Management](../../com/gnss/nmea.md) 有关info接口的返回的介绍*
