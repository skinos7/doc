#ifndef H_NETWORK_LANDNET_H
#define H_NETWORK_LANDNET_H
/**
 * @brief 网络相关的基本接口
 * @author dimmalex
 * @version 1.0
*/

#define ETC_HOSTS_FILE  "/etc/hosts"
#define ETC_DNS_FILE  "/etc/resolv.conf"
#define RESOLV_DIR  PROJECT_TMP_DIR"/resolv"
#define CONNECT_PID_FILE  PROJECT_VAR_DIR"/.connect.pid"
#define CONNECT_UNIX_FILE PROJECT_VAR_DIR"/.connect.unix"



void static_ip_enable( const char *device, talk_t cfg );
void static_ip_disable( const char *device );
boole mode_static( const char *object, const char *ifdev, const char *device, talk_t cfg, talk_t info );
talk_t dhcp_client_connect( const char *ifname, const char *ifdev, const char *device, talk_t cfg );
talk_t pppoe_client_connect( const char *ifname, const char *ifdev, const char *device, talk_t cfg );



void slaac_ip_enable( const char *device );
void slaac_ip_disable( const char *device );
void manual_ip_enable( const char *device, talk_t cfg );
void manual_ip_disable( const char *device );
boole method_manual( const char *object, const char *ifdev, const char *device, talk_t cfg, talk_t info );
talk_t automatic_client_connect( const char *ifname, const char *ifdev, const char *device, talk_t cfg );



/**
 * @brief switch the extern route rule
 * @param[in] tid route id
 * @param[in] dest dest ip address
 * @param[in] mask netmask
 * @param[in] metric
 * @param[in] v route infomation
 * @param[in] clear  true for delete first
 * @return succeed or failed
 *		@retval true for succeed
 *		@retval false for failed
 */
boole routes_switch( const char *tid, const char *dest, const char *mask, const char *metric, talk_t v, boole clear );
/**
 * @brief switch the extern route rule on two line
 * @param[in] tid route id
 * @param[in] dest dest ip address
 * @param[in] mask netmask
 * @param[in] metric
 * @param[in] v route infomation
 * @param[in] v2 route2 infomation
 * @param[in] clear  true for delete first
 * @return succeed or failed
 *		@retval true for succeed
 *		@retval false for failed
 */
boole routes_switch2( const char *tid, const char *dest, const char *mask, const char *metric, talk_t v, talk_t v2, boole clear );
/**
 * @brief create the extern route
 * @param[in] tid route id
 * @param[in] ifnamest ifname status
 * @return succeed or failed
 *		@retval true for succeed
 *		@retval false for failed
 */
boole routes_create_ifname( int tid, talk_t ifnamest );



/**
 * @brief create shunts
 * @param[in] custom value
 * @return succeed or failed
 *		@retval true for succeed
 *		@retval false for failed
 */
boole shunts_create( talk_t list );
/**
 * @brief disable shunts
 * @param[in] force force old connection
 * @return succeed or failed
 *		@retval true for succeed
 *		@retval false for failed
 */
boole shunts_disable( boole force );
/**
 * @brief direct all stream to ifname
 * @param[in] force force old connection
 * @param[in] ifname ifname
 * @return succeed or failed
 *		@retval true for succeed
 *		@retval false for failed
 */
boole shunts_fix_ifname( boole force, const char *ifname );
/**
 * @brief balancing stream on two ifname
 * @param[in] force force old connection
 * @param[in] ifname ifname
 * @param[in] ifname2 ifname
 * @return succeed or failed
 *		@retval true for succeed
 *		@retval false for failed
 */
boole shunts_balancing_2ifname( boole force, const char *ifname, const char *ifname2 );



#endif   /* ----- #ifndef H_NETWORK_LANDNET_H  ----- */

