/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
*               through use of the definition module present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef __SORT_H
#define __SORT_H

/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "algorithm_def.h"

#include "compare.h"

#include "modify_sequence.h"

/*
*********************************************************************************************************
*									            DEFINES
*********************************************************************************************************
*/

/* Configure        if enable sort debug.													            */
#define SORT_CFG_DEBUG_EN										            0

/* Configure        if enable sort debug.													            */
#define SORT_CFG_DEFAULT_COMPARE_ADDRESS								                                \
    (&compare_control_greater)

/* Configure        if enable sort debug.													            */
#define SORT_CFG_DEFAULT_SWAP_ADDRESS									                                \
    (&modify_sequence_control_swap)

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

/**
* @brief This function will sort the object by the comp and the sort algorithm is distinguished by
*		   the sort_algorithm_addr that will get by xxx_convert_type_to_func_addr_table().
*
* @param data the pointer to the data list will give
*
* @return void
*/

errno_t sort_control(enum sort_algorithm_type type,
				  struct sort_package_s package);

/**
 * @brief This function will sort the object by the compare().
 *
 * @param sort_package the information package of the sort
 * @param compare the compare() function
 *
 * @return void
 */

errno_t sort_control_bubble_sort(struct sort_package_s sort_package);

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

#endif // !__SORT_H