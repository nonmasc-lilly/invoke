# invoke
invoke is a simple toolchain for making tiny C executables

To actually compile an invoke based C codebase you only need three files (plus your own files)

- link.ld : [one of the internal gnu linker scripts](https://gist.github.com/csukuangfj/c4bd4f406912850efcbedd2367ac5f33)
- invoke.s : the assembly for invoke
- invoke.h : the C header file so that you can use invoke

The only other thing you will need to compile is gcc and ld of which the options should be as follows:

```
gcc -c -s <.c file> -o <output> -O0 -nostdlib -fno-ident -fno-asynchronous-unwind-tables -fno-stack-protector
```
per file as well as:

```
ld <.o files> -o <output> -nostdlib -s -T link.ld
```

The additional files are as follows:

- mem.c : a simple implementation of malloc, realloc, free, and memcpy that loosely follow standard based on [the malloc tutorial](https://danluu.com/tech-discrimination/)
- mem.h : the header for mem.c
- mkgen.c a tool to generate Makefiles for invoke
- Makefile : mkgens makefile
- mkgen : a compiled binary of mkgen.c
