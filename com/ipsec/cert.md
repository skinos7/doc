***
## Management of IPSEC server certificate
Management of IPSEC server certificate

#### **Methods**

+ `clear_ca[]` **delete ipsec server CA certificate**, *succeed return ttrue, failed return tfalse, error return terror*

+ `clear_cert[]` **delete ipsec server certificate**, *succeed return ttrue, failed return tfalse, error return terror*

+ `clear_key[]` **delete ipsec server private key**, *succeed return ttrue, failed return tfalse, error return terror*

+ `make_ca[]` **generate ipsec server CA certificate and CA private key**, *succeed return ttrue, failed return tfalse, error return terror*

+ `make_cert[]` **generate ipsec server certificate private key**, *succeed return ttrue, failed return tfalse, error return terror*

+ `list_key[]` **list ipsec server CA certificate/private key and certificate/private key file**, *succeed return talk to describes infomation, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "ca.crt":"CA certificate file pathname",
        "ca.key":"CA private key file pathname",
        "server.crt":"server certificate file pathname",
        "server.key":"server private key file pathname"
    }
    ```
    ```shell
    # examples, list ipsec server CA and server certificate/private key file
    ipsecs@cert.list_key
    {
        "ca.crt":"/var/.cfg/ovpns/ca.crt",                     // CA certificate
        "ca.key":"/var/.cfg/ovpns/ca.key",                     // CA private key
        "server.crt":"/var/.cfg/ovpns/server.crt",             // server certificate
        "server.key":"/var/.cfg/ovpns/server.key"              // server private key
    }
    ```

+ `delete_client[ client name ]` **delete ipsec client of server certificate and private key**, *succeed return ttrue, failed return tfalse, error return terror*
    
+ `add_client[ client name ]` **generate ipsec client of server certificate and private key**, *succeed return ttrue, failed return tfalse, error return terror*

+ `list_client[]` **list ipsec client of server certificate/private key**, *succeed return talk to describes infomation, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "client name":
        {
            "key":"client private key file pathname",
            "crt":"client certificate file pathname"
        }
        // ...more client
    }
    ```
    ```shell
    # examples, list ipsec client of server certificate/private key file
    ipsecs@cert.list_client
    {
        "test":                                          // client name is test
        {
            "key":"/var/.cfg/ipsecs/server.key.test",         // client test private key
            "crt":"/var/.cfg/ipsecs/server.crt.test"          // client test certificate
        },
        "test2":                                         // client name is test2
        {
            "crt":"/var/.cfg/ipsecs/server.crt.test2",        // client test2 private key
            "key":"/var/.cfg/ipsecs/server.key.test2"         // client test2 certificate
        }
    }
    ```

