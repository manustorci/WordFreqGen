/*
 * header file per utilities.c
 */
#ifndef UTILITIES_H
#define UTILITIES_H

#include <stddef.h>

// funzione per convertire una stringa in minuscolo
void toLowerCase(char *str);

// funzione per controllare se un carattere è un delimitatore di frase
int isSentenceDelimiter(char c);

// funzione di stampa di errori e uscita
void error_exit(const char *message);

#endif // UTILITIES_H
