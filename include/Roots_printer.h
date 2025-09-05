/*! \file */

#ifndef ROOTS_PRINTER_H
#define ROOTS_PRINTER_H

#include "Common.h"

/*!
 *Prints roots from Equation_roots to output stream

 *\param[in] roots_ptr A pointer to set of roots to be printed
 *\param[in] config_ptr A pointer to config object that determines behaviour of program
 */
void print_roots(Equation_roots const *roots_ptr, Config const *config_ptr);

#endif
