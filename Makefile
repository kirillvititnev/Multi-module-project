.PHONY: all
all: proj.out 
proj.out: main.o fnc.o
	gcc -lm -m32 fnc.o main.o -o proj.out
main.o: main.c
	gcc -m32 -c main.c -o main.o
fnc.o: fnc.asm
	nasm -f elf32 fnc.asm -o fnc.o
.PHONY: clean

clean:
	rm *.o proj.out
 





