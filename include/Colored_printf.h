/*! \file */
#ifndef COLORED_PRINTF_H
#define COLORED_PRINTF_H

/*!
 *Contains colors than can be used to write in concole
 */
enum Color
{
    BLACK,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE
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
