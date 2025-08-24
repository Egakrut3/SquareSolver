#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <assert.h>

typedef long double ld;

enum User_error_code
{
    NO_ERROR,
    NORMAL_TERMINATION,
    UNKNOWN_OPTION,
    INCORRECT_OPTION_ARGUMENT,
    INVALID_ERROR
};

struct User_error
{
    User_error_code code;
    char const *const *data;
};

struct Square_equation
{
    ld a, b, c;
};

enum Cnt_roots
{
    ANY_NUMBER_IS_ROOT = -1,
    NO_ROOTS           = 0,
    ONE_ROOT           = 1,
    TWO_ROOTS          = 2
};

struct Equation_roots
{
    ld root1, root2;
    Cnt_roots cnt_roots;
};

#endif
