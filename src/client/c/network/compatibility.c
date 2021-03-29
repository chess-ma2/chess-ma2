/**
 * @author Antoine
 * @date Start 9/03/2021
 * @details This part is responsible
 * to check compatibility of version client/server.
 */

//Safety loop guard
#ifndef CLIENT_NETWORK_COMPATIBILITY_C
#define CLIENT_NETWORK_COMPATIBILITY_C

//Includes
#include "compatibility.h"

int check_compatibility()
{
    int fd = 1;
    int e = define_connection(CHESS_MA2_NETWORK_ADDRESS, CHESS_MA2_NETWORK_PORT_COMPATIBILITY, &fd);
    if (e != 0)
        return e;

    //Send
    dprintf(fd, "0|%i|TEST\n", CHESS_MA2_NETWORK_VERSION);

    //Read
    char buff[128];//Enougth, if more long-->Error
    e = read(fd, buff, 128);

    //No longer needed, maybe in future with more details(nb players online).
    close(fd);

    if (e <= 0 || e >= 128)
        return 9;

    switch (*(buff+0))
    {
        case '0': {
            unsigned long r = 0;
            int e = check_network_answer(buff + 2, &e, &r);
            if (r == 0)
                return 10 + r;

            if (CHESS_MA2_NETWORK_VERSION < r)
                return 20;
            if (CHESS_MA2_NETWORK_VERSION > r)
                return 21;
            return 0;
        }
        //Switch case for future integration of other level protocols.
        default:
            return 10;
    }
    return 0;
}

int check_network_answer(char *buff, int *end, unsigned long *result)
{
    *result = 0;
    int i = 0;
    while (*(buff + i) != '|')
    {
        if (*(buff + i) < '0' || '9' < *(buff+i))
            return 1;
        *result = 10*(*result)+ (*(buff+i) - '0');
        i++;
    }
    *end = i;
    return 0;
}

//End safety loop guard
#endif