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
 * c_create
 * Returns osm from a given file path
 *)
external c_create : string -> osm = "osm_from_file"
(* 
 * c_read
 * Displays a progress bar
 *)
external c_read : osm -> unit = "osm_read_data"

let read fileMap =
    let map = c_create fileMap in
    c_read map