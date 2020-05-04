/*
 *********************************************************************************************************
 *                                               MODULE
 *
 * Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
 *               through use of the definition module present pre-processor macro definition.
 *********************************************************************************************************
 */

#ifndef __DEBUG_MICRO_H
#define __DEBUG_MICRO_H

/*
 *********************************************************************************************************
 *                                            INCLUDE FILES
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *									            DEFINES
 *********************************************************************************************************
 */

/* Define			debug micro control left bracket.								                    */
#define DEBUG_MICRO_CONTROL_LEFTBRACKET                                                                 \
    (

/* Define			debug micro control expand.								                            */
#define DEBUG_MICRO_CONTROL_EXPAND(...)                                                                 \
    __VA_ARGS__

/* Define			debug micro control string.								                            */
#define DEBUG_MICRO_CONTROL_STRING(...)                                                                 \
    #__VA_ARGS__

/* Define			debug micro control field offset.								                    */
#define DEBUG_MICRO_CONTROL_FIELD(variable_address, field_type, field_offset)                           \
    *(field_type*)((char *)variable_address + (field_offset))

/* Define			debug micro control field offset.								                    */
#define DEBUG_MICRO_CONTROL_FIELD_OFFSET(type, field)                                                   \
    ((size_t)(size_t *) & (((type *)0)->field))

/* Define			debug micro control probe, if zero, the compiler will throw warnings.		        */
#define DEBUG_MICRO_CONTROL_PROBE(zero)                                                                 \
    (1u ? sizeof(char[zero]) : 0u)

/* Define			debug micro control probe value what x.		                                        */
#define DEBUG_MICRO_CONTROL_PROBE_WHAT_X(value, symbol, x)                                              \
    DEBUG_MICRO_CONTROL_PROBE(value symbol x)

/* Define			debug micro control probe not zero.		                                            */
#define DEBUG_MICRO_CONTROL_PROBE_NOT_ZERO(value)                                                       \
    DEBUG_MICRO_CONTROL_PROBE_WHAT_X(value, !=, 0)

/* Define			debug micro control probe arg max.		                                            */
#define DEBUG_MICRO_CONTROL_PROBE_ARG_MAX(max, ...)	                                                    \
    DEBUG_MICRO_CONTROL_PROBE_WHAT_X(DEBUG_MICRO_CONTROL_VA_ARGS_ARG_NUM(__VA_ARGS__), <=, max)

/* Define			debug micro control probe arg min.		                                            */
#define DEBUG_MICRO_CONTROL_PROBE_ARG_MIN(min, ...)	                                                    \
    DEBUG_MICRO_CONTROL_PROBE_WHAT_X(DEBUG_MICRO_CONTROL_VA_ARGS_ARG_NUM(__VA_ARGS__), >=, min)

/* Define			debug micro control function-like.										            */
#define DEBUG_MICRO_CONTROL_FUNCTION_LIKE(...)                                                          \
    do {                                                                                                \
        __VA_ARGS__;                                                                                    \
    } while (0)

/* Define			debug micro control get the index-th arg of the va_arg.				                */
#define DEBUG_MICRO_CONTROL_VA_ARGS_ARG(index, ...)                                                     \
    DEBUG_MICRO_CONTROL_VA_ARGS_ARG ## index DEBUG_MICRO_CONTROL_LEFTBRACKET __VA_ARGS__)

/* Define			debug micro control get the number of the va_arg, the range between 0 and 6.		*/
#define DEBUG_MICRO_CONTROL_VA_ARGS_ARG_NUM(...)                                                        \
	DEBUG_MICRO_CONTROL_VA_ARGS_ARG DEBUG_MICRO_CONTROL_LEFTBRACKET                                     \
        7, __VA_ARGS__, 6, 5, 4, 3, 2, 1, 0)

/* Define			debug micro control get the args of the va_arg from first to last.				    */
#define DEBUG_MICRO_CONTROL_VA_ARGS_ARGS_FROM(first, ...)                                               \
    DEBUG_MICRO_CONTROL_VA_ARGS_ARGS_FROM ## first DEBUG_MICRO_CONTROL_LEFTBRACKET __VA_ARGS__)

/* Define			debug micro control get the arg1 of the va_arg.							            */
#define DEBUG_MICRO_CONTROL_VA_ARGS_ARG1(arg1, ...)                                                     \
    arg1

/* Define			debug micro control get the arg2 of the va_arg.							            */
#define DEBUG_MICRO_CONTROL_VA_ARGS_ARG2(arg1, arg2, ...)                                               \
    arg2

/* Define			debug micro control get the arg3 of the va_arg.							            */
#define DEBUG_MICRO_CONTROL_VA_ARGS_ARG3(arg1, arg2, arg3, ...)                                         \
    arg3

/* Define			debug micro control get the arg4 of the va_arg.							            */
#define DEBUG_MICRO_CONTROL_VA_ARGS_ARG4(arg1, arg2, arg3, arg4, ...)                                   \
    arg4

/* Define			debug micro control get the arg5 of the va_arg.							            */
#define DEBUG_MICRO_CONTROL_VA_ARGS_ARG5(arg1, arg2, arg3, arg4, arg5, ...)                             \
    arg5

/* Define			debug micro control get the arg6 of the va_arg.							            */
#define DEBUG_MICRO_CONTROL_VA_ARGS_ARG6(arg1, arg2, arg3, arg4, arg5, arg6, ...)                       \
    arg6

/* Define			debug micro control get the arg7 of the va_arg.							            */
#define DEBUG_MICRO_CONTROL_VA_ARGS_ARG7(arg1, arg2, arg3, arg4, arg5, arg6, arg7, ...)                 \
    arg7

/* Define			debug micro control get the args of the va_arg from 1 to last.				        */
#define DEBUG_MICRO_CONTROL_VA_ARGS_ARGS_FROM1(...)                                                     \
    __VA_ARGS__

/* Define			debug micro control get the args of the va_arg from 2 to last.				        */
#define DEBUG_MICRO_CONTROL_VA_ARGS_ARGS_FROM2(arg1, ...)                                               \
    __VA_ARGS__

/* Define			debug micro control get the args of the va_arg from 3 to last.				        */
#define DEBUG_MICRO_CONTROL_VA_ARGS_ARGS_FROM3(arg1, arg2, ...)                                         \
    __VA_ARGS__

/* Define			debug micro control get the args of the va_arg from 4 to last.				        */
#define DEBUG_MICRO_CONTROL_VA_ARGS_ARGS_FROM4(arg1, arg2, arg3, ...)                                   \
    __VA_ARGS__

/* Define			debug micro control get the args of the va_arg from 5 to last.				        */
#define DEBUG_MICRO_CONTROL_VA_ARGS_ARGS_FROM5(arg1, arg2, arg3, arg4, ...)                             \
    __VA_ARGS__

/* Define			debug micro control get the args of the va_arg from 6 to last.				        */
#define DEBUG_MICRO_CONTROL_VA_ARGS_ARGS_FROM6(arg1, arg2, arg3, arg4, arg5, ...)                       \
    __VA_ARGS__

/* Define			debug micro control get the args of the va_arg from 7 to last.				        */
#define DEBUG_MICRO_CONTROL_VA_ARGS_ARGS_FROM7(arg1, arg2, arg3, arg4, arg5, arg6, ...)                 \
    __VA_ARGS__

/* Define			debug micro control get the args of the va_arg from 8 to last.				        */
#define DEBUG_MICRO_CONTROL_VA_ARGS_ARGS_FROM8(arg1, arg2, arg3, arg4, arg5, arg6, arg7, ...)           \
    __VA_ARGS__

/*
 *********************************************************************************************************
 *									           DATA TYPES
 *********************************************************************************************************
 */

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

/*
 *********************************************************************************************************
 *                                             MODULE END
 *********************************************************************************************************
 */

#endif // !__DEBUG_MICRO_H