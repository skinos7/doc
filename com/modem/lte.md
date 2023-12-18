
***
## LTE/NR Modem Management
Management LTE modem

#### Configuration( modem@lte )
**modem@lte** is first LTE modem
**modem@lte2** is second LTE modem

```json
// Attributes introduction 
{
    // lock attributes
    "lock_imei":"lock imei",                   // [ "disable", "enable", IMEI ], enable: The IMEI detected for the first time will be locked
    "lock_imsi":"lock imsi",                   // [ "disable", "enable", IMEI ], enable will lock current imei
    "lock_pin":"simcard pin",                  // [ string ]
    "lock_nettype":"network type",             // [ "2g", "3g", "4g", "nsa", "sa" ]
    "lock_band":"lock band",                   // The format varies depending on the module
    "lock_cell":"lock cell",                   // The format varies depending on the module
    "gnss":"gps function",                     // [ "disable", "enable" ]
    "atport":"atport function",                // [ "disable", "enable" ]

    "custom_set":                              // custom at setting list at the modem setup
    {
        "AT command":"AT exeucte result"             // [ string ]:[ string ]
        // ...more AT command
    },
    "custom_watch":                            // custom at watch list at the modem watch
    {
        "AT command":"AT exeucte result"             // [ string ]:[ string ]
        // ...more AT command
    },

    // simcard dial attributes
    "need_simcard":"SIMcard must be detected",                                                 // [ "enable", "disable" ]
    "simcard_failed_threshold":"first failed to reset time",                                   // [ number ]
    "simcard_failed_threshold2":"second failed to reset time",                                 // [ number ]
    "simcard_failed_threshold3":"third failed to reset time",                                  // [ number ]
    "simcard_failed_everytime":"every failed to reset time",                                   // [ number ]
    
    // signal dial attributes
    "need_plmn":"must register to plmn",                                                       // [ "enable", "disable" ]
    "need_signal":"Signal must be effectivity",                                                // [ "enable", "disable" ]
    "signal_failed_threshold":"first failed to reset time",                                    // [ number ]
    "signal_failed_threshold2":"second failed to reset time",                                  // [ number ]
    "signal_failed_threshold3":"third failed to reset time",                                   // [ number ]
    "signal_failed_everytime":"every failed to reset time",                                    // [ number ]

    // watch attributes
    "watch_interval":"How often do query the modem",  // [ number ], the unit in second

    // profile attributes
    "profile":"custom the profile",            // [ "disable", "enable" ]
    "profile_cfg":                             // custom profile save here, the json be used when "profile" value is enable
    {
        "dial":"dial number",                     // [ number ]
        "cid":"dial CID",                         // [ number ], default is 1
        "type":"ip address type",                 // [ "ipv4", "ipv6", "ipv4v6" ]
        "auth":"authentication method",           // [ "pap", "chap", "papchap" ]
        "apn":"APN name",                         // [ string ]
        "user":"user name",                       // [ string ]
        "passwd":"user password",                 // [ string ]
        "cids":"multi CID settings",              // [ "disable", "enable" ], "enable" for set multi-CID for modem
        "cids_cfg":                               // settings of multi-CID save here, the json be used when "cids" value is enable
        {
            "CID number":                                 // [ number ]
            {
                "type":"ip address type",                 // [ "ipv4", "ipv6", "ipv4v6" ]
                "apn":"APN name",                         // [ string ]
                "user":"user name",                       // [ string ]
                "passwd":"user password",                 // [ string ]
            }
            //"CID nubmer ":{ CID profile }     How many CID profile need setting save how many properties
        }
    },

    // backup simcard configure
    "bsim":"backup simcard function",                         // [ "disable", "enable" ]
    "bsim_cfg":                                               // settings of backup simcard save here, the json be used when "bsim" value is enable
    {
        "mode":"Specify the simcard",                                                    // [ "auto", "bsim", "msim", "detect" ], "bsim" for backup simcard, "msim" for main simcard, "detect" the IO for auto that need detect IO support
        "signal_failed":"Check the signal failed how many times to switch the simcard",  // [ number ]
        "dial_failed":"connect to internet failed how many times to switch the simcard", // [ number ]
        "failover":"backup simcard usage duration",                                      // [ number ], the unit is second

        // backup simcard lock attributes
        "lock_imei":"lock imei",                   // [ "disable", "enable", IMEI ], "enable": The IMEI detected for the first time will be locked
        "lock_imsi":"lock imsi",                   // [ "disable", "enable", IMEI ], enable will lock current imei
        "lock_pin":"simcard pin",                  // [ string ]
        "lock_netmode":"network type",             // [ "2g", "3g", "4g", "nsa", "sa" ]
        "lock_band":"lock band",                   // The format varies depending on the module
        "lock_cell":"lock cell",                   // The format varies depending on the module

        // backup profile attributes
        "profile":"custom the profile",            // [ "disable", "enable" ]
        "profile_cfg":                             // custom profile save here, the json be used when "profile" value is enable
        {
            "dial":"dial number",                     // [ number ]
            "cid":"dial CID",                         // [ number ], default is 1
            "type":"ip address type",                 // [ "ipv4", "ipv6", "ipv4v6" ]
            "apn":"APN name",                         // [ string ]
            "user":"user name",                       // [ string ]
            "passwd":"user password",                 // [ string ]
            "cids":"multi CID settings",              // [ "disable", "enable" ], enable for set multi-CID for modem
            "cids_cfg":                                   // settings of multi-CID save here, the json be used when "cids" value is enable
            {
                "CID number":                                 // [ number ]
                {
                    "type":"ip address type",                 // [ "ipv4", "ipv6", "ipv4v6" ]
                    "apn":"APN name",                         // [ string ]
                    "user":"user name",                       // [ string ]
                    "passwd":"user password",                 // [ string ]
                }
                //"CID nubmer ":{ CID profile }     How many CID profile need setting save how many properties
            }
        }
    },

    // soft backup simcard configure
    "ssim":"soft backup simcard function",                         // [ "disable", "enable" ]
    "ssim_cfg":                                                    // settings of soft backup simcard save here, the json be used when "ssim" value is enable
    {
        "mode":"Specify the operator",                                                   // [ "signal", "plmn" ], "signal" for test and use the The best signal operator, "46000" for china mobile, "46001" china union, "46003" for china telecom
        "signal_failed":"Check the signal failed how many times to switch the simcard",  // [ number ]
        "dial_failed":"connect to internet failed how many times to switch the simcard", // [ number ]
    },

    // SMS
    "sms":"SMS function enable or disable",
    "sms_cfg":
    {
        "center":"SMS center number",                             // [ number ]
        "he":"enable or disable the he command",                  // [ "disable", "enable" ]
        "he_contact":"set a contact to send the he command",      // [ number ]
        "he_prefix":"set a prefix at the he command"              // [ string ]
    }

}
```

Examples, show all the first lte modem configure
```shell
modem@lte
{
 
    "lock_imei":"enable",              # The IMEI detected for the first time will be locked
    "lock_imsi":"460015356123463",     # the simcard imsi must be 460015356123463

    "gnss":"enable",                   # enbale the GPS function

    "profile":"enable",                # custom the profile
    "profile_cfg":
    {
        "dial":"*99#",                     # dial number is *99#
        "cid":"1",                         # dial CID is 1
        "type":"ipv4v6",                   # ip address type is ipv4 and ipv6
        "apn":"internet",                  # APN is internet
        "user":"card",                     # username is card
        "passwd":"card",                   # password is card
        "cids":"enable",                   # enable the settings for multi-CID
        "cids_cfg":                               # settings of multi-CID save here, the json be used when "cids" value is enable
        {
            "2":                                      # CID2 profile
            {
                "type":"ipv4v6",                         # CID2 ip address type is ipv4 and ipv6
                "apn":"internet2",                       # CID2 APN is internet2
                "user":"card",                           # CID2 username is card
                "passwd":"card",                         # CID2 password is card
            },
            "3":                                      # CID3 profile
            {
                "type":"ipv4v6",                        # CID3 ip address type is ipv4 and ipv6
                "apn":"internet3",                      # CID3 APN is internet3
                "user":"card",                          # CID3 username is card
                "passwd":"card",                        # CID3 password is card
            },
            "4":                                      # CID4 profile
            {
                "type":"ipv4v6",                        # CID4 ip address type is ipv4 and ipv6
                "apn":"internet4",                      # CID4 APN is internet4
                "user":"card",                          # CID4 username is card
                "passwd":"card",                        # CID4 password is card
            }                        
        }
    }
}
```  

Examples, enable the GNSS for first lte modem
```shell
modem@lte:gnss=enable
ttrue
```  

#### **Methods**
**modem@lte** is first LTE modem
**modem@lte2** is second LTE modem

+ `status[]` **get the lte modem infomation**, *succeed return talk to describes infomation, failed reeturn NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "state":"Current state",        // [ "setup", "register", "ready", "connecting", "connected", "reset" ]
                                             // "setup" for setup the modem
                                             // "register" for register the network
                                             // "ready" for ready to connect to internet, hint signal/network/simcard all ok
                                             // "connecting" for connect to the internet
                                             // "connected" for connect internet succeed
                                             // "reset" for reset the modem
        "mversion":"Modem version",     // [ string ]
        "imei":"IMEI numer",            // [ string ]
        "imsi":"IMSI number",           // [ string ]
        "iccid":"ICCID number",         // [ number, "nosim", "pin", "puk" ]
                                                // number for iccid
                                                // "nosim" for cannot found the simcard
                                                // "pin" for the simcard need PIN code
                                                // "puk" for the simcard pin error

        "plmn":"MCC and MNC",           // [ number, "noreg", "dereg" ]
                                                // number for MCC and MNC
                                                // "noreg" for cannot register to opeartor
                                                // "unreg" for cannot register to opeartor
                                                // "dereg" for register to operator be refused
        "netera":"technology Generation",// [ "2G", "3G", "4G", "5G" ], Optional
        "nettype":"network type",        // The format varies depending on the module
                                         // 2G usually shows GSM, GPRS, EDGE, CDMA
                                         // 3G usually shows WCDMA, EVDO, TDSCDMA, HSPA, HSDPA, HSUPA
                                         // 4G usually shows LTE, FDD, TDD

        
        "signal":"signal level",         // [ "0", "1", "2", "3", "4" ], "0" for no signal, "1" for weakest signal , "4" for strongest signal
        "csq":"CSQ number",              // [ number ]
        "rssi":"signal intensity",       // [ number ], the unit is dBm
        "rsrp":"RSRP value",             // Optional, The format varies depending on the module
        "rsrq":"RSRQ value",             // Optional, The format varies depending on the module
        "sinr":"sinr value",             // Optional, The format varies depending on the module 
        "band":"current band",           // Optional, The format varies depending on the module
        "pcid":"Physical Cell ID",       // [ number ], Optional

        "operator":"operator name",      // [ string ]
        "operator_advise":               // Recommended profile for PLMN
        {
            "name":"operator name",               
            "dial":"dial number",                     // [ number ]
            "cid":"dial CID",                         // [ number ], default is 1
            "type":"ip address type",                 // [ "ipv4", "ipv6", "ipv4v6" ]
            "apn":"APN name",                         // [ string ]
            "user":"user name",                       // [ string ]
            "passwd":"user password"                  // [ string ]
        }
    }
    ```

    ```shell
    # examples, get the first lte modem infomation
    modem@lte.status
    {
        "imei":"867160040494084",          # imei is 867160040494084
        "imsi":"460015356123463",          # imei is 460015356123463
        "iccid":"89860121801097564807",    # imei is 89860121801097564807
        "csq":"3",                         # CSQ nubmer is 3
        "signal":"3",                      # signal level is 3
        "state":"connect",                 # state is connect to the internet
        "plmn":"46001",                    # plmn is 46001
        "nettype":"WCDMA",                 # nettype is WCDMA
        "rssi":"-107",                     # signal intensity is -107
        "operator":"ChinaMobile",              # operator name is ChinaMobile
        "operator_advise":                 # recommended profile for ChinaMobile
        {
            "name":"ChinaMobile",                 # name is ChinaMobile
            "dial":"*99#",                     # dial number is *99#
            "apn":"3gnet"                      # APN is 3gnet
        }
    }
    ```

+ `reset[]` **reset the modem**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, reset the first lte modem
    modem@lte.reset
    ttrue
    # examples, reset the second lte modem
    modem@lte2.reset
    ttrue
    ```

+ `at[]` **at to the modem**, *succeed return ttrue and print the command result, failed return tfalse, error return terror*
    ```shell
    # examples, talk to first lte modem AT command for simcard state
    modem@lte.talk[at+cpin?]
    +CPIN: READY

    OK
    ttrue
    # examples, talk to second lte modem AT command for network state
    modem@lte2.talk[at+creg?]
    +CREG: 2,1,"A538","1EB3FB7",2

    OK
    ttrue
    ```

+ `siminfo[]` **get the modem simcard infomation**, *succeed return talk to describes simcard infomation, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "bsim_state":"current use which simcard",        // [ main or backup ]
        "bsim_iccid":"backup simcard iccid",             // [ string ]
        "bsim_imsi":"backup simcard imsi",               // [ string ]
        "msim_iccid":"main simcard iccid",               // [ string ]
        "msim_imsi":"main simcard imsi"                  // [ string ]
    }
    ```

    ```shell
    # examples, get the first lte modem simcard infomation
    modem@lte.siminfo
    {
        "bsim_state":"backup",
        "msim_iccid":"89860617040001496431",
        "msim_imsi":"460060014049643",
        "bsim_iccid":"89860121801097564807",
        "bsim_imsi":"460015356123463"
    }
    ```

+ `profile[]` **get the modem profile**, *succeed return talk to describes profile, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "name":"operator name",               // [ string ]
        "dial":"*dial number",                // [ string ]
        "apn":"APN code",                     // [ string ]
        "mtty":"modem tty device pathname"    // [ string ]
    }
    ```

    ```shell
    # examples, get the first lte modem profile
    modem@lte.profile
    {
        "name":"中国联通",
        "dial":"*99#",
        "apn":"3gnet",
        "mtty":"/dev/ttyUSB3"
    }
    ```

+ `shut[]` **shutdown the modem**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, shutdown the frist lte modem
    modem@lte.shut
    ttrue
    # examples, shutdown the second lte modem
    modem@lte2.shut
    ttrue
    ```

+ `setup[]` **setup the modem**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, setup the frist lte modem
    modem@lte.setup
    ttrue
    # examples, setup the second lte modem
    modem@lte2.setup
    ttrue
    ```



+ `smssend[ dest, content ]` **send a sms**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, use LTE1 send a hello to 13266606322
    modem@lte.smssend[ +8613266606322, hello ]
    ttrue
    # examples, use LTE2 send a "hello world" to 13266606322
    modem@lte2.smssend[ +8613266606322, "hello world" ]
    ttrue
    ```

+ `smslist[]` **list all sms**, *succeed return talk to describes sms list, failed return NULL, error return terror*
    ```shell
    # examples, list all sms on LTE1
    modem@lte.smslist
    {
        "lte.5ugPSw":
        {
            "id":"lte.5ugPSw",
            "contact":"8617688704240",
            "date":"23-12-18 22:50:30",
            "content":"看 ddddd"
        },
        "lte.Y9kWLV":
        {
            "id":"lte.Y9kWLV",
            "contact":"8617688704240",
            "date":"23-12-18 22:50:03",
            "content":"要   现的"
        },
        "lte.ovV6nw":
        {
            "id":"lte.ovV6nw",
            "contact":"8617688704240",
            "date":"23-12-18 22:49:22",
            "content":"看下午方便的话可以"
        },
        "lte.sTQ9x1":
        {
            "id":"lte.sTQ9x1",
            "contact":"8617688704240",
            "date":"23-12-18 22:51:22",
            "content":"iiik'帮"
        },
        "lte.uKyisL":
        {
            "id":"lte.uKyisL",
            "contact":"8617688704240",
            "date":"23-12-18 22:51:49",
            "content":"ss'ddd"
        }
    }
    ```

+ `smsdel[ sms id ]` **delete a sms**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, delete a sms on LTE1
    modem@lte.smsdel[ lte.5ugPSw ]
    ttrue
    ```


