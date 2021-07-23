// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;
typedef uint8_t BYTE;
typedef int16_t SAMPLE;

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

    // Copy header from input file to output file
    BYTE buffer[HEADER_SIZE];
    fread(&buffer, sizeof(BYTE), HEADER_SIZE, input);
    fwrite(&buffer, sizeof(BYTE), HEADER_SIZE, output);



    // Read samples from input file and write updated data to output file
    SAMPLE sampleBuffer[1];
    while (fread(&sampleBuffer, sizeof(SAMPLE), 1, input))
    {
        sampleBuffer[0] = sampleBuffer[0] * factor;
        fwrite(&sampleBuffer, sizeof(SAMPLE), 1, output);
    }
    // Close files
    fclose(input);
    fclose(output);

    return 0;
}
