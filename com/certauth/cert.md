***
## Management of certificate Authority
Management of certificate Authority

#### **Methods**

+ `clear_ca[]` **delete CA certificate**, *succeed return ttrue, failed return tfalse, error return terror*

+ `clear_cert[]` **delete server certificate**, *succeed return ttrue, failed return tfalse, error return terror*

+ `clear_key[]` **delete server private key**, *succeed return ttrue, failed return tfalse, error return terror*

+ `clear_tlskey[]` **delete server TLS key**, *succeed return ttrue, failed return tfalse, error return terror*

+ `clear_statickey[]` **delete server static key**, *succeed return ttrue, failed return tfalse, error return terror*

+ `clear_dh[]` **delete server Diffie-Hellman parameter**, *succeed return ttrue, failed return tfalse, error return terror*


+ `make_ca[]` **generate CA certificate and CA private key**, *succeed return ttrue, failed return tfalse, error return terror*

+ `make_cert[]` **generate server certificate private key**, *succeed return ttrue, failed return tfalse, error return terror*

+ `make_tlskey[]` **generate server TLS key**, *succeed return ttrue, failed return tfalse, error return terror*

+ `make_statickey[]` **generate server static key**, *succeed return ttrue, failed return tfalse, error return terror*

+ `make_dh[]` **generate server Diffie-Hellman parameter**, *succeed return ttrue, failed return tfalse, error return terror*

+ `list_key[]` **list server CA certificate/private key and certificate/private key file**, *succeed return talk to describes infomation, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "ca.crt":"CA certificate file pathname",
        "ca.key":"CA private key file pathname",
        "server.crt":"server certificate file pathname",
        "server.key":"server private key file pathname",
        "server.tlskey":"server TLS key file pathname",
        "server.statickey":"server static key file pathname",
        "server.dh2048":"server Diffie-Hellman parameter file pathname"
    }
    ```
    ```shell
    # examples, list server CA and server certificate/private key file
    certauth@cert.list_key
    {
        "ca.crt":"/mnt/config/certauth/ca.crt",                     // CA certificate
        "ca.key":"/mnt/config/certauth/ca.key",                     // CA private key
        "server.crt":"/mnt/config/certauth/server.crt",             // server certificate
        "server.key":"/mnt/config/certauth/server.key",             // server private key
        "server.tlskey":"/mnt/config/certauth/server.tlskey",       // TLS key
        "server.statickey":"/mnt/config/certauth/server.statickey", // static key
        "server.dh2048":"/mnt/config/certauth/server.dh2048"        // Diffie-Hellman parameter
    }
    ```


+ `delete_client[ client name ]` **delete client of server certificate and private key**, *succeed return ttrue, failed return tfalse, error return terror*
    
+ `add_client[ client name ]` **generate client of server certificate and private key**, *succeed return ttrue, failed return tfalse, error return terror*

+ `list_client[]` **list client of server certificate/private key**, *succeed return talk to describes infomation, failed return NULL, error return terror*
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
    # examples, list client of server certificate/private key file
    certauth@cert.list_client
    {
        "test":                                          // client name is test
        {
            "key":"/mnt/config/ovpns/server.key.test",         // client test private key
            "crt":"/mnt/config/ovpns/server.crt.test"          // client test certificate
        },
        "test2":                                         // client name is test2
        {
            "crt":"/mnt/config/ovpns/server.crt.test2",        // client test2 private key
            "key":"/mnt/config/ovpns/server.key.test2"         // client test2 certificate
        }
    }
    ```

