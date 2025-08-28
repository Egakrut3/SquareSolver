/*! \file */

#ifndef COMMON_H
#define COMMON_H

#include "Colored_printf.h"
#include <stdio.h>
#include <assert.h>

/*!
 *One-word exchange for long double
 */
typedef long double ld;

/*!
 *Contains errors that may occur because of user
 */
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

/*!
 *Extenranal constructor for User_error

 *\param[in] code A code of error
 *\param[in] str_cnt Count of strings to be passed to User_error.data
 *\param[in] others Strings to be passed to User_error.data themselves
 
 *\return Constructed User_error
 */
User_error construct_User_error(User_error_code const code, int const str_cnt, ...);

/*!
 *External destructor for User_error

 *\param[in] ptr A pointer to User_error to be destructed
 */
void destruct_User_error(User_error *const ptr);

/*!
 *External "assignement operator" for User_error

 *\param[out] to A pointer to destination User_error
 *\param[in] from A pointer to source User_error
 */
void copy_User_error(User_error *const to, User_error const *const from);

struct Square_equation
{
    ld a, b, c;
};

/*!
 *Contains count of roots and reason explaining how that count was calculated
 */
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

/*!
 *Checks whether two sets of roots are equal or not

 *\param[in] roots1 The first set of roots
 *\param[in] roots The second set of roots

 *\return Returns 1 if sets considered equal and 0 otherwise
 */
int are_equal (Equation_roots const *const roots1, Equation_roots const *const roots2);

struct Solve_test_instance
{
    Square_equation eq;
    Equation_roots roots;
};

#endif
