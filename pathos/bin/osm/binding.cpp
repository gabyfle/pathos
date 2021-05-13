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

    static inline value to_value(Osm*);
    static inline Osm * to_osm(value);

    CAMLprim value ocaml_osm_from_file(value);
    CAMLprim value ocaml_osm_read_data(value);
}

/**
 * Converts an Osm pointer to a value type
 * @param Osm* p
 * @return value
 */
static inline value to_value(Osm * p)
{
    return caml_copy_nativeint((intnat) p);
}

/**
 * Converts a value to an Osm pointer
 * @param value
 * @return Osm*
 */
static inline Osm * to_osm(value v)
{
    return (Osm *) Nativeint_val(v);
}

/**
 * osm_from_file
 * Returns `osm` type from a given file path
 */
extern "C"
CAMLprim value ocaml_osm_from_file(value file)
{
    CAMLparam1 (file);
    std::string fileName = String_val(file);

    std::cout << "Creating OSM object..." << std::endl;

    Osm osm = Osm(fileName);

    //if (sizeof(osm))
    //    std::cout << "Done" << std::endl;

    value v = to_value(&osm);

    CAMLreturn (v);
}

/**
 * osm_read_data
 * Displays a progress bar
 */
extern "C"
CAMLprim value ocaml_osm_read_data(value obj)
{
    CAMLparam1 (obj);

    Osm osm = *to_osm(obj);

    osm.read();

    CAMLreturn (Val_unit);
}
