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

(* Mapping.count_ways osm
 * Counts the number of ways in the OSM file *)
val count_ways : osm -> int

(* Mapping.count_nodes osm
 * Counts the number of nodes in the OSM file *)
val count_nodes : osm -> int

(* Mapping.count_relations osm
 * Counts the number of relations in the OSM file *)
val count_relations : osm -> int

(* Mapping.count osm
 * Counts the number of ways, nodes and relations in the OSM file *)
val count : osm -> (int * int * int)
