#ifndef  H_LAND_LANDHEAD_H
#define  H_LAND_LANDHEAD_H

/**
 * @file skinhead.h
 * @author dimmalex@gmail.com
 * @version 7.0
 * @date 20220219
 * @brief skinos system commom macro
 * @details define the marco for common length/file/type/mode/project/components, include the skin system header file
 * @see his brother stdhead.h and his child skin.h
 * @note define boole data type, redefine the false and true value
 */



/// identify max length macro
#ifndef NAME_MAX
#define NAME_MAX             (256)
#endif
/// pathname max length macro
#ifndef PATH_MAX
#define PATH_MAX             (512)
#endif
/// command line max length macro
#ifndef LINE_MAX
#define LINE_MAX             (1024)
#endif
/// command line max options macro
#ifndef LINE_OPTIONS_MAX
#define LINE_OPTIONS_MAX     (24)
#endif
/// component command line max length macro
#define COM_PARAMLINE_MAX 10240



/// default file mode
#define REGULAR_FILE_MODE (0660)
/// default directory mode
#define REGULAR_DIR_MODE (0770)



/// redefine the true
#ifdef true
    #undef true
#endif
#define true 1
/// redefine the false
#ifdef false
    #undef false
#endif
#define false 0
/// define boole data type for boolean
typedef int boole;
/// define project and component gap
#define PROJECT_OBJECT_GAPS "@"
#define PROJECT_OBJECT_GAPC '@'
/// define component and interface gap
#define OBJECT_METHOD_GAPS "."
#define OBJECT_METHOD_GAPC '.'
/// define method and parameter gap
#define METHOD_PARAM_STARTS "["
#define METHOD_PARAM_STARTC '['
#define METHOD_PARAM_ENDS "]"
#define METHOD_PARAM_ENDC ']'
/// define parameter and parameter gap
#define PARAM_PARAM_GAPS ","
#define PARAM_PARAM_GAPC ','
/// define component and configure gap
#define OBJECT_CONFIG_GAPS ":"
#define OBJECT_CONFIG_GAPC ':'
/// define configure and configure gap
#define CONFIG_CONFIG_GAPS "/"
#define CONFIG_CONFIG_GAPC '/'



/// platform driver project
#define PDRIVER_PROJECT "pdriver"
/// hardware project
#define ARCH_PROJECT "arch"
/// core project
#define LAND_PROJECT "land"

/** device data management component */
#define GPIO_COM "arch@gpio"
#define DATA_COM "arch@data"
#define CONFIG_COM "arch@config"
#define FIRMWARE_COM "arch@firmware"
/** hardware platform network management component */
#define NET_CONFIG "arch@net"
#define ETHERNET_COM "arch@ethernet"
/** hardware platform usb management component */
#define USB_COM "arch@usb"
#define USB_PROJECT "usb"
/** hardware platform pci management component */
#define PCI_COM "arch@pci"
#define PCI_PROJECT "pci"
/** hardware platform sdio management component */
#define SDIO_COM "arch@sdio"
#define SDIO_PROJECT "sdio"
/** system custom management component */
#define CUSTOM_COM "arch@custom"
/** configure lock management component */
#define LOCK_COM "arch@lock"

/** machine basic property management component */
#define MACHINE_COM "land@machine"
/** service management component */
#define SERVICE_COM "land@service"
/** fpk management component */
#define FPK_COM "land@fpk"
/** init/uninit management component */
#define INIT_COM "land@init"
#define UNINIT_COM "land@uninit"
/** joint management component */
#define JOINT_COM "land@joint"
/** auth management component */
#define AUTH_COM "land@auth"
/** date management component */
#define DATE_COM "clock@date"

/** telnet management component */
#define TELNETD_COM "tui@telnet"
/** ssh management component */
#define SSHD_COM "tui@ssh"
/** web ui management component */
#define WEBS_PROJECT "webs"
#define WUI_PROJECT "wui"
#define WUI_COM "wui@admin"


/** network management component */
#define NETWORK_MODE "default"
#define NETWORK_PROJECT "network"
#define NETWORK_COM "network@frame"
#define IFNAME_NAME "ifname"
#define LAN_COM IFNAME_NAME"@lan"
#define LAN1_COM IFNAME_NAME"@lan1"
#define LAN2_COM IFNAME_NAME"@lan2"
#define LAN3_COM IFNAME_NAME"@lan3"
#define LAN4_COM IFNAME_NAME"@lan4"
#define WLTE_COM IFNAME_NAME"@lte"
#define WLTE2_COM IFNAME_NAME"@lte2"
#define WLTE3_COM IFNAME_NAME"@lte3"
#define WLTE4_COM IFNAME_NAME"@lte4"
#define WAN_COM IFNAME_NAME"@wan"
#define WAN2_COM IFNAME_NAME"@wan2"
#define WAN3_COM IFNAME_NAME"@wan3"
#define WAN4_COM IFNAME_NAME"@wan4"
#define WISP_COM IFNAME_NAME"@wisp"
#define WISP2_COM IFNAME_NAME"@wisp2"
#define WNIC_COM IFNAME_NAME"@nic"
#define WNIC2_COM IFNAME_NAME"@nic2"
#define WNIC3_COM IFNAME_NAME"@nic3"
#define WNIC4_COM IFNAME_NAME"@nic4"
#define KEEPLIVE_COM "network@keeplive"
#define BRIDGE_COM "network@bridge"
#define BRIDGE_NAME "bridge"
#define VLAN_COM "network@vlan"
#define VLAN_NAME "vlan"
#define MASQ_CHAIN "masq"
#define NAT_COM "forward@nat"
#define FIREWALL_COM "forward@firewall"



/// wifi management component
#define WIFI_PROJECT "wifi"
#define WIFIDRV_PROJECT "wifidrv"         // wifi driver project( include usb driver or pci driver or sdio driver )
#define NRADIO_COM "wifi@n"
#define NSSID_COM "wifi@nssid"
#define NSSID2_COM "wifi@nssid2"
#define NSTA_COM "wifi@nsta"
#define ARADIO_COM "wifi@a"
#define ASSID_COM "wifi@assid"
#define ASSID2_COM "wifi@assid2"
#define ASTA_COM "wifi@asta"

/** modem management component */
#define MODEM_PROJECT "modem"             // modem project
#define MODEMDRV_PROJECT "modemdrv"       // modem driver project( include usb driver or pci driver )
#define MODEM_COM "modem@device"          // modem management
#define OPERATOR_COM "modem@operator"     // operator management
#define BSIM_COM "modem@bsim"             // modem backup simcard management
#define SMS_COM "modem@sms"               // modem sms management
#define LTE_COM "modem@lte"               // modem object
#define LTE2_COM "modem@lte2"             // modem object

/** netcard management component */
#define NETCARD_PROJECT "netcard"                // network inetface card(NIC) project
#define NETCARDDRV_PROJECT "netcarddrv"          // network inetface card(NIC) driver project( include usb driver or pci driver )
#define NETCARD_COM "netcard@device"             // network inetface card(NIC) management
#define NIC_COM "netcard@nic"                    // network inetface card(NIC) object
#define NIC2_COM "netcard@nic2"                  // network inetface card(NIC) object

/** uart management component */
#define UART_PROJECT "uart"                // uart project
#define UART_COM "uart@frame"              // uart management
#define SERIAL_COM "uart@serial"           // uart object
#define SERIAL2_COM "uart@serial2"         // uart object
#define SERIAL3_COM "uart@serial3"         // uart object
#define SERIAL4_COM "uart@serial4"         // uart object
#define SERIAL_CONVERT_PROJECT "uartgain"  // uart convert proejct

/** uart modbus management component */
#define MODBUSDRV_PROJECT "modbusdrv"      // modbus slave driver project

/** sensor device management component */
#define SENSOR_PROJECT "sensor"



/** gnss management component */
#define GNSS_PROJECT "gnss"                // gnss project
#define NMEA_COM "gnss@nmea"               // gnss object



/** station/client management component */
#define STATION_COM "client@station"
#define STATION_GLOBAL_COM "client@global"
#define STATION_DEFAULT_COM "client@default"
#define STATION_DHCPS_COM "client@dhcps"
#define STATION_ACL_COM "client@acl"
#define STATION_LIMIT_COM "client@limit"
#define STATION_FILTER_COM "client@filter"
#define STATION_TC_COM "client@tc"



/** agent local component */
#define AGENT_LOCAL_COM "agent@local"
/** agent factory component */
#define AGENT_FACTORY_COM "agent@factory"



/// system important path
#if defined gPLATFORM__host || defined gPLATFORM__shost
	#define PROJECT_TMP_DIR "/tmp/skin"
	#define PROJECT_VAR_DIR "/var/skin"
	#define PROJECT_LIB_DIR "/usr/local/lib"
	#define PROJECT_BIN_DIR "/usr/local/bin"
	#define PROJECT_ETC_DIR "/etc"
	#define PROJECT_MNT_DIR PROJECT_VAR_DIR"/mnt"
#else
	#define PROJECT_TMP_DIR "/tmp"
	#define PROJECT_VAR_DIR "/var"
	#define PROJECT_LIB_DIR "/var/lib"
	#define PROJECT_BIN_DIR "/var/bin"
	#define PROJECT_ETC_DIR "/etc"
	#define PROJECT_MNT_DIR "/mnt"
#endif
#define PROJECT_DIR "/prj"
#define PROJECT_CONF_DIR PROJECT_VAR_DIR"/.conf"
#define PROJECT_REG_DIR PROJECT_VAR_DIR"/.reg"
#define PROJECT_SER_DIR PROJECT_VAR_DIR"/.ser"
#define PROJECT_COM_DIR PROJECT_VAR_DIR"/.com"
#define PROJECT_OEM_DIR PROJECT_VAR_DIR"/.oem"
#define PROJECT_CFG_DIR PROJECT_MNT_DIR"/config"
#define PROJECT_INT_DIR PROJECT_MNT_DIR"/internal"
#define PROJECT_APP_DIR PROJECT_MNT_DIR"/internal/prj"
#define PROJECT_DEF_DIR PROJECT_MNT_DIR"/internal/def"
#define SHELL_METHOD_HEADER PROJECT_DIR"/land/method.sh"
#define SHELL_SERVICE_HEADER PROJECT_DIR"/land/service.sh"
#define DAEMON_PID_FILE PROJECT_VAR_DIR"/.daemon.pid"



/// system important filename
#define RANDOM_FILENAME  "/var/.urandom"
#define CRACKID_MAC "00:01:02:03:04:00"



/// include important header file
#include "link.h"
#include "syslog.h"
#include "talk.h"
#include "param.h"
#include "path.h"
#include "misc.h"
#include "register.h"
#include "config.h"
#include "project.h"
#include "com.h"
#include "service.h"
#include "he2com.h"
#include "reactor.h"



#endif   /* ----- #ifndef H_LAND_LANDHEAD_H  ----- */

