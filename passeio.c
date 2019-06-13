#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include "data.h"
#include "clientefs.h"
#include "cidade.h"
#include "roteiro.h"
#include "passeio.h"
#include "tags.h"
#include "session.h"

struct passeio *criar_passeio(int id)
{
	struct passeio *novo_passeio = (struct passeio*)
		malloc(sizeof(struct passeio));
	novo_passeio -> id = id;
	novo_passeio -> data_agenda = data_base();
	novo_passeio -> ativo = FALSE;
	novo_passeio -> next = NULL;
	novo_passeio -> prev = NULL;

	for(int i = 0;i<MAX_CLIENTES;i++)
	{
		novo_passeio -> clientes[i] = "";
	}
	return novo_passeio;
}

void set_passeio_id(struct passeio *passeio_atual,int id)
{
	passeio_atual -> id = id;
}

void set_passeio_agenda(struct passeio *passeio_atual,int ano,int mes,int dia,
	int hora,int min)
{
	passeio_atual -> data_agenda.ano = ano;
	passeio_atual -> data_agenda.mes = mes;
	passeio_atual -> data_agenda.dia = dia;
	passeio_atual -> data_agenda.hora = hora;
	passeio_atual -> data_agenda.min = min;	
}

void set_passeio_ativo(struct passeio *paseio_atual,int estado)
{
	paseio_atual -> ativo = estado;
}

void set_passeio_cliente(struct passeio *passeio_atual,
	struct cliente *cliente_atual,int index)
{
	passeio_atual -> clientes[index] = cliente_atual -> cpf;
}

char **get_passeio_clientes(struct passeio *passeio_atual)
{
	return passeio_atual -> clientes; 
}

void set_passeio_next(struct passeio *passeio_atual, struct passeio *prox)
{
	passeio_atual -> next = prox;
}

void set_passeio_prev(struct passeio *passeio_atual, struct passeio *prev)
{
	passeio_atual -> prev = prev;
}

int get_passeio_id(struct passeio *passeio_atual)
{
	return passeio_atual -> id;
}

struct data get_passeio_agenda(struct passeio *passeio_atual)
{
	return passeio_atual -> data_agenda;
}

int get_passeio_estado(struct passeio *passeio_atual)
{
	return passeio_atual -> ativo;
}

int get_passeio_clientes_count
	(struct passeio *passeio_atual)
{
	int result = 0;
	for(int i = 0; i< MAX_CLIENTES;i++)
	{
		if(passeio_atual -> clientes[i] != "") result++;
		else break;
	}
	return result;
}

void inserir_passeio(struct roteiro *roteiro_base,struct passeio *passeio_novo)
{
	struct roteiro *pont_roteiro = roteiro_base;
	struct passeio *pont_passeio = roteiro_base -> passeios;

	if (pont_passeio != NULL){
		while (pont_passeio -> next != NULL){
			pont_passeio = pont_passeio -> next;
		}
		pont_passeio -> next = passeio_novo;
		passeio_novo -> prev = pont_passeio;
	}

	else {
		pont_roteiro -> passeios = passeio_novo;
	}
	pont_roteiro -> last_passeio = passeio_novo;
	passeio_novo -> id = roteiro_base -> count_passeios;
	roteiro_base -> count_passeios++;	
}


void inserir_cliente_passeio(struct passeio *passeio_atual,struct cliente *cliente_atual)
{
	for(int i = 0;i < MAX_CLIENTES;i++){
		if(passeio_atual -> clientes[i] == ""){
			passeio_atual -> clientes[i] = get_cliente_cpf(cliente_atual);
			break;
		}
		else if (i == MAX_TAGS_LENGTH - 1)
			break;
	}
}

void listar_passeios(struct roteiro *roteiro_base)
{
	printf("\nPasseios cadastrados com roteiro: %s\n",
		get_roteiro_nome(roteiro_base));
	if(roteiro_base -> passeios != NULL){
		struct passeio *passeio_tmp = roteiro_base -> passeios;
		while(passeio_tmp != NULL){
			printf("\n[%d] - [Data:%d/%d/%d]\n      Status: %d\n",
				get_passeio_id(passeio_tmp),
				get_passeio_agenda(passeio_tmp).dia,
				get_passeio_agenda(passeio_tmp).mes,
				get_passeio_agenda(passeio_tmp).ano,
				get_passeio_estado(passeio_tmp));
				printf("      Numero de clientes cadastrados:%d\n",
				get_passeio_clientes_count(passeio_tmp));
			passeio_tmp = passeio_tmp -> next;
		}
	}
	else{
		printf("Nenhum passeio marcado");
	}
}

void limpar_passeios(struct roteiro *roteiro_base)
{
	struct passeio *passeio_temp = roteiro_base -> passeios;
	struct passeio *passeio_next;
	if(passeio_temp != NULL)
	{
		passeio_next = passeio_temp -> next;
		while (passeio_temp != NULL)
		{
			if(passeio_temp -> prev == NULL) roteiro_base -> passeios = NULL;
			free(passeio_temp);
			passeio_temp = passeio_next;
		}
	}
}
