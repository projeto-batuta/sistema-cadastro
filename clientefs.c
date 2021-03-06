#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "defs.h"
#include "data.h"
#include "clientefs.h"
#include "cidade.h"
#include "roteiro.h"
#include "passeio.h"
#include "tags.h"

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

void deletar_cliente(struct cliente *cliente_atual)
{
        struct cliente *next = cliente_atual -> prev;
        struct cliente *prev = cliente_atual -> next;
        free(cliente_atual ->nome);
        free(cliente_atual);
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
	struct cliente *pont_cliente = cidade_base -> clientes;

	if (pont_cliente != NULL){
		while (pont_cliente -> next != NULL) 
			pont_cliente = pont_cliente -> next;
		pont_cliente -> next = cliente_novo;
		cliente_novo -> prev = pont_cliente;
	} else {
		cidade_base -> clientes = cliente_novo;
		cliente_novo -> prev = NULL;
	}
        cliente_novo->next = NULL;
	cidade_base ->count_clientes++;
}

void listar_clientes(struct cidade *cidade_atual)
{
	struct cliente *pont_temp = cidade_atual -> clientes;
	int count=1;
	printf("\nClientes cadastrados em %s:\n\n",
                get_cidade_nome(cidade_atual));
	while(pont_temp != NULL) {
		printf("[%d] - Nome: %s\n", count,get_cliente_nome(pont_temp));
                printf("      CPF: %s\n\n",get_cliente_cpf(pont_temp));
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
			if(get_cliente_cpf(pont_temp_cli) == cpf) {
				result = pont_temp_cli;
			}
			pont_temp_cli = pont_temp_cli -> next;
		}
		pont_temp_cid = pont_temp_cid -> next;
	}

	return result;
	
}

void limpar_clientes(struct cliente *clientes)
{
        if(clientes->next != NULL){
                limpar_clientes(clientes->next);
        }

        if(clientes->cpf != NULL)
                free(clientes->cpf);

        if(clientes->nome != NULL)
                free(clientes->nome);
        
        free(clientes);
}

void carrega_cli_cid(struct cidade *root)
{
        int qtd_cidades, qtd_clientes;
        FILE *reg_clientes = fopen("reg_cli_cid.dat", "rb");

        if (!reg_clientes){
                printf("Nenhum arquivo de clientes disponivel\n");
                return;
        }

        fread(root, sizeof(struct cidade), 1, reg_clientes);
        root->nome = malloc(NAME_LENGTH*sizeof(char));
        strcpy(root->nome,"ROOT");
        qtd_cidades = root->count_cidades;
        
        for (int i = 0; i < qtd_cidades; i++) {
                struct cidade *cidade_atual = criar_cidade(NULL);

                char *nome_cidade = malloc(NAME_LENGTH*sizeof(char));

                fread(cidade_atual, sizeof(struct cidade), 1, reg_clientes);
                fread(nome_cidade, sizeof(char), NAME_LENGTH, reg_clientes);

                cidade_atual->nome = malloc(NAME_LENGTH*sizeof(char));
                
                strcpy(cidade_atual->nome, nome_cidade);
                free(nome_cidade);

                root->next = cidade_atual;
                cidade_atual->next = NULL;
                root = root->next;

                qtd_clientes = cidade_atual->count_clientes;


                for(int j = 0; j < qtd_clientes; j++) {
                        struct cliente *cliente_atual = criar_cliente(NULL);
                        struct cliente *aux;

                        
                        char *nome_cliente = malloc(NAME_LENGTH*sizeof(char));
                        char *cpf = malloc(CPF_LENGTH*sizeof(char));

                        fread(cliente_atual, sizeof(struct cliente), 1,
                                reg_clientes);
                        fread(nome_cliente, sizeof(char), NAME_LENGTH,
                                reg_clientes);
                        fread(cpf, sizeof(char), CPF_LENGTH, reg_clientes);

                        cliente_atual->nome = malloc(NAME_LENGTH*sizeof(char));
                        cliente_atual->cpf = malloc (CPF_LENGTH*sizeof(char));

                        strcpy(cliente_atual->nome, nome_cliente);
                        strcpy(cliente_atual->cpf, cpf);

                        free(nome_cliente);
                        free(cpf);

                        if (j == 0) {
                                cidade_atual->clientes = cliente_atual;
                                aux = cliente_atual;
                        } else {
                                aux->next = cliente_atual;
                                cliente_atual->next = NULL;
                                aux = aux->next;
                        }
                }
        }


        if (fclose(reg_clientes)) {
                printf("error closing file.");
                exit(-1);
        }
}


void registra_cli_cid(struct cidade *root)
{
        struct cliente *cliente_atual = malloc(sizeof(struct cliente));
        if (!cliente_atual) {
                printf("Malloc error at cliente_atual\n");
                exit(1);
        }

        FILE *reg_clientes;
        if (!(reg_clientes = fopen("reg_cli_cid.dat", "wb"))){
                printf("Erro ao abrir reg_cli_cid\n");
                return;
        }

        fwrite(&*root, sizeof(struct cidade), 1, reg_clientes);
        root = root->next;


        while (root != NULL) {
                fwrite(&*root, sizeof(struct cidade), 1, reg_clientes);
                fwrite(root->nome,sizeof(char), NAME_LENGTH,
                        reg_clientes);
                cliente_atual = root->clientes;

                while (cliente_atual != NULL) {
                        fwrite(&*cliente_atual, sizeof(struct cliente), 1,
                                reg_clientes);
                        if (cliente_atual->nome)
                                fwrite(cliente_atual->nome,sizeof(char),
                                        NAME_LENGTH, reg_clientes);
                        
                        if(cliente_atual->cpf)
                                fwrite(cliente_atual->cpf, sizeof(char),
                                        CPF_LENGTH, reg_clientes);
                                
                        cliente_atual = cliente_atual->next;
                } 

                root = root->next;
        }
        
        if (fclose(reg_clientes)) {
                printf("error closing file.");
                exit(-1);
        }

        free(cliente_atual);
}