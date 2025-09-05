/*! \file */

#ifndef SOLVER_H
#define SOLVER_H

#include "Common.h"

/*!
 *Solves the not greater than square equation

 *\param[in] eq A pointer to an equation to be solved
 *\param[in] config_ptr A pointer to Config object that determines behaviour of program

 *\return Returns roots of this equation
 */
Equation_roots solve(Square_equation const *eq, Config const *config_ptr);

#endif
