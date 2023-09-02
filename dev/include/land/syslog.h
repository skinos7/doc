#ifndef H_LAND_LOG_H
#define H_LAND_LOG_H

/**
 * @file log.h
 * @author dimmalex@gmail.com
 * @version 7.0
 * @date 20220219
 * @brief log call implementation
 */



/// log line lenght
#define SYSLOG_LINE_MAX           4096
/// log level
#define SYSLOG_FAULT              (1<<0)        /* ERROR */
#define SYSLOG_WARN               (1<<1)        /* WARNNING */
#define SYSLOG_INFO               (1<<2)        /* INFOMATION */
#define SYSLOG_DEBUG              (1<<3)        /* DEBUG */
#define SYSLOG_VERBOSE            (1<<4)        /* VERBOSE */
#define SYSLOG_LEVEL_MASK         0x1F          /* log level mask */
/// log options
#define SYSLOG_ERRNO              (1<<5)      /* output errno */
#define SYSLOG_TUI                (1<<6)      /* output to tui */
#define SYSLOG_LOG                (1<<7)      /* output to syslog */
#define SYSLOG_FILE               (1<<8)      /* output to syslog */
#define SYSLOG_TRACE              (1<<9)      /* output trace */
#define SYSLOG_OPT_MASK           0xFC0       /* log option mask ( not include LOG_ERRNO )*/
#define SYSLOG_OPTION_MASK        0xFE0       /* log option mask */
/// log type
#define SYSLOG_LAND           (1<<12)       /* land frame */
#define SYSLOG_ARCH           (1<<13)       /* arch */
#define SYSLOG_JOINT          (1<<14)       /* joint */
#define SYSLOG_SERVICE        (1<<15)       /* service */
#define SYSLOG_GATHER         (1<<16)       /* gather and agent */
#define SYSLOG_NETWORK        (1<<17)       /* network */
#define SYSLOG_MODEM          (1<<18)       /* lte/nr modem */
#define SYSLOG_UART           (1<<18)       /* UART */
#define SYSLOG_DEFAULT        (1<<20)       /* default */
#define SYSLOG_TYPE_MASK     0xFFFFF000           /* 日志类型掩码 */

/// syslog file name
#define SYSLOG_FILENAME "syslog.txt"

/**
 * @brief open the syslog, same openlog()
 * @param[in] name process name
 * @param[in] flags log level or log options or log type
 * @return none
 */
void syslog_open( const char *name, int flags );
/**
 * @brief close the syslog
 * @return none
 */
void syslog_close( void );
/**
 * @brief Internal actual logging function
 * @param[in] flags The identifier for this log
 * @param[in] filename Name of the current log file
 * @param[in] line The line number of the current logging code
 * @param[in] format log contents
 * @return none
 */
void syslog_string( unsigned int flags, const char *filename, int line, const char *format, ... );



/* 记录事件信息(要求指定事件信息标志)*/
#define journal( flags, ... )     syslog_string( (flags), (__FILE__), (__LINE__), __VA_ARGS__ )

/* 记录调试最细节的信息*/
#define verbose( ... )            syslog_string( (SYSLOG_DEFAULT|SYSLOG_VERBOSE), (__FILE__), (__LINE__), __VA_ARGS__ )
/* 记录调试的事件信息*/
#define debug( ... )              syslog_string( (SYSLOG_DEFAULT|SYSLOG_DEBUG), (__FILE__), (__LINE__), __VA_ARGS__ )
/* 记录提示的事件信息*/
#define info( ... )               syslog_string( (SYSLOG_DEFAULT|SYSLOG_INFO), (__FILE__), (__LINE__), __VA_ARGS__ )
/* 记录警告的事件信息*/
#define warn( ... )               syslog_string( (SYSLOG_DEFAULT|SYSLOG_WARN), (__FILE__), (__LINE__), __VA_ARGS__ )
/* 记录警告的事件信息, 并附带errno变量的值*/
#define warning( ... )            syslog_string( (SYSLOG_DEFAULT|SYSLOG_WARN|SYSLOG_ERRNO), (__FILE__), ( __LINE__ ), __VA_ARGS__ )
/* 记录错误的事件信息*/
#define fault( ... )              syslog_string( (SYSLOG_DEFAULT|SYSLOG_FAULT), (__FILE__), (__LINE__), __VA_ARGS__ )
/* 记录错误的事件信息, 并附带errno变量的值*/
#define faulting( ... )           syslog_string( (SYSLOG_DEFAULT|SYSLOG_FAULT|SYSLOG_ERRNO), (__FILE__), (__LINE__), __VA_ARGS__ )

/* 系统框架调试最细节信息 */
#define lverbose( ... )      syslog_string( (SYSLOG_LAND|SYSLOG_VERBOSE), (__FILE__), (__LINE__), __VA_ARGS__ )
/* 系统框架调试信息 */
#define ldebug( ... )        syslog_string( (SYSLOG_LAND|SYSLOG_DEBUG), (__FILE__), (__LINE__), __VA_ARGS__ )
/* 系统框架提示信息 */
#define linfo( ... )         syslog_string( (SYSLOG_LAND|SYSLOG_INFO), (__FILE__), (__LINE__), __VA_ARGS__ )
/* 系统框架警告信息 */
#define lwarn( ... )         syslog_string( (SYSLOG_LAND|SYSLOG_WARN), (__FILE__), (__LINE__), __VA_ARGS__ )
/* 系统框架警告的事件信息, 并附带errno变量的值*/
#define lwarning( ... )      syslog_string( (SYSLOG_LAND|SYSLOG_WARN|SYSLOG_ERRNO), (__FILE__), ( __LINE__ ), __VA_ARGS__ )

/* 系统底层调试最细节信息 */
#define averbose( ... )      syslog_string( (SYSLOG_ARCH|SYSLOG_VERBOSE), (__FILE__), (__LINE__), __VA_ARGS__ )
/* 系统底层调试信息 */
#define adebug( ... )        syslog_string( (SYSLOG_ARCH|SYSLOG_DEBUG), (__FILE__), (__LINE__), __VA_ARGS__ )
/* 系统底层提示信息 */
#define ainfo( ... )         syslog_string( (SYSLOG_ARCH|SYSLOG_INFO), (__FILE__), (__LINE__), __VA_ARGS__ )
/* 系统底层警告信息 */
#define awarn( ... )         syslog_string( (SYSLOG_ARCH|SYSLOG_WARN), (__FILE__), (__LINE__), __VA_ARGS__ )
/* 系统底层警告的事件信息, 并附带errno变量的值*/
#define awarning( ... )      syslog_string( (SYSLOG_ARCH|SYSLOG_WARN|SYSLOG_ERRNO), (__FILE__), ( __LINE__ ), __VA_ARGS__ )

/* 管理交互调试最细节信息 */
#define gverbose( ... )      syslog_string( (SYSLOG_GATHER|SYSLOG_VERBOSE), (__FILE__), (__LINE__), __VA_ARGS__ )
/* 管理交互调试信息 */
#define gdebug( ... )        syslog_string( (SYSLOG_GATHER|SYSLOG_DEBUG), (__FILE__), (__LINE__), __VA_ARGS__ )
/* 管理交互提示信息 */
#define ginfo( ... )         syslog_string( (SYSLOG_GATHER|SYSLOG_INFO), (__FILE__), (__LINE__), __VA_ARGS__ )
/* 管理交互警告信息 */
#define gwarn( ... )         syslog_string( (SYSLOG_GATHER|SYSLOG_WARN), (__FILE__), (__LINE__), __VA_ARGS__ )
/* 管理交互警告的事件信息, 并附带errno变量的值*/
#define gwarning( ... )      syslog_string( (SYSLOG_GATHER|SYSLOG_WARN|SYSLOG_ERRNO), (__FILE__), ( __LINE__ ), __VA_ARGS__ )

/* 网络交互调试最细节信息 */
#define nverbose( ... )      syslog_string( (SYSLOG_NETWORK|SYSLOG_VERBOSE), (__FILE__), (__LINE__), __VA_ARGS__ )
/* 网络交互调试信息 */
#define ndebug( ... )        syslog_string( (SYSLOG_NETWORK|SYSLOG_DEBUG), (__FILE__), (__LINE__), __VA_ARGS__ )
/* 网络交互提示信息 */
#define ninfo( ... )         syslog_string( (SYSLOG_NETWORK|SYSLOG_INFO), (__FILE__), (__LINE__), __VA_ARGS__ )
/* 网络交互警告信息 */
#define nwarn( ... )         syslog_string( (SYSLOG_NETWORK|SYSLOG_WARN), (__FILE__), (__LINE__), __VA_ARGS__ )
/* 网络交互警告的事件信息, 并附带errno变量的值*/
#define nwarning( ... )      syslog_string( (SYSLOG_NETWORK|SYSLOG_WARN|SYSLOG_ERRNO), (__FILE__), ( __LINE__ ), __VA_ARGS__ )

/* 模块交互调试最细节信息 */
#define mverbose( ... )      syslog_string( (SYSLOG_MODEM|SYSLOG_VERBOSE), (__FILE__), (__LINE__), __VA_ARGS__ )
/* 模块交互调试信息 */
#define mdebug( ... )        syslog_string( (SYSLOG_MODEM|SYSLOG_DEBUG), (__FILE__), (__LINE__), __VA_ARGS__ )
/* 模块交互提示信息 */
#define minfo( ... )         syslog_string( (SYSLOG_MODEM|SYSLOG_INFO), (__FILE__), (__LINE__), __VA_ARGS__ )
/* 模块交互警告信息 */
#define mwarn( ... )         syslog_string( (SYSLOG_MODEM|SYSLOG_WARN), (__FILE__), (__LINE__), __VA_ARGS__ )
/* 模块交互警告的事件信息, 并附带errno变量的值*/
#define mwarning( ... )      syslog_string( (SYSLOG_MODEM|SYSLOG_WARN|SYSLOG_ERRNO), (__FILE__), ( __LINE__ ), __VA_ARGS__ )

/* 串口交互调试最细节信息 */
#define uverbose( ... )      syslog_string( (SYSLOG_UART|SYSLOG_VERBOSE), (__FILE__), (__LINE__), __VA_ARGS__ )
/* 串口交互调试信息 */
#define udebug( ... )        syslog_string( (SYSLOG_UART|SYSLOG_DEBUG), (__FILE__), (__LINE__), __VA_ARGS__ )
/* 串口交互提示信息 */
#define uinfo( ... )         syslog_string( (SYSLOG_UART|SYSLOG_INFO), (__FILE__), (__LINE__), __VA_ARGS__ )
/* 串口交互警告信息 */
#define uwarn( ... )         syslog_string( (SYSLOG_UART|SYSLOG_WARN), (__FILE__), (__LINE__), __VA_ARGS__ )
/* 串口交互警告的事件信息, 并附带errno变量的值*/
#define uwarning( ... )      syslog_string( (SYSLOG_UART|SYSLOG_WARN|SYSLOG_ERRNO), (__FILE__), ( __LINE__ ), __VA_ARGS__ )



#endif   /* ----- #ifndef H_LAND_LOG_H  ----- */

