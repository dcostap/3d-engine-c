#include "utils.h"

char *read_file(const char *filename, size_t *filesize)
{
    char *buffer;
    size_t length;
    FILE *f = fopen(filename, "rb");
    size_t read_length;

    if (f)
    {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);

        // 1 GiB; best not to load a whole large file in one string
        if (length > 1073741824)
        {
            printf("read_file error: File too large\n");
            exit(0);
        }

        buffer = (char *)malloc(length + 1);

        if (length)
        {
            read_length = fread(buffer, 1, length, f);

            if (length != read_length)
            {
                free(buffer);
                printf("read_file error: File read went wrong\n");
                exit(0);
            }
        }

        fclose(f);

        buffer[length] = '\0';
        *filesize = length;
    }
    else
    {
        printf("read_file error: File %s doesn't exist\n", filename);
        exit(0);
    }

    return buffer;
}