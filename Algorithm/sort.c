/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "sort.h"

/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

/* Define			sort control common assert block.													*/
#define SORT_CONTROL_COMMON_ASSERT_BLOCK()																\
	assert((int)0 <= (int)left);																		\
	assert((int)0 <= (int)right);																		\
	assert((int)left < (int)right);																		\
	assert(package.mem_len);																			\
	assert(package.object_ptr);																			\
	assert((package.object_operator.get_element_ptr || package.object_operator.get_address_ptr)			\
		   ? (package.object_operator.get_element_ptr && package.object_operator.get_address_ptr)		\
		   : (true))

/* Define			sort control common prepare block.													*/
#define SORT_CONTROL_COMMON_PREPARE_BLOCK()																\
	SORT_CONTROL_COMMON_ASSERT_BLOCK();																	\
	sort_control_common_default_package(&package)

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

/**
 * @brief This type is the sort algorithm category enum.
 */

void *sort_control_algorithm_address_table[] = {
	sort_control_bubble_sort,
	sort_control_quick_sort
};

/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/**
 * @brief This function will get the element of object.
 *
 * @param package the package of the sort
 * @param index the index of the element
 *
 * @return the element pointer
 */

void *sort_control_common_get_element(struct sort_package_s sort_package,
									  size_t index);

/**
 * @brief This function will get the address of element.
 *
 * @param package the package of the sort
 * @param index the index of the element
 *
 * @return the address of the element
 */

void *sort_control_common_get_address(struct sort_package_s sort_package,
									  size_t index);

/**
 * @brief This function will default the package.
 *
 * @param package the package of the sort
 *
 * @return the error code
 */

static inline errno_t
sort_control_common_default_package(struct sort_package_s *package);

/**
 * @brief This function will compare the elements.
 *
 * @param sort_package the package of the sort
 * @param left the index of the left element
 * @param right the index of the right element
 *
 * @return the error code
 */

errno_t sort_control_common_compare(struct sort_package_s package,
									size_t left,
									size_t right);

/**
 * @brief This function will swap the elements.
 *
 * @param sort_package the package of the sort
 * @param left the index of the left element
 * @param right the index of the right element
 *
 * @return the error code
 */

errno_t sort_control_common_swap(struct sort_package_s package,
								 size_t left,
								 size_t right);

/**
 * @brief This function will partition the object for the quick sort algorithm.
 *
 * @param package the package of sort algorithm
 * @param left the leftmost index of the element
 * @param right the rightmost index of the element
 *
 * @return void
 */

size_t sort_contorl_quick_sort_partition(struct sort_package_s package,
										 size_t left,
										 size_t right);

/*
*********************************************************************************************************
*                                            FUNCTIONS
*********************************************************************************************************
*/

/**
 * @brief This function will sort the object by the sort algorithm.
 *
 * @param type the type of sort algorithm
 * @param package the package of sort algorithm
 * @param left the leftmost index of the element
 * @param right the rightmost index of the element
 *
 * @return void
 */

extern inline errno_t
sort_control(enum sort_algorithm_type type,
			 struct sort_package_s package,
			 size_t left,
			 size_t right)
{
	assert(0 <= left);
	assert(0 <= right);
	assert(left < right);
	assert(package.mem_len);
	assert(package.object_ptr);
	assert((package.object_operator.get_element_ptr || package.object_operator.get_address_ptr)
		   ? (package.object_operator.get_element_ptr && package.object_operator.get_address_ptr)
		   : (true));																		/* Assert if both the operators valid */

	sort_t sort = sort_control_algorithm_address_table[type];								/* Get the sort algorithm function address */

	return sort(package, left, right);
}

/**
 * @brief This function will sort the object by the bubble sort algorithm.
 *
 * @param package the package of sort algorithm
 * @param left the leftmost index of the element
 * @param right the rightmost index of the element
 *
 * @return void
 */

errno_t sort_control_bubble_sort(struct sort_package_s package,
								 size_t left,
								 size_t right)
{
	SORT_CONTROL_COMMON_PREPARE_BLOCK();

	for (size_t cnt = left; cnt < right; cnt++) {
		for (size_t ct = left; ct < right - cnt; ct++) {
			switch (sort_control_common_compare(package, ct, ct + 1)) {							/* Compare the element */
				case true:
					if (sort_control_common_swap(package, ct, ct + 1)) {						/* Swap the element */
						return 2;
					}
					break;
				case false:
					break;
				default:
					return 1;
			}
		}
	}

	return 0;
}

/**
 * @brief This function will sort the object by the quick sort algorithm.
 *
 * @param package the package of sort algorithm
 * @param left the leftmost index of the element
 * @param right the rightmost index of the element
 *
 * @return void
 */

errno_t sort_control_quick_sort(struct sort_package_s package,
								size_t left,
								size_t right)
{
	SORT_CONTROL_COMMON_PREPARE_BLOCK();

	size_t
		pivot_index = sort_contorl_quick_sort_partition(package, left, right);

	if ((int)0 > (int)pivot_index) {
		return 1;
	}

	if ((int)left < (int)pivot_index - 1) {
		sort_control_quick_sort(package, left, pivot_index - 1);
	}

	if ((int)pivot_index + 1 < (int)right) {
		sort_control_quick_sort(package, pivot_index + 1, right);
	}

	return 0;
}

/**
 * @brief This function will get the element of object.
 *
 * @param package the package of the sort
 * @param index the index of the element
 *
 * @return the element pointer
 */

static inline void
*sort_control_common_get_element(struct sort_package_s sort_package,
								 size_t index)
{
	assert(0 <= index);

	static void *value;

	if (NULL == sort_package.object_operator.get_element_ptr) {								/* If the object operator is valid */
		value = *(void **)((size_t)sort_package												/* Calculate the element */
						   .object_ptr + index * sort_package.mem_len);
	} else {
		value = sort_package.object_operator												/* Get the element */
			.get_element_ptr(sort_package.object_ptr, index);
	}

	return value;
}

/**
 * @brief This function will get the address of element.
 *
 * @param package the package of the sort
 * @param index the index of the element
 *
 * @return the address of the element
 */

static inline void
*sort_control_common_get_address(struct sort_package_s sort_package,
								 size_t index)
{
	assert(0 <= index);

	static void *address;

	if (NULL == sort_package.object_operator.get_element_ptr) {								/* If the object operator is valid */
		address = (void *)((size_t)sort_package												/* Calculate the address */
						   .object_ptr + index * sort_package.mem_len);
	} else {
		address = sort_package.object_operator												/* Get the address */
			.get_address_ptr(sort_package.object_ptr, index);
	}

	return address;
}

/**
 * @brief This function will default the package.
 *
 * @param package the package of the sort
 *
 * @return the error code
 */

static inline errno_t
sort_control_common_default_package(struct sort_package_s *package)
{
	if (0u == package->mem_len_key) {
		package->mem_len_key = package->mem_len;												/* Default the memory length of the object's compare key */
	}

	if (NULL == package->compare_ptr
		&& NULL == (package->compare_ptr = SORT_CFG_DEFAULT_COMPARE_ADDRESS)) {					/* Default the compare function */
		return 1;
	}

	if (NULL == package->swap_ptr
		&& NULL == (package->swap_ptr = SORT_CFG_DEFAULT_SWAP_ADDRESS)) {						/* Default the swap function */
		return 2;
	}

	return 0;
}

/**
 * @brief This function will compare the elements.
 *
 * @param package the package of the sort
 * @param left the index of the left element
 * @param right the index of the right element
 *
 * @return the error code
 */

static inline errno_t
sort_control_common_compare(struct sort_package_s package,
							size_t left,
							size_t right)
{
	assert(0 <= left);
	assert(0 <= right);

	static char
		*value_lhs,
		*value_rhs;

	value_lhs = sort_control_common_get_element(package, left);
	value_rhs = sort_control_common_get_element(package, right);

	if (NULL == value_lhs &&
		NULL == value_rhs) {
		return 0xff;
	}

	#if (SORT_CFG_DEBUG_EN)

	printf("sort_algorithm.common.compare: lhs:\"%s\" rhs:\"%s\" \r\n"
		   , value_lhs, value_rhs);

	#endif // (SORT_CFG_DEBUG_EN)

	if (package.compare_ptr(value_lhs, value_rhs, package.mem_len_key)) {
		return 1;
	}

	return 0;
}

/**
 * @brief This function will swap the elements.
 *
 * @param package the package of the sort
 * @param left the index of the left element
 * @param right the index of the right element
 *
 * @return the error code
 */

static inline errno_t
sort_control_common_swap(struct sort_package_s package,
						 size_t left,
						 size_t right)
{
	assert(0 <= left);
	assert(0 <= right);

	static void
		*address_lhs,
		*address_rhs;

	address_lhs = sort_control_common_get_address(package, left);
	address_rhs = sort_control_common_get_address(package, right);

	if (NULL == address_lhs &&
		NULL == address_rhs) {
		return 1;
	}

	#if (SORT_CFG_DEBUG_EN)

	printf("sort_algorithm.common.swap: lhs:%p rhs:%p \r\n"
		   , address_lhs, address_rhs);

	#endif // (SORT_CFG_DEBUG_EN)

	if (package.swap_ptr(address_lhs, address_rhs, package.mem_len)) {						/* Swap the value */
		return 2;
	}

	return 0;
}

/**
 * @brief This function will partition the object for the quick sort algorithm.
 *
 * @param package the package of sort algorithm
 * @param left the leftmost index of the element
 * @param right the rightmost index of the element
 *
 * @return void
 */

size_t sort_contorl_quick_sort_partition(struct sort_package_s package,
										 size_t left,
										 size_t right)
{
	assert((int)left < (int)right);

	size_t
		pivot = right,
		tail = left - 1;

	for (size_t cnt = left; cnt < right; cnt++) {
		switch (sort_control_common_compare(package, pivot, cnt)) {							/* Compare the element */
			case true:
				if (sort_control_common_swap(package, ++tail, cnt)) {						/* Swap the element */
					return -1;
				}
				break;
			case false:
				break;
			default:
				return -2;
		}
	}

	if (sort_control_common_swap(package, tail + 1, pivot)) {								/* Swap the pivot behind the tail */
		return -3;
	}

	return tail + 1;																		/* Return the index of pivot */
}