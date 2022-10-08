#ifndef H_LAND_MISC_H
#define H_LAND_MISC_H

/**
 * @file misc.h
 * @author dimmalex@gmail.com
 * @version 7.0
 * @date 20220219
 * @brief miscellaneous function implementation
 */



/* MD5 checksum */
typedef struct
{
    unsigned int count[2];
    unsigned int state[4];
    unsigned char buffer[64];
} md5_ctx;
#define F(x,y,z) ((x & y) | (~x & z))
#define G(x,y,z) ((x & z) | (y & ~z))
#define H(x,y,z) (x^y^z)
#define I(x,y,z) (y ^ (x | ~z))
#define ROTATE_LEFT(x,n) ((x << n) | (x >> (32-n)))
#define FF(a,b,c,d,x,s,ac) \
{ \
    a += F(b,c,d) + x + ac; \
    a = ROTATE_LEFT(a,s); \
    a += b; \
}
#define GG(a,b,c,d,x,s,ac) \
{ \
    a += G(b,c,d) + x + ac; \
    a = ROTATE_LEFT(a,s); \
    a += b; \
}
#define HH(a,b,c,d,x,s,ac) \
{ \
    a += H(b,c,d) + x + ac; \
    a = ROTATE_LEFT(a,s); \
    a += b; \
}
#define II(a,b,c,d,x,s,ac) \
{ \
    a += I(b,c,d) + x + ac; \
    a = ROTATE_LEFT(a,s); \
    a += b; \
}
void md5_init( md5_ctx *context);
void md5_update( md5_ctx *context,unsigned char *input,unsigned int inputlen );
void md5_final( md5_ctx *context,unsigned char digest[16] );
void md5_transform( unsigned int state[4],unsigned char block[64] );
void md5_encode( unsigned char *output,unsigned int *input,unsigned int len );
void md5_decode( unsigned int *output,unsigned char *input,unsigned int len );
char *b64_encode( char *s );
char *b64_encode_block( char *s, int len );
char *b64_decode( char *s );
char *b64_decode_block( char *s, int *len, int flags );
char *url_encode( char const *s, int len, int *new_length );
int url_decode( char *str, int len );
char *mac_encode( char *message, const char *key );
char *mac_decode( char *message, const char *key );
void string2hex( const char *src, char *dest, int len );
void hex2string( const char *src, char *dest, int len);
void hex2printf( const char *src, char *dest, int len);
void char_replace( char *src, char a, char b );
unsigned long rand_long( void );



/**
 * @brief free for errno not set
 * @return none
 */
#define efree( x ) do{ int err=errno;free(x);errno=err; }while(0)
/**
 * @brief upper case the string
 * @return none
 */
void lowtoupp( char *str );
/**
 * @brief upper case the string
 * @return none
 */
void upptolow( char *str );
/**
 * @brief convert hex string to int
 * @return int
 */
int hexstr2int( const char *s );



typedef struct hp_mac_st
{
    union
    {
        unsigned short one;
        unsigned char array[2];
    }head;  /* head two */
    union
    {
        unsigned int one;
        unsigned char array[4];
    }end;   /* end six */
} hp_mac_struct;
typedef hp_mac_struct* hp_mac_t;
boole string2mac( const char *macbuf, hp_mac_t mac );
boole mac2string( hp_mac_t mac, char *macbuf );
unsigned int mac2int( hp_mac_t mac );
boole serial2mac( const char *macbuf, hp_mac_t mac );
boole mac2serial( hp_mac_t mac, char *macbuf );
void mac2add( hp_mac_t mac,  int i );
boole macrang( hp_mac_t mac,  hp_mac_t start, hp_mac_t end, int mod );



/**
 * @brief Get when timestamp, millisecond
 * @return Success returns the current timestamp */
long long timestamp( void );
/**
 * @brief get system uptime in second
 * @return system uptime in second
 *		@retval positive for succeed
 *  	@retval 0 for failed
 */
unsigned int uptime_int( void );
/**
 * @brief get the system uptime string
 * @param[out] buffer system uptime string store here
 * @param[in] buflen buffer length
 * @return string
 *		@retval string for succeed
 *		@retval NULL for failed, the errno code will be sets
 */
const char *uptime_string( char *buffer, int buflen );
/**
 * @brief get the system uptime description
 * @param[out] buffer system uptime description store here
 * @param[in] buflen buffer length
 * @return string
 *		@retval string for succeed
 *		@retval NULL for failed, the errno code will be sets
 */
const char *uptime_desc( char *buffer, int buflen );
/**
 * @brief get the live time description
 * @param[in] uptime uptime in the past point
 * @param[out] buffer live time description store here
 * @param[in] buflen buffer length
 * @return string
 *		@retval string for succeed
 *		@retval NULL for failed, the errno code will be sets
 */
const char *livetime_desc( unsigned int uptime, char *buffer, int buflen );
/**
 * @brief get the current date description
 * @param[out] buffer current date description store here
 * @param[in] buflen buffer length
 * @return string
 *		@retval string for succeed
 *		@retval NULL for failed, the errno code will be sets
 */
const char *date_desc( char *buffer, int buflen );
/**
 * @brief set the current date
 * @param[in] seconds current UTC second
 * @param[in] zone zone
 * @return none
 */
void date_set( time_t seconds, const char* zone );
/**
 * @brief get the mtd device by partition name
 * @param[in] partition partition
 * @param[out] mtd mtd char device
 * @param[out] mtdblock mtd block device
 * @return operation succeed or failed
 * 		@retval true for succeed
 *  	@retval false for failed, the errno code will be sets
 */
boole partition2device( const char *name, char *mtd, char *mtdblock );
/**
 * @brief count how many file in a directory
 * @param[in] directory path
 * @return how many file in the directory
 *		@retval positive for succeed
 *		@retval negative for failed, the errno code will be sets
 */
int directory_subsum( const char *dir );
/**
 * @brief count a directory size, include the subdir
 * @param[in] directory path
 * @return directory size
 *		@retval positive for succeed
 *		@retval negative for failed, the errno code will be sets
 */
int directory_size( const char *dir );



/**
 * @brief nothing to do of signal handler function
 * @param[in] signo signal number
 * @return none
 */
void signal_noprocess( int signo );
/**
 * @brief same the signal() function and more safe
 * @param[in] signo signal number
 * @param[in] func signal handler function
 * @return original signal handler
 * 		@retval function for succeed
 *  	@retval SIG_ERR for failed, the errno code will be sets
 */
typedef void (*sighandler_t)(int);
sighandler_t signal_register( int signo, sighandler_t func );
/**
 * @brief same the system() function and more safe
 * @param[in] format shell command
 * @return value of command return
 * 		@retval 0 for succeed
 *  	@retval negative for failed, the errno code will be sets
 */
int shell( const char *format, ... );
/**
 * @brief same the system() function and more safe, also have timeout control
 * @param[in] timeout return after timout
 * @param[in] silent not to print when true
 * @param[in] format shell command
 * @return return of command
 *		@retval 0 for succeed
 *		@retval negative for failed, the errno code will be sets
 */
int execute( int timeout, boole silent, const char *format, ... );
/**
 * @brief exeute the iptables with lock
 * @param[in] format shell command
 * @return value of command return
 * 		@retval 0 for succeed
 *  	@retval negative for failed, the errno code will be sets
 */
int iptables( const char *format, ... );
/**
 * @brief exeute the ip6tables with lock
 * @param[in] format shell command
 * @return value of command return
 * 		@retval 0 for succeed
 *  	@retval negative for failed, the errno code will be sets
 */
int ip6tables( const char *format, ... );
/**
 * @brief exeute the ebtables with lock
 * @param[in] format shell command
 * @return value of command return
 * 		@retval 0 for succeed
 *  	@retval negative for failed, the errno code will be sets
 */
int ebtables( const char *format, ... );
/**
 * @brief insmod the module
 * @param[in] module
 * @return none 
 */
void insert_module( const char *module );
/**
 * @brief rmmod the module
 * @param[in] module
 * @return none 
 */
void remove_module( const char *module );



/**
 * @brief lock the corresponding area of the file
 * @param[in] fd file description handler
 * @param[in] ex mutex when true
 * @param[in] start starting offset for lock
 * @param[in] whence How to interpret start: SEEK_SET, SEEK_CUR, SEEK_END
 * @param[in] len number of bytes to lock
 * @param[in] wait wait or not. -1 indicates permanent wait, 0 indicates no wait, and a positive integer indicates waiting time
 * @return pid of process lock succeed
 *		@retval pid for succeed
 *		@retval negative for failed, the errno code will be sets
 */
int fd_lock( int fd, boole ex, int start, int whence, int len, int wait );
/**
 * @brief unlock the corresponding area of the file
 * @param[in] fd file description handler
 * @param[in] ex mutex when true
 * @param[in] start starting offset for lock
 * @param[in] whence How to interpret start: SEEK_SET, SEEK_CUR, SEEK_END
 * @param[in] len number of bytes to lock
 * @return opertion succeed or failed
 *		@retval true for succeed
 *		@retval false for failed, the errno code will be sets
 */
boole fd_unlock( int fd, boole ex, int start, int whence, int len );
/**
 * @brief set the fd nonblock
 * @param[in] fd file description handler
 * @return opertion succeed or failed
 *		@retval true for succeed
 *		@retval false for failed, the errno code will be sets
 */
boole fd_nonblock( int fd );
/**
 * @brief set the fd block
 * @param[in] fd file description handler
 * @return opertion succeed or failed
 *		@retval true for succeed
 *		@retval false for failed, the errno code will be sets
 */
boole fd_block( int fd );
/**
 * @brief get the region locking pid of process corresponding to the file
 * @param[in] fd file description handler
 * @param[in] ex mutex when true
 * @param[in] start starting offset for lock
 * @param[in] whence how to interpret start: SEEK_SET, SEEK_CUR, SEEK_END
 * @param[in] len number of bytes to lock
 * @return pid of process lock succeed
 *		@retval pid for succeed
 *		@retval negative for failed, the errno code will be sets
 */
pid_t fd_lock_pid( int fd, boole ex, int start, int whence, int len );
/**
 * @brief open a file with a lock
 * @param[in] filename file pathname
 * @param[in] flags flags for open() function
 * @param[in] mode mode for open() function
 * @param[in] block block or not. -1 indicates permanent block, 0 indicates no block, and a positive integer indicates waiting time
 * @return file description handler
 *		@retval handler for succeed
 *		@retval negative for failed, the errno code will be sets
 */
int lock_open( const char *filename, int flags, int mode, int block );
/**
 * @brief unlock and close the file
 * @param[in] fd file description handler
 * @return opertion succeed or failed
 *		@retval 0 for succeed
 *		@retval negative for failed, the errno code will be sets
 */
int lock_close( int fd );
/**
 * @brief read a talk from fd
 * @param[in] fd file description handler
 * @param[in] timeout <0 for block, >0 for wait timeout in second
 * @return a pointer of json
 *		@retval json for peer succeed
 *		@retval NULL for peer return
 *		@retval ttrue for peer return
 *		@retval tfalse for peer return
 *		@retval NULL for peer failed, the errno code will be sets
 *  	@retval terror for peer got wrong, the errno code will be sets

 *  	@retval TALK_EINVAL for calling of parameter error, and errno code will be sets
 *  	@retval TALK_EPERM for calling of permission denied, the errno code will be sets
 *  	@retval TALK_ECOM for calling of cannot find the component, the errno code will be sets
 *  	@retval TALK_EFUNC for calling of cannot find the component method, the errno code will be sets
 *  	@retval TALK_EJSON for calling of peer component return wrong data, the errno code will be sets
 */
talk_t fd2talk( int fd, int timeout );
/**
 * @brief send a json
 * @param[in] fd file description handler
 * @param[in] json a pointer of json
 * @param[in] errocde errno be send when json < TALK_ECODEMAX
 * @param[in] timeout <0 for block, >0 for wait timeout in second
 * @return number of send bytes
 *		@retval <0 for succeed
 *		@retval negative for failed, the errno code will be sets
 */
int talk2fd( int fd, talk_t talk, int errcode, int timeout );
/**
 * @brief send a json
 * @param[in] sock socket description handler
 * @param[in] json a pointer of json
 * @param[in] errocde errno be send when json < TALK_ECODEMAX
 * @param[in] timeout <0 for block, >0 for wait timeout in second
 * @param[in] peer peer address
 * @param[in] peerlen peer address size
 * @return number of send bytes
 *		@retval <0 for succeed
 *		@retval negative for failed, the errno code will be sets
 */
int talk2sock( int sock, talk_t talk, int errcode, int timeout, struct sockaddr *peer, socklen_t peerlen );



/**
 * @brief safe to count the string length
 * @param[in] string
 * @return length of string
 *		@retval positive for succeed
 *		@retval zero for NULL or empty string
 */
int stringlen( const char *string );
/**
 * @brief write a string to a file
 * @param[in] filename file pathname
 * @param[in] format string same printf()
 * @return length of data written on success
 *		@retval positive for succeed
 *		@retval negative for failed, the errno code will be sets
 */
int string2file( const char *filename, const char *format, ... );
/**
 * @brief write a string to a file end
 * @param[in] filename file pathname
 * @param[in] format string same printf()
 * @return length of data written on success
 *		@retval positive for succeed
 *		@retval negative for failed, the errno code will be sets
 */
int string3file( const char *filename, const char *format, ... );
/**
 * @brief read a string to a file
 * @param[in] filename file pathname
 * @param[out] readbuf buffer the string will be store here
 * @param[in] bufsize size of buffer
 * @return string
 *		@retval string for succeed
 *		@retval NULL for failed, the errno code will be sets
 */
const char *file2string( const char *filename, char *buffer, int bufsize );
/**
 * @brief write a integer to a file
 * @param[in] filename file pathname
 * @param[in] integer
 * @return length of data written on success
 *		@retval positive for succeed
 *		@retval negative for failed, the errno code will be sets
 */
int int2file( const char *filename, int integer );
/**
 * @brief read a integer from a file
 * @param[in] filename file pathname
 * @return integer
 *		@retval integer for succeed
 *		@retval -1 for failed, the errno code will be sets
 */
int file2int( const char *filename );



/**
 * @brief netmask transition
 */
const char *ip2subnet( const char *ip, const char *mask, char *subnet, int len );
const char *netmask2cidr( const char *netmask, char *buf, int buflen );
unsigned int netmask2num( const char *mask );
/**
 * @brief test the netcard have the flag
 * @param[in] card network interface name
 * @param[in] flag
 * @return flag is or not exist
 *		@retval 1 for exist
 *		@retval 0 for no exist
 *		@retval -1 for failed, the errno code will be sets
 */
int netdev_flags( const char *card, short flag );
/**
 * @brief get the netcard basic infomation
 * @param[in] card network interface name
 * @param[out] ip network interface ip return to store here
 * @param[in] ip_len ip length
 * @param[out] pppip network interface ppp ip or gateway ip return to store here
 * @param[in] pppip_len pppip length
 * @param[out] mask network ineterface netmask return to store here
 * @param[in] mask_len mask length
 * @param[out] mac network interface mac address return to store here
 * @param[in] mac_len mac length
 * @return opertion succeed or failed
 *		@retval 0 for succeed
 *		@retval -1 for failed, the errno code will be sets
 */
int netdev_info( const char *card, char *ip, int ip_len, char *pppip, int pppip_len, char *mask, int mask_len, char *mac, int mac_len );
/**
 * @brief get the netcard flow infomation
 * @param[in] card network interface name
 * @param[out] rx_bytes
 * @param[out] rx_packets
 * @param[out] rx_errs
 * @param[out] tx_bytes
 * @param[out] tx_packets
 * @param[out] tx_errs
 * @param[out] tx_drops
 * @return opertion succeed or failed
 *		@retval 0 for succeed
 *		@retval -1 for failed, the errno code will be sets
 */
int netdev_flew( const char *card, unsigned long long *rx_bytes , unsigned long long *rx_packets , unsigned long long *rx_errs, unsigned long long *rx_drops, unsigned long long *tx_bytes , unsigned long long *tx_packets , unsigned long long *tx_errs, unsigned long long *tx_drops );



#define MAIN_TABLE_NAME "main"
#define MAIN_TABLE_ID 254
#define MAIN_TABLE_PREF 32766
#define IFNAME_TABLE_PREF 35000
#define RULE_TABLE_PREF 40000
#define DEFAULT_TABLE_NAME "default"
#define DEFAULT_TABLE_ID 253
#define DEFAULT_TABLE_PREF 50000
/**
 * @brief get the route rule infomation
 * @param[in] destname dest of rule
 * @param[in] mask  mask of rule
 * @param[out] gateway
 * @param[out] netdev
 * @return rule exist or not
 *		@retval true for exist
 *		@retval false for not exist
 */
boole route_info( const char *destname, const char *mask, char *gateway, char *netdev );
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
boole route_switch( const char *dest, const char *mask, const char *metric, talk_t v, boole clear );
/**
 * @brief get the extern route rule infomation
 * @param[in] tid route id
 * @param[in] destname dest of rule
 * @param[in] mask  mask of rule
 * @param[out] gateway
 * @param[out] netdev
 * @return match the rule number
 *		@retval >0 for exist
 *		@retval 0 for not exist
 *		@retval <0 for error
 */
boole routes_info( const char *tid, const char *destname, const char *mask, char *gateway, char *netdev );
/**
 * @brief get the default route infomation
 * @param[out] gateway
 * @param[out] netdev
 * @return rule exist or not
 *		@retval true for exist
 *		@retval false for not exist
 */
boole gateway_info( char *gateway, char *netdev );



/**
 * @brief set the socket reuse
 * @param[in] fd file description handler
 * @return opertion succeed or failed
 *		@retval true for succeed
 *		@retval false for failed, the errno code will be sets
 */
boole socket_reuse( int sock );
/**
 * @brief set the tcp socket keepalive
 * @param[in] fd file description handler
 * @return opertion succeed or failed
 *		@retval true for succeed
 *		@retval false for failed, the errno code will be sets
 */
boole socket_keepalive( int sock, int keepalive );
/**
 * @brief make tcp socket and connect to peer
 * @param[in] peer only support ip address in string
 * @param[in] port
 * @param[in] timeout
 * @return file description handler
 *		@retval >=0 for succeed
 *		@retval <0 for failed, the errno code will be sets
 */
int tcp_connect( const char *peer, int port, int timeout );
/**
 * @brief make udp socket and connect to peer
 * @param[in] peer only support ip address in string
 * @param[in] port
 * @param[in] timeout
 * @return file description handler
 *		@retval >=0 for succeed
 *		@retval <0 for failed, the errno code will be sets
 */
int udp_connect( const char *peer, int port, int timeout );
/**
 * @brief make unix socket and connect to peer
 * @param[in] peer
 * @param[in] local
 * @return file description handler
 *		@retval >=0 for succeed
 *		@retval <0 for failed, the errno code will be sets
 */
int unix_connect( const char *peer, const char *local );
/**
 * @brief make unix socket for server
 * @param[in] path
 * @return file description handler
 *		@retval >=0 for succeed
 *		@retval <0 for failed, the errno code will be sets
 */
int unix_listen( const char *path );



/**
 * @brief resolv the dns
 * @param[in] addr dns name
 * @param[out] ipbuf  ip buffer
 * @param[in] ipbuflen ip buffer length
 * @param[in] timeout
 * @return ip address
 *		@retval ip address
 *		@retval NULL for failed, the errno code will be sets
 */
const char *dns2ipstring( const char *addr, char *ipbuf, int ipbuflen, int timeout );



#endif   /* ----- #ifndef H_LAND_MISC_H  ----- */

