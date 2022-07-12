***
## 应用层网关组件（forward@alg） 
此组件为管理应用层网关, 默认表示所有的应用层网关开启, 此功能只会在路由模式(即网关,4G,无线互联网,宽带路由器等)下工作

#### **配置** 
```json
{
    "amanda":"enable",            // amanda应用网关：enable表示开启， disable表示禁用
    "ftp":"enable",            // FTP应用网关：enable表示开启， disable表示禁用
    "h323":"enable",          // H323应用网关：enable表示开启， disable表示禁用
    "irc":"enable",          // IRC应用网关：enable表示开启， disable表示禁用
    "pptp":"enable",          // PPTP应用网关：enable表示开启， disable表示禁用
    "gre":"enable",          // GRE应用网关：enable表示开启， disable表示禁用
    "sip":"enable",         // SIP应用网关：enable表示开启， disable表示禁用
    "rtsp":"enable",       // RTSP应用网关：enable表示开启， disable表示禁用
    "snmp":"enable",       // SNMP应用网关：enable表示开启， disable表示禁用
    "tftp":"enable",       // TFTP应用网关：enable表示开启， disable表示禁用
    "udplite":"enable"     // UDP Lite应用网关：enable表示开启， disable表示禁用
}
```


