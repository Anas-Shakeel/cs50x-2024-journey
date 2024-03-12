// Lecture 04 - "Memory"
// Program 09 - "Cp.c"

/*
Copy any file

HOW?
syntax
>> ./cp srcFile dstFile

srcFile = the file to copy from
dstFile = the file to copy to

example
>> ./cp pic.jpg pic2.jpg

Program will:
Copy the data from pic.jpg to pic2.jpg
Autocreate the pic2.jpg file
*/

#include <stdio.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Open the files in binary read mode.
    FILE *src = fopen(argv[1], "rb"); // SRC file to read data from...
    FILE *dst = fopen(argv[2], "wb"); // DST file to write data to...

    BYTE b;

    while (fread(&b, sizeof(b), 1, src) != 0)
    {
        fwrite(&b, sizeof(b), 1, dst);

        // ? fread + fwrite function args explained
        /*
        fread(where to put the byte of file,
              size of the chunk to copy,
              how many chunks to copy,
              from where to read the chunks
            )
        fread returns '>0' value if the reading was successfull
            and returns '0' if reading was failed
            It returns 0 when it reaches at the end of file, when there is no more data to read!

        fwrite(where to find the chunk (to write),
              size of the chunk,
              how many chunks to write (at a time),
              where to write the chunks
            )
         */
        //
    }

    return 0;
}