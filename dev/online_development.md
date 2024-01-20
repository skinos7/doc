

## 运行系统中创建脚本项目

#### SSH或Telnet进入系统终端 
如在Windows下使用Telnet工具或是SSH客户端(如需中文支持必须工具支持UTF8编码)进入运行系统
```shell
dimmalex@dimmalexdeMBP ~ % telnet 192.168.8.1
Trying 192.168.8.1...
Connected to h721-127200.
Escape character is '^]'.

H721-127200 login: admin
Password: 

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
 @ ----------------------- List all the project
 @? ---------------------- List all the static component
 @@ ---------------------- List all the dynamic component
 <com> ------------------- Show component configure
 <com>:<config> ---------- Get component configure attribute
 <com>:<config>=<value> -- Set component configure attribute
 -----------------------------------------------------------
# 
```
以上示例中网关的地址为192.168.8.1, 出现以上提示表示已进入系统终端

#### 进入SHELL终端 
在系统终端中输入elf回车即可进入SHELL终端
```shell
# elf


BusyBox v1.23.2 (2024-01-19 23:10:17 CST) built-in shell (ash)


               EEEEEEEEE   LL           FFFFFFFFF
               EE          LL           FF
               EE          LL           FF
               EEEEEEEEE   LL           FFFFFFFFF
               EE          LL           FF
               EE          LL           FF
        Ashy   EEEEEEEEE   LLLLLLLLLL   FF

 --------------------------------------------------------------
 Command Help
 --------------------------------------------------------------
 hetui ---------------------- Enter to HE terminal
 he @ ----------------------- List all the project
 he @? ---------------------- List all the static component
 he @@ ---------------------- List all the dynamic component
 he <com> ------------------- Show component configure
 he <com>:<config> ---------- Get component configure attribute
 he <com>:<config>=<value> -- Set component configure attribute
 --------------------------------------------------------------
admin@H721-127200:~# 
~ #
```

#### 查看prj指令相关说明 
prj指令协助在运行系统中开发, 在SHELL终端执行如下指令查看相关的命令说明
```shell
admin@H721-127200:~# prj
argument error
help:
      prj create      project_name                       create a project template
      prj delete      project_name                       delete the project
      prj add_com     project_name com_name              create a shell component template
      prj add_init    project_name init_level   com_api  register a component api at system init call
      prj add_uninit  project_name uninit_level com_api  register a component api at system shutdown call
      prj add_joint   project_name joint_event  com_api  register a component api at joint cast
      prj add_object  project_name object_name com_name  create a dynamic component depend on exist component
      prj add_wui     project_name wui_name              create a ace web page template for project
      prj check       project_name                       check the a project json format
      prj pack        project_name                       pack the project into fpk
admin@H721-127200:~# 
```

#### 在运行系统中创建项目
执行
```shell
prj create 项目名
```
创建项目, 以下是创建test项目
```shell
admin@H721-127200:~# prj create test
project test introduction: Demonstrate how to develop a project
The project directory /mnt/internal/prj/test/
admin@H721-127200:~# 
```

执行
```shell
he fpk.list[ 项目名 ]
```
查看项目的基本信息, 以下查看刚创建的test项目
```shell
admin@H721-127200:~# he fpk.list[ test ]
{
    "name":"test",
    "version":"7.0.0",
    "author":"tmptools",
    "intro":"Demonstrate how to develop a project",
    "path":"/mnt/internal/prj/test/",
    "size":"122"
}
```
以上显示为一个JSON表示test项目的基本信息, 如path属性指明项目所在的位置, size表示项目的大小



#### 在运行系统中创建SHELL组件
执行
```shell
prj add_com 项目名 组件名
```
创建项目SHELL组件, 以下是在test项目中创建名为loglte的SHELL组件
```shell
admin@H721-127200:~# prj add_com test loglte
The component file /mnt/internal/prj/test/loglte.ash
admin@H721-127200:~#
```
创建后会打印SHELL组件文件位置

查看创建的SHELL组件
```shell
admin@H721-127200:~# cat /mnt/internal/prj/test/loglte.ash
#!/bin/bash
# Copyright (C) 2020-2022 ASHYELF
# include fundamental function support, you cannot delete this
. $cheader


# setup method for register a normal service
setup()
{
    echo "the ${PROJECT}@${COM} setup has be called"
    he log.info[ "the ${PROJECT}@${COM} setup has be called"  ]
    creturn ttrue
}
# shut method for unregister all service
shut()
{
    echo "the ${PROJECT}@${COM} setup has be called"
    he log.info[ "the ${PROJECT}@${COM} setup has be called"  ]
    creturn ttrue
}



# method, service will exit with ttrue, the service will log for forever
service()
{
    nubmer=1
    max=11
    while :
    do
        number=$[number+1]
        he log.info[ "hello world ( $number ) times"  ]
        sleep 1
    done
    creturn tfalse
}

# method, call by ${PROJECT}@${COM}.list
list()
{
    ret='{"'$PARAM1'":"'$PARAM2'"}'
    creturn $ret
}

# call the method, you cannot delete this
cend
admin@H721-127200:~#
```
以上为一个SHELL组件的基本示例, 其中有四个shell函数
 - setup(), 通常用来注册为开机运行
 - shut(), 通常用来注册为关机运行
 - service(), 通常用来注册为服务
 - list()

这四个函数都可以通过he指令直接执行
开发者可以在这个SHELL组件中添加或是删除函数, 也可以重写这些函数, **但文件中的开头$cheader及结尾cend不能改动**


#### 执行SHELL组件中的函数
执行
```
he 项目@组件.函数
```
来运行SHELL组件的函数
```shell
admin@H721-127200:~# he test@loglte.setup
the test@loglte setup has be called
ttrue
ttrue
admin@H721-127200:~#
```
以上打印的信息显示/mnt/internal/prj/test/loglte.ash中的setup函数被执行了
1. 此函数的第一条指令是向终端打印the test@loglte setup has be called
2. 此函数的第二条指令是向日志打印the test@loglte setup has be called

通过he log.show查看log中是否也有对应的打印来再次确认setup被执行
```shell
admin@H721-127200:~# he log.show
Jan 19 12:58:07 H721-127200 user.info client@station: 60:3E:5F:67:B8:06 appear{1869/station.c/180}
Jan 19 12:58:18 H721-127200 user.info he: the test@loglte setup has be called{4129/syslog.c/874}
admin@H721-127200:~#
```
*SHELL组件中的所有函数都可以通过 he 项目@组件.函数 的方式在shell终端中运行*
*SHELL组件中的所有函数都可以通过 项目@组件.函数 的方式在HE终端中运行*


#### 将SHELL组件中的函数注册为开机启动项
以上创建的SHELL脚本组件中的函数可以注册为启动项，通过执行来注册
```
prj add_init 项目名 启动级别 项目@组件.函数
```

接以上示例将logtest.ash中的setup函数注册为开机启动项, 启动级别为general
```shell
admin@H721-127200:~# prj add_init test general test@loglte.setup
```
使用fpk.list来查看项目信息是否发生变化
```
admin@H721-127200:~# he fpk.list[ test ]
{
    "name":"test",
    "version":"7.0.0",
    "author":"tmptools",
    "intro":"Demonstrate how to develop a project",
    "init":
    {
        "general":
        {
            "test@loglte.setup":""
        }
    },
    "path":"/mnt/internal/prj/test/",
    "size":"1136"
}
admin@H721-127200:~# he fpk.list[ test]
```
可以看到项目信息中有增加了init的属性即表示注册启动项成功，系统重启后此SHELL脚本的setup函数将会在系统开机时启动
*注： 所有注册开机运行及关机运行的脚本必须在执行完后应立即退出，否则将使系统的程序开关机流程停在未退出的程序中*


#### 将SHELL组件中的函数注册为关机项
SHELL脚本组件中的函数也可以注册为关机项，通过执行来注册, 常用的关机级别为general
```
prj add_uninit 项目名 关机级别 项目@组件.函数
```


#### 将SHELL组件中的函数注册为系统事件
通过注册系统事件让系统在事件发生后运行指定的SHELL组件的函数， 通过执行
```
prj add_joint 项目名 事件 项目@组件.函数
```
注册系统事件
*注： 系统中有很多事件， 也可以自定义事件, 具体介绍在joint.md中*
*注： 所有事件处理脚本必须在执行完后应立即退出，否则将使系统的事件流程停在未退出的程序中*



#### 在项目中创建配置
可为项目创建配置, 配置格式必须为JSON格式, 如下在test项目中创建loglte配置， 即在项目目录下创建一个名为loglte.cfg文件
```shell
admin@H721-127200:/tmp/mnt/internal/prj/test# cat loglte.cfg
{
    "status":"enable",
    "property":"my test value"
}
admin@H721-127200:/tmp/mnt/internal/prj/test#
```

之后还可以通过
```shell
prj check [项目名]
```
来检查项目的所有的JSON格式是否正确, 如果不正确就会报错, 全部正确则不会打印任何信息, 如我们检查test项目执行如下
```shell
admin@H721-127200:/tmp/mnt/internal/prj/test# prj check test
admin@H721-127200:/tmp/mnt/internal/prj/test#
```

在SHELL终端中查看刚创建的配置
```shell
admin@H721-127200:/tmp/mnt/internal/prj/test# he test@loglte
{
    "status":"enable",
    "property":"my test value"
}
admin@H721-127200:/tmp/mnt/internal/prj/test#
```

在SHELL终端中修改test@loglte配置的status属性为disable
```shell
admin@H721-127200:/tmp/mnt/internal/prj/test#
admin@H721-127200:/tmp/mnt/internal/prj/test# he test@loglte:status=disable
ttrue
admin@H721-127200:/tmp/mnt/internal/prj/test# he test@loglte:status
disable
admin@H721-127200:/tmp/mnt/internal/prj/test# he test@loglte
{
    "status":"disable",
    "property":"my test value"
}
```
在SHELL终端中为test@loglte配置添加一个newfeature的属性并赋值为bigtest
```shell
admin@H721-127200:/tmp/mnt/internal/prj/test# he test@loglte:newfeature=bigtest
ttrue
admin@H721-127200:/tmp/mnt/internal/prj/test# he test@loglte:newfeature
bigtest
admin@H721-127200:/tmp/mnt/internal/prj/test# he test@loglte
{
    "status":"disable",
    "property":"my test value",
    "newfeature":"bigtest"
}
admin@H721-127200:/tmp/mnt/internal/prj/test#
```
在SHELL终端中删除test@loglte配置的property属性, 即将属性赋值为空即可
```shell
admin@H721-127200:/tmp/mnt/internal/prj/test# he test@loglte:property=
ttrue
admin@H721-127200:/tmp/mnt/internal/prj/test# he test@loglte:property
admin@H721-127200:/tmp/mnt/internal/prj/test# he test@loglte
{
    "status":"disable",
    "newfeature":"bigtest"
}
admin@H721-127200:/tmp/mnt/internal/prj/test#
```



#### 在项目中创建网页界面
执行
```shell
prj add_wui 项目名 界面标识
```
创建网页界面, 比如接上面的示例项目名为test, 界面ID也名命为loglte, 那么执行如下：
```shell
admin@H721-127200:/tmp/mnt/internal/prj/test# prj add_wui test loglte
web menu title(Chinese): Log LTE
web menu name(English): Log LTE
{
    "page":"loglte.html",
    "lang":
    {
        "cn":"loglte-cn.json",
        "en":"loglte-en.json"
    },
    "cn":"Log LTE",
    "en":"Log LTE"
}
The web page file /mnt/internal/prj/test/loglte.html
admin@H721-127200:/tmp/mnt/internal/prj/test#
```
执行后会交互式的询问菜单的中英文名称（在管理网页中的应用菜单下显示的入口名, 中文必须会UTF8编码）, 入后会在test的项目目录下生成三个文件：
- loglte.html   界面文件
- loglte-cn.json 中文语言文件
- loglte-en.json 英文语言文件
*注：使用中文名称或中文语言时系统一定要设为UTF8的编码, 否则将无法工作*

之后编辑对应的html界面即可, 接以上示例所生成的loglte.html中是一个简单的示例， 包含了获取及设置test@loglte配置
编写网页需要有javascript、html的基本知识，并稍了解jquery的用法即可，具体的界面程序的开发可参见 [项目及组件开发介绍.md](./项目及组件开发介绍.md) 中的 **编写网页界面程序**
*注：以上网页界面可在管理网页的<应用>下访问, 如以上示例的中文入口为<Log LTE>*



#### 打包运行系统中创建的项目
执行
```shell
prj pack 项目名
```
将项目打包为FPK安装包, 打包成FPK安装包后即可通过管理界面的升级界面安装到其它的网关中， 比如接上面的示例项目名为test, 那么执行如下打包：
```shell
admin@H721-127200:/tmp/mnt/internal/prj/test# prj pack test
The packaging is located in this /tmp/test-7.0.0-mt7621.fpk
admin@H721-127200:/tmp/mnt/internal/prj/test#
```
打包生成的FPK安装包并会打印FPK安装包的位置, 可通过tftp或其它的网络协议传送出来, 然后可以通过管理界面升级到其它网关中



#### 删除运行系统中的项目
执行
```shell
prj delete 项目名
```
将删除以项目名名命的项目
也可在管理网页界面中的<系统>下<软件管理>中删除对应的软件(一些定制版软件无此界面)


#### 完整的SHELL组件loglte的示例
此组件通过脚本实现跟据loglte配置中的status是否为enable来启动每5秒钟向日志记录LTE的信号强度
```shell
admin@H721-127200:/tmp/mnt/internal/prj/test# cat loglte.ash
#!/bin/bash
# Copyright (C) 2020-2022 ASHYELF
# include fundamental function support, you cannot delete this
. $cheader


# setup method for register a normal service
setup()
{
    # get the value of test@loglte:status
    status=`he ${PROJECT}@${COM}:status`
    if [ "X$status" = "Xenable" ]
    then
        # register a service to run the test@loglte.service function
        he service.start[ ${PROJECT}@${COM}, ${PROJECT}@${COM}, service ]
        # log to syslog
        he log.info[ "register a service to run ${PROJECT}@${COM}.service" ]
    fi
    creturn ttrue
}
# shut method for unregister all service
shut()
{
    # stop the service
    he service.stop[ ${PROJECT}@${COM} ]
    creturn ttrue
}



# method, service will exit with ttrue, the service will log for forever
service()
{
    while :
    do
        # get current RSSI of LTE
        date=`date`
        signal=`he ifname@lte.status:rssi`
        # log to syslog
        he log.info[ "${date} log the LTE signal( RSSI ) current is ${signal}dBm"  ]
        # sleep 5 second
        sleep 5
    done
    creturn tfalse
}

# call the method, you cannot delete this
cend
```