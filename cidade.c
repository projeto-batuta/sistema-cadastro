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
#include "session.h"

struct cidade *criar_cidade(char *nome)
{
	struct cidade *nova_cidade = (struct cidade*)
		malloc(sizeof(struct cidade));
	nova_cidade -> count_cidades = 0;
	nova_cidade -> count_clientes = 0;
	nova_cidade -> nome = nome;
	nova_cidade -> clientes = NULL;
	nova_cidade -> next = NULL;
	return nova_cidade;
}


void set_cidade_nome(struct cidade *cidade_atual,char *nome)
{
	cidade_atual -> nome = nome;
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
	if (pont_temp -> next == NULL){
                pont_temp -> next = cidade_nova;
        } else {
		while (pont_temp -> next != NULL) 
			pont_temp = pont_temp -> next;
		pont_temp -> next = cidade_nova;
	}
	cidade_base -> count_cidades++;
}

void listar_cidades(struct cidade *cidades)
{	
        cidades = cidades->next;
	printf("\nCidades cadastradas:\n");
	while(cidades != NULL)
	{
		printf("- %s\n",cidades->nome);
		cidades = cidades -> next;
	}
}

void listar_cidades_cadastro(struct cidade *cidades)
{	
	struct cidade *tmp = cidades -> next;
	printf("\nCidades cadastradas:\n");
        printf("[0] - Nova cidade\n");
	int cont = 1;
	while(tmp != NULL)
	{
		printf("[%d] - %s\n",cont,get_cidade_nome(tmp));
		tmp = tmp -> next;
		cont++;
	}
}

struct cidade *buscar_cidade_index(struct cidade *root,int index)
{
	struct cidade *result = NULL;
	struct cidade *pont_temp = root;
	int cont = 0;
	if(index <= root->count_cidades) {
		while(pont_temp != NULL) {
			if(cont == index)
				result = pont_temp;
                                
			pont_temp = pont_temp -> next;
			cont++;
		}
	}
        return result;
}

void limpar_cidades(struct cidade *cidades)
{

        if(cidades->clientes != NULL) {
                limpar_clientes(cidades->clientes);
        }
	if(cidades->next != NULL){
		limpar_cidades(cidades->next);
	}
        if (cidades->nome)
                free(cidades->nome);
                
        free(cidades);
}

int get_cidade_max_idade(struct cidade *base)
{
	struct cliente *tmp = base -> clientes;
	int maior = tmp -> data_n.ano;
	while (tmp != NULL){
		if(get_cliente_data_n(tmp).ano < maior)
			maior = get_cliente_data_n(tmp).ano;
		tmp = tmp -> next;
	}
	return maior;
}

int get_cidade_min_idade(struct cidade *base)
{
	struct cliente *tmp = base -> clientes;
	int menor = tmp -> data_n.ano;
	while (tmp != NULL){
		if(get_cliente_data_n(tmp).ano > menor)
			menor = get_cliente_data_n(tmp).ano;
		tmp = tmp -> next;
	}
	return menor;
}

int get_cidades_max_idade(struct cidade *principal)
{
	struct cidade *tmp = principal -> next;
	int maior = get_cidade_max_idade(tmp);
	if(maior != 0){
		while(tmp != 0){
			if(get_cidade_max_idade(tmp) < maior)
				maior = get_cidade_max_idade(tmp);
			tmp = tmp -> next;
		}
	}
	return maior;
}

int get_cidades_min_idade(struct cidade *principal)
{
	struct cidade *tmp = principal -> next;
	int menor = get_cidade_max_idade(tmp);
	if(menor != 0){
		while(tmp != 0){
			if(get_cidade_max_idade(tmp) > menor)
				menor = get_cidade_max_idade(tmp);
			tmp = tmp -> next;
		}
	}
	return menor;
}

void listar_cidades_idade_media(struct session *root)
{
	struct cidade *principal = root -> root_cidade;
	if(principal != NULL){
		printf("\nCidades e suas idades(médias)\n");
		struct cidade *tmp = principal;
		int ano_atual = root ->data_atual.ano;
		int maior = ano_atual - get_cidades_max_idade(principal);
		int menor = ano_atual - get_cidades_min_idade(principal);
		tmp = tmp -> next;
		while (tmp != NULL)
		{
			int media = ano_atual - get_cidade_idade_media(tmp);
			printf("\n[%s]\n",get_cidade_nome(tmp));
			plotar_graf(menor,maior,media,60);
			tmp = tmp -> next;
			}
		printf("\n\nIdade Max : [%d]\tIadade Min[%d]\n",menor,maior);
	} else {
		printf("\nNenhuma cidade cadastrada\n");
	}
}

int get_cidade_idade_media(struct cidade *cidade_base)
{
	int result = 0;
	int sum = 0;
	int count = 0;
	struct cliente *tmp = cidade_base -> clientes;
	while(tmp != NULL) {
		sum = sum + get_cliente_data_n(tmp).ano;
		tmp = tmp -> next;
		count++;
	}
	result = sum/count;
	return result;
}

int get_cidades_idade_media(struct cidade *root)
{
	int result = 0;
	int sum = 0;
	int count = 0;
	struct cidade *tmp = root -> next;
	while(tmp != NULL){
		sum = sum + get_cidade_idade_media(tmp);
		tmp = tmp -> next;
		count++;
	}
	result = sum/count;
	printf("%d",result);
	return result;
}
