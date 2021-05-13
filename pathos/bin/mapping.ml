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


(* 
 * c_create
 * Returns osm from a given file path
 *)
external c_create : string -> osm = "ocaml_osm_from_file"
(* 
 * c_count_ways
 * Count the number of ways of the current OSM file
 *)
external c_count_ways : osm -> int = "ocaml_osm_count_ways"

(*
 * Create a OSM type object from a .OSM file
 *)
let create file =
    c_create file

(*
 * Counts the number of ways in the OSM file
 *)
let count_ways osm =
    c_count_ways osm
