/**
 * @author Antoine
 * @date Start 27/03/2021
 * @details This part juste save and load date form disk (game part)
 */

//Safety loop guard
#ifndef COMMON_DATA_FILE_IO_H
#define COMMON_DATA_FILE_IO_H

#include <stdio.h>
#include <stdlib.h>

/**
 * @author Antoine
 * @date 27/03/2021
 * @details Save string in a file.
 * @param path path of target file save
 * @param str content to save
 * @return 0 in success else an error.
 */
int save_io(char * path, char * str);

/**
 * @author Antoine
 * @date 27/03/2021
 * @details load string in a file, one line MAX and 1024 CHARs Max
 * @param path path of target file save
 * @return string found, please free after
 */
char * load_io(char * path);

//End safety guard
#endif