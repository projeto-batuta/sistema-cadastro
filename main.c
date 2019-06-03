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

// int cidades_cont = 0;
// int clientes_cont = 0;
// int passeios_cont = 0;
// int roteiros_cont = 0;
// int tag_cont = 0;

char *recebe_string()
{
	int pos_string= 0, tamanho = 1;
	char *nome = malloc(tamanho * sizeof(char));
	char c;

	while(1){
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

/*Cadastro*/
int cadastro(struct cidade *cidade_base)
{
	char *nome;
	char *cidade;
	char *cpf;
	struct data data_Nasc = data_base();
	char genero = 'i';

	printf("\nCadastro:\n");
  
	printf("Insira o seu nome:\n");
	nome = recebe_string();

	printf("Insira o cpf:\n");
	cpf = recebe_string();

	listar_cidades_cadastro(cidade_base);
	int choice;
	printf("Selecione a cidade desejada\n");
	scanf("%d",&choice);
	struct cidade *cidade_escolhida = buscar_cidade_index(cidade_base,choice);


	if(buscar_cliente(cidade_base,cpf)!=NULL)
	{
		return FALSE;	
	}

	printf("Digite o dia de nascimento:\n");
	scanf("%d",&data_Nasc.dia);

	printf("Digite o mes de nascimento:\n");
	scanf("%d",&data_Nasc.mes);

	printf("Digite ano de nascimento:\n");
	scanf("%d",&data_Nasc.ano);

	struct cliente *novo_cliente = criar_cliente(nome);
	set_cliente_cpf(novo_cliente,cpf);
	set_cliente_data_n(novo_cliente,data_Nasc.ano,data_Nasc.mes,data_Nasc.dia);
	set_cliente_genero(novo_cliente,genero);

	inserir_cliente(cidade_escolhida,novo_cliente);

	return TRUE;
}

int cadastro_cidade(struct cidade *main){
	char *nome;

	printf("Digite o nome da cidade:\n");
	nome = recebe_string();
	struct cidade *nova_cidade = criar_cidade(nome);
	inserir_cidade(main,nova_cidade);
}

int main(void){
	char *nome = "Recife";
	struct cidade *principal = criar_cidade("ROOT");
	cadastro_cidade(principal);
	// struct cidade *nova = criar_cidade(nome);
	// struct tag *novat = criar_tag("Gourmet");
	// struct cliente *novoc = criar_cliente("Giovanni");
	// inserir_tag(novat);
	// inserir_cidade(main,nova);
	// listar_cidades(main);
	// inserir_cliente(nova,novoc);
	// listar_tags();
	// insere_tag_cliente(novoc,novat);
	// listar_tags_cliente(novoc);
	listar_cidades(principal);
	cadastro(principal);

	listar_clientes(principal -> next);

	// printf("%s",tags);
	return 0 ;
}