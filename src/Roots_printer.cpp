#include "Roots_printer.h"
#include <math.h>

void print_roots(Equation_roots const *const roots_ptr, Config const *const config_ptr)
{
    assert(roots_ptr and config_ptr);

    switch (roots_ptr->cnt_roots)
    {
        case ANY_NUMBER_IS_ROOT:
            assert(isnan(roots_ptr->root1) and isnan(roots_ptr->root2));

            fprintf(config_ptr->output_stream, "Any number, since this is a trivial equation\n");
            break;

        case DEGENERATE_NO_ROOTS:
            assert(isnan(roots_ptr->root1) and isnan(roots_ptr->root2));

            fprintf(config_ptr->output_stream,
                   "No real roots, since coefficients before x2 and x are equal 0 and last one - not\n");
            break;

        case SQUARE_NO_ROOTS:
            assert(isnan(roots_ptr->root1) and isnan(roots_ptr->root2));

            fprintf(config_ptr->output_stream, "No real roots, since discriminant is less, than 0\n");
            break;

        case LINEAR_ONE_ROOT:
            assert(isfinite(roots_ptr->root1) and isnan(roots_ptr->root2));

            fprintf(config_ptr->output_stream, "One root %LG, since this is a normal linear equation\n",
                    roots_ptr->root1);
            break;

        case SQUARE_ONE_ROOT:
            assert(isfinite(roots_ptr->root1) and isnan(roots_ptr->root2));

            fprintf(config_ptr->output_stream, "One root %LG since discriminant is equal 0\n",
                    roots_ptr->root1);
            break;

        case SQUARE_TWO_ROOTS:
            assert(isfinite(roots_ptr->root1) and isfinite(roots_ptr->root2));

            fprintf(config_ptr->output_stream,
                    "Two roots: %LG and %LG since discriminant is greater, than 0\n",
                    roots_ptr->root1, roots_ptr->root2);
            break;

        case __INVALID_COUNT:
        default:
            assert(0);

            break;
    }

    return;
}
