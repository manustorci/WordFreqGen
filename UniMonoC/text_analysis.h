#ifndef TEXT_ANALYSIS_H
#define TEXT_ANALYSIS_H

#include <stdio.h>

// definisci la dimensione della tabella hash per la tabella delle parole
#define HASH_SIZE 997

// struttura per memorizzare una parola e la sua frequenza
typedef struct SuccessorNode {
    char *word;
    int frequency;
    float relative_frequency;
    struct SuccessorNode *next;
} SuccessorNode;

typedef struct WordNode {
    char *word;
    SuccessorNode *successors;
    struct WordNode *next;
} WordNode;

// struttura per la tabella delle parole
typedef struct WordTable {
    WordNode **buckets;
    size_t size;
} WordTable;

// inizializza la tabella delle parole
void init_word_table(WordTable *table, size_t size);

// aggiunge una parola alla tabella
void add_word(WordTable *table, const char *word, const char *next_word);

// libera la memoria utilizzata dalla tabella delle parole
void free_word_table(WordTable *table);

// stampa la tabella delle parole in un file CSV
void print_word_table(const WordTable *table, FILE *file, const char *firstWord);

// funzione per analizzare il testo e popolare la tabella delle parole
void analyze_text(FILE *inputFile, WordTable *table, char **firstWord, char **lastWord);

char* find_first_word(FILE *file);
char* find_last_token(FILE *file);

#endif // TEXT_ANALYSIS_H
