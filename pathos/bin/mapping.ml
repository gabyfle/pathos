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
external c_create : string -> osm = "ocaml_osm_from_file"

(* c_count_ways
 * Count the number of ways of the current OSM file *)
external c_count_ways : osm -> int = "ocaml_osm_count_ways"

(* c_count_nodes
 * Count the number of nodes of the current OSM file *)
external c_count_nodes : osm -> int = "ocaml_osm_count_nodes"

(* c_count_relations
 * Count the number of relations of the current OSM file *)
external c_count_relations : osm -> int = "ocaml_osm_count_relations"

(* c_count
 * Count the number of ways, nodes and relations of the current OSM file 
 * Returns a TUPLE (ways * nodes * relations) *)
external c_count : osm -> (int * int * int) = "ocaml_osm_count"

let create = c_create

let count_ways = c_count_ways

let count_nodes = c_count_nodes

let count_relations = c_count_relations

let count = c_count
