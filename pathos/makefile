engine: main.o map.o button.o config.o util.o
	gcc -o engine main.o map.o button.o config.o util.o -llua5.4 -lSDL2main -lSDL2 -lSDL2_ttf
	rm -f *.o *~

main.o: main.c
	gcc -c -Wall main.c -llua5.4 -lSDL2main -lSDL2

map.o: map.c
	gcc -c -Wall map.c

button.o:
	gcc -c -Wall gui/button.c -lSDL2main -lSDL2 -lSDL2_ttf

config.o: config.c
	gcc -c -Wall config.c -llua5.4

util.o: util.c
	gcc -c -Wall util.c -llua5.4 -lSDL2main -lSDL2
