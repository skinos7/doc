

#### TTL/RS232/RS485串口下使用HE指令查询设备状态

- 通过串口工具连接对应的串口即可进入终端HE指令界面
 *注:串口默认为57600的波特率（8位数据位/1位停止位/无流控/无校检）*

- 进入串口设备启动后首先会显示简介界面, 界面如下：
    ```
                EEEEEEEEE   LL           FFFFFFFFF
                EE          LL           FF
                EE          LL           FF
                EEEEEEEEE   LL           FFFFFFFFF
                EE          LL           FF
                EE          LL           FF
            Ashy   EEEEEEEEE   LLLLLLLLLL   FF

    -----------------------------------------------------------
    Command Help
    -----------------------------------------------------------
    @ ----------------------- List all the component
    <com> ------------------- Show component configure
    <com>. ------------------ List all component interface
    <com>:<config> ---------- Get component configure attribute
    <com>:<config>=<value> -- Set component configure attribute
    -----------------------------------------------------------
    # 
    ```




#### 统一查询LTE的所有信息
1. 发送
```
ifname@lte.status\r
```

2. 收接
```
# ifname@lte.status
{
    "mode":"dhcpc",
    "ifname":"ifname@lte",
    "netdev":"usb1",
    "gw":"10.43.143.21",
    "dns":"120.80.80.80",
    "dns2":"221.5.88.88",
    "ifdev":"modem@lte",
    "ontime":"1235",
    "metric":"10",
    "status":"up",
    "ip":"10.43.143.22",
    "mask":"255.255.255.252",
    "livetime":"00:07:10:0",
    "rx_bytes":"3013",
    "rx_packets":"22",
    "tx_bytes":"2295",
    "tx_packets":"18",
    "mac":"02:50:F4:00:00:00",
    "tid":"1",
    "devcom":"modem@device",
    "name":"Quectel-EC2X",
    "imei":"864337056708978",
    "mversion":"20CEFHLGR06A05M1G",
    "iccid":"89860121801097564807",
    "imsi":"460015356123463",
    "pcid":"463",
    "lac":"7794",
    "ci":"4209288",
    "netera":"4G",
    "rsrp":"-101",
    "nettype":"FDD LTE",
    "rssi":"-70",
    "rsrq":"-11",
    "sinr":"-20",
    "band":"LTE BAND 1",
    "plmn":"46001",
    "csq":"20",
    "signal":"4",
    "operator":"中国联通",
    "operator_advise":
    {
        "name":"中国联通",
        "dial":"*99#",
        "apn":"3gnet"
    },
    "state":"connected"
}
# 
```
###### 以上返回的JSON中：
属性为 **ip** 的值为 **LTE的IP地址**， 如存在，直接显示即可
属性为 **csq** 的值为 **LTE的CSQ信号**， 如存在，直接显示即可
属性为 **rsrp** 的值为 **LTE的RSRP信号**， 如存在，直接显示即可
属性为 **iccid** 的值为 **LTE的ICCID**， 如存在，直接显示即可
属性为 **imei** 的值为 **LTE的IMEI**， 如存在，直接显示即可
属性为 **delay** 的值为 **LTE的线路延迟**， 如存在，直接显示即可， 如不存在此属性表示未开启
属性为 **operator** 的值为 **LTE的运营商(UTF8编码)**， 如存在，直接显示即可

###### 以上JSON及其下的属性会跟据设备的实际情况有如下几个情况
无返回 -- 未正常与设备连接
只回显（即只返回发送的部分） -- 与设备连接正常但设备未正常工作
返回空JSON（ {} ）-- 与设备连接正常但设备未正常工作
返回JSON但无对应的属性节点 -- 与设备连接正常但设备正在搜寻对应的信息
返回JSON但有对应的属性节点但值空 -- 与设备连接正常但设备正在搜寻对应的信息






#### 单独查询LTE信号CSQ
1. 发送
```
ifname@lte.status:csq\r
```

2. 收接
```
# ifname@lte.status:csq
20
# 
```


#### 单独查询LTE信号RSRP
1. 发送
```
ifname@lte.status:rsrp\r
```

2. 收接
```
# ifname@lte.status:rsrp
-104
# 
```


#### 单独查询LTE的IP地址
1. 发送
```
ifname@lte.status:ip\r
```

2. 收接
```
# ifname@lte.status:ip
10.43.143.22
# 
```


#### 单独查询LTE的ICCID
1. 发送
```
ifname@lte.status:iccid\r
```

2. 收接
```
89860121801097564807
# 
```


#### 单独查询LTE的IMEI
1. 发送
```
ifname@lte.status:imei\r
```

2. 收接
```
# ifname@lte.status:imei
864337056708978
# 
```





#### 查询电池状态
1. 发送
```
camera@battery.status\r
```

2. 收接
```
# camera@battery.status
{
    "percent":"20%",
    "charge":"enable"
}
# 
```
###### 以上返回的JSON中：
属性为 **percent** 的值为 **电池电量**， 直接显示即可，如不存在表示正在搜寻对应的信息
属性为 **charge** 的值为 **是否充电**， enable表示充电中，其它或空表示未充电

###### 以上JSON及其下的属性会跟据设备的实际情况有如下几个情况
无返回 -- 未正常与设备连接
只回显（即只返回发送的部分） -- 与设备连接正常但设备未正常工作
返回空JSON（ {} ）-- 与设备连接正常但设备正在搜寻对应的信息
返回JSON但无对应的属性节点 -- 与设备连接正常但设备正在搜寻对应的信息
返回JSON但有对应的属性节点但值空 -- 与设备连接正常但设备正在搜寻对应的信息

