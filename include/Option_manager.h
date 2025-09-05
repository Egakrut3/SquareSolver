/*! \file */

#ifndef OPTION_MANAGER_H
#define OPTION_MANAGER_H

#include "Common.h"

/*!
 *Parses command-line flags

 *\param[in] argc Command-line flags count
 *\param[in] argv Command-line flags themselves
 *\param[out] config_ptr A pointer to config object to be setted

 *\return Information about error made by user (possible no error)
 */
[[nodiscard]] User_error set_config(size_t, char const* const *, Config *);

#endif
