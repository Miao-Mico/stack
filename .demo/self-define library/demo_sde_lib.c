#include "demo_sde_lib.h"

void main(void)
{
#if DEMO_SDE_LIB_CFG_CFG_MICRO_EN

	main_micro();

#endif // DEMO_SDE_LIB_CFG_LIBARY_CFG_MICRO_EN

#if DEMO_SDE_LIB_CFG_CFG_LOG_EN

	main_log();

#endif // DEMO_SDE_LIB_CFG_CFG_LOG_EN

#if DEMO_SDE_LIB_CFG_CFG_ASSERT_EN

	main_assert();

#endif // DEMO_SDE_LIB_CFG_CFG_ASSERT_EN

#if DEMO_SDE_LIB_CFG_CFG_ERROR_EN

	main_error();

#endif // DEMO_SDE_LIB_CFG_CFG_ERROR_EN

	return;
}