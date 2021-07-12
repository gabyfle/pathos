(*.-.. -.-- -.-. ..-.. . / -.-. .- -- .. .-.. .-.. . / --. ..- ..-.. .-. .. -.*)
(*                                                                            *)
(* This file is a part of                                                     *)
(*                                                                            *)
(* The Pathos project -                                                       *)
(* An attempt to generate evacuation plan in real time                        *)
(* @author Gabriel Santamaria <gaby.santamaria@outlook.fr>                    *)
(*                                                                            *)
(* File: main.ml                                                              *)
(*                                                                            *)
(*.-.. --- ...- . -..  /  .--. .- - .... --- ...  / .--. .-. --- .--- . -.-. -*)

let () =
    let osm = Mapping.create "bordeaux.osm.pbf" in
    Mapping.read osm;
    let g = Mapping.build_graph osm in
    ignore (g);
    let edges = Graph.get_edges g in
    for i = 0 to Array.length edges - 1 do
        for j = 0 to Array.length edges - 1 do
            Printf.printf " %d " edges.(i).(j);
        done;
        Printf.printf "\n"
    done;
