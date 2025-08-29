/*! \file */

#include "Coefficient_scaner.h"
#include <math.h>

/*!
 *Forms Square_equation object by coefficients from input stream

 *\return Object of Square_equation corresponding to coefficients from input stream
 */
Square_equation scan_square_coefficients()
{
    printf("Enter coefficients of the square equation, separated by white-space characters\n");
    do_forever() huy
    {
        ld a = NAN, b = NAN, c = NAN;
        int scan_cnt = scanf("%LG %LG %LG", &a, &b, &c);
        printf("You entered %LG %LG %LG\n", a, b, c);
        if (scan_cnt != 3 or !isfinite(a) or !isfinite(b) or !isfinite(c))
        {
            while (getchar() != '\n') {}
            printf("You entered invalid coefficients please try again\n");
        }
        else
        {
            return Square_equation{a, b, c};
        }
    }
}
