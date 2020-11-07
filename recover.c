#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // Check for proper usage
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Open raw data file
    FILE *rawfile = fopen(argv[1], "r");
    if (rawfile == NULL)
    {
        printf("Unable to open file\n");
        return 1;
    }

    FILE *newfile;
    char filename[16];
    int filecount = 0;
    unsigned char bytes[512];

    while (true)
    {

        if (feof(rawfile))
        {
            fclose(rawfile);
            break;
        }

        // Read 512 bytes from file
        fread(bytes, sizeof(bytes), 1, rawfile);

        // Check if start of new jpg
        if (bytes[0] == 0xff &&
            bytes[1] == 0xd8 &&
            bytes[2] == 0xff &&
            (bytes[3] & 0xf0) == 0xe0)
        {
            // Check if first jpg
            if (filecount == 0)
            {
                // Update filename
                sprintf(filename, "000.jpg");

                // Open new file for writing using filename
                newfile = fopen(filename, "w");

                // Print bytes to file
                fwrite(bytes, sizeof(bytes), 1, newfile);

                // Close file
                fclose(newfile);

                // Increment filecount
                filecount++;
            }
            else
            {
                // Update filename
                sprintf(filename, "%03i.jpg", filecount);

                // Open new file for writing using new filename
                newfile = fopen(filename, "w");

                // Print bytes to file
                fwrite(bytes, sizeof(bytes), 1, newfile);

                // Close file
                fclose(newfile);

                // Increment filecount
                filecount++;
            }
        }
        // If not at the start of a file
        else
        {
            // If a file has already started
            if (filecount > 0)
            {
                // Open new file for appending using new filename
                newfile = fopen(filename, "a");
    
                // Print bytes to file
                fwrite(bytes, sizeof(bytes), 1, newfile);
                
                // Close file
                fclose(newfile);
            }
        }
    }

    fclose(rawfile);
    return 0;
}