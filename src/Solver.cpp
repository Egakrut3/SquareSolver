/*! \file */

#include "Solver.h"
#include <math.h>

/*!
 *Solves degenerate equation

 *\param[in] a Coefficient before x^0
 *\param[in] config_ptr A pointer to Config object that determines behaviour of program

 *\return Returns roots of this equation
 */
static Equation_roots degenerate_solver(ld const a, Config const *const config_ptr)
{
    assert(isfinite(a) and config_ptr and config_ptr->is_valid);

    if (is_nil(a, config_ptr))
    {
        return Equation_roots{NAN, NAN, ANY_NUMBER_IS_ROOT};
    }

    return Equation_roots{NAN, NAN, DEGENERATE_NO_ROOTS};
}

/*!
 *Solves linear equation

 *\param[in] a Coefficient before x^1
 *\param[in] b Coefficient before x^0
 *\param[in] config_ptr A pointer to Config object that determines behaviour of program

 *\return Returns roots of this equation
 */
static Equation_roots linear_solver(ld const a, ld const b, Config const *const config_ptr)
{
    assert(isfinite(a) and isfinite(b) and config_ptr and config_ptr->is_valid);

    if (is_nil(a, config_ptr))
    {
        return degenerate_solver(b, config_ptr);
    }

    return Equation_roots{-b / a, NAN, LINEAR_ONE_ROOT};
}

/*!
 *Solves square equation

 *\param[in] a Coefficient before x^2
 *\param[in] b Coefficient before x^1
 *\param[in] c Coefficient before x^0
 *\param[in] config_ptr A pointer to Config object that determines behaviour of program

 *\return Returns roots of this equation
 */
static Equation_roots square_solver(ld const a, ld const b, ld const c, Config const *const config_ptr)
{
    assert(isfinite(a) and isfinite(b) and isfinite(c) and config_ptr and config_ptr->is_valid);

    if (is_nil(a, config_ptr))
    {
        return linear_solver(b, c, config_ptr);
    }

    ld const D2 = b * b - 4 * a * c;

    if (is_nil(D2, config_ptr))
    {
        return Equation_roots{-b / (2 * a), NAN, SQUARE_ONE_ROOT};
    }

    if (D2 < 0)
    {
        return Equation_roots{NAN, NAN, SQUARE_NO_ROOTS};
    }

    assert(D2 >= 0);

    ld const D = sqrtl(D2);
    return Equation_roots{(-b - D) / (2 * a), (-b + D) / (2 * a), SQUARE_TWO_ROOTS};
}

/*!
 *Solves the not greater than square equation

 *\param[in] eq A pointer to an equation to be solved
 *\param[in] config_ptr A pointer to Config object that determines behaviour of program

 *\return Returns roots of this equation
 */
Equation_roots solve(Square_equation const *const eq, Config const *const config_ptr)
{
    assert(eq and config_ptr and config_ptr->is_valid);

    return square_solver(eq->a, eq->b, eq->c, config_ptr);
}
