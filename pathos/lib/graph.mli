(* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *)
(*                                                             *)
(* (simple) Graph library                                      *)
(*                                                             *)
(* @author Gabriel Santamaria <gaby.santamaria@outlook.fr>     *)
(*                                                             *)
(* File: graph.mli                                             *)
(*                                                             *)
(** * * * ** ** * * * * * * * ** * * * ** * * * * * * * * * * **)

type vertex = int
type graph

(* Graph.create n 
 * Creates a graph with n vertex *)
val create: int -> graph

(* Graph.size g 
 * Returns the number of vertex in g *)
val size: graph -> int

(* Graph.add_edge g a b f
 * Adds a new edge between a and b and that is externally incident to the vertex a with the capacity of f *)
val add_edge: graph -> vertex -> vertex -> int -> unit


