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
	int count_passeios;
	struct passeio *passeios;
	struct roteiro *next;
	struct passeio *last_passeio;
};

struct cidade
{
	char *nome;
	int count_clientes;
	struct cliente *clientes;
	struct cliente *last_cliente;
	int count_roteiros;
	struct roteiro *roteiros;
	int count_cidades;
	struct cidade *next;
};

struct tag *tags;