/**
 * This file is a part of
 *
 * The Pathos project -
 * An attempt to generate evacuation plan in real time
 * @author Gabriel Santamaria <gaby.santamaria@outlook.fr>  
 *
 * File: binding.cpp
 */

#include <iostream>
#include "mapping/osm.hpp"

extern "C" {
    #include <caml/mlvalues.h>
    #include <caml/memory.h>
}

void testing()
{
    Osm map(1, 2);
    map.displayValues();
}

extern "C" 
value display_numbers(value one, value two)
{

    std::cout << "Hello my friend" << std::endl;

    return one;
}
