# About

`pathos` is an attempt to make a system for generating personalized evacuation plans during disasters. At its current state, pathos generate large txt files with data of the personalized evacuation plan for each one of the endangered people.

## How does it works

*TODO: explain in few words how does it works*

## Building

### OCaml files

pathos is using `dune` as the main build system. To build the OCaml files, just launch `dune build` in your terminal at the root of the project.

### C++ files

Building the C++ files of pathos is a little more hard since (in my opinion) the build systems for C-lang are real pain in the ass.

You'll need to first download the **Osmium** library, which is used to handle `.osm` files. I recommand using `vcpkg` by launching `vcpkg install osmium`.

## References

* Part VI and more precisely chapter 26 of *Introduction to Algorithms* by Thomas H. Cormen, Charles E. Leiserson, Ronald Rivest, Clifford Stein
* *ESCAPE : Evacuation Strategy through Clustering and Autonomous Operation in Public Safety Systems* by Georgios Fragkos, Pavlos Athanasios Apostolopoulos and Eirini Eleni Tsiropoulou
