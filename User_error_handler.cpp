#include "User_error_handler.h"

int handle_user_error(User_error const *const error)
{
    assert(error and error->valid);

    switch (error->code)
    {
        case NO_ERROR:
            return 0;

        case NORMAL_TERMINATION:
            return 1;

        case UNKNOWN_OPTION:
            assert(error->data);

            printf("\"%s\" option is unknown", error->data[0]);
            return 1;

        case INCORRECT_OPTION_ARGUMENT:
            assert(error->data);

            printf("\"%s\" argument of option \"%s\" is incorrect in this place", error->data[1], error->data[0]);
            return 1;

        case INVALID_ERROR:
        default:
            [[fallthrough]]
            assert(0);

            return 1;
    }
}
