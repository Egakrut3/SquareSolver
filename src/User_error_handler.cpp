/*! \file */

#include "User_error_handler.h"

/*!
 *Handles an User_error object

 *\param[in] error A pointer to an error to be handled

 *\return Returns 1 if the program must be finished and 0 otherwise
 */
int8_t handle_user_error(User_error const *const error)
{
    assert(error and error->valid);

    switch (error->code)
    {
        case NO_ERROR:
            return 0;

        case NORMAL_TERMINATION:
            return 1;

        case UNKNOWN_OPTION:
            assert(error->data and error->data[0]);

            printf("\"%s\" option is unknown\n", error->data[0]);
            return 1;

        case NOT_ENOUGH_OPTION_ARGUMENTS:
            assert(error->data and error->data[0]);

            printf("\"%s\" option requires more arguments after itself\n", error->data[0]);
            return 1;

        case INCORRECT_OPTION_ARGUMENT:
            assert(error->data and error->data[0] and error->data[1]);

            printf("\"%s\" argument of option \"%s\" is incorrect in this place\n", error->data[1], error->data[0]);
            return 1;

        case INVALID_ERROR:
        default:
            assert(0);

            return 1;
    }
}
