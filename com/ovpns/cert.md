***
## Management of OPENVPN server certificate
Management of OPENVPN server certificate

#### **Methods**

+ `clear_ca[]` **delete openvpn server CA certificate**, *succeed return ttrue, failed return tfalse, error return terror*

+ `clear_cert[]` **delete openvpn server certificate**, *succeed return ttrue, failed return tfalse, error return terror*

+ `clear_key[]` **delete openvpn server private key**, *succeed return ttrue, failed return tfalse, error return terror*

+ `clear_tlskey[]` **delete openvpn server TLS key**, *succeed return ttrue, failed return tfalse, error return terror*

+ `clear_statickey[]` **delete openvpn server static key**, *succeed return ttrue, failed return tfalse, error return terror*

+ `clear_dh[]` **delete openvpn server Diffie-Hellman parameter**, *succeed return ttrue, failed return tfalse, error return terror*


+ `make_ca[]` **generate openvpn server CA certificate and CA private key**, *succeed return ttrue, failed return tfalse, error return terror*

+ `make_cert[]` **generate openvpn server certificate private key**, *succeed return ttrue, failed return tfalse, error return terror*

+ `make_tlskey[]` **generate openvpn server TLS key**, *succeed return ttrue, failed return tfalse, error return terror*

+ `make_statickey[]` **generate openvpn server static key**, *succeed return ttrue, failed return tfalse, error return terror*

+ `make_dh[]` **generate openvpn server Diffie-Hellman parameter**, *succeed return ttrue, failed return tfalse, error return terror*

+ `list_key[]` **list openvpn server CA certificate/private key and certificate/private key file**, *succeed return talk to describes infomation, failed return NULL, error return terror*
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
    # examples, list openvpn server CA and server certificate/private key file
    ovpns@cert.list_key
    {
        "ca.crt":"/var/.cfg/ovpns/ca.crt",                     // CA certificate
        "ca.key":"/var/.cfg/ovpns/ca.key",                     // CA private key
        "server.crt":"/var/.cfg/ovpns/server.crt",             // server certificate
        "server.key":"/var/.cfg/ovpns/server.key",             // server private key
        "server.tlskey":"/var/.cfg/ovpns/server.tlskey",       // TLS key
        "server.statickey":"/var/.cfg/ovpns/server.statickey", // static key
        "server.dh2048":"/var/.cfg/ovpns/server.dh2048"        // Diffie-Hellman parameter
    }
    ```


+ `delete_client[ client name ]` **delete openvpn client of server certificate and private key**, *succeed return ttrue, failed return tfalse, error return terror*
    
+ `add_client[ client name ]` **generate openvpn client of server certificate and private key**, *succeed return ttrue, failed return tfalse, error return terror*

+ `list_client[]` **list openvpn client of server certificate/private key**, *succeed return talk to describes infomation, failed return NULL, error return terror*
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
    # examples, list openvpn client of server certificate/private key file
    ovpns@cert.list_client
    {
        "test":                                          // client name is test
        {
            "key":"/var/.cfg/ovpns/server.key.test",         // client test private key
            "crt":"/var/.cfg/ovpns/server.crt.test"          // client test certificate
        },
        "test2":                                         // client name is test2
        {
            "crt":"/var/.cfg/ovpns/server.crt.test2",        // client test2 private key
            "key":"/var/.cfg/ovpns/server.key.test2"         // client test2 certificate
        }
    }
    ```

