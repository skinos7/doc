#ifndef H_UART_LANDUART_H
#define H_UART_LANDUART_H
/**
 * @brief uart相关接口
 * @author dimmalex
 * @version 1.0
*/
#include <event.h>
#include <event2/event.h>



int serial_n2speed (int bps);
void serial_setdtr (int tty_fd, int on);
int serial_open( const char *path, talk_t cfg, int timeout );



#endif   /* ----- #ifndef H_UART_LANDUART_H  ----- */

