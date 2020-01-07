/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "stack.h"

#include "vector.h"

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
typedef STACK_CFG_ALLOCATOR_TYPE *STACK_ALLOCATOR_TYPEDEF_PTR;

struct stack_t {
	/* @brief RESERVED This variables will record the identity code of container.						*/
	int	id_code;

	/* @brief This variables will record if the stack attach to other container instead of initialize.	*/
	bool attach;

	/* @brief This variables will point to the container.												*/
	void *container;

	/* @brief This variables will point to the function address table of front container type.			*/
	int *container_func_addr_table;

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

	stack_control_capacity_capacity,

	stack_control_capacity_size,

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
 * @param stack the pointer to container adapter struct
 * @param container the pointer to container
 *
 * @return NONE
 */

void stack_control_configration_init(STACK_TYPEDEF_PPTR stack,
									 enum container_type type,
									 CONTAINER_GLOBAL_CFG_SIZE_TYPE element_size, bool string_type,
									 void (*assign)(void *dst, void *src), void (*free)(void *dst))
{
	assert(stack);
	assert(type);
	assert(element_size);

	STACK_ALLOCATOR_TYPEDEF_PTR
		allocator = NULL;																	/* Variables pointer to	the allocator struct */

	allocator_ctrl.configration.init(&allocator, NULL);										/* Initialize the allocator struct */

	struct stack_t
		*stack_alloced = (struct stack_t *)allocator_ctrl.allocate(allocator,				/* Allocate #1 */
																   1, sizeof(struct stack_t));
																							/* Variables pointer to	the stack struct which
																								will be allocate and assign to the stack 	*/
	void
		*container = NULL;																	/* Variables pointer to	the specified container struct */

	void (*container_control_configration_init)(void **container,
												CONTAINER_GLOBAL_CFG_SIZE_TYPE element_size, bool string_type,
												void (*assign)(void *dst, void *src), void (*free)(void *dst)) = NULL;
																							/* Variables pointer to	the initialize function of
																								specified container 		*/

	int
		*func_addr_table = container_control_convert_type_to_func_addr_table(type);			/* Variables pointer to	the function address table of
																								specified container 		*/

	container_control_configration_init = (void (*)(void **, CONTAINER_GLOBAL_CFG_SIZE_TYPE, bool,
													void (*)(void *, void *),
													void (*)(void *)))func_addr_table[INITIALIZE];
																							/* Assign the initialize function of
																								specified container function address table to the pointer */

	if (NULL == stack ||																	/* Check if stack point to NULL			*/
		NULL == stack_alloced) {															/* Check if data_pack_alloced point to NULL	*/
		return;
	}

	container_control_configration_init(&container, element_size, string_type, assign, free);/* Initialize the specified container struct */

	stack_alloced->id_code = STACK;															/* Assign stack structure					*/
	stack_alloced->attach = false;
	stack_alloced->container = container;
	stack_alloced->container_func_addr_table = func_addr_table;
	stack_alloced->allocator = allocator;

	*stack = stack_alloced;

	printf("init.stack block : %p \r\n", stack_alloced);									/* Debug only								*/
}

/**
 * @brief This function will initialize the stack struct and attach to the specified container.
 *
 * @param stack the pointer to container adapter struct
 * @param container the pointer to container
 *
 * @return NONE
 */

void stack_control_configration_attach(STACK_TYPEDEF_PPTR stack, void **container, void *func_addr_table)
{
	assert(stack);
	assert(container);
	assert(*container);
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
		NULL == *container ||																/* Check if stack point to NULL			*/
		NULL == func_addr_table ||															/* Check if stack point to NULL			*/
		NULL == stack_alloced) {															/* Check if data_pack_alloced point to NULL	*/
		return;
	}

	stack_alloced->id_code = STACK;															/* Assign stack structure					*/
	stack_alloced->attach = true;
	stack_alloced->container = container;
	stack_alloced->container_func_addr_table = func_addr_table;
	stack_alloced->allocator = allocator;

	*stack = stack_alloced;

	printf("init.stack block : %p \r\n", stack_alloced);									/* Debug only								*/
}

/**
 * @brief This function will destroy the stack struct.
 *
 * @param stack the pointer to container adapter struct
 *
 * @return NONE
 */

void stack_control_configration_destroy(STACK_TYPEDEF_PPTR stack)
{
	assert(stack);

	void
		*container = NULL;																	/* Variables pointer to	the specified container struct */

	void (*container_control_configration_destroy)(void **container) = NULL;				/* Variables pointer to	the destroy function of
																								specified container 		*/

	int
		*func_addr_table = (*stack)->container_func_addr_table;								/* Variables pointer to	the function address table of
																								specified container 		*/

	STACK_ALLOCATOR_TYPEDEF_PTR
		allocator = (*stack)->allocator;													/* Variables pointer to	the allocator struct */

	container_control_configration_destroy = (void (*)(void **))(*stack)->container_func_addr_table[DESTROY];
																							/* Assign the destroy function of
																								specified container function address table to the pointer */

	container_control_configration_destroy(&(*stack)->container);							/* Destroy the container */

	printf("destroy.stack block : %p \r\n", (*stack));

	allocator_ctrl.deallocate(allocator, (*stack), 1);										/* Deallocate #2 */

	(*stack)->id_code = 0u;
	(*stack)->attach = false;
	(*stack)->container = NULL;
	(*stack)->container_func_addr_table = NULL;
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

	CONTAINER_GLOBAL_CFG_SIZE_TYPE(*container_control_capacity_capacity)(void *) = NULL;
																							/* Variables pointer to	the capacity function of
																								specified container 		*/

	void *(*container_control_element_access_at)(void *, CONTAINER_GLOBAL_CFG_SIZE_TYPE) = NULL;
																							/* Variables pointer to	the at function of
																								specified container 		*/

	int
		*func_addr_table = stack->container_func_addr_table;								/* Variables pointer to	the function address table of
																								specified container 		*/

	container_control_capacity_capacity = (CONTAINER_GLOBAL_CFG_SIZE_TYPE(*)(void *))stack->container_func_addr_table[CAPACITY];
																							/* Assign the capacity function of
																								specified container function address table to the pointer */

	container_control_element_access_at = (void *(*)(void *, CONTAINER_GLOBAL_CFG_SIZE_TYPE))stack->container_func_addr_table[AT];
																							/* Assign the at function of
																								specified container function address table to the pointer */

	return container_control_element_access_at(stack->container,
											   container_control_capacity_capacity(stack->container) - 1);											
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
		((CONTAINER_GLOBAL_CFG_SIZE_TYPE)stack_control_capacity_capacity(stack))) {
		return true;
	} else {
		return false;
	}
}

/**
 * @brief This function will return the number of elements in the underlying container.
 *
 * @param stack the pointer to container adapter struct
 *
 * @return NONE
 */

CONTAINER_GLOBAL_CFG_SIZE_TYPE stack_control_capacity_capacity(STACK_TYPEDEF_PTR stack)
{
	assert(stack);

	void
		*container = NULL;																	/* Variables pointer to	the specified container struct */

	CONTAINER_GLOBAL_CFG_SIZE_TYPE(*container_control_capacity_capacity)(void *) = NULL;
																							/* Variables pointer to	the capacity function of
																								specified container 		*/

	int
		*func_addr_table = stack->container_func_addr_table;								/* Variables pointer to	the function address table of
																								specified container 		*/

	container_control_capacity_capacity = (CONTAINER_GLOBAL_CFG_SIZE_TYPE(*)(void *))stack->container_func_addr_table[CAPACITY];
																							/* Assign the capacity function of
																								specified container function address table to the pointer */

	return container_control_capacity_capacity(stack->container);							/* Get the number of elements in the underlying container */
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

	CONTAINER_GLOBAL_CFG_SIZE_TYPE(*container_control_capacity_size)(void *) = NULL;
																							/* Variables pointer to	the max size function of
																								specified container 		*/

	int
		*func_addr_table = stack->container_func_addr_table;								/* Variables pointer to	the function address table of
																								specified container 		*/

	container_control_capacity_size = (CONTAINER_GLOBAL_CFG_SIZE_TYPE(*)(void *))stack->container_func_addr_table[SIZE];
																							/* Assign the max size function of
																								specified container function address table to the pointer */

	return container_control_capacity_size(stack->container);								/* Get the maximum number of elements the container
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

	void *(*container_control_modifiers_push_back)(void *, void *) = NULL;					/* Variables pointer to	the capacity function of
																								specified container 		*/

	int
		*func_addr_table = stack->container_func_addr_table;								/* Variables pointer to	the function address table of
																								specified container 		*/

	container_control_modifiers_push_back = (void *(*)(void *, void *))stack->container_func_addr_table[PUSH_BACK];
																							/* Assign the capacity function of
																								specified container function address table to the pointer */

	container_control_modifiers_push_back(stack->container, source);						/* push the given element source to the top of the stack */
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

	void
		*container = NULL;																	/* Variables pointer to	the specified container struct */

	void (*container_control_modifiers_earse)(void *,
											  CONTAINER_GLOBAL_CFG_SIZE_TYPE, void *) = NULL;	/* Variables pointer to	the capacity function of
																								specified container 		*/

	int
		*func_addr_table = stack->container_func_addr_table;								/* Variables pointer to	the function address table of
																								specified container 		*/

	container_control_modifiers_earse = (void(*)(void *,
												 CONTAINER_GLOBAL_CFG_SIZE_TYPE,
												 void *))stack->container_func_addr_table[ERASE];
																							/* Assign the capacity function of
																								specified container function address table to the pointer */

	container_control_modifiers_earse(stack->container,
									  stack_control_capacity_capacity(stack) - 1, string);	/* push the given element source to the top of the stack */

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

	void
		*container = NULL;																	/* Variables pointer to	the specified container struct */

	void (*container_control_modifiers_swap)(void **, void **) = NULL;						/* Variables pointer to	the capacity function of
																								specified container 		*/

	int
		*func_addr_table = (*stack)->container_func_addr_table;								/* Variables pointer to	the function address table of
																								specified container 		*/

	container_control_modifiers_swap = (void (*)(void **, void **))(*stack)->container_func_addr_table[SWAP];
																							/* Assign the capacity function of
																								specified container function address table to the pointer */

	container_control_modifiers_swap(&(*stack)->container, &(*other)->container);			/* exchange the contents of the container adaptor with those of other */
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

	void
		*container = NULL;																	/* Variables pointer to	the specified container struct */

	void (*container_control_modifiers_copy)(void **, void *) = NULL;						/* Variables pointer to	the capacity function of
																								specified container 		*/

	int
		*func_addr_table = (*destination)->container_func_addr_table;						/* Variables pointer to	the function address table of
																								specified container 		*/

	container_control_modifiers_copy = (void (*)(void **, void *))(*destination)->container_func_addr_table[COPY];
																							/* Assign the capacity function of
																								specified container function address table to the pointer */

	container_control_modifiers_copy(&(*destination)->container, source->container);		/* copy the contents of the container adaptor to those of other */
}