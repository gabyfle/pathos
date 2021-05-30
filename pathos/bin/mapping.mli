(*.-.. -.-- -.-. ..-.. . / -.-. .- -- .. .-.. .-.. . / --. ..- ..-.. .-. .. -.*)
(*                                                                            *)
(* This file is a part of                                                     *)
(*                                                                            *)
(* The Pathos project -                                                       *)
(* An attempt to generate evacuation plan in real time                        *)
(* @author Gabriel Santamaria <gaby.santamaria@outlook.fr>                    *)
(*                                                                            *)
(* File: mapping.mli                                                          *)
(* Description: Map data handling functions and algorithms                    *)
(*                                                                            *)
(*.-.. --- ...- . -..  /  .--. .- - .... --- ...  / .--. .-. --- .--- . -.-. -*)

type osm

(* Mapping.create str
 * Create a OSM type object from a .OSM file *)
val create : string -> osm

(* Mapping.read osm 
 * Reads the given OSM object and arrange data to prepare graph building *)
val read : osm -> unit

(* Mapping.count osm
 * Counts the number of ways, nodes and relations in the OSM file *)
val count : osm -> (int * int)
