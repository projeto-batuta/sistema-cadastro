#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define NAME_LENGTH 50
#define OBS_LENGTH 400
#define CPF_LENGTH 12
#define MAX_CIDADES 100
#define MAX_CLIENTES 10
#define MAX_TAGS_LENGTH 5
#define TRUE 1
#define FALSE 0
#define NONE 0 //Apenas para o uso de char

/*Structs*/

struct data 
{
	int ano;
	int mes;
	int dia;
	int hora;
	int min;
};

struct tag 
{
	char *nome;
	int chamadas;
	struct tag *next;
};

struct cliente
{
	char *nome;
	char *cpf;
	char genero;
	struct data data_n;
	struct tag *tags[MAX_TAGS_LENGTH];
	struct cliente *next;
	struct cliente *prev;
};

struct passeio
{
	int id;
	struct data data_agenda;
	int ativo;
	struct cliente *clientes[MAX_CLIENTES];
	struct passeio *next;
	struct passeio *prev;
};

struct roteiro
{
	char *nome;
	char *info;
	struct data duracao;
	struct passeio *passeios;
	struct roteiro *next;
	struct passeio *last_passeio;
};

struct cidade
{
	char *nome;
	struct cliente *clientes;
	struct cliente *last_cliente;
	struct roteiro *roteiros;
	struct cidade *next;
};

/*Variáveis globais*/

struct tag *tags;

int cidades_cont = 0;
int clientes_cont = 0;
int passeios_cont = 0;
int roteiros_cont = 0;
int tag_cont = 0;


/*Construtores*/

struct data data_base(){
	struct data data_padrao;
	data_padrao.ano = 0;
	data_padrao.dia = 0;
	data_padrao.hora = 0;
	data_padrao.min = 0;
	data_padrao.mes = 0;
	return data_padrao;
}


struct cidade *criar_cidade(char *nome)
{
	struct cidade *nova_cidade = (struct cidade*)
		malloc(sizeof(struct cidade));
	nova_cidade -> nome = nome;
	nova_cidade -> clientes = NULL;
	nova_cidade -> last_cliente = NULL;
	nova_cidade -> roteiros = NULL;
	nova_cidade -> next = NULL;
	return nova_cidade;
}

struct roteiro *criar_roteiro(char *nome)
{
	struct roteiro *novo_roteiro = (struct roteiro*)
		malloc(sizeof(struct roteiro));
	novo_roteiro -> nome = nome;
	novo_roteiro -> info = NULL;
	novo_roteiro -> duracao = data_base();
	novo_roteiro -> passeios = NULL;
	novo_roteiro -> next = NULL;
	return novo_roteiro;
}

struct passeio *criar_passeio(int id)
{
	struct passeio *novo_passeio = (struct passeio*)
		malloc(sizeof(struct passeio));
	novo_passeio -> id = id;
	novo_passeio -> data_agenda = data_base();
	novo_passeio -> ativo = FALSE;
	novo_passeio -> next = NULL;
	novo_passeio -> prev = NULL;

	for(int i = 0;i<MAX_CLIENTES;i++)
	{
		novo_passeio -> clientes[i] = NULL;
	}
	return novo_passeio;
}

struct cliente *criar_cliente(char *nome)
{
	struct cliente *novo_cliente = (struct cliente *)
		malloc(sizeof(struct cliente));
	novo_cliente -> nome = nome;
	novo_cliente -> cpf = NULL;
	novo_cliente -> genero = 'd';
	novo_cliente -> data_n = data_base();
	novo_cliente -> next = NULL;
	novo_cliente -> prev = NULL;

	for(int i = 0;i<MAX_TAGS_LENGTH;i++)
	{
		novo_cliente -> tags[i] = NULL;
	}
	return novo_cliente;
}

struct tag *criar_tag(char *nome)
{
	struct tag *nova_tag = (struct tag*)
		malloc(sizeof(struct tag));
	nova_tag -> nome = nome;
	nova_tag -> chamadas = 0;
	nova_tag -> next = NULL;
	return nova_tag;
}

/*Setters - Modificadores*/

/*Cidade*/

void set_cidade_nome(struct cidade *cidade_atual,char *nome)
{
	cidade_atual -> nome = nome;
}

void set_cidade_last_cliente(struct cidade *cidade_atual,
	struct cliente *last)
{
	cidade_atual -> last_cliente = last;
}

void set_cidade_next(struct cidade *cidade_atual,struct cidade *cidade_add)
{
	cidade_atual -> next = cidade_add;
}


/*Roteiro*/

void set_roteiro_nome(struct roteiro *roteiro_atual,char *nome)
{
	roteiro_atual -> nome = nome;
}

void set_roteiro_info(struct roteiro *roteiro_atual,char *info)
{
	roteiro_atual -> info = info;
}

void set_roteiro_duracao(struct roteiro *roteiro_atual,int dia,int hora,int min)
{
	roteiro_atual -> duracao.dia = dia;
	roteiro_atual -> duracao.hora = hora;
	roteiro_atual -> duracao.min = min;
}

void set_roteiro_last_passeio(struct roteiro *roteiro_atual, struct passeio *last)
{
	roteiro_atual -> last_passeio = last;
}


/*Passeio*/

void set_passeio_id(struct passeio *passeio_atual,int id)
{
	passeio_atual -> id = id;
}

void set_passeio_agenda(struct passeio *passeio_atual,int ano,int mes,int dia,
	int hora,int min)
{
	passeio_atual -> data_agenda.ano = ano;
	passeio_atual -> data_agenda.mes = mes;
	passeio_atual -> data_agenda.dia = dia;
	passeio_atual -> data_agenda.hora = hora;
	passeio_atual -> data_agenda.min = min;	
}

void set_passeio_ativo(struct passeio *paseio_atual,int estado)
{
	paseio_atual -> ativo = estado;
}

void set_passeio_cliente(struct passeio *passeio_atual,
	struct cliente *cliente_atual,int index)
{
	passeio_atual -> clientes[index] = cliente_atual;
}

void set_passeio_next(struct passeio *passeio_atual, struct passeio *prox)
{
	passeio_atual -> next = prox;
}

void set_passeio_prev(struct passeio *passeio_atual, struct passeio *prev)
{
	passeio_atual -> prev = prev;
}

/*Cliente*/

void set_cliente_nome(struct cliente *cliente_atual,char *nome)
{
	cliente_atual -> nome = nome;
}

void set_cliente_cpf(struct cliente *cliente_atual,char *cpf)
{
	cliente_atual -> cpf = cpf;
}

void set_cliente_genero(struct cliente *cliente_atual,char genero)
{
	cliente_atual -> genero = genero;
}

void set_cliente_data_n(struct cliente *cliente_atual,int ano,int mes,int dia)
{
	cliente_atual -> data_n.ano = ano;
	cliente_atual -> data_n.mes = mes;
	cliente_atual -> data_n.dia = dia;
}

void set_cliente_tag(struct cliente *cliente_atual,
	int index, struct tag *tag_atual)
{
	cliente_atual -> tags[index] = tag_atual;
}

void set_cliente_next(struct cliente *cliente_atual,struct cliente *next)
{
	cliente_atual -> next = next;
}

void set_cliente_prev(struct cliente *cliente_atual,struct cliente *prev)
{
	cliente_atual -> prev = prev;
}


/*Cliente*/

void set_tag_nome(struct tag *tag_atual,char *nome)
{
	tag_atual -> nome = nome;
}

void set_tag_chamadas(struct tag *tag_atual,int chamadas){
	tag_atual -> chamadas = chamadas;
}

void set_tag_next(struct tag *tag_atual,struct tag *next)
{
	tag_atual -> next = next;
}

/*Getters - Consultores*/

/*Cidade*/

char *get_cidade_nome(struct cidade *cidade_atual)
{
	return cidade_atual -> nome;
}

/*Roteiro*/

char *get_roteiro_nome(struct roteiro *roteiro_atual)
{
	return roteiro_atual -> nome; 
}

char *get_roteiro_info(struct roteiro *roteiro_atual)
{
	return roteiro_atual -> info;
}

struct data get_roteiro_duracao(struct roteiro *roteiro_atual) 
{
	return roteiro_atual -> duracao;
}

/*Passeio*/

int get_passeio_id(struct passeio *passeio_atual)
{
	return passeio_atual -> id;
}

struct data get_passeio_agenda(struct passeio *passeio_atual)
{
	return passeio_atual -> data_agenda;
}

int get_passeio_estado(struct passeio *passeio_atual)
{
	return passeio_atual -> ativo;
}

/*Retorna o array de clientes*/
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

char get_cliente_genero(struct cliente *cliente_atual)
{
	return cliente_atual -> genero;
}

struct data get_cliente_data_n(struct cliente *cliente_atual)
{
	return cliente_atual -> data_n;
}

struct tag **get_cliente_tags(struct cliente *cliente_atual)
{
	return cliente_atual -> tags;
}

/*Tag*/

char *get_tag_nome(struct tag  *tag_atual)
{
	return tag_atual -> nome;
}

int get_tag_chamadas(struct tag *tag_atual)
{
	return tag_atual -> chamadas;
}

/*Inseridores*/

void inserir_cidade(struct cidade *cidade_base,struct cidade *cidade_nova)
{
	struct cidade *pont_temp = cidade_base;
	if (pont_temp -> next == NULL) pont_temp -> next = cidade_nova;
	else {
		while (pont_temp -> next != NULL) 
			pont_temp = pont_temp -> next;
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
	pont_roteiro -> last_passeio = passeio_novo;
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
	struct tag *pont_temp = tags;
	if (tags == NULL) 
		tags = tag_nova;
	else {
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

/*Listagem*/

void listar_cidades(struct cidade *cidades)
{	
	struct cidade *tmp = cidades;
	printf("\nCidades cadastradas:\n");
	while(tmp != NULL)
	{
		printf("- %s\n",get_cidade_nome(tmp));
		tmp = tmp -> next;
	}
}

void listar_tags(){
	struct tag *pont_temp = tags;
	printf("\nTags cadastradas:\n");
	while(pont_temp != NULL)
	{
		printf("- %s\n",get_tag_nome(pont_temp));
		pont_temp = pont_temp -> next;
	}
}

void listar_tags_cliente(struct cliente *cliente_atual)
{
	printf("\nTags de %s:\n",get_cliente_nome(cliente_atual));
	for(int i = 0;i < MAX_TAGS_LENGTH;i++)
	{
		if(get_cliente_tags(cliente_atual)[i] != NULL)
		{
			printf("- %s\n",get_tag_nome(get_cliente_tags(cliente_atual)[i]));
		}
		else printf("- Espaco disponivel\n");
	}
}

void listar_clientes(struct cidade *cidade_atual)
{
	struct cliente *pont_temp = cidade_atual -> clientes;
	printf("\nClientes cadastrados em %s:\n",get_cidade_nome(cidade_atual));
	while(pont_temp != NULL){
		printf("- Nome: %s\n  CPF: %s\n\n",get_cliente_nome(pont_temp),get_cliente_cpf(pont_temp));
		pont_temp = pont_temp -> next;
	}
}

/*Auxiliares*/

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
void cadastro(struct cidade *main){
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
	struct cidade *main = criar_cidade("ROOT");
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

	cadastro(main);

	// printf("%s",tags);
	return 0 ;
}