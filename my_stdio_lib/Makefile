clean: 
	rm *.so *.o main

so_stdio.o: so_stdio.c
	gcc -c -fPIC so_stdio.c -o so_stdio.o

libso_stdio.o: so_stdio.o
	gcc -shared so_stdio.o -o libso_stdio.so

main: main.c libso_stdio.so #testing
	gcc main.c -o main -lso_stdio -L .

build: main
	export LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:.
