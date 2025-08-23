#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

typedef long double ld;

struct Square_equation
{
    ld a, b, c;
};

enum Cnt_roots
{
    any_number_is_root = -1, no_roots = 0, one_root = 1, two_roots = 2
};

struct Equation_roots
{
    ld root1, root2;
    Cnt_roots cnt_roots;
};

#endif
