#ifndef H_LAND_TALK_H
#define H_LAND_TALK_H

/**
 * @file talk.h
 * @author dimmalex@gmail.com
 * @version 7.0
 * @date 20220219
 * @brief Implementation of common communication data types
 * @details common communication data types named talk_t, Used for information transfer between components, Used by configuration information, Even for information interaction with users
 */



/// The important part is based on JSON implementation
#include "json.h"
/// The beginning character of Base64 encode JSON string
#define JSON_BASE64_PREFIX '^'
/// The beginning character of readable JSON string
#define JSON_STRING_PREFIX '{'
/// The operator options for patch
#define JSON_PATCH_OPERATOR "~op"
/// talk_st equal json_t
typedef json_t talk_struct;

/// talk_t is a pointer of talk_st
typedef talk_struct* talk_t;
/// tnull retruning by interface function hint that no information is available
/// tnull retruning by service function hint everything is fine
#define tnull (talk_t)NULL

/// talk_t also can point to boole_t
typedef talk_t   boole_t;
/// ttrue retruning by interface function hint operator succceed
#define ttrue_code          1
#define ttrue      (boole_t)ttrue_code
/// tfalse retruning by interface function hint operator failed
/// tfalse retruning by service function hint service failed( need restart the service )
#define tfalse_code         2
#define tfalse     (boole_t)tfalse_code
/// tfalse retruning by interface function hint operator error
/// tfalse retruning by service function hint service error( don't restart the service )
#define terror_code         3
#define terror     (talk_t)terror_code

/// TALK_EINVAL returning by calling mechanism accident for the call invalid
#define TALK_EINVAL_code    4
#define TALK_EINVAL (talk_t)TALK_EINVAL_code
/// TALK_EPERM returning by calling mechanism accident for permission denied 
#define TALK_EPERM_code     5
#define TALK_EPERM   (talk_t)TALK_EPERM_code
/// TALK_ECOM returning by calling mechanism accident for cannot found the corresponding component 
#define TALK_ECOM_code      6
#define TALK_ECOM   (talk_t)TALK_ECOM_code
/// TALK_EFUNC returning by calling mechanism accident for cannot found the corresponding function 
#define TALK_EFUNC_code     7
#define TALK_EFUNC  (talk_t)TALK_EFUNC_code
/// TALK_EFORK returning by calling mechanism accident for fork error 
#define TALK_EFORK_code     8
#define TALK_EFORK  (talk_t)TALK_EFORK_code
/// TALK_EPIPE returning by calling mechanism accident for pipe error
#define TALK_EPIPE_code     9
#define TALK_EPIPE  (talk_t)TALK_EPIPE_code
/// TALK_EJSON returning by calling mechanism accident for data of component return is wrong format
#define TALK_EJSON_code     10
#define TALK_EJSON  (talk_t)TALK_EJSON_code
/// TALK_ETIME returning by calling mechanism accident for wait data timeout
#define TALK_ETIME_code     11
#define TALK_ETIME  (talk_t)TALK_ETIME_code

/// (talk_t)11 to (talk_t)256 for later extension and customer customization
/// TALK_CODEMAX is the max of the code  
#define TALK_ECODEMAX_code    30
#define TALK_ECODEMAX (talk_t)TALK_ECODEMAX_code



/** @brief The mapping between talk_t and string JSON

{ // beginning of json object, talk_t pointing to it, top json we call it json object

    // axp, axp_t pointing to it, "name" is identify as a string, "dim" is value as a string
    "name":"dim"

    // beginning of axp its identify is "info", axp_t pointing to it, "info" is identify as a string, {} follow is value as a json
    "info":
    { // beginning of json
		// axp, axp_t pointing to it, "age" is identify as a string, "30" is value as a number
        "age":30,

		// axp, axp_t pointing to it, "level" is identify as a string, "low" is value as a string
        "level":"low"

    } // ending of json
	// ending of axp its idenfity is "info"

} // ending of json object

summarize:
	Three value of data content:
		string/nubmer( const char * )
		integer( int )
		boolean( boole )
	Tree structure pointers:
		json(It be point by talk_t), {}
		axp(It could also be point by talk_t), attribute identify must be x(string), value can be json or x(string/integer/boolean)
		x(It could also be point by talk_t), actual data, content can be string/integer/boolean
*/



/**
 * @brief create string from x(dynamic allocation)
 * @param[in] x
 * @return string
 * 		@retval string for succeed
 *  	@retval NULL for error, the errno code will be sets
 */
#define     x2string talk2string
/**
 * @brief create x(dynamic allocation), which content is string
 * @param[in] string
 * @return x
 * 		@retval x for succeed
 *  	@retval NULL error, the errno code will be sets
 */
#define     string2x string2talk
/**
 * @brief get number from x
 * @param[in] x
 * @return number
 * 		@retval number for succeed
 *  	@retval 0 for value is 0
 *  	@retval 0 for error, the errno code will be sets
 */
int 		x2number( talk_t x );
/**
 * @brief create x(dynamic allocation), which content is string
 * @param[in] number
 * @return x
 * 		@retval x for succeed
 *  	@retval NULL error, the errno code will be sets
 */
talk_t		number2x( int number );
		/**
		 * @brief get integer from x
		 * @param[in] x
		 * @return integer
		 * 		@retval integer for succeed
		 *  	@retval 0 for value is 0
		 *  	@retval 0 for error, the errno code will be sets
		 */
		int 		x2int( talk_t json );
		/**
		 * @brief create x(dynamic allocation), which content is integer
		 * @param[in] integer
		 * @return x
		 * 		@retval x for succeed
		 *  	@retval NULL error, the errno code will be sets
		 */
		talk_t		int2x( int integer );
		/**
		 * @brief get boolean from x
		 * @param[in] x
		 * @return boolean
		 * 		@retval true for succeed
		 *  	@retval false for value is false
		 *  	@retval false for error, the errno code will be sets
		 */
		boole 		x2boole( talk_t json );
		/**
		 * @brief create x(dynamic allocation), which content is boolean
		 * @param[in] boolean
		 * @return x
		 * 		@retval x for succeed
		 *  	@retval NULL error, the errno code will be sets
		 */
		talk_t		boole2x( boole boolean );
/**
 * @brief determines whether the talk is or not is x
 * @param[in] v
 * @return true for x, false for other
 * 		@retval true for x
 *  	@retval false for not
 */
boole       x_check( talk_t v );
/**
 * @brief dup x(dynamic allocation)
 * @param[in] x
 * @return x
 * 		@retval x for succeed
 *  	@retval NULL error, the errno code will be sets
 */
#define     x_dup talk_dup
/**
 * @brief free x
 * @param[in] x
 * @return none
 */
#define     x_free talk_free
/**
 * @brief get the string conetent of x, this value is also not available when the x is released
 * @param[in] x
 * @return string
 */
#define     x_text( x )   (x>TALK_ECODEMAX?x->text:NULL)



/**
 * @brief create a axp(dynamic allocation)
 * @param[in] attr attribute idenfity, this string only copy to json
 * @param[in] string value in string type, this string only copy to json
 * @param[in] v v can be x/json, this parameter is valid when string is NULL, this parameter will be linkin to the axp which will be returned
 * @return axp
 * 		@retval axp for succeed
 *  	@retval NULL error, the errno code will be sets
 */
talk_t      axp_create( const char *attr, const char *string, talk_t v );
/**
 * @brief dup axp(dynamic allocation)
 * @param[in] axp
 * @return axp
 * 		@retval axp for succeed
 *  	@retval NULL error, the errno code will be sets
 */
#define     axp_dup talk_dup
/**
 * @brief free axp
 * @param[in] axp
 * @return none
 */
#define     axp_free talk_free
/**
 * @brief set attribute name of axp
 * @param[in] axp
 * @param[in] attr, this string only copy to json
 * @return operation success or failure
 * 		@retval true for succeed
 *  	@retval false for failure, the errno code will be sets
 */
boole       axp_set_id( talk_t axp, const char *attr );
#define     axp_set_attr axp_set_id
/**
 * @brief set axp value which is string type
 * @param[in] axp
 * @param[in] string, this string only copy to axp
 * @return operation success or failure
 * 		@retval true for succeed
 *  	@retval false for failure, the errno code will be sets
 */
boole       axp_set_string( talk_t axp, const char *string );
		/**
		 * @brief set axp value which is integer type
		 * @param[in] axp
		 * @param[in] integer
		 * @return operation success or failure
		 * 		@retval true for succeed
		 *  	@retval false for failure, the errno code will be sets
		 */
		boole       axp_set_int( talk_t axp, int integer );
		/**
		 * @brief set axp value which is boolean type
		 * @param[in] axp
		 * @param[in] boolean
		 * @return operation success or failure
		 * 		@retval true for succeed
		 *  	@retval false for failure, the errno code will be sets
		 */
		boole       axp_set_boole( talk_t axp, boole boolean );
/**
 * @brief set axp value which is json
 * @param[in] axp
 * @param[in] json, this parameter will be linkin to the axp
 * @return operation success or failure
 *		@retval true for succeed
 *		@retval false for failure, the errno code will be sets
 */
boole       axp_set_json( talk_t axp, talk_t json );
/**
 * @brief set axp value which can be x/json
 * @param[in] axp
 * @param[in] json, this parameter will be linkin to the axp
 * @return operation success or failure
 *		@retval true for succeed
 *		@retval false for failure, the errno code will be sets
 */
boole       axp_set_value( talk_t axp, talk_t value );
/**
 * @brief strip and return axp value, which value can be x/json
 * @param[in] axp
 * @return x/json
 * 		@retval x/json for succeed
 *  	@retval NULL error, the errno code will be sets
 */
talk_t      axp_cut_value( talk_t axp );
/**
 * @brief delete axp value
 * @param[in] axp
 * @return operation success or failure
 * 		@retval true for succeed
 *  	@retval false for failure, the errno code will be sets
 */
boole       axp_delete_value( talk_t axp );



/**
 * @brief determines whether the talk is or not is axp
 * @param[in] v
 * @return true for axp, false for other
 * 		@retval true for axp
 *  	@retval false for not axp, the errno code will be sets
 */
boole       axp_check( talk_t v );
/**
 * @brief get the attribute name of axp, this value is also not available when the axp is released
 * @param[in] axp
 * @return attribute name
 * 		@retval string for succeed
 *  	@retval NULL for error, the errno code will be sets
 */
const char *axp_id( talk_t axp );
#define     axp_get_attr axp_id
/**
 * @brief get the value of axp, which value in string type, this value is also not available when the axp is released
 * @param[in] axp
 * @return value in string type
 * 		@retval string for succeed
 *  	@retval NULL for error, the errno code will be sets
 */
const char *axp_string( talk_t axp );
#define     axp_get_string axp_string
		/**
		 * @brief get the value of axp, which value in integer type
		 * @param[in] axp
		 * @return value in integer type
		 *		@retval integer for succeed
		 *		@retval 0 for value is 0
		 *		@retval 0 for error, the errno code will be sets
		 */
		int         axp_int( talk_t axp );
		/**
		 * @brief get the value of axp, which value in boolean type
		 * @param[in] axp
		 * @return value in boolean type
		 * 		@retval true for succeed
		 *  	@retval false for value is false
		 *  	@retval false for error, the errno code will be sets
		 */
		boole       axp_boole( talk_t axp );
/**
 * @brief get the value of axp, which value in json type, this value is also not available when the axp is released
 * @param[in] axp
 * @return json
 * 		@retval json for succeed
 *  	@retval NULL for value is NULL
 *  	@retval NULL for error, the errno code will be sets
 */
talk_t		axp_json( talk_t axp );
#define     axp_get_json axp_json
/**
 * @brief get the value of axp, which value can be x/json, this value is also not available when the axp is released
 * @param[in] axp
 * @return x/json
 *		@retval x/json for succeed
 *		@retval NULL for value is NULL
 *		@retval NULL for error, the errno code will be sets
 */
talk_t      axp_value( talk_t axp );
#define     axp_get_value axp_value
/**
 * @brief create string from axp(dynamic allocation)
 * @param[in] axp
 * @return string
 *		@retval string for succeed
 *		@retval NULL for error, the errno code will be sets
 */ 
#define     axp2string talk2string



/**
 * @brief create a json(dynamic allocation)
 * @param[in] axp create empty json when this is NULL, not NULL will be first axp at new json when be create
 * @return json
 * 		@retval json for succeed
 *  	@retval NULL error, the errno code will be sets
 */
talk_t      json_create( talk_t axp );
/**
 * @brief dup json(dynamic allocation)
 * @param[in] json
 * @return json
 * 		@retval json for succeed
 *  	@retval NULL error, the errno code will be sets
 */
#define     json_dup talk_dup
/**
 * @brief free json
 * @param[in] json
 * @return none
 */
#define     json_free talk_free
/**
 * @brief set axp value in json, which value is string type
 * @param[in] json
 * @param[in] attr attribute name
 * @param[in] string value, this string only copy to json
 * @return operation succeed or failed
 * 		@retval true for succeed
 *  	@retval false for failed
 */
boole       json_set_string( talk_t json, const char *attr, const char *string );
/**
 * @brief set axp value in json, which value is string type
 * @param[in] json
 * @param[in] attr attribute name
 * @param[in] number value
 * @return operation succeed or failed
 * 		@retval true for succeed
 *  	@retval false for failed
 */
boole       json_set_number( talk_t json, const char *attr, int integer );
		/**
		 * @brief set axp value in json, which value is double type
		 * @param[in] json
		 * @param[in] attr attribute name
		 * @param[in] format string format
		 * @param[in] floatpoint floatpoint value
		 * @return operation succeed or failed
		 * 		@retval true for succeed
		 *  	@retval false for failed
		 */
		boole       json_set_floatpoint( talk_t json, const char *attr, const char *format, double floatpoint );
		/**
		 * @brief set axp value in json, which value is pointer type
		 * @param[in] json
		 * @param[in] attr attribute name
		 * @param[in] pointer
		 * @return operation succeed or failed
		 * 		@retval true for succeed
		 *  	@retval false for failed
		 */
		boole       json_set_pointer( talk_t json, const char *attr, void *pointer );
		/**
		 * @brief set axp value in json, which value is character type
		 * @param[in] json
		 * @param[in] attr attribute name
		 * @param[in] character value
		 * @return operation succeed or failed
		 * 		@retval true for succeed
		 *  	@retval false for failed
		 */
		boole       json_set_char( talk_t json, const char *attr, char character );
		/**
		 * @brief set axp value in json, which value is integer type
		 * @param[in] json
		 * @param[in] attr attribute name
		 * @param[in] integer value
		 * @return operation succeed or failed
		 * 		@retval true for succeed
		 *  	@retval false for failed
		 */
		boole       json_set_int( talk_t json, const char *attr, int integer );
		/**
		 * @brief set axp value in json, which value is boolean type
		 * @param[in] json
		 * @param[in] attr attribute name
		 * @param[in] boolean value
		 * @return operation succeed or failed
		 * 		@retval true for succeed
		 *  	@retval false for failed
		 */
		boole       json_set_boole( talk_t json, const char *attr, boole boolean );
/**
 * @brief set axp value in json, which value is json
 * @param[in] json
 * @param[in] attr attribute name
 * @param[in] json value, this json well be linked in json
 * @return operation succeed or failed
 * 		@retval true for succeed
 *  	@retval false for failed, the errno code will be sets
 */
boole       json_set_json( talk_t json, const char *attr, talk_t jsonvalue );
/**
 * @brief set axp value in json, which value can be x/json
 * @param[in] json
 * @param[in] attr attribute name
 * @param[in] x/json value, this json well be linked in json
 * @return operation succeed or failed
 * 		@retval true for succeed
 *  	@retval false for failed, the errno code will be sets
 */
boole       json_set_value( talk_t json, const char *attr, talk_t value );
/**
 * @brief empty json 
 * @param[in] json
 * @return operation succeed or failed
 * 		@retval true for succeed
 *  	@retval false for failed, the errno code will be sets
 */
boole       json_empty( talk_t json );
/**
 * @brief sync the json by other json
 * @param[in] src source json
 * @param[in] dest destination json
 * @return operation succeed or failed
 * 		@retval 1 for sync succeed
 * 		@retval 0 for no modify
 *  	@retval negative for error, the errno code will be sets
 */
#define    json_patch talk_patch



/**
 * @brief determines whether the talk is or not is json
 * @param[in] json
 * @return true for json, false for other
 * 		@retval true for json
 *  	@retval false for not json, the errno code will be sets
 */
boole       json_check( talk_t json );
/**
 * @brief get the value of axp in json, which value in string type, this value is also not available when the json is released
 * @param[in] json
 * @param[in] attr attribute name
 * @return string
 * 		@retval string
 *  	@retval NULL for value is NULL
 *  	@retval NULL for error, the errno code will be sets
 */
const char *json_string( talk_t json, const char *attr );
#define     json_get_string json_string
/**
 * @brief get the value of axp in json, which value in number type
 * @param[in] json
 * @param[in] attr attribute name
 * @return number
 * 		@retval number for succeed
 *  	@retval 0 for value is 0
 *  	@retval 0 for not found, the errno code will be sets
 */
int         json_number( talk_t json, const char *attr );
#define     json_get_number json_number
		/**
		 * @brief get the value of axp in json, which value in pointer type
		 * @param[in] json
		 * @param[in] attr attribute name
		 * @return pointer
		 * 		@retval pointer for succeed
		 *  	@retval NULL for value is NULL
		 *  	@retval NULL for not found, the errno code will be sets
		 */
		void*       json_pointer( talk_t json, const char *attr );
		#define     json_get_pointer json_pointer
		/**
		 * @brief get the value of axp in json, which value in integer type
		 * @param[in] json
		 * @param[in] attr attribute name
		 * @return integer
		 * 		@retval integer for succeed
		 *  	@retval 0 for value is 0
		 *  	@retval 0 for not found, the errno code will be sets
		 */
		int         json_int( talk_t json, const char *attr );
		#define     json_get_int json_int
		/**
		 * @brief get the value of axp in json, which value in boolean type
		 * @param[in] json
		 * @param[in] attr attribute name
		 * @return boolean
		 * 		@retval true for succeed
		 *  	@retval false for value is false
		 *  	@retval false for not found, the errno code will be sets
		 */
		boole       json_boole( talk_t json, const char *attr );
		#define     json_get_boole json_boole
/**
 * @brief get axp in json, this value is also not available when the json is released
 * @param[in] json
 * @param[in] attr attribute name
 * @return axp
 *		@retval axp for succeed
 *		@retval NULL for value is NULL
 *		@retval NULL for error, the errno code will be sets
 */
talk_t      json_axp( talk_t json, const char *attr );
#define     json_get_axp json_axp
/**
 * @brief get value of axp in json, which value is json, this value is also not available when the json is released
 * @param[in] json
 * @param[in] attr attribute name
 * @return json
 *		@retval json for succeed
 *		@retval NULL for value is NULL
 *		@retval NULL for error, the errno code will be sets
 */
talk_t		json_json( talk_t json, const char *attr );
#define     json_get_json json_json
/**
 * @brief get value of axp in json, which value can be  x/json, this value is also not available when the json is released
 * @param[in] json
 * @param[in] attr attribute name
 * @return x/json
 *		@retval x/json for succeed
 *		@retval NULL for value is NULL
 *		@retval NULL for error, the errno code will be sets
 */
talk_t      json_value( talk_t json, const char *attr );
#define     json_get_value json_value
/**
 * @brief get the next axp of the json, this value is also not available when the json is released
 * @param[in] json
 * @param[in] axp return the first axp at the json when this is NULL, return NULL when this is the last axp
 * @return axp
 * 		@retval axp for succeed
 *  	@retval NULL for current axp is the last axp
 *  	@retval NULL for error, the errno code will be sets
 */
talk_t      json_next( talk_t json, talk_t axp );
#define     json_each json_next
/**
 * @brief get the previous axp of the json, this value is also not available when the json is released
 * @param[in] json
 * @param[in] axp return the last axp at the json when this is NULL, return NULL when this is the first axp
 * @return axp
 * 		@retval axp for succeed
 *  	@retval NULL for current axp is the first axp
 *  	@retval NULL for error, the errno code will be sets
 */
talk_t      json_prev( talk_t json, talk_t axp );
/**
 * @brief get how many axp in the json
 * @param[in] json
 * @return number
 * 		@retval 0 for empty json
 *  	@retval >0 number of axp
 *  	@retval <0 for error, the errno code will be sets
 */
int         json_size( talk_t json );
/**
 * @brief create string from json(dynamic allocation)
 * @param[in] json
 * @return string
 * 		@retval string for succeed
 *  	@retval NULL error, the errno code will be sets
 */
#define     json2string talk2string



/**
 * @brief delete axp from json
 * @param[in] json
 * @return attribute name
 * @return operation succeed or failed
 * 		@retval true for succeed
 *  	@retval false for error, the errno code will be sets
 */
boole       json_delete_axp( talk_t json, const char *attr );
/**
 * @brief strip a value from axp in the json and return it, which value can be x/json
 * @param[in] json
 * @return attribute name
 * @return x/json
 * 		@retval x/json for succeed, the x/json is disconnect from axp in json
 *  	@retval NULL for cannot find corresponding x/json
 *  	@retval NULL for error, the errno code will be sets
 */
talk_t      json_cut_value( talk_t json, const char *attr );
/**
 * @brief strip a value from axp in the json and return it, which value is a json
 * @param[in] json
 * @return attribute name
 * @return json
 * 		@retval json for succeed, the json is disconnect from axp in json
 *  	@retval NULL for cannot find corresponding json
 *  	@retval NULL for error, the errno code will be sets
 */
talk_t		json_cut_json( talk_t json, const char *attr );
/**
 * @brief strip a axp from json and return it
 * @param[in] json
 * @return attribute name
 * @return axp
 * 		@retval axp for succeed, the axp is disconnect from json
 *  	@retval NULL for cannot find corresponding axp
 *  	@retval NULL for error, the errno code will be sets
 */
talk_t      json_cut_axp( talk_t json, const char *attr );
/**
 * @brief attach/add axp to json
 * @param[in] json
 * @param[in] axp
 * @return operation succeed or failed
 * 		@retval true for succeed
 *  	@retval false for error, the errno code will be sets
 */
boole       json_attach_axp( talk_t json, talk_t axp );
/**
 * @brief detach/cut axp to json
 * @param[in] json
 * @param[in] axp
 * @return operation succeed or failed
 * 		@retval true for succeed
 *  	@retval false for error, the errno code will be sets
 */
boole       json_detach_axp( talk_t json, talk_t axp );



/**
 * @brief create talk from json format string(dynamic allocation)
 * @param[in] string json syntax
 * @return json
 * 		@retval json for succeed
 *  	@retval NULL error, the errno code will be sets
 */
talk_t      string2talk( const char *string );
/**
 * @brief create string from talk(dynamic allocation)
 * @param[in] json a pointer of json
 * @return string
 * 		@retval string for succeed
 *  	@retval NULL error, the errno code will be sets
 */
char       *talk2string( talk_t json );
/**
 * @brief load a JSON structure from a file(dynamic allocation)
 * @param[in] path filename
 * @return json
 * 		@retval json for succeed
 *  	@retval NULL for failed, the errno code will be sets
 */
talk_t      file2talk( const char *path );
/**
 * @brief store the JSON structure to a file
 * @param[in] json a pointer of json
 * @param[in] path filename
 * @return the number of characters written to the file
 * 		@retval positive for succeed
 *  	@retval negative for error, the errno code will be sets
 */
int         talk2file( talk_t json, const char *path );
/**
 * @brief dup the talk(dynamic allocation)
 * @param[in] json
 * @return json
 * 		@retval json for succeed
 *  	@retval NULL error, the errno code will be sets
 */
talk_t      talk_dup( talk_t json );
/**
 * @brief patch the talk by other talk
 * @param[in] src a pointer of json is refer json
 * @param[in] dest a pointer of json will be modify
 * @return operation succeed or failed
 * 		@retval 1 for patch succeed
 * 		@retval 0 for no modify
 *  	@retval negative for error, the errno code will be sets
 */
int         talk_patch( talk_t src, talk_t dest );
/**
 * @brief compare two talk are the same
 * @param[in] json
 * @param[in] json2
 * @return true or false
 * 		@retval true for same
 * 		@retval false for not smae
 */
boole       talk_equal( talk_t json, talk_t json2 );
/**
 * @brief free a json
 * @param[in] json
 * @return none
 */
void        talk_free( talk_t json );



/**
 * @brief print talk to std output stream and make it readable
 * @param[in] json
 * @return none
 */
void        talk_print( talk_t json );
/**
 * @brief print talk to FILE stream and make it readable
 * @param[in] fp FILE handler
 * @param[in] json
 * @return none
 */
void        talk_fprint( FILE *fp, talk_t json );
/**
 * @brief store the JSON structure to a file and make it readable
 * @param[in] json
 * @param[in] path filename
 * @return operation succeed or failed
 * 		@retval true for succeed
 *  	@retval false for error, the errno code will be sets
 */
boole       talk_save( talk_t json, const char *path );



#endif   /* ----- #ifndef H_LAND_TALK_H  ----- */

