***
## Management of destination NAT
Management of destination NAT to proxy internet port on local network for local client access

#### Configuration( forward@dnat )
```json
// Attributes introduction 
{
    "rule name":                    // [ string ], user can custom the rule name
    {
        "destip":"internet server ip address",    // [ ip address ]
        "destport":"internet server port",        // [ number ]
                                                            // signal port: 80
                                                            // range of port: 80-100
                                                            // multiple port: 80,8080,8000
        "protocol":"protocol type",               // [ "tcp", "udp", "tcpudp" ], tcpudp for tcp and udp
        "targetport":"local proxy port"           // [ number ]
    }
    // ... more rule
}
```
Examples, show current all of dnat rule
```shell
forward@dnat
{
    "proxy1":                          # rule name is proxy1
    {
        "destip":"29.23.11.35",        # internet server ip is 29.23.11.35
        "destport":"28-90",            # internet server port is start 28, end at 90 
        "protocol":"tcpudp",           # proxy tcp and udp
        "targetport":"100"             # proxy the server on port 100 at local interface
    }
}
```
Examples, add a rule named proxy2
```shell
forward@dnat:proxy2={"destip":"202.96.134.144","destport":"53","protocol":"tcpudp","targetport":"500"}
ttrue
```
Examples, delete a rule named proxy2
```shell
forward@dnat:proxy2=
ttrue
```
