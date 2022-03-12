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
    const char *INFO_C = "\033[0;034m";
    const char *DEFAULT_C = "\033[0m";

    switch (lvl)
    {
        case 1:
            printf(INFO_C);
            break;
        case 2:
            printf(SUCCESS_C);
            break;
        case 3:
            printf(WARNING_C);
            break;
        case 4:
            printf(ERROR_C);
            break;
        default:
            break;
    }

    puts(msg);
    printf(DEFAULT_C); // reset the default color
}

/**
 * error()
 * Displays the error message and quit the program
 * @param lua_State* the Lua state to close
 * @param char * the format string
 * @return void
 * @see "Programming in Lua - Fourth Edition" Chapter 27, Section 1 : A first example, where Roberto Ierusalimschy gived that function
 */
void error(lua_State *L, const char *fmt, ...)
{
    char buffer[256];

    va_list argp;
    va_start(argp, fmt);
    vsprintf(buffer, fmt, argp);

    print(3, buffer);

    lua_close(L);
    //SDL_Quit();

    exit(EXIT_FAILURE);
}
