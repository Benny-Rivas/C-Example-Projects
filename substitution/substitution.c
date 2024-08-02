#include <cs50.h>
#include <stdio.h>

int _key_validation(char *a, char k_check[])
{
    int counter = 0;
    int copy_counter = 0;
    for (int i = 0; a[i] != '\0'; i++)
    {
        if ((a[i] > 96 && a[i] < 123) || (a[i] > 64 && a[i] < 91))
        {
            counter++;
        }
        else
        {
            return 1;
        }
    }

    if (counter != 26)
    {
        return 1;
    }

    for (int i = 0; k_check[i] != '\0'; i++)
    {
        copy_counter = 0;
        for (int j = 0; a[j] != '\0'; j++)
        {
            if (k_check[i] == a[j] || k_check[i] + 32 == a[j])
            {
                copy_counter++;
            }
        }
        if (copy_counter > 1)
        {
            return 1;
        }
    }
    return counter;
}

void _cypher_text(string plain, char *a, char key_array[])
{
    string cypher_text = plain;
    for (int i = 0; cypher_text[i] != '\0'; i++)
    {
        for (int j = 0; key_array[j] != '\0'; j++)
        {
            if ((cypher_text[i] == key_array[j] && cypher_text[i] > 64 && cypher_text[i] < 91) ||
                (cypher_text[i] == key_array[j] + 32 && cypher_text[i] > 64 && cypher_text[i] < 91))
            {
                if (a[j] > 64 && a[j] < 91)
                {
                    cypher_text[i] = a[j];
                    break;
                }
                else if (a[j] > 96 && a[j] < 123)
                {
                    cypher_text[i] = a[j] - 32;
                    break;
                }
            }
            else if ((cypher_text[i] == key_array[j] && cypher_text[i] > 96 &&
                      cypher_text[i] < 123) ||
                     (cypher_text[i] == key_array[j] + 32 && cypher_text[i] > 96 &&
                      cypher_text[i] < 123))
            {
                if (a[j] > 96 && a[j] < 123)
                {
                    cypher_text[i] = a[j];
                    break;
                }
                else if (a[j] > 64 && a[j] < 91)
                {
                    cypher_text[i] = a[j] + 32;
                    break;
                }
            }
        }
        printf("ciphertext: %s\n", cypher_text);
    }
}

int main(int argc, char *argv[])
{
    char *key = argv[1];
    int key_length;
    char key_check[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                          'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    if (argc != 2)
    {
        printf("Usage: ./substitution KEY\n");
        return 1;
    }

    key_length = _key_validation(key, key_check);

    if (key_length == 1)
    {
        printf("***Key is Invalid!!!***\n");
        return 1;
    }

    string plain_text = get_string("Plaintext: ");

    _cypher_text(plain_text, key, key_check);

    return 0;
}
