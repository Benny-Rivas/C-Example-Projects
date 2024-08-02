#include <cs50.h>
#include <stdio.h>

int _string_check(string a)
{
    int string_length = 0;

    for (int i = 0; a[i] != '\0'; i++)
    {
        if (a[i] > 122 || (a[i] < 97 && a[i] > 90) || a[i] < 65)
        {
            //printf("***Invalid input!!!***\n");
            //string_length = 0;
            //break;
            string_length++;
        }
        else if (a[i] < 123 && a[i] > 96)
        {
            a[i] = a[i] - 32;
            string_length++;
        }
        else
        {
            string_length++;
        }
    }

    return string_length;
}

int _check_points(string a, char string_key[], int c, int int_key[])
{
    int sum = 0;

    for (int i = 0; i < c; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            if (a[i] == string_key[j])
            {
                sum = sum + int_key[j];
            }
        }
    }

    return sum;
}

int main(void)
{
    char character_key[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                              'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    int point_key[26] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                         1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

    int p1_length = 0;
    int p2_length = 0;

    string p1_answ;
    string p2_answ;

    int p1_points;
    int p2_points;

    while (p1_length == 0)
    {
        p1_answ = get_string("P1 Pick a word: \n");
        p1_length = _string_check(p1_answ);
    }

    p1_points = _check_points(p1_answ, character_key, p1_length, point_key);

    while (p2_length == 0)
    {
        p2_answ = get_string("P2 Pick a word: \n");
        p2_length = _string_check(p2_answ);
    }

    p2_points = _check_points(p2_answ, character_key, p2_length, point_key);

    if (p1_points == p2_points)
    {
        printf("Tie! Player1:  %i     Player2:  %i\n", p1_points, p2_points);
    }
    else if (p1_points < p2_points)
    {
        printf("Player 2 Wins! Player1:  %i     Player2:  %i\n", p1_points, p2_points);
    }
    else
    {
        printf("Player 1 Wins! Player1:  %i     Player2:  %i\n", p1_points, p2_points);
    }

    return 0;
}
