/*! \file */

#ifndef COEFFICIENT_SCANER_H
#define COEFFICIENT_SCANER_H

#include "Common.h"

/*!
 *Forms Square_equation object by coefficients from input stream

 *\param[out] eq_ptr A pointer to square equation that is destination for scanned equation
 *\param[in] config_ptr A pointer to config object that determines behaviour of program

 *\return Return User_error object containing information about error occured (possible no error)
 */
[[nodiscard]] User_error scan_square_coefficients(Square_equation *eq_ptr, Config const *config_ptr);

#endif
