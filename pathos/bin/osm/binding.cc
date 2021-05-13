/**
 * This file is a part of
 *
 * The Pathos project -
 * An attempt to generate evacuation plan in real time
 * @author Gabriel Santamaria <gaby.santamaria@outlook.fr>  
 *
 * File: binding.cc
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
    CAMLprim value ocaml_osm_count_ways(value);
}

/**
 * Converts an Osm pointer to a value type
 * @param Osm* p
 * @return value
 */
static inline value to_value(Osm * p)
{
    value v = caml_alloc(sizeof(*p), Abstract_tag);
    *((Osm **) Data_abstract_val(v)) = p;
    return v;
}

/**
 * Converts a value to an Osm pointer
 * @param value
 * @return Osm*
 */
static inline Osm * to_osm(value v)
{
    return *((Osm **) Data_abstract_val(v));
}

/**
 * osm_from_file
 * Returns osm type from a given file path
 */
extern "C"
CAMLprim value ocaml_osm_from_file(value file)
{
    CAMLparam1 (file);
    std::string fileName = String_val(file);

    std::cout << "Creating OSM object..." << std::endl;

    value v = caml_alloc(sizeof(Osm), Abstract_tag);
    Osm* osm = new (Data_abstract_val(v)) Osm(fileName);

    CAMLreturn (to_value(osm));
}

/**
 * osm_count_ways
 * Returns the number of ways in the OSM map file
 */
extern "C"
CAMLprim value ocaml_osm_count_ways(value obj)
{
    CAMLparam1 (obj);

    Osm osm = *to_osm(obj);    

    CAMLreturn (Val_long(osm.count_ways()));
}
