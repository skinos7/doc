***

## Management of System Service   
Manage gateway service task

#### The following describes service concepts   
* A service is a Linux background process
* The service is usually an endless loop that runs and never exits
* If the service exits unexpectedly, the system will restart the service
* All the method in the component can run in service mode. However, this method cannot be exited, Otherwise, the system will rerun the method frequently  


#### **Methods**

+ `run[ [delay], service name, component name, method name, [parameter list] ]` **add service**, register and start a service, if the service already exists, stop and delete it and then add it, *succeed return ttrue, failed return tfalse, error return terror*   
    ```shell
    # examples, add wui@admin.service to run, named this service wuiserver
    land@service.run[ , wuiserver, wui@admin, service ]
    ttrue
    # examples, add tui@ssh.service to run delay 5 second, named this service sshserver
    land@service.run[ 5000000, sshserver, tui@ssh, service ]
    ttrue    
    ```

+ `delete[ service name ]` **stop and delete service**, *succeed return ttrue, failed return tfalse, error return terror*   
    ```shell
    # examples, stop and delete the service wuiserver
    land@service.delete[ wuiserver ]
    ttrue   
    ```

+ `start[ service name, component name, method name ]` **add service**, only start is if the service already exists, add it if the service does not exist, *succeed return ttrue, failed return tfalse, error return terror*   
    ```shell
    # examples, add wui@admin.service to run, named this service wuiserver
    land@service.start[ wuiserver, wui@admin, service ]
    ttrue
    # examples, add tui@ssh.service to run, named this service sshserver
    land@service.start[ sshserver, tui@ssh, service ]
    ttrue    
    ```

+ `stop[ service name ]` **stop service**, *succeed return ttrue, failed return tfalse, error return terror*   
    ```shell
    # examples, stop the service wuiserver
    land@service.stop[ wuiserver ]
    ttrue   
    ```

+ `reset[ service name, [component name], [method name] ]` **reset service**, only reset is if the service already exists, add it if the service does not exist and the parameter component/method is given , *succeed return ttrue, failed return tfalse, error return terror*   
    ```shell
    # examples, add wui@admin.service to run, named this service wuiserver
    land@service.reset[ wuiserver, wui@admin, service ]
    ttrue
    # examples, add tui@ssh.service to run, named this service sshserver
    land@service.reset[ sshserver, tui@ssh, service ]
    ttrue    
    ```

+ `off[ service name ]` **off control service**, then the system don't restart the service when the service exitd any way, *succeed return ttrue, failed return tfalse, error return terror*   
    ```shell
    # examples, off control the service wuiserver
    land@service.off[ wuiserver ]
    ttrue   
    ```


+ `pid[ service name ]` **get the service pid**, *succeed return pid, failed return NULL, error return terror*   
    ```shell
    # examples, get service wuiserver pid
    land@service.pid[ wuiserver ]
    2041   
    ```

+ `info[ service name ]` **get the service infomation**, *succeed return talk, failed return NULL, error return terror*   
    ```json
    // Attributes introduction of talk by the method return
    {
        "name":"service name",                                         // [ string ]
        "status":"service state",                                      // [ "start", "reset", "off", "stop", "unregister", "finish" ]
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
    # examples, get service wuiserver infomation
    land@service.info[ wuiserver ]
    {
        "name":"wuiserver",         # service name is wuiserver
        "delay":"0",                # no delay to run
        "com":"wui@admin",          # component name is wui@admin
        "op":"service",             # component method is service
        "1":"/tmp/webpage",         # the first parameter is /tmp/webpage
        "pid":"2041",               # service process id is 2041
        "last_start":"130"          # last start when system uptime 130 second
    }
    ```

+ `list` **list all the service**, *succeed return talk, failed return NULL, error return terror*   
    ```json
    // Attributes introduction of talk by the method return
    {
        "service name":
        {
            "name":"service name",                                         // [ string ]
            "status":"service state",                                      // [ "start", "reset", "off", "stop", "unregister", "finish" ]
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
