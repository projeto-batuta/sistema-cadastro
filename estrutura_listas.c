#include <stdio.h>
#include <stdlib.h>
#define NAME_LENGTH 50
#define OBS_LENGTH 400
#define CPF_LENGTH 12
#define MAX_CIDADES 100
#define MAX_CLIENTES 10
#define MAX_TAGS_LENGTH 10
#define TRUE 1
#define FALSE 0

/*
Project by: ORUN Group from CESAR School

IN DEVELOPMENT...

 ______     ______     __  __     __   __    
/\  __ \   /\  == \   /\ \/\ \   /\ "-.\ \   
\ \ \/\ \  \ \  __<   \ \ \_\ \  \ \ \-.  \  
 \ \_____\  \ \_\ \_\  \ \_____\  \ \_\\"\_\ 
  \/_____/   \/_/ /_/   \/_____/   \/_/ \/_/ 
                                             

Coders: Antonio Almeida, Giovanni Procida e Jonathas Barreto;

More info on: https://sites.google.com/cesar.school/orun/home
*/

/*Contadores:-------------------------------------------*/

int cidades_cont = 0;
int clientes_cont = 0;
int passeios_cont = 0;
int roteiros_cont = 0;
int tag_cont = 0;

/*Estruturas:-------------------------------------------*/

struct data {
	int dia;
	int mes;
	int ano;
	int hora;
	int min;
};

struct tag {
	int nome[NAME_LENGTH];
	int chamadas;
	struct tag *next;
};


struct cliente {
	char nome[NAME_LENGTH];
	char cidade[NAME_LENGTH]; /*Revisar esse elemento, pois vai estar sendo apontado na lista encadeada de cidades*/
	char cpf[CPF_LENGTH];
	struct data data_nasc;
	struct tag *tags[MAX_TAGS_LENGTH];
	struct cliente *next;
	struct cliente *prev;
};

struct passeio {
	int id;
	struct data data;
	struct data horario;
	int ativo;
	struct cliente *clientes[MAX_CLIENTES];
	struct passeio *next;
	struct passeio *prev;
};

struct roteiro {
	char nome[NAME_LENGTH];
	char obs [OBS_LENGTH];
	struct data duracao;
	struct passeio *passeios;
	struct roteiro *next;
	struct passeio *ult_passeio;
};


struct cidade {
	char nome[NAME_LENGTH];
	struct cliente *clientes;
	struct roteiro *roteiros;
	struct cidade *next;
};

/*Structs padrão (zerados):-----------------------------*/
/*Servem para gerar elementos de caso base de structs*/

struct data data_base(){
	struct data data_padrao;
	data_padrao.ano = 0;
	data_padrao.dia = 0;
	data_padrao.hora = 0;
	data_padrao.min = 0;
	data_padrao.mes = 0;
	return data_padrao;
}

/*Construtores:-----------------------------------------*/

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

struct tag *tags_list;

/*Insercao:---------------------------------------------*/

void inserir_cidade(struct cidade *cidade_base,struct cidade *cidade_nova)
{
	struct cidade *pont_temp = cidade_base;
	while (pont_temp -> next != NULL) 
		pont_temp = pont_temp -> next = NULL;
	pont_temp -> next = cidade_nova;
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

struct cliente **get_passeio_clientes(struct passeio *passeio_atual){
	return passeio_atual -> clientes;
}

/*Cliente*/

char *get_cliente_nome(struct cliente *cliente_atual)
{
	return cliente_atual -> nome;
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

// char *get_cliente_cidade_nome()

/*Funcoes de listagem (temporário):---------------------*/

void listar_cidades(struct cidade *cidades)
{	
	struct cidade *pont = cidades;
	for(int i = 0;i <= cidades_cont;i++){
		printf("\n%s",pont -> nome);
		pont = pont -> next;
	}
}





/*Main:-------------------------------------------------*/

int main(void){
	// struct cidade *cidade_base = criar_cidade("Recife");
	// struct cidade *nova_cidade = criar_cidade("Joao Pessoa");
	// struct roteiro *novo_roteiro = criar_roteiro("Olinda-Recife",2);
	// struct roteiro *novo_roteiro2 = criar_roteiro("BoaViagem-Olinda",2);
	// struct passeio *novo_passeio = criar_passeio(1);
	// struct passeio *novo_passeio2 = criar_passeio(2);
	// struct cliente *novo_cliente = criar_cliente("Joao Gilberto","07706651139");
	// struct cliente *novo_cliente2 = criar_cliente("Maicon M","07705551139");
	// struct cidade *nova_cidade3 = criar_cidade("Natal");

	// struct tag *novaTag = criar_tag("Aventura");
	// struct tag *novaTag2 = criar_tag("Terror");

	// inserir_cliente_passeio(novo_passeio,novo_cliente);

	// set_cliente_nome(novo_cliente,"Giovanni");
	// inserir_tag(novaTag);
	// inserir_tag(novaTag2);
	// insere_tag_cliente(novo_cliente2,novaTag);
	// insere_tag_cliente(novo_cliente,novaTag);
	// printf("%d\n" ,tags_list ->chamadas );
	// inserir_cidade(cidade_base,nova_cidade);
	// inserir_roteiro(cidade_base,novo_roteiro);
	// inserir_roteiro(cidade_base,novo_roteiro2);
	// inserir_passeio(novo_roteiro,novo_passeio);
	// inserir_passeio(novo_roteiro,novo_passeio2);
	// inserir_cliente(cidade_base,novo_cliente);
	// inserir_cliente(nova_cidade,novo_cliente2);

	// printf("%ls\n",tags_list -> nome);
	// printf("%ls\n",tags_list -> next -> nome);

	// printf("%ls",get_cliente_tags(novo_cliente)[0] ->nome);

	// printf("%ls",get_tag_nome(novaTag));

	// printf("%s",cidade_base -> clientes -> nome);

	// printf("%d",get_roteiro_data(novo_roteiro).hora);


	// // struct cidade *pont = cidade_base;
	// // struct roteiro *pont2 = cidade_base -> roteiros;

	// struct cliente *pont3 = cidade_base -> clientes;

	// // listar_cidades(cidade_base);

}