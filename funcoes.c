#include <stdio.h>
#include <stdlib.h>
#include "estruturas.h"
#include "funcoes.h"
#define TRUE 1
#define FALSE 0
// #define NULL ((void *)0)

struct tag *tags_list;


int cidades_cont = 1;
int clientes_cont = 0;
int passeios_cont = 0;
int roteiros_cont = 0;
int tag_cont = 0;


struct data data_base()
{
	struct data data_padrao;
	data_padrao.ano = 0;
	data_padrao.dia = 0;
	data_padrao.hora = 0;
	data_padrao.min = 0;
	data_padrao.mes = 0;
	return data_padrao;
}


struct cidade *criar_cidade(char nome[])
{
	struct cidade *nova_cidade = (struct cidade*)malloc(sizeof(struct cidade));
	nova_cidade -> clientes = NULL;
	nova_cidade -> roteiros = NULL;
	nova_cidade -> next = NULL;
	for(int i = 0;i < NAME_LENGTH;i++) {
		nova_cidade -> nome[i] = nome[i];
	}
	return nova_cidade;
}

struct roteiro *criar_roteiro(char nome[],int duracao)
{
	struct roteiro *novo_roteiro = (struct roteiro*)malloc(sizeof(struct roteiro));
	struct data duracaoS;
	duracaoS.hora = duracao;
	novo_roteiro -> duracao = duracaoS;
	novo_roteiro -> next = NULL;
	novo_roteiro -> passeios = NULL;
	novo_roteiro -> ult_passeio  = NULL;
	for (int i = 0;i < OBS_LENGTH;i++){
		if (i < NAME_LENGTH) novo_roteiro -> nome[i] = nome[i];
		novo_roteiro -> obs[i] = 0;
	}
	return novo_roteiro;	
}

struct passeio *criar_passeio(int id)
{
	struct passeio *novo_passeio = (struct passeio*)malloc(sizeof(struct passeio));
	novo_passeio -> id = id;
	novo_passeio -> ativo = FALSE;
	novo_passeio -> data = data_base();
	novo_passeio -> horario = data_base();
	novo_passeio -> next = NULL;
	novo_passeio -> prev = NULL;
	for (int i = 0;i < MAX_CLIENTES;i++){
		novo_passeio -> clientes[i] = NULL;
	}
	return novo_passeio;
}

struct cliente *criar_cliente(char nome[],char cpf[])
{
	struct cliente *novo_cliente = (struct cliente*)malloc(sizeof(struct cliente)); 
	novo_cliente -> data_nasc = data_base();
	novo_cliente -> next = NULL;
	novo_cliente -> prev = NULL;
	for(int i = 0;i < NAME_LENGTH;i++){
		if (i < CPF_LENGTH) novo_cliente -> cpf[i] = cpf[i];
		if (i < MAX_TAGS_LENGTH) novo_cliente -> tags[i] = NULL;
		novo_cliente -> cidade[i] = 0;
		novo_cliente -> nome[i] = nome[i];
	}
	return novo_cliente;
}


struct tag *criar_tag(char nome[])
{
	struct tag *nova_tag = (struct tag*)malloc(sizeof(struct tag));
	nova_tag -> chamadas = 0;
	nova_tag -> next = NULL;
	for(int i = 0;i < NAME_LENGTH;i++){
		nova_tag -> nome[i] = nome[i];
	}
	return nova_tag;
}

/*Variaveis globais:------------------------------------*/



/*Insercao:---------------------------------------------*/

void inserir_cidade(struct cidade *cidade_base,struct cidade *cidade_nova)
{
	struct cidade *pont_temp = cidade_base;
	if (pont_temp -> next == NULL) pont_temp -> next = cidade_nova;
	else {
		while (pont_temp -> next != NULL) 
			pont_temp = pont_temp -> next = NULL;
		pont_temp -> next = cidade_nova;
	}
	cidades_cont++;
}


void inserir_roteiro(struct cidade *cidade_base, struct roteiro *roteiro_novo)
{
	struct roteiro *aux = cidade_base -> roteiros;
	if(aux != NULL){
		while (aux -> next != NULL) aux = aux -> next;
		aux -> next = roteiro_novo;
	}
	else {
		cidade_base -> roteiros = roteiro_novo;
	}
	roteiros_cont++;
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
	pont_roteiro -> ult_passeio = passeio_novo;
	passeio_novo -> id = passeios_cont;
	passeios_cont++;	
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
	clientes_cont++;
}

void inserir_cliente_passeio(struct passeio *passeio_atual,struct cliente *cliente_atual)
{
	for(int i = 0;i < MAX_CLIENTES;i++){
		if(passeio_atual -> clientes[i] == NULL){
			passeio_atual -> clientes[i] = cliente_atual;
			break;
		}
		else if (i == MAX_TAGS_LENGTH - 1)
			break;
	}
}

void inserir_tag(struct tag *tag_nova)
{	
	if (tags_list == NULL) 
		tags_list = tag_nova;
	else {
		struct tag *pont_temp = tags_list;
		while (pont_temp -> next != NULL){
			pont_temp = pont_temp -> next;
		}
		pont_temp -> next = tag_nova;
	}
	tag_cont++;
}

void insere_tag_cliente(struct cliente *cliente_atual, struct tag *tag_atual)
{
	for(int i = 0;i < MAX_TAGS_LENGTH;i++){
		if(cliente_atual -> tags[i] == NULL){
			cliente_atual -> tags[i] = tag_atual;
			tag_atual -> chamadas++;
			break;
		}
		else if (i == MAX_TAGS_LENGTH - 1)
			break;
	}
}

/*Setters:----------------------------------------------*/
/*Funções responsaveis pela a modificacao de atributos de um struct*/

/*Cidade*/

void set_cidade_nome(struct cidade *cidade_atual,char nome[])
{
	for (int i = 0;i < NAME_LENGTH;i++){
		cidade_atual -> nome[i] = nome[i];
	}
}

/*Roteiro*/

void set_roteiro_nome(struct roteiro *roteiro_atual,char nome[])
{
	for (int i = 0;i < NAME_LENGTH;i++){
		roteiro_atual -> nome[i] = nome[i];
	}
}

void set_roteiro_obs(struct roteiro *roteiro_atual,char obs[])
{
	for (int i = 0;i < OBS_LENGTH;i++){
		roteiro_atual -> obs[i] = obs[i];
	}
}

void set_roteiro_data(struct roteiro *roteiro_atual,int dias,int horas,int min) 
{
	roteiro_atual -> duracao.dia = dias;
	roteiro_atual -> duracao.hora = horas;
	roteiro_atual -> duracao.min = min;
}

// void set_roteiro_tag(struct roteiro *roteiro_atual,struct tag *tag_atual,int i)
// {
// 	roteiro_atual -> tags[i] = tag_atual;
// }

/*Passeio*/

void set_passeio_data_hor(struct passeio *passeio_atual,int ano,int mes,int dia,int hora,int min)
{
	passeio_atual -> data.ano = ano;
	passeio_atual -> data.mes = mes;
	passeio_atual -> data.dia = dia;
	passeio_atual -> horario.hora = hora;
	passeio_atual -> horario.min = min;
}

void set_passeio_estado(struct passeio *passeio_atual,int estado)
{
	passeio_atual -> ativo = estado;
}

void set_passeio_cliente(struct passeio *passeio_atual,struct cliente *cliente_atual,int i)
{
	passeio_atual -> clientes[i] = cliente_atual;
}

/*Cliente*/

void set_cliente_nome(struct cliente *cliente_atual,char nome[])
{
	for (int i = 0;i < NAME_LENGTH;i++){
		cliente_atual -> nome[i] = nome[i];
	}
}

void set_cliente_cidade_nomes(struct cliente *cliente_atual,char nome[])
{
	for (int i = 0;i < NAME_LENGTH;i++){
		cliente_atual -> cidade[i] = nome[i];
	}
}

void set_cliente_cpf(struct cliente *cliente_atual,char cpf[])
{
	for (int i = 0;i < CPF_LENGTH;i++){
		cliente_atual -> cpf[i] = cpf[i];
	}
}

void set_cliente_tag(struct cliente *cliente_atual,struct tag *tag_atual,int i)
{
	cliente_atual -> tags[i] = tag_atual;
}

void set_cliente_data(struct cliente *cliente_atual,struct data nasc)
{
	cliente_atual -> data_nasc = nasc;
}

/*Tag*/

void set_tag_nome(struct tag *tag_atual,char nome[])
{
	for (int i = 0;i < NAME_LENGTH;i++){
		tag_atual -> nome[i] = nome[i];
	}
}


/*Getters:----------------------------------------------*/
/*Funções responsaveis pela a retornar atributos de uma struct*/

/*Cidade*/

char *get_cidade_nome(struct cidade *cidade_atual)
{
	return cidade_atual -> nome;
}

/*Roteiro*/

char *get_roteiro_nome(struct roteiro *roteiro_atual)
{
	return roteiro_atual ->nome; 
}

char *get_roteiro_obs(struct roteiro *roteiro_atual)
{
	return roteiro_atual -> obs;
}

struct data get_roteiro_data(struct roteiro *roteiro_atual) 
{
	return roteiro_atual -> duracao;
}

/*Passeio*/

struct data get_passeio_data(struct passeio *passeio_atual)
{
	return passeio_atual -> data;
}

struct data get_passeio_horario(struct passeio *passeio_atual)
{
	return passeio_atual -> horario;
}

int get_passeio_estado(struct passeio *passeio_atual)
{
	return passeio_atual -> ativo;
}

struct cliente **get_passeio_clientes(struct passeio *passeio_atual)
{
	return passeio_atual -> clientes;
}

/*Cliente*/

char *get_cliente_nome(struct cliente *cliente_atual)
{
	return cliente_atual -> nome;
}

char *get_cliente_cpf(struct cliente *cliente_atual)
{
    	return cliente_atual -> cpf;
}

char *get_cliente_cidade_nome(struct cliente *cliente_atual)
{
	return cliente_atual -> cidade;
}

struct tag **get_cliente_tags(struct cliente *cliente_atual)
{
	return cliente_atual -> tags;
}

/*Tag*/

char *get_tag_nome(struct tag *tag_atual)
{
	return tag_atual -> nome;
}

int get_tag_chamadas(struct tag *tag_atual)
{
	return tag_atual -> chamadas;
}


/*Funcoes de teste*/



void listar_cidades(struct cidade *cidades)
{	
	struct cidade *pont = cidades;
   	printf("Cidades cadastradas:\n\n");
	for(int i = 0;i < cidades_cont;i++){
		printf("- %s\n\n",get_cidade_nome(pont));
		pont = pont -> next;
	}
}

void listar_tags()
{
	struct tag *pont_temp = tags_list;
	printf("TAGs cadastradas:\n\n");
	while (pont_temp != NULL)
	{
		printf("- Nome:%ls\n  Chamadas:%d\n\n",get_tag_nome(pont_temp),
		get_tag_chamadas(pont_temp));
		pont_temp = pont_temp -> next;
	}
    
}

void listar_tags_cliente(struct cliente *cliente_atual)
{
	printf("\nTAGs de: %s\n\n",cliente_atual -> nome);
	for (int i = 0; i< MAX_TAGS_LENGTH;i++){
		if (get_cliente_tags(cliente_atual)[i] != NULL){
		printf("- Nome:%ls\n\n",get_cliente_tags(cliente_atual)[i]);
		}
		else{
		printf("-  Espaço em branco\n\n");
		}
	}
	
}

void listar_clientes(struct cidade *cidade_atual)
{
	struct cliente *pont_temp = cidade_atual -> clientes;
	printf("Clientes cadastrados em %s:\n\n",get_cidade_nome(cidade_atual));
	while (pont_temp != NULL)
	{
		printf("- Nome: %s\n  CPF: %s\n",get_cliente_nome(pont_temp),
		get_cliente_cpf(pont_temp));
		pont_temp = pont_temp -> next;
	}
	
}

void listar_roteiros_cidade(struct cidade *cidade_atual)
{
	struct roteiro *pont_temp = cidade_atual -> roteiros;
	printf("\nRoteiros cadastrados em %s:\n\n", get_cidade_nome(cidade_atual));
	while (pont_temp != NULL)
	{
		printf("- Nome: %s\n  Duracao: %d:%d\n\n",get_roteiro_nome(pont_temp),
		get_roteiro_data(pont_temp).hora,get_roteiro_data(pont_temp).min);
		pont_temp = pont_temp -> next;
	}
}

int compare_strings(char string1[],char string2[],int length)
{
	int result = TRUE;
	for(int i = 0; i < length;i++)
	{
		if (string1[i] != string2[i]){
			result = FALSE;
			break;
		}
	}
	return result;
}

char *string_upp(char string[],int length)
{
	for(int i = 0;i<length;i++){
		string[i] = toupper(string[i]);
	}
	return string;	
}

/*Funcoes de busca (temporário):------------------------*/


//corrigirrrr
struct cidade *buscarCidade(struct cidade *cidades,char nome[])
{
	struct cidade *result = NULL;
	struct cidade *pont_temp = cidades;
	if (compare_strings(get_cidade_nome(cidades),nome,NAME_LENGTH) == TRUE){
		result = cidades;
	}
	else{
		while (pont_temp != NULL){
			int result = compare_strings(get_cidade_nome(pont_temp),nome,NAME_LENGTH);
			if(result == TRUE);
				result = pont_temp;
				break;
			}
			pont_temp = pont_temp -> next;
	}
	return result;
}

/*Funcoes de cadastro (temporário):---------------------*/

void demo_call(struct cidade *cidades)
{

	struct cidade *nova_cidade = criar_cidade("JOAO_PESSOA");
	struct cidade *nova_cidade2 = criar_cidade("NATAL");

	struct tag *nova_tag = criar_tag("Aventura");
	struct tag *nova_tag2 = criar_tag("Terror");

	struct cliente *novo_cliente = criar_cliente("Rivanildo","08006004098");
	struct cliente *novo_cliente2 = criar_cliente("Jorgete","08506404028");
	

	struct roteiro *novo_roteiro = criar_roteiro("Recife-Olinda",2);
	struct roteiro *novo_roteiro2 = criar_roteiro("Joao Pessoa-Itambaba",5);

	set_roteiro_data(novo_roteiro,0,3,30);
	set_roteiro_data(novo_roteiro2,0,5,00);

	inserir_roteiro(cidades,novo_roteiro);
	inserir_roteiro(nova_cidade,novo_roteiro2);

	insere_tag_cliente(novo_cliente,nova_tag);
	insere_tag_cliente(novo_cliente,nova_tag2);

	insere_tag_cliente(novo_cliente2,nova_tag);

	inserir_cliente(cidades,novo_cliente);
	inserir_cliente(nova_cidade,novo_cliente2);

	inserir_cidade(cidades,nova_cidade);
	// inserir_cidade(cidades,nova_cidade2);

	inserir_tag(nova_tag);
	inserir_tag(nova_tag2);

	listar_cidades(cidades);
	listar_tags();
	listar_clientes(cidades);
	listar_clientes(nova_cidade);
	listar_tags_cliente(novo_cliente);
	listar_roteiros_cidade(cidades);
	listar_roteiros_cidade(nova_cidade);

	printf("\nCidades cadastradas: %d",cidades_cont);
	printf("\nRoteiros cadastrados: %d",roteiros_cont);
	printf("\nClientes cadastrados: %d",clientes_cont);
}

void cadastro_cliente(struct cidade *cidades)
{
	char nome[NAME_LENGTH];
	char cidade[NAME_LENGTH];
	char cpf[NAME_LENGTH];
	int dia_nasc;
	int mes_nasc;
	int ano_nasc;

	printf("Insira o seu nome: ");
	scanf("%s",&nome);

	printf("Insira a sua cidade: ");
	scanf("%s",&cidade);

	printf("Insira o seu CPF: ");
	scanf("%s",&cpf); 

	printf("Insira o dia do seu nascimento: ");
	scanf("%d",&dia_nasc);

	printf("Insira o mes do seu nascimento: ");
	scanf("%d",&mes_nasc);

	printf("Insira o ano do seu nascimento: ");
	scanf("%d",&ano_nasc);

	struct cliente *novo_cliente = criar_cliente(nome,cpf);
	set_cliente_cidade_nomes(novo_cliente,cidade);
	struct data nasc;
	nasc.dia = dia_nasc;
	nasc.mes = mes_nasc;
	nasc.ano = ano_nasc;
	set_cliente_data(novo_cliente,nasc);
	set_cliente_cidade_nomes(novo_cliente,string_upp(cidade,NAME_LENGTH));
	printf("%s",novo_cliente -> cidade);

	inserir_cliente(cidades,novo_cliente);

	struct cidade *econtrada;

	// if (econtrada == NULL)
	// {
		// struct cidade *nova_cidade = criar_cidade(cidade);
		// inserir_cidade(cidades,nova_cidade);
		// econtrada = nova_cidade;
	// }
	// else {
	// 	printf("Cidade encontrada");
	// 	econtrada = cidades;
	// }

	inserir_cliente(cidades,novo_cliente);

	// struct cidade *result = buscarCidade(cidades,string_upp(cidade,NAME_LENGTH));
	// if (result == NULL){
	// 	printf("\nCidades diferentes");
	// 	result = criar_cidade(cidade);
	// 	inserir_cidade(cidades,result);
	// 	printf("\n%s",result ->nome);
	// }
	// else {
	// 	printf("\nCidade ja existente");
	// 	inserir_cliente(cidades,novo_cliente);
	// }
	
	printf("%s", nome);
}