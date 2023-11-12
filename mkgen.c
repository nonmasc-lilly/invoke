#include "invoke.h"
#include "malloc.h"

int string_length(const char *string) {
    if(string == NULL) return -1;
    int i;
    for(i = 0; string[i]; i++);
    return i;
}

int print_string(char *string) {
    SYS_WRITE(1, string, string_length(string));
}

int main(int argc, char *argv[]) {
    int mkfl, i, fsz;
    char *mkcont;
    if(argc < 3) {
        print_string("USAGE: ");
        print_string(argv[0]);
        print_string(" <output path> <input files>\n");
        SYS_EXIT(0);
    }

    const char *preamble = "all: *.c *.s *.h\n";
    mkcont = malloc(string_length(preamble));
    fsz = string_length(preamble);
    memcpy(mkcont, preamble, fsz);

    for(int i = 2; i < argc; i++) {
        const char *build_preamble = "\tgcc -c -s ";
        const char *build_postamble =
            " -O0 -nostdlib -fno-ident -fno-asynchronous-unwind-tables\n";
        mkcont = realloc(mkcont, fsz + string_length(build_preamble) +
            2*string_length(argv[i]) + 6 + string_length(build_postamble));
        memcpy(mkcont + fsz, build_preamble, string_length(build_preamble));
        memcpy(mkcont + fsz + string_length(build_preamble), argv[i], string_length(argv[i]));
        memcpy(mkcont + fsz + string_length(build_preamble) + string_length(argv[i]), " -o ", 4);
        memcpy(mkcont + fsz + string_length(build_preamble) + string_length(argv[i]) + 4,
            argv[i], string_length(argv[i]));
        memcpy(mkcont + fsz + string_length(build_preamble) + 2*string_length(argv[i]) + 4, ".o",
            2);
        memcpy(mkcont + fsz + string_length(build_preamble) + 2*string_length(argv[i]) + 6,
            build_postamble, string_length(build_postamble));
        fsz += string_length(build_preamble) + 2*string_length(argv[i]) + 6 +
            string_length(build_postamble);
    }

    const char *link_preamble = "\n\tld -s -nostdlib -T link.ld ";
    mkcont = realloc(mkcont, fsz + string_length(link_preamble));
    memcpy(mkcont + fsz, link_preamble, string_length(link_preamble));
    fsz += string_length(link_preamble);
    for(int i = 2; i < argc; i++) {
        mkcont = realloc(mkcont, fsz + string_length(argv[i]) + 3);
        memcpy(mkcont + fsz, argv[i], string_length(argv[i]));
        memcpy(mkcont + fsz + string_length(argv[i]), ".o ", 3);
        fsz += string_length(argv[i]) + 3;
    }

    const char *clean_label = "\nclean: *.o\n\trm -rf *.o\n";
    mkcont = realloc(mkcont, fsz + string_length(clean_label));
    memcpy(mkcont + fsz, clean_label, string_length(clean_label));
    fsz += string_length(clean_label);

    mkfl = SYS_OPEN(argv[1], OPEN_CREAT | OPEN_WRONLY | OPEN_TRUNC, 0666);
    SYS_WRITE(mkfl, mkcont, fsz);

    print_string("content generated:\n==========\n");
    SYS_WRITE(1, mkcont, fsz);
    print_string("==========\n");

    free(mkcont);

    return 0;
}
