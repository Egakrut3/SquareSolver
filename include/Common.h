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
    NOT_ENOUGH_OPTION_ARGUMENTS,
    INCORRECT_OPTION_ARGUMENT,
    INVALID_ERROR
};

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
    //will dumbly copy pointers to my dynamic array.
    //Because of this I must delete implementation
    //of them and make my own function, which copy one
    //object of struct to another.

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
