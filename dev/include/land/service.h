#ifndef H_LAND_SERVICE_H
#define H_LAND_SERVICE_H

/**
 * @file service.h
 * @author dimmalex@gmail.com
 * @version 7.0
 * @date 20220219
 * @brief service management implementation
 */



/// service exit code
#define EXIT_ttrue     101
#define EXIT_tfalse    102
#define EXIT_terror    103
#define EXIT_EINVAL    104
#define EXIT_EPERM     105
#define EXIT_ECOM      106
#define EXIT_EFUNC     107
#define EXIT_EFORK     108
/// talk to service management
talk_t service_call( const char *cmd, talk_t v, int timeout );



/**
 * @brief register a service
 * @param[in] delay a pointer of object structure of component
 * @param[in] com a pointer of object structure of component
 * @param[in] method name of method function
 * @param[in] param a pointer of parameter structure
 * @param[in] nameformat string for name
 * @return succeed or failed
 *		@retval true for succeed
 *		@retval false for failed
 */
boole crun( int delay, obj_t com, const char *method, param_t param, const char *nameformat, ... );
boole srun( int delay, const char *com, const char *method, param_t param, const char *nameformat, ...  );
/**
 * @brief register a service
 * @param[in] delay a pointer of object structure of component
 * @param[in] com a pointer of object structure of component
 * @param[in] method name of method function
 * @param[in] json a pointer of talk structure for parameter
 * @param[in] nameformat string for name
 * @return succeed or failed
 *		@retval true for succeed
 *		@retval false for failed
 */
boole crunt( int delay, obj_t com, const char *method, talk_t json, const char *nameformat, ... );
boole srunt( int delay, const char *com, const char *method, talk_t json, const char *nameformat, ... );
boole crun2t( int delay, obj_t com, const char *method, talk_t json, talk_t json2, const char *nameformat, ... );
boole srun2t( int delay, const char *com, const char *method, talk_t json, talk_t json2, const char *nameformat, ...  );
/**
 * @brief register a service
 * @param[in] delay a pointer of object structure of component
 * @param[in] name string for name
 * @param[in] com a pointer of object structure of component
 * @param[in] method name of method function
 * @param[in] paramformat string for parameter
 * @return succeed or failed
 *		@retval true for succeed
 *		@retval false for failed
 */
boole cruns( int delay, const char *name, obj_t com, const char *method, const char *paramformat, ... );
boole sruns( int delay, const char *name, const char *com, const char *method, const char *paramformat, ... );



/**
 * @brief reset a service or start a service use the component method
 * @param[in] com a pointer of object structure of component
 * @param[in] method name of method function
 * @param[in] param a pointer of parameter structure
 * @param[in] nameformat string for name
 * @return succeed or failed
 *		@retval true for succeed
 *		@retval false for failed
 */
boole creset( obj_t com, const char *method, param_t param, const char *nameformat, ... );
boole sreset( const char *com, const char *method, param_t param, const char *nameformat, ...  );
/**
 * @brief reset a service or start a service use the component method
 * @param[in] com a pointer of object structure of component
 * @param[in] method name of method function
 * @param[in] json a pointer of talk structure for parameter
 * @param[in] nameformat string for name
 * @return succeed or failed
 *		@retval true for succeed
 *		@retval false for failed
 */
boole cresett( obj_t com, const char *method, talk_t json, const char *nameformat, ... );
boole sresett( const char *com, const char *method, talk_t json, const char *nameformat, ... );
boole creset2t( obj_t com, const char *method, talk_t json, talk_t json2, const char *nameformat, ... );
boole sreset2t( const char *com, const char *method, talk_t json, talk_t json2, const char *nameformat, ...  );
/**
 * @brief reset a service or start a service use the component method
 * @param[in] name string for name
 * @param[in] com a pointer of object structure of component
 * @param[in] method name of method function
 * @param[in] paramformat string for parameter
 * @return succeed or failed
 *		@retval true for succeed
 *		@retval false for failed
 */
boole cresets( const char *name, obj_t com, const char *method, const char *paramformat, ... );
boole sresets( const char *name, const char *com, const char *method, const char *paramformat, ... );



/**
 * @brief start a service
 * @param[in] com a pointer of object structure of component
 * @param[in] method name of method function
 * @param[in] param a pointer of parameter structure
 * @param[in] nameformat string for name
 * @return succeed or failed
 *		@retval true for succeed
 *		@retval false for failed
 */
boole cstart( obj_t com, const char *method, param_t param, const char *nameformat, ... );
boole sstart( const char *com, const char *method, param_t param, const char *nameformat, ...  );
/**
 * @brief start a service
 * @param[in] com a pointer of object structure of component
 * @param[in] method name of method function
 * @param[in] json a pointer of talk structure for parameter
 * @param[in] nameformat string for name
 * @return succeed or failed
 *		@retval true for succeed
 *		@retval false for failed
 */
boole cstartt( obj_t com, const char *method, talk_t json, const char *nameformat, ... );
boole cstart2t( obj_t com, const char *method, talk_t json, talk_t json2, const char *nameformat, ... );
boole sstartt( const char *com, const char *method, talk_t json, const char *nameformat, ... );
boole sstart2t( const char *com, const char *method, talk_t json, talk_t json2, const char *nameformat, ...  );
/**
 * @brief start a service
 * @param[in] name string for name
 * @param[in] com a pointer of object structure of component
 * @param[in] method name of method function
 * @param[in] paramformat string for parameter
 * @return succeed or failed
 *		@retval true for succeed
 *		@retval false for failed
 */
boole cstarts( const char *name, obj_t com, const char *method, const char *paramformat, ... );
boole sstarts( const char *name, const char *com, const char *method, const char *paramformat, ... );



/*
* @brief delete a service
* @param[in] nameformat string for name
* @return succeed or failed
*	   @retval true for succeed
*	   @retval false for failed
*/
boole sdelete( const char *nameformat, ... );
/*
* @brief stop a service
* @param[in] nameformat string for name
* @return succeed or failed
*	   @retval true for succeed
*	   @retval false for failed
*/
boole sstop( const char *nameformat, ... );
/*
* @brief take off a service
* @param[in] nameformat string for name
* @return succeed or failed
*	   @retval true for succeed
*	   @retval false for failed
*/
boole soff( const char *nameformat, ... );
/*
* @brief get a service pid
* @param[in] nameformat string for name
* @return service pid
*	   @retval >=0 for succeed
*	   @retval <0 for failed
*/
pid_t spid( const char *nameformat, ... );
/*
* @brief get a service infomation
* @param[in] nameformat string for name
* @return succeed or failed
*	   @retval true for succeed
*	   @retval false for failed
*/
talk_t sinfo( const char *nameformat, ... );
/*
* @brief get all service list
* @return service list
*	   @retval talk for succeed
*	   @retval NULL for failed
*/
talk_t slist( void );



#endif   /* ----- #ifndef H_LAND_SERVICE_H  ----- */

