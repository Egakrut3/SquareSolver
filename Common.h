#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>

typedef long double ld;

struct Square_equation
{
    ld a, b, c;
};

enum Cnt_roots
{
    ANY_NUMBER_IS_ROOT = -1,
    NO_ROOTS = 0,
    ONE_ROOT = 1,
    TWO_ROOTS = 2
};

struct Equation_roots
{
    ld root1, root2;
    Cnt_roots cnt_roots;
};

#endif
