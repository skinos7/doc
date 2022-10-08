***

## Management of register component
Each component can have a number of registers, can be used to hold information about the component itself or to communicate with other components, all register value will be lost when system restart


#### **Methods**

+ `list[ component ]` **list all register**, show specified component register list, *succeed return talk, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "register name":"register value size in byte"
        // ... more register list
    }    
    ```
    ```shell
    # examples, get component ifname@wan register list
    register.list[ifname@wan]
    {
        "ifdev":"20",                    // named ifdev register size is 20 byte
        "tid":"4",                       // named tid register size is 4 byte
        "mode":"20",                     // named mode register size is 20 byte
        "method":"20",
        "connect_failed":"4",
        "netdev":"20",
        "keeplive":"20",
        "metric":"20",
        "custom_dns":"20",
        "dns":"20",
        "dns2":"20",
        "delay_buf":"240",
        "delay_pos":"4",
        "delay":"4"
    }
    ```

+ `set_int[ component, register name, value ]` **set a integer value to register**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, set 5 to tid of ifname@wan component
    register.set_int[ifname@wan, tid, 5]
    ttrue
    ```
+ `int[ component, register name ]` **show register value in integer**, *succeed return number, failed return NULL, error return terror*
    ```shell
    # examples, show the tid of ifname@wan component
    register.int[ifname@wan, tid]
    5
    ```

+ `set_boole[ component, register name, value ]` **set a boolean value to register**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, set true to myreg of ifname@wan component
    register.set_boole[ifname@wan, myreg, true]
    ttrue
    ```
+ `boole[ component, register name ]` **show register value in boole**, *succeed return true or false, failed return NULL, error return terror*
    ```shell
    # examples, show the myreg of ifname@wan component
    register.boole[ifname@wan, myreg]
    true
    ```

+ `set_char[ component, register name, value ]` **set character value to register**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, set b to myreg2 of ifname@wan component
    register.set_char[ifname@wan, myreg2, b]
    ttrue
    ```
+ `char[ component, register name ]` **show register value in character**, *succeed return character, failed return NULL, error return terror*
    ```shell
    # examples, show the myreg2 of ifname@wan component
    register.char[ifname@wan, myreg2]
    b
    ```

+ `set_string[ component, register name, value ]` **set string value to register**, *succeed return ttrue, failed return tfalse, error return terror*
    ```shell
    # examples, set myreg3valueisnull to myreg3 of ifname@wan component
    register.set_string[ifname@wan, myreg3, myreg3valueisnull ]
    ttrue
    ```
+ `string[ component, register name ]` **show register value in string**, *succeed return string, failed return NULL, error return terror*
    ```shell
    # examples, show the mode register of ifname@wan component
    register.string[ifname@wan, myreg3]
    myreg3valueisnull
    ```
