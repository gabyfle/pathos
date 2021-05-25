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

using namespace Mapping;

extern "C" {
    #define CAML_NAME_SPACE
    #include <caml/mlvalues.h>
    #include <caml/memory.h>
    #include <caml/alloc.h>
    #include <caml/custom.h>

    static value to_value(Osm*);
    static Osm * to_osm(value);

    CAMLprim value ocaml_osm_from_file(value);

    #pragma region Counting
    CAMLprim value ocaml_osm_count(value);
    #pragma endregion Counting
}

/**
 * Converts an Osm pointer to a value type
 * @param Osm* p
 * @return value
 */
static value to_value(Osm * p)
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
static Osm * to_osm(value v)
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

    value v = caml_alloc(sizeof(Osm), Abstract_tag);
    Osm* osm = new (Data_abstract_val(v)) Osm(fileName);

    CAMLreturn (to_value(osm));
}

/**
 * osm_count
 * Returns a TUPLE containing the number of ways, nodes and relations in the OSM map file
 */
extern "C"
CAMLprim value ocaml_osm_count(value obj)
{
    CAMLparam1 (obj);
    CAMLlocal1(tuple);

    Osm osm = *to_osm(obj);

    /* Tuple containing (ways * nodes * relations) */
    auto t = osm.count();

    tuple = caml_alloc_tuple(3);

    Store_field(tuple, 0, std::get<0>(t));
    Store_field(tuple, 1, std::get<1>(t));
    Store_field(tuple, 2, std::get<2>(t));

    CAMLreturn (tuple);
}
