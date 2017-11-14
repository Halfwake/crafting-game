CFLAGS = -Wall -g -std=c99

main: main.c menu.o callback.o state.o button.o texture.o dialog.o
	gcc $(CFLAGS) main.c menu.o callback.o state.o button.o texture.o dialog.o -o main -lSDL2

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

dialog.o: dialog.c dialog.h
	gcc $(CFLAGS) -c dialog.c
