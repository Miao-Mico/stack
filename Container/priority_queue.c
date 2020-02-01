/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "priority_queue.h"

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

/**
 * @brief This struct is the priority_queue structure module
 */

struct priority_queue_s {
	/* @brief RESERVED This variables will record the identity code of container type.					*/
	enum container_type_e	container_type_id;

	/* @brief This variables will record if the priority_queue attach to other container
				instead of initialize.																	*/
	bool attach;

	/* @brief This variables will point to the container.												*/
	void *container;

	/* @brief This variables will point to the function address table of front container type.			*/
	struct container_control_s *container_control;

	/* @brief This variables will point to the allocator.												*/
	void *allocator;

	/* @brief This variables will point to the allocator control.										*/
	struct allocator_control_s *allocator_ctrl;
};

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

struct priority_queue_control_s priority_queue_ctrl =
{
	NULL
};

/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            FUNCTIONS
*********************************************************************************************************
*/