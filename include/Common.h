#ifndef COMMON_H
#define COMMON_H

#include "Colored_printf.h"
#include <stdio.h>
#include <assert.h>

typedef long double ld;

enum User_error_code
{
    NO_ERROR,
    NORMAL_TERMINATION,
    UNKNOWN_OPTION,
    NOT_ENOUGH_OPTION_ARGUMENTS,
    INCORRECT_OPTION_ARGUMENT,
    INVALID_ERROR
};

/*!
    \brief Contains error of user
*/
struct User_error
{
    char **data;
    User_error_code code;
    int str_cnt, valid;

    //Since I use dynamically allocated memeory
    //in my struct, I must clear it by call
    //"destruct_User_error", when I'm not going
    //to use this variable anymore. However
    //built-in assign-operator and copy-constructor,
    //will sometimes implicitly copy pointers to my
    //dynamic array to the unnamed variables and
    //forget them after use, what may lead memory leaks.
    //Because of this I must delete implementation of
    //them, what is the use of C++ syntaxis in order to
    //avoid features appeared only in C++, and make my
    //own function, which copy one object of struct to
    //another.

    //User_error (User_error const &) = delete;
    User_error &operator= (User_error const &) = delete;
};

User_error construct_User_error(User_error_code const, int const, ...);

void destruct_User_error(User_error *const);

void copy_User_error(User_error *const, User_error const *const);

struct Square_equation
{
    ld a, b, c;
};

enum Cnt_roots
{
    ANY_NUMBER_IS_ROOT,
    DEGENERATE_NO_ROOTS,
    SQUARE_NO_ROOTS,
    LINEAR_ONE_ROOT,
    SQUARE_ONE_ROOT,
    SQUARE_TWO_ROOTS
};

struct Equation_roots
{
    ld root1, root2;
    Cnt_roots cnt_roots;
};

int are_equal (Equation_roots const *const, Equation_roots const *const);

struct Solve_test_instance
{
    Square_equation eq;
    Equation_roots roots;
};

#endif
