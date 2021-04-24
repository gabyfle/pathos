(* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *)
(*                                                             *)
(* (simple) Graph library                                      *)
(*                                                             *)
(* @author Gabriel Santamaria <gaby.santamaria@outlook.fr>     *)
(*                                                             *)
(* File: graph.mli                                             *)
(*                                                             *)
(** * * * ** ** * * * * * * * ** * * * ** * * * * * * * * * * **)

type node
type graph

(* Graph.create n 
 * Creates a graph with n node *)
val create: int -> graph

(* Graph.size g 
 * Returns the number of node in g *)
val size: graph -> int

(* Graph.add_edge g a b f
 * Adds a new edge between a and b and that is externally incident to the node a with the capacity of f *)
val add_edge: graph -> node -> node -> int -> unit

(* Graph.del_edge g a b
 * Deletes the edge between a and b *)
val del_edge: graph -> node -> node -> unit

(* Graph.get_edge g a b 
 * Returns the value of the edge between a and b
 * Convention: if the value is 0, there is no edge between a and b *)
val get_edge: graph -> node -> node -> int

(* Graph.get_adj g v
 * Returns the adjacent nodes of v in g *)
val get_adj: graph -> node -> node list

(* Graph.breadth_first g 
 * Breadth-first search algorithm *)
val breadth_first: graph -> unit
