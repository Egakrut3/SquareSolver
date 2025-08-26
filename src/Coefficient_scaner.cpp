#include "Coefficient_scaner.h"
#include <math.h>

Square_equation scan_square_coefficients()
{
    printf("Enter coefficients of the square equation, separated by white-space characters\n");
    while (1)
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
