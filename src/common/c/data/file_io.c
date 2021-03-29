/**
 * @author Antoine
 * @date Start 27/03/2021
 * @details This part juste save and load date form disk (game part)
 */

//Safety loop guard
#ifndef COMMON_DATA_FILE_IO_C
#define COMMON_DATA_FILE_IO_C

#define MAX_BUFFER 1024

#include "file_io.h"

int save_io(char * path, char * str)
{
    FILE * f = fopen(path, "w+");
    if (f == NULL)
        return 1;

    if (fputs(str, f) == 0)
    {
        fclose(f);
        return 2;
    }

    fclose(f);
    return 0;
}


char * load_io(char * path)
{
    FILE * f = fopen(path, "r");
    if (f == NULL)
        return "";

    char *str = malloc(sizeof(char)*MAX_BUFFER);

    fgets(str, MAX_BUFFER, f);

    fclose(f);
    return str;
}

//End safety guard
#endif