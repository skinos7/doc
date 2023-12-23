
***
## device management servic
component name is devport, user use the component methods to control the device
all methods need username

#### **Methods**

+ `list[ username, [group] ]` **get the device list of username**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    {
        "device mac address":
        {
        }
        // ... more device
    }    
    ```

+ `add[ username, device mac identify, [comment] ]` **add a device to server**, *succeed return tture, failed return tfalse, error return terror*

+ `delete[ username, device mac identify ]` **delete a device from server**, *succeed return tture, failed return tfalse, error return terror*

+ `status[ username, device mac identify ]` **get the device list of username**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    ```

+ `getconfig[ username, device mac identify ]` **get the device list of username**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    ```

+ `setconfig[ username, device mac identify, { device configure } ]` **delete a device from server**, *succeed return tture, failed return tfalse, error return terror*


+ `port_map[ username, device mac identify, extern port, local ip, local port ]` **get the device list of username**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    ```

+ `port_unmap[ username, device mac identify, extern port ]` **delete a device from server**, *succeed return tture, failed return tfalse, error return terror*


+ `firmware_list[ username ]` **get the device list of username**, *succeed return talk to describes, failed return NULL, error return terror*
    ```json
    // Attributes introduction of talk by the method return
    ```

+ `firmware_add[ username, pathname ]` **delete a device from server**, *succeed return tture, failed return tfalse, error return terror*

+ `firmware_delete[ username, pathname ]` **delete a device from server**, *succeed return tture, failed return tfalse, error return terror*

