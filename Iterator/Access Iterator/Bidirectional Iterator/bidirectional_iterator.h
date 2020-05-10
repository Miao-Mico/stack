/*
 *********************************************************************************************************
 *                                               MODULE
 *
 * Note(s) : (1) This definition header file is protected from multiple pre-processor inclusion
 *               through use of the definition module present pre-processor macro definition.
 *********************************************************************************************************
 */

#ifndef __BIDIRECTIONAL_ITERATOR_H
#define __BIDIRECTIONAL_ITERATOR_H

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
 * @brief This type is the bidirectional iterator structure.
 */

struct bidirectional_iterator_s {
	void *(*advance)(struct access_iterator_s *iterator,
					 int step);

	size_t(*distance)(struct access_iterator_s *iterator);

	void *(*next)(struct access_iterator_s *iterator);

	void *(*prev)(struct access_iterator_s *iterator);
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
 * @brief This type is the bidirectional iterator structure.
 */

extern struct bidirectional_iterator_s bidirectional_iterator;

/*
 *********************************************************************************************************
 *                                             MODULE END
 *********************************************************************************************************
 */

#endif // !__BIDIRECTIONAL_ITERATOR_H