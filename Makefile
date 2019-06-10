CC = gcc

LINKERFLAG = -Wall

sistema_cadastro: main.o cidade.o clientefs.o data.o passeio.o roteiro.o tags.o
	$(CC) -o sistema_cadastro main.o cidade.o clientefs.o data.o passeio.o roteiro.o tags.o

debug_cadastro:  main.o cidade.o clientefs.o data.o passeio.o roteiro.o tags.o
	$(CC) -g sistema_cadastro main.o cidade.o clientefs.o data.o passeio.o roteiro.o tags.o

main.o: main.c defs.h
	$(CC) -c main.c

tags.o: tags.c tags.h 
	$(CC) -c tags.c

roteiro.o: roteiro.c roteiro.h
	$(CC) -c roteiro.c

passeio.o: passeio.c passeio.h
	$(CC) -c passeio.c

clientefs.o: clientefs.c clientefs.h
	$(CC) -c clientefs.c

cidade.o: cidade.c cidade.h
	$(CC) -c cidade.c

data.o: data.c data.h
	$(CC) -c data.c

clean:
	@echo "Cleaning up..."
	rm -rvf *.o