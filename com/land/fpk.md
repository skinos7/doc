
***
## FPK Management
Manage system FPK(project)

#### The following describes the project concept 
* A project is a collection of programs developed for the completion of specific needs, equivalent to a Windows application, an app in Android
* Each project has a corresponding directory, called the project directory, stored in the ./project directory in the SDK, and the project-related source code and resource files are stored in the project directory
* All development and programming should be in a project
* Each project directory must include: 
    - Project information file, named **prj.json**
    - Projects compile Makefile, such as When using Openwrt's compilation system, Makefile uses Openwrt's format
* Each project directory can contain:
    - Executable program or executable program source code (in the SDK it will be the source code of the executable program, and only the executable program will be installed on the device)
    - Library or library source code (in the SDK there will be the source code for the library, whereas installed to the device there will only be binaries of the library) 
    - Kernel driver or its source code (in the SDK there will be driver source code, whereas only driver binaries will be installed on the device)  
    - Component source code (component source code in the SDK, only component binaries installed in the device)  
    - Default profile for component or project
    - Webpage interface files for user Management
    - Language files for webpage interface
    - Script files and other resource files

#### The following introduces the FPK concept
* After the project development is completed, then package into a FPK(installation package), the FPK will be installed into the system
* FPK is equivalent to the software installation package in Windows, the apk file in Android
* The FPK ending in .fpk
* The FPK can be installed into the system through the webpage or command
* Every FPK must include: 
	- Project information file, named **prj.json**
* Each FPK can contain:
	- library
	- executable file
	- Driver files
	- .com/.ash end of the component file
	- .cfg the end of the configuration file
	- .html end of the webpage interface file
	- Language file ending with .json
	- .sh end of the SHELL script file
	- Other resource files
	- Library header files for development under install/include (used in SDK compilation)
	- Libraries for development under install/lib (used in SDK compiled)


#### prj.json: Project information file
It is generated automatically when the project is created, you can learn his format to judge your work on development projects
```json
// Attributes introduction 
{
    "name":"project(FPK) name",                    // [ string ]
    "intro":"project(FPK) introduction",           // [ string ]
    "desc":"detailed description of the project",  // [ string ]
    "type":"project(FPK) type",                    // [ "root" ], root indicates that the root permission is required
    "version":"project(FPK) version",              // [ string ]
    "author":"project(FPK) author",                // [ string ]

    "osc":                           // all open source programs included in the project show in this attributes
    {
        "open source program directory":"description"
        // "...":"..." How many open source program show how many properties
    },
    "lib":                           // all libraray included in the project show in this attributes
    {
        "library directory":"description"
        // "...":"..." How many library show how many properties
    },
    "exe":                           // all execute program included in the project show in this attributes
    {
        "execute program directory":"description"
        // "...":"..." How many execute program show how many properties
    },
    "com":                           // all component included in the project show in this attributes
    {
        "component directory":"description"
        // "...":"..." How many component show how many properties
    },
    "res":                           // all resource file or directory included in the project show in this attributes
    {
        "resource file or directory":"description"
        // "...":"..." How many resource file or directory show how many properties
    },
    "obj":                           // all object( Dynamic components ) included in the project show in this attributes
    {
        "object name":"actual components"
        // "...":"..." How many object( Dynamic components ) show how many properties
    },
    "init":                           // all starting items included in the project show in this attributes
    {
        "initialize level":"components method"
        // "...":"..." How many starting items show how many properties
    },
    "uninit":                           // all shutdown items included in the project show in this attributes
    {
        "shutdown level":"components method"
        // "...":"..." How many shutdown items show how many properties
    },
    "joint":                           // all joint process items included in the project show in this attributes
    {
        "joint event":"components method"
        // "...":"..." How many joint process items show how many properties
    }
}
// examples
{
    "name":"arch",                              // arch project
    "intro":"mtk platform layer for farm os",   // project introduction
    "desc":"This project at MTK chip will provide a unified management or use interface to the upper layerthe proejct", 
                                                // project description
    "type":"root",                              // that the root permission is required
    "version":"6.0.0",                          // version is 6.0.0
    "author":"dimmalex@gmail.com",              // author is dimmalex@gmail.com
    "osc":                                      // have 1 open source program
    {
        "ntpclient":"ntp client"                      // ntpclient, is a ntp client
    },
    "lib":                                      // have 1 library
    {
        "land":"core library"                         // land library, core library
    },
    "exe":                                      // have 3 execute program
    {
        "daemon":"service daemon",                    // daemon, service implementation
        "he":"tools for call all component",          // he, command tools for skinos
        "hetui":"tools for terminal"                  // hetui, command ui for skinos
    },
    "com":                                      // have 7 execute program
    {
        "device":"device infomation",                 // device, manage all device
        "data":"data management",                     // data, manage configure and eeprom
        "firmware":"firmware management",             // firmware, manage firmware
        "gpio":"register and gpio management",        // gpio, manage mtk gpio
        "test":"test the device management",          // test, manage factory test
        "ethernet":"ethernet switch management",      // ethernet, manage mtk switch
        "mt7628":"802.11n wireless management"        // mt7628, manage mt7628 wireless radio
    },
    "res":                                      // have 1 resource file
    {
        "testpage.py":"only test"                    // testpage.py, test tools at factory
    },
    "obj":                                      // have 2 object( Dynamic components )
    {
        "wifi@nradio":"mt7628",                      // object is wifi@nradio, actual components is mt7628
        "test":"test"                                // object is test, actual components is test
    },
    "init":                                      // have 3 starting items
    {
        "ethernet":"arch@ethernet.setup",            // arch@ethernet.setup call at the ethernet of initialize level
        "nradio":"wifi@nradio.setup",                // wifi@nradio.setup call at the nradio of initialize level
        "aradio":"wifi@aradio.setup"                 // wifi@aradio.setup call at the aradio of initialize level
    },
    "uninit":                                      // have 2 shutdown items
    {
        "nradio":"wifi@nradio.shut",                 // wifi@nradio.shut call at the nradio of initialize level
        "aradio":"wifi@aradio.shut"                  // wifi@aradio.shut call at the aradio of initialize level
    },
    "joint":                                      // have 14 joint process items
    {
        "firmware/upgrading":"arch@gpio.event",  // arch@reggpio.event call when the firmware/upgrading happened
        "firmware/upgraded":"arch@gpio.event",   // arch@reggpio.event call when the firmware/upgraded happened
        "network/arise":"arch@gpio.event",       // arch@reggpio.event call when the firmware/arise happened
        "network/ready":"arch@gpio.event",
        "network/lining":"arch@gpio.event",
        "network/online":"arch@gpio.event",
        "network/offline":"arch@gpio.event",
        "modem/poweron":"arch@gpio.event",
        "modem/poweroff":"arch@gpio.event",
        "modem/msim":"arch@gpio.event",
        "modem/bsim":"arch@gpio.event",
        "signal/flash":"arch@gpio.event",
        "nssid/up":"arch@gpio.event",
        "nssid/down":"arch@gpio.event"
    }    
}
```  


#### **Methods**

+ `register[ <project directory> [, project directory2] [,...] ]` **register project to system**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, register a project
    land@fpk.register[ /PRJ/storage ]
    ttrue
    ```

+ `unregister[ <project directory> [, project directory2] [,...] ]` **unregister project from system**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, register a project
    land@fpk.unregister[ /PRJ/storage ]
    ttrue
    ```

+ `list[ [project] ]` **list project infomation**, *succeed return talk for project infomation, failed return NULL, error return terror*
    ```shell
    # examples, list ifname project infomation
    and@fpk.list[ifname]
    {
        "name":"ifname",
        "intro":"common network connection",
        "desc":"ip connect and wifi connect component",
        "type":"root",
        "version":"7.0.0",
        "author":"dimmalex@gmail.com",
        "com":
        {
            "ethcon":"ethernet connect component",
            "ltecon":"lte modem connect component"
        },
        "path":"/PRJ/ifname/",
        "size":"55692"
    }
    # examples, list all project infomation
    and@fpk.list
    {
        "arch":
        {
            "path":"/PRJ/arch/",
            "size":"273739",
            "intro":"mtk mt7621 platform layer for skinos",
            "version":"7.0.0",
            "author":"dimmalex@gmai.com"
        },
        "client":
        {
            "path":"/PRJ/client/",
            "size":"54690",
            "intro":"Client management",
            "version":"7.0.0",
            "author":"dimmalex@gmail.com"
        },

        "ifname":
        {
            "path":"/PRJ/ifname/",
            "size":"55692",
            "intro":"common network connection",
            "version":"7.0.0",
            "author":"dimmalex@gmail.com"
        },
        "land":
        {
            "path":"/PRJ/land/",
            "size":"145238",
            "intro":"component infrastructure",
            "version":"7.0.0",
            "author":"dimmalex@gmail.com"
        },
        "wui":
        {
            "path":"/PRJ/wui/",
            "size":"500",
            "intro":"web system basic ui page",
            "version":"7.0.0",
            "author":"dimmalex@gmail.com"
        }
        ...
    }
    ```

+ `install[ <FPK file> [, FPK file2] [,...] ]` **install FPK to system**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, install wui project FPK to system
    land@fpk.install[ wui-7.0.0-x86.fpk ]
    ttrue
    ```

+ `uninstall[ <project name> [, project name2] [,...] ]` **uninstall project from system**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, uninstall wui project from system
    land@fpk.uninstall[ wui ]
    ttrue
    ```


+ `repo_list` **list all FPK of remote repository**, *succeed return talk for FPK of remote repository, failed return NULL, error return terror*
    ```shell
    # examples, list all FPK of remote repository
    land@fpk.repo_list
    {
        "network":
        {
            "intro":"network infrastructure",
            "desc":"management network",
            "version":"7.0.0",
            "author":"dimmalex@gmail.com",
            "size":"192828",
            "fpk":"network-7.0.0-mt7621.fpk"
        },
        "storage":
        {
            "intro":"storage management",
            "desc":"system storage management and ftp/samba server management",
            "version":"7.0.0",
            "author":"dimmalex@gmail.com",
            "size":"3511",
            "fpk":"storage-7.0.0-mt7621.fpk"
        },
        "webs":
        {
            "intro":"web server",
            "version":"7.0.0",
            "author":"dimmalex@gmail.com",
            "size":"139538",
            "fpk":"webs-7.0.0-mt7621.fpk"
        }
        ...
    }
    ```

+ `repo_update` **update the buffer and list all FPK of remote repository**, *succeed return talk for FPK of remote repository, failed return NULL, error return terror*
    ```shell
    # examples, update and list all FPK of remote repository
    land@fpk.repo_list
    {
        "network":
        {
            "intro":"network infrastructure",
            "desc":"management network",
            "version":"7.0.0",
            "author":"dimmalex@gmail.com",
            "size":"192828",
            "fpk":"network-7.0.0-mt7621.fpk"
        },
        "storage":
        {
            "intro":"storage management",
            "desc":"system storage management and ftp/samba server management",
            "version":"7.0.0",
            "author":"dimmalex@gmail.com",
            "size":"3511",
            "fpk":"storage-7.0.0-mt7621.fpk"
        },
        "webs":
        {
            "intro":"web server",
            "version":"7.0.0",
            "author":"dimmalex@gmail.com",
            "size":"139538",
            "fpk":"webs-7.0.0-mt7621.fpk"
        }
        ...
    }
    ```

+ `repo_install[ <FPK file on the remote repository> ]` **install FPK to system from remote repository**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, install webs-7.0.0-mt7621.fpk from remote repository
    land@fpk.repo_install[ webs-7.0.0-mt7621.fpk ]
    ttrue
    ```
