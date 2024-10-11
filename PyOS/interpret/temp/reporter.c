#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file = fopen("/tmp/report.txt", "w");
    if (file == NULL) {
        perror("Fatal IN001: Failed to create report file.");
        return EXIT_FAILURE;
    }
    fprintf(file, "PyOS Module is running on PyOS System.\n");
    fclose(file);
    return EXIT_SUCCESS;
}