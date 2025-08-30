/*! \file */

#include "User_error_handler.h"

/*!
 *Handles an User_error object

 *\param[in] error_ptr A pointer to an error to be handled

 *\return Returns true if the program must be finished and false otherwise
 */
bool handle_user_error(User_error const *const error_ptr)
{
    assert(error_ptr and error_ptr->valid);

    switch (error_ptr->code)
    {
        case NO_ERROR:
            return false;

        case UNKNOWN_OPTION:
            assert(error_ptr->data and error_ptr->data[0]);

            printf("\"%s\" option is unknown\n", error_ptr->data[0]);
            return true;

        case NOT_ENOUGH_OPTION_ARGUMENTS:
            assert(error_ptr->data and error_ptr->data[0]);

            printf("\"%s\" option requires more arguments after itself\n", error_ptr->data[0]);
            return true;

        case INVALID_OPTION_ARGUMENT:
            assert(error_ptr->data and error_ptr->data[0] and error_ptr->data[1] and error_ptr->data[2]);

            printf("In option \"%s\" argument \"%s\": %s\n",
                   error_ptr->data[0], error_ptr->data[1], error_ptr->data[2]);
            return true;

        case INVALID_INPUT:
            assert(error_ptr->data and error_ptr->data[0]);

            printf("You've entered invalid values: %s", error_ptr->data[0]);
            return true;

        default:
            assert(0);

            return true;
    }
}
