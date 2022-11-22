
## 库仑计管理
管理串口上的库仑计

#### **配置( inrico@coulombmeter  )** 

```json
// 属性介绍
{
    "warn_percent":"报警电压值",           // [ 数字 ], 百分比
    "full_voltage":"电池满电电压值",       // [ 浮点 ], 单位为V
    "under_voltage":"电池欠压值",          // [ 浮点 ], 单位为V
    
    "rated_current":"电池额定容量",        // [ 浮点 ], 单位为AH
    "current_range":"电流量程",            // [ 浮点 ], 单位为A

    "back_light":"背光模式",                // [ 数字 ]
    "use_time":"使用次数",                  // [ 数字 ]

    "address":"库仑计地址"           // [ 数字 ], 只读
    "version":"库仑计软件版本",      // [ 数字 ], 只读
    "percent":"当前电量",            // [ 数字 ], 百分比
    "voltage":"当前电压",            // [ 数字 ], 百分比
    "current":"当前电流",            // [ 数字 ], 百分比
    "temperature":"当前温度",        // [ 数字 ], 摄氏度
    "direction":"充放电状态"         // [ charge, discharge ], charge表示充电中, discharge表示放电中
}
```

示例, 显示所有配置
```shell
inrico@coulombmeter
{
    "warn_percent":"12",                // 报警电压值为百分之12
    "full_voltage":"0.00",              // 电池满电电压值0.00V
    "under_voltage":"0.00",             // 电池欠压值为0.00V
    "current_range":"15",               // 电流量程为15A
    "rated_current":"60.00",            // 电池额定容量为60AH
    "use_time":"20",                    // 电池使用次数为20
    "back_light":"0",                   // 背光模式为0
    "version":"53",                     // 库仑计软件版本为53
    "address":"1",                      // 库仑计地址为1
    "percent":"100",                    // 当前电量为百分100
    "voltage":"13.27",                  // 当前电压为13.27
    "current":"0.00",                   // 当前电流为0.00A
    "temperature":"-50.0",              // 当前温度为-50摄氏度
    "direction":"discharge"             // 当前处于放电状态
}
```  
示例, 设置电池额定容量为70AH
```shell
inrico@coulombmeter:rated_current=70
ttrue
```  
示例, 设置背光模式为1
```shell
inrico@coulombmeter:back_light=1
ttrue
```  

