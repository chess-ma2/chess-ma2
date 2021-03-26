/**
 * @author Antoine
 * @date Start 9/03/2021
 * @details This part is responsible
 * to check compatibility of version client/server.
 */

//Safety loop guard
#ifndef CLIENT_NETWORK_COMPATIBILITY_H
#define CLIENT_NETWORK_COMPATIBILITY_H

#include "tcp_connect.c"

/**
 * @author Antoine
 * @date Start 9/03/2021
 * @details Main function of this file
 * and check compatibility of client with server.
 * @warning This function is not safe for thread,
 * she can block.
 * @return 0 in success, other in problem or error.
 *      [1;8] For error in TCP Connect.
 *      9 Answer of server is invalid or impossible to read.
 *      10 Answer not understood
 *      [11;19] Correspond to errors of "check_network_answer" + 10
 *      20 version of client is too old in compare of server.
 *      21 version of server is too old in compare of client version.
 *              Yes in theory client can do nothing is server side the problem.
 */
int check_compatibility();

/**
 * @author Antoine
 * @date 12/03/2021
 * @details Sub version where is test answer of server.
 * @param buff buffer where is store answer.
 * @param end store index+1 of end of analyse.
 * @param result contain integer output found, in case of errors,
 * output is not known.
 * @return errors, 0 no errors, [1-9] error
 *      1 NAN - Not A Number is found
 */
int check_network_answer(char *buff, int *end, unsigned long *result);

//End safety loop guard
#endif