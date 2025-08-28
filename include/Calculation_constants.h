/*! \file */

#ifndef CALCULATION_CONSTANTS_H
#define CALCULATION_CONSTANTS_H

#include "Common.h"

/*!
 *The value of eps (acceptable error) if user hasn't entered any
 */
ld const default_eps = 1E-9;

/*!
 *Sets the value of eps (acceptable error)
 
 *\param[in] new_eps A new value for the eps
 */
void set_eps(ld const new_eps);

/*!
 *Checks whether long double value equal 0 or not, taking error into account

 *\param[in] x The number to check for equality to 0

 *\return returns 1 if number considered to be 0 and 0 otherwhise
 */
int is_nil(ld const x);

#endif
