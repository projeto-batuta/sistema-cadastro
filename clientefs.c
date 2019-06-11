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

        if (!novo_cliente) {
                printf("Malloc error at novo_cliente\n");
                exit(1);
        }

	novo_cliente -> nome = nome;
	novo_cliente -> cpf = NULL;
	novo_cliente -> genero = 'd';
	novo_cliente -> data_n = data_base();
	novo_cliente -> next = NULL;
	novo_cliente -> prev = NULL;

	for(int i = 0;i<MAX_TAGS_LENGTH;i++)
	{
		novo_cliente -> tags[i] = 0;
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

int *get_cliente_tags(struct cliente *cliente_atual)
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
	int count=1;
	printf("\nClientes cadastrados em %s:\n\n",get_cidade_nome(cidade_atual));
	while(pont_temp != NULL){
		printf("[%d] - Nome: %s\n      CPF: %s\n\n",count,get_cliente_nome(pont_temp),get_cliente_cpf(pont_temp));
		pont_temp = pont_temp -> next;
		count++;
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
			if(cliente_temp -> prev == NULL)
                                cidade_base->clientes = NULL;
			free(cliente_temp);
			cliente_temp = cliente_next;
		}
	}
}

struct cidade *carrega_cli_cid(struct cidade *root)
{
        int qtd_cidades, qtd_clientes;
        FILE *fp;

        if (!(fp = fopen("reg_cli_cid.dat", "wb")))
                exit(1);

        fread(root, sizeof(struct cidade), 1, fp);
        qtd_cidades = root->count_cidades;

        for (int i = 0; i < qtd_cidades; i++) {
                struct cidade *cidade_atual = criar_cidade(NULL);
                char *nome_cidade = malloc(NAME_LENGTH*sizeof(char));

                // le do arquivo a struct cidade e o nome da cidade, em seguida
                // faz as atribuiçoes do nome e dos ponteiros.
                fread(cidade_atual, sizeof(struct cidade), 1, fp);
                fread(nome_cidade, sizeof(char), NAME_LENGTH, fp);

                cidade_atual->nome = nome_cidade;
                root->next = cidade_atual;
                cidade_atual->next = NULL;
                root = root->next;

                qtd_clientes = cidade_atual->count_clientes;

                for(int j = 0; j < qtd_clientes; j++) {
                        struct cliente *cliente_atual = criar_cliente(NULL);
                        struct cliente *aux;
                        char *nome_cliente = malloc(NAME_LENGTH*(sizeof(char)));
                        char *cpf = malloc(CPF_LENGTH*(sizeof(char)));

                        fread(cliente_atual, sizeof(struct cliente), 1, fp);
                        fread(nome_cliente, sizeof(char), NAME_LENGTH, fp);
                        fread(cpf, sizeof(char), CPF_LENGTH, fp);

                        cliente_atual->nome = nome_cliente;
                        cliente_atual->cpf = cpf;

                        if (j == 0){
                                cidade_atual->clientes = cliente_atual;
                                aux = cliente_atual;
                        }

                        aux->next = cliente_atual;
                        cliente_atual->next = NULL;
                        aux = aux->next;
                }
        }
        
        if (fclose(fp)) {
                printf("error closing file.");
                exit(-1);
        }
}

void registra_cli_cid(struct cidade *root)
{
        struct cidade *cidade_atual = root->next;
        struct cliente *cliente_atual;

        FILE *fp;

        if (!(fp = fopen("reg_cli_cid.dat", "wb")))
                exit(1);

        fwrite(&root, sizeof(struct cidade), 1, fp);

        while (cidade_atual != NULL)
        {
                cliente_atual = cidade_atual->clientes;
                fwrite(&cidade_atual, sizeof(struct cidade), 1, fp);
                fwrite(cidade_atual->nome,sizeof(char), NAME_LENGTH, fp);

                while (cliente_atual != NULL)
                {
                        fwrite(&cliente_atual, sizeof(struct cliente), 1, fp);
                        fwrite(cliente_atual->nome,sizeof(char), NAME_LENGTH, fp);
                        fwrite(cliente_atual->cpf, sizeof(char), CPF_LENGTH, fp);
                        cliente_atual = cliente_atual->next;
                }

                cidade_atual = cidade_atual->next;
        }

        if (fclose(fp))
        {
                printf("error closing file.");
                exit(-1);
        }
}