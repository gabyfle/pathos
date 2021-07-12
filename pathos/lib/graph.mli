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

(* Graph.add_node g id
 * Adds an ID to the first node that hasn't one yet *)
val add_node: graph -> int64 -> unit

(* Graph.get_edges g 
 * Returns the edges matrix of the graph *)
val get_edges : graph -> int array array

(* Graph.add_edge g a b f
 * Adds a new edge between a and b and that is externally incident to the node a with the capacity of f *)
val add_edge: graph -> node -> node -> int -> unit

(* Graph.has_node g id
 * Determines if a graph has a node with the same id as the given one *)
val has_node: graph -> int64 -> bool

(* Graph.get_by_id g id
 * Gets a node by it's id *)
val get_by_id: graph -> int64 -> node

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

(* Graph.bfs g n func
 * Breadth-first search algorithm 
 * Applies the given function to each encountred node and its successor *)
val bfs: graph -> node -> (node -> node -> unit) -> unit
