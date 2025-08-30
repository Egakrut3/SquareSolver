/*! \file */

#include "Option_manager.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>

/*!
 *Contains options which user can configure from command-line
 */
enum Option
{
    HELP_OPTION,    ///<Corresponds to --help option
    EPS_OPTION,     ///<Corresponds to --eps option
    TEST_OPTION,    ///<Corresponds to --test option
    __OPTION_COUNT, ///<Used to access to count of options
};

/*!
 *Parses --help option and its arguments

 *\param[in, out] str_ptr A pointer to argv iterator from whose string parsing must start
 *\param[in] end_str A pointer to last argv string
 *\param[out] config_ptr A pointer to config object to be setted

 *\return Return User_error object containing information about error occured (possible no error)
 */
[[nodiscard]] static User_error set_help_config(char const *const **const str_ptr,
                                                char const *const *const end_str,
                                                Config *const config_ptr)
{
    assert(str_ptr and *str_ptr and *str_ptr != end_str and !strcmp(**str_ptr, "--help") and end_str and
           config_ptr and config_ptr->is_valid);

    config_ptr->is_help = true;
    printf("Usage: square.exe [options] file...\nOptions:\n"
           "\t%-10s %s\n" "\t%-10s %s\n" "\t%-10s %s\n",
           "--help", "Display the information",
           "--eps" , "Sets the value of eps (acceptable error) by followed parameter",
           "--test", "Tells path to file containing test fo solve function by folowed parameter");
    return construct_User_error(NO_ERROR, 0);
}

/*!
 *Parses --eps option and its arguments

 *\param[in, out] str_ptr A pointer to argv iterator from whose string parsing must start
 *\param[in] end_str A pointer to last argv string
 *\param[out] config_ptr A pointer to config object to be setted

 *\return Return User_error object containing information about error occured (possible no error)
 */
[[nodiscard]] static User_error set_eps_config(char const *const **const str_ptr,
                                               char const *const *const end_str,
                                               Config *const config_ptr)
{
    assert(str_ptr and *str_ptr and *str_ptr != end_str and !strcmp(**str_ptr, "--eps") and end_str and
           config_ptr and config_ptr->is_valid);

    if (++*str_ptr == end_str)
    {
        return construct_User_error(NOT_ENOUGH_OPTION_ARGUMENTS, 1, "--eps");
    }

    char *last_ptr = nullptr;
    ld const new_eps = strtold(**str_ptr, &last_ptr);

    assert(last_ptr);

    if (*last_ptr == '\0' and isfinite(new_eps) and new_eps >= 0)
    {
        config_ptr->eps = new_eps;
        return construct_User_error(NO_ERROR, 0);
    }
    else
    {
        return construct_User_error(INCORRECT_OPTION_ARGUMENT, 3,
                                    "--eps", **str_ptr, "Must be finite floating-point value");
    }
}

[[nodiscard]] static User_error set_test_arr_from_file(char const *const path,
                                                Config *const config_ptr)
{
    assert(path and config_ptr);

    FILE *test_file = nullptr;
    fopen_s(&test_file, path, "r");

    if (!test_file)
    {
        return construct_User_error(INCORRECT_OPTION_ARGUMENT, 3,
                                    "--test", path, "Can't open this file or it doesn't exist");
    }

    int check_input = 0;
    check_input = fscanf(test_file, "%zu", &config_ptr->test_arr_size);

    assert(check_input == 1);

    free(config_ptr->test_arr);
    config_ptr->test_arr = (Solve_test_instance *)calloc(config_ptr->test_arr_size,
                                                         sizeof(Solve_test_instance));

    assert(config_ptr->test_arr);

    for (size_t i = 0; i < config_ptr->test_arr_size; ++i)
    {
        ld a = NAN, b = NAN, c = NAN,
           root1 = NAN, root2 = NAN;
        char *str_Cnt_roots = (char *)calloc(30, sizeof(char));
        check_input = fscanf(test_file, "%LG%LG%LG%LG%LG%30s",
               &a, &b, &c,
               &root1, &root2, str_Cnt_roots);

        if (check_input != 6 or !isfinite(a) or !isfinite(b) or !isfinite(c))
        {
            return construct_User_error(INCORRECT_OPTION_ARGUMENT, 3,
                                        "--test", path,
                                        "This file doesn't satisfy format of test: "
                                        "first value means count of tests, "
                                        "next values means tests themselves. "
                                        "Each test consist of 3 finite floating-point values specifying "
                                        "coefficients of the equation, "
                                        "2 floating-point values specifying correct roots of the "
                                        "equation (possible NAN if corresponding root doesn't exist) and "
                                        "1 string specifying corresponding state of Cnt_roots enum");
        }

        Cnt_roots cnt_roots = strto_Cnt_roots(str_Cnt_roots);
        free(str_Cnt_roots);
        if (cnt_roots == __INVALID_COUNT)
        {
            return construct_User_error(INCORRECT_OPTION_ARGUMENT, 3, "--test", path,
                                        "This file contains invalid string in place where "
                                        "Cnt_roots state was expected");
        }

        config_ptr->test_arr[i] = Solve_test_instance{Square_equation{a, b, c},
                                                      Equation_roots{root1, root2, cnt_roots}};
    }

    fclose(test_file);
    return construct_User_error(NO_ERROR, 0);
}

/*!
 *Parses --test option and its arguments

 *\param[in, out] str_ptr A pointer to argv iterator from whose string parsing must start
 *\param[in] end_str A pointer to last argv string
 *\param[out] config_ptr A pointer to config object to be setted

 *\return Return User_error object containing information about error occured (possible no error)
 */
[[nodiscard]] static User_error set_test_config(char const *const **const str_ptr,
                                                char const *const *const end_str,
                                                Config *const config_ptr)
{
    assert(str_ptr and *str_ptr and *str_ptr != end_str and !strcmp(**str_ptr, "--test") and end_str and
           config_ptr and config_ptr->is_valid);

    if (++*str_ptr == end_str)
    {
        return construct_User_error(NOT_ENOUGH_OPTION_ARGUMENTS, 1, "--test");
    }

    return set_test_arr_from_file(**str_ptr, config_ptr);
}

/*!
 *An array containing write of all options
 */
static char const *const flag_option_arr[__OPTION_COUNT] = {
       "--help",
       "--eps",
       "--test",
};
/*!
 *An array containing pointers to setters of all options
 */
static User_error (*const set_option_arr[__OPTION_COUNT])(char const *const **const,
                                                          char const *const *const,
                                                          Config *const) = {
       &set_help_config,
       &set_eps_config,
       &set_test_config,
};

/*!
 *Selects and call option setter corresponding to the option from argv

 *\param[in, out] str_ptr A pointer to argv iterator from whose string parsing must start
 *\param[in] end_str A pointer to last argv string
 *\param[out] config_ptr A pointer to config object to be setted
 *\param[in] used_option Array that indicates whether an option has been used or not

 *\return Return User_error object containing information about error occured (possible no error)
 */
[[nodiscard]] static User_error select_option_setter(char const *const **const str_ptr,
                                                     char const *const *const end_str,
                                                     Config *const config_ptr, bool *const used_option)
{
    assert(str_ptr and *str_ptr and *str_ptr != end_str and end_str and
           config_ptr and config_ptr->is_valid and used_option);

    for (size_t i = 0; i < __OPTION_COUNT; ++i)
    {
        if (strcmp(**str_ptr, flag_option_arr[i]))
        {
            continue;
        }

        used_option[i] = true;
        User_error new_error = set_option_arr[i](str_ptr, end_str, config_ptr);
        if (new_error.code != NO_ERROR)
        {
            return new_error;
        }

        destruct_User_error(&new_error);
        break;
    }

    return construct_User_error(NO_ERROR, 0);
}

/*!
 *Parses command-line flags

 *\param[in] argc Command-line flags count
 *\param[in] argv Command-line flags themselves
 *\param[out] config_ptr A pointer to config object to be setted

 *\return Information about error made by user (possible no error)
 */
[[nodiscard]] User_error set_config(size_t const argc, char const *const *const argv,
                                    Config *const config_ptr)
{
    assert(argc > 0 and argv and config_ptr and config_ptr->is_valid);

    char const *const *const end_str = argv + argc;
    bool used_options[__OPTION_COUNT] = {};
    for (char const *const *str = argv + 1; str != end_str; ++str)
    {
        assert(str);

        User_error new_error = select_option_setter(&str, end_str, config_ptr, used_options);
        if (new_error.code != NO_ERROR)
        {
            return new_error;
        }

        destruct_User_error(&new_error);
    }

    if (!used_options[EPS_OPTION])
    {
        config_ptr->eps = default_eps;
    }

    if (!used_options[TEST_OPTION])
    {

#ifdef _DEBUG

        User_error new_error = set_test_arr_from_file("Solve_test_case", config_ptr);
        if (new_error.code != NO_ERROR)
        {
            return new_error;
        }

        destruct_User_error(&new_error);
#else

        config_ptr->test_arr_size = 0;
        config_ptr->test_arr = nullptr;

#endif

    }

    return construct_User_error(NO_ERROR, 0);
}
