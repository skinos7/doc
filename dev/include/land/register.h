#ifndef H_LAND_REGISTER_H
#define H_LAND_REGISTER_H

/**
 * @file register.h
 * @author dimmalex@gmail.com
 * @version 7.0
 * @date 20220219
 * @brief global register variable implementation
 * @details Functions similar to environment variables are different from environment variables as follows:
 			1. register variable have only one COPY of information in the system, as opposed to environment variables having a COPY per process
 			2. Can store binary information
 			3. Can be used for inter-process communication, cross-process small data interaction
 */



/// register file handler structure: this structure is a handler of register file
typedef struct register_file_st
{
	// link node for add to linker
    link_struct link;

	// register file pathname
    char path[PATH_MAX];

	// file handler
    int fd;

	// mmap to the memory
    char *mem;

	// mmap size
    int size;
} register_file_struct;
typedef register_file_struct* register_file_t;

/// register index structure: the structure store at the head of register file to describe file layout
typedef struct register_index_st
{
    int magic;                 // magic head
    int var_numb;              // variable number
    int var_offset;            // variable offset at the file
    int var_inuse;             // how many variable in use
    int value_size;            // variable value size
    int value_offset;          // variable value offset at the file
    int value_inuse;           // how many variable value in use
} register_index_struct;
typedef register_index_struct* register_index_t;

/// register variable structure: this structure is a handler of register variable
typedef struct register_var_st
{
    char identify[NAME_MAX];     // variable name
    int value_start;             // variable value offset at file
    int value_size;              // register value size
} register_var_struct;
typedef register_var_struct* register_var_t;
/* default number register at one register file */
#define REGISTER_VAR_NUM   (50)
/* register value default size */
#define REGISTER_VAR_SIZE   (256)


// adv function
register_file_t register_open( const char *object, int value_number, int total_size, int mode );
void            register_close( register_file_t reg );
register_var_t  register_search( register_file_t h, const char *name );


/**
 * @brief set a register variable
 * @param[in] o a pointer of object, NULL for system default
 * @param[in] name value name
 * @param[in] v value
 * @param[in] size value size in byte
 * @param[in] max_size init the value size in byte
 * @return pointer of value
 * 		@retval pointer for succeed
 *  	@retval NULL for error, errno will be set
 */
void		   *register_set( const char *object, const char *name, const void *v, int size, int max_size );
/**
 * @brief set a register variable value and buffer the pointer of register value
 * @param[in] name value name
 * @param[out] register value pointer store here
 * @param[in] value value for register
 * @return none
 */
#define         int2register( object, name, pointer, value ) \
	do{ \
		if( pointer == NULL ) \
			pointer = (int *)register_set( object, name, &value, sizeof(value), 0 ); \
		else \
			*pointer = value; \
	}while(0)
#define         boole2register( object, name, pointer, value ) \
	do{ \
		if( pointer == NULL ) \
			pointer = (boole *)register_set( object, name, &value, sizeof(value), 0 ); \
		else \
			*pointer = value; \
	}while(0)
#define         string2register( object, name, pointer, value, max_size ) \
	do{ \
		int len; \
		if( pointer == NULL ) \
		{ \
			if ( value != NULL ) \
			{ \
				len = strlen(value)+1; \
			} \
			else \
			{ \
				len = 1; \
			} \
			pointer = (char *)register_set( object, name, value, len, max_size ); \
		} \
		else \
		{ \
			len = register_size( NULL, name ); \
			if ( value != NULL ) \
			{ \
				strncpy( pointer, value, len-1 ); \
			} \
			else \
			{ \
				*pointer = '\0'; \
			} \
		} \
	}while(0)
#define int2reg( name, pointer, value )                     int2register( LAND_PROJECT, name, pointer, value )
#define boole2reg( name, pointer, value )                   boole2register( LAND_PROJECT, name, pointer, value )
#define string2reg( name, pointer, value, max_size )        string2register( LAND_PROJECT, name, pointer, value, max_size )

/**
 * @brief get a register variable
 * @param[in] o a pointer of object, NULL for system default
 * @param[in] name value name
 * @return pointer of register variable
 * 		@retval pointer for succeed
 *  	@retval NULL for error, errno will be set
 */
register_var_t  register_get( const char *object, const char *name );
/**
 * @brief get a register variable value pointer
 * @param[in] o a pointer of object
 * @param[in] name value name
 * @return pointer of value
 * 		@retval pointer for succeed
 *  	@retval NULL for error, errno will be set
 */
void		   *register_pointer( const char *object, const char *name );
/**
 * @brief get a register variable value and buffer the pointer of register value
 * @param[in] name value name
 * @param[out] register value pointer store here
 * @param[out] value value store here
 * @param[in] defvalue default value for register
 * @return none
 */
#define         register2int( object, name, pointer, value, defvalue ) \
	do{ \
		if( pointer == NULL ) \
			pointer = (int *)register_pointer( object, name ); \
		if ( pointer != NULL ) \
			value = *pointer; \
		else \
			value = defvalue; \
	}while(0)
#define         register2boole( object, name, pointer, value, defvalue ) \
	do{ \
		if( pointer == NULL ) \
			pointer = (boole *)register_pointer( object, name ); \
		if ( pointer != NULL ) \
			value = *pointer; \
		else \
			value = defvalue; \
	}while(0)
#define         register2string( object, name, pointer, value, defvalue ) \
	do{ \
		if( pointer == NULL ) \
			pointer = (char *)register_pointer( object, name ); \
		if ( pointer != NULL ) \
			value = pointer; \
		else \
			value = defvalue; \
	}while(0)
#define reg2int( name, pointer, value, defvalue )      register2int( LAND_PROJECT, name, pointer, value, defvalue )
#define reg2boole( name, pointer, value, defvalue )    register2boole( LAND_PROJECT, name, pointer, value, defvalue )
#define reg2string( name, pointer, value, defvalue )   register2string( LAND_PROJECT, name, pointer, value, defvalue )

/**
 * @brief get a register variable value size
 * @param[in] o a pointer of object
 * @param[in] name value name
 * @return size of value
 * 		@retval positive or zeore for succeed
 *  	@retval negative for error, errno will be sets
 */
int             register_size( const char *object, const char *name );



#endif   /* ----- #ifndef H_LAND_REGISTER_H  ----- */

