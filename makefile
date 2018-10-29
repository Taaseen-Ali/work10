all: random_stuff.o
	gcc random_stuff.o

random_stuff.o: random_stuff.c
	gcc -c random_stuff.c

run:
	./a.out

clean:
	rm *.o



