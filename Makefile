main: main.c
	gcc main.c -fsanitize=undefined
	./a.out example
