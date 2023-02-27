***
## TTL settings
Management of out packet TTL

#### Configuration( forward@ttl )

```json
// Attributes introduction 
{
    "mode":"mode fo ttl settings",     # [ "none", "fix", "inc", "dec" ], ttl modify mode
    "fix":"output packet TTL settings",# [ number ], vaild when "mode" be "fix"
    "inc":"increase the TTL",          # [ number ], vaild when "mode" be "inc"
    "dec":"reduce the TTL"             # [ number ], vaild when "mode" be "dec"
}
```

Examples, show current all of ttl configure
```shell
forward@ttl
{
    "mode":"fix",     # fix the output packet ttl
    "fix":"99",       # ttl number is 99
}
```  
