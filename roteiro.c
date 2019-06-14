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

struct roteiro *criar_roteiro(char *nome)
{
	struct roteiro *novo_roteiro = (struct roteiro*)
		malloc(sizeof(struct roteiro));
	novo_roteiro -> nome = nome;
	novo_roteiro -> info = NULL;
	novo_roteiro -> duracao = data_base();
	novo_roteiro -> passeios = NULL;
	novo_roteiro -> next = NULL;
	return novo_roteiro;
}

void set_roteiro_nome(struct roteiro *roteiro_atual,char *nome)
{
	roteiro_atual -> nome = nome;
}

void set_roteiro_info(struct roteiro *roteiro_atual,char *info)
{
	roteiro_atual -> info = info;
}

void set_roteiro_duracao(struct roteiro *roteiro_atual,int dia,int hora,int min)
{
	roteiro_atual -> duracao.dia = dia;
	roteiro_atual -> duracao.hora = hora;
	roteiro_atual -> duracao.min = min;
}

void set_roteiro_last_passeio(struct roteiro *roteiro_atual, struct passeio *last)
{
	roteiro_atual -> last_passeio = last;
}

int get_roteiro_count(struct roteiro *roteiro_base)
{
	return roteiro_base -> count_passeios;
}

char *get_roteiro_nome(struct roteiro *roteiro_atual)
{
	return roteiro_atual -> nome; 
}

char *get_roteiro_info(struct roteiro *roteiro_atual)
{
	return roteiro_atual -> info;
}

struct data get_roteiro_duracao(struct roteiro *roteiro_atual) 
{
	return roteiro_atual -> duracao;
}

struct passeio *get_roteiro_passeios(struct roteiro *roteiro_base)
{
	return roteiro_base -> passeios;
}

void inserir_roteiro(struct roteiro *roteiro_base, struct roteiro *roteiro_novo)
{
	struct roteiro *aux = roteiro_base;
	while(aux -> next != NULL){
		aux = aux -> next;
	}
	aux -> next = roteiro_novo;
	roteiro_base -> count_passeios++;
}

void limpar_roteiros(struct roteiro *roteiro_base)
{
	if(roteiro_base != NULL){
		struct roteiro *aux = roteiro_base;
		if(roteiro_base -> next != NULL){
			aux -> duracao;
			struct roteiro *next = aux -> next;
			limpar_roteiros(next);
		}
		free(aux);
	}
}

void listar_roteiros(struct roteiro *roteiro_base)
{
	printf("\nRoteiros cadastrados:\n");
	int count = 0;
	if(roteiro_base != NULL){
		struct roteiro *aux = roteiro_base;
		while(aux != NULL){
			if(count > 0)
			{
			printf("[%d] - %s [Tempo: %d:%d]\n       %s\n",count,aux -> nome,
			 aux -> duracao.hora, aux -> duracao.min,aux ->info);
			}
			aux = aux -> next;
			count++;
		}
	}
}

struct roteiro *buscar_roteiro_id(struct roteiro *roteiro_base,int id)
{
	struct roteiro *result = NULL;
	if(roteiro_base -> count_passeios >= id)
	{
		int count = 0;
		struct roteiro *aux = roteiro_base;
		while(aux != NULL)
		{
			if(count == id)
				result = aux;
			aux = aux -> next;
			count++;
		}
	}
	return result;
}