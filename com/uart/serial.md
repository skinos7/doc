***
## UART management components
Manage UART. Usually uart@serial is the first UART. If there are multiple UART in the system, uart@serial2 will be the second UART, and increase by degress
**UART application components**: UART implementation manager, uart@nmea, uart@dtu, uart@hetui, uart@modbus, specified by "con" in configuration 
**UART device component**: Provides UART information for UART application components, such as modem@lte and modem@lte2, "dev" is specified in the configuration 
**UART Data conversion component**: The UART application component calls the interface of the component for protocol conversion when the UART operator is connected to the data of the peer end. The component must provide the specified interface as required 

#### **configuration( uart@serial )**
**uart@serial** is first UART
**uart@serial2** is second UART

```json
// Attribute introduction
{
    // UART configure
    "status":"UART status",                                      // [ enable, disable ]
    "convert":"Whether to enable hardware function conversion",  // [ disable, enable ] 
    "concom":"UART application components",                         // [ uart@dtu, uart@nmea, uart@hetui, uart@modbus ]
                                                                        // uart@dtu is DTU mode
                                                                        // uart@nmea is GPS mode
                                                                        // uart@hetui is He command mode
                                                                        // uart@modbus is ModBus
    "dev":"UART device component",                               // [ string ], modem@lte is LTE modem component
    "ttydev":"UART device pathname",                             // [ string ], Specify the serial device file directly

    // serial configure
    "speed":"Baud rate",            // [ 9600, 19200, 38400, 57600, 76800, 115200, 230400 ]
    "flow":"flow control",          // [ disable, hard, soft ], disable is disable, hard is hardware flow control, soft is software flow control
    "parity":"parity type",         // [ disable, even, odd ]
    "databit":"data bit",           // [ 5, 6, 7, 8 ]
    "stopbit":"stop bit",           // [ 1, 2 ]

    // This function is used to periodically send data to the serial port to activate the mechanism. After this function is enabled, data is periodically sent to the serial port. This function is valid in DTU mode
    "active":"active packet send to serial",                       // [ disable, enable, idle, timing ], disable for disable, enable for active once, idle for idle Specifies the time to send, timing for interval specifies the time to send
    "active_interval":"Activate packet sending interval",          // [ number ], the unit is second, vaild when "active" is idle or timing
    "active_string":"Contents of activation package",           // [ Hex data ], such as 414243 when sending ABC

    // Serial port reading parameter
    "frame_maxsize":"frame max size",                         // [ number ], frame byte
    "frame_interval":"frame interval",                        // [ number ], the unit is ms

    // Modbus configure vaild when concom is uart@modbus
    "modbus":
    {
        "port":"modbus port",
        "maxconn":"Maximum number of simultaneous connections",
        "timeout":"Connection timeout",                           // the unit is ms
        "retries":"retres times",
        "pause":"The interval between requests",                  // the unit is ms
        "wait":"Time to wait for a response"                      // the unit is ms
    },
 
    "dtu":
    {
        "client":
        {
            "status":"client status",               // [ disable, enable ]
            "proto":"client protocol",              // [ tcp, udp, mqtt ]
            "server":"server address",              // [ string ]
            "port":"server port",                   // [ number ]

            "login":"register packet",                // [ disable, hex, ascii, mac ]
                                                            // disable for disable register packet
                                                            // hex for hex string
                                                            // ascii for ascii string
                                                            // mac for hex device mac
            "login_string":"register packet context", // [ string ], such as 414243 when sending ABC when "login" is hex

            // 用于向网络端（客户端或服务器）定时发送数据来保持网络连接的机制， 开启后将定时向其它的网络端定时发送数据
            "keeplive":"disable",            //<保活包> 分为disable(禁用), idle(空闲时发送), timing(定时发送)
            "keeplive_interval":"30",        // <保活包发送间隔> 以秒为单位
            "keeplive_string":"",            // <保活包内容>  十六进制的数据, 如发送ABC时填写414243

            "frame_start":"disable|hex|ascii|mac",     // <包前缀> 分为disable(禁用), hex为十六制, ascii为字符式, mac使用十六制进的mac地址为包后缀
            "frame_start_string":"",  //  <包前缀内容>  十六进制的数据, 如发送ABC时填写414243 , 为<包前缀>为enable时必填
            "frame_end":"disable|hex|ascii|mac", //  <包后缀> 分为disable(禁用), hex为十六制, ascii为字符式, mac使用十六制进的mac地址为包后缀
            "frame_end_string":"",    // <包后缀内容>  十六进制的数据, 如发送ABC时填写414243 , 为<包后缀>为enable时必填

            "mqtt_id":"设备ID号",
            "mqtt_username":"管理帐号",
            "mqtt_password":"密码",
            "mqtt_interval":"mqtt interval",
            "mqtt_keepalive":"mqtt keepalive",
            "mqtt_publish":"mqtt publish topic",
            "mqtt_publish_qos":"mqtt publish qos",
            "mqtt_subscribe":
            {
                "subscribe topic":"topic qos",
                "subscribe topic2":"topic2 qos",
                "subscribe topic3":"topic3 qos",
                // "subscribe topic":"topic qos"     How many subscribe topic need setting save how many properties
            }

        },
        "server":
        {
            "status":"disable",
            "proto":"tcp",
            "port":"",
            "limit":"",

            "login":"register packet",                // [ disable, hex, ascii, mac ]
                                                            // disable for disable register packet
                                                            // hex for hex string
                                                            // ascii for ascii string
                                                            // mac for hex device mac
            "login_string":"register packet context", // [ string ], such as 414243 when sending ABC when "login" is hex

            // 用于向网络端（客户端或服务器）定时发送数据来保持网络连接的机制， 开启后将定时向其它的网络端定时发送数据
            "keeplive":"disable",            //<保活包> 分为disable(禁用), idle(空闲时发送), timing(定时发送)
            "keeplive_interval":"30",        // <保活包发送间隔> 以秒为单位
            "keeplive_string":"",         // <保活包内容>  十六进制的数据, 如发送ABC时填写414243

            "frame_start":"disable|hex|ascii|mac",     // <包前缀> 分为disable(禁用), hex为十六制, ascii为字符式, mac使用十六制进的mac地址为包后缀
            "frame_start_string":"",  //  <包前缀内容>  十六进制的数据, 如发送ABC时填写414243 , 为<包前缀>为enable时必填
            "frame_end":"disable|hex|ascii|mac", //  <包后缀> 分为disable(禁用), hex为十六制, ascii为字符式, mac使用十六制进的mac地址为包后缀
            "frame_end_string":"",    // <包后缀内容>  十六进制的数据, 如发送ABC时填写414243 , 为<包后缀>为enable时必填
        }
    }


}

```





#### **配置** 
```json
// 属性介绍
{
    // 所有模式下的串口通用设置
    "status":"串口状态",        // 串口的状态, disable为禁用, enable为启用
    "convert":"是否转换功能",    // 通常disable表示TTL模式, 其它为原来的硬件功能模式
    "con":"串口应用组件",       // uart@dtu为DTU, uart@gnss为GPS, uart@hetui为终端命令行, uart@modbus为ModBus协议, uart@mqtt为MQTT协议
    "dev":"串口设备组件",       // 串口应用组件将要通过调用其接口获到实际的串口信息
    "tty":"串口设备文件",       // 当是直接的串口时, 可以在此直接给出串口文件路径, 如/dev/ttyS0表示第一个串口
    "uart":                         // 串口设置
    {
        "speed":"波特率",            // 分9600, 19200, 38400, 57600, 76800, 115200, 230400
        "flow":"流控",               // 值为disable表示禁用, hard表示硬流控, soft表示软流控
        "parity":"校验",             // 值为disable表示禁用, even表示偶校验, odd表示奇校验
        "databit":"数据位",          // 分为5, 6, 7, 8
        "stopbit":"停止位",          // 分为1, 2
        //用于向串口（下位机）定时发送数据来激活下位机的机制， 开启后将定时向串口定时发送数据, 在MQTT及DTU模式下有效
        "active":"disable",      //<激活包> 分为disable(禁用), idle(空闲时发送), timing(定时发送),
        "active_interval":"30",  // <激活包发送间隔> 以秒为单位
        "active_hexstring":""   // <激活包内容>  十六进制的数据, 如发送ABC时填写414243
    },



    // MODBUS模式下的设置
    "modbus":                      // ModBus相关的设置, con为uart@modbus有效
    {
        "port":"端口",
        "maxconn":"最大同时连接数",
        "timeout":"连接超时时间",    // 秒为单位
        "retries":"重试次数",
        "pause":"两个请求间的间隔",  // 毫秒为单位
        "wait":"等待回复的时间"      // 毫秒为单位
    },
 


   // MQTT模式下的设置
    "mqtt":                        // MQTT相关的设置, con为uart@mqtt有效
    {
        "broker":"管理服务器地址",            // MQTT管理服务器的地址
        "port":"管理服务器端口",              // MQTT管理服务器使用的端口
        "id":"设备ID号",
        "username":"管理帐号",
        "password":"密码",
        "keepalive":"MQTT PING包间隔",        // 秒为单位
        "interval":"MQTT失败后连接间隔",      // 秒为单位
        "subscribe":                          // 默认连接成功后订阅topic
        {
            "默订订阅topic":"QOS",
            "默订订阅topic2":"QOS",
            // ...
        },
        "publish":"串口数据默认发布的topic",
        "publish_qos":"发布消息的QOS等级",
        //预留
        "convert":"数据转换组件"              // 用于在MQTT及串口或其它接口间的协议管理的组件(必须接要求提供指定的接口)
    },



    // GPS模式下的设置
    "gnss_center":      // 指定GPS上报的内容及服务器地址, con为uart@nmea有效
    {
        "status":"是否上报GPS信息",   // enable为上传GPS信息, disable为不上传
        "server":"上传的服务器地址",
        "proto":"协议",               // tcp为TCP, udp为UDP
        "port":"端口",
        "interval":"上传间隔",        // 秒为单位
        "content":"内容",             // NMEA的协议头, 需要上传多个头以;号分开
        "id":"自定义ID号"             // 以$PAHYR头上传
    },
    "gnss_local":       // 在本地提供NMEA协议服务, con为uart@nmea有效
    {
        "status":"是否在本地提供GPS信息",   // enable为提供, disable为禁用
        "proto":"协议",                     // tcp为TCP, udp为UDP
        "port":"端口",
        "interval":"发送间隔",              // 秒为单位
        "content":"内容",                   // NMEA的协议头, 需要提供多个头以;号分开
        "id":"自定义ID号",                   // 以$PAHYR头提供
        "limit":"5"                         // 连接数限制, 不允许超过此数的连接同时连入
    },



    // 串口透传下的设置
    "dtu_proto":                  // DTU协议, con为uart@dtu有效
    {
        // 用于向网络端（客户端或服务器）定时发送数据来保持网络连接的机制， 开启后将定时向其它的网络端定时发送数据
        "keeplive":"disable",            //<保活包> 分为disable(禁用), idle(空闲时发送), timing(定时发送)
        "keeplive_interval":"30",        // <保活包发送间隔> 以秒为单位
        "keeplive_hexstring":"",         // <保活包内容>  十六进制的数据, 如发送ABC时填写414243
        "login":"disable|hex|ascii|mac", // <注册包> 分为disable(禁用), hex为十六制, ascii为字符式, mac为使用十六制进的mac地址为注册包
        "login_hexstring":"",  // <注册包内容>  十六进制的数据, 如发送ABC时填写414243 , 为<注册包>为enable时必填
        "pktstart":"disable|hex|ascii|mac",  // <包前缀> 分为disable(禁用), hex为十六制, ascii为字符式, mac使用十六制进的mac地址为包后缀
        "pktstart_hexstring":"",  //  <包前缀内容>  十六进制的数据, 如发送ABC时填写414243 , 为<包前缀>为enable时必填
        "pktend":"disable|hex|ascii|mac", //  <包后缀> 分为disable(禁用), hex为十六制, ascii为字符式, mac使用十六制进的mac地址为包后缀
        "pktend_hexstring":"",    // <包后缀内容>  十六进制的数据, 如发送ABC时填写414243 , 为<包后缀>为enable时必填
    },
    "dtu_center":                  // DTU数据中心, con为uart@dtu有效  
    {
        "status":"disable",
        "proto":"tcp",
        "server":"",
        "port":""
    },
    "dtu_center2":                  // DTU数据中心2, con为uart@dtu有效
    {
        "status":"disable",
        "proto":"tcp",
        "server":"",
        "port":""
    },
    "dtu_center3":                  // DTU数据中心3, con为uart@dtu有效  
    {
        "status":"disable",
        "proto":"tcp",
        "server":"",
        "port":""
    },
    "dtu_local":                  // DTU本地访问, con为uart@dtu有效 
    {
        "status":"disable",
        "proto":"tcp",
        "port":"",
        "timeout":"",
        "limit":""
    }
}

```  


#### **接口** 

+ `status[]` 显示串口相关的状态信息， 每种模式都有不同的属性跟解释

>*成功返回如下JSON, 失败返回NULL*

```json
    //以下为在uart@nmea下的状态
    {
        "step":"search",       // GPS定位步骤, notty无端口, search搜索信息, located已定位
        "utc":"",            // nmea的UTC格式
        "lon":"",            // nmea经度
        "lat":"",            // nmea纬度
        "longitude":"",      // 经度
        "latitude":"",       // 纬度
        "speed":"",          // 速度
        "direction":"",      // 方向
        "declination":"",
        "elv":"",            // 海拨高度, 米为单位
        "inview":"",         // 可见卫星数
        "inuse":"",          // 使用卫星数"
        "lac":"2869",                    // 基站位置区编码
        "ci":"33C5083",                  // 基站扇区编号
        "plmn":"46000",                  // MCC+MNC
        "gnss_center":
        {
            "status":"up",   // 连接GPS上报服务器的状态, down为未连接, uping为连接中, up为连接成功
            "ip":""    // 上报服务器的IP地址
        },
        "gnss_center2":
        {
            "status":"up",   // 连接GPS上报服务器的状态, down为未连接, uping为连接中, up为连接成功
            "ip":""    // 上报服务器的IP地址
        }
    }
```


