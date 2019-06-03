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

struct cliente *criar_cliente(char *nome)
{
	struct cliente *novo_cliente = (struct cliente *)
		malloc(sizeof(struct cliente));
	novo_cliente -> nome = nome;
	novo_cliente -> cpf = NULL;
	novo_cliente -> genero = 'd';
	novo_cliente -> data_n = data_base();
	novo_cliente -> next = NULL;
	novo_cliente -> prev = NULL;

	for(int i = 0;i<MAX_TAGS_LENGTH;i++)
	{
		novo_cliente -> tags[i] = NULL;
	}
	return novo_cliente;
}
void set_cliente_next(struct cliente *cliente_atual,struct cliente *next)
{
	cliente_atual -> next = next;
}

void set_cliente_prev(struct cliente *cliente_atual,struct cliente *prev)
{
	cliente_atual -> prev = prev;
}

void set_cliente_data_n(struct cliente *cliente_atual,int ano,int mes,int dia)
{
	cliente_atual -> data_n.ano = ano;
	cliente_atual -> data_n.mes = mes;
	cliente_atual -> data_n.dia = dia;
}

void set_cliente_genero(struct cliente *cliente_atual,char genero)
{
	cliente_atual -> genero = genero;
}


void set_cliente_cpf(struct cliente *cliente_atual,char *cpf)
{
	cliente_atual -> cpf = cpf;
}

char *get_cliente_nome(struct cliente *cliente_atual)
{
	return cliente_atual -> nome;
}

char *get_cliente_cpf(struct cliente *cliente_atual)
{
	return cliente_atual -> cpf;
}

char get_cliente_genero(struct cliente *cliente_atual)
{
	return cliente_atual -> genero;
}

struct data get_cliente_data_n(struct cliente *cliente_atual)
{
	return cliente_atual -> data_n;
}

struct tag **get_cliente_tags(struct cliente *cliente_atual)
{
	return cliente_atual -> tags;
}

void inserir_cliente(struct cidade *cidade_base,struct cliente *cliente_novo)
{
	struct cidade *pont_cidade = cidade_base;
	struct cliente *pont_cliente = pont_cidade -> clientes;

	if (pont_cliente != NULL){
		while (pont_cliente -> next != NULL) 
			pont_cliente = pont_cliente -> next;
		pont_cliente -> next = cliente_novo;
		cliente_novo -> prev = pont_cliente;
	}
	else {
		pont_cidade -> clientes = cliente_novo;
		cliente_novo -> prev = NULL;
	}
	cidade_base ->count_clientes++;
}
void listar_clientes(struct cidade *cidade_atual)
{
	struct cliente *pont_temp = cidade_atual -> clientes;
	printf("\nClientes cadastrados em %s:\n",get_cidade_nome(cidade_atual));
	while(pont_temp != NULL){
		printf("- Nome: %s\n  CPF: %s\n\n",get_cliente_nome(pont_temp),get_cliente_cpf(pont_temp));
		pont_temp = pont_temp -> next;
	}
}

struct cliente *buscar_cliente(struct cidade *main,char *cpf)
{
	struct cliente *result = NULL;
	struct cidade *pont_temp_cid = main;
	struct cliente *pont_temp_cli;
	while (pont_temp_cid != NULL){
		pont_temp_cli = pont_temp_cid -> clientes;
		while(pont_temp_cli != NULL)
		{
			if(get_cliente_cpf(pont_temp_cli) == cpf){
				result = pont_temp_cli;
			}
			pont_temp_cli = pont_temp_cli -> next;
		}
		pont_temp_cid = pont_temp_cid -> next;
	}

	return result;
	
}

void limpar_clientes(struct cidade *cidade_base)
{
	struct cliente *cliente_temp = cidade_base -> clientes;
	struct cliente *cliente_next;
	if(cliente_temp!= NULL)
	{
		cliente_next = cliente_temp -> next;
		while(cliente_temp != NULL)
		{
			if(cliente_temp -> prev == NULL) cidade_base -> clientes = NULL;
			free(cliente_temp);
			cliente_temp = cliente_next;
		}
	}
}

