#ifndef  H_LAND_SKINAPI_H
#define  H_LAND_SKINAPI_H

/**
 * @file skinapi.h
 * @author dimmalex@gmail.com
 * @version 7.0
 * @date 20220219
 * @brief skinos system commom api base the ccall
 */



/// machine api
#define machine_restart( delay, key )   scalls( MACHINE_COM, "restart", "%d,%s", delay, key?:"" )



/// fpk api
#define fpk_register( ... ) scalls( FPK_COM, "register", __VA_ARGS__ )



/// init api
#define init_register( level, call )     scalls( INIT_COM, "register", "%s,%s", level, call )
#define uninit_register( level, call )   scalls( UNINIT_COM, "register", "%s,%s", level, call )



/// joint api
#define joint_register( joint, call )   scalls( JOINT_COM, "register", "%s,%s", joint, call )
#define joint_calls( joint, string )    scalls( JOINT_COM, "call", "%s,%s", joint, string?:"" )
#define joint_callt( joint, json ) do \
		{ \
			param_t ptmp; \
			ptmp = param_import( NULL, NULL ); \
			ptmp->option[0] = joint; \
			ptmp->talk[1] = json; \
			ptmp->end = 2; \
			ptmp->dirty = true; \
			scall( JOINT_COM, "call", ptmp ); \
			ptmp->option[0] = NULL; \
			ptmp->talk[1] = NULL; \
			param_free( ptmp ); \
		} while(0)
#define joint_unregister( joint, call )   scalls( JOINT_COM, "unregister", "%s,%s", joint, call )



#endif   /* ----- #ifndef H_LAND_SKINAPI_H  ----- */

