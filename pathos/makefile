engine: main.o map.o util.o
	gcc -o engine main.o map.o util.o $(sdl2-config --cflags --libs) -llua5.4

main.o: main.c
	gcc -c -Wall main.c $(sdl2-config --cflags --libs) -llua5.4

map.o: map.c
	gcc -c -Wall map.c

config.o: config.c
	gcc -c -Wall config.c $(sdl2-config --cflags --libs) -llua5.4

util.o: util.c
	gcc -c -Wall util.c $(sdl2-config --cflags --libs) -llua5.4