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

	// register object
    char object[NAME_MAX];

	// register file pathname
    char path[PATH_MAX];

	// file handler
    int fd;
    int flags;

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
register_file_t register_open( const char *object, int flags, int mode, int value_number, int total_size );
void			register_close( register_file_t h );
register_var_t  register_search( register_file_t h, const char *name );
void           *register_value_set( register_file_t h, const char *name, const void *v, int size, int max_size );
void           *register_value_pointer( register_file_t h, const char *name );
int             register_value_size( register_file_t h, const char *name );



/**
 * @brief set a register variable
 * @param[in] com compoent name, cannot be NULL
 * @param[in] name value name
 * @param[in] v value pointer
 * @param[in] size value size in byte
 * @param[in] max_size init the value size in byte
 * @return pointer of value
 * 		@retval pointer for succeed
 *  	@retval NULL for error, errno will be set
 */
void           *register_set( const char *com, const char *name, const void *v, int size, int max_size );
/**
 * @brief get a register variable pointer for write
 * @param[in] com compoent name, cannot be NULL
 * @param[in] name value name
 * @return pointer of value
 * 		@retval pointer for succeed
 *  	@retval NULL for error, errno will be set
 */
void           *register_pointer( const char *com, const char *name );
/**
 * @brief set a register variable value and buffer the pointer of register value
 * @param[in] com compoent name, NULL for system default( land )
 * @param[in] name value name
 * @param[out] register value pointer store here
 * @param[in] value value for register
 * @return none
 */
#define         int2register( com, name, pointer, value ) \
	do{ \
		if( pointer == NULL ) pointer = (int *)register_set( com, name, &value, sizeof(value), 0 ); \
		else *pointer = value; \
	}while(0)
#define         boole2register( com, name, pointer, value ) \
	do{ \
		if( pointer == NULL ) pointer = (boole *)register_set( com, name, &value, sizeof(value), 0 ); \
		else *pointer = value; \
	}while(0)
#define         string2register( com, name, pointer, value, max_size ) \
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
				len = 0; \
			} \
			pointer = (char *)register_set( com, name, value, len, max_size ); \
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



/**
 * @brief get a register variable size
 * @param[in] com compoent name, NULL for system default( land )
 * @param[in] name value name
 * @return value size
 * 		@retval value size for succeed
 *  	@retval -1 for error, errno will be set
 */
int             register_size( const char *com, const char *name );
/**
 * @brief get a register variable pointer for read only
 * @param[in] com compoent name, NULL for system default( land )
 * @param[in] name value name
 * @return pointer of value
 * 		@retval pointer for succeed
 *  	@retval NULL for error, errno will be set
 */
const void	   *register_value( const char *com, const char *name );
/**
 * @brief get a register variable value and buffer the pointer of register value
 * @param[in] com compoent name, NULL for system default( land )
 * @param[in] name value name
 * @param[out] register value pointer store here
 * @param[out] value value store here
 * @param[in] defvalue default value for register
 * @return none
 */
#define         register2int( com, name, pointer, value, defvalue ) \
	do{ \
		if ( pointer == NULL ) pointer = (const int *)register_value( com, name ); \
		if ( pointer != NULL ) value = *pointer; \
		else value = defvalue; \
	}while(0)
#define         register2boole( com, name, pointer, value, defvalue ) \
	do{ \
		if ( pointer == NULL ) pointer = (const boole *)register_value( com, name ); \
		if ( pointer != NULL ) value = *pointer; \
		else value = defvalue; \
	}while(0)
#define         register2string( com, name, pointer, value, defvalue ) \
	do{ \
		if ( pointer == NULL ) pointer = (const char *)register_value( com, name ); \
		if ( pointer != NULL ) value = pointer; \
		else value = defvalue; \
	}while(0)



#endif   /* ----- #ifndef H_LAND_REGISTER_H  ----- */

