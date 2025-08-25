#ifndef COLORED_PRINTF_H
#define COLORED_PRINTF_H

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

int colored_printf(Color const color, char const *const format, ...);

#endif
