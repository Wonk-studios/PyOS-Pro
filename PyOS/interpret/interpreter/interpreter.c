#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define SCRIPT_FOLDER "script"
#define MAIN_FILE "main.py"
#define BUFFER_SIZE 1024

void compile_python_files(const char *folder, FILE *main_file) {
    struct dirent *entry;
    DIR *dp = opendir(folder);

    if (dp == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dp))) {
        if (entry->d_type == DT_REG) {
            char filepath[BUFFER_SIZE];
            snprintf(filepath, sizeof(filepath), "%s/%s", folder, entry->d_name);

            FILE *file = fopen(filepath, "r");
            if (file == NULL) {
                perror("fopen");
                continue;
            }

            char buffer[BUFFER_SIZE];
            while (fgets(buffer, sizeof(buffer), file)) {
                fputs(buffer, main_file);
            }

            fclose(file);
        }
    }

    closedir(dp);
}

int main() {
    FILE *main_file = fopen(MAIN_FILE, "w");
    if (main_file == NULL) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    compile_python_files(SCRIPT_FOLDER, main_file);

    fclose(main_file);

    printf("Compiled all Python scripts into %s\n", MAIN_FILE);

    return EXIT_SUCCESS;
}