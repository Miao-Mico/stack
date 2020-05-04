/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
*               through use of the definition module present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef __ITERATOR_ADAPTOR_PRIVITE_DEFINITION_H
#define __ITERATOR_ADAPTOR_PRIVITE_DEFINITION_H

/*
 *********************************************************************************************************
 *                                            INCLUDE FILES
 *********************************************************************************************************
 */

#include "iterator_adaptor_def.h"

/*
 *********************************************************************************************************
 *									            DEFINES
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *									           DATA TYPES
 *********************************************************************************************************
 */

/**
 * @brief This type is the iterator adaptor structure.
 */

struct iterator_adaptor_s {
    /* @brief RESERVED This variables will record the identity code of iterator_ptr type.				*/
    enum iterator_adaptor_type_e iterator_type_id;

    /* @brief This variables will record the allocator unit structure.									*/
    struct allocator_unit_s allocator_unit;

    /* @brief This variables is the unit of the iterator.											    */
    struct iterator_unit_s iterator_unit;

	/* @brief This variables is the adapt status of the iterator.									    */
    enum unify_adaptor_adapt_status_e adapt_status;

    /* @brief This variables will be a external addon, validity only depends on memory allocation.		*/
    char addon[0];
};

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

#endif // !__ITERATOR_ADAPTOR_PRIVITE_DEFINITION_H