#ifndef H_LAND_CONFIG_H
#define H_LAND_CONFIG_H

/**
 * @file config.h
 * @author dimmalex@gmail.com
 * @version 7.0
 * @date 20220219
 * @brief implementation function to get/set/list the config
 */



/**
 * @brief set the value of configuration of the object
 * @param[in] com a object or string description for object
 * @param[in] value a json or string
 * @param[in] attr a attribute or string description for attribute
 * @return the operation is succeed or failed
 *		@retval ttrue for succeed
 *		@retval tfalse for failed, and errno code will be sets
 */
boole config_set( obj_t com, talk_t value, attr_t attr );
boole config_sset( const char *com, talk_t value, attr_t attr );
boole config_ssets( const char *com, talk_t value, const char *attr, ... );
boole config_set_string( obj_t com, const char *value, attr_t attr );
boole config_sset_string( const char *com, const char *value, attr_t attr );
boole config_ssets_string( const char *com, const char *value, const char *attr, ... );



/**
 * @brief get the configuration of the object(dynamic allocation)
 * @param[in] com a object or string description for object
 * @param[in] attr a attribute or string description for attribute
 * @return json
 *		@retval json for succeed
 *		@retval NULL for failed, the errno code will be sets
 *  	@retval TALK_EINVAL for invaild options, the errno code will be sets
 *  	@retval TALK_EPERM for permission denied, the errno code will be sets
 *  	@retval TALK_EJSON for json format error, the errno code will be sets
 */
talk_t      config_get( obj_t com, attr_t attr );
talk_t      config_sget( const char *com, attr_t attr );
talk_t      config_sgets( const char *com, const char *attr, ... );
/**
 * @brief get the configuration attribute value of the object
 * @param[out] buffer buffer the string will be store here
 * @param[in] buflen size of buffer
 * @param[in] com a object or string description for object
 * @param[in] attr a attribute or string description for attribute
 * @return string
 *		@retval string for succeed
 * 		@retval NULL for none configure attribute, and errno code be zero
 * 		@retval NULL for failed, and errno code will be sets
 */
const char *config_get_string( char *buffer, int buflen, obj_t com, attr_t attr );
const char *config_gets_string( char *buffer, int buflen, obj_t com, const char *attr, ... );
const char *config_sgets_string( char *buffer, int buflen, const char *com, const char *attr, ... );



/**
 * @brief get the configuration list of the object or all system(dynamic allocation)
 * @param[in] project project name
 * @return a pointer of json for config list
 *		@retval json for succeed
 *		@retval <TALK_ECODEMAX for failed, and errno code will be sets
 */
talk_t config_list(   const char *project );
/**
 * @brief get the configure pathname
 * @param[out] buffer buffer the configure pathname will be store here
 * @param[in] buflen size of buffer
 * @param[in] project project name
 * @param[in] oscformat configure file
 * @return configure pathname
 *		@retval string for succeed
 *		@retval NULL for failed, and errno code will be sets
 */
const char *config_path(    char *buffer, int buflen, const char *project, const char *oscformat, ... );



#endif   /* ----- #ifndef H_LAND_CONFIG_H  ----- */

