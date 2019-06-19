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
#include <time.h>

struct session *criar_session()
{
	struct session *nova_session = (struct session*)
		malloc(sizeof(struct session));
	nova_session->root_cidade = criar_cidade("ROOT");
	nova_session->root_roteiro = criar_roteiro("ROOT");
	nova_session->tag_root = criar_tag("ROOT");
        set_data_atual(nova_session);
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

int cadastro(struct session *session)
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

	listar_cidades_cadastro(session->root_cidade);

	int choice;
	printf("\nSelecione a sua cidade\n");
	scanf("%d",&choice);

        if (!choice) {
                __fpurge(stdin);
                cadastro_cidade(session->root_cidade);
                choice = session->root_cidade->count_cidades;
        }

	struct cidade *cidade_escolhida = buscar_cidade_index(session->root_cidade,choice);

        if (!cidade_escolhida) {
                printf("Erro ao buscar cidade\n");
                return FALSE;
        }


	if(buscar_cliente(session->root_cidade,cpf)!=NULL)
		return FALSE;

	printf("\nDigite o dia de nascimento:\n");
	scanf("%d",&data_Nasc.dia);

	printf("\nDigite o mes de nascimento:\n");
	scanf("%d",&data_Nasc.mes);

	printf("\nDigite ano de nascimento:\n");
	scanf("%d",&data_Nasc.ano);

        printf("\nSelecione 5 tags dentre as 10:\n");
        listar_tags(session->tag_root);
        int escolha_tag, counter_tag = 0, teste_tag;

	struct cliente *novo_cliente = criar_cliente(nome);

        while (counter_tag < 5) {
                scanf("%d", &escolha_tag);
                teste_tag = insere_tag_cliente(novo_cliente, session, escolha_tag);
                if(teste_tag)
                        counter_tag++;
                
        }

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



void set_data_atual(struct session *sessao_atual)
{
	time_t acttime;
        acttime = time(NULL);
        struct tm timer = *localtime(&acttime);
        sessao_atual -> data_atual.dia = timer.tm_mday;
        sessao_atual -> data_atual.mes = timer.tm_mon + 1;
        sessao_atual -> data_atual.ano = timer.tm_year + 1900;
}

void imprimir_opcoes(int opcao)
{
        printf("\n");
	char *listagens[4] = {"1 - Cidades e clientes", "2 - Cidades", "3 - Tags","4 - Roteiros"};
        char *estats[2] = {"1 - Idade", "2 - Tags"};
        switch(opcao){
        case 2:
                for (int i = 0; i < 4; i++){
                        printf("%s\n",listagens[i]);
                }
                break;
        case 3:
                for (int i = 0; i < 2; i++){
                        printf("%s\n", estats[i]);
                }
                break;
        default:
                printf("Opcao invalida\n");
                break;
        }       
}

int interface(struct session *sessao)
{
	printf("Bem vindo ao FREVO - Edição Terminal\n");
	printf("1 - Cadastrar novo cliente\n");
        printf("2 - Cadastrar novo roteiro\n");
        printf("3 - Listagens\n");
        printf("4 - Estatísticas\n");
        printf("5 - Sair\n");

        int escolha;
        scanf("%d", &escolha);
        switch (escolha) {
        case 1:
                cadastro(sessao);
                __fpurge(stdin);
                break;
        case 2:
                cadastro_roteiro(sessao -> root_roteiro);
                __fpurge(stdin);
        case 3:
                imprimir_opcoes(2);
                int listagem;
                scanf("%d", &listagem);
                switch(listagem){
                case 1:
                        listar_cidades_e_clientes(sessao->root_cidade);
                        break;
                case 2:
                        listar_cidades(sessao->root_cidade);
                        break;
                case 3:
                        listar_tags(sessao->tag_root);
                        break;
                case 4:
                        listar_roteiros(sessao->root_roteiro);
                        break;
                default:
                        printf("Opcao invalida\n");
                        break;
                }
                break;                
        
        case 4:
                listar_cidades_idade_media(sessao);
                stats_tag_geral(sessao->tag_root);
                printf("\n\n");
                break;
        case 5:
                return TRUE;
        
        default:
                printf("Opcao invalida\n");
                break;
        }
        return FALSE;
}

void cadastro_roteiro(struct roteiro *root)
{
	char *nome;
	struct data datas = data_base();
	printf("Digite o nome do roteiro:\n");
	nome = recebe_string();
	printf("Digite as horas de duracao:\n");
	scanf("%d",&datas.hora);
	__fpurge(stdin);
	printf("Digite os minutos de duracao:\n");
	scanf("%d",&datas.min);
	__fpurge(stdin);
	struct roteiro *novo_roteiro = criar_roteiro(nome);
	set_roteiro_duracao(novo_roteiro,0,datas.hora,datas.min);
	inserir_roteiro(root,novo_roteiro);
}

void limpar_session(struct session *session)
{
        limpar_cidades(session->root_cidade);

        limpar_tags(session->tag_root);

        if (session->root_roteiro != NULL)
                limpar_roteiros(session->root_roteiro);
                
        free(session);
}