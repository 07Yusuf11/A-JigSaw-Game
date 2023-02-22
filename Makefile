YusufJigSaw: main.o game.o
	gcc game.o main.o -o YusufJigSaw -lSDL2 -lSDL2_image -lSDL2_ttf
main.o: main.c
	gcc -c -g main.c
game.o: game.c game.h
	gcc -c -g game.c
clean:
	rm *.o YusufJigSaw
