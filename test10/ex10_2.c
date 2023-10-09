#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("The number of command line arguments is: %d\n", argc);

    int count=1;

		for (int i = 0; i < argc; i++) {
        printf("Argument %d: %s\n", i, argv[i]);
    }

    return 0;
}

