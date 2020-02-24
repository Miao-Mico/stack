/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
*               through use of the definition module present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef __RED_BLACK_TREE_H
#define __RED_BLACK_TREE_H

/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "binary_search_tree.h"

/*
*********************************************************************************************************
*									            DEFINES
*********************************************************************************************************
*/

/* Configure    the type of allocator.                                                                  */
#define RED_BLACK_TREE_CFG_ALLOCATOR_TYPE								    ALLOCATOR_COMMON

/* Configure    if enable integrated structure.                                                         */
#define RED_BLACK_TREE_CFG_INTERGRATED_STRUCTURE_MODE_EN					1u

/* Configure    if enable debug mode.																	*/
#define RED_BLACK_TREE_CFG_DEBUG_EN											1u

/*
*********************************************************************************************************
*									           DATA TYPES
*********************************************************************************************************
*/

/* Configure    red-black-tree type.																	*/
typedef struct tree_family_s
*RED_BLACK_TREE_TYPEDEF_PTR,
**RED_BLACK_TREE_TYPEDEF_PPTR;;

/*
*********************************************************************************************************
*								            FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/**
 * @brief This function will initialize the tree struct
 *
 * @param tree the pointer to the tree struct pointer
 * @param element_size the element memory size of the tree struct
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

void red_black_tree_control_configuration_init(RED_BLACK_TREE_TYPEDEF_PPTR tree,
											   container_size_t element_size,
											   void (*assign)(void *dst, void *src), void (*free)(void *dst));

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

#endif // !__RED_BLACK_TREE_H