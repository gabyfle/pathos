engine: main.o entity.o map.o menu.o button.o config.o util.o
	gcc -g -o engine main.o entity.o map.o menu.o button.o config.o util.o -llua5.4 -lSDL2main -lSDL2 -lSDL2_ttf
	rm -f *.o *~

main.o: main.c
	gcc -c -Wall main.c -llua5.4 -lSDL2main -lSDL2

entity.o: entity.c
	gcc -c -Wall entity.c -llua5.4 -lSDL2main -lSDL2

map.o: map.c
	gcc -c -Wall map.c

menu.o: menu.c
	gcc -c -Wall menu.c -lSDL2 -lSDL2_ttf

button.o:
	gcc -c -Wall gui/button.c -lSDL2main -lSDL2 -lSDL2_ttf

config.o: config.c
	gcc -c -Wall config.c -llua5.4

util.o: util.c
	gcc -c -Wall util.c -llua5.4 -lSDL2main -lSDL2
