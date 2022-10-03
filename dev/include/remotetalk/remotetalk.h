#ifndef H_NETWORK_REMOTETALK_H
#define H_NETWORK_REMOTETALK_H
/**
 * @brief 远程交互talk时常用的接口
 * @author dimmalex
 * @version 1.0
*/
#include <curl/curl.h>
//#define REMOTE_TALK_DEBUG



/*
    向远程http服务器post一个JSON并得到http服务器返回的JSON
    url: 远程http服务器地址
    type: 要POST的HTTP类型
    encrypt: 数据加密方式, 如base64
    v: 要POST的JSON
    contimeout: 连接最大等待时长
    talktimeout: 交互数据时最大等待时长
    cookiefile: 存储cookie的文件
    成功返回服务器返回的JSON, 服务器无返回则返回NULL , 出错返回tfalse*/
talk_t easy_rtalk_type( const char *url, const char *type, const char *encrypt, talk_t v, int contimeout, int talktimeout, const char *cookiefile );
/*
    向远程http服务器post一个JSON并得到http服务器返回的JSON
    url: 远程http服务器地址
    v: 要POST的JSON
    contimeout: 连接最大等待时长
    talktimeout: 交互数据时最大等待时长
    cookiefile: 存储cookie的文件
    成功返回服务器返回的JSON, 服务器无返回则返回NULL , 出错返回tfalse*/
talk_t easy_rtalk( const char *url, talk_t v, int contimeout, int talktimeout, const char *cookiefile );



#endif   /* ----- #ifndef H_NETWORK_REMOTETALK_H  ----- */

