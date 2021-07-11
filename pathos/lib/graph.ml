(* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *)
(*                                                             *)
(* (simple) Graph library                                      *)
(*                                                             *)
(* @author Gabriel Santamaria <gaby.santamaria@outlook.fr>     *)
(*                                                             *)
(* File: graph.ml                                              *)
(*                                                             *)
(** * * * ** ** * * * * * * * ** * * * ** * * * * * * * * * * **)

type node = { key: int; id: int64 }
type graph = { edges: int array array; nodes: node array }

exception Exit

let create (n: int) =
    let edges = Array.make_matrix n n 0 in
    let nodes = Array.init n (fun k -> { key = k; id = -1 }) in
    { edges = edges; nodes = nodes }

let size (g: graph) =
    Array.length g.nodes

let add_node (g: graph) (id: int64) =
    try
        for i = 0 to (Array.length g.nodes) - 1 do
            if g.nodes.(i).id <> - 1 then
                g.nodes.(i).id = id;
                raise Exit
    with Exit ->
        ()

let add_edge (g: graph) (a: node) (b: node) (f: int) =
    g.edges.(a.key).(b.key) <- f

let has_node (g: graph) (id: int64) =
    try
        for i = 0 to (Array.length g.nodes) - 1 do
            if g.nodes.(i).id = id then raise Exit
        done;
        false
    with Exit ->
        true

let get_by_id (g: graph) (id: int64) =
    let found = ref node in
    try
        for i = 0 to (Array.length g.nodes) - 1 do
            if g.nodes.(i).id = id then begin
                found := g.nodes.(i);
                raise Exit
            end
        done;
        raise Not_found
    with Exit ->
        !found

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

let bfs (g: graph) (root: node) (func: node -> node -> unit) =
    let q = Queue.create () in
    Queue.add root q;

    let black = Array.make (size g) false in (* Parallel table to know if a node has already been explored or not *)
    
    let rec loop u =
        if not (Queue.is_empty q) then
            let n = Queue.take q in
            let adj = get_adj g n in
            
            List.iter (fun w ->
                if not black.(w.key) then begin
                    func n w;
                    Queue.add w q;
                end
            ) adj;

            black.(n.key) <- true;

            loop ()
        else
            u
    in
    loop ()
