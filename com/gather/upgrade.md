***
## Upgrading Components in Batches on lcoal network
upgrade the Skinos system on local network

#### Configuration( gather@upgrade )

```json
// Attributes introduction
{
    "status":"enable or disable the function",                                    // [ "disable", "enable" ]

    "root":"directory for storing the upgrade package",                           // [ string ], default is /mnt
    "upgrade":"upgrade configuration file in the upgrade package directory",      // [ string ], default is upgrade.txt

    "device":"specifies device for TFTP upgrade at bootloader",                  // [ string ], default is local_device register of land
    "ip":"specifies the IP address used for the TFTP upgrade at bootloader",     // [ IP address ], default is 10.10.10.3
    "mask":"specifies the IP netmask used for the TFTP upgrade at bootloader",   // [ network mask ], default is 255.255.255.0

    // will save to upgrade.txt, and pass to device that need upgrade
    "config":
    {
        "model":"upgrade model",                         // [ string ], defualt is no modify 
        "cmodel":"upgrade custom model",                 // [ string ], defualt is no modify 
        "language":"upgrade language",                   // [ string ], defualt is no modify, cn is chinese, en is engish
        "datecode":"upgrade datecode",                   // [ string ], defualt is no modify
        "default":"default the configure after upgrade", // [ "disable", "enable" ]
        "product_test":"test the device after upgrade",  // [ string ], test option can togather, ex: 4g;5g;nic;reset
                                                                        // 4g for test the LTE
                                                                        // 5g for test the LTE2
                                                                        // nic for test the LAN/WAN connection
                                                                        // reset for test the reset button
                                                                        // online for test the extern connection
                                                                        // ping for test the ping 114.114.114.114

        "zz":"current upgrade firmware",                 // [ string ], cannot modify
        "version":"current upgrade firmware version",    // [ string ], cannot modify
        "scope":"current upgrade firmware scope"         // [ string ], coanot modify
    }
}
```
Examples, show all the configure
```shell
gather@upgrade
{
    "status":"disable",           # disable the upgrade
    "root":"/mnt",                # firmware file store in /mnt
    "upgrade":"upgrade.txt",      # upgrade configure file is upgrade.txt
    "ip":"10.10.10.3",            # tftp server ip 10.10.10.3 for device upgrade at bootloader
    "mask":"255.255.255.0",        # tftp server ip mask is 255.255.255.0 for device upgrade at bootloader
    "config":
    {
        "model":"D218P",                                # modify the upgrade devcie model to D218P
        "cmodel":"V518",                                # modify the upgrade devcie cmodel to V518

        "language":"en",                                # modify the upgrade devcie language to engish
        "datecode":"20221025",                          # modify the upgrade devcie datecode to 20221025

        "default":"enable",                             # default the device after upgrade
        "product_test":"4g;5g;"                         # test the LTE and LTE2

        "zz":"mt7628_d218_zwzx_v7.1022.zz",       # current upgrade firmware is mt7628_d218_zwzx_4.3.3w-060521.zz
        "version":"v7.1022",                      # upgrade firmware version is 
        "scope":"std"                             # current release scope is std
    }
}
```  
Examples, enable the upgrade
```shell
gather@upgrade:status=enable
ttrue
```  

#### **Methods**

+ `list[]` **list all the found firmware**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "filename":
        {
            "dir":"directory pathname",
            "scope":"scope identify",
            "version":"version identify",
            "zz":"filename"
        }
        // ... more firmware
    }    
    ```
    ```shell
    # examples, get all the found device
    gather@beacon.list
    {
        "mt7628_d218_h728_v7.2.0915.zz":
        {
            "dir":"/mnt/mmcblk0p1",
            "scope":"h728",
            "version":"v7.2.0915",
            "zz":"mt7628_d218_h728_v7.2.0915.zz"
        },
        "mt7628_d218_std_v7.2.0916.zz":
        {
            "dir":"/mnt/mmcblk0p1",
            "scope":"std",
            "version":"v7.2.0916",
            "zz":"mt7628_d218_std_v7.2.0916.zz"
        },
        "mt7621_h721_std_v7.2.1023.zz":
        {
            "dir":"/mnt/mmcblk0p1",
            "scope":"std",
            "version":"v7.2.1023",
            "zz":"mt7621_h721_std_v7.2.1023.zz"
        }
    }  
    ```

+ `switch[ firmware filename ]` **switch the firmware to upgrade auto**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, switch to upgrade mt7628_d218_std_v7.2.0916.zz auto
    gather@upgrade.switch[ mt7628_d218_std_v7.2.0916.zz ]
    ttrue
    ```

+ `import[ firmware filename ]` **import the firmware to upgrade list**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, import mt7628_d218_std_v7.2.0923.zz
    gather@upgrade.import[ mt7628_d218_std_v7.2.0923.zz ]
    ttrue
    ```

+ `delete[ firmware filename ]` **delete the firmware from upgrade list**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, delete mt7621_h721_std_v7.2.1023.zz
    gather@upgrade.delete[ mt7621_h721_std_v7.2.1023.zz ]
    ttrue
    ```

