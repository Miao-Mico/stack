/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
*               through use of the AT definition module present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef __CONTAINER_DEFINATION_H
#define __CONTAINER_DEFINATION_H

/*
*********************************************************************************************************
*                                          INCLUDE FILES
*********************************************************************************************************
*/

#include "stdio.h"
#include "string.h"
#include "stdarg.h"
#include "stdbool.h"
#include "assert.h"
#include "malloc.h"

#include "allocator.h"

/*
*********************************************************************************************************
*												DEFINES
*********************************************************************************************************
*/

/* Configure    container global size type.                                                                       */
#define CONTAINER_GLOBAL_CFG_SIZE_TYPE															size_t

/*
*********************************************************************************************************
*									         DATA TYPES
*********************************************************************************************************
*/

/* Configure the enum category of container.															*/
enum container_category {
	SEQUENCE_CONTAINERS = 0x10,

	ASSOCIATIVE_CONTAINERS = 0x20,

	UNORDERED_ASSOCIATIVE_CONTAINERS = 0x30,

	CONTAINERS_ADAPTORS = 0x40,

	SPAN = 0x50,
};

/* Configure the enum type of container.																*/
enum container_type {
	VECTOR = SEQUENCE_CONTAINERS,
	DEQUE,
	LIST,

	SET = ASSOCIATIVE_CONTAINERS,
	MAP,

	UNORDERED_SET = UNORDERED_ASSOCIATIVE_CONTAINERS,

	STACK = CONTAINERS_ADAPTORS,
	QUEUE,
};

/* Configure the enum function type of container.														*/
enum container_function_type {
	INITIALIZE,
	DESTROY,

	AT,

	EMPTY,
	SIZE,
	CAPACITY,

	PUSH_BACK,
	ERASE,
	COPY,
	SWAP
};

/* Configure the enum universal function type of container.												*/
struct container_control_t {
	struct {
		/* @brief This function will initialize the container struct and the specified container.		*/
		void (*init)(void **container,
					 enum container_type type,
					 CONTAINER_GLOBAL_CFG_SIZE_TYPE element_size, bool string_type,
					 void (*assign)(void *dst, void *src), void (*free)(void *dst));

		/* @brief This function will destroy the container struct. */
		void (*destroy)(void **container);
	}configuration;

	struct {
		/* @brief This function will returns a reference to the element 
					at specified location position, with bounds checking.								*/
		void *(*at)(void *container, CONTAINER_GLOBAL_CFG_SIZE_TYPE position);
	}element_access;

	struct {
		/* @brief This function will check if the underlying container has no elements.					*/
		bool(*empty)(void *container);

		/* @brief This function will returns the number of elements in the container.					*/
		size_t(*size)(void *container);

		/* @brief This function will returns the maximum number of elements 
					the container is able to hold due to system or library implementation limitations.	*/
		size_t(*max_size)(void *container);
	}capacity;

	struct {
		/* @brief This function will inserts elements at the specified location in the container.		*/
		void (*insert)(void *container,
					   CONTAINER_GLOBAL_CFG_SIZE_TYPE position, void *source);

		/* @brief This function will erases the specified elements from the container.                  */
		void *(*earse)(void *container,
					   CONTAINER_GLOBAL_CFG_SIZE_TYPE position, void *source);

		/* @brief This function will exchange the contents of the container adaptor with those of other. */
		void (*swap)(void **container,
					 void **other);

		/* @brief This function will erase the specified elements from the container. */
		void (*copy)(void **destination,
					 void *source);
	}modifiers;
};

/*
*********************************************************************************************************
*								        FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/**
 * @brief This function will initialize the container struct and attach to the specified container.
 *
 * @param container container adapter struct
 * @param container the pointer to container
 *
 * @return NONE
 */

inline int *container_control_convert_type_to_func_addr_table(enum container_type type);

/*
*********************************************************************************************************
*                                       EXTERN GLOBAL VARIABLES
*********************************************************************************************************
*/

/**
 * @brief This array will contain all the universal vector functions address.
 */

extern int vector_function_address_tables[];

/*
*********************************************************************************************************
*                                            FUNCTIONS
*********************************************************************************************************
*/

/**
 * @brief This function will initialize the container struct and attach to the specified container.
 *
 * @param container container adapter struct
 * @param container the pointer to container
 *
 * @return NONE
 */

inline int *container_control_convert_type_to_func_addr_table(enum container_type type)
{
	int
		*func_addr_table = NULL;

	switch (type) {
		case VECTOR:
			func_addr_table = (int *)&vector_function_address_tables;
			break;
		case DEQUE:
			break;
		case LIST:
			break;
		case SET:
			break;
		case MAP:
			break;
		case UNORDERED_SET:
			break;
		case STACK:
			break;
		case QUEUE:
			break;
		default:
			break;
	}

	return func_addr_table;
}

/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif // __CONTAINER_DEFINATION_H