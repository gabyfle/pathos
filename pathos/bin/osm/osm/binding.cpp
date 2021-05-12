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

#include "mapping/osm.hpp"

extern "C" {
    #define CAML_NAME_SPACE
    #include <caml/mlvalues.h>
    #include <caml/memory.h>
    #include <caml/alloc.h>
    #include <caml/custom.h>
}

/**
 * osm_from_file
 * Returns `osm` type from a given file path
 */
extern "C"
CAMLprim value osm_from_file(value file)
{
    CAMLparam1 (file);
    std::string fileName = String_val(file);

    std::cout << fileName << std::endl;

    CAMLreturn (Val_unit);
}

/**
 * osm_read_data
 * Displays a progress bar
 */
extern "C"
CAMLprim value osm_read_data(value osmObj)
{
    CAMLparam1 (osmObj);

    std::cout << "Testing" << std::endl;

    CAMLreturn (Val_unit);
}
