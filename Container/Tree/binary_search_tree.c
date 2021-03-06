/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include "binary_search_tree.h"

#include "container_pte_def.h"

/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

#define BINARY_SEARCH_TREE_GET_EXTRA_INFO()																		\
tree_family_control_get_extra_infomation(binary_search_tree)

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
 * @brief This struct is the binary search binary_search_tree chain node link structure module.
 */

struct binary_search_tree_chain_node_link_s {
	void *parent;

	void *lchild;

	void *rchild;
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

/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/**
 * @brief This function will analysis the shared pack.
 *
 * @param void
 *
 * @return void
 */

void binary_search_tree_control_switch_control(binary_search_tree_stp binary_search_tree);

/**
 * @brief This function will control the search()'s match rule.
 *
 * @param void
 *
 * @return void
 */

container_size_t
binary_search_tree_control_search_match_rule(binary_search_tree_stp binary_search_tree,
											 struct tree_family_chain_node_s *node,
											 void *data);

/**
 * @brief This function will control the search()'s recursion rule.
 *
 * @param void
 *
 * @return void
 */

container_size_t
binary_search_tree_control_search_recursion_rule(binary_search_tree_stp binary_search_tree,
												 struct tree_family_chain_node_s **node,
												 void *data);

/**
 * @brief This function will control b_tree_control_insert()'s insert.
 *
 * @param void
 *
 * @return void
 */

void *binary_search_tree_control_insert_rule(binary_search_tree_stp binary_search_tree,
											 struct tree_family_search_node_return_s search_return,
											 void *data);

/**
 * @brief This function will control b_tree_control_delete()'s delete.
 *
 * @param void
 *
 * @return void
 */

void *binary_search_tree_control_delete_rule(binary_search_tree_stp binary_search_tree,
											 struct tree_family_search_node_return_s search_return,
											 void *data);

/*
*********************************************************************************************************
*					LOCAL GLOBAL VARIABLES & LOCAL FUNCTION PROTOTYPES INTERSECTION
*********************************************************************************************************
*/

/**
 * @brief This struct will record the binary search binary_search_tree's environment.
 */

struct tree_family_control_environment_s binary_search_tree_control_environment = {
	TREE_FAMILY_2D_NODE_TYPE,
	{
		binary_search_tree_control_search_match_rule,
		binary_search_tree_control_search_recursion_rule,
		binary_search_tree_control_insert_rule,
		binary_search_tree_control_delete_rule
	},
	{
		.degree = 2,
		.mem_size_key = 4,
		.minimum_amt_key = 1,
	}
};

/**
 * @brief This struct will record the binary search binary_search_tree's node operator.
 */

struct tree_family_node_operator_s binary_search_tree_control_node_operator = {
	binary_search_tree_control_search_match_rule,
	binary_search_tree_control_search_recursion_rule,
	binary_search_tree_control_insert_rule,
	binary_search_tree_control_delete_rule
};

/*
*********************************************************************************************************
*                                            FUNCTIONS
*********************************************************************************************************
*/

/**
 * @brief This function will initialize the binary_search_tree struct
 *
 * @param binary_search_tree the pointer to the binary_search_tree struct pointer
 * @param element_size the element memory size of the binary_search_tree struct
 * @param assign the pointer to the assign element handler of the specified data type
 * @param free the pointer to the free element handler of the specified data type
 *
 * @return NONE
 */

extern inline void
binary_search_tree_control_configuration_init(binary_search_tree_stpp binary_search_tree,
											  container_size_t key_size,
											  container_size_t element_size,
											  generic_type_element_assign_t assign,
											  generic_type_element_free_t free)
{
	assert(binary_search_tree);
	assert(0 <= element_size);

	tree_family_control_configuration_init(binary_search_tree, 
										   binary_search_tree_control_switch_control,
										   2, key_size,
										   TREE_FAMILY_RED_BLACK_TREE,
										   BINARY_SEARCH_TREE_CFG_ALLOCATOR_TYPE,
										   element_size, assign, free);
}

/**
 * @brief This function will analysis the shared pack.
 *
 * @param void
 *
 * @return void
 */

void binary_search_tree_control_switch_control(binary_search_tree_stp binary_search_tree)
{
	binary_search_tree_control_environment.extra_info 
		= *(struct tree_family_extra_infomation_s *)(&binary_search_tree->addon);

	tree_family_control_get_control(binary_search_tree_control_environment);
}

/**
 * @brief This function will control the search()'s match rule.
 *
 * @param void
 *
 * @return void
 */

container_size_t
binary_search_tree_control_search_match_rule(binary_search_tree_stp binary_search_tree,
											 struct tree_family_chain_node_s *node,
											 void *data)
{
	assert(binary_search_tree);
	assert(node);
	assert(data);

	container_size_t location = 0;

	for (; location < BINARY_SEARCH_TREE_GET_EXTRA_INFO().degree - 1; location++) {
		if (NULL != *((void **)node->data + location) &&
			compare_control_equal(data, *((void **)node->data + location), BINARY_SEARCH_TREE_GET_EXTRA_INFO().mem_size_key)) {
			goto EXIT;
		}
	}

	location = SEARCH_CODE_NO_SUCH_ELEMENT;

EXIT:

	#if (BINARY_SEARCH_TREE_CFG_DEBUG_EN)

	printf("search.match rule:node:%p Data ",
		   node);

	for (size_t cnt = 0; cnt < BINARY_SEARCH_TREE_GET_EXTRA_INFO().degree - 1; cnt++) {
		printf("No.%d:\"%s\"-%p ", cnt, (char *)*((void **)node->data + cnt), *((void **)node->data + cnt));
	}

	printf("-->match:%p location:%d\r\n", (0xff != location) ? *((void **)node->data + location) : NULL, location);

	#endif // (BINARY_SEARCH_TREE_CFG_DEBUG_EN)

	return location;
}

/**
 * @brief This function will control the search()'s recursion rule.
 *
 * @param void
 *
 * @return void
 */

container_size_t
binary_search_tree_control_search_recursion_rule(binary_search_tree_stp binary_search_tree,
												 struct tree_family_chain_node_s **node,
												 void *data)
{
	assert(binary_search_tree);
	assert(node);
	assert(*node);
	assert(data);

	container_size_t evaluation_level = LINK_OPERATOR_CODE_CHILD_FAR_LEFT;

	for (; evaluation_level < BINARY_SEARCH_TREE_GET_EXTRA_INFO().degree; evaluation_level++) {
		if ((NULL == *((void **)(*node)->data + evaluation_level - 1) ||				/* If the data of this evaluation_level is NULL,the previous would the far right one */
			(NULL != *((void **)(*node)->data + evaluation_level - 1) &&				/* If the data of this evaluation_level isn't NULL,and the data is lesser than the data of this evaluation_level */
			 compare_control_lesser(data, *((void **)(*node)->data + evaluation_level - 1),
									BINARY_SEARCH_TREE_GET_EXTRA_INFO().mem_size_key)))) {
			goto EXIT;
		}
	}

	evaluation_level = BINARY_SEARCH_TREE_GET_EXTRA_INFO().degree;												/* Assign to be the id of link far right */

EXIT:

	#if (BINARY_SEARCH_TREE_CFG_DEBUG_EN)

	printf("search.recursion rule:node:%p Link ", (*node));

	for (size_t cnt = 1; cnt <= BINARY_SEARCH_TREE_GET_EXTRA_INFO().degree; cnt++) {
		printf("No.%d:%p ", cnt, *((void **)(*node)->link + cnt));
	}

	printf("-->next:%p evaluation_level:%d\r\n", *((void **)(*node)->link + evaluation_level), evaluation_level);

	#endif // (BINARY_SEARCH_TREE_CFG_DEBUG_EN)

	*node = *((void **)(*node)->link + evaluation_level);								/* Recursion to it's child */

	return evaluation_level;
}

/**
 * @brief This function will control b_tree_control_insert()'s insert.
 *
 * @param void
 *
 * @return void
 */

void *binary_search_tree_control_insert_rule(binary_search_tree_stp binary_search_tree,
											 struct tree_family_search_node_return_s search_return,
											 void *data)
{
	assert(binary_search_tree);
	assert(data);

	struct tree_family_chain_node_s *node = tree_family_control_init_node(binary_search_tree);
	void *data_cpy = binary_search_tree->allocator_control_ptr->allocate(binary_search_tree->allocator_ptr, 1, binary_search_tree->info.mem_size);

	if (NULL == data_cpy) {
		return NULL;
	}

	memcpy(data_cpy, data, binary_search_tree->info.mem_size);

	*((void **)node->data) = data_cpy;												/* Copy the data and assign to data */
	*((void **)node->link) = search_return.node_prev;								/* Link the search parent to be node's parent */

	*((void **)search_return.node_prev->link + search_return.estimate) = node;		/* Link the node to be the search parent's child,
																						the estimate would be two value [1 or 2] */
	return node;
}

/**
 * @brief This function will control b_tree_control_delete()'s delete.
 *
 * @param void
 *
 * @return void
 */

void *binary_search_tree_control_delete_rule(binary_search_tree_stp binary_search_tree,
											 struct tree_family_search_node_return_s search_return,
											 void *data)
{
	assert(binary_search_tree);
	assert(data);

	struct tree_family_chain_node_s
		*node = search_return.node,
		*parent = search_return.node_prev;

	container_size_t relation = LINK_OPERATOR_CODE_PARENT;											/* Record the relation id with their parent */

	while (NULL != node) {
		if (tree_family_node_control_get_if_leaf(binary_search_tree, node)) {										/* Delete the node that is a leaf node */
			if (NULL == parent) {
				binary_search_tree->element_ptr = NULL;
			} else {
				relation = tree_family_node_control_get_relation_with_parent(binary_search_tree, node, parent);

				if (LINK_OPERATOR_CODE_PARENT != relation) {
					*((void **)parent->link + relation) = NULL;
				}
			}

			goto EXIT;

			//tree_family_control_destroy_node(binary_search_tree, &node);
		} else if (NULL != *((void **)node->link + 1) &&											/* If it have two child linked */
				   NULL != *((void **)node->link + 2)) {
			tree_family_get_precursor_and_successor_return_st
				get_precursor_successor_return = tree_family_control_get_precursor(binary_search_tree, node, 0);

			if (NULL == get_precursor_successor_return.node &&										/* If the precursor is NULL,get the successor */
				(get_precursor_successor_return = tree_family_control_get_successor(binary_search_tree, node, 0),
				 NULL == get_precursor_successor_return.node)) {
				goto FAIL;
			}

			MODIFY_SEQUENCE_CONTROL_SWAP((size_t)(*((void **)get_precursor_successor_return.node->data +
									  get_precursor_successor_return.location)),
									  (size_t)(*((void **)node->data + search_return.location)));	/* Swap the data of the node with it's precursor or the successor */

			node = get_precursor_successor_return.node;
			parent = *((void **)node->link);
		} else {																					/* If it have only one child linked */
			struct tree_family_chain_node_s *node_cut = NULL;

			if (NULL != *((void **)node->link + 1)) {
				relation = 1;
			} else if (NULL != *((void **)node->link + 2)) {
				relation = 2;
			}

			node_cut = *((void **)node->link + relation);											/* Cut the node's child */

			if (NULL == parent &&
				NULL == (parent = binary_search_tree->element_ptr = node_cut, node_cut = NULL)) {						/* If it's parent is NULL,it would be the root */
				goto FAIL;
			} else {
				*((void **)parent->link + LINK_OPERATOR_CODE_PARENT) = node_cut;					/* Link the node into parent to be one of it's child */
			}

			goto EXIT;
		}
	}

EXIT:

	return node;

FAIL:

	return NULL;
}

/**
 * @brief This function will control b_tree_control_delete()'s delete.
 *
 * @param void
 *
 * @return void
 */

extern inline struct tree_family_control_environment_s
binary_search_tree_control_get_environment(void)
{
	return binary_search_tree_control_environment;
}