#ifndef PROCESS_MANAGEMENT_H
#define PROCESS_MANAGEMENT_H

#include <unistd.h>
#include "text_analysis.h"
#include "text_generation.h"

// crea un processo di input che legge un file
pid_t create_input_process(const char *inputFilePath, int output_fd);

// crea un processo di analisi del testo
pid_t create_analysis_process(int input_fd, int output_fd);

// crea un processo generatore di testo
pid_t create_generate_process(const char *csvFilePath, const char *outputFilePath, int num_words, const char *start_word);

// attende la terminazione dei processi
void wait_for_processes(pid_t inputPid, pid_t analysisPid, pid_t generatePid);

#endif // PROCESS_MANAGEMENT_H
