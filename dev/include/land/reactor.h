#ifndef H_LAND_REACTOR_H
#define H_LAND_REACTOR_H
/**
 * @file reactor.h
 * @author dimmalex@gmail.com
 * @version 7.0
 * @date 20220219
 * @brief event loop patch implementation
 */



/// event log function
void reactor_log( int severity, const char *msg );
/// break from event loop
void reactor_break( int fd, short what, void *arg );
/// function type of ack to event control
typedef talk_t (*reactor_control_t)( const char *cmd, talk_t v, struct event_base *base );
/// event control forward function
void reactor_control( int fd, short what, void *arg );
/// call to event control
talk_t reactor_call( obj_t object, const char *cmd, talk_t v, int timeout );
talk_t reactor_scall( const char *object, const char *cmd, talk_t v, int timeout );



/**
 * @brief register a signal to break event loop
 * @param[in] base event base structure
 * @param[in] signal signal nubmer
 * @return return event handler
 * 		@retval event handler for succeed
 * 		@retval NULL for failed
 */
struct event *reactor_signal_break( struct event_base *base, int signal );
/**
 * @brief register a signal to ignore event loop
 * @param[in] base event base structure
 * @param[in] signal signal nubmer
 * @return return event handler
 * 		@retval event handler for succeed
 * 		@retval NULL for failed
 */
struct event *reactor_signal_ignore( struct event_base *base, int signal );
/**
 * @brief register a timer function to run
 * @param[in] base event base structure
 * @param[in] cb control accept function
 * @param[in] sec second
 * @param[in] usec
 * @return return event handler
 * 		@retval event handler for succeed
 * 		@retval NULL for failed
 */
struct event *reactor_timer_create( struct event_base *base, event_callback_fn cb, int sec, int usec );
/**
 * @brief register a signal handler function to run
 * @param[in] base event base structure
 * @param[in] signal signal nubmer
 * @param[in] cb signal handler function
 * @return return event handler
 * 		@retval event handler for succeed
 * 		@retval NULL for failed
 */
struct event *reactor_signal_create( struct event_base *base, int signal, event_callback_fn cb );
/**
 * @brief register a control function for event loop
 * @param[in] base event base structure
 * @param[in] cb control accept function
 * @return return event handler
 * 		@retval event handler for succeed
 * 		@retval NULL for failed
 */
struct event *reactor_control_create( struct event_base *base, obj_t this, reactor_control_t cb );
struct event *reactor_control_screate( struct event_base *base, const char *object, reactor_control_t cb );
void reactor_control_const( struct event *event, boole const_ack );



#endif   /* ----- #ifndef H_LAND_REACTOR_H  ----- */

