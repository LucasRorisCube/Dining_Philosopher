all: main

run: main
	./main

functions.o: functions.c
	gcc -pthread -o functions.o -c functions.c

main.o: main.c
	gcc -pthread -o main.o -c main.c

main: main.o functions.o
	gcc -pthread -o main main.o functions.o
	
clean:
	@rm *.o