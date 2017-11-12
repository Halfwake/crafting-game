CFLAGS = -Wall -std=c99

main: main.c menu.o callback.o state.o
	gcc $(CFLAGS) main.c menu.o callback.o state.o -o main -lSDL2

menu.o: menu.c menu.h callback.o
	gcc $(CFLAGS) -c menu.c

callback.o: callback.c callback.h state.h
	gcc $(CFLAGS) -c callback.c

state.o: state.c state.h
	gcc $(CFLAGS) -c state.c


