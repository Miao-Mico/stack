/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
*               through use of the definition module present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef __DEQUE_H
#define __DEQUE_H

/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "container_def.h"

/*
*********************************************************************************************************
*									            DEFINES
*********************************************************************************************************
*/

/* Configure    the type of allocator.                                                                  */
#define DEQUE_CFG_MAX_SIZE										50u

/* Configure    the type of allocator.                                                                  */
#define DEQUE_CFG_ALLOCATOR_TYPE                                ALLOCATOR_COMMON

/* Configure    if enable integrated structure.                                                         */
#define DEQUE_CFG_INTEGRATED_STRUCTURE_MODE_EN			        1u

/* Configure    if enable stack debug.																    */
#define DEQUE_CFG_DEBUG_EN										0u

/*
*********************************************************************************************************
*									           DATA TYPES
*********************************************************************************************************
*/

typedef struct deque_s
*deque_stp,
**deque_stpp;

/**
 * @brief This struct is the deque element operator structure module
 */

struct deque_control_s {
	struct {
		/* @brief This function will initialize the deque struct.                                      */
		void (*init)(deque_stpp deque,
					 container_size_t dst_size,
					 generic_type_element_assign_t assign,
					 generic_type_element_free_t free);

		/* @brief This function will destroy the deque struct and free the space.                      */
		void (*destroy)(deque_stpp deque);

		/* @brief This function will configure the deque element handler.                              */
		void (*element_handler)(deque_stp deque,
								generic_type_element_assign_t assign,
								generic_type_element_free_t free);

		/* @brief This function will configure the deque exception callback.                           */
		void (*exception)(deque_stp deque,
						  void (*empty)(void), void (*full)(void));
	}configuration;

	struct {
		/* @brief This function will initialize the deque struct.                                      */
		void (*begin)(deque_stp deque);

		/* @brief This function will initialize the deque struct.                                      */
		void (*end)(deque_stp deque);
	}iterators;

	struct {
		/* @brief This function will returns a reference to the element
				  at specified location position, with bounds checking.                                 */
		void *(*at)(deque_stp deque,
					container_size_t position);

		/* @brief This function will returns a reference to the first element in the container.         */
		void *(*front)(deque_stp deque);

		/* @brief This function will returns reference to the last element in the container.            */
		void *(*back)(deque_stp deque);
	}element_access;

	struct {
		/* @brief This function will checks if the container has no elements.                           */
		bool (*empty)(deque_stp deque);

		/* @brief This function will returns the number of elements in the container.                   */
		container_size_t(*size)(deque_stp deque);

		/* @brief This function will returns the maximum number of elements the container
				  is able to hold due to system or library implementation limitations.                  */
		container_size_t(*max_size)(deque_stp deque);

		/* @brief This function will resizes the container to contain count elements.                   */
		void (*resize)(deque_stpp deque,
					   container_size_t size);

		/* @brief This function will requests the removal of unused capacity.                           */
		void (*shrink_to_fit)(deque_stpp deque);
	}capacity;

	struct {
		/* @brief This function will erases all elements from the container.                            */
		void (*clear)(deque_stp deque);

		/* @brief This function will inserts elements at the specified location in the container.       */
		void (*insert)(deque_stp deque,
					   container_size_t position,
					   container_size_t amount, void **source);

	   /* @brief This function will erases the specified elements from the container.                  */
		void (*erase)(deque_stp deque,
					  container_size_t position);

		/* @brief This function will prepends the given element value to the beginning of the container.*/
		void (*push_front)(deque_stp deque,
						   void *source);

		/* @brief This function will inserts a new element to the beginning of the container.           */
		void (*emplace_front)(deque_stp deque,
							  void *source);

		/* @brief This function will removes the first element of the container.                        */
		void (*pop_front)(deque_stp deque);

		/* @brief This function will appends the given element source to the end of the container.      */
		void (*push_back)(deque_stp deque,
						  void *source);

		/* @brief This function will removes the last element of the container.                         */
		void (*pop_back)(deque_stp deque);

		/* @brief This function will exchanges the contents of the container with those of other.       */
		void (*swap)(deque_stpp deque,
					 deque_stpp other);

		/* @brief This function will copy the contents of the container to those of other.              */
		void (*copy)(deque_stpp destination,
					 deque_stp source);
	}modifiers;
};

/*
*********************************************************************************************************
*								            FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                       EXTERN GLOBAL VARIABLES
*********************************************************************************************************
*/

/**
 * @brief This function will initialize the deque struct.
 *
 * @param deque the pointer to the container struct pointer
 * @param element_size the pointer to container
 * @param string_type the pointer to container
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

void deque_control_configuration_init(struct deque_s **deque,
									  container_size_t element_size,
									  generic_type_element_assign_t assign,
									  generic_type_element_free_t free);

/**
 * @brief This function will destroy the deque struct and free the space.
 *
 * @param deque the pointer to the container struct pointer
 *
 * @return
 *  - 0    : succeed,destroy the deque struct and free the space completely
 *  - else : fail
 */

void deque_control_configuration_destroy(struct deque_s **deque);

/**
 * @brief This function will configure the deque element handler.
 *
 * @param deque the pointer to the container struct
 * @param assign pointer to the address of element assign handler
 * @param free pointer to the address of element free handler
 *
 * @return NONE
 */

void deque_control_configuration_element_handler(struct deque_s *deque,
												 generic_type_element_assign_t assign,
												 generic_type_element_free_t free);

/**
 * @brief This function will configure the deque exception callback.
 *
 * @param deque the pointer to the container struct
 * @param empty the pointer to the handler that container has no elements when the container temp to insert
 * @param full the pointer to the handler that container has no elements when the container temp to erase
 *
 * @return NONE
 */

void deque_control_configuration_exception(struct deque_s *deque,
										   void (*empty)(void), void (*full)(void));

/**
 * @brief This function will
 *
 * @param deque the pointer to the container struct
 *
 * @return NONE
 */

void deque_control_iterators_front(struct deque_s *deque);

/**
 * @brief This function will
 *
 * @param deque the pointer to the container struct
 *
 * @return NONE
 */

void deque_control_iterators_back(struct deque_s *deque);

/**
 * @brief This function will returns a reference to the element at specified location position, with bounds checking.
 *
 * @param deque the pointer to the container struct
 * @param position the position of element,it would be equal or greater than zero,it would be equal or greater than zero
 *
 * @return NONE
 */

void *deque_control_element_access_at(struct deque_s *deque,
									  container_size_t position);

/**
 * @brief This function will returns a reference to the first element in the container.
 *
 * @param deque the pointer to the container struct
 *
 * @return NONE
 */

extern inline void *deque_control_element_access_front(struct deque_s *deque);

/**
 * @brief This function will returns reference to the last element in the container.
 *
 * @param deque the pointer to the container struct
 *
 * @return NONE
 */

extern inline void *deque_control_element_access_back(struct deque_s *deque);

/**
 * @brief This function will checks if the container has no elements.
 *
 * @param deque the pointer to the container struct
 *
 * @return
 *  if the container has no elements
 */

extern inline bool deque_control_capacity_empty(struct deque_s *deque);

/**
 * @brief This function will returns the number of elements in the container.
 *
 * @param deque the pointer to the container struct
 *
 * @return
 *  the number of elements in the container
 */

extern inline container_size_t deque_control_capacity_size(struct deque_s *deque);

/**
 * @brief This function will returns the maximum number of elements the container.
 * is able to hold due to system or library implementation limitations.
 *
 * @param deque the pointer to the container struct
 *
 * @return
 *  the maximum number of elements the container
 */

extern inline container_size_t deque_control_capacity_max_size(struct deque_s *deque);

/**
 * @brief This function will increase the capacity of the deque to a size that's greater or equal to new_cap.
 *
 * @param deque the pointer to the container struct
 * @param position the position of element,it would be equal or greater than zero
 * @param size the size of elements
 *
 * @return NONE
 */

void deque_control_capacity_resize(struct deque_s **deque,
								   container_size_t size);

/**
 * @brief This function will requests the removal of unused capacity.
 *
 * @param deque the pointer to the container struct
 *
 * @return NONE
 */

void deque_control_capacity_shrink_to_fit(struct deque_s **deque);

/**
 * @brief This function will erases all elements from the container.
 *
 * @param deque the pointer to the container struct
 *
 * @return NONE
 */

void deque_control_modifiers_clear(struct deque_s *deque);

/**
 * @brief This function will inserts elements at the specified location in the container.
 *
 * @param deque the pointer to the container struct
 * @param position the position of element,it would be equal or greater than zero
 * @param amount the amount of elements
 * @param source pointer to the source
 *
 * @return
 *  the address of element the asserted
 */

void deque_control_modifiers_insert(struct deque_s *deque,
									container_size_t position,
									container_size_t amount, void **source);

/**
 * @brief This function will erases the specified elements from the container.
 *
 * @param deque the pointer to the container struct
 * @param position the position of element,it would be equal or greater than zero
 * @param destination pointer to the destination
 *
 * @return NONE
 */

void deque_control_modifiers_erase(struct deque_s *deque,
								   container_size_t position);

/**
 * @brief This function will prepends the given element value to the beginning of the container
 *
 * @param list the pointer to the list struct pointer
 * @param source pointer to the source
 *
 * @return NONE
 */

void deque_control_modifiers_push_front(struct deque_s *deque,
										void *source);

/**
 * @brief This function will Inserts a new element to the beginning of the container.
			The element is constructed through std::allocator_traits::construct,
			which typically uses placement-new to construct the element in-place
			at the location provided by the container.
			The arguments args... are forwarded to the constructor as std::forward<Args>(args)....
 *
 * @param list the pointer to the list struct pointer
 * @param destination pointer to the destination
 *
 * @return NONE
 */

void deque_control_modifiers_emplace_front(struct deque_s *deque,
										   void *source);

/**
 * @brief This function will removes the first element of the container
 *
 * @param list the pointer to the list struct pointer
 *
 * @return NONE
 */

void deque_control_modifiers_pop_front(struct deque_s *deque);

/**
 * @brief This function will appends the given element source to the end of the container.
 *
 * @param deque the pointer to the container struct
 * @param source pointer to source
 *
 * @return NONE
 */

void deque_control_modifiers_push_back(struct deque_s *deque,
									   void *source);

/**
 * @brief This function will removes the last element of the container.
 *
 * @param deque the pointer to the container struct
 * @param destination pointer to destination
 *
 * @return NONE
 */

void deque_control_modifiers_pop_back(struct deque_s *deque);
/**
 * @brief This function will exchanges the contents of the container with those of other.
 *
 * @param deque the pointer to the container struct
 * @param other container struct
 *
 * @return NONE
 */

void deque_control_modifiers_swap(struct deque_s **deque,
								  struct deque_s **other);

/**
 * @brief This function will copy the contents of the container to those of other.
 *
 * @param destination container struct
 * @param source container struct
 *
 * @return NONE
 */

void deque_control_modifiers_copy(struct deque_s **destination,
								  struct deque_s *source);

/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif // !__DEQUE_H