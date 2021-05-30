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
 * Count the number of ways, nodes and relations of the current OSM file 
 * Returns a TUPLE (ways * nodes * relations) *)
external count : osm -> (int * int) = "ocaml_osm_count"

(* c_way_id
 * Returns the given way's id *)
external way_id : way -> int64 = "ocaml_way_get_id"

(* c_way_type
 * Returns the given way's type *)
external way_type : way -> string = "ocaml_way_get_type"
