(*.-.. -.-- -.-. ..-.. . / -.-. .- -- .. .-.. .-.. . / --. ..- ..-.. .-. .. -.*)
(*                                                                            *)
(* This file is a part of                                                     *)
(*                                                                            *)
(* The Pathos project -                                                       *)
(* An attempt to generate evacuation plan in real time                        *)
(* @author Gabriel Santamaria <gaby.santamaria@outlook.fr>                    *)
(*                                                                            *)
(* File: map.ml                                                               *)
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
 * c_read
 * Displays a progress bar
 *)
external c_read : osm -> unit = "ocaml_osm_read_data"

let read fileMap =
    let map = c_create fileMap in
    c_read map