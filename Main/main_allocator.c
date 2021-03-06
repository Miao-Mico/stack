#include "main_cfg.h"

#define MAIN_ALLOCATOR_CFG_ALLOCATOR_COMMON_EN	1u

#if (MAIN_ALLOCATOR_CFG_ALLOCATOR_COMMON_EN)

#define ALLOCATOR_TYPE	ALLOCATOR_COMMON

#endif // (MAIN_ALLOCATOR_CFG_ALLOCATOR_COMMON_EN)

struct allocator_control_s
	*allocator_control_ptr = NULL;

void
*allocator = { NULL };

void
*block = NULL;

void main_allocator(void)
{
	printf("\r\n------------------------+ allocator demo start +------------------------\r\n");

	allocator_control_ptr = allocator_control_convert_type_to_func_addr_table(ALLOCATOR_TYPE);	/* Variables pointer to	the function address table of
																								specified container type		*/

	printf("\r\nallocator.init start \r\n");
	allocator_control_ptr->configuration.init(&allocator, NULL);

	printf("\r\nallocator.exception start \r\n");
	allocator_control_ptr->configuration.exception(&allocator, NULL);

	printf("\r\nallocator.allocate start \r\n");
	block = allocator_control_ptr->allocate(allocator, 1, 1);
	printf("allocator.allocate:block %p \r\n", block);

	printf("\r\nallocator.deallocate start \r\n");
	allocator_control_ptr->deallocate(allocator, block, 1);

	printf("\r\nallocator.destroy start \r\n");
	allocator_control_ptr->configuration.destroy(&allocator);

	printf("\r\n------------------------+ allocator demo end +------------------------\r\n");

	return;
}