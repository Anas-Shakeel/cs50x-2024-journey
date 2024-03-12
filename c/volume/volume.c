// Lecture 04 - "Memory"
// Problem Set 01 - "Volume"

/*
? What is the problem?
Make a program that will change the volume of an audio file (of .WAV format)


? What is a WAV file?
.wav file is an extension for an audio file.

? Structure of a WAV file?
Like any other file, WAV files also, consist of bytes.

In wav file,
the first 44 bytes of the file are the header for that wav file
Header > contains the information about that file that the computer or the
    programs on the might need to know in order to read, understand and
    interprete that file.

After the 44 byte header, are two byte samples of audio. many many of these
    2 bytes of audio, repeated back to back to back!
    Each of these samples, represent the value of some audio waveform at
    a particular point in time.

Wav file:
    One 44-byte header.
    Many 2-byte samples:
        to change the volume of a sample, multiply the sample by a number.


? Program Output:
>> ./volume [input file] [output file] [multiplication factor]
>> ./volume input.wav output.wav 2.0

? Program Specifications:
- Read the header from the input file
- Write the header to the output file
- Repeat for each sample:
    - Read the sample from the input file
    - Multiply the sample value by the volume factor
    - Write the new sample to the output file

? Things that will be helpful
- uint8_t == Stores unsigned integers that are 8 bits or 1 byte large
    - Useful for a generic byte of data
    - Can be used for the headers (array of 44 of these)

- int16_t == Stores signed integers (positive, 0 or negative) of 16 bits or
                2 bytes each.
            - Great choice for representing the samples.

- File I/O:
    - fread  = used to read a file
    - fwrite = used to write to a file

*/

// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

// Defining the Types
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
    BYTE bytes[HEADER_SIZE];
    fread(bytes, HEADER_SIZE, 1, input);   // copy 44 bytes into bytes[44] array
    fwrite(bytes, HEADER_SIZE, 1, output); // write the bytes from array to output file

    // Create a buffer for a single sample
    SAMPLE buffer;

    // Read single sample from input into buffer while there are samples left to read
    while (fread(&buffer, sizeof(SAMPLE), 1, input))
    {
        // Update volume of sample
        buffer *= factor;

        // Write updated sample to new file
        fwrite(&buffer, sizeof(SAMPLE), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
