***

## Management of Service component
Administration of equipment service task

#### The following describes service concepts
* A service is a Linux background process
* The service is usually an endless loop that runs and never exits
* If the service exits unexpectedly, the system will restart the service
* All the method in the component can run in service mode. However, do not exit the method running in service mode. Otherwise, the system will continuously run the method  


#### **Methods**

+ `run[ [delay], service name, component name, method name, [parameter list] ]` **add service**, If the service already exists, delete it and then add it, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, add wui@admin.service to run
    land@service.run[ , wui@admin, wui@admin, service ]
    ttrue
    # examples, add tui@ssh.service to run delay 5 second
    land@service.run[ 5000000, sshserver, tui@ssh, service ]
    ttrue    
    ```

+ `delete[ service name ]` **delete service**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, stop and delete the service wui@admin
    land@service.unregister[ wui@admin ]
    ttrue   
    ```

+ `start[ service name, component name, method name ]` **add service**, Only start is if the service already exists, Add  register it if the service does not exist, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, add wui@admin.service to run
    land@service.start[ wui@admin, wui@admin, service ]
    ttrue
    # examples, add tui@ssh.service to run
    land@service.start[ sshserver, tui@ssh, service ]
    ttrue    
    ```

+ `stop[ service name ]` **stop service**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, stop the service wui@admin
    land@service.stop[ wui@admin ]
    ttrue   
    ```

+ `reset[ service name, [component name], [method name] ]` **reset service**, Only reset is if the service already exists, Add register it if the service does not exist, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, add wui@admin.service to run
    land@service.reset[ wui@admin, wui@admin, service ]
    ttrue
    # examples, add tui@ssh.service to run
    land@service.reset[ sshserver, tui@ssh, service ]
    ttrue    
    ```

+ `off[ service name ]` **off control service**, then the system don't restart the service when the service exitd, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, off control the service wui@admin
    land@service.off[ wui@admin ]
    ttrue   
    ```


+ `pid[ service name ]` **get the service pid**, *succeed return pid, failed return NULL, error return terror*
    ```shell
    # examples, get service wui@admin pid
    land@service.pid[ wui@admin ]
    2041   
    ```

+ `info[ service name ]` **get the service infomation**, *succeed return talk, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "name":"service name",                                         // [ string ]
        "status":"service state",                                      // [ start, reset, off, stop, unregister, finish ]
        "delay":"delay to run",                                        // [ number ], the unit in microsecond
        "com":"component name",                                        // [ string ]
        "op":"method name",                                            // [ string ]
        "1":"first parameter",                                         // [ string or talk ]
        "2":"second parameter",                                        // [ string or talk ]
        "3":"third parameter",                                         // [ string or talk ]
        "pid":"pid number",                                            // [ number ]
        "last_start":"the system uptime when the service last start"   // [ number ]
    }    
    ```
    ```shell
    # examples, get service wui@admin infomation
    land@service.info[ wui@admin ]
    {
        "name":"wui@admin",
        "delay":"0",
        "com":"wui@admin",
        "op":"service",
        "1":"/tmp/webpage",
        "pid":"2041",
        "last_start":"130"
    }
    ```

+ `list` **list all the service**, *succeed return talk, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "service name":
        {
            "name":"service name",                                         // [ string ]
            "status":"service state",                                      // [ start, reset, off, stop, unregister, finish ]
            "delay":"delay to run",                                        // [ number ], the unit in microsecond
            "com":"component name",                                        // [ string ]
            "op":"method name",                                            // [ string ]
            "pid":"pid number",                                            // [ number ]
            "last_start":"the system uptime when the service last start"   // [ number ]
        }
        // "...":{ service infomation }  // How many service show how many properties
    }    
    ```
    ```shell
    # examples, list all service
    land@service.list
    {
        "clock@restart":
        {
            "name":"clock@restart",
            "delay":"0",
            "com":"clock@restart",
            "op":"service",
            "pid":"1745",
            "last_start":"40"
        },
        "tui@telnet":
        {
            "name":"tui@telnet",
            "delay":"0",
            "com":"tui@telnet",
            "op":"service",
            "pid":"1758",
            "last_start":"40"
        },
        "tui@ssh":
        {
            "name":"tui@ssh",
            "delay":"0",
            "com":"tui@ssh",
            "op":"service",
            "pid":"1763",
            "last_start":"40"
        },
        "wui@admin":
        {
            "name":"wui@admin",
            "delay":"0",
            "com":"wui@admin",
            "op":"service",
            "1":"/tmp/webpage",
            "pid":"2041",
            "last_start":"130"
        }
    }
    ```
