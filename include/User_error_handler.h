/*! file */

#ifndef USER_ERROR_HANDLER_H
#define USER_ERROR_HANDLER_H

#include "Common.h"

/*!
 *Handles an User_error object

 *\param[in] error A pointer to an error to be handled

 *\return Returns 1 if the program must be finished and 0 otherwise
 */
int handle_user_error(User_error const* const error);

#endif
