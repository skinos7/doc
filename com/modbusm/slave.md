***
## MODBUS slave option components
Manage modbus slave option. call by uart@modbusm, Usually modbusm@xxx for name, the xxx can be custom

#### **configuration( modbusm@xxx )**

```json
// Attribute introduction
{
    "status":"work or not",            // [ "enable", "disable" ]

    "options":                         // options list
    {
        "option name":                     // [ string ]
        {
            "op":"operation id",               // [ "bits", "regs" ]
            "addr":"slave address",            // [ number ]
            "reg":"slave register",            // [ number ]
            "num":"read number of byte",       // [ number ]
    
            "timeout":"timeout of response",   // [ number ], the unit is millisecond
            "interval":"read interval",        // [ number ], the unit is millisecond
            "lost":"failed time to call com",  // [ number ]
    
            "com":"com pathname"               // [ string ]
            "method":"com method"              // [ string ]
        }
        // ... more options
    }
}

```


