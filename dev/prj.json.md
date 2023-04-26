
## 项目描述文件（prj.json） 
- prj.json是在项目目录必须存在
- prj.json在项目编译打包时一起打包到FPK安装包
- prj.json在项目或FPK安装包中描述整个项目的资源

## prj.json属性介绍
```json
// 属性介绍
{
    "name":"project name",                 // [ string ]
    "intro":"project brief",               // [ string ]
    "desc":"project description",          // [ string ]
    "type":"project type",                 // [ "root", "admin", "user", "app", ... ] 
                                                // "root" indicates that root permission is required, For now, only ROOT is implemented
    "version":"project version",           // [ string ]
    "author":"project author",             // [ string ]

    "osc":                                 // open source program list
    {
        "open source program name":"open source program brief"    // [ string ]: [ string ]
                                                                  // The "open source program name" is the corresponding directory where the source code is stored
        // ... more open source program
    },
    "ko":                                  // kernel module list
    {
        "kernel module name":"kernel module brief"                // [ string ]: [ string ]
                                                                  // The "kernel module name" is the corresponding directory where the source code is stored
        // ... more kernel module
    },
    "lib":                                  // share library list
    {
        "share library name":"share library brief"                // [ string ]: [ string ]
                                                                  // The "share library name" is the corresponding directory where the source code is stored
        // ... more share library
    },
    "lib":                                  // share library list
    {
        "share library name":"share library brief"                // [ string ]: [ string ]
                                                                  // The "share library name" is the corresponding directory where the source code is stored
        // ... more share library
    },
    "exe":                                  // list of executable program only use by current project
    {
        "executable program name":"executable programy brief"     // [ string ]: [ string ]
                                                                  // The "executable program name" is the corresponding directory where the source code is stored
        // ... more executable program
    },
    "cmd":                                  // list of executable program for linux command, linux can execute this executable program in shell
    {
        "executable program name":"executable programy brief"     // [ string ]: [ string ]
                                                                  // The "executable program name" is the corresponding directory where the source code is stored
        // ... more executable program
    },

    "com":                                  // list of component
    {
        "component name":"component brief"                        // [ string ]: [ string ]
                                                                  // The "component name" is the corresponding directory where the source code is stored
        // ... more component
    },
    "obj":                                  // list of component instance
    {
        "component object full name":"component full name"        // [ string ]: [ string ]
                                                                  // The "component object name" is an alias for component full name
                                                                  // component can recognize different names in the code to do different processing
                                                                  // For example, ifname@lan and ifname@lan2 are both the same component and different object
        // ... more object
    },

    "res":                                  // list of resource file or resource directory
    {
        "resource file or resource directory":"resource brief"    // [ string ]: [ string ]
        // ... more resource
    },

    "init":                                 // list of component setup call at system initialization
    {
        "init level":                                             // [ string ]
        {
            "component interface":"interface brief"               // [ string ]: [ string ]
            // ... more component interface
        }
        // ... more initialize level
    },
    "uninit":                               // list of component shut call at system shutdown
    {
        "uninit level":                                           // [ string ]
        {
            "component interface":"interface brief"               // [ string ]: [ string ]
            // ... more component interface
        }
        // ... more shutdown level
    },
    "joint":                                // list of component call when system event action
    {
        "joint name":                                             // [ string ]
        {
            "component interface":"interface brief"               // [ string ]: [ string ]
            // ... more component interface
        }
        // ... more event handling
    },

    "wui":
    {
        "web page name":
        {
            "menu":"which menu item to place under",
            "en":"menu entry name for this web page in english",
            "cn":"menu entry name for this web page in chinese",
            "page":"web page html file",
            "lang":                                                           // list language resource file
            {
                "cn":"chinese language document",
                "en":"english language document"
                // ... more language
            },
            "object":"show the entry whether this component exists",         // [ string ], vaild when "config" be null
            "config":"show the entry whether this config exists",            // [ string ]
            "attr":"show the entry whether this attribute exists"            // [ string ], vaild when "config" non-null
        }
        // ... more web page
    }

}
```  

## 示例介绍tui项目中的prj.json
tui项目位置 **[tiger7/project/tui](./project/tui)**, 以下是tui项目的项目描述文件prj.json
```json
{
    "name":"tui",                                         // name is tui
    "intro":"Terminal user interface service", 
    "type":"root",
    "version":"7.0.0",
    "author":"dimmalex@gmail.com",
    "com":                                                // two components in the tui project, 
    {   
        "telnet":"telnet server management",                    // The corresponding component code is in the "telnet" directory of the "tui" project directory
        "ssh":"ssl shell server management"                     // The corresponding component code is in the "ssh" directory of the "tui" project directory
    },  
    "cmd":                                                // one command in the tui project
    {   
        "sline":"tools for terminal command line"               // The corresponding component code is in the "sline" directory of the "tui" project directory
    },  
    "obj":                                                // two object in the tui project
    {   
        "telnetd":"telnet",                                    // Indicates that calling telnetd is equal to tui@telnet
        "sshd":"ssh"                                           // Indicates that calling sshd is equal to tui@ssh
    },  

    "init":
    {   
        "app":
        {   
            "tui@telnet.setup":"",                             // interface "setup" of component "tui@telnet" well be call at the "app" level in the system initialization
            "tui@ssh.setup":""                                 // interface "setup" of component "tui@ssh" well be call at the "app" level in the system initialization
        }   
    },  

    "wui":                                                // the project have two web page
    {   
        "telnet":                                              // register a webpage name "telnet" to system web management
        {   
            "menu":"System",                                             // register to "System" menu item of system web management
            "en":"Telnet Server",                                        // menu entry is "Telnet Server" in english
            "cn":"Telnet服务器",                                          // menu entry is "Telnet服务器" in chinese
            "page":"telnet.html",                                        // html code file is "telnet.html" in the project directory
            "config":"tui@telnet",                                       // this menu entry show when "tui@telnet" exist
            "lang":
            {   
                "cn":"cn.json",                                          // language resource file in chinese for "telnet.html"
                "en":"en.json"                                           // language resource file in english for "telnet.html"
            }   
        },  
        "ssh":                                                 // register a webpage name "ssh" to system web management
        {   
            "menu":"System",                                             // register to "System" menu item of system web management
            "en":"SSH Server",                                           // menu entry is "SSH Server" in english
            "cn":"SSH服务器",                                            // menu entry is "SSH服务器" in chinese
            "page":"ssh.html",                                           // html code file is "ssh.html" in the project directory
            "config":"tui@ssh",                                          // this menu entry show when "tui@ssh" exist
            "lang":
            {   
                "cn":"cn.json",                                         // language resource file in chinese for "ssh.html"
                "en":"en.json"                                          // language resource file in english for "ssh.html"
            }   
        }   
    }   
}
```