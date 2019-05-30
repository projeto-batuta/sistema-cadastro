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

void inserir_roteiro(struct cidade *cidade_base, struct roteiro *roteiro_novo)
{
	struct roteiro *aux = cidade_base -> roteiros;
	if(aux != NULL){
		while (aux -> next != NULL) aux = aux -> next;
		aux -> next = roteiro_novo;
	}
	else {
		cidade_base -> roteiros = roteiro_novo;
	}
	// roteiros_cont++;
}