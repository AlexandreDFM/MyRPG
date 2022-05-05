/*
** EPITECH PROJECT, 2021
** printf
** File description:
** More Print Functions
*/

#ifndef PRINT_F
    #define PRINT_F

    #include <stdio.h>

int my_put_nbrprintf(FILE *file, int nb);
void my_putchar(char c);
int my_putnbr_bin(int nbr);
int my_putnbr_oct(int nbr);
int my_put_short(int number);
int my_putchar_disp(FILE *file, char *c);
int my_fprintf_log(FILE *file, char *str, va_list ap);
int my_put_special(char *str);
int my_printf(FILE *file, char *str, ...);
int my_put_special(char *str);
int my_putnbr_hexaup(int nbr);
int my_putnbr_hexalow(int nbr);
int my_putstrprintf(FILE *file, char *str);
int my_put_specialarg(char str);
int my_put_address(unsigned int str);
int my_put_long(long long int number);
int my_put_unsigned(unsigned int nbr);
int my_putnbr_hexaaddress(unsigned int nbr);

#endif
