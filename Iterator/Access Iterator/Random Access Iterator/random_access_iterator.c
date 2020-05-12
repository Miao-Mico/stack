/*
 *********************************************************************************************************
 *                                            INCLUDE FILES
 *********************************************************************************************************
 */

#include "random_access_iterator.h"

/*
 *********************************************************************************************************
 *                                            LOCAL DEFINES
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *                                           LOCAL CONSTANTS
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *                                          LOCAL DATA TYPES
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *                                            LOCAL TABLES
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *                                       LOCAL GLOBAL VARIABLES
 *********************************************************************************************************
 */

/**
 * @brief This variable is the random access iterator structure.
 */

struct random_access_iterator_s random_access_iterator = {
	.advance.access_unit.function_ptr = access_iterator_control_iterator_operations_advance,

	.distance.function_ptr = access_iterator_control_iterator_operations_distance,

	.next.function_ptr = access_iterator_control_iterator_operations_next,

	.prev.function_ptr = access_iterator_control_iterator_operations_prev,

	.at.function_ptr = access_iterator_control_iterator_operations_at,

	.front.function_ptr = access_iterator_control_iterator_operations_front,

	.back.function_ptr = access_iterator_control_iterator_operations_back,
};

/*
 *********************************************************************************************************
 *                                      LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *					LOCAL GLOBAL VARIABLES & LOCAL FUNCTION PROTOTYPES INTERSECTION
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *                                            FUNCTIONS
 *********************************************************************************************************
 */