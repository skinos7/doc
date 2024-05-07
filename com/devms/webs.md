***
## Device management web server for user
web server for user to management the own device

#### Configuration( devms@webs )
```json
{
    "status":"disable or enable",            // [ "disable", "enable" ]
    "port":"server port",                    // [ number ]
    "start_port":"ttyd start port",          // [ number ]
}
```
Examples, show all the configure
```shell
devms@webs
{
    "status":"enable",
    "port":"9000"
}
```  
Examples, modify the port to 8009
```shell
devms@webs:port=8009
ttrue
```  

