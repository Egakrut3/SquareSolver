/*! \file */
#ifndef COLORED_PRINTF_H
#define COLORED_PRINTF_H

/*!
 *Contains colors than can be used to write in concole
 */
enum Color
{
    BLACK,   ///<Black color
    RED,     ///<Red color
    GREEN,   ///<Green color
    YELLOW,  ///<Yellow color
    BLUE,    ///<Blue color
    MAGENTA, ///<Magenta color
    CYAN,    ///<Cyan color
    WHITE,   ///<White color
};

/*!
 *Is identical to printf, but uses color

 *\param[in] color The desired color for printf
 *\param[in] format The format to passed to printf
 *\param[in, out] other The arguments to passed to printf

 *\return Returns value equal to value returned by printf
 */
int colored_printf(Color const color, char const *const format, ...);

#endif
