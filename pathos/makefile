engine: main.o map.o config.o util.o
	gcc -o engine main.o map.o config.o util.o -llua5.4 -lSDL2main -lSDL2
	rm -f *.o *~

main.o: main.c
	gcc -c -Wall main.c -llua5.4 -lSDL2main -lSDL2

map.o: map.c
	gcc -c -Wall map.c

config.o: config.c
	gcc -c -Wall config.c -llua5.4

util.o: util.c
	gcc -c -Wall util.c -llua5.4 -lSDL2main -lSDL2
