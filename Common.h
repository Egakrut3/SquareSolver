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

struct Equation_roots
{
    ld root1, root2;
    int cnt_roots;
};

enum Cnt_roots
{
    any_number_is_root = -1, no_roots = 0, one_root = 1, two_roots = 2
};

#endif
