/*
 *********************************************************************************************************
 *                                               MODULE
 *
 * Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
 *               through use of the definition module present pre-processor macro definition.
 *********************************************************************************************************
 */

#ifndef __ITERATOR_ADAPTOR_DEFINITION_H
#define __ITERATOR_ADAPTOR_DEFINITION_H

/*
 *********************************************************************************************************
 *                                            INCLUDE FILES
 *********************************************************************************************************
 */

#include "iterator_def.h"

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

/*
 *********************************************************************************************************
 *								            FUNCTION PROTOTYPES
 *********************************************************************************************************
 */

errno_t iterator_adaptor_control_configuration_init(struct iterator_adaptor_s **iterator_adaptor,
													enum iterator_adaptor_type_e iterator_adaptor_type,
													enum iterator_type_e iterator_type,
													enum allocator_type_e allocator_type,
													struct iterator_object_unit_s object_unit);

errno_t iterator_adaptor_control_configuration_readapt(struct iterator_adaptor_s **iterator_adaptor);

errno_t iterator_adaptor_control_configuration_destroy(struct iterator_adaptor_s **iterator_adaptor);

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

#endif // !__ITERATOR_ADAPTOR_DEFINITION_H