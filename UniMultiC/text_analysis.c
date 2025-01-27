#include "text_analysis.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <math.h>

#define HASH_SIZE 997 // dimensione predefinita della tabella hash

/*
 * determina se un carattere è valido per comporre una parola
 * accetta lettere dell'alfabeto e l'apostrofo
 *
 * parametri
 *   c: carattere da valutare
 *
 * ritorno
 *   restituisce 1 (true) se il carattere è una lettera o un apostrofo, altrimenti 0 (false)
 */
int is_valid_character(char c) {
    return (isalpha(c) || (unsigned char)c >= 128);  // include l'apostrofo come parte di una parola
}

/*
 * formatta la frequenza in una stringa con precisione a quattro cifre decimali
 *
 * parametri
 *   frequency: valore float della frequenza da formattare
 *
 * ritorno
 *   restituisce una stringa contenente la frequenza formattata
 */
char *format_frequency(float frequency) {
    static char formatted[10];
    if (frequency >= 0.9999) {
        sprintf(formatted, "1");
    } else {
        sprintf(formatted, "%.4f", frequency); // limita a quattro cifre decimali
    }
    return formatted;
}

/*
 * funzione hash per generare un indice basato sulla stringa data
 *
 * parametri
 *   str: stringa da cui generare l'hash
 *
 * ritorno
 *   restituisce l'indice hash calcolato, che può essere utilizzato per localizzare un bucket in una tabella hash
 */
unsigned long hash(const char *str) {
    unsigned long hash = 5381; // valore iniziale dell'hash
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash % HASH_SIZE;
}

/*
 * inizializza una tabella di word table con una data dimensione
 * alloca memoria per ciascun bucket della tabella
 *
 * parametri
 *   table: puntatore alla struttura WordTable da inizializzare
 *   size: dimensione della tabella di hash (numero di buckets)
 *
 * ritorno
 *   nessun valore di ritorno esplicito
 */
void init_word_table(WordTable *table, size_t size) {
    printf("size %zu", size);
    table->size = size;
    table->buckets = malloc(size * sizeof(WordNode*)); // alloca memoria per i buckets
    if (!table->buckets) {
        fprintf(stderr, "Memory allocation failed for buckets\n");
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < size; i++) {
        table->buckets[i] = NULL;
    }
    printf("size %zu,%p", table->size, (void*)table->buckets);
}

/*
 * analizza il testo da un file di input, estraendo e processando ogni parola
 * gestisce la prima e l'ultima parola per eventuali collegamenti iniziali e finali
 *
 * parametri
 *   inputFile: puntatore al file da cui leggere il testo
 *   table: puntatore alla tabella delle parole per memorizzare le frequenze
 *   firstWord: doppio puntatore alla prima parola del testo
 *   lastWord: doppio puntatore all'ultima parola processata
 *
 * ritorno
 *   nessun valore di ritorno; i risultati sono memorizzati direttamente nelle strutture dati fornite
 */
void analyze_text(FILE *inputFile, WordTable *table, char **firstWord, char **lastWord) {
    char word[256] = {0};
    char c;
    int idx = 0;
    *firstWord = find_first_word(inputFile);
    *lastWord = NULL;
    char previousWord[256] = {0};

    while ((c = fgetc(inputFile)) != EOF) {
        if (is_valid_character(c)) {
            word[idx++] = tolower((unsigned char)c); // aggiunge il carattere alla parola in minuscolo
        } else if (c == '\'') {
            if (idx > 0) {
                word[idx++] = c; // include l'apostrofo se è preceduto da una lettera
                word[idx] = '\0';
                if (*firstWord == NULL) {
                    *firstWord = strdup(word);
                    if (!*firstWord) {
                        fprintf(stderr, "Memory allocation failed for firstWord\n");
                        exit(EXIT_FAILURE);
                    }
                }
                if (*lastWord != NULL) {
                    add_word(table, *lastWord, word);
                }
                strcpy(previousWord, word);
                free(*lastWord);
                *lastWord = strdup(word);
                if (!*lastWord) {
                    fprintf(stderr, "Memory allocation failed for lastWord\n");
                    exit(EXIT_FAILURE);
                }
                idx = 0;
            }
        } else if (!isspace(c) && c != '.' && c != '?' && c != '!') {
            // Ignora altri caratteri non validi per delimitare le parole
        } else {
            if (idx > 0) {
                word[idx] = '\0';
                if (*firstWord == NULL) {
                    *firstWord = strdup(word);
                    if (!*firstWord) {
                        fprintf(stderr, "Memory allocation failed for firstWord\n");
                        exit(EXIT_FAILURE);
                    }
                }
                if (*lastWord != NULL) {
                    add_word(table, *lastWord, word);
                }
                strcpy(previousWord, word);
                free(*lastWord);
                *lastWord = strdup(word);
                if (!*lastWord) {
                    fprintf(stderr, "Memory allocation failed for lastWord\n");
                    exit(EXIT_FAILURE);
                }
                idx = 0;
            }
            if (c == '.' || c == '?' || c == '!') {
                word[0] = c;
                word[1] = '\0';
                if (*lastWord != NULL) {
                    add_word(table, previousWord, word);
                }
                free(*lastWord);
                *lastWord = strdup(word);
                if (!*lastWord) {
                    fprintf(stderr, "Memory allocation failed for lastWord\n");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }

    if (idx > 0) {
        word[idx] = '\0';
        if (*firstWord == NULL) {
            *firstWord = strdup(word);
            if (!*firstWord) {
                fprintf(stderr, "Memory allocation failed for firstWord\n");
                exit(EXIT_FAILURE);
            }
        }
        if (*lastWord != NULL) {
            add_word(table, *lastWord, word);
        }
        free(*lastWord);
        *lastWord = strdup(word);
        if (!*lastWord) {
            fprintf(stderr, "Memory allocation failed for lastWord\n");
            exit(EXIT_FAILURE);
        }
    }

    // collega l'ultima parola con la prima parola trovata
    if (*firstWord && *lastWord) {
        add_word(table, *lastWord, *firstWord);
    }
}

/*
 * calcola e assegna le frequenze relative per tutti i successori di un dato nodo
 * le frequenze relative sono calcolate come il rapporto tra la frequenza di un successore
 * e la somma delle frequenze di tutti i successori del nodo
 *
 * parametri
 *   node: puntatore al nodo WordNode da cui calcolare le frequenze relative
 *
 * ritorno
 *   nessun valore di ritorno esplicito. la funzione modifica direttamente i nodi successori
 *   aggiornando il loro campo 'relative_frequency' con il valore calcolato
 *
 */
void calculate_relative_frequencies(WordNode *node) {
    if (!node || !node->successors) return;

    SuccessorNode *snode = node->successors;
    //printf("%s",snode->word);
    int total = 0;
    while (snode) {
        total += snode->frequency; // somma tutte le frequenze dei successori
        snode = snode->next;
    }

    snode = node->successors;
    while (snode) {
        snode->relative_frequency = (float) snode->frequency / total; // calcola la frequenza relatia
        snode = snode->next;
    }
}

/*
 * aggiunge una coppia di parole (attuale e successiva) alla tabella delle frequenze
 *
 * parametri
 *   table: Puntatore alla tabella delle parole
 *   word: Parola corrente
 *   next_word: Prossima parola dopo la corrente
 *
 * ritorno
 *   nessun valore di ritorno esplicito. la funzione aggiorna la tabella delle frequenze
 */
void add_word(WordTable *table, const char *word, const char *next_word) {
    if (word == NULL || next_word == NULL) return;

    //printf("%s %s",word, next_word);

    unsigned long index = hash(word); // calcola l'indice hash per la parola
    WordNode *node = table->buckets[index];

    while (node != NULL && strcmp(node->word, word) != 0) {
        node = node->next;
    }
    if (node == NULL) {
        node = malloc(sizeof(WordNode));
        if (!node) {
            fprintf(stderr, "Memory allocation failed for WordNode\n");
            exit(EXIT_FAILURE);
        }
        node->word = strdup(word);
        if (!node->word) {
            fprintf(stderr, "Memory allocation failed for word in WordNode\n");
            exit(EXIT_FAILURE);
        }
        node->successors = NULL;
        node->next = table->buckets[index];
        table->buckets[index] = node;
    }

    SuccessorNode *snode = node->successors;
    while (snode != NULL && strcmp(snode->word, next_word) != 0) {
        snode = snode->next;
    }
    if (snode == NULL) {
        snode = malloc(sizeof(SuccessorNode));
        if (!snode) {
            fprintf(stderr, "Memory allocation failed for SuccessorNode\n");
            exit(EXIT_FAILURE);
        }
        snode->word = strdup(next_word);
        if (!snode->word) {
            fprintf(stderr, "Memory allocation failed for word in SuccessorNode\n");
            exit(EXIT_FAILURE);
        }
        snode->frequency = 1;
        snode->next = node->successors;
        node->successors = snode;
    } else {
        snode->frequency++; // incrementa la frequenza del successore
    }
}

/*
 * libera tutte le risorse allocate dalla tabella delle parole
 *
 * parametri
 *   table: Puntatore alla tabella delle parole da liberare
 *
 * ritorno
 *   nessun valore di ritorno. la funzione ha il compito di liberare la memoria
 */
void free_word_table(WordTable *table) {
    for (size_t i = 0; i < table->size; i++) {
        WordNode *node = table->buckets[i];
        while (node) {
            WordNode *tmp = node;
            node = node->next;

            SuccessorNode *snode = tmp->successors;
            while (snode) {
                SuccessorNode *stmp = snode;
                snode = snode->next;
                free(stmp->word);
                free(stmp);
            }

            free(tmp->word);
            free(tmp);
        }
    }
    free(table->buckets);
}

/*
 * stampa la tabella delle parole e delle frequenze relative su un file
 *
 * parametri
 *   table: Puntatore alla tabella delle parole
 *   file: Puntatore al file su cui scrivere
 *   firstWord: Prima parola del testo per uso specifico nel formato di output
 *
 * ritorno
 *   nessun valore di ritorno. i risultati sono direttamente scritti sul file fornito
 */
void print_word_table(const WordTable *table, FILE *file, const char *firstWord) {
    for (size_t i = 0; i < table->size; i++) {
        WordNode *node = table->buckets[i];
        while (node) {
            calculate_relative_frequencies(node); // calcola le frequenze relative per i successori del nodo
            SuccessorNode *snode = node->successors;
            if (snode) {
                fprintf(file, "%s", node->word);
                printf("Node: %s\n", node->word);  // Debug: mostra la parola corrente
                while (snode) {
                    fprintf(file, ",%s,%s", snode->word, format_frequency(snode->relative_frequency));
                    printf("Successor: %s, Frequency: %s\n", snode->word, format_frequency(snode->relative_frequency));  // Debug: mostra il successore e la frequenza
                    snode = snode->next;
                }
                fprintf(file, "\n");
            }
            node = node->next;
        }
    }
    fflush(file);  // Ensure all data is written to the file
}


char* find_first_word(FILE *file) {
    char buffer[256];
    char *token = NULL;
    char *first = NULL;

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        token = strtok(buffer, " \t\n");
        while (token != NULL) {
            char temp[256];
            int idx = 0;
            for (int i = 0; token[i] != '\0'; i++) {
                if (token[i] == '\'') {
                    temp[idx++] = token[i];
                    temp[idx] = '\0';
                    first = malloc(strlen(temp) + 1);
                    if (first != NULL) {
                        strcpy(first, temp);
                        for (char *p = first; *p; ++p) {
                            *p = tolower((unsigned char)*p);
                        }
                        rewind(file);
                        return first;
                    } else {
                        fprintf(stderr, "Allocazione memoria fallita\n");
                        exit(EXIT_FAILURE);
                    }
                } else {
                    temp[idx++] = token[i];
                }
            }
            if (idx > 0) {
                temp[idx] = '\0';
                first = malloc(strlen(temp) + 1);
                if (first != NULL) {
                    strcpy(first, temp);
                    for (char *p = first; *p; ++p) {
                        *p = tolower((unsigned char)*p);
                    }
                    rewind(file);
                    return first;
                } else {
                    fprintf(stderr, "Allocazione memoria fallita\n");
                    exit(EXIT_FAILURE);
                }
            }
            token = strtok(NULL, " \t\n");
        }
    }
    rewind(file);
    return first;
}

char* find_last_token(FILE *file) {
    char *token;
    char *last = NULL;
    char buffer[30];

    // cerchiamo la parola
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        token = strtok(buffer, " \t\n");
        while (token != NULL) {
            free(last); // libera la memoria precedentemente allocata
            size_t len = strlen(token);
            last = malloc(len + 1);
            if (last != NULL) {
                strcpy(last, token);
            } else {
                fprintf(stderr, "allocazione memoria fallita\n");
                exit(EXIT_FAILURE);
            }
            token = strtok(NULL, " \t\n");
        }
    }

    // altrimenti la punteggiatura
    if (last != NULL && ispunct(last[strlen(last) - 1])) {
        char* punct = malloc(2);
        if (punct == NULL) {
            fprintf(stderr, "allocazione memoria fallita\n");
            exit(EXIT_FAILURE);
        }
        punct[0] = last[strlen(last) - 1];
        punct[1] = '\0';
        free(last);
        last = punct;
    }

    rewind(file); // riavvolge il file per permettere altre letture
    return last;
}


