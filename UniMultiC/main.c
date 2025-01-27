#include "utilities.h"
#include "text_analysis.h"
#include "process_management.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if ((argc != 4 && argc != 6) && (argc != 5)) {
        fprintf(stderr, "Usage: %s <mode> <input file> <output file> [<num words> <start word>]\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *mode = argv[1];
    const char *inputFilePath = "/Users/emanuelestorci/Documents/c/UniMultiC/input.txt";
    const char *outputFilePath = "/Users/emanuelestorci/Documents/c/UniMultiC/output.txt";
    int num_words = (argc > 4) ? atoi(argv[4]) : 0;
    const char *start_word = (argc == 6) ? argv[5] : NULL;

    if (strcmp(mode, "analysis") == 0) {
        int pipe1[2], pipe2[2];
        if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
            perror("Failed to create pipes");
            return EXIT_FAILURE;
        }

        printf("pipe1: %d %d, pipe2: %d %d ", pipe1[0], pipe1[1], pipe2[0], pipe2[1]);

        pid_t pidInput = create_input_process(inputFilePath, pipe1[1]);
        close(pipe1[1]);

        pid_t pidAnalysis = create_analysis_process(pipe1[0], pipe2[1]);
        close(pipe1[0]);
        close(pipe2[1]);

        wait_for_processes(pidInput, pidAnalysis, -1);

        FILE *outputFile = fopen(outputFilePath, "w");
        if (!outputFile) {
            perror("Failed to open output file");
            return EXIT_FAILURE;
        }

        char buffer[1024];
        ssize_t bytesRead;
        while ((bytesRead = read(pipe2[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytesRead] = '\0';
            fputs(buffer, outputFile);
        }

        fclose(outputFile);
        close(pipe2[0]);

        return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}
