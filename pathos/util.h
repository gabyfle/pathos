/**
 * 
 * pathos - Simulation engine 
 * 2022 - Gabriel Santamaria
 * 
**/

#include <SDL2/SDL.h>

#include <lua5.4/lua.h>
#include <lua5.4/lauxlib.h>
#include <lua5.4/lualib.h>

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

/**
 * print()
 * Displays a message with a certain level (error, success, warning)
 * @param int lvl level of the message
 * @param char* msg message to be displayed
 * @return void
 */
void print(int, char *);

/**
 * error()
 * Displays the error message and quit the program
 * @param lua_State* the Lua state to close
 * @param char * the format string
 * @return void
 * @see "Programming in Lua - Fourth Edition" Chapter 27, Section 1 : A first example, where Roberto Ierusalimschy gived that function
 */
void error(lua_State *, const char *, ...);
