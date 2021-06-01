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
    Mapping.big_testing osm;
    Printf.printf "Finished %!"