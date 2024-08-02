#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover FileName\n");
        return 1;
    }

    FILE *card = fopen(argv[1], "r");

    if (card == NULL)
    {
        printf("Could not open file.\n");
        return 2;
    }

    uint8_t buffer[512];
    FILE *image = NULL;
    char filename[8];
    int file_count = 0;

    while (fread(buffer, 1, 512, card) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] >= 0xe0 &&
            buffer[3] <= 0xef)
        {
            if (image != NULL)
            {
                fclose(image);
            }

            sprintf(filename, "%03i.jpg", file_count);
            image = fopen(filename, "w");

            if (image == NULL)
            {
                printf("Could not create output file.\n");
                fclose(card);
                return 3;
            }

            file_count++;
        }

        if (image != NULL)
        {
            fwrite(buffer, 1, 512, image);
        }
    }

    if (image != NULL)
    {
        fclose(image);
    }

    fclose(card);
    return 0;
}
