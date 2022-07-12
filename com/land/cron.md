***

## Management of scheduled task component
Administration of equipment scheduled task

#### Configuration( land@cron )

```json
// Attributes introduction 
{
    "task name":             // [ string ], The task name can be customized and must be unique
    {
        "min":"specify the minutes",          // [ 0-59 ]
                                                    // * for Every second  
                                                    // 1,2,3 for 1,2,3 second
                                                    // 2-4 for 2,3,4 second
                                                    // */2 for twice a minute
        "hour":"specify the hour",            // [ 0-23 ]
        "day":"specify the day",              // [ 1-31 ]
        "month":"specify the month",          // [ 1-12 ]
        "week":"specify the week",            // [ 0-6 ] or [ sun, mon, tue, wed, thu, fir, sat ]
                                                    // 0 for Sunday
        "call":"specify component or program",// [ string ]
                                                    // default is a component method
                                                    // start with - for shell command
    },
    // "...":{ task infomation }     How many task show how many properties
}
// Examples, have two task
{
    "mycheck":             // task name is mycheck, execute for twice a minute
    {
        "min":"*/2",
        "hour":"*",
        "day":"*",
        "month":"*",
        "week":"*",
        "call":"myproject@mycheck.checkonline"    // custom execute a component method
    },
    "mycheck2":            // task name is mycheck, execute for every a minute
    {
        "min":"*",
        "hour":"*",
        "day":"*",
        "month":"*",
        "week":"*",
        "call":"-echo 'ddddd sss'>>/tmp/ss" // execute shell echo 'ddddd sss'>>/tmp/ss
    }
}
```  

#### **Methods**

+ `add[ task name, call, <min>, <hour>, <day>, <month>, <week> ]` **add a scheduled task**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, add call restart at 3:30 every day
    land@cron.add[ restart_task, land@machine.restart, 30, 3, *, *, * ]
    ttrue
    ```

+ `delete[ task name ]` **delete a scheduled task**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, delete restart_task
    land@cron.delete[ restart_task ]
    ttrue
    ```



## 计时任务
管理系统计时任务, 对busybox的cron的包装

#### **配置( land@cron )** 
```json
// 属性介绍
{
    "任务名称":             // [ 字符串 ], 用户可自定义任务名, 任务名必须唯一
    {
        "min":"分钟",                  // [ 0-59 ], *为所有; 1,2,3为1,2,3秒; 2-4为2,3,4秒, */2为一分钟两次
        "hour":"时",                   // [ 0-23 ]
        "day":"天",                    // [ 1-31 ]
        "month":"月",                  // [ 1-12 ]
        "week":"星期",                 // [ 0-6 ] 或 [ sun,mon,tue,wed,thu,fir,sat ], 0为星期日
        "call":"调用接口",             // [ 字符串 ], -号开头为shell指令, /开头为一个对应的程序
    },
    // "...":{ 任务信息 }    // 更多其它任务
}
// 示例, 以下有两个任务
{
    "mycheck":             // 第一个任务名为mycheck
    {
        "min":"*/2",          // 一分钟执行两次
        "hour":"*",
        "day":"*",
        "month":"*",
        "week":"*",
        "call":"myproject@mycheck.checkonline"    // 自定义的一个组件接口
    },
    "mycheck2":           // 第二个任务名为mycheck2
    {
        "min":"*",          // 一分钟执行一次
        "hour":"*",
        "day":"*",
        "month":"*",
        "week":"*",
        "call":"-echo 'ddddd sss'>>/tmp/ss"      // 执行echo 'ddddd sss'>>/tmp/ss
    }
}
```


#### **接口** 

+ `add[ <任务名>, [命令], min, hour, day, month, week ]` **创建定时任务**, *成功返回ttrue, 失败返回tfalse*
    ```shell
    # 示例, 添加一个每天3点半重启系统的任务
    land@cron.add[ restart_task, land@machine.restart, 30, 3, *, *, * ]
    ttrue
    ```

+ `delete[ <任务名> ]` **删除定时任务**， *成功返回ttrue, 失败返回tfalse*
    ```shell
    # 删除上面添加的重启的任务
    land@cron.delete[ restart_task ]
    ttrue
    ```

