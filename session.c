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
#include <stdio_ext.h>

struct session *criar_session()
{
	struct session *nova_session = (struct session*)
		malloc(sizeof(struct session));
	nova_session -> root_cidade = criar_cidade("ROOT");
	nova_session -> root_roteiro = criar_roteiro("ROOT");
	nova_session -> tag_root = criar_tag("ROOT");
	return nova_session;
}

void plotar_graf(int min,int max,int valor,int niveis)
{
	float range = (max - min);
	float niveis_tam = range / niveis;
	int valor_adaptado = valor / niveis_tam;
	// printf("\n");
	for(int i = 0;i<valor_adaptado;i++) {
		if(i == valor_adaptado - 1){
			printf("|%d",valor);
			break;
		}
		else
			printf("=");
	}
}

int cadastro(struct cidade *cidade_base)
{
	char *nome;
	char *cidade;
	char *cpf;
	struct data data_Nasc = data_base();
	char genero = 'i';

	printf("\nCadastro:\n");
  
	printf("\nInsira o seu nome:\n");
	nome = recebe_string();

	printf("\nInsira o cpf:\n");
	cpf = recebe_string();

	listar_cidades_cadastro(cidade_base);

	int choice;
	printf("\nSelecione a sua cidade\n");
	scanf("%d",&choice);
        if (!choice) {
                __fpurge(stdin);
                cadastro_cidade(cidade_base);
                choice = cidade_base->count_cidades;
        }
	struct cidade *cidade_escolhida = buscar_cidade_index(cidade_base,choice);

        if (!cidade_escolhida) {
                printf("Erro ao buscar cidade\n");
                return FALSE;
        }


	if(buscar_cliente(cidade_base,cpf)!=NULL)
		return FALSE;

	printf("\nDigite o dia de nascimento:\n");
	scanf("%d",&data_Nasc.dia);

	printf("\nDigite o mes de nascimento:\n");
	scanf("%d",&data_Nasc.mes);

	printf("\nDigite ano de nascimento:\n");
	scanf("%d",&data_Nasc.ano);

	struct cliente *novo_cliente = criar_cliente(nome);
	set_cliente_cpf(novo_cliente,cpf);
	set_cliente_data_n(novo_cliente,data_Nasc.ano,data_Nasc.mes,data_Nasc.dia);
	set_cliente_genero(novo_cliente,genero);

	inserir_cliente(cidade_escolhida,novo_cliente);

	return TRUE;
}

void cadastro_cidade(struct cidade *root)
{
	char *nome;
	printf("Digite o nome da nova cidade:\n");
	nome = recebe_string();
	struct cidade *nova_cidade = criar_cidade(nome);
	inserir_cidade(root,nova_cidade);
}