(* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *)
(*                                                             *)
(* (simple) Graph library                                      *)
(*                                                             *)
(* @author Gabriel Santamaria <gaby.santamaria@outlook.fr>     *)
(*                                                             *)
(* File: graph.ml                                              *)
(*                                                             *)
(** * * * ** ** * * * * * * * ** * * * ** * * * * * * * * * * **)

type vertex = int
type graph = vertex array array

let create (n: int) =
    Array.make_matrix n n 0

let size = Array.length

let add_edge (g: graph) (a: int) (b: int) (f: vertex) =
    g.(a).(b) <- f
