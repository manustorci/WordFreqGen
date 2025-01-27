#include "process_management.h"
#include "utilities.h"
#include "text_analysis.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

pid_t create_input_process(const char *inputFilePath, int output_fd) {
    pid_t pid = fork();
    if (pid == 0) {
        dup2(output_fd, STDOUT_FILENO);
        close(output_fd);

        execlp("cat", "cat", inputFilePath, NULL);
        perror("Failed to execute input process");
        exit(EXIT_FAILURE);
    }
    close(output_fd);
    return pid;
}

pid_t create_analysis_process(int input_fd, int output_fd) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork fallita");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        printf("processo figlio creato %d \n",getpid());
        printf("prima input fd %d, output %d",input_fd,output_fd);

        //dup2(input_fd, STDIN_FILENO);
        if (dup2(input_fd,STDIN_FILENO) < 0) {
            perror("dup input fallita");
            fprintf(stderr,"dup in fallita");
            exit(EXIT_FAILURE);
        }
        //dup2(output_fd, STDOUT_FILENO);
        if (dup2(output_fd,STDOUT_FILENO) < 0) {
            perror("dup output fallita");
            fprintf(stderr,"dup out fallita");
            exit(EXIT_FAILURE);
        }

        printf("dopo dup2");
        close(input_fd);
        close(output_fd);

        WordTable table;
        printf("prima di init word");
        init_word_table(&table, 1000);
        printf("dopo di init word");

        FILE *inputStream = fdopen(STDIN_FILENO, "r");
        if (!inputStream) {
            perror("errore nell aprire input stream");
            exit(EXIT_FAILURE);
        }

        char *firstWord = NULL;
        char *lastWord = NULL;
        analyze_text(inputStream, &table, &firstWord, &lastWord);
        fclose(inputStream);

        FILE *outputStream = fdopen(STDOUT_FILENO, "w");
        if (!outputStream) {
            perror("errore nell aprire output stream");
            exit(EXIT_FAILURE);
        }
        print_word_table(&table, outputStream, firstWord);
        fflush(outputStream);
        fclose(outputStream);

        free_word_table(&table);
        free(firstWord);
        free(lastWord);

        exit(EXIT_SUCCESS);
    }
    close(input_fd);
    close(output_fd);
    return pid;
}

pid_t create_generate_process(const char *csvFilePath, const char *outputFilePath, int num_words, const char *start_word) {
    pid_t pid = fork();
    if (pid == 0) {
        char num_words_str[10];
        sprintf(num_words_str, "%d", num_words);

        if (start_word) {
            execlp("./generate_text", "./generate_text", csvFilePath, outputFilePath, num_words_str, start_word, NULL);
        } else {
            execlp("./generate_text", "./generate_text", csvFilePath, outputFilePath, num_words_str, NULL);
        }

        perror("Failed to execute generate process");
        exit(EXIT_FAILURE);
    }
    return pid;
}

void wait_for_processes(pid_t inputPid, pid_t analysisPid, pid_t generatePid) {
    int status;
    waitpid(inputPid, &status, 0);
    waitpid(analysisPid, &status, 0);
    if (generatePid != -1) {
        waitpid(generatePid, &status, 0);
    }
}
