

# 在云管理中添加用户帐号   

### 1. 登录到安装了云管理Ubuntu    
通过SSH或其它终端工具登陆到Ubuntu   

### 2. 执行sline进入SkinOS的终端命令行   
```
ubuntu@VM-0-8-ubuntu:~$ sline
$
```   

### 3. 添加用户帐号   
添加一个名为asheylf的用户帐号, 密码为 Z1x2c3v4b5, 语言为 中文, 注解为 示例用   
```shell
$ dport.user_add[ ashyelf, Z1x2c3v4b5,, cn, 示例用 ]
ttrue
$
```   

列出云管理上所有的用户的帐号   
```shell
$ dport.user_list
{
    "ashyelf":
    {
        "vcode":"",
        "lang":"cn",
        "comment":"示例用"
    },
    "onlytest":
    {
        "vcode":"",
        "lang":"cn",
        "comment":"测试帐号"
    }
}
$
```   

**更多参数说明见 [接入管理](../../com/devms/devport.md)**   


