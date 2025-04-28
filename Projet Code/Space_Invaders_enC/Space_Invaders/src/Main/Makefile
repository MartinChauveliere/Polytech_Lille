CC=clang
TARGET=Jeu
CFLAGS=-g -W -Wall -Wextra
LDFLAGS=-I Graphique -l graph -L ../Graphique -l SDL -l SDL_ttf

default: $(TARGET)

main.o : main.c
	clang $(CFLAGS) -c main.c
	
Liste.o : ../ListeC/Liste.c ../ListeC/Liste.h
	clang $(CFLAGS) -c ../ListeC/Liste.c

Monstre.o : ../Monstre/Monstre.c ../Monstre/Monstre.h
	clang $(CFLAGS) -c ../Monstre/Monstre.c
	
Interactif.o : ../Interactif/Interactif.c ../Interactif/Interactif.h 
	clang $(CFLAGS) -c ../Interactif/Interactif.c
	
init.o : init.c init.h
	clang $(CFLAGS) -c init.c


	
	
$(TARGET): Liste.o main.o Monstre.o Interactif.o init.o
	clang main.o Liste.o Monstre.o Interactif.o init.o -o $(TARGET) $(LDFLAGS)

.PHONY: clean
clean:
	rm -f *.o
	rm -f $(TARGET)

tidy : main.c ../ListeC/Liste.c ../Monstre/Monstre.c ../Interactif/Interactif.c init.c
	$(CC)-tidy  main.c ../ListeC/Liste.c ../Monstre/Monstre.c ../Interactif/Interactif.c init.c --checks="readability-*" -header-filter=.*
	
format : 
	$(CC)-format -style='Microsoft' main.c ../ListeC/Liste.c ../Monstre/Monstre.c ../Interactif/Interactif.c init.c

