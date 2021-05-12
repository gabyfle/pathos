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
#include <string>

#include <osmium/io/any_input.hpp>

#include "mapping/osm.hpp"

extern "C" {
    #include <caml/mlvalues.h>
    #include <caml/memory.h>
}

/**
 * osm_from_file
 * Returns `osm` type from a given file path
 */
extern "C"
CAMLprim value osm_from_file(value file)
{
    std::string fileName = String_val(file);

    Osm osm(fileName);

    return *reinterpret_cast<value*>(&osm);
}
