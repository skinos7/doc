
## firmware management API   
firmware management API, depend on devport   
*all methods need username*   

#### **Methods**   

+ `firmware_list[ username ]` **get the device firmware list of username**, *succeed return talk to describes, failed return NULL, error return terror*   
    ```json
    // Attributes introduction of talk by the method return
    // that file save at $user/firmware
    {
        "firmware file name":                        // [ string ]:{}
        {
            "dir":"firmware directory",                   // [ string ]
            "custom":"firmware custom identify",          // [ string ]
            "scope":"firmware scope identify",            // [ string ]
            "version":"firmware version",                 // [ string ]
            "zz":"firmware file name"                     // [ string ]
        }
        // ... more firmware
    }    
    ```   

+ `firmware_add[ username, pathname ]` **add a firmware file**, *succeed return tture, failed return tfalse, error return terror*   

+ `firmware_delete[ username, filename ]` **delete a firmware**, *succeed return tture, failed return tfalse, error return terror*   

