#include <stdio.h>
#include <stdlib.h>

void print_version() {
    printf("homel v%s\n", "0.0.1");
}

int main(int argc, char **argv) {
    print_version();
    return EXIT_SUCCESS;
}

