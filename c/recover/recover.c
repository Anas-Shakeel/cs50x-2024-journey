/*
Recover the JPEG photos from a memory card

TODO (Simplified):
    Open up memory card file
    look for beginning of JPEG file
    Open a new JPEG file
    Write 512 bytes until a new JPEG found

How to Open memory card file
    Take advantage of the fopen() function:
        FILE *file = fopen(filename, "r");

How to know if an image is JPEG?
    Every JPEG begins with a distinct header
    Header size > 4-bytes
    Meaning?
        First byte of JPEGs is > 0xff
        Second byte is         > 0xd8
        Third byte is          > 0xff
        Fourth byte could be any of > 0xe0,0xe1,0xe2,.......0xed,0xee,0xef
JPEGs:
    Every JPEG starts with a distinct header
        First three bytes: 0xff  0xd8  0xff
        Last byte: 0xe0, 0xe1 ... 0xef
    JPEGs are stored back to back in memory
    Each block is 512 bytes

Procedure:
    Start at the first block of JPEG file & check for JPEG header
        If header not found:
            Move to the next block
        else:
            Repeat:
                Read 512 bytes block
                    if Block starts with JPEG header:
                        / start of a new jpeg file
                        close the old jpeg file
                        create a new JPEG
                        Repeat the whole process
                    else:
                        keep writing the block into the same JPEG file

How to read the JPEGs?
    you can use the fread() function:
        fread(data, size, number, input_file);
            data: pointer where to store the data you're reading (a buffer - array of bytes)
            size: size of element to read
            number: number of elements to read
            input_file: FILE * to read from

    How to know if that 512-bytes chunk, is start of JPEG file?
        Since JPEGs have a distinct header:
        If the 512-bytes block stored in buffer:
            Check if buffer[0] == 0xff
            Check if buffer[1] == 0xd8
            Check if buffer[2] == 0xff
            Check if (buffer[3] & 0xf0) == 0xe0  // bitwise operation

            If all above are true:
                Means you've found a JPEG beginning
                Create a new JPEG file to write the data

    How to make a new JPEG file:
        Each file should have a very particular filename AS:
            Filename:  ###.jpg , Starting with 000.jpg
            So keep track of how many JPEGs are found to write the correct filename

        How to create the string in the format "###.jpg"?
            sprintf(filename, "%03i.jpg", 2); // to create a filename string
            After creating the filename:
                Open a new file with the filename:
                    FILE *img = fopen(new_filename, "w");;

    How to write to JPEGs?
        fwrite(data, size, number, output_file);
            data: pointer to bytes that will be written to file
            size: size of each element to write (number of bytes in each element that are going to be written)
            number: number of those elements to write
            output_file: FILE * to write to

    READ FILES:
        Keep these things in mind while reading the file

        - fread() returns the number of bytes that were read from the file:
            so, if we ask it to read 512 bytes from a file:
                it will read the bytes and return 512:
                but if there are no 512 more bytes to read:
                    it will return some number that is less that 512

        - Determine what condition to write to check whether fread has gotten at
        the end of the file or not:


Lets put all of them together and write the PSEUDO CODE:
    Open memory card
    Repeat until end of card:
        Read 512 bytes into a buffer
        IF start of new JPEG  // (detect by looking at the header)
            IF first JPEG // ()
                ... // (write the data into 000.jpg & start writing your very first file)
            ELSE:
                ... // (if already found a JPEG )
                Close the file you've been writing to
                open up a new file to continue writing
        ELSE:
            ... // (If not the start of a new JPEG,  this is next 512-byte to write)
            If already found a JPEG:
                ... // keep writing to it

    CLose any remaining files


Program's Specifications:
    Take exactly one argument, "name of forensic image from which to recover JPEGS"
    If not exactly one argument:
        print USAGE message
        return 1 from main

    If forensic image cannot be opened for reading:
        tell the user
        return 1

    Files you generate should each be named ###.jpg, where ### is a three-digit
        decimal number, starting with 000 for the first image and counting up.

    Program, if uses malloc, must not leak any memory


Things to consider:
    sprintf() stores the string at a memory location:
        so for a string like ###.jpg
        It will take 8 bytes to store it!
        Why?
            well there will be 7 characters in the string + nul character
            a total of 8 characters
            And each char takes one byte
            Hence, 8-bytes


*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Define a BYTE type (for buffering)
typedef uint8_t BYTE; // no need to define here but, i like to have a type of my own!
const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    // Accept a single cmd-line arg
    if (argc != 2)
    {
        printf("USAGE ./recover FILE\n");
        return 1;
    }

    // Open up forensic file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        // File can't be opened
        printf("File cannot be opened.\n");
        return 1;
    }

    // Create a buffer array (for well, buffering)
    BYTE buffer[BLOCK_SIZE]; // 512-bytes of buffer array

    // JPEG counter
    int counter = 0;

    char filename[8];                       // stores filename (can store upto 8 chars)
    sprintf(filename, "%03i.jpg", counter); // set filename to "000.jpg"
    FILE *new_jpeg = NULL;

    // While there's data left to read on card
    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, file) == 512)
    {
        // Check the header (look for JPEG signature)
        if ((buffer[0] == 0xFF) && (buffer[1] == 0xD8) && (buffer[2] == 0xFF) && ((buffer[3] & 0xF0) == 0xE0))
        {
            // Header ok. new JPEG found!
            if (counter == 0)
            {
                // First JPEG file
                new_jpeg = fopen(filename, "w");                    // open a new jpeg
                fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, new_jpeg); // write buffer

                // Incr. counter
                counter++;
            }
            else if (counter > 0)
            {
                // Not First JPEG file
                fclose(new_jpeg);                                   // close previous JPEG
                sprintf(filename, "%03i.jpg", counter);             // rename new jpg
                new_jpeg = fopen(filename, "w");                    // Open the jpg
                fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, new_jpeg); // Write buffer to it
                counter++;                                          // increment counter
            }
        }
        else
        {
            // Continuing the same JPEG
            if (counter > 0)
            {
                // JPEG already found
                fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, new_jpeg); // write the buffer to the same already opened JPEG
            }
        }
    }

    // Close any opened files
    fclose(file);
    fclose(new_jpeg);
}

/*
Pseudo Code:
Repeat until end of card:
    read 512 bytes into buffer
    IF New JPEG: (header-test passed)
        / Start of a new JPEG, header found!
        IF its the FIRST JPEG:
            OPEN the first JPEG file of name [filename] // filename should be 000.jpg here
            write data into the file
            SKIP to next iteration
        ELSE IF this is not the first JPEG: // means already found a JPEG
            CLOSE the file being written previously
            CREATE a new filename
            OPEN the JPEG file with that filename
            WRITE the block into it
            SKIP to next iteration

    ELSE:
        / No header found, same old JPEG!
        IF already found a JPEG:
            WRITE the block to opened file
            SKIP to next iteration
        ELSE:
            SKIP to next iter. // incase some garbage block found!



*/
