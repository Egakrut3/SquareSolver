/*! \file */

#ifndef SOLVER_H
#define SOLVER_H

#include "Common.h"

/*!
 *Solves the square equation

 *\param[in] eq A pointer to an equation to be solved

 *\return Return the set of roots of the equation
 */
Equation_roots solve(Square_equation const *const eq);

#endif
