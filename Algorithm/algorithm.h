/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
*               through use of the definition module present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef __ALGORITHM_H
#define __ALGORITHM_H

/*
*********************************************************************************************************
*                                          INCLUDE FILES
*********************************************************************************************************
*/

#include "string_matching.h"

#include "compare.h"

#include "sort.h"

/*
*********************************************************************************************************
*												DEFINES
*********************************************************************************************************
*/

/* Define		the definition of swap algorithm.														*/
#define ALGORITHM_SWAP(x,y)		(x) = (x) ^ (y),(y) = (x) ^ (y),(x) = (x) ^ (y)

/*
*********************************************************************************************************
*									           DATA TYPES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*								         FUNCTION PROTOTYPES
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

#endif // !__ALGORITHM_H
