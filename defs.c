#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "defs.h"
#include "data.h"
#include "clientefs.h"
#include "cidade.h"
#include "roteiro.h"
#include "passeio.h"
#include "tags.h"

char *recebe_string()
{
	int pos_string= 0, tamanho = 1;
	char *nome = malloc(tamanho * sizeof(char));
	char c;

	while(1) {
        c = getchar();
		if(c == '\n'){
			break;
		}
		tamanho++;
		nome = realloc(nome, tamanho * sizeof(char));
		nome[pos_string] = c;
		pos_string++;
	}
	return nome;
}

void listar_cidades_e_clientes(struct cidade *base)
{
	for(int i = 1;i <= base -> count_cidades;i++){
		struct cidade *tmp = buscar_cidade_index(base,i);
		listar_clientes(tmp);		
	}
}

struct tag *tags;