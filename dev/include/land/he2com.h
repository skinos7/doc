#ifndef H_LAND_HE2COM_H
#define H_LAND_HE2COM_H

/**
 * @file he2com.h
 * @author dimmalex@gmail.com
 * @version 7.0
 * @date 20220219
 * @brief The command line invokes the function implementation required by the component
 */



/* he command type */
#define HE_OBJECT_TAG   0           /* default, component configure get */
#define HE_FILE_TAG     '/'         /* absolute path to the file */
#define HE_CALL_TAG     '.'         /* method call */
#define HE_CONFIG_TAG   ':'         /* configure attribute */
#define HE_SET_TAG      '='         /* set the configure value */
#define HE_OR_TAG       '|'         /* modify the configure value */
#define HE_PARAM_TAG    '['         /* parameter start */
#define HE_PARAMEND_TAG ']'         /* parameter end */
/* he command structure */
typedef struct he_st
{
    /* he type */
    int flags;
    /* component */
    obj_t o;                                           // need free
    /* method */
    char *m;
    /* parameter */
    param_t p;                                         // need free
    /* configure attribute */
    attr_t a;                                          // need free
    /* value */
    talk_t v;                                          // need free
    // buffer for command
    char *buffer;                                      // need free
    // command
    char *cmd;                                         // need free
} he_struct;
typedef he_struct* he_t;



/**
 * @brief parse he command into their corresponding structures
 * @param[in] string he command
 * @return a pointer of he structure
 * 		@retval he for succeed
 *  	@retval NULL for failed, the errno code will be sets
 */
he_t string2he( const char *cmd );
/**
 * @brief parse he talk into their corresponding structures
 * @param[in] cmd he talk
 * @return a pointer of he structure
 * 		@retval he for succeed
 *  	@retval NULL for failed, the errno code will be sets
 */
he_t talk2he( talk_t cmd );
/**
 * @brief make he talk depend he structure
 * @param[in] p a pointer of he structure
 * @return a pointer of he talk
 * 		@retval talk for succeed
 *  	@retval NULL for failed, the errno code will be sets
 */
talk_t he2talk( he_t p );
/**
 * @brief free a he structure
 * @param[in] p a pointer of he structure
 * @return none
 */
void he_free( he_t p );
/**
 * @brief execute a he command
 * @param[in] cmd a pointer of he structure
 * @return a pointer of json
 *		@retval json for peer succeed
 *		@retval NULL for peer return
 *		@retval ttrue for peer return
 *		@retval tfalse for peer return
 *		@retval NULL for peer failed, the errno code will be sets
 *  	@retval terror for peer got wrong, the errno code will be sets

 *  	@retval TALK_EINVAL for calling of parameter error, and errno code will be EINVAL
 *  	@retval TALK_ECOM for calling of cannot find the component, the errno code will be ENOENT
 *  	@retval TALK_EPERM for calling of permission denied, the errno code will be EPERM
 *  	@retval TALK_EFUNC for calling of cannot find the component method, the errno code will be ENOSYS
 *  	@retval TALK_EPIPE for calling of pipe faild, the errno code will be sets
 *  	@retval TALK_EFORK for calling of fork faild, the errno code will be sets
 *  	@retval TALK_EJSON for calling of peer component return wrong data, the errno code will be ENOMSG
 */
talk_t he_execute( he_t cmd );



/**
 * @brief execute a string he command
 * @param[in] string he command
 * @return suceess or failed
 *		@retval 0 for suceess
 *		@retval <0 for failed
 */
int string_he_command( const char *cmd );
/**
 * @brief execute a json he command
 * @param[in] json he command
 * @return json command result
 */
talk_t json_he_command( talk_t cmd );



#endif   /* ----- #ifndef H_LAND_HE2COM_H  ----- */

