#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

    if (argc != 2)  // Check usage
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");  // Open file
    if (file == NULL)
    {
        printf("Error occured when opening this file\n");
        return 1;
    }

    unsigned char bytes[512];     // Read 512 bytes
    FILE *image = NULL;
    char fileName[8];
    int fileCounter = 0;
    int jpegCounter = 0;

    while (fread(bytes, 512, 1, file) == 1)
    {
        
    if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && ((bytes[3] & 0xf0) == 0xe0))     // Check 512 bytes
    {
        if (jpegCounter == 1)
        {
            fclose(image);
        }
        else
        {
            jpegCounter = 1;
        }

    sprintf(fileName,"%03i.jpg",fileCounter);
    image = fopen(fileName,"w");
    fileCounter ++;
    }
    
    if (jpegCounter == 1)
    {
        fwrite(&bytes, 512, 1, image);
    }
    }

    fclose(file);  // Close file and image
    fclose(image);

    return 0;
}
