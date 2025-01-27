#include "text_generation.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
 * inizializza la lista delle frequenze impostando il suo puntatore a NULL
 *
 * parametri
 *   head: doppio puntatore alla testa della lista delle frequenze
 */
void init_frequency_list(FrequencyNode **head) {
    *head = NULL;
}

/*
 * aggiunge un nuovo nodo alla lista delle frequenze
 *
 * parametri
 *   head: doppio puntatore alla testa della lista delle frequenze
 *   currentWord: parola corrente (stringa)
 *   nextWord: parola successiva (stringa)
 *   frequency: frequenza associata come float, viene convertita e memorizzata come intero
 *
 * descrizione
 *   crea un nuovo nodo, alloca la memoria necessaria e lo inizializza con le parole
 *   e la frequenza data. inserisce il nodo all'inizio della lista
 */
void add_to_frequency_list(FrequencyNode **head, const char *currentWord, const char *nextWord, float frequency) {
    FrequencyNode *new_node = malloc(sizeof(FrequencyNode));
    if (!new_node) {
        fprintf(stderr, "Memory allocation failed for new_node\n");
        exit(EXIT_FAILURE);
    }
    new_node->currentWord = strdup(currentWord);
    new_node->nextWord = strdup(nextWord);
    new_node->frequency = (int)(frequency * 100); // converte la frequenza in intero (moltiplicato per 100)
    new_node->next = *head;
    *head = new_node;

    // debug print
    //printf("Added to frequency list: %s -> %s (%d)\n", currentWord, nextWord, new_node->frequency);
}

/*
 * genera una parola casuale basata sulla frequenza e la parola corrente
 *
 * parametri
 *   head: puntatore alla testa della lista delle frequenze
 *   currentWord: la parola corrente da cui generare la successiva
 *   originalFirstWord: la prima parola del testo, usata per iniziare di nuovo se necessari
 *
 * ritorno
 *   ritorna la parola generata come stringa duplicata
 */
char *generate_random_word(const FrequencyNode *head, const char *currentWord) {
    if (!head) {
        //fprintf(stderr, "The frequency list is empty.\n");
        return NULL; // se la lista delle frequenze è vuota, ritorna NULL
    }

    int total = 0;
    const FrequencyNode *node;
    const FrequencyNode *nodes[100];
    int frequencies[100];
    int count = 0;

    for (node = head; node; node = node->next) {
        if (strcmp(node->currentWord, currentWord) == 0) {
            nodes[count] = node;
            frequencies[count] = node->frequency;
            total += node->frequency;
            count++;
        }
    }

    int r = rand() % total; // genera un numero casuale
    int cumulative = 0;

    for (int i = 0; i < count; i++) {
        cumulative += frequencies[i];
        if (r < cumulative) {
            return strdup(nodes[i]->nextWord);
        }
    }

    //fprintf(stderr, "No word selected, this should not happen.\n");
    return NULL;
}

/*
 * libera tutta la memoria allocata dalla lista delle frequenze
 *
 * parametri
 *   head: puntatore alla testa della lista delle frequenze
 */
void free_frequency_list(FrequencyNode *head) {
    while (head != NULL) {
        FrequencyNode *tmp = head;
        head = head->next;
        free(tmp->currentWord);
        free(tmp->nextWord);
        free(tmp);
    }
}

/*
 * converte una stringa in minuscolo
 *
 * parametri
 *   str: puntatore alla stringa originale
 *
 * ritorno
 *   ritorna la stringa convertita in minuscolo
 */
char *to_lowercase(const char *str) {
    char *lower_str = strdup(str);
    for (int i = 0; lower_str[i]; i++) {
        lower_str[i] = tolower(lower_str[i]); // converte ogni carattere in minuscolo
    }
    return lower_str;
}

/*
 * carica una lista delle frequenze da un file csv
 *
 * parametri
 *   filename: nome del file da cui caricare la lista
 *   head: doppio puntatore alla testa della lista delle frequenze
 *
 * ritorno
 *   ritorna 1 se il caricamento ha successo, altrimenti 0
 */
int load_frequency_list_from_csv(const char *filename, FrequencyNode **head) {
    FILE *file = fopen(filename, "r"); // apre il file CSV per la lettura
    if (!file) {
        fprintf(stderr, "Unable to open the CSV file: %s\n", filename);
        return 0;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        char *currentWord = strtok(line, ",");
        if (!currentWord) continue;
        char *lowerCurrentWord = to_lowercase(currentWord);

        while (1) {
            char *nextWord = strtok(NULL, ",");
            if (!nextWord) break;

            char *freqStr = strtok(NULL, ",\n");
            if (!freqStr) break;

            float frequency = atof(freqStr);
            if (frequency > 0) {
                add_to_frequency_list(head, lowerCurrentWord, nextWord, frequency); // aggiunge la parola e la frequenza alla lista
            } else {
                fprintf(stderr, "Invalid frequency '%s' for words '%s, %s'\n", freqStr, currentWord, nextWord);
            }
        }

        free(lowerCurrentWord);
    }

    fclose(file); // chiude il file CSV
    return 1;
}

/*
 * seleziona una parola iniziale casuale dalla lista delle frequenze
 *
 * parametri
 *   head: puntatore alla testa della lista delle frequenze
 *
 * ritorno
 *   ritorna la parola iniziale scelta
 */
char *select_random_initial_word(FrequencyNode *head) {
    const char *initialPunctuations[] = {".", "?", "!"}; // punteggiature iniziali per identificare le parole iniziali
    char *initialWords[100];
    int initialCount = 0;

    for (FrequencyNode *node = head; node; node = node->next) {
        for (int i = 0; i < 3; i++) {
            if (strcmp(node->currentWord, initialPunctuations[i]) == 0) {
                initialWords[initialCount++] = strdup(node->nextWord);
            }
        }
    }

    if (initialCount == 0) {
        fprintf(stderr, "No initial words found\n");
        return NULL;
    }

    //printf("Initial words list:\n");
    for (int i = 0; i < initialCount; i++) {
        printf("%s\n", initialWords[i]);
    }

    int randomIndex = rand() % initialCount;
    //printf("Selected initial word: %s\n", initialWords[randomIndex]);
    return initialWords[randomIndex];
}

/*
 * verifica se una parola esiste nella lista delle frequenze
 *
 * parametri
 *   head: puntatore alla testa della lista delle frequenze
 *   word: la parola da cercare
 *
 * ritorno
 *   ritorna 1 se la parola esiste nella lista, altrimenti 0
 */
int word_exists_in_frequency_list(FrequencyNode *head, const char *word) {
    for (FrequencyNode *node = head; node; node = node->next) {
        if (strcmp(node->currentWord, word) == 0) {
            return 1;
        }
    }
    return 0;
}
