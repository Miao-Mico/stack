/*
 *********************************************************************************************************
 *                                               MODULE
 *
 * Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
 *               through use of the definition module present pre-processor macro definition.
 *********************************************************************************************************
 */

#ifndef __RANDOM_ACCESS_ITERATOR_H
#define __RANDOM_ACCESS_ITERATOR_H

/*
 *********************************************************************************************************
 *                                            INCLUDE FILES
 *********************************************************************************************************
 */

#include "access_iterator_def.h"

/*
 *********************************************************************************************************
 *									            DEFINES
 *********************************************************************************************************
 */

/*
 *********************************************************************************************************
 *									           DATA TYPES
 *********************************************************************************************************
 */

/**
 * @brief This variable is the random access iterator structure.
 */

struct random_access_iterator_s {
	struct access_iterator_advance_unit_s advance;

	struct access_iterator_access_unit_s distance;

	struct access_iterator_access_unit_s next;

	struct access_iterator_access_unit_s prev;

	struct access_iterator_access_unit_s at;

	struct access_iterator_access_unit_s front;

	struct access_iterator_access_unit_s back;
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
 * @brief This variable is the random access iterator structure.
 */

extern struct random_access_iterator_s random_access_iterator;

/*
 *********************************************************************************************************
 *                                             MODULE END
 *********************************************************************************************************
 */

#endif // !__RANDOM_ACCESS_ITERATOR_H