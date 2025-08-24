#ifndef FLAG_MANAGER_H
#define FLAG_MANAGER_H

#include "Common.h"

//TODO - make error colector
/*enum Set_config_return
{
    TO_CONTINUE,
    TO_INTERRUPT
};*/

User_error set_config(int const, char const* const[]);

#endif
