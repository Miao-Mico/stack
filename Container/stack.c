/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "stack.h"

/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

#define SEQUENCE_STACK_EXCEPTION_TYPE_AMOUNT	4
#define CHAIN_STACK_EXCEPTION_TYPE_AMOUNT		4

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

/* Configure    stack type.                                                                            */
typedef STACK_CFG_ALLOCATOR_PTR_TYPE STACK_ALLOCATOR_TYPEDEF_PTR;

struct stack_t {
	/* @brief RESERVED This variables will record the identity code of container type.					*/
	enum container_type	container_type_id;

	/* @brief This variables will record if the stack attach to other container instead of initialize.	*/
	bool attach;

	/* @brief This variables will point to the container.												*/
	void *container;

	/* @brief This variables will point to the function address table of front container type.			*/
	struct container_control_t *container_control;

	/* @brief This variables will point to the allocator.												*/
	STACK_ALLOCATOR_TYPEDEF_PTR allocator;
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

struct stack_control_t stack_ctrl =
{
	stack_control_configration_init,

	stack_control_configration_attach,

	stack_control_configration_destroy,

	stack_control_element_access_top,

	stack_control_capacity_empty,

	stack_control_capacity_size,

	stack_control_capacity_max_size,

	stack_control_modifiers_push,

	stack_control_modifiers_emplace,

	stack_control_modifiers_pop,

	stack_control_modifiers_swap,

	stack_control_modifiers_copy
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

/**
 * @brief This function will initialize the stack struct and the specified container.
 *
 * @param stack the pointer to container adapter struct pointer
 * @param type the type of the container
 * @param element_size the pointer to container
 * @param string_type the pointer to container
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

void stack_control_configration_init(STACK_TYPEDEF_PPTR stack,
									 enum container_type type,
									 CONTAINER_GLOBAL_CFG_SIZE_TYPE element_size,
									 void (*assign)(void *dst, void *src), void (*free)(void *dst))
{
	assert(stack);
	assert(element_size);

	enum container_type
		adapt_container_type = STACK_CFG_DEFAULT_ADAPT_CONTAINER_TYPE;

	if (type) {
		adapt_container_type = type;
	}

	STACK_ALLOCATOR_TYPEDEF_PTR
		allocator = NULL;																	/* Variables pointer to	the allocator struct */

	allocator_ctrl.configration.init(&allocator, NULL);										/* Initialize the allocator struct */

	struct stack_t
		*stack_alloced = (struct stack_t *)allocator_ctrl.allocate(allocator,				/* Allocate #1 */
																   1, sizeof(struct stack_t));
																							/* Variables pointer to	the stack struct which
																								will be allocate and assign to the stack 	*/

	struct container_control_t
		*container_ctrl = NULL;

	void
		*container = NULL;																	/* Variables pointer to	the specified container struct */

	int
		*func_addr_table = container_control_convert_type_to_func_addr_table(adapt_container_type);
																							/* Variables pointer to	the function address table of
																								specified container type		*/

	container_ctrl = (struct container_control_t *)func_addr_table;

	if (NULL == stack ||																	/* Check if stack point to NULL			*/
		NULL == stack_alloced) {															/* Check if data_pack_alloced point to NULL	*/
		return;
	}

	container_ctrl->configuration.init(&container, element_size, assign, free);/* Initialize the specified container struct */

	stack_alloced->container_type_id = STACK;												/* Assign stack structure					*/
	stack_alloced->attach = false;
	stack_alloced->container = container;
	stack_alloced->container_control = container_ctrl;
	stack_alloced->allocator = allocator;

	*stack = stack_alloced;

	printf("init.stack allocator : %p \r\n    ", allocator);									/* Debug only								*/
	printf("init.stack block : %p \r\n    ", stack_alloced);
}

/**
 * @brief This function will initialize the stack struct and attach to the specified container.
 *
 * @param stack the pointer to container adapter struct pointer
 * @param container the pointer to container pointer
 * @param func_addr_table the pointer to the function address table of the specified container
 *
 * @return NONE
 */

void stack_control_configration_attach(STACK_TYPEDEF_PPTR stack, void *container, void *func_addr_table)
{
	assert(stack);
	assert(container);
	assert(func_addr_table);

	STACK_ALLOCATOR_TYPEDEF_PTR
		allocator = NULL;																	/* Variables pointer to	the allocator struct */

	allocator_ctrl.configration.init(&allocator, NULL);										/* Initialize the allocator struct */

	struct stack_t
		*stack_alloced = (struct stack_t *)allocator_ctrl.allocate(allocator,				/* Allocate #1.1 */
																   1, sizeof(struct stack_t));
																							/* Variables pointer to	the stack struct which
																								will be allocate and assign to the stack 	*/

	if (NULL == stack ||																	/* Check if stack point to NULL			*/
		NULL == func_addr_table ||															/* Check if stack point to NULL			*/
		NULL == stack_alloced) {															/* Check if data_pack_alloced point to NULL	*/
		return;
	}

	stack_alloced->container_type_id = STACK;												/* Assign stack structure					*/
	stack_alloced->attach = true;
	stack_alloced->container = container;
	stack_alloced->container_control = (struct container_control_t *)func_addr_table;
	stack_alloced->allocator = allocator;

	*stack = stack_alloced;

	printf("init.stack block : %p \r\n    ", stack_alloced);									/* Debug only								*/
}

/**
 * @brief This function will destroy the stack struct.
 *
 * @param stack the pointer to container adapter struct pointer
 *
 * @return NONE
 */

void stack_control_configration_destroy(STACK_TYPEDEF_PPTR stack)
{
	assert(stack);

	void
		*container = NULL;																	/* Variables pointer to	the specified container struct */

	STACK_ALLOCATOR_TYPEDEF_PTR
		allocator = (*stack)->allocator;													/* Variables pointer to	the allocator struct */

	printf("destroy.stack container : %p \r\n    ", (*stack)->container);

	(*stack)->container_control->configuration.destroy(&(*stack)->container);				/* Destroy the container */

	printf("destroy.stack allocator : %p \r\n    ", (*stack)->allocator);
	printf("destroy.stack block : %p \r\n    ", (*stack));

	allocator_ctrl.deallocate(allocator, (*stack), 1);										/* Deallocate #2 */

	(*stack)->container_type_id = 0u;
	(*stack)->attach = false;
	(*stack)->container = NULL;
	(*stack)->container_control = NULL;
	(*stack)->allocator = NULL;

	allocator_ctrl.configration.destroy(&allocator);

	*stack = NULL;
}

/**
 * @brief This function will return reference to the top element in the stack.
 *
 * @param stack the pointer to container adapter struct
 *
 * @return NONE
 */

void *stack_control_element_access_top(STACK_TYPEDEF_PTR stack)
{
	assert(stack);

	void
		*container = NULL;																	/* Variables pointer to	the specified container struct */

	return stack->container_control->element_access.at(stack->container,
													   stack->container_control->capacity.size(stack->container) - 1);
																							/* Get the top element of the container */
}

/**
 * @brief This function will check if the underlying container has no elements.
 *
 * @param stack the pointer to container adapter struct
 *
 * @return NONE
 */

bool stack_control_capacity_empty(STACK_TYPEDEF_PTR stack)
{
	assert(stack);

	if (((CONTAINER_GLOBAL_CFG_SIZE_TYPE)stack_control_capacity_size(stack)) <=
		((CONTAINER_GLOBAL_CFG_SIZE_TYPE)stack_control_capacity_max_size(stack))) {
		return true;
	} else {
		return false;
	}
}

/**
 * @brief This function will returns the number of elements in the container.
 *
 * @param stack the pointer to container adapter struct
 *
 * @return NONE
 */

CONTAINER_GLOBAL_CFG_SIZE_TYPE stack_control_capacity_size(STACK_TYPEDEF_PTR stack)
{
	assert(stack);

	void
		*container = NULL;																	/* Variables pointer to	the specified container struct */

	printf("stack.size : %d \r\n    ", stack->container_control->capacity.size(stack->container));

	return stack->container_control->capacity.size(stack->container);						/* Get the number of elements in the container */
}

/**
 * @brief This function will returns the maximum number of elements
 *			the container is able to hold due to system or library implementation limitations.
 *
 * @param stack the pointer to container adapter struct
 *
 * @return NONE
 */

CONTAINER_GLOBAL_CFG_SIZE_TYPE stack_control_capacity_max_size(STACK_TYPEDEF_PTR stack)
{
	assert(stack);

	void
		*container = NULL;																	/* Variables pointer to	the specified container struct */

	return stack->container_control->capacity.max_size(stack->container);					/* Get the maximum number of elements the container
																								is able to hold due to system or library implementation limitations */
}

/**
 * @brief This function will push the given element source to the top of the stack.
 *
 * @param stack the pointer to container adapter struct
 * @param source the pointer to source
 *
 * @return NONE
 */

void stack_control_modifiers_push(STACK_TYPEDEF_PTR stack, void *source)
{
	assert(stack);

	void
		*container = NULL;																	/* Variables pointer to	the specified container struct */

	stack->container_control->modifiers.insert(stack->container,
											   stack_control_capacity_size(stack),1, &source);	
																							/* push the given element source to the top of the stack */
}

/**
 * @brief This function will push a new element on top of the stack. The element is constructed in-place.
 *
 * @param stack the pointer to container adapter struct
 * @param destination the pointer to destination
 *
 * @return NONE
 */

void stack_control_modifiers_emplace(STACK_TYPEDEF_PTR stack, void *destination)
{
	assert(stack);
}

/**
 * @brief This function will remove the top element from the stack.
 *
 * @param stack the pointer to container adapter struct
 *
 * @return NONE
 */

void *stack_control_modifiers_pop(STACK_TYPEDEF_PTR stack)
{
	assert(stack);

	char
		*string = calloc(10, sizeof(char));

	stack->container_control->modifiers.earse(stack->container,
													 stack_control_capacity_size(stack) - 1, string);	
																							/* push the given element source to the top of the stack */

	return string;
}

/**
 * @brief This function will exchange the contents of the container adaptor with those of other.
 *
 * @param stack the pointer to container adapter struct
 * @param other the pointer to other container adapter struct
 *
 * @return NONE
 */

void stack_control_modifiers_swap(STACK_TYPEDEF_PPTR stack, STACK_TYPEDEF_PPTR other)
{
	assert(stack);

	(*stack)->container_control->modifiers.swap(&(*stack)->container, &(*other)->container);/* exchange the contents of the container adaptor with those of other */
}

/**
 * @brief This function will copy the contents of the container adaptor to those of other.
 *
 * @param destination the pointer to destination container adapter struct
 * @param source the pointer to source container adapter struct
 *
 * @return NONE
 */

void stack_control_modifiers_copy(STACK_TYPEDEF_PPTR destination, STACK_TYPEDEF_PTR source)
{
	assert(destination);
	assert(source);

	(*destination)->container_control->modifiers.copy(&(*destination)->container, source->container);		/* copy the contents of the container adaptor to those of other */
}