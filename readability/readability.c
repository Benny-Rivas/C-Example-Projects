#include <cs50.h>
#include <stdio.h>

int _check_characters(string input)
{
    int character_counter = 0;

    for (int i = 0; input[i] != '\0'; i++)
    {
        if ((input[i] < 123 && input[i] > 96) || (input[i] < 91 && input[i] > 64))
        {
            character_counter++;
        }
    }

    return character_counter;
}

int _check_words(string input)
{
    int word_counter = 0;

    for (int i = 0; input[i] != '\0'; i++)
    {
        if (input[i] == 32)
        {
            word_counter++;
        }
    }

    word_counter++;
    return word_counter;
}

int _check_sentence_count(string input)
{
    int sentence_counter = 0;

    for (int i = 0; input[i] != '\0'; i++)
    {
        if (input[i] == 63 || input[i] == 33 || input[i] == 46)
        {
            sentence_counter++;
        }
    }

    return sentence_counter;
}

float _coleman_index(float a, float b, float c)
{
    float L = (a / b) * 100;
    float S = (c / b) * 100;
    float I = 0.0588 * L - 0.296 * S - 15.8;
    return I;
}

float _round_number(float a)
{
    int below_var = (int) a;
    int top_var = below_var + 1;

    if ((below_var - a) * -1 > top_var - a)
    {
        a = top_var;
        return a;
    }
    else
    {
        a = below_var;
        return a;
    }
}

int main(void)
{
    float num_of_chars;
    float num_of_words;
    float num_of_sentences;
    float final_num;

    string text_input = get_string("Input text to assess here:\n");

    num_of_chars = _check_characters(text_input);
    num_of_words = _check_words(text_input);
    num_of_sentences = _check_sentence_count(text_input);
    final_num = _coleman_index(num_of_chars, num_of_words, num_of_sentences);
    final_num = _round_number(final_num);

    if (final_num < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (final_num > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) final_num);
    }
}
