#ifndef TEXT_GENERATION_H
#define TEXT_GENERATION_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// struttura per un nodo nella lista di frequenza delle parole
typedef struct FrequencyNode {
    char *currentWord;
    char *nextWord;
    int frequency;
    struct FrequencyNode *next;
} FrequencyNode;

// inizializza una lista di frequenza
void init_frequency_list(FrequencyNode **head);

// aggiunge una coppia di parole alla lista di frequenza
void add_to_frequency_list(FrequencyNode **head, const char *currentWord, const char *nextWord, float frequency);

//genera una parola casuale basata sulla parola corrente
char *generate_random_word(const FrequencyNode *head, const char *currentWord);

// libera tutte le risorse allocate dalla lista di frequenza
void free_frequency_list(FrequencyNode *head);

// carica la lista delle frequenze da un file csv
int load_frequency_list_from_csv(const char *filename, FrequencyNode **head);

// converte una stringa in minuscolo
char *to_lowercase(const char *str);

// seleziona una parola iniziale casuale per iniziare la generazione del testo
char *select_random_initial_word(FrequencyNode *head);

// verifica se una parola esiste nella lista delle frequenze
int word_exists_in_frequency_list(FrequencyNode *head, const char *word);

#endif // TEXT_GENERATION_H
