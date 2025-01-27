CC=gcc
CFLAGS=-I. -Wall

# definire l'eseguibile
all: myprogram

# collegare gli oggetti per formare l'eseguibile
myprogram: main.o text_analysis.o text_generation.o
	$(CC) -o myprogram main.o text_analysis.o text_generation.o

# compilare i singoli file sorgente in oggetti
main.o: main.c
	$(CC) -c main.c $(CFLAGS)

text_analysis.o: text_analysis.c
	$(CC) -c text_analysis.c $(CFLAGS)

text_generation.o: text_generation.c
	$(CC) -c text_generation.c $(CGFLAGS)

# pulire i file oggetto e l'eseguibile
clean:
	rm -f *.o myprogram

