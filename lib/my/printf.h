/*
** EPITECH PROJECT, 2021
** printf
** File description:
** More Print Functions
*/

#ifndef PRINT_F
    #define PRINT_F

int my_printf(char *str, ...);
void my_putchar(char c);
int my_putstr(char const *str);
int my_put_nbr(int nb);
int my_putnbr_bin(int nbr);
int my_putnbr_oct(int nbr);
int my_put_short(short int number);
int my_put_special(char *str);
int my_putnbr_hexaup(int nbr);
int my_putnbr_hexalow(int nbr);
int my_put_address(unsigned int str);
int my_put_special(char *str);
int my_put_specialarg(char str);
int my_put_long(long long int number);
int my_putnbr_hexaaddress(unsigned int nbr);
int my_put_unsigned(unsigned int nbr);

#endif
