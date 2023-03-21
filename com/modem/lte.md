
***
## LTE modem Management
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
        "mode":"Specify the simcard",                                                    // [ "auto", "bsim", "msim" ], "bsim" for backup simcard, "msim" for main simcard
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
Examples, show all the lte modem configure
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
Examples, enable the GNSS for lte modem
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
    # examples, get the first modem infomation
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
        "operator":"中国联通",             # operator name is 中国联通
        "operator_advise":                 # recommended profile for 中国联通
        {
            "name":"中国联通",                 # name is 中国联通
            "dial":"*99#",                     # dial number is *99#
            "apn":"3gnet"                      # APN is 3gnet
        }
    }
    ```

+ `reset[]` **reset the modem**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, reset the first modem
    modem@lte.reset
    ttrue
    # examples, reset the second modem
    modem@lte2.reset
    ttrue
    ```

+ `at[]` **at to the modem**, *succeed return ttrue and print the command result, failed return tfalse, error return terror*
    ```shell
    # examples, talk to first modem AT command for simcard state
    modem@lte.talk[at+cpin?]
    +CPIN: READY

    OK
    ttrue
    # examples, talk to second modem AT command for network state
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
    # examples, get the first modem simcard infomation
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
    # examples, get the second modem profile
    modem@lte2.profile
    {
        "name":"中国联通",
        "dial":"*99#",
        "apn":"3gnet",
        "mtty":"/dev/ttyUSB3"
    }
    ```

+ `shut[]` **shutdown the modem**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, shutdown the frist modem
    modem@lte.shut
    ttrue
    ```

+ `setup[]` **setup the modem**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, setup the frist modem
    modem@lte.setup
    ttrue
    ```

