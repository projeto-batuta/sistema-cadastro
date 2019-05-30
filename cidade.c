#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#ifndef DEFS
#define DEFS
#include "defs.h"
#include "data.h"
#include "clientefs.h"
#include "cidade.h"
#include "roteiro.h"
#include "passeio.h"
#include "tags.h"
#endif

struct cidade *criar_cidade(char *nome)
{
	struct cidade *nova_cidade = (struct cidade*)
		malloc(sizeof(struct cidade));
	nova_cidade -> nome = nome;
	nova_cidade -> clientes = NULL;
	nova_cidade -> last_cliente = NULL;
	nova_cidade -> roteiros = NULL;
	nova_cidade -> next = NULL;
	return nova_cidade;
}


void set_cidade_nome(struct cidade *cidade_atual,char *nome)
{
	cidade_atual -> nome = nome;
}


void set_cidade_last_cliente(struct cidade *cidade_atual,
	struct cliente *last)
{
	cidade_atual -> last_cliente = last;
}

void set_cidade_next(struct cidade *cidade_atual,struct cidade *cidade_add)
{
	cidade_atual -> next = cidade_add;
}

char *get_cidade_nome(struct cidade *cidade_atual)
{
	return cidade_atual -> nome;
}

void inserir_cidade(struct cidade *cidade_base,struct cidade *cidade_nova)
{
	struct cidade *pont_temp = cidade_base;
	if (pont_temp -> next == NULL) pont_temp -> next = cidade_nova;
	else {
		while (pont_temp -> next != NULL) 
			pont_temp = pont_temp -> next;
		pont_temp -> next = cidade_nova;
	}
	// cidades_cont++;
}

void listar_cidades(struct cidade *cidades)
{	
	struct cidade *tmp = cidades;
	printf("\nCidades cadastradas:\n");
	while(tmp != NULL)
	{
		printf("- %s\n",get_cidade_nome(tmp));
		tmp = tmp -> next;
	}
}