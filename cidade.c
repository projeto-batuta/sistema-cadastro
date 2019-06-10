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
	nova_cidade -> count_cidades = 0;
	nova_cidade -> count_clientes = 0;
	nova_cidade -> nome = nome;
	nova_cidade -> clientes = NULL;
	nova_cidade -> last_cliente = NULL;
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

int get_cidade_clientes_count(struct cidade *atual)
{
	return atual -> count_clientes;
}

int get_cidade_count(struct cidade *root)
{
	return root -> count_cidades;
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
	cidade_base -> count_cidades++;
}

void listar_cidades(struct cidade *cidades)
{	
	struct cidade *tmp = cidades -> next;
	printf("\nCidades cadastradas:\n");
	while(tmp != NULL)
	{
		printf("- %s\n",get_cidade_nome(tmp));
		tmp = tmp -> next;
	}
}

void listar_cidades_cadastro(struct cidade *cidades)
{	
	struct cidade *tmp = cidades -> next;
	printf("\nCidades cadastradas:\n");
	int cont = 1;
	while(tmp != NULL)
	{
		printf("[%d] - %s\n",cont,get_cidade_nome(tmp));
		tmp = tmp -> next;
		cont++;
	}
}

struct cidade *buscar_cidade_index(struct cidade *main,int i)
{
	struct cidade *result = NULL;
	struct cidade *pont_temp = main;
	int cont = 0;
	if(i <= main -> count_cidades)
	{
		while(pont_temp != NULL)
		{
			if(cont == i)
			{
				result = pont_temp;
			}
			pont_temp = pont_temp -> next;
			cont++;
		}
	}
	return result;
}

void limpar_cidades(struct cidade *cidade_root)
{
	struct cidade *cidade_temp = cidade_root;
	struct cidade *cidade_next;
	if(cidade_temp != NULL)
	{
		cidade_next = cidade_temp -> next;
		while (cidade_temp != NULL)
		{
			if(cidade_temp == cidade_root -> next) cidade_root -> next = NULL;
			limpar_clientes(cidade_temp);
			// limpar_roteiros(cidade_temp);
			free(cidade_temp);
			cidade_temp = cidade_next;
		}
	}
}
