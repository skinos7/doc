***
## VRRP management components
Manage VRRP

#### **configuration( ha@vrrp )**

```json
// Attribute introduction
{
    "status":"VRRP status",        // [ "enable", "disable" ]
    "mode":"work mode",            // [ "master", "backup" ]

    "id":"router identify",        // [ number ]
    "priority":"router priority",  // [ number ]
    "advert":"router advert time", // [ nubmer ], the unit is second
    "nopreempt":"no preempt",      // [ "disable", "enable" ]
    "auth":"auth password",        // [ string ]
    "vip":"virtual ip and mask"    // [ ip address/mask ], ex. "192.168.8.254/24"
}


