CC = gcc

objects = main.o cidade.o clientefs.o data.o passeio.o roteiro.o tags.o defs.o session.o

LINKERFLAG = -Wall

sistema_cadastro: $(objects)
	$(CC) -o sistema_cadastro $(objects)

debug_cadastro:  $(objects)
	$(CC) -g sistema_cadastro $(objects)

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

defs.o: defs.c defs.h
	$(CC) -c defs.c

session.o: session.c session.h
	$(CC) -c session.c

clean:
	@echo "Cleaning up..."
	rm -rvf *.o sistema_cadastro