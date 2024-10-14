#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file = fopen("/tmp/report.txt", "w");
    if (file == NULL) {
        perror("Error creating report file");
        return EXIT_FAILURE;
    }
    fprintf(file, "C module is present\n");
    fclose(file);
    return EXIT_SUCCESS;
}