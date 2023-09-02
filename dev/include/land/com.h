#ifndef H_LAND_COM_H
#define H_LAND_COM_H

/**
 * @file com.h
 * @author dimmalex@gmail.com
 * @version 7.0
 * @date 20220219
 * @brief component call implementation
 * @details implementation communication to other component function use talk structure or parameter structure
 */



/// function type of get the component's configure 
typedef talk_t (*comget_t)( obj_t, attr_t );
/// function type of set the component's configure 
typedef boole (*comset_t)( obj_t, talk_t, attr_t );
/// universal method function type of component
typedef void* (*commethod_t)( obj_t, param_t );

/// com structure: this structure is a handler of components
typedef struct com_st
{
	// link node for add to link
    link_struct link;

	// reference count
	int ref;

	// component file type
#define COM_FILE_KO 1
#define COM_FILE_LIB 2
#define COM_FILE_SHELL 3
#define COM_FILE_EXECUTE 4
	signed char type;

	// component file pathname
    char path[PATH_MAX];

	// handler of component
    void *handle;

	// function of get the component's configure 
    comset_t setter;

	// function of set the component's configure 
    comget_t getter;

} com_struct;
typedef com_struct *com_t;

/// shell pipe return fd
#define SHELL_COM_PIPE 7
/// interval function
#define COM_METHOD_PREFIX "_"
com_t  com_open( obj_t obj );
void   com_close( com_t com );
boole  com_exist( obj_t obj, const char *method );
boole  com_sexist( const char *com, const char *method );
talk_t com_list( const char *project );
talk_t com_project_list( void );
talk_t com_register_list( void );
boole  com_register( const char *target, const char *origin );
boole  com_unregister( const char *target );



/**
 * @brief call a component method
 * @param[in] com a object or string description for object
 * @param[in] method name of method function
 * @param[in] parameter a pointer of parameter structure
 * @return json
 *		@retval json for peer succeed, return json must free after used
 *		@retval NULL for peer return
 *		@retval ttrue for peer return
 *		@retval tfalse for peer return
 *  	@retval terror for peer got wrong, the errno code will be sets

 *  	@retval TALK_EINVAL for calling of parameter error, and errno code will be EINVAL
 *  	@retval TALK_ECOM for calling of cannot find the component, the errno code will be ENOENT
 *  	@retval TALK_EPERM for calling of permission denied, the errno code will be EPERM
 *  	@retval TALK_EFUNC for calling of cannot find the component method, the errno code will be ENOSYS
 *  	@retval TALK_EPIPE for calling of pipe faild, the errno code will be sets
 *  	@retval TALK_EFORK for calling of fork faild, the errno code will be sets
 *  	@retval TALK_EJSON for calling of peer component return wrong data, the errno code will be ENOMSG
 */
void         *ccall( obj_t com, const char *method, param_t parameter );
void         *scall( const char *com, const char *method, param_t parameter );
/**
 * @brief call a component method use parameter of talk type
 * @param[in] com a object or string description for object
 * @param[in] method name of method function
 * @param[in] json a pointer of talk structure for first option
 * @param[in] jsons a pointer of talk structure for second option
 * @return return the component method's return when succeed or error return when call failed
 * 		@retval same the ccall
 */
void         *ccallt( obj_t com, const char *method, talk_t json );
void         *ccall2t( obj_t com, const char *method, talk_t json, talk_t json2 );
void         *ccall4p( obj_t obj, const char *method, void *pointer, void *pointer2, void *pointer3, void *pointer4 );
void         *scallt( const char *com, const char *method, talk_t json );
void         *scall2t( const char *com, const char *method, talk_t json, talk_t json2  );
void         *scall4p( const char *obj, const char *method, void *pointer, void *pointer2, void *pointer3, void *pointer4 );
/**
 * @brief call a component method use parameter of string
 * @param[in] com a object or string description for object
 * @param[in] method name of method function
 * @param[in] paramformat string for parameter description
 * @return return the component method's return when succeed or error return when call failed
 * 		@retval same the ccall
 */
void         *ccalls( obj_t com, const char *method, const char *paramformat, ... );
void         *scalls( const char *com, const char *method, const char *paramformat, ... );
/**
 * @brief call a component method, get the string return
 * @param[out] buffer buffer the string will be store here
 * @param[in] buflen size of buffer
 * @param[in] com a object or string description for object
 * @param[in] method name of method function
 * @param[in] parameter a pointer of parameter structure
 * @return return the component method's return when succeed or NULL return when call failed
 * 		@retval string for component method's return succeed
 * 		@retval NULL for component none return
 * 		@retval NULL for call failed, and errno code will be sets
 */
const char   *ccall_string( char *buffer, int buflen, obj_t com, const char *method, param_t parameter );
const char   *scall_string( char *buffer, int buflen, const char *com, const char *method, param_t parameter );
/**
 * @brief call a component method use parameter of talk, get the string return
 * @param[out] buffer buffer the string will be store here
 * @param[in] buflen size of buffer
 * @param[in] com a object or string description for object
 * @param[in] method name of method function
 * @param[in] json a pointer of talk structure for parameter
 * @return return the component method's return when succeed or NULL return when call failed
 * 		@retval string for component method's return succeed
 * 		@retval NULL for component none return
 * 		@retval NULL for call failed, and errno code will be sets
 */
const char   *ccallt_string( char *buffer, int buflen, obj_t com, const char *method, talk_t json );
const char   *scallt_string( char *buffer, int buflen, const char *com, const char *method, talk_t json );
/**
 * @brief call a component method use parameter of string, get the string return
 * @param[out] buffer buffer the string will be store here
 * @param[in] buflen size of buffer
 * @param[in] com a object or string description for object
 * @param[in] method name of method function
 * @param[in] paramformat string for parameter description
 * @return return the component method's return when succeed or NULL return when call failed
 * 		@retval string for component method's return succeed
 * 		@retval NULL for component none return
 * 		@retval NULL for call failed, and errno code will be sets
 */
const char   *ccalls_string( char *buffer, int buflen, obj_t com, const char *method, const char *paramformat, ... );
const char   *scalls_string( char *buffer, int buflen, const char *com, const char *method, const char *paramformat, ... );



/**
 * @brief set a component configure with json value
 * @param[in] com a object or string description for object
 * @param[in] value a json
 * @param[in] attr a attribute or string description for attribute
 * @return return the operation is succeed or failed
 * 		@retval true for succeed
 *  	@retval false for failed, and errno code will be sets
 */
boole cset( obj_t com, talk_t value, attr_t attr );
boole csets( obj_t com, talk_t value, const char *attr, ... );
boole sset( const char *com, talk_t value, attr_t attr );
boole ssets( const char *com, talk_t value, const char *attr, ... );
/**
 * @brief set a component configure with string value
 * @param[in] com a object or string description for object
 * @param[in] value string
 * @param[in] attr a attribute or string description for attribute
 * @return return the operation is succeed or failed
 * 		@retval true for succeed
 *  	@retval false for failed, and errno code will be sets
 */
boole cset_string( obj_t com, const char *value, attr_t attr );
boole csets_string( obj_t com, const char *value, const char *attr, ... );
boole sset_string( const char *com, const char *value, attr_t attr );
boole ssets_string( const char *com, const char *value, const char *attr, ... );



/**
 * @brief get a component configure value in json(dynamic allocation)
 * @param[in] com a object or string description for object
 * @param[in] attr a attribute or string description for attribute
 * @return return the component configure
 * 		@retval talk for component configure
 * 		@retval NULL for none component configure

 *  	@retval TALK_EINVAL for invaild options, the errno code will be sets
 *  	@retval TALK_EPERM for permission denied, the errno code will be sets
 *  	@retval TALK_EJSON for json format error, the errno code will be sets
 */
void          *cget( obj_t com, attr_t attr );
void          *cgets( obj_t com, const char *attr, ... );
void          *sget( const char *com, attr_t attr );
void          *sgets( const char *com, const char *attr, ... );
/**
 * @brief get a component configure value in string
 * @param[out] buffer buffer the string will be store here
 * @param[in] buflen size of buffer
 * @param[in] com a object or string description for object
 * @param[in] attr a attribute or string description for attribute
 * @return return the component configure
 * 		@retval string for get component configure succeed
 * 		@retval NULL for none component configure
 * 		@retval NULL for failed, and errno code will be sets
 */
const char    *cget_string( char *buffer, int buflen, obj_t com, attr_t attr );
const char    *cgets_string( char *buffer, int buflen, obj_t com, const char *attr, ... );
const char    *sget_string( char *buffer, int buflen, const char *com, attr_t attr );
const char    *sgets_string( char *buffer, int buflen, const char *com, const char *attr, ... );



#endif   /* ----- #ifndef H_LAND_COM_H  ----- */

