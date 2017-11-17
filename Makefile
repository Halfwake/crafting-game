CFLAGS = -Wall -g -std=c99

main: main.c menu.o callback.o state.o button.o texture.o popup.o font.o
	gcc $(CFLAGS) main.c menu.o callback.o state.o button.o texture.o popup.o font.o -o main -lSDL2 -lSDL2_ttf-2.0

menu.o: menu.c menu.h
	gcc $(CFLAGS) -c menu.c

callback.o: callback.c callback.h
	gcc $(CFLAGS) -c callback.c

state.o: state.c state.h
	gcc $(CFLAGS) -c state.c

button.o: button.c button.h
	gcc $(CFLAGS) -c button.c

texture.o: texture.c texture.h
	gcc $(CFLAGS) -c texture.c

popup.o: popup.c popup.h
	gcc $(CFLAGS) -c popup.c

font.o: font.c font.h
	gcc $(CFLAGS) -c font.c
