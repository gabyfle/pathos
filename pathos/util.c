/**
 * 
 * pathos - Simulation engine 
 * 2022 - Gabriel Santamaria
 * 
**/

#include "util.h"

/**
 * print()
 * Displays a message with a certain level (error, success, warning)
 * @param int lvl level of the message
 * @param char* msg message to be displayed
 * @return void
 */
void print(int lvl, char *msg)
{
    const char *ERROR_C = "\033[1;31m";
    const char *WARNING_C = "\033[0;33m";
    const char *SUCCESS_C = "\033[0;32m";
    const char *DEFAULT_C = "\033[0m";

    switch (lvl)
    {
        case 1:
            printf(SUCCESS_C);
            break;
        case 2:
            printf(WARNING_C);
            break;
        case 3:
            printf(ERROR_C);
            break;
        default:
            break;
    }

    puts(msg);
    printf(DEFAULT_C); // reset the default color
}
