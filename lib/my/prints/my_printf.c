/*
** EPITECH PROJECT, 2021
** my_printf
** File description:
** Print all demands
*/

#include "../printf.h"
#include <stdarg.h>

void init_pointer(int (**print)())
{
    print[(int)('%')] = &my_putchar;
    print[(int)('d')] = &my_put_nbr;
    print[(int)('i')] = &my_put_nbr;
    print[(int)('s')] = &my_putstr;
    print[(int)('S')] = &my_put_special;
    print[(int)('x')] = &my_putnbr_hexalow;
    print[(int)('X')] = &my_putnbr_hexaup;
    print[(int)('b')] = &my_putnbr_bin;
    print[(int)('o')] = &my_putnbr_oct;
    print[(int)('p')] = &my_put_address;
    print[(int)('u')] = &my_put_unsigned;
    print[(int)('h')] = &my_put_short;
    print[(int)('l')] = &my_put_long;
}

int check(char *c, int i)
{
    char *data = "disSxXbopu%";
    char *li = "li";
    char *si = "hd";
    if (c[i + 1] <= 30) {
        return (0);
    }
    for (int j = 0; data[j] != '\0'; j++) {
        if (c[i + 1] == data[j])
            return (1);
    }
    if (c[i + 1] == li[0] || c[i + 1] == si[0]) {
        if (c[i + 2] == li[1] || c[i + 2] == si[1]) {
            return (2);
        }
    }
    return (0);
}

int my_printf(char *str, ...)
{
    int (*print[160])();
    init_pointer(print);
    va_list ap;
    va_start(ap, str);
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '%' && str[i + 1] == 'c') {
            my_putchar(va_arg(ap, int));
            i = i + 1;
        } else if (str[i] == '%' && (check(str, i) == 1
        || check(str, i) == 2)) {
            (*print[(int)(str[i + 1])])(va_arg(ap, char *));
            i = i + (check(str, i));
        } else {
            my_putchar(str[i]);
        }
    }
    return (0);
}
