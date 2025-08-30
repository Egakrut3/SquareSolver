/*! \file */

#include "Coefficient_scaner.h"
#include <math.h>

/*!
 *Forms Square_equation object by coefficients from input stream

 *\param[out] eq_ptr A pointer to square equation to be scanned
 *\param[in] config_ptr A pointer to config object that determines behaviour of program

 *\return Return User_error object containing information about error occured (possible no error)
 */
User_error scan_square_coefficients(Square_equation *const eq_ptr, Config const *const config_ptr) //TODO - possible make infinite loop when stdin
{
    assert(eq_ptr and config_ptr);

    int const check_input = fscanf(config_ptr->input_stream, "%LG %LG %LG", &eq_ptr->a, &eq_ptr->b, &eq_ptr->c);
    if (check_input == 3 or isfinite(eq_ptr->a) or isfinite(eq_ptr->b) or isfinite(eq_ptr->c))
    {
        return construct_User_error(NO_ERROR, 0);
    }

    return construct_User_error(INVALID_INPUT, 1, "Must contain 3 finite floating-point numbers");
}
