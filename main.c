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
void cadastro(struct cidade *principal){
	char *nome;
	char *cidade;
	char *cpf;
	char *data_Nasc;
	char *tags;

	printf("\nCadastro:\n");
  
	printf("Insira o seu nome:\n");
	nome = recebe_string();

	printf("Insira a cidade:\n");
	cidade = recebe_string();

	printf("Insira o cpf:\n");
	cpf = recebe_string();


}

int main(void){
	char *nome = "Recife";
	struct cidade *principal = criar_cidade("ROOT");
	// struct cidade *nova = criar_cidade(nome);
	// struct tag *novat = criar_tag("Gourmet");
	// struct cliente *novoc = criar_cliente("Giovanni");
	// inserir_tag(novat);
	// inserir_cidade(main,nova);
	// listar_cidades(main);
	// inserir_cliente(nova,novoc);
	// listar_clientes(nova);
	// listar_tags();
	// insere_tag_cliente(novoc,novat);
	// listar_tags_cliente(novoc);

	cadastro(principal);

	// printf("%s",tags);
	return 0 ;
}