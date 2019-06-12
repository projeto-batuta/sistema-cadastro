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

/*Cadastro*/


void demo(struct cidade *root,struct tag *tag_root,struct roteiro *roteiro_root)
{
	struct cidade *cidade_olinda = criar_cidade("OLINDA");
	struct cidade *cidade_recife = criar_cidade("RECIFE");
	struct cidade *cidade_jab = criar_cidade("JABOATAO_DOS_GUARARAPES");
	struct cidade *cidade_gravata_beach = criar_cidade("GRAVATA_BEACH");

	struct roteiro *novo_recolinda = criar_roteiro("RECIFE-OLINDA");
	struct roteiro *novo_bvolinda = criar_roteiro("BV_OLINDA");

	inserir_roteiro(roteiro_root,novo_recolinda);
	set_roteiro_duracao(novo_recolinda,0,2,30);
	inserir_roteiro(roteiro_root,novo_bvolinda);

	limpar_roteiros(roteiro_root);
	listar_roteiros(roteiro_root);

	inserir_cidade(root,cidade_olinda);
	inserir_cidade(root,cidade_recife);
	inserir_cidade(root,cidade_jab);
	inserir_cidade(root,cidade_gravata_beach);

	struct cliente *cliente_olavo = criar_cliente("Olavo");
	set_cliente_cpf(cliente_olavo,"1515");
	set_cliente_data_n(cliente_olavo,1880,6,12);
	struct cliente *cliente_carlos = criar_cliente("Carlos");
        set_cliente_cpf(cliente_carlos, "30102");
	set_cliente_data_n(cliente_carlos,1920,2,15);
	struct cliente *cliente_jorgete = criar_cliente("Jorgete");
        set_cliente_cpf(cliente_jorgete, "9876231");
	set_cliente_data_n(cliente_jorgete,1970,4,12);
	struct cliente *cliente_maicon = criar_cliente("Maicon");
        set_cliente_cpf(cliente_maicon, "289391");
	set_cliente_data_n(cliente_maicon,1999,7,30);
	struct cliente *cliente_waldisney = criar_cliente("Waldisney");
        set_cliente_cpf(cliente_waldisney, "771231");
	set_cliente_data_n(cliente_waldisney,1906,6,6);

	carrega_tags(tag_root);
	listar_tags(tag_root);

	insere_tag_cliente(cliente_maicon,tag_root,1);
	insere_tag_cliente(cliente_maicon,tag_root,2);
        insere_tag_cliente(cliente_jorgete,tag_root,1);
	listar_tags_cliente(cliente_maicon,tag_root);
	inserir_cliente(cidade_olinda,cliente_carlos);
	inserir_cliente(cidade_jab,cliente_olavo);
	inserir_cliente(cidade_recife,cliente_jorgete);
	inserir_cliente(cidade_recife,cliente_maicon);
	inserir_cliente(cidade_gravata_beach,cliente_waldisney);
}

int get_cliente_maior_idade_cidade(struct cidade *base)
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

// void list_cli_faixa_idade(struct cidade *base,int init,int end,int ano_atual)
// {
// 	int clientes_count = get_cidade_clientes_count(base);
// 	struct cliente *tmp = base -> clientes;
// 	for(int i = 0; i < clientes_count;i++ )
// 	{
// 		if()
// 	}
// }

int get_cliente_maior_idade_geral(struct cidade *principal)
{
	struct cidade *tmp = principal -> next;
	int maior = get_cliente_maior_idade_cidade(tmp);
	if(maior != 0){
		while(tmp != 0){
			if(get_cliente_maior_idade_cidade(tmp) < maior)
				maior = get_cliente_maior_idade_cidade(tmp);
			tmp = tmp -> next;
		}
	}
	return maior;
}

void imprimir_opcoes(int contexto)
{
	char *contextos [4] = {"Cidades","Clientes","Roteiros","Passeios"};
	char *opcoes [4] = {"Criar","Listar","Buscar","Inserir"};
	if(contexto >=0){
		printf("\n[Opcoes] - %s", contextos[contexto]);
		for(int i = 0;i < 4;i++){
			printf("\n[%d] - %s", (i+1),opcoes[i]);
		}
	}
	else{
		printf("\n[Opcoes] - Contexto");
		for(int i = 0;i < 4;i++){
			printf("\n[%d] - %s", (i+1),contextos[i]);
		}
	}
}

void interface(struct cidade *cidade_root,struct tag *tag_root)
{
	char *contextos [4] = {"Cidades","Clientes","Roteiros","Passeios"};
	printf("Bem vindo ao FREVO - Edição Terminal                        ");
	int choice;
	printf("\nEscolha o contexto desejado:\n\n");
	imprimir_opcoes(-1);
	scanf("%d",&choice);
	imprimir_opcoes(choice-1);

}

int main(void)
{
	char *nome = "Recife";
	struct cidade *principal = criar_cidade("ROOT");
	struct tag *tag_root = criar_tag("ROOT");
	struct roteiro *principal_roteiro = criar_roteiro("ROOT");

	demo(principal,tag_root,principal_roteiro);

        registra_cli_cid(principal);
        // carrega_cli_cid(principal);
	// interface(principal,principat_tag);

	// list_cli_faixa_idade(principal -> next -> next,0,50,2019);

	// printf("\n%d",get_cliente_maior_idade_cidade(buscar_cidade_index(principal,2)));
	// int looper = TRUE;
	// while (looper == TRUE) {	
	// 	listar_cidades_e_clientes(principal);
	// 	printf("\nNumero de clientes:%d", principal -> next-> count_clientes);
	// 	cadastro(principal);

	// 	 fflush(stdin);
	// 	__fpurge(stdin);

	// 	scanf("%d",&looper);
	// 	fflush(stdin);
	// 	__fpurge(stdin);
	// }

	listar_cidades(principal);

	listar_cidades_e_clientes(principal);


	listar_clientes(principal -> next);
	// printf("%s",tags);
	// struct cidade *primary = principal -> next;
	// limpar_cidades(principal); 
	return 0 ;
}