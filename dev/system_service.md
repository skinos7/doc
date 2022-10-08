
## 操作系统服务

系统中项目的组件实现一些需要长久运行的函数, 称之为 **后台服务函数**, 这类函数需要一直运行, 并且在发生异常退出时需要系统将些重新运行, 通过操作系统服务API我们可以实现将组件的这类函数以服务的方式运行, 并让系统保证其一直运行


## 操作系统服务时需要用到的交互结构
 - [项目及组件开发-参数结构param_t](./param_t.md)
 - [项目及组件开发-组件交互结构talk_t](./talk_t.md)
 - [项目及组件开发-寻址结构obj_t/attr_t](./obj_t.md)


## 操作服务API说明

开发者可编写一些函数，然后通过操作服务API将其作为服务一直运行

此文档描述的函数接口都位于[land/service.h](./include/land/service.h)中, 通过包含[land/skin.h](./include/land/skin.h)即可
```c
    #include "land/skin.h"
```

## API头文件中的介绍

[land/service.h](./include/land/service.h)



## 服务API分类

##### 启动一个服务
将组件的 **后台服务函数** 以服务的方式运行
```c
/**
 * @brief 以服务的方式注册一个组件的接口
 * @param flags 标识位
 * @param delay 延迟毫秒数
 * @param obj 组件名称
 * @param method 接口名称
 * @param param 参数
 * @param nameformat 服务名称( 为新创建的服务命名 )
 * @return 成功返回0或大于0, 失败返回负数 */
int serv_register( unsigned int flags, unsigned int delay, obj_t obj, const char *func, param_t param, const char *nameformat, ... );
int serv_sregister( unsigned int flags, unsigned int delay, const char *obj, const char *func, param_t param, const char *nameformat, ... );
int serv_registers( unsigned int flags, unsigned int delay, obj_t obj, const char *func, const char *param, const char *nameformat, ... );
int serv_sregisters( unsigned int flags, unsigned int delay, const char *obj, const char *func, const char *param, const char *nameformat, ... );
int serv_registert( unsigned int flags, unsigned int delay, obj_t obj, const char *func, talk_t param, const char *nameformat, ... );
int serv_sregistert( unsigned int flags, unsigned int delay, const char *obj, const char *func, talk_t param, const char *nameformat, ... );


/* ######################################################################## */
/* ######################################################################## */
/* #############################  Service Create ########################## */
/* ######################################################################## */
/* ######################################################################## */
/**
 * @brief 以服务的方式运行一个组件的接口
 * @param obj 组件名称
 * @param method 接口名称
 * @param param 参数
 * @param nameformat 服务名称( 为新创建的服务命名 )
 * @return 成功返回0或大于0, 失败返回负数 */
#define serv_start( obj, func, param, ... ) serv_register( 0, 0, obj, func, param, __VA_ARGS__ )
#define serv_sstart( obj, func, param, ... ) serv_sregister( 0, 0, obj, func, param, __VA_ARGS__ )
#define serv_starts( obj, func, param, ... ) serv_registers( 0, 0, obj, func, param, __VA_ARGS__ )
#define serv_sstarts( obj, func, param, ... ) serv_sregisters( 0, 0, obj, func, param, __VA_ARGS__ )
#define serv_startt( obj, func, param, ... ) serv_registert( 0, 0, obj, func, param, __VA_ARGS__ )
#define serv_sstartt( obj, func, param, ... ) serv_sregistert( 0, 0, obj, func, param, __VA_ARGS__ )

```

##### 停止或重启一个服务
- 停止一个服务
```c
/**
 * @brief 停止一个服务
 * @param nameformat 服务名称
 * @return 成功返回停止前的PID, 失败返回负数 */
int serv_stop( const char *nameformat, ... );
```
- 重启一个服务
```c
/**
 * @brief 重启一个服务
 * @param nameformat 服务名称
 * @return 成功返回重启前的PID, 失败返回负数 */
int serv_reset( const char *nameformat, ... );
```
- 禁止系统在服务退出时重启运行它
```c
/**
 * @brief 注销一个服务
 * @param nameformat 服务名称( 为新创建的服务命名 )
 * @return 成功返回0或大于0, 失败返回负数 */
int serv_unregister( const char *nameformat, ... );
#define serv_off( ... ) serv_unregister( __VA_ARGS__ )
```

##### 获取服务的信息

- 列出系统中所有的服务
```c
/**
 * @brief 得到所有服务的信息
 * @return 成功返回所有服务列表, 以下为JSON格式示列; 失败返回NULL
 {
	 "服务名称":				// 属性介绍
	 {
		 "status":"状态", 	  // 服务状态, live为运行中, die为未运行   
		 "pid":"进程ID号",			  
		 "obj":"组件名", 	  
		 "op":"接口名"			 
	 },
	 "reggpio-agent":			// IO口代理服务示例
	 {
		 "status":"die",		   // die表示未运行
		 "pid":"825",			   // 进程ID号为825
		 "obj":"arch@reggpio",	   // 对应的组件名为arch项目下的reggpio组件
		 "op":"agent"			   // 接口为agent
	 },
	 // ...更多的服务
 }*/
talk_t serv_list( void );
```
- 获取服务的进程ID号
```c
/**
 * @brief 得到一个服务的进程ID号
 * @param nameformat 服务名称
 * @return 成功返回服务进程 的ID号, 失败返回负数 */
pid_t serv_pid( const char *nameformat, ... );
```
- 获取指定服务的信息
```c
/**
 * @brief 得到一个服务的信息
 * @param nameformat 服务名称
 * @return 成功返回信息(格式示例如下, 属性值跟据实际的服务变化); 失败或无此服务返回NULL 
 {
	"status":"live",		  // 服务状态, live为运行中, die为未运行
	"pid":"2232",			  // 进程ID号
	"obj":"tui@ssh",		  // 组件名
	"op":"service"			  // 组件接口
 }*/
talk_t serv_info( const char *nameformat, ... );
```



## 操作系统服务API示例

- 在组件中编写一个服务函数
```c

talk_t _service( obj_t this, param_t param )
{
	/* 执行实际的服务, 以下以执行循环表明之后的代码会一直运行 */
	while(1)
	{
		/* 间隔5秒向日志系统是记录信息 */
		info( "i am working\n" );
		sleep( 5 );
	}
	// 返回tfalse表示服务失败退出, 系统将重启此服务
	return tfalse;
}
// 注意, 服务函数返回值不同会导致系统是否重运行此函数
// EXIT_ttrue  --- 表示服务完成需要完成的任务, 正常退出系统不再重启此服务
// EXIT_terror --- 表示服务出现致命错误, 系统不再重启此服务
// EXIT_tfalse --- 表示服务失败退出, 系统将重启此服务
// NULL        --- 未定义, 系统将重启此服务
```

- 在组件的setup方法中以服务的方式运行上面编写的service方法, 运行组件此setup方法后, 系统就会保持一直运行service方法
```c
talk_t _setup( obj_t this, param_t param )
{
    /* 将本组件中的_service函数做为myTestService系统服务运行 */
    if ( cstart( this, "service", NULL, "myTestService" ) < 0 )
    {
        perror( "start the myTestService failed" );
        return tfalse;
    }
    return ttrue;
}

```

- 接以上示例, 在shut方法中编写停止示例中的服务
```c
talk_t _shut( obj_t this, param_t param )
{
    /* 停止myTestService系统服务 */
    if ( sstop( "myTestService" ) < 0 )
    {
        return tfalse;
    }

    return ttrue;
}

```


## 在命令行中管理服务

通过[land@service](../com/land/service.md)组件接口可以查看及管理当前系统服务



