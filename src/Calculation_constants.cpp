#include "Calculation_constants.h"
#include <math.h>

static ld eps = 1E-9;

void set_eps(ld const new_eps)
{
    assert(isfinite(new_eps) and new_eps >= 0);
    
    eps = new_eps;
    return;
}

int is_nil(ld const x)
{
    return fabsl(x) <= eps;
}
