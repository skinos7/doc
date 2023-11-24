***
## Device management ui server for user
web page server for user to management the own device

#### Configuration( devms@devui )
```json
{
    "status":"disable or enable",            // [ "disable", "enable" ]
    "port":"server port",                    // [ number ]
}
```
Examples, show all the configure
```shell
devms@devui
{
    "status":"enable",
    "port":"80"
}
```  
Examples, modify the port to 8009
```shell
devms@devui:port=8009
ttrue
```  

