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
    #include <caml/mlvalues.h>
    #include <caml/memory.h>
    #include <caml/alloc.h>
    #include <caml/custom.h>

    #define TO_VALUE(VAR) caml_copy_nativeint((intnat) VAR)
    #define TO_TYPE(TYPE, VAR) (TYPE *) Nativeint_val(VAR)

    CAMLprim value ocaml_osm_from_file(value);
    CAMLprim void ocaml_osm_read(value);

    #pragma region Counting
    CAMLprim value ocaml_osm_count(value);
    #pragma endregion Counting
}
/**
 * osm_from_file
 * Returns osm type from a given file path
 */
extern "C"
CAMLprim value ocaml_osm_from_file(value file)
{
    CAMLparam1(file);
    std::string fileName = String_val(file);

    value v = caml_alloc(sizeof(Osm), Abstract_tag);
    Osm* osm = new (Data_abstract_val(v)) Osm(fileName);

    CAMLreturn (TO_VALUE(osm));
}

/**
 * osm_read
 * Reads the data from the OSM file
 * Returns ()
 */
extern "C"
CAMLprim void ocaml_osm_read(value obj)
{
    CAMLparam1(obj);

    Osm* osm = TO_TYPE(Osm, obj);
    osm->read();

    CAMLreturn0;
}

/**
 * osm_count
 * Returns a TUPLE containing the number of ways, nodes and relations in the OSM map file
 */
extern "C"
CAMLprim value ocaml_osm_count(value obj)
{
    CAMLparam1(obj);
    CAMLlocal1(tuple);

    Osm* osm = TO_TYPE(Osm, obj);

    /* Tuple containing (ways * nodes * relations) */
    auto t = osm->count();

    tuple = caml_alloc_tuple(2);

    Store_field(tuple, 0, std::get<0>(t));
    Store_field(tuple, 1, std::get<1>(t));

    CAMLreturn (tuple);
}

/**
 * way_get_id
 * Returns the way id as an int64
 */
extern "C"
CAMLprim value ocaml_way_get_id(value obj)
{
    CAMLparam1(obj);
    CAMLlocal1(id);

    Way* way = TO_TYPE(Way, obj);
    auto i = way->get_id();

    id = caml_copy_int64(i);

    CAMLreturn (id);
}

/**
 * way_get_type
 * Returns the way type as a string
 */
extern "C"
CAMLprim value ocaml_way_get_type(value obj)
{
    CAMLparam1(obj);
    CAMLlocal1(type);
    
    Way* way = TO_TYPE(Way, obj);
    auto str = way->get_type().c_str();

    type = caml_copy_string(str);

    CAMLreturn (type);
}
