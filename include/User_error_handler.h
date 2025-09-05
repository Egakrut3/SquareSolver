/*! \file */

#ifndef USER_ERROR_HANDLER_H
#define USER_ERROR_HANDLER_H

#include "Common.h"

/*!
 *Handles an User_error object

 *\param[in] error_ptr A pointer to an error to be handled

 *\return Returns true if the program must be finished and false otherwise
 */
bool handle_user_error(User_error const *error_ptr);

#endif
