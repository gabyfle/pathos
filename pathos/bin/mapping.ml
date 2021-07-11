type osm

type way (* internal abstract (c defined) type representing a way *)
(*
 * Highways type
 *
 * Freeway: Large highways that can handle a lot of traffic
 * Departmental: Medium-sized highways
 * Street: The smallest highways. Can handle only few cars at the same time
 *
 *
type highways = Freeway | Departmental | Street*)

(* c_create
 * Returns osm from a given file path *)
external create : string -> osm = "ocaml_osm_from_file"

(* c_read
 * Reads the given OSM object and arrange data to prepare graph building *)
external read : osm -> unit = "ocaml_osm_read"

(* c_count
 * Count the number of ways and nodes of the current OSM file 
 * Returns a TUPLE (ways * nodes) *)
external count : osm -> (int * int) = "ocaml_osm_count"

(* c_count_connected_nodes
 * Counts the number of connected nodes (ie. nodes that are connected to at least one way) in the given file
 * Returns an int *)
external count_connected_nodes : osm -> int = "ocaml_osm_nodes_connected"

(* c_iter_ways
 * Iterates through all ways *)
external iter_ways : osm -> (int64 -> way -> unit) -> unit = "ocaml_osm_iter_ways"

(* c_way_id
 * Returns the given way's id *)
external way_id : way -> int64 = "ocaml_way_get_id"

(* c_way_nodes_count
 * Returns the number of nodes that are in the given way *)
external way_nodes_count : way -> int = "ocaml_way_get_nodes_count"

(* c_way_type
 * Returns the given way's type *)
external way_type : way -> string = "ocaml_way_get_type"

(* c_way_length
 * Returns the given way's length *)
external way_length : way -> float = "ocaml_way_get_length"
