/*! \file */

#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <assert.h>
#include <stdint.h>

/*!
 *A macros to make infinite loop clearer
 */
#define do_forever() for(;;)

/*!
 *One-word exchange for long double
 */
typedef long double ld;

/*!
 *Contains errors that may occur because of user
 */
enum User_error_code
{
    NO_ERROR,                    ///<No error occured
    UNKNOWN_OPTION,              ///<User specified unknown option
    NOT_ENOUGH_OPTION_ARGUMENTS, ///<User didn't specify enough argument for an option
    INCORRECT_OPTION_ARGUMENT,   ///<User specified incorrect argument for an option
};

/*!
 *Contains information about error than occured because of user
 */
struct User_error
{
    size_t str_cnt;       ///<Count strings in data
    char **data;          ///<An array of strings containing information about error
    User_error_code code; ///<Code of an error

    bool valid;           ///<Indicates whether this object is valid or not

    //Since I use dynamically allocated memeory
    //in my struct, I must clear it by call
    //"destruct_User_error", when I'm not going
    //to use this variable anymore. However
    //built-in assign-operator and copy-constructor,
    //will sometimes implicitly copy pointers to my
    //dynamic array to the unnamed variables and
    //forget them after use, what may lead memory leaks.
    //Because of this I must delete implementation of
    //them, what is the use of C++ syntaxis, in order to
    //avoid features appeared only in C++, and make my
    //own function, which copy one object of struct to
    //another.

    //User_error (User_error const &) = delete;
    User_error &operator= (User_error const &) = delete;
};

User_error construct_User_error(User_error_code const, size_t const, ...);

void destruct_User_error(User_error *const);

/*!
 *Contains coefficients of square equation
 */
struct Square_equation
{
    ld a; ///<Coefficient before x^2
    ld b; ///<Coefficient before x^1
    ld c; ///<Coefficient before x^0
};

/*!
 *Contains count of roots and reason explaining how that count was calculated
 */
enum Cnt_roots
{
    ANY_NUMBER_IS_ROOT,  ///<Any number is root of trivial equation
    DEGENERATE_NO_ROOTS, ///<Degenerate equation has no roots
    SQUARE_NO_ROOTS,     ///<Square equation has no roots, because discriminant less than 0
    LINEAR_ONE_ROOT,     ///<Linear equation has one root
    SQUARE_ONE_ROOT,     ///<Square equation has one root, since discriminant equal 0
    SQUARE_TWO_ROOTS,    ///<Square equation has two roots, since discriminant greater than 0
    __INVALID_COUNT,     ///<This count can't be calculated
};

Cnt_roots strto_Cnt_roots(char const *const);

/*!
 *Contains roots of an equation
 */
struct Equation_roots
{
    ld root1;            ///<Contains the first root (if exist)
    ld root2;            ///<Contains the second root (if exist)
    Cnt_roots cnt_roots; ///<Contains information about count of roots
};

/*!
 *Contains a single test for solve function
 */
struct Solve_test_instance
{
    Square_equation eq;   ///<An equation to be solved
    Equation_roots roots; ///<Correct roots of this equation
};

struct Config
{
    ld eps;                        ///<Contains eps value for calculations
    size_t test_arr_size;          ///<Contains size of array of tests
    Solve_test_instance *test_arr; ///<Array of tests itself
    bool is_help;                  ///<Contains flag whether this run of program is for help information or not

    bool is_valid;                 ///<Indicates whether this object is valid or not

    //Identical to User_error case
    Config& operator=(Config const&) = delete;
};

void destruct_Config(Config *const);

/*!
 *Value for eps (acceptable error) if user doesn't specify any
 */
static ld const default_eps = 1E-9;

bool is_nil(ld const, Config const *const);

bool are_equal(Equation_roots const *const, Equation_roots const *const, Config const *const);

#endif
