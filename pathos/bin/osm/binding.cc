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
    #include <caml/callback.h>
    #include <caml/custom.h>

    #define TO_VALUE(VAR) caml_copy_nativeint((intnat) VAR)
    #define TO_TYPE(TYPE, VAR) (TYPE *) Nativeint_val(VAR)

    #pragma region OSM
    CAMLprim value ocaml_osm_from_file(value);
    CAMLprim void ocaml_osm_read(value);
    CAMLprim value ocaml_osm_count(value);
    CAMLprim value ocaml_osm_nodes_connected(value);
    CAMLprim void ocaml_osm_iter_ways(value, value);
    #pragma endregion OSM

    #pragma region Way
    CAMLprim value ocaml_way_get_id(value);
    CAMLprim value ocaml_way_get_type(value);
    CAMLprim value ocaml_way_get_length(value);
    CAMLprim value ocaml_way_is_end(value, value);
    CAMLprim value ocaml_way_is_start(value, value);
    CAMLprim value ocaml_way_is_end(value, value);
    CAMLprim void ocaml_way_iter_nodes(value, value);
    CAMLprim value ocaml_way_get_nodes_count(value);
    #pragma endregion Way

    #pragma region Node
    CAMLprim value ocaml_node_get_id(value);
    #pragma endregion Node
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

    CAMLreturn(TO_VALUE(osm));
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

    CAMLreturn(tuple);
}

/**
 * osm_nodes_connected
 * Returns the number of connected nodes (ie. nodes that are connected to at least one way) in the given file
 */
CAMLprim value ocaml_osm_nodes_connected(value obj)
{
    CAMLparam1(obj);
    CAMLlocal1(count);

    Osm* osm = TO_TYPE(Osm, obj);

    auto c = osm->count_connected_nodes();

    count = caml_copy_int64(c);

    CAMLreturn(count);
}

/**
 * osm_iter_ways
 * Iters throught all ways inside the file
 * @param obj: OSM object that contains Ways
 * @param func: function to apply to each way f: (int64 -> way -> unit)
 */
extern "C"
CAMLprim void ocaml_osm_iter_ways(value obj, value func)
{
    CAMLparam2(obj, func);
    Osm* osm = TO_TYPE(Osm, obj);

    auto it = osm->get_ways();

    for(const auto& o : it) {
        /* CAMLlocal2(i, w); */
        auto i = caml_copy_int64(o.first);
        auto w = caml_alloc(sizeof(Way), Abstract_tag);
        w = TO_VALUE(&o.second);

        caml_callback2(func, i, w);
    }

    CAMLreturn0;
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

    CAMLreturn(id);
}

/**
 * way_is_extremity
 * Returns whether or not a given id is the one of an end of the given way
 * @param obj: Way object
 * @param id: int64 value that represent a node id
 */
extern "C"
CAMLprim value ocaml_way_is_extremity(value obj, value id)
{
    CAMLparam2(obj, id);
    CAMLlocal1(b);

    Way* way = TO_TYPE(Way, obj);
    auto i = Int_val(id);
    bool is_end = (way->get_start() == id || way->get_end() == i);

    b = Val_bool(is_end);

    CAMLreturn(b);
}

/**
 * way_is_start
 * Returns whether or not a given id is the start of the given way
 * @param obj: Way object
 * @param id: int64 value that represent a node id
 */
extern "C"
CAMLprim value ocaml_way_is_start(value obj, value id)
{
    CAMLparam2(obj, id);
    CAMLlocal1(b);

    Way* way = TO_TYPE(Way, obj);
    auto i = Int_val(id);
    bool is_start = way->get_start() == i;

    b = Val_bool(is_start);

    CAMLreturn(b);
}

/**
 * way_is_end
 * Returns whether or not a given id is the end of the given way
 * @param obj: Way object
 * @param id: int64 value that represent a node id
 */
extern "C"
CAMLprim value ocaml_way_is_end(value obj, value id)
{
    CAMLparam2(obj, id);
    CAMLlocal1(b);

    Way* way = TO_TYPE(Way, obj);
    auto i = Int_val(id);
    bool is_end = way->get_end() == i;

    b = Val_bool(is_end);

    CAMLreturn(b);
}

/**
 * way_iter_nodes
 * Iters throught all nodes inside a way
 * @param obj: Way object that contains the nodes
 * @param func: function to apply to each node f: (int64 -> node -> unit)
 */
extern "C"
CAMLprim void ocaml_way_iter_nodes(value obj, value func)
{
    CAMLparam2(obj, func);
    Way* way = TO_TYPE(Way, obj);

    auto it = way->get_nodes();

    for (const auto& o : it) {
        std::cout << o.id << std::endl;
        auto i = caml_copy_int64(o.id);
        auto n = caml_alloc(sizeof(Node), Abstract_tag);
        n = TO_VALUE(&o);

        caml_callback2(func, i, n);
    }
}

/**
 * way_get_nodes_count
 * Returns the way's node count as an int
 */
extern "C"
CAMLprim value ocaml_way_get_nodes_count(value obj)
{
    CAMLparam1(obj);
    CAMLlocal1(nodes);

    Way* way = TO_TYPE(Way, obj);
    auto i = way->get_nodes_count();

    nodes = caml_copy_int64(i);

    CAMLreturn(nodes);
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

    CAMLreturn(type);
}

/**
 * way_get_length
 * Returns the way's length as a double
 */
extern "C"
CAMLprim value ocaml_way_get_length(value obj)
{
    CAMLparam1(obj);
    CAMLlocal1(length);

    Way* way = TO_TYPE(Way, obj);
    auto l = way->get_length();

    length = caml_copy_double(l);

    CAMLreturn(length);
}

/**
 * node_get_id
 * Returns the node's id as an int64
 * @param obj: the node object
 */
CAMLprim value ocaml_node_get_id(value obj)
{
    CAMLparam1(obj);
    CAMLlocal1(id);

    Node* nd = TO_TYPE(Node, obj);
    auto i = nd->id;

    id = caml_copy_int64(i);

    CAMLreturn(id);
}
