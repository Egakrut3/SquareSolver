/*! \file */

#ifndef CALCULATION_CONSTANTS_H
#define CALCULATION_CONSTANTS_H

#include "Common.h"

/*!
 *The value of eps (acceptable error) if user hasn't entered any
 */
ld const default_eps = 1E-9;

void set_eps(ld const);

int8_t is_nil(ld const);

#endif
