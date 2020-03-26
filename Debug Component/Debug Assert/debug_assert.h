/*
 *********************************************************************************************************
 *                                               MODULE
 *
 * Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
 *               through use of the definition module present pre-processor macro definition.
 *********************************************************************************************************
 */

#ifndef __DEBUG_ASSERT_H
#define __DEBUG_ASSERT_H

/*
 *********************************************************************************************************
 *                                            INCLUDE FILES
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *									            DEFINES
 *********************************************************************************************************
 */

/* Define			debug assert control pointer.										                */
#define DEBUG_ASSERT_CONTROL_POINTER(pointer, error_type, error_code)							        \
	do {																								\
		assert(NULL != (pointer));									/* Assert first,DEBUG will work */	\
		if (NULL == (pointer)) {									/* If second,RELEASE will work	*/	\
			return (error_type)(error_code);															\
		}																								\
	} while (false)

/* Define			debug assert control variable.										                */
#define DEBUG_ASSERT_CONTROL_VARIABLE(variable, comp, value_type, value, error_type, error_code)        \
	do {																								\
		assert((((value_type)(variable)) comp ((value_type)(value))));	                                \
		if (!(((value_type)(variable)) comp ((value_type)(value)))) {	                                \
			return (error_type)(error_code);															\
		}																								\
	} while (false)

/*
 *********************************************************************************************************
 *									           DATA TYPES
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *								            FUNCTION PROTOTYPES
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *                                       EXTERN GLOBAL VARIABLES
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *                                             MODULE END
 *********************************************************************************************************
 */

#endif // !__DEBUG_ASSERT_H