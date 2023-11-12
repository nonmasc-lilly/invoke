all: invoke.s
	gcc -w -c -s mem.c -o mem.o -O0 -nostdlib -fno-ident -fno-asynchronous-unwind-tables -fno-stack-protector
	gcc -w -c -s mkgen.c -o mkgen.o -O0 -nostdlib -fno-ident -fno-asynchronous-unwind-tables
	gcc -w -c -s invoke.s -o invoke.o -nostdlib -fno-ident -fno-asynchronous-unwind-tables
	ld invoke.o mkgen.o malloc.o -o mkgen -nostdlib -s -T link.ld
size:
	wc -c malloc.o
	wc -c invoke.o
	wc -c mkgen.o
	wc -c mkgen
clean:
	rm -rf *.o
