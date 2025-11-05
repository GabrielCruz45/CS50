#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // check for correct usage
    if (argc < 2)
    {
        printf("Correct usage of program: ./recover data.raw");
        return 1;
    }

    // open memory card
    FILE *memoryCard = fopen(argv[1], "rb");
    if (memoryCard == NULL)
    {
        printf("Error opening card!\n");
        return 1;
    }

    BYTE buffer[512];
    int jpegFileCounter = 0;

    char *filename = NULL;
    FILE *jpeg = NULL;

    while(fread(buffer, sizeof(buffer), 1, memoryCard) != 0)
    {
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            printf("buffer is start!\n");
            if (jpegFileCounter == 0)
            {
                printf("buffer is first!\n");
                // if start of 1st jpeg, create new file; JAZZ
                filename = (char *)malloc(sizeof(char) * 8);

                if (filename == NULL)
                {
                    printf("Could not allocate memory to filename!\n");
                    return 1;
                }
                sprintf(filename, "%03i.jpg", jpegFileCounter);

                jpeg = fopen(filename, "wb");
                if (jpeg == NULL)
                {
                    printf("jpeg could not be opened!\n");
                    return 1;
                }

                // write to new file
                fwrite(buffer, sizeof(buffer), 1, jpeg);

                // up the file number
                jpegFileCounter++;
            }
            else
            {
                printf("buffer is %ind!\n", jpegFileCounter);

                // if 2nd or more jpeg, close previous jpeg and open a new one
                fclose(jpeg);
                printf("success fclosing jpeg 1!\n");

                free(filename);

                filename = (char *)malloc(sizeof(char) * 8);
                if (filename == NULL)
                {
                    printf("Could not allocate memory to filename!\n");
                    return 1;
                }
                sprintf(filename, "%03i.jpg", jpegFileCounter);

                jpeg = fopen(filename, "wb");
                if (jpeg == NULL)
                {
                    printf("jpeg could not be opened!\n");
                    return 1;
                }

                // write to new file
                fwrite(buffer, sizeof(buffer), 1, jpeg);

                // up the file number
                jpegFileCounter++;
            }
        }
        else
        {
            // just keep writing!
            fwrite(buffer, sizeof(buffer), 1, jpeg);
        }
    }

    fclose(jpeg);
    fclose(memoryCard);
}
