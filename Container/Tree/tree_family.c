/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "tree_family.h"

/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

#define LINK_OPERATOR_IS_PARENT(id)																	\
	(LINK_OPERATOR_CODE_PARENT == (id))

#define LINK_OPERATOR_IS_CHILD_FAR_RIGHT(id)															\
	(LINK_OPERATOR_CODE_CHILD_FAR_RIGHT >= (id) &&														\
	(tree_family_control_node_infomation.link_element_count - 1) <= (id))

#define LINK_OPERATOR_IS_CHILD_FAR_LEFT(id)															\
	(LINK_OPERATOR_CODE_CHILD_FAR_LEFT == (id))

#define DATA_OPERATOR_IS_DATA_FAR_RIGHT(id)															\
	(DATA_OPERATOR_CODE_DATA_FAR_RIGHT >= (id) &&														\
	(tree_family_control_node_infomation.data_element_count - 1) <= (id))

#define DATA_OPERATOR_IS_DATA_FAR_LEFT(id)																\
	(DATA_OPERATOR_CODE_DATA_FAR_LEFT == (id))

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
 * @brief This variables will record the tree control environment.
 */

struct tree_family_control_environment_s tree_family_control_environment = { 0 };

/**
 * @brief This variables will record the tree's node information in control.
 */

struct tree_family_node_infomation_s tree_family_control_node_infomation = { 0 };

/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/**
 * @brief This function will call when get control of the tree-family controller.
 *
 * @param node_operator the node's operator
 *
 * @return NONE
 */

void tree_family_control_get_control_callback(enum tree_family_node_type_e member_type);

/**
* @brief This function will compare if the left-hand-side greater than the right-hand-side.
*
* @param lhs the pointer to the left-hand-side value.
* @param rhs the pointer to the right-hand-side value.
*
* @return if left-hand-side greater than the right-hand-side
*	- true	yes
*	- false	no
*/

void *tree_family_sort_algorithm_control_get_data(void *object,
												  container_size_t loc);

/**
* @brief This function will compare if the left-hand-side greater than the right-hand-side.
*
* @param lhs the pointer to the left-hand-side value.
* @param rhs the pointer to the right-hand-side value.
*
* @return if left-hand-side greater than the right-hand-side
*	- true	yes
*	- false	no
*/

void tree_family_sort_algorithm_control_swap_data(void *object,
												  container_size_t lhs, container_size_t rhs);

/**
* @brief This function will compare if the left-hand-side greater than the right-hand-side.
*
* @param lhs the pointer to the left-hand-side value.
* @param rhs the pointer to the right-hand-side value.
*
* @return if left-hand-side greater than the right-hand-side
*	- true	yes
*	- false	no
*/

bool tree_family_node_control_compare_greater(void *lhs,
											  void *rhs, container_size_t len);

/**
* @brief This function will destroy all the node when traversal.
*
* @param void
*
* @return void
*/

void tree_family_control_destroy_posorder_traversal_operator(struct tree_family_s *tree,
															 void *node,
															 container_size_t data_element_count);

/**
* @brief This function will replace the switch_control(tree) before enter control sandbox.
*
* @param void
*
* @return void
*/

void tree_family_control_switch_control_in_sandbox(struct tree_family_s *tree);

/**
* @brief This function will callback the handler that container has no elements when the container temp to insert.
*
* @param NODE
*
* @return NONE
*/

void tree_family_control_configuration_exception_default_empty_callback(void);

/**
 * @brief This function will callback the handler that container has no elements when the container temp to erase.
 *
 * @param NODE
 *
 * @return NONE
 */

void tree_family_control_configuration_exception_default_full_callback(void);

/*
*********************************************************************************************************
*					LOCAL GLOBAL VARIABLES & LOCAL FUNCTION PROTOTYPES INTERSECTION
*********************************************************************************************************
*/

/**
 * @brief This variables will record the tree's data sort package.
 */

struct sort_package_s tree_family_control_data_sort_package = {
	.object = NULL,
	.len = 0u,
	.mem_len = 0u,
	.get_value_method = tree_family_sort_algorithm_control_get_data,
	.swap_method = tree_family_sort_algorithm_control_swap_data,
	.compare_method = tree_family_node_control_compare_greater,
};

/*
*********************************************************************************************************
*                                            FUNCTIONS
*********************************************************************************************************
*/

/**
 * @brief This function will get control of the tree-family controller.
 *
 * @param node_operator the node's operator
 *
 * @return NONE
 */

extern inline void tree_family_control_get_control(struct tree_family_control_environment_s environment)
{
	if (tree_family_control_environment.member_type != environment.member_type) {
		tree_family_control_environment = environment;

		tree_family_control_get_control_callback(environment.member_type);
	}
}

/**
 * @brief This function will run the func_addr() in sandbox with specified environment.
 *
 * @param node_operator the node's operator
 *
 * @return NONE
 */

void tree_family_control_get_control_in_sandbox(struct tree_family_s *tree,
												struct tree_family_control_environment_s environment,
												void (*func_addr)(void *, ...),
												size_t count_param,
												...)
{
	tree_family_control_environment = environment;

	tree_family_control_get_control_callback(environment.member_type);

	void *switch_control_tree = tree->switch_control;										/* Store current tree's switch control address */

	tree->switch_control = tree_family_control_switch_control_in_sandbox;

	void *param_func[8] = { NULL };

	va_list va_ptr = NULL;

	va_start(va_ptr, count_param);

	for (size_t cnt = 0; cnt < count_param; cnt++) {
		param_func[cnt] = (void *)va_arg(va_ptr, size_t);
	}

	va_end(va_ptr);

	func_addr(param_func[0], param_func[1], param_func[2], param_func[3],
			  param_func[4], param_func[5], param_func[6], param_func[7]);					/* If the function's parameters are greater than 8,
																								i think you need to split the function into pieces */

	tree->switch_control = switch_control_tree;												/* Recovery current tree's switch control address */
}

/**
 * @brief This function will call when get control of the tree-family controller.
 *
 * @param node_operator the node's operator
 *
 * @return NONE
 */

static inline void tree_family_control_get_control_callback(enum tree_family_member_type_e member_type)
{
	enum tree_family_node_type_e node_type = member_type & 0x0f;

	tree_family_control_node_infomation.member_type = member_type;
	tree_family_control_node_infomation.data_element_count = node_type - 1;
	tree_family_control_node_infomation.link_element_count = node_type + 1;
	tree_family_control_node_infomation.id_data_far_right = node_type - 2;
	tree_family_control_node_infomation.id_link_far_right = node_type;
	tree_family_control_node_infomation.link_mem_len =
		tree_family_control_node_infomation.link_element_count * sizeof(void *);
}

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

void tree_family_control_configuration_init(struct tree_family_s **tree,
											void (*switch_control)(struct tree_family_s *tree),
											container_size_t degree,
											enum tree_family_member_type_e member_type,
											enum allocator_type_e allocator_type,
											container_size_t element_size,
											generic_type_element_assign_t assign,
											generic_type_element_free_t free)
{
	assert(tree);
	assert(0 <= element_size);

	void
		*allocator = NULL;

	struct allocator_control_s
		*allocator_ctrl = NULL;

	allocator_ctrl = allocator_control_convert_type_to_func_addr_table(allocator_type);	/* Variables pointer to	the function address table of
																							specified container type		*/

	allocator_ctrl->configuration.init(&allocator, NULL);

	struct tree_family_s
		*tree_alloced = allocator_ctrl->allocate(allocator,
												 1, sizeof(struct tree_family_s));	/* Allocate #1 */

	if (NULL == tree ||																	/* Check if tree point to NULL			*/
		NULL == tree_alloced) {															/* Check if tree_alloced point to NULL	*/
		return;
	}

	tree_alloced->container_type_id = member_type;										/* Assign tree structure					*/

	tree_alloced->info.max_size = 0;
	tree_alloced->info.size = 0u;
	tree_alloced->info.mem_size = element_size;
	tree_alloced->info.degree = degree;
	tree_alloced->info.minimum_key = (size_t)ceil((float)degree / 2) - 1;
	tree_alloced->info.mem_size_key = 4;

	tree_alloced->allocator = allocator;
	tree_alloced->allocator_ctrl = allocator_ctrl;

	tree_alloced->root = NULL;

	tree_alloced->exception.empty = tree_family_control_configuration_exception_default_empty_callback;
	tree_alloced->exception.full = tree_family_control_configuration_exception_default_full_callback;

	tree_alloced->switch_control = switch_control;

	if (NULL != assign &&																	/* Check if assign point to NULL			*/
		NULL != free) {																		/* Check if free point to NULL				*/
		tree_alloced->element_handler.assign = assign;
		tree_alloced->element_handler.free = free;
	}

	*tree = tree_alloced;

	#if (TREE_FAMILY_CFG_DEBUG_EN)												/* Debug only								*/

	printf("tree.configuration.init:allocator : %p \r\n", allocator);
	printf("tree.configuration.init:tree block : %p \r\n", tree_alloced);

	#endif // (TREE_FAMILY_CFG_DEBUG_EN)
}

/**
 * @brief This function will destroy the tree struct and free the space
 *
 * @param tree the pointer to the tree struct pointer
 *
 * @return NONE
 */

void tree_family_control_configuration_destroy(struct tree_family_s **tree)
{
	assert(tree);

	(*tree)->switch_control(*tree);

	void *allocator = (*tree)->allocator;

	struct allocator_control_s *allocator_ctrl = (*tree)->allocator_ctrl;

	#if (TREE_FAMILY_CFG_DEBUG_EN)

	printf("tree.configuration.destroy:tree block : %p \r\n", (*tree));
	printf("tree.configuration.destroy:allocator : %p \r\n", allocator);

	#endif // (TREE_FAMILY_CFG_DEBUG_EN)

	tree_family_control_posorder_traversal(*tree, (*tree)->root,
										   tree_family_control_destroy_posorder_traversal_operator);

	allocator_ctrl->deallocate(allocator, *tree, 1);																			/* deallocate #1 */

	allocator_ctrl->configuration.destroy(&allocator);

	*tree = NULL;
}

/**
 * @brief This function will configure the tree element handler
 *
 * @param tree the pointer to the tree struct pointer
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

void tree_family_control_configuration_element_handler(struct tree_family_s *tree,
													   generic_type_element_assign_t assign,
													   generic_type_element_free_t free)
{
	assert(tree);
	assert(assign);
	assert(free);

	tree->element_handler.assign = assign;
	tree->element_handler.free = free;
}

/**
 * @brief This function will configure the tree exception callback
 *
 * @param tree the pointer to the tree struct pointer
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

void tree_family_control_configuration_exception(struct tree_family_s *tree,
												 void (*empty)(void), void (*full)(void))
{
	assert(tree);

	if (NULL == empty) {
		tree->exception.empty = empty;
	}

	if (NULL == full) {
		tree->exception.full = full;
	}
}

/**
 * @brief This function will get the node at the specified location in the container.
 *
 * @param tree the pointer to the tree struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

tree_family_search_node_return_st
tree_family_control_search(struct tree_family_s *tree, void *data)
{
	assert(tree);

	tree_family_search_node_return_st search_return = { SEARCH_CODE_NO_SUCH_ELEMENT };

	if (NULL == data) {
		goto EXIT;
	}

	tree->switch_control(tree);

	struct tree_family_chain_node_s *node_current = tree->root;

	while (NULL != node_current) {
		search_return.location = tree_family_control_environment.node_operator.search_match_rule(tree, node_current, data);

		if (SEARCH_CODE_NO_SUCH_ELEMENT != search_return.location) {
			search_return.node = node_current;
			search_return.content = (void *)((size_t)(*((void **)node_current->data + search_return.location)) +
											 tree->info.mem_size_key);

			goto EXIT;
		}

		search_return.node_prev = node_current;

		search_return.estimate = tree_family_control_environment.node_operator.search_recursion_rule(tree, &node_current, data);
	}

EXIT:

	return search_return;
}

/**
 * @brief This function will set the node at the specified location in the container.
 *
 * @param tree the pointer to the tree struct pointer
 * @param node the pointer to the tree node struct pointer
 * @param position the position of node
 *
 * @return NONE
 */

void tree_family_control_insert(struct tree_family_s *tree, void *data)
{
	assert(tree);

	if (NULL == data) {
		return;
	}

	tree->switch_control(tree);

	tree_family_search_node_return_st
		search_return = tree_family_control_search(tree, data);

	if (SEARCH_CODE_NO_SUCH_ELEMENT == search_return.location) {													/* Can't search the node */
		if (NULL == search_return.node_prev) {
			void *data_cpy = tree->allocator_ctrl->allocate(tree->allocator, 1, tree->info.mem_size);

			tree->root = tree_family_control_init_node(tree);

			if (NULL != tree->root &&
				NULL != data_cpy) {
				memcpy(data_cpy, data, tree->info.mem_size);
				tree_family_node_control_set_data(tree, tree->root, data_cpy, DATA_OPERATOR_CODE_DATA_FAR_LEFT);
			}
		} else {
			tree_family_control_environment.node_operator.insert_rule(tree, search_return, data);
		}
	}
}

/**
 * @brief This function will delete the node at the specified location in the container.
 *
 * @param tree the pointer to the tree struct pointer
 * @param position the position of node,it would be equal or greater than zero
 *
 * @return NONE
 */

void tree_family_control_delete(struct tree_family_s *tree,
								void *data)
{
	assert(tree);
	assert(data);

	tree->switch_control(tree);

	struct tree_family_search_node_return_s
		search_return = tree_family_control_search(tree, data);

	if (SEARCH_CODE_NO_SUCH_ELEMENT != search_return.location) {							/* Can search the node */
		void *item_del =
			tree_family_control_environment.
			node_operator.
			delete_rule(tree, search_return, data);

		if (NULL != item_del) {
			if (TREE_FAMILY_B_TREE > tree->container_type_id) {
				tree_family_control_destroy_node(tree, &item_del);
			} else {
				tree_family_node_control_destroy_data(tree, &item_del);
			}
		}
	}
}

/**
 * @brief This function will initialize the tree node struct.
 *
 * @param tree the pointer to the tree struct pointer
 *
 * @return NONE
 */

void *tree_family_control_init_node(struct tree_family_s *tree)
{
	assert(tree);

	struct tree_family_chain_node_s
		*node_alloced = tree->allocator_ctrl->allocate(tree->allocator,
													   1, sizeof(struct tree_family_chain_node_s));	/* Allocate #1 */

	void *data_pack_allocated = tree->allocator_ctrl->allocate(tree->allocator,
															   1, tree->info.mem_size);				/* Allocate #2 */

	void *link_pack_allocated = tree->allocator_ctrl->allocate(tree->allocator,
															   1, tree_family_control_node_infomation.link_mem_len);					/* Allocate #3 */

	if (NULL == tree ||																				/* Check if tree point to NULL					*/
		NULL == node_alloced ||																		/* Check if tree node point to NULL				*/
		NULL == data_pack_allocated ||																/* Check if tree node data pack point to NULL	*/
		NULL == link_pack_allocated) {																/* Check if tree node link pack point to NULL	*/
		return NULL;
	}

	node_alloced->data = data_pack_allocated;
	node_alloced->link = link_pack_allocated;

	return node_alloced;
}

/**
 * @brief This function will destroy tree node struct and free the space.
 *
 * @param tree the pointer to the tree struct pointer
 * @param node the pointer to the tree node struct pointer
 *
 * @return NONE
 */

void tree_family_control_destroy_node(struct tree_family_s *tree,
									  void **node)
{
	assert(tree);

	if (NULL == *node) {
		return;
	}

	struct tree_family_chain_node_s *node_destroy = *node;

	tree->allocator_ctrl->deallocate(tree->allocator, node_destroy->data, 1);				/* Deallocate #2 */

	tree->allocator_ctrl->deallocate(tree->allocator, node_destroy->link, 1);				/* Deallocate #3 */

	tree->allocator_ctrl->deallocate(tree->allocator, *node, 1);							/* Deallocate #1 */

	*node = NULL;
}

/**
 * @brief This function will initialize the tree node's data struct.
 *
 * @param void
 *
 * @return void
 */

void *tree_family_node_control_init_data(struct tree_family_s *tree)
{
	struct tree_family_chain_node_data_content_s
		*block_data_allocated = tree->allocator_ctrl->allocate(tree->allocator, 1,
															   tree->info.mem_size);

	return block_data_allocated;
}

/**
 * @brief This function will destroy the data.
 *
 * @param void
 *
 * @return void
 */

void tree_family_node_control_destroy_data(struct tree_family_s *tree,
										   void **data)
{
	assert(tree);
	assert(data);

	tree->allocator_ctrl->deallocate(tree->allocator, *data, 1);

	*data = NULL;
}

/**
 * @brief This function will set the data into the node.
 *
 * @param void
 *
 * @return void
 */

void tree_family_node_control_set_data(struct tree_family_s *tree,
									   struct tree_family_chain_node_s *node,
									   void *data,
									   container_size_t id)
{
	assert(tree);
	assert(node);

	tree->switch_control(tree);

	if (NULL == data ||
		NULL != *((void **)node->data + 												/* If have enough space for the data */
				  tree_family_control_node_infomation.id_data_far_right)) {
		return;
	}

	if (DATA_OPERATOR_IS_DATA_FAR_RIGHT(id)) {											/* Determine the data's id */
		if (NULL != *((void **)node->data + DATA_OPERATOR_CODE_DATA_FAR_LEFT)) {		/* Set the data as the far right one */
			id = tree_family_control_node_infomation.id_data_far_right;

			while (NULL == *((void **)node->link + id) &&
				   DATA_OPERATOR_CODE_DATA_FAR_LEFT < --id);
		}
	}

	container_size_t id_data = tree_family_control_node_infomation.id_data_far_right;

	while (id < id_data &&																/* Sort the data to make a space */
		   NULL != *((void **)node->data + id_data)) {
		*((void **)node->data + id_data) = *((void **)node->data + --id_data);
	}

	*((void **)node->data + id) = data;													/* Set the data to the space */
}

/**
 * @brief This function will insert the data into the node,which means have to sort.
 *
 * @param void
 *
 * @return void
 */

void tree_family_node_control_insert_data(struct tree_family_s *tree,
										  struct tree_family_chain_node_s *node,
										  void *data)
{
	assert(tree);
	assert(node);

	tree->switch_control(tree);

	if (NULL == node->data ||
		NULL == data) {
		return;
	}

	void *data_node = node->data;

	if (0 == tree_family_node_control_get_node_type(tree, node)) {
		*((void **)data_node) = tree_family_node_control_init_data(tree);

		if (NULL == *((void **)data_node)) {
			return;
		}

		memcpy(*((void **)data_node), data, tree->info.mem_size);
	} else {
		void
			*data_cpy = tree->allocator_ctrl->allocate(tree->allocator, 1, tree->info.mem_size),
			*data_package_sort = tree->allocator_ctrl->allocate(tree->allocator, 			/* The package which store the address of the node's data */
																tree_family_control_node_infomation.data_element_count + 1,
																sizeof(void *));

		if (NULL == data_cpy ||
			NULL == data_package_sort) {
			return;
		}

		memcpy(data_cpy, data, tree->info.mem_size);

		for (size_t id_data = DATA_OPERATOR_CODE_DATA_FAR_LEFT; id_data < tree_family_control_node_infomation.data_element_count; id_data++) {
			*((void **)data_package_sort + id_data) = (void *)((size_t)data_node + id_data * sizeof(void *));
		}

		*((void **)data_package_sort + tree_family_control_node_infomation.data_element_count) = &data_cpy;

		tree_family_control_data_sort_package.object = data_package_sort;
		tree_family_control_data_sort_package.len = tree_family_control_node_infomation.data_element_count + 1;
		tree_family_control_data_sort_package.mem_len = tree->info.mem_size_key;

		sort_algorithm_control(sort_algorithm_control_convert_type_to_func_addr(TREE_FAMILY_CFG_SORT_ALGORITHM_TYPE),
							   tree_family_control_data_sort_package,						/* Sort the address of the data in the data package by the data's key */
							   tree_family_node_control_compare_greater);
	}
}

/**
 * @brief This function will delete the data of the node,and return the data's address.
 *
 * @param void
 *
 * @return void
 */

void *tree_family_node_control_del_data(struct tree_family_s *tree,
										struct tree_family_chain_node_s *node,
										container_size_t id)
{
	assert(node);

	if (DATA_OPERATOR_IS_DATA_FAR_RIGHT(id)) {				/* Get the data far right */
		id = tree->info.degree - 1;
		while (0 < id &&
			   NULL == *((void **)node->data + id)) {
			id--;
		}
	}

	void *data_del = *((void **)node->data + id);

	for (size_t id_link = id; id_link < tree->info.degree - 2; id_link++) {
		*((void **)node->data + id_link) = *((void **)node->data + id_link + 1);
	}

	*((void **)node->data + tree->info.degree - 2) = NULL;

	return data_del;
}

/**
 * @brief This function will return the type of the node.
 *
 * @param void
 *
 * @return void
 */

container_size_t tree_family_node_control_get_node_type(struct tree_family_s *tree,
														struct tree_family_chain_node_s *node)
{
	assert(tree);
	assert(node);

	tree->switch_control(tree);

	void *data_node = node->data;

	container_size_t count_have_data = 0;

	for (size_t cnt = 0; cnt < tree_family_control_node_infomation.data_element_count; cnt++) {
		if (NULL != *((void **)data_node + cnt)) {
			count_have_data++;
		}
	}

	return count_have_data;
}

/**
 * @brief This function will initialize the tree node's link struct.
 *
 * @param void
 *
 * @return void
 */

void *tree_family_node_control_init_link(struct tree_family_s *tree)
{
	struct tree_family_chain_node_data_content_s
		*block_link_allocated = tree->allocator_ctrl->allocate(tree->allocator, 1,
															   tree_family_control_node_infomation.link_mem_len);

	return block_link_allocated;
}

/**
 * @brief This function will destroy the link.
 *
 * @param void
 *
 * @return void
 */

void tree_family_node_control_destroy_link(struct tree_family_s *tree,
										   void **link)
{
	assert(tree);
	assert(link);

	tree->allocator_ctrl->deallocate(tree->allocator, *link, 1);

	*link = NULL;
}

/**
 * @brief This function will return the family member of the node.
 *
 * @param tree the pointer to the tree
 * @param node the pointer to the node
 * @param id the id member that the parent is 0,children are greater than 0
 *
 * @return void
 */

void *tree_family_node_control_get_family_member(struct tree_family_s *tree,
												 struct tree_family_chain_node_s *node,
												 container_size_t id)
{
	assert(tree);
	assert(node);

	tree->switch_control(tree);

	void **link_node = *((void **)node + 1);

	if (LINK_OPERATOR_IS_CHILD_FAR_RIGHT(id)) {
		container_size_t id_far_right = tree->info.degree;
		while (2 < id_far_right &&
			   NULL == *((void **)link_node + id_far_right)) {
			id_far_right--;
		}

		return *((void **)link_node + id_far_right);
	}

	return *(link_node + id);
}

/**
 * @brief This function will get the node's available brother node.
 *
 * @param tree the pointer to the tree struct pointer
 * @param node the pointer to node
 *
 * @return the address of the node's available brother node
 */

void *tree_family_node_control_get_neighbour(struct tree_family_s *tree,
											 struct tree_family_chain_node_s *node,
											 struct tree_family_chain_node_s *parent,
											 container_size_t relation_with_parent)
{
	assert(tree);
	assert(node);

	if (NULL == parent &&
		NULL == (parent = *((void **)node->link))) {
		goto FAIL;
	}

	if (LINK_OPERATOR_CODE_PARENT == relation_with_parent &&
		LINK_OPERATOR_CODE_PARENT == (relation_with_parent = 								/* Get the relation id with parent */
									  tree_family_node_control_get_relation_with_parent(tree, node, parent))) {
		goto FAIL;
	} else if (LINK_OPERATOR_CODE_CHILD_FAR_LEFT == relation_with_parent) {
		return *((void **)parent->link + LINK_OPERATOR_CODE_CHILD_FAR_LEFT + 1);
	} else if (LINK_OPERATOR_CODE_CHILD_FAR_RIGHT == relation_with_parent) {
		return *((void **)parent->link + tree->info.degree);
	}

	container_size_t
		minimum = tree->info.minimum_key,
		type_node = 0,
		location = 0;

	const int offset[2] = { 1,-1 };															/* Prefer the left one */

	void *neignbour[2] = {
		*((void **)parent->link + relation_with_parent + offset[0]) ,
		*((void **)parent->link + relation_with_parent + offset[1]) };

	for (size_t side = 0; side < 2; side++) {
		if (NULL != neignbour[side] &&
			minimum <= (type_node = tree_family_node_control_get_node_type(tree, neignbour[side]))) {
			location = relation_with_parent + offset[side];
			minimum = type_node;
		}
	}

	if (0 >= location) {
	FAIL:
		return NULL;
	}

	return *((void **)parent->link + location);
}

/**
 * @brief This function will set the child of the node,and return the link's address.
 *
 * @param void
 *
 * @return void
 */

void *tree_family_node_control_set_child(struct tree_family_s *tree,
										 struct tree_family_chain_node_s *node,
										 struct tree_family_chain_node_s *family_member,
										 container_size_t id)
{
	assert(tree);
	assert(node);

	tree->switch_control(tree);

	if (NULL == family_member ||
		LINK_OPERATOR_IS_PARENT(id)) {
		goto EXIT;
	}

	if (LINK_OPERATOR_IS_CHILD_FAR_RIGHT(id)) {
		if (NULL != *((void **)node->link + (id = 1))) {								/* If the first one is NULL */
			while (tree->info.degree > id++ &&
				   NULL != *((void **)node->link + id)) {
			}
		}
	} else if (LINK_OPERATOR_IS_CHILD_FAR_LEFT(id)) {
		if (NULL != *((void **)node->link + id)) {
			if (NULL == *((void **)node->link + (id = tree->info.degree))) {			/* Have enough space for the family member */
				while (1 < --id &&
					   NULL != *((void **)node->link + id)) {
					*((void **)node->link + id + 1) = *((void **)node->link + id);
				}
			}
		}
	}

	*((void **)family_member->link + LINK_OPERATOR_CODE_PARENT) = node;
	*((void **)node->link + id) = family_member;

EXIT:

	return family_member;
}

/**
 * @brief This function will delete the data of the node,and return the data's address.
 *
 * @param void
 *
 * @return void
 */

void *tree_family_node_control_del_family_member(struct tree_family_s *tree,
												 struct tree_family_chain_node_s *node,
												 container_size_t id)
{
	assert(tree);
	assert(node);

	void *family_member_del = NULL;

	if (LINK_OPERATOR_IS_CHILD_FAR_RIGHT(id)) {										/* Get the child far right */
		id = tree->info.degree;
		while (1 < id &&
			   NULL == *((void **)node->link + id)) {
			id--;
		}
	}

	family_member_del = *((void **)node->link + id);

	for (size_t id_link = (LINK_OPERATOR_IS_PARENT(id)) ? tree->info.degree : id; 		/* Sort the child member */
		 id_link < tree->info.degree; id_link++) {
		*((void **)node->link + id_link) = *((void **)node->link + id_link + 1);
	}

	*((void **)node->link + tree->info.degree) = NULL;

	return family_member_del;
}

/**
 * @brief This function will return if one of the parent's left child is node.
 *
 * @param void
 *
 * @return void
 */

bool tree_family_node_control_get_if_left_child(struct tree_family_s *tree,
												struct tree_family_chain_node_s *node,
												struct tree_family_chain_node_s *parent)
{
	assert(tree);
	assert(node);
	assert(parent);

	if (NULL == parent &&
		NULL == (parent = *((void **)node->link))) {
		return false;
	}

	container_size_t
		link_id_far_left = 1,
		link_id_far_right = tree_family_node_control_get_node_type(tree, parent) + 1;

	while (link_id_far_right > link_id_far_left &&
		   node != *((void **)parent->link + link_id_far_left)) {
		link_id_far_left++;
	}

	if (link_id_far_right > link_id_far_left) {
		return true;
	}

	return false;
}

/**
 * @brief This function will return the type of the node.
 *
 * @param void
 *
 * @return void
 */

bool tree_family_node_control_get_if_right_child(struct tree_family_s *tree,
												 struct tree_family_chain_node_s *node,
												 struct tree_family_chain_node_s *parent)
{
	assert(tree);
	assert(node);

	if (NULL == parent &&
		NULL == (parent = *((void **)node->link))) {
		return false;
	}

	container_size_t
		link_id_far_left = 1,
		link_id_far_right = tree_family_node_control_get_node_type(tree, parent) + 1;

	while (link_id_far_left < link_id_far_right &&
		   node != *((void **)parent->link + link_id_far_right)) {
		link_id_far_right--;
	}

	if (link_id_far_left < link_id_far_right) {
		return true;
	}

	return false;
}

/**
 * @brief This function will return the type of the node.
 *
 * @param void
 *
 * @return void
 */

container_size_t
tree_family_node_control_get_relation_with_parent(struct tree_family_s *tree,
												  struct tree_family_chain_node_s *node,
												  struct tree_family_chain_node_s *parent)
{
	assert(tree);
	assert(node);

	if ((NULL == parent &&
		 NULL == (parent = *((void **)node->link))) ||
		node == parent) {
		goto FAIL;
	}

	for (size_t id = 1; id <= tree->info.degree + 1; id++) {
		if (node == *((void **)parent->link + id)) {
			return id;
		}
	}

FAIL:

	return LINK_OPERATOR_CODE_PARENT;
}

/**
 * @brief This function will return the type of the node.
 *
 * @param void
 *
 * @return void
 */

bool tree_family_node_control_get_if_leaf(struct tree_family_s *tree,
										  struct tree_family_chain_node_s *node)
{
	assert(node);

	tree->switch_control(tree);

	if (NULL == node) {
		return false;
	}

	void
		**link_node = node->link;

	container_size_t count_have_brother = 0;

	for (size_t cnt = 1; cnt < tree_family_control_node_infomation.link_element_count; cnt++) {
		if (NULL != *(link_node + cnt)) {
			count_have_brother++;
		}
	}

	if (0 < count_have_brother) {
		return false;
	} else {
		return true;
	}
}

/**
* @brief This function will compare if the left-hand-side greater than the right-hand-side.
*
* @param lhs the pointer to the left-hand-side value.
* @param rhs the pointer to the right-hand-side value.
*
* @return if left-hand-side greater than the right-hand-side
*	- true	yes
*	- false	no
*/

static inline void *tree_family_sort_algorithm_control_get_data(void *object,
																container_size_t loc)
{
	assert(object);

	return **((char ***)object + loc);
}

/**
* @brief This function will compare if the left-hand-side greater than the right-hand-side.
*
* @param lhs the pointer to the left-hand-side value.
* @param rhs the pointer to the right-hand-side value.
*
* @return if left-hand-side greater than the right-hand-side
*	- true	yes
*	- false	no
*/

static inline void tree_family_sort_algorithm_control_swap_data(void *object,
																container_size_t lhs,
																container_size_t rhs)
{
	assert(object);

	ALGORITHM_SWAP((size_t)(**((char ***)object + lhs)), (size_t)(**((char ***)object + rhs)));
}

/**
* @brief This function will compare if the left-hand-side greater than the right-hand-side.
*
* @param lhs the pointer to the left-hand-side value.
* @param rhs the pointer to the right-hand-side value.
*
* @return if left-hand-side greater than the right-hand-side
*	- true	yes
*	- false	no
*/

bool tree_family_node_control_compare_greater(void *lhs, void *rhs,
											  container_size_t len)
{
	if (NULL == lhs) {						/* Regard NULL as the greatest value */
		return true;
	} else if (NULL == rhs) {
		return false;
	}

	for (size_t cnt = 1; cnt <= len; cnt++) {
		if (*((char *)lhs + len - cnt) > *((char *)rhs + len - cnt)) {
			return true;
		}
	}

	return false;
}

/**
 * @brief This function will destroy tree node struct and free the space.
 *
 * @param tree the pointer to the tree struct pointer
 * @param node the pointer to the tree node struct pointer
 *
 * @return NONE
 */

void tree_family_control_preorder_traversal(struct tree_family_s *tree,
											struct tree_family_chain_node_s *node,
											tree_family_traversal_operator_t *operator)
{
	assert(tree);

	tree->switch_control(tree);

	if (NULL == node) {
		return;
	}

	void **link = node->link;

	operator(tree, node, tree_family_control_node_infomation.data_element_count);

	for (size_t cnt = 1; cnt < tree_family_control_node_infomation.link_element_count; cnt++) {
		tree_family_control_preorder_traversal(tree, *(link + cnt), operator);
	}
}

/**
 * @brief This function will destroy tree node struct and free the space.
 *
 * @param tree the pointer to the tree struct pointer
 * @param node the pointer to the tree node struct pointer
 *
 * @return NONE
 */

void tree_family_control_inorder_traversal(struct tree_family_s *tree,
										   struct tree_family_chain_node_s *node,
										   tree_family_traversal_operator_t *operator)
{
	assert(tree);

	tree->switch_control(tree);

	if (NULL == node) {
		return;
	}

	void **link = node->link;

	tree_family_control_inorder_traversal(tree, *(link + 1), operator);

	operator(tree, node, tree_family_control_node_infomation.data_element_count);

	for (size_t cnt = 2; cnt < tree_family_control_node_infomation.link_element_count; cnt++) {
		tree_family_control_inorder_traversal(tree, *(link + cnt), operator);
	}
}

/**
 * @brief This function will destroy tree node struct and free the space.
 *
 * @param tree the pointer to the tree struct pointer
 * @param node the pointer to the tree node struct pointer
 *
 * @return NONE
 */

void tree_family_control_posorder_traversal(struct tree_family_s *tree,
											struct tree_family_chain_node_s *node,
											tree_family_traversal_operator_t *operator)
{
	assert(tree);

	tree->switch_control(tree);

	if (NULL == node) {
		return;
	}

	void **link = node->link;

	for (size_t cnt = 1; cnt < tree_family_control_node_infomation.link_element_count; cnt++) {
		tree_family_control_posorder_traversal(tree, *(link + cnt), operator);
	}

	operator(tree, node, tree_family_control_node_infomation.data_element_count);
}

/**
 * @brief This function will get the node's precursor node.
 *
 * @param tree the pointer to the tree struct pointer
 * @param node the pointer to node
 *
 * @return the address of the precursor node
 */

tree_family_get_precursor_and_successor_return_st
tree_family_control_get_precursor(struct tree_family_s *tree,
								  struct tree_family_chain_node_s *node,
								  container_size_t location)
{
	assert(tree);
	assert(node);

	tree->switch_control(tree);

	container_size_t
		id_parent = 0,
		id_far_left = location + 1,
		id_far_right = location + 2;

	tree_family_get_precursor_and_successor_return_st
		get_precursor_successor_return = { 0 };
	struct tree_family_chain_node_s
		*node_current = tree_family_node_control_get_family_member(tree, node, id_far_left);						/* Get the node's left child */

	#if (TREE_FAMILY_CFG_DEBUG_EN)

	printf("\"%s\"'s ", (char *)*((void **)node->data + location));

	#endif // (TREE_FAMILY_CFG_DEBUG_EN)

	if (NULL != node_current) {																						/* If the node's left child is valid */
		while (NULL != (node = tree_family_node_control_get_family_member(tree,										/* Get the node_current's right child,then assign to the node */
																		  node_current,
																		  LINK_OPERATOR_CODE_CHILD_FAR_RIGHT))) {
			node_current = node;																					/* Assign the node to the node_current */
		}

		if (NULL != node_current) {																					/* It must be the leaf node,and get the far right data of the node */
			if (2 < tree->info.degree) {
				id_far_right = tree_family_node_control_get_node_type(tree, node_current);
				while (0 < id_far_right &&
					   NULL == *((void **)node_current->data + id_far_right)) {
					id_far_right--;
				}

				goto EXIT;
			}
		}
	} else {
		if (1 < tree_family_node_control_get_node_type(tree, node) &&												/* If the node is multi-node */
			2 <= id_far_left) {
			node_current = node;

			id_far_right = id_far_left - 2;

			goto EXIT;
		} else {
			node_current = tree_family_node_control_get_family_member(tree, node, id_parent);							/* Get the node's parent,then assign to the node_current */

			while (NULL != node_current &&
				   !tree_family_node_control_get_if_right_child(tree, node, node_current)) {
				node = node_current;																					/* Set the node as his own parent */
				node_current = tree_family_node_control_get_family_member(tree, node, id_parent);						/* Get the node's parent,then assign to the node_current */
			}

			if (NULL != node) {
				if (2 < tree->info.degree) {
					id_far_right = tree_family_node_control_get_relation_with_parent(tree, node, node_current) - 2;

					goto EXIT;
				}
			}
		}
	}

	id_far_right = 0;

EXIT:

	if (NULL != node_current) {
		get_precursor_successor_return.node = node_current;
		get_precursor_successor_return.location = id_far_right;
		get_precursor_successor_return.data = *((void **)node_current->data + id_far_right);
	}

	#if (TREE_FAMILY_CFG_DEBUG_EN)

	printf("precursor is %p's No.%d:\"%s\"-%d \r\n",
		   get_precursor_successor_return.node,
		   get_precursor_successor_return.location,
		   (char *)get_precursor_successor_return.data,
		   (size_t)TREE_FAMILY_DEBUG_OPERATOR_GET_KEY_FROM_DATA(get_precursor_successor_return.data) - '0');

	#endif // (TREE_FAMILY_CFG_DEBUG_EN)

	return get_precursor_successor_return;
}

/**
 * @brief This function will get the node's successor node.
 *
 * @param tree the pointer to the tree struct pointer
 * @param node the pointer to node
 *
 * @return the address of the successor node
 */

tree_family_get_precursor_and_successor_return_st
tree_family_control_get_successor(struct tree_family_s *tree,
								  struct tree_family_chain_node_s *node,
								  container_size_t location)
{
	assert(tree);
	assert(node);

	tree->switch_control(tree);

	container_size_t
		id_parent = 0,
		id_far_left = location + 1,
		id_far_right = location + 2;

	tree_family_get_precursor_and_successor_return_st
		get_precursor_successor_return = { 0 };
	struct tree_family_chain_node_s
		*node_current = tree_family_node_control_get_family_member(tree, node, id_far_right);						/* Get the node's right child */

	#if (TREE_FAMILY_CFG_DEBUG_EN)

	printf("\"%s\"'s ", (char *)*((void **)node->data + location));

	#endif // (TREE_FAMILY_CFG_DEBUG_EN)

	if (NULL != node_current) {																						/* If the node's right child is valid */
		while (NULL != (node = tree_family_node_control_get_family_member(tree, node_current, LINK_OPERATOR_CODE_CHILD_FAR_LEFT))) {		/* Get the node_current's left child,then assign to the node */
			node_current = node;																					/* Assign the node to the node_current */
		}
	} else {
		if (1 < tree_family_node_control_get_node_type(tree, node)) {												/* If the node is multi-node */
			node_current = node;

			id_far_left = id_far_right - 1;

			goto EXIT;
		} else {
			node_current = tree_family_node_control_get_family_member(tree, node, id_parent);						/* Get the node's parent,then assign to the node_current */

			while (NULL != node_current &&
				   !tree_family_node_control_get_if_left_child(tree, node, node_current)) {
				node = node_current;																				/* Set the node as his own parent */
				node_current = tree_family_node_control_get_family_member(tree, node, id_parent);					/* Get the node's parent,then assign to the node_current */
			}

			if (NULL != node) {
				id_far_left = tree_family_node_control_get_relation_with_parent(tree, node, node_current) - 2 + 1;

				goto EXIT;
			}
		}
	}

	id_far_left = 0;

EXIT:

	if (NULL != node_current) {
		get_precursor_successor_return.node = node_current;
		get_precursor_successor_return.location = id_far_left;
		get_precursor_successor_return.data = *((void **)node_current->data + id_far_left);
	}

	#if (TREE_FAMILY_CFG_DEBUG_EN)

	printf("successor is %p's No.%d:\"%s\"-%d \r\n",
		   get_precursor_successor_return.node,
		   get_precursor_successor_return.location,
		   (char *)get_precursor_successor_return.data,
		   (size_t)TREE_FAMILY_DEBUG_OPERATOR_GET_KEY_FROM_DATA(get_precursor_successor_return.data) - '0');

	#endif // (TREE_FAMILY_CFG_DEBUG_EN)

	return get_precursor_successor_return;
}

/**
* @brief This function will print all the node when traversal.
*
* @param void
*
* @return void
*/

void tree_family_control_traversal_printer(struct tree_family_s *tree,
										   void *node,
										   container_size_t data_element_count)
{
	printf("node:%p data: ", node);

	char ***data = node;

	for (size_t id_data = DATA_OPERATOR_CODE_DATA_FAR_LEFT; id_data < data_element_count; id_data++) {
		if (NULL != *(*data + id_data)) {
			if (DATA_OPERATOR_CODE_DATA_FAR_LEFT < id_data) {
				printf("\r\n");
			}
			printf("key:\"%s\"-%d content:\"%s\" ", *(*data + id_data), *(*(*data + id_data)) - '0', (char *)((size_t)(*(*data + id_data)) + tree->info.mem_size_key));
		}
	}

	printf("data_addr:%p link_addr:%p \r\n",
		   *((void **)node + 0), *((void **)node + 1));
}

/**
* @brief This function will destroy all the node when traversal.
*
* @param void
*
* @return void
*/

void tree_family_control_destroy_posorder_traversal_operator(struct tree_family_s *tree,
															 void *node,
															 container_size_t data_element_count)
{
	printf("will destroy ");

	tree_family_control_traversal_printer(tree, node, data_element_count);

	//if (2 <= tree_family_node_control_get_node_type(tree, node)) {		/* Not binary node */
	//
	//}

	//tree_family_control_destroy_node(tree, &node);
}

/**
* @brief This function will replace the switch_control(tree) before enter control sandbox.
*
* @param void
*
* @return void
*/

void tree_family_control_switch_control_in_sandbox(struct tree_family_s *tree)
{
}

/**
* @brief This function will callback the handler that container has no elements when the container temp to insert.
*
* @param NODE
*
* @return NONE
*/

void tree_family_control_configuration_exception_default_empty_callback(void)
{
}

/**
 * @brief This function will callback the handler that container has no elements when the container temp to erase.
 *
 * @param NODE
 *
 * @return NONE
 */

void tree_family_control_configuration_exception_default_full_callback(void)
{
}