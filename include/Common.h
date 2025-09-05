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
    INVALID_OPTION_ARGUMENT,     ///<User specified invalid argument for an option
    INVALID_INPUT,               ///<User entered invalid values
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
    User_error &operator= (User_error &) = delete;
};

/*!
 *Extenranal constructor for User_error

 *\param[in] code A code of error
 *\param[in] str_cnt Count of strings to be passed to User_error.data
 *\param[in] others Strings to be passed to User_error.data themselves

 *\return Constructed User_error
 */
[[nodiscard]] User_error construct_User_error(User_error_code code, size_t str_cnt, ...);

/*!
 *External destructor for User_error

 *\param[in, out] error_ptr A pointer to User_error to be destructed
 */
void destruct_User_error(User_error *error_ptr);

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

/*!
 *Converts null-terminated string to one of Cnt_roots states. If Cnt_roots doesn't contain state with this name return __INVALID_COUNT

 *\param[in] str A string containing name of Cnt_roots state

 *\return Returns corresponding Cnt_roots object
 */
Cnt_roots strto_Cnt_roots(char const *str);

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
    FILE *input_stream;            ///<An input stream
    FILE *output_stream;           ///<An output stream
    bool is_help;                  ///<Contains flag whether this run of program is for help information or not

    bool is_valid;                 ///<Indicates whether this object is valid or not

    //Identical to User_error case
    Config& operator=(Config &) = delete;
};

/*!
 *External destructor for Config

 *\param[in, out] config_ptr A pointer to Config to be destructed
 */
void destruct_Config(Config *config_ptr);

/*!
 *Value for eps (acceptable error) if user doesn't specify any
 */
static ld const default_eps = 1E-9;


/*!
 *Checks whether long double value equal 0 or not, taking error into account

 *\param[in] x The number to check for equality to 0
 *\param[in] config_ptr A pointer to config object that determines behaviour of program

 *\return Returns true if number considered to be 0 and false otherwhise
 */
bool is_nil(ld x, Config const *config_ptr);

/*!
 *Checks whether two sets of roots are equal or not

 *\param[in] roots1_ptr The first set of roots
 *\param[in] roots2_ptr The second set of roots
 *\param[in] config_ptr A pointer to config object that determines behaviour of program

 *\return Returns true if sets considered equal and false otherwise
 */
bool are_equal(Equation_roots const *roots1_ptr, Equation_roots const *roots2_ptr,
               Config const *config_ptr);

#endif
