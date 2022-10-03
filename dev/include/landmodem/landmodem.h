#ifndef H_MODEM_LANDMODEM_H
#define H_MODEM_LANDMODEM_H
/**
 * @brief modem相关的基本接口
 * @author dimmalex
 * @version 1.0
*/



/* usb tty device name find, return find device name, return NULL for nofound*/
const char *usbtty_device_find( const char *syspath, char *buf, int buflen );
/* usb tty device path list find, return >0 is find device number, return 0 for nofound*/
int         usbttylist_device_find( const char *syspath, char device[][NAME_MAX] );
/* usb ethernet device name find, return device name, return NULL for nofound */
const char *usbeth_device_find( const char *syspath, char *buf, int buflen );



/* lte object get */
const char *lte_object_get( const char *radio, const char *syspath, talk_t cfg, char *buf, int buflen );
/* lte object free */
void        lte_object_free( const char *object );



/* setup the device, 0 for oK, >0 for failed, <0 for error */
int usbtty_setup( atcmd_t fd, boole test );
/* cfun the device, 0 for oK, >0 for failed, <0 for error */
int usbtty_cfun1( atcmd_t fd, boole query );
/* disable cfun, 0 for oK, >0 for failed, <0 for error */
int usbtty_cfun0( atcmd_t fd );
/* get the cgsn 0 for succeed, >0 for failed, <0 for error */
int usbtty_cgsn( atcmd_t fd, talk_t status );
/* get the version 0 for succeed, >0 for failed, <0 for error */
int usbtty_cgmr( atcmd_t fd, talk_t status );

/* get the pin 0 for succeed, >0 for failed( 100 for pin, 101 or puk ), <0 for error */
int usbtty_cpin( atcmd_t fd, talk_t status, const char *pin );
/* get the imsi 0 for succeed, >0 for failed, <0 for error */
int usbtty_cimi( atcmd_t fd, talk_t status );
/* get the ccid 0 for succeed, >0 for failed, <0 for error */
int usbtty_ccid( atcmd_t fd, talk_t status );
/* get the ccid 0 for succeed, >0 for failed, <0 for error */
int usbtty_iccid( atcmd_t fd, talk_t status );

/* set the sms mode  0 for succeed, >0 for failed, <0 for error */
int usbtty_smsmode( atcmd_t fd, int set );
/* set the creg mode  0 for succeed, >0 for failed, <0 for error */
int usbtty_cregmode( atcmd_t fd, int set );
/* get the cgreg mode 0 for succeed, >0 for failed, <0 for error */
int usbtty_cgregmode( atcmd_t fd, int set );
/* get the cereg mode 0 for succeed, >0 for failed, <0 for error */
int usbtty_ceregmode( atcmd_t fd, int set );
/* set the cereg mode, 0 for succeed, >0 for failed, <0 for error */
int usbtty_c5gregmode( atcmd_t fd, int set );
/* set the cops format  0 for succeed, >0 for failed, <0 for error */
int usbtty_copsformat( atcmd_t fd, int set );

/* get the csq >0 for succeed, ==0 for failed, <0 for error */
int usbtty_csq( atcmd_t fd, int *csq );
/* get the register network status 0 for succeed, >0 for failed, <0 for error */
int usbtty_creg( atcmd_t fd, talk_t status );
/* get the register network status 0 for succeed, >0 for failed, <0 for error */
int usbtty_cgreg( atcmd_t fd, talk_t status );
/* get the register network status 0 for succeed, >0 for failed, <0 for error */
int usbtty_cereg( atcmd_t fd, talk_t status );
/* get the register nr network status, 0 for succeed, >0 for failed, <0 for error */
int usbtty_c5greg( atcmd_t fd, talk_t status );
/* get the network 0 for succeed, >0 for failed, <0 for error */
int usbtty_cops( atcmd_t fd, talk_t status );
/* sync the date, 0 for oK, >0 for failed, <0 for error */
int usbtty_cclk( atcmd_t fd, int *year, int *month, int *day, int *hour, int *min, int *sec, int *zone );

/* set the pdp param 0 for succeed, >0 for failed, <0 for error */
int usbtty_cgdcont( atcmd_t fd, const char *cid, const char *type, const char *apn, boole query );
/* get the qcrmcall connect ok, 0 for oK, >0 for failed, <0 for error */
int usbtty_qcrmcallok( atcmd_t fd );



#endif   /* ----- #ifndef H_MODEM_LANDMODEM_H  ----- */

