#include "text_analysis.h"
#include "text_generation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

/*
 * programma principale per l'analisi e la generazione di testo
 *
 * parametri
 *   argc: conteggio degli argomenti
 *   argv: array di argomenti
 *
 * ritorno
 *   ritorna 0 se l'esecuzione è terminata con successo, 1 se c'è stato un errore
 */
int main(int argc, char *argv[]) {
    printf("Program started\n");

    srand(time(NULL)); // inizializza il generatore di numeri casuali

    // controllo minimo degli argomenti passati al programma
    if (argc < 2) {
        printf("Usage: %s <command> [options]\n", argv[0]);
        printf("Commands:\n");
        printf("  analyze <inputfile> <outputfile>\n");
        printf("  generate <inputfile> <outputfile> <wordcount> [startword]\n");
        return 1;
    }

    const char *command = argv[1]; // legge il comando dal primo argomento

    if (strcmp(command, "analyze") == 0 && argc == 4) {
        // gestisce il comando "analyze" per analizzare un testo
        FILE *inputFile = fopen(argv[2], "r"); // apertura del file di input per la lettura
        if (!inputFile) {
            perror("Failed to open input file");
            return 1;
        }

        FILE *outputFile = fopen(argv[3], "w"); // apertura del file di output per scrittura
        if (!outputFile) {
            perror("Failed to open output file");
            fclose(inputFile);
            return 1;
        }


        WordTable table;
        char *firstWord = NULL;
        char *lastWord = NULL;
        init_word_table(&table, HASH_SIZE); // inizializza la tabella delle parole

        analyze_text(inputFile, &table, &firstWord, &lastWord); // analizza il testo e popola la tabella
        print_word_table(&table, outputFile, firstWord); // stampa la tabella delle parole nel file di output

        // pulizia e chiusura delle risorse
        free_word_table(&table);
        free(firstWord);
        free(lastWord);
        fclose(inputFile);
        fclose(outputFile);

    } else if (strcmp(command, "generate") == 0 && argc >= 5) {
        // gestisce il comando "generate" per generare testo basato sulla frequenza delle parole
        int wordCount = atoi(argv[4]); // numero di parole da generare
        if (wordCount <= 0) {
            fprintf(stderr, "Invalid number of words to generate: %s\n", argv[4]);
            return 1;
        }

        FrequencyNode *head = NULL;
        init_frequency_list(&head); // inizializza la lista delle frequenze
        if (!load_frequency_list_from_csv(argv[2], &head)) { // carica la lista delle frequenze dal file csv
            fprintf(stderr, "Failed to load frequency list from file: %s\n", argv[2]);
            return 1;
        }

        FILE *outputFile = fopen(argv[3], "w"); // apertura del file di output per scrittura
        if (!outputFile) {
            perror("Failed to open output file");
            free_frequency_list(head);
            return 1;
        }

        // seleziona la prima e la parola di partenza per la generazione del testo
        char *currentWord;
        //char *originalFirstWord = NULL;
        char *startWord = NULL;

        // gestion della parola di partenza per la generazione del testo
        if (argc == 6) {
            startWord = to_lowercase(argv[5]);
            currentWord = strdup(startWord);
            if (!word_exists_in_frequency_list(head, currentWord)) {
                fprintf(stderr, "La parola inserita non è presenta nel testo: %s\n", currentWord);
                free(currentWord);
                free(startWord);
                free_frequency_list(head);
                fclose(outputFile);
                return 1;
            }
        } else {
            currentWord = select_random_initial_word(head);
            if (!currentWord) {
                fprintf(stderr, "Failed to select initial word\n");
                free_frequency_list(head);
                fclose(outputFile);
                return 1;
            }
            startWord = strdup(currentWord);
        }


        printf("Starting with word: %s\n", currentWord);
        int isNewSentence = 1;

        // capitalizzazione della prima parola del nuovo testo, se necessario
        if (isNewSentence) {
            currentWord[0] = toupper(currentWord[0]);
        }
        fprintf(outputFile, "%s ", currentWord);
        isNewSentence = 0;

        // generazione delle parole fino al raggiungimento del conteggio desiderato
        for (int i = 1; i < wordCount; i++) {
            char *word = generate_random_word(head, to_lowercase(currentWord));
            if (word) {
                if (isNewSentence) {
                    word[0] = toupper(word[0]);
                }
                fprintf(outputFile, "%s ", word);
                if (strcmp(word, ".") == 0 || strcmp(word, "!") == 0 || strcmp(word, "?") == 0) {
                    isNewSentence = 1;
                } else {
                    isNewSentence = 0;
                }
                free(currentWord);
                currentWord = to_lowercase(word);
                free(word);
            } else {
                fprintf(stderr, "Generated word is NULL.\n");
                break;
            }
        }

        // chiusura delle risorse dopo la generazione del testo
        fclose(outputFile);
        free(currentWord);
        free(startWord);
        free_frequency_list(head);

    } else {
        printf("Invalid command or number of arguments.\n");
        return 1;
    }

    return 0;
}
