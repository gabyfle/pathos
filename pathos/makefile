engine: main.o map.o util.o
	gcc -o engine main.o map.o util.o $(sdl2-config --cflags --libs) -llua5.4

main.o: main.c
	gcc -c -Wall main.c 

map.o: map.c
	gcc -c -Wall map.c

util.o: util.c
	gcc -c -Wall util.c