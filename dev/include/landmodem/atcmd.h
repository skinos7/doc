#ifndef  H_SKIN_ATCMD_H
#define  H_SKIN_ATCMD_H
/*
 *    Description:  AT串口通信帮助函数库(atcmd)
 *         Author:  dimmalex (dim), dimmalex@gmail.com
 *        Company:  HP
 */



/* 判断是否为IO错误的宏*/
#define serial_error(num) ((num)==EIO)
/* 给出数字的波特率,返回终端函数接口可 认的波特率 */
int serial_n2speed( int bps );
/* 设置串口DTR  */
void serial_setdtr (int tty_fd, int on);



/*  AT串口操作超时时间, 即一次操作要求返回 的时间*/
#define ATCMD_ATTIMEOUT 5
/*  AT串口操作BUFFER 大小*/
#define ATCMD_ATBUFFSIZE 20480
/*  AT串口操作模式*/
#define ATCMD_DEF 0                    /* 默认的操作模式, 即ATCMD_DEBUG+ATCMD_ECHO */
#define ATCMD_NOECHO 1                 /* 使用有AT无回显的方式与串口通信 */
#define ATCMD_ECHO 4                   /* 使用有AT回显的方式与串口通信 */
/*  AT串口操作返回值 */
#define ATCMD_ret_param -2                /* 参数错误 */
#define ATCMD_ret_error -1                /* 出错 */
#define ATCMD_ret_succeed 0               /* 成功 */
#define ATCMD_ret_term 1                  /* 收到退出信号 */
#define ATCMD_ret_close 2                 /* 串口被对端关闭 */
#define ATCMD_ret_incomplete 3            /* 接收未全部完成 */
#define ATCMD_ret_urc 4                   /* URC处理 */
#define ATCMD_ret_timeout 5               /* 操作超时 */
#define ATCMD_ret_failed 6                /* 操作失败 */
struct atcmd_struct;



/* URC回复解析处理回调函数类型
    atfd: AT串口句柄
    urc: AT串口返回的URC  */
typedef int (*atcmd_urc_fn)( struct atcmd_struct *atfd, const char *urc );
/* AT回复解析回调函数 类型
    atfd: AT串口句柄
    cmd: 刚已发送过的AT指令
    expect: 期望的回复
    flags: AT串口操作模式 */
typedef int (*atcmd_parse_fn)( struct atcmd_struct *atfd, const char *cmd,  const char *expect, int flags );
/* AT串口帮助接口句柄结构 , 此结构中的所有成员由atcmd_为前缀的AT串口函数维护, 其它函数不得直接访问*/
typedef struct atcmd_struct
{
    int fd;                                       /* 串口fd描述符 */
    int nread;                                 /* 已读到的数据个数*/
    char readbuf[ATCMD_ATBUFFSIZE];      /* 读BUFFER */
    char ackbuf[ATCMD_ATBUFFSIZE];         /* 串口回复数据存储BUFFER */
    int flags;                                              /* 串口操作标识位*/
    atcmd_urc_fn urc;                                 /* URC回调函数, 即如果有URC时, 调用此函数来处理 */
    atcmd_parse_fn parse;   /* 解析回调函数, 有数据回复时调用此函数解析 */
    sigset_t open_sigmask;   /* 存储用于open时的sigmask*/
    sigset_t atcmd_sigmask; /* 存储用于串口操作时的sigmask*/
    sigset_t save_sigmask;   /* 保存用所有串口操作前的sigmask, 便 于关闭时恢复系统原始的sigmask */
} atcmd_st;
typedef atcmd_st* atcmd_t;



/* 打开串口返回 atcmd句柄
    path: 串口路经
    flag: open标识
    speed: 串口波特率
    parse: 指定自定义的解析回调函数(如果为NULL, 系统会自动提供)
    urc: 指定自定义的URC解析及处理回调函数( 如果为NULL, 系统忽略URC )
    flags: AT串口操作模式(建议使用ATCMD_DEF或0即ATCMD_DEBUG|ATCMD_ECHO )
    返回: 成功时为打开后的AT串口句柄, 失败时为NULL */
atcmd_t atcmd_open( const char *path, int flag, int speed, atcmd_parse_fn parse, atcmd_urc_fn urc, int flags );
/* 关闭 串口atcmd句柄并释放相关的资源 
    atfd: 要关闭及释放的AT串口句柄
    返回: 成功时为true, 失败时为false  */
boole    atcmd_close( atcmd_t atfd );

/* 向AT串口发送数据包
    atfd: AT串口句柄
    cmd: AT指令
    export: 期望的回复, 
    flags: AT串口操作模式, ATCMD_DEF或0表示使用在打开时指令的
    返回: 如果export不为空, 收到export就返回ATCMD_ret_succeed;
                 如果export为空, 收到OK时返回ATCMD_ret_succeed, 
                 不管怎样:
                        收到ERROR时返回ATCMD_ret_failed
                        超时返回ATCMD_ret_timeout
                        参数出错返回ATCMD_ret_param
                        系 统操作出错返回ATCMD_ret_error
                        被对端关闭返回ATCMD_ret_close  */
int          atcmd_send( atcmd_t atfd, const char *cmd, int timeout, const char *expect, int flags );
int          atcmd_tx( atcmd_t atfd, int timeout, const char *expect, int flags, const char *cmd, ... );
/* 得到最后一次串口的回复 
    atfd: AT串口句柄
    返回: 最后一次串口回复的字串(atcmd_rx返回字符串的长度) */
char      *atcmd_lastack( atcmd_t atfd );
int        atcmd_rx( atcmd_t atfd, char *recvbuf, int recvlen );



/* 例:
    atcmd_t atfd;
    const char *ptr;
    atfd = atcmd_open( "/dev/ttyS0", (O_RDWR|O_NONBLOCK|O_SYNC), 115200, NULL, NULL, ATCMD_DEF );
    if ( atfd != NULL )
    {
        if ( atcmd_send( atfd, "AT+GSN", 2, "+CGSN:", 0 ) == ATCMD_ret_succeed )
        {
            ptr = atcmd_lastack( atfd );
            printf( "AT+CGN return %s\n", ptr );
        }
        if ( atcmd_send( atfd, "AT+CPIN?", 2, NULL, 0 ) == ATCMD_ret_succeed )
        {
            ptr = atcmd_lastack( atfd );
            printf( "AT+CPIN? return %s\n", ptr );
        }
        atcmd_close( atfd );
    } */



#endif   /* ----- #ifndef H_SKIN_ATCMD_H  ----- */

