/*! \file */

#ifndef OPTION_MANAGER_H
#define OPTION_MANAGER_H

#include "Common.h"

//TODO - make error colector
/*enum Set_config_return
{
    TO_CONTINUE,
    TO_INTERRUPT
};*/

/*!
 *Parses command-line flags

 *\param[in] argc Command-line flags count
 *\param[in] argv Command-line flags themselves

 *\return Information about error made by user (possible no error)
 */
User_error set_config(int const argc, char const* const *const argv);

#endif
