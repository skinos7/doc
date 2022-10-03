#ifndef H_LAND_PARAM_H
#define H_LAND_PARAM_H
/**
 * @file param.h
 * @author dimmalex@gmail.com
 * @version 7.0
 * @date 20220219
 * @brief implementation of parameter structure and related functions
 * @details used to pass strings or talk_t when called, component's function need accept a pointer of pararmter structure, strings and talk can build into paramter as options
 */



/// Maximum options in one paramter structure
#define PARAM_OPTIONS_MAX 20

/// parameter structure
/// example: 'myname,{"test":"testvalue"},test3' of options description for parameter
///    		 "myname" is first option, is a string option
///    		 '{"test":"testvalue"}' second option, is a json option
///    		 "test3" is third option, is a string option
typedef struct param_st
{
	// what serial number does the start with
    // example: offset is 0
	int start;

	// what serial number does the end with
    // example: size is 3
    int end;

    // string options pointer
    // example: id[0] point to "myname"
    // 			id[1] point to '{"test":"testvalue"}'
    // 			id[2] point to "test3"
    char *option[PARAM_OPTIONS_MAX];

    // talk options pointer
    // example: id[0] point to NULL
    // 			id[1] point to a talk of {"test":"testvalue"}
    // 			id[2] point to NULL
    talk_t talk[PARAM_OPTIONS_MAX];                                 // need free at param_free()

    // readable compiled string for this parameter
    // example: 'myname,{"test":"testvalue"},test3'
    char *string;                                                   // need free at param_free()

	// description the option is modifyied
	boole dirty;

} param_struct;
typedef param_struct* param_t;



/**
 * @brief create a structure of parameter depend on string of options description
 * @param[in] options string description for options
 * @return a pointer of parameter
 * 		@retval param for succeed
 *  	@retval NULL for error, errno will be sets
 */
param_t     param_create( const char *options );
/**
 * @brief create a structure of parameter from json description
 * @param[in] talk 1/2/3/4 attr will be dup as the options
 * @return a pointer of parameter
 * 		@retval param for succeed
 *  	@retval NULL for error, errno will be sets
 */
param_t     param_build( talk_t json );
/**
 * @brief create a structure of parameter related json
 * @param[out] param a pointer of paramter, calloc a new paramter when this is NULL
 * @param[in] json the talk will be first and only option
 * @return a pointer of parameter
 * 		@retval param for succeed
 *  	@retval NULL for error, errno will be sets
 */
param_t     param_import( param_t param, talk_t json );
/**
 * @brief create a structure of parameter related json
 * @param[out] param a pointer of paramter, calloc a new paramter when this is NULL
 * @param[in] json the talk will be first option
 * @param[in] json2 the talk will be second option
 * @return a pointer of parameter
 * 		@retval param for succeed
 *  	@retval NULL for error, errno will be sets
 */
param_t     param_import2( param_t param, talk_t json, talk_t json2 );
/**
 * @brief adjust param beginning location, increase starting location
 * @param[in] param pointer of parameter
 * @param[in] number increase few starting location
 * @return opertion succeed or failed
 *		@retval 0 for succeed
 *		@retval negative for failed, the errno code will be sets
 */
boole       param_shift( param_t param, int number );
/**
 * @brief adjust param beginning location, decrease starting location
 * @param[in] param pointer of parameter
 * @param[in] number decrease few starting location
 * @return opertion succeed or failed
 *		@retval 0 for succeed
 *		@retval negative for failed, the errno code will be sets
 */
boole       param_unshift( param_t param, int number );
/**
 * @brief free a parameter
 * @param[in] param pointer of parameter
 * @return none
 */
void        param_free( param_t param );



/**
 * @brief get how many options in parameter
 * @param[in] param a pinter of parameter
 * @return number of options
 * 		@retval positive or zeore for succeed
 *  	@retval negative for error, errno will be sets
 */
int         param_size( param_t param );
/**
 * @brief get string option of required from parameter
 * @param[in] param a pinter of parameter
 * @param[in] serial serial number( It starts 1 ), -1 will for get the last option
 * @return string option
 * 		@retval string succeed
 *  	@retval NULL error, errno will be sets
 */
const char *param_string( param_t param, int serial );

/**
 * @brief get talk option of required from parameter
 * @param[in] param a pinter of parameter
 * @param[in] serial serial number( It starts 1 ), -1 will for get the last option
 * @return talk option
 * 		@retval talk succeed
 *  	@retval NULL error, errno will be sets
 */
talk_t      param_talk( param_t param, int serial );
/**
 * @brief get string of the options description with parameter
 * @param[in] param a pinter of parameter
 * @return string of the options description
 * 		@retval string for succeed
 *  	@retval NULL for error, errno will be sets
 */
const char *param_combine( param_t param );



#endif   /* ----- #ifndef H_LAND_PARAM_H  ----- */

