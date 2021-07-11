(*.-.. -.-- -.-. ..-.. . / -.-. .- -- .. .-.. .-.. . / --. ..- ..-.. .-. .. -.*)
(*                                                                            *)
(* This file is a part of                                                     *)
(*                                                                            *)
(* The Pathos project -                                                       *)
(* An attempt to generate evacuation plan in real time                        *)
(* @author Gabriel Santamaria <gaby.santamaria@outlook.fr>                    *)
(*                                                                            *)
(* File: mapping.ml                                                           *)
(* Description: Map data handling functions and algorithms                    *)
(*                                                                            *)
(*.-.. --- ...- . -..  /  .--. .- - .... --- ...  / .--. .-. --- .--- . -.-. -*)

type osm

type o_way (* internal abstract (c defined) type representing a way *)
type o_node (* same but for a node *)

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
external iter_ways : osm -> (int64 -> o_way -> unit) -> unit = "ocaml_osm_iter_ways"

(* c_way_id
 * Returns the given way's id *)
external way_id : o_way -> int64 = "ocaml_way_get_id"

(* c_iter_nodes
 * Iterates throught all nodes that belongs to a certain way *)
external iter_nodes : o_way -> (int64 -> o_node -> unit) -> unit = "ocaml_way_iter_nodes"

(* c_way_nodes_count
 * Returns the number of nodes that are in the given way *)
external way_nodes_count : o_way -> int = "ocaml_way_get_nodes_count"

(* c_way_is_end
 * Returns whether or not a given id is a way end *)
external way_is_end : o_way -> int64 -> bool = "ocaml_way_is_end"

(* c_way_type
 * Returns the given way's type *)
external way_type : o_way -> string = "ocaml_way_get_type"

(* c_way_length
 * Returns the given way's length *)
external way_length : o_way -> float = "ocaml_way_get_length"

(* c_node_id 
 * Returns the given node's id *)
external node_id : o_node -> int64 = "ocaml_node_get_id"

(* build_graph
 * osm -> graph
 * Builds a graph from an osm object *)
let build_graph o =
    let (_, a_size) = count o in
    let graph = Graph.create a_size in

    let connections = Hashtbl.create a_size in (* handle the number of ways connected to each nd *)
    let ways_connections id way = 
        (* build the connections hashtable to know to how many ways are connected each nodes *)
        let count_connections id _ =
            try
                let count = Hashtbl.find connections id in
                Hashtbl.replace connections id (count + 1);
                if not Graph.has_node graph id then Graph.add_node graph id;
            with Not_found -> (* this node hasn't already been counted *)
                Hashtlb.add connections id 1;
        in
        iter_nodes way count_connections
    in
    iter_ways o ways_connections;

    let create_edges id way =
        let current = ref int64 in
        let control_nodes id _ =
            if not (way_is_end way id) && (Hashtbl.find connections id > 1) then
                let a, b = !current, Graph.get_by_id graph id in
                Graph.add_edge a b;
            else
                (* todo : create a function to know if the id is the start or the end *)