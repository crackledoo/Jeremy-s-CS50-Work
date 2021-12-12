// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);
    if(!factor)
    {
        printf("Could not adjust volume. Please provide a non-zero factor.\n");
        return 1;
    }
    int c = 0;
    // TODO: Copy header from input file to output file
    uint8_t header[HEADER_SIZE];
    fread(header, HEADER_SIZE, 1, input);
    fwrite(header, HEADER_SIZE, 1, output);
    c++;
    printf("%i\n", c);
    // TODO: Read samples from input file and write updated data to output file
    int16_t buffer[200];
    // Close files
    while (fread(buffer, 200, 2, input) > 0)
    {
        for (int i = 0; i < 200; i++)
        {
            buffer[i] = buffer[i] * factor;
        }
        fwrite(buffer, 200, 2, output);
    }
    fclose(input);
    fclose(output);
    return 0;
}
