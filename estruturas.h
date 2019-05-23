#define NAME_LENGTH 50
#define OBS_LENGTH 400
#define CPF_LENGTH 12
#define MAX_CIDADES 100
#define MAX_CLIENTES 10
#define MAX_TAGS_LENGTH 5

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

// struct data data_base(){
// 	struct data data_padrao;
// 	data_padrao.ano = 0;
// 	data_padrao.dia = 0;
// 	data_padrao.hora = 0;
// 	data_padrao.min = 0;
// 	data_padrao.mes = 0;
// 	return data_padrao;
// }