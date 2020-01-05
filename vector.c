/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "vector.h"

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
 * @brief This struct is the vector structure module
 */

struct vector_t {
	struct {
		/* @brief This variables will record the maximum number of elements.						*/
		VECTOR_SIZE_TYPEDEF max_size;

		/* @brief This variables will record the number of elements that
				  the container has currently allocated space for.                                  */
		VECTOR_SIZE_TYPEDEF capacity;

		/* @brief This variables will record the size that each element will take up.				*/
		VECTOR_SIZE_TYPEDEF mem_size;

		/* @brief This variables will record if the element type equal string type.					*/
		bool string_type;
	}info;

	/* @brief This variables will point to the address of the vector data memory block.				*/
	void *data;

	struct {
		/* @brief This variables will point to the address of the vector element assign handler.	*/
		void (*assign)(void *dst, void *src);

		/* @brief This variables will point to the address of the vector element free handler.		*/
		void (*free)(void *dst);
	}element_handler;

	struct {
		/* @brief This variables will point to the address of the vector empty callback handler.	*/
		void (*empty)(void);

		/* @brief This variables will point to the address of the vector full callback handler.	*/
		void (*full)(void);

		/* @brief This variables will point to the address of the heap null callback handler.		*/
		void (*null_heap)(void);
	}callback;
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

#if (VECTOR_CFG_INTERGRATED_STRUCTURE_MODE_EN)

/**
 * @brief This struct will control all the vector functions conveniently.
 */

struct vector_control_t vector_ctrl = {
	{
		vector_control_configuration_init,

		vector_control_configuration_destroy,

		vector_control_configuration_element_handler,

		vector_control_configuration_callback,
	},
	{
		vector_control_iterators_front,

		vector_control_iterators_back,
	},
	{
		vector_control_element_access_at,

		vector_control_element_access_front,

		vector_control_element_access_back,
	},
	{
		vector_control_capacity_empty,

		vector_control_capacity_size,

		vector_control_capacity_max_size,

		vector_control_capacity_capacity,

		vector_control_capacity_reserve,

		vector_control_capacity_shrink_to_fit,
	},
	{
		vector_control_modifiers_clear,

		vector_control_modifiers_insert,

		vector_control_modifiers_erase,

		vector_control_modifiers_push_back,

		vector_control_modifiers_pop_back,

		vector_control_modifiers_resize,

		vector_control_modifiers_copy,

		vector_control_modifiers_swap,
	}
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
 * @brief This function will initialize the vector struct.
 *
 * @param vector container struct
 * @param element_size the size of element
 * @param string_type if the element is the string type
 * @param assign_func pointer to the assign function of element
 * @param free_func pointer to the free function of element
 *
 * @return
 *  - 0    : succeed,initialize the at struct completely
 *  - else : fail
 */

void vector_control_configuration_init(VECTOR_TYPEDEF_PPTR vector,
									   VECTOR_SIZE_TYPEDEF element_size, bool string_type,
									   void (*assign_func)(void *dst, void *src), void (*free_func)(void *dst))
{
	assert(vector);
	assert(0 <= element_size);

	struct vector_t
		*vector_alloced = (struct vector_t *)calloc(1, sizeof(struct vector_t));

	void
		*data_pack_alloced = calloc(VECTOR_CFG_DEFAULT_MAX_SIZE,
		(string_type) ? (element_size + VECTOR_CFG_DEFAULT_MAX_SIZE) : (element_size));

	if (NULL == vector ||
		NULL == vector_alloced ||
		NULL == data_pack_alloced) {
		return;
	}

	vector_alloced->info.max_size = VECTOR_CFG_DEFAULT_MAX_SIZE;
	vector_alloced->info.capacity = 0u;
	vector_alloced->info.mem_size = element_size;

	vector_alloced->info.string_type = string_type;

	vector_alloced->data = data_pack_alloced;

	if (NULL != assign_func &&
		NULL != free_func) {
		vector_alloced->element_handler.assign = assign_func;
		vector_alloced->element_handler.free = free_func;
	}

	// TODO : vector callbacks

	*vector = vector_alloced;

	printf("init.vector block : %p \r\n", vector_alloced);
	printf("init.vector data block : %p \r\n", data_pack_alloced);
}

/**
 * @brief This function will destroy the vector struct and free the space.
 *
 * @param vector container struct
 *
 * @return
 *  - 0    : succeed,destroy the vector struct and free the space completely
 *  - else : fail
 */

void vector_control_configuration_destroy(VECTOR_TYPEDEF_PPTR vector)
{
	assert(vector);

	printf("destroy.vector data block : %p \r\n", (*vector)->data);
	printf("destroy.vector block : %p \r\n", (*vector));

	free((*vector)->data);

	(*vector)->info.max_size = 0u;
	(*vector)->info.capacity = 0u;

	(*vector)->data = NULL;

	(*vector)->element_handler.assign = NULL;
	(*vector)->element_handler.free = NULL;

	(*vector)->callback.empty = NULL;
	(*vector)->callback.full = NULL;
	(*vector)->callback.null_heap = NULL;

	free(*vector);

	*vector = NULL;
}

/**
 * @brief This function will configure the vector element handler.
 *
 * @param vector container struct
 * @param assign pointer to the address of element assign handler
 * @param free pointer to the address of element free handler
 *
 * @return NONE
 */

void vector_control_configuration_element_handler(VECTOR_TYPEDEF_PTR vector,
												  void (*assign)(void *dst, void *src), void (*free)(void *dst))
{
	vector->element_handler.assign = assign;
	vector->element_handler.free = free;
}

/**
 * @brief This function will
 *
 * @param vector container struct
 * @param empty pointer to the address of element callback that container has no elements when delete element
 * @param full pointer to the address of element callback that container has no elements when add element
 * @param null_heap pointer to the address of element callback that malloc is valid
 *
 * @return NONE
 */

void vector_control_configuration_callback(VECTOR_TYPEDEF_PTR vector,
										   void (*empty)(void), void (*full)(void), void (*null_heap)(void))
{
	vector->callback.empty = empty;
	vector->callback.full = full;
	vector->callback.null_heap = null_heap;
}

/**
 * @brief This function will
 *
 * @param vector container struct
 *
 * @return NONE
 */

void vector_control_iterators_front(VECTOR_TYPEDEF_PTR vector)
{
	// TODO ...
}

/**
 * @brief This function will
 *
 * @param vector container struct
 *
 * @return NONE
 */

void vector_control_iterators_back(VECTOR_TYPEDEF_PTR vector)
{
	// TODO ...
}

/**
 * @brief This function will returns a reference to the element at specified location position, with bounds checking.
 *
 * @param vector container struct
 * @param position the position of element
 *
 * @return NONE
 */

void *vector_control_element_access_at(VECTOR_TYPEDEF_PTR vector,
									   VECTOR_SIZE_TYPEDEF position)
{
	assert(vector);
	assert(0 <= position);

	void
		*element = (void *)((int)vector->data + position * vector->info.mem_size);

	printf("vector.at -> data block : %p | element : %p \r\n", vector->data, element);

	return element;
}

/**
 * @brief This function will returns a reference to the first element in the container.
 *
 * @param vector container struct
 *
 * @return NONE
 */

void *vector_control_element_access_front(VECTOR_TYPEDEF_PTR vector)
{
	assert(vector);

	return vector_control_element_access_at(vector, 0);
}

/**
 * @brief This function will returns reference to the last element in the container.
 *
 * @param vector container struct
 *
 * @return NONE
 */

void *vector_control_element_access_back(VECTOR_TYPEDEF_PTR vector)
{
	assert(vector);

	return vector_control_element_access_at(vector, vector->info.capacity - 1);
}

/**
 * @brief This function will checks if the container has no elements.
 *
 * @param vector container struct
 *
 * @return
 *  if the container has no elements
 */

extern inline bool vector_control_capacity_empty(VECTOR_TYPEDEF_PTR vector)
{
	assert(vector);

	if (vector->info.max_size <= vector->info.capacity) {
		return true;
	} else {
		return false;
	}
}

/**
 * @brief This function will returns the number of elements in the container.
 *
 * @param vector container struct
 *
 * @return
 *  the number of elements in the container
 */

VECTOR_SIZE_TYPEDEF vector_control_capacity_size(VECTOR_TYPEDEF_PTR vector)
{
	assert(vector);

	return vector->info.capacity;
}

/**
 * @brief This function will returns the maximum number of elements the container.
 * is able to hold due to system or library implementation limitations.
 *
 * @param vector container struct
 *
 * @return
 *  the maximum number of elements the container
 */

VECTOR_SIZE_TYPEDEF vector_control_capacity_max_size(VECTOR_TYPEDEF_PTR vector)
{
	assert(vector);

	return VECTOR_CFG_DEFAULT_HARDWARE_MAX_AVAILABLE_HEAP_SIZE / vector->info.mem_size;
}

/**
 * @brief This function will returns the number of elements that the container has currently allocated space for.
 *
 * @param vector container struct
 *
 * @return
 *  the number of elements that the container has currently allocated space for
 */

VECTOR_SIZE_TYPEDEF vector_control_capacity_capacity(VECTOR_TYPEDEF_PTR vector)
{
	assert(vector);

	return vector->info.max_size * vector->info.mem_size;
}

/**
 * @brief This function will increase the capacity of the vector to a size that's greater or equal to new_cap.
 *
 * @param vector container struct
 * @param position the position of element
 * @param size the size of elements
 *
 * @return NONE
 */

void vector_control_capacity_reserve(VECTOR_TYPEDEF_PPTR vector,
									 VECTOR_SIZE_TYPEDEF size)
{
	assert(vector);
	assert(0 <= size);

	// TODO...
}

/**
 * @brief This function will requests the removal of unused capacity.
 *
 * @param vector container struct
 *
 * @return NONE
 */

void vector_control_capacity_shrink_to_fit(VECTOR_TYPEDEF_PPTR vector)
{
	assert(vector);

	// TODO...
}

/**
 * @brief This function will set elements at the specified location in the container.
 *
 * @param vector container struct
 * @param position the position of element
 * @param source pointer to the source
 *
 * @return NONE
 */

void vector_control_modifiers_set(VECTOR_TYPEDEF_PTR vector,
								  VECTOR_SIZE_TYPEDEF position, void *source)
{
	assert(vector);
	assert(0 <= position);
	assert(source);

	void
		*destination = (void *)((int)vector->data + position * vector->info.mem_size);

	//printf("vector.set -> data block : %p | element : %p \r\n", vector->data, destination);

	if (NULL != vector->element_handler.assign) {
		vector->element_handler.assign(destination, source);
	} else {
		if (vector->info.string_type) {
			strcpy(destination, source);
		} else {
			memcpy(destination, source, vector->info.mem_size);
		}
	}
}

/**
 * @brief This function will get elements at the specified location in the container.
 *
 * @param vector container struct
 * @param position the position of element
 * @param destination pointer to the destination
 *
 * @return NONE
 */

void vector_control_modifiers_get(VECTOR_TYPEDEF_PTR vector,
								  VECTOR_SIZE_TYPEDEF position, void *destination)
{
	assert(vector);
	assert(0 <= position);
	assert(destination);

	void
		*source = (void *)((int)vector->data + position * vector->info.mem_size);

	if (NULL == source) {
		return;
	}

	//printf("vector.get -> data block : %p | element : %p \r\n", vector->data, source);

	if (NULL != vector->element_handler.assign) {
		vector->element_handler.assign(destination, source);
	} else {
		if (vector->info.string_type) {
			strcpy(destination, source);
		} else {
			memcpy(destination, source, vector->info.mem_size);
		}
	}
}

/**
 * @brief This function will delete elements at the specified location in the container.
 *
 * @param vector container struct
 * @param position the position of element
 *
 * @return NONE
 */

void vector_control_modifiers_del(VECTOR_TYPEDEF_PTR vector,
								  VECTOR_SIZE_TYPEDEF position)
{
	assert(vector);
	assert(0 <= position);

	vector_control_modifiers_set(vector, position, "");

	vector->info.capacity--;
}

/**
 * @brief This function will erases all elements from the container.
 *
 * @param vector container struct
 *
 * @return NONE
 */

void vector_control_modifiers_clear(VECTOR_TYPEDEF_PTR vector)
{
	assert(vector);

	if (0 >= vector->info.capacity) {
		if (NULL != vector->callback.empty) {
			vector->callback.empty();
		}

		return;
	}

	printf("vector.clear -> capacity : %d \r\n", vector->info.capacity);

	for (VECTOR_SIZE_TYPEDEF element_pos = 0; element_pos < vector->info.capacity; element_pos++) {
		vector_control_modifiers_set(vector, element_pos, "");
	}

	vector->info.capacity = 0;
}

/**
 * @brief This function will inserts elements at the specified location in the container.
 *
 * @param vector container struct
 * @param position the position of element
 * @param amount the amount of elements
 * @param source pointer to the source
 *
 * @return
 *  the address of element the asserted
 */

void *vector_control_modifiers_insert(VECTOR_TYPEDEF_PTR vector,
									  VECTOR_SIZE_TYPEDEF position, VECTOR_SIZE_TYPEDEF amount, void **source)
{
	assert(vector);
	assert(0 <= position);
	assert(0 <= amount);
	assert(source);
	assert(*source);

	if (vector->info.max_size <= vector->info.capacity) {
		if (NULL != vector->callback.full) {
			vector->callback.full();
		}

		return NULL;
	}

	void
		**element = calloc(1, sizeof(void **));

	VECTOR_SIZE_TYPEDEF
		element_amount = vector->info.capacity - position,
		back_element_pos = position + amount;

	if (NULL == element) {
		return NULL;
	}

	printf("vector.insert -> element amount : %d \r\n", element_amount);

	for (VECTOR_SIZE_TYPEDEF element_pop = position; element_pop < vector->info.capacity; element_pop++) {		/* Copy the vector to element */
		*(element + element_pop) = calloc(1, vector->info.mem_size);

		vector_control_modifiers_get(vector, element_pop, *(element + element_pop));

		printf("vector.insert -> element no.%d : %s \r\n", element_pop, (char *)*(element + element_pop));
	}

	for (VECTOR_SIZE_TYPEDEF element_pop = position; element_pop < back_element_pos; element_pop++) {			/* Insert the source to the vector */
		vector_control_modifiers_set(vector, element_pop, *(source + element_pop));

		printf("vector.insert -> source no.%d : %s \r\n", element_pop, (char *)*(source + element_pop));
	}

	for (VECTOR_SIZE_TYPEDEF element_pop = back_element_pos; element_pop < back_element_pos + element_amount; element_pop++) {	/* Insert the elements to the vector */
		vector_control_modifiers_set(vector, element_pop, *(element + element_pop - back_element_pos));
	}

	for (VECTOR_SIZE_TYPEDEF element_cnt = 0; element_cnt < element_amount; element_cnt++) {
		free(*(element + element_cnt));

		*(element + element_cnt) = NULL;
	}

	free(*element);
	*element = NULL;

	vector->info.capacity += amount;

	return vector_control_element_access_at(vector, position);
}

/**
 * @brief This function will erases the specified elements from the container.
 *
 * @param vector container struct
 * @param position the position of element
 * @param destination pointer to the destination
 *
 * @return NONE
 */

void vector_control_modifiers_erase(VECTOR_TYPEDEF_PTR vector,
									VECTOR_SIZE_TYPEDEF position, void *destination)
{
	assert(vector);
	assert(0 <= position);
	assert(destination);

	if (0 >= vector->info.capacity) {
		if (NULL != vector->callback.empty) {
			vector->callback.empty();
		}

		return;
	}

	vector_control_modifiers_get(vector, position, destination);

	vector_control_modifiers_del(vector, position);
}

/**
 * @brief This function will appends the given element source to the end of the container.
 *
 * @param vector container struct
 * @param source pointer to source
 *
 * @return NONE
 */

void vector_control_modifiers_push_back(VECTOR_TYPEDEF_PTR vector,
										void *source)
{
	assert(vector);
	assert(source);

	if (vector->info.max_size <= vector->info.capacity) {
		if (NULL != vector->callback.full) {
			vector->callback.full();
		}

		return;
	}

	vector_control_modifiers_set(vector, (vector->info.capacity) ? vector->info.capacity - 1 : 0, source);

	vector->info.capacity++;
}

/**
 * @brief This function will removes the last element of the container.
 *
 * @param vector container struct
 * @param destination pointer to destination
 *
 * @return NONE
 */

void vector_control_modifiers_pop_back(VECTOR_TYPEDEF_PTR vector,
									   void *destination)
{
	assert(vector);
	assert(destination);

	if (vector->info.capacity <= 0) {
		if (NULL != vector->callback.empty) {
			vector->callback.empty();
		}

		return;
	}

	vector_control_modifiers_get(vector, (vector->info.capacity) ? vector->info.capacity - 1 : 0, destination);

	vector_control_modifiers_del(vector, (vector->info.capacity) ? vector->info.capacity - 1 : 0);

	vector->info.capacity;
}

/**
 * @brief This function will resizes the container to contain count elements.
 *
 * @param vector container struct
 * @param count the count of elements
 *
 * @return NONE
 */

void vector_control_modifiers_resize(VECTOR_TYPEDEF_PPTR vector,
									 VECTOR_SIZE_TYPEDEF count)
{
	assert(vector);
	assert(0 <= count);

	if ((*vector)->info.max_size >= count) {
		return;
	}

	void
		*data_pack_alloced = calloc(count,
		((*vector)->info.string_type) ?
									((*vector)->info.mem_size + VECTOR_CFG_DEFAULT_MAX_SIZE) :
									((*vector)->info.mem_size));

	if (NULL == data_pack_alloced) {
		return;
	}

	(*vector)->info.max_size = count;
	(*vector)->data = data_pack_alloced;
}

/**
 * @brief This function will copy the contents of the container to those of other.
 *
 * @param destination container struct
 * @param source container struct
 *
 * @return NONE
 */

void vector_control_modifiers_copy(VECTOR_TYPEDEF_PPTR destination,
								   VECTOR_TYPEDEF_PTR source)
{
	assert(destination);
	assert(source);

	if (NULL == *destination) {
		vector_control_configuration_init(destination,
										  source->info.mem_size, source->info.string_type, source->element_handler.assign, source->element_handler.free);
	} else {
		(*destination)->info = source->info;
		(*destination)->element_handler = source->element_handler;
		(*destination)->callback = source->callback;
	}

	for (VECTOR_SIZE_TYPEDEF element_amt = 0; element_amt < source->info.capacity; element_amt++) {
		vector_control_modifiers_set(*destination, element_amt, (void *)((int)source->data + element_amt * source->info.mem_size));
	}
}

/**
 * @brief This function will exchanges the contents of the container with those of other.
 *
 * @param vector container struct
 * @param other container struct
 *
 * @return NONE
 */

void vector_control_modifiers_swap(VECTOR_TYPEDEF_PPTR vector,
								   VECTOR_TYPEDEF_PPTR other)
{
	assert(vector);
	assert(other);
	assert(*vector);

	VECTOR_TYPEDEF_PTR
		vector_swap = NULL;

	vector_control_modifiers_copy(&vector_swap, *other);

	vector_control_modifiers_copy(other, *vector);

	vector_control_modifiers_copy(vector, vector_swap);
}

#endif