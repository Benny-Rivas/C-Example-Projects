#include <cs50.h>
#include <stdio.h>

void _do_math(int change)
{
    int quarter = 25;
    int dime = 10;
    int nickel = 5;
    int penny = 1;

    int num_of_quarters = change / quarter;
    change = change - quarter * num_of_quarters;

    int num_of_dimes = change / dime;
    change = change - dime * num_of_dimes;

    int num_of_nickels = change / nickel;
    change = change - nickel * num_of_nickels;

    int num_of_pennies = change / penny;

    int total_number_of_coins = num_of_quarters + num_of_dimes + num_of_nickels + num_of_pennies;

    printf("%i\n", total_number_of_coins);
}

int main(void)
{
    int actual_change = 0;

    while (actual_change <= 0)
    {
        actual_change = get_int("Input the amount of change. (Format: 0, 00, 000, etc.)\n");
    }

    _do_math(actual_change);
}
