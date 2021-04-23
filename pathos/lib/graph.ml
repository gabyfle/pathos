(* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *)
(*                                                             *)
(* (simple) Graph library                                      *)
(*                                                             *)
(* @author Gabriel Santamaria <gaby.santamaria@outlook.fr>     *)
(*                                                             *)
(* File: graph.ml                                              *)
(*                                                             *)
(** * * * ** ** * * * * * * * ** * * * ** * * * * * * * * * * **)

type node = { key: int; distance: int }
type graph = { edges: int array array; nodes: node array }

let create (n: int) =
    let edges = Array.make_matrix n n 0 in
    let nodes = Array.init n (fun k -> { key = k; distance = -1 }) in
    { edges = edges; nodes = nodes }

let size (g: graph) =
    Array.length g.nodes

let add_edge (g: graph) (a: node) (b: node) (f: int) =
    g.edges.(a.key).(b.key) <- f

let del_edge (g: graph) (a: node) (b: node) =
    g.edges.(a.key).(b.key) <- 0

let get_edge (g: graph) (a: node) (b: node) =
    g.edges.(a.key).(b.key)

let get_adj (g: graph) (nd: node) =
    let ext = g.edges.(nd.key) in (* edges incident externally to v *)
    let max = (Array.length ext) - 1 in (* nodes number *)
    let rec get_adj_aux (i: int) (acc: node list) =
        let l = if ext.(i) <> 0 then (g.nodes.(i) :: acc)
                else acc
        in
        if i = max then l
        else get_adj_aux (i + 1) l
    in
    get_adj_aux 0 []
