#include <cs50.h>
#include <stdio.h>

void _setup_bricks(int h)
{
    for (int i = 0; i < h; i++) // Dictates the current row
    {
        for (int j = i; j < h - 1; j++) // Draw initial spaces
        {
            printf(" ");
        }

        for (int j = 0; j <= i; j++) // Draw the first pyramid section in row
        {
            printf("#");
        }

        printf("  "); // Draw the space between pyramids

        for (int j = 0; j <= i; j++) // Draw the second pyramid section in row
        {
            printf("#");
        }

        printf("\n"); // Start new row
    }
}

int main(void)
{
    int answer = 0;
    while (answer < 1 || answer > 8) // Takes input from a range of 1-8
    {
        answer = get_int("How tall should the pyramid be? **(Can be 1-8)**\n");
    }

    _setup_bricks(answer);
}
