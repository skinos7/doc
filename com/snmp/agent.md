
***
## Management of snmp agent
Management equipment snmp agent

#### Configuration( snmp@agent )

```json
// Attributes introduction 
{
    "status":"enable or disable",                // [ disable, enable ]
    "port":"UDP server port",                    // [ number ]

    "rocommunity":"read only community",         // [ string ]
    "rwcommunity":"read write community",        // [ string ]
    
    "v3":"snmp v3 privacy type",                 // [ disable, noauth, auth, privacy ]
    "username":"snmp v3 username",               // [ string ], the v3 must be "auth" or "privacy"
    "auth":"authentication type",                // [ MD5, SHA ], the v3 must be "auth" or "privacy"
    "password":"authentication password",        // [ string ], the v3 must be "auth" or "privacy"
    "privacy":"privacy type",                    // [ DES, AES ], the v3 must be "privacy"
    "key":"privacy password",                    // [ string ], the v3 must be "privacy"

    "custom":                                    // custom the oid shell in here
    {
        "oid name":                                  // [ string ], you can custom the rule name
        {
            "oid":"OID pathname",                    // [ string ]
            "cmd":"execute the command at shell"     // [ string ]
        }
    }


}
```
Examples, show all configure
```shell
snmp@agent
{
}
```  
Examples, modify the rocommunity to public
```shell
snmp@agent:rocommunity=public
ttrue
```  




