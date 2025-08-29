/*! \file */

#include "Calculation_constants.h"
#include <math.h>

/*!
 *Acceptable accuracy for calculations
 */
static ld eps = default_eps;

/*!
 *Sets the value of eps (acceptable error)

 *\param[in] new_eps A new value for the eps
 */
void set_eps(ld const new_eps)
{
    assert(isfinite(new_eps) and new_eps >= 0);

    eps = new_eps;
    return;
}

/*!
 *Checks whether long double value equal 0 or not, taking error into account

 *\param[in] x The number to check for equality to 0

 *\return Returns 1 if number considered to be 0 and 0 otherwhise
 */
int8_t is_nil(ld const x)
{
    return fabsl(x) <= eps;
}
