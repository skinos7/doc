***
## MODBUS slave driver components
Manage modbus slave driver. used by uart@modbusm, usually modbusdrv@xxx for name, the xxx can be custom with sensor model

#### **configuration( modbusm@xxx )**

```json
// Attribute introduction
{
    "mstcom":"at which uart device",                // [ string ], default work on every uart device which mode is uart@modbusm

    "addr":"slave address on modbus",               // [ number ]

    "devcom":"which modbus driver use",             // [ string ], default is the configure name

    "devcom":"register which sensor device",        // [ string ]

    "options":                         // options list
    {
        "option name":                     // [ string ]
        {
            "op":"operation id",               // [ number ]
            "reg":"slave register",            // [ number ]
            "num":"read number of item",       // [ number ]
    
            "timeout":"timeout of response",   // [ number ], the unit is millisecond
            "interval":"read interval",        // [ number ], the unit is millisecond
            "lost":"failed time to call com"   // [ number ]
        }
        // ... more options
    },

    "operation name":               // [ string ]
    {
        "op":"operation id",               // [ number ]
        "reg":"slave register",            // [ number ]
        "num":"write number of item",      // [ number ]
        "value":"write byte hex",          // [ hex string ]
        "timeout":"timeout of response"    // [ number ], the unit is millisecond
    }
    // ... more options

}

```


