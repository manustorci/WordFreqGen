/*
 * Contiene funzioni ausiliarie, come quelle per la manipolazione
 * delle stringhe e altre operazioni comuni
 */
#include "utilities.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * converte tutti i caratteri di una stringa in minuscolo
 *
 * parametri
 *   str: puntatore a caratteri della stringa da convertire
 *
 * descrizione
 *   La funzione attraversa ogni carattere della stringa data,
 *   convertendolo in minuscolo utilizzando la funzione tolower().
 *   si ferma se il puntatore è NULL per prevenire errori
 */
void strtolower(char *str) {
    if (str == NULL) return;
    for (; *str; ++str) *str = tolower((unsigned char)*str);
}

/*
 * verifica se un carattere è un segno di punteggiatura che può terminare una frase
 *
 * parametri
 *   str: puntatore a caratteri che rappresenta il simbolo da verificare
 *
 * ritorno
 *   ritorna 1 (true) se il carattere è un segno di punteggiatura che termina una frase,
 *   altrimenti 0 (false)
 *
 * descrizione
 *   la funzione controlla se il carattere fornito è uno tra punto, punto interrogativo
 *   o punto esclamativo
 */
int is_punctuation(const char *str) {
    static const char *punctuations = ".?!";
    return (str != NULL && strlen(str) == 1 && strchr(punctuations, *str) != NULL);
}
/*
 * stampa un messaggio di errore e termina il programma
 *
 * parametri
 *   message: stringa contenente il messaggio di errore da visualizzare
 *
 * descrizione
 *   questa funzione è usata per gestire gli errori, stampando un messaggio
 *   di errore specifico sulla console e terminando
 *   l'esecuzione del programma con uno stato di uscita di errore
 */
void error_exit(const char *message) {
    fprintf(stderr, "Error: %s\n", message);
    exit(EXIT_FAILURE);
}