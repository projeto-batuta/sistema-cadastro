struct cidade *criar_cidade(char nome[]);
struct roteiro *criar_roteiro(char nome[],int duracao);
struct passeio *criar_passeio(int id);
struct cliente *criar_cliente(char nome[],char cpf[]);
struct tag *criar_tag(char nome[]);

struct data data_base();
void inserir_cidade(struct cidade *cidade_base,struct cidade *cidade_nova);
void inserir_roteiro(struct cidade *cidade_base, struct roteiro *roteiro_novo);
void inserir_passeio(struct roteiro *roteiro_base,struct passeio *passeio_novo);
void inserir_cliente(struct cidade *cidade_base,struct cliente *cliente_novo);
void inserir_cliente_passeio(struct passeio *passeio_atual,struct cliente *cliente_atual);
void inserir_tag(struct tag *tag_nova);
void insere_tag_cliente(struct cliente *cliente_atual, struct tag *tag_atual);

void set_cidade_nome(struct cidade *cidade_atual,char nome[]);
void set_roteiro_nome(struct roteiro *roteiro_atual,char nome[]);
void set_roteiro_obs(struct roteiro *roteiro_atual,char obs[]);
void set_roteiro_data(struct roteiro *roteiro_atual,int dias,int horas,int min);
void set_passeio_data_hor(struct passeio *passeio_atual,int ano,int mes,int dia,int hora,int min);
void set_passeio_estado(struct passeio *passeio_atual,int estado);
void set_passeio_cliente(struct passeio *passeio_atual,struct cliente *cliente_atual,int i);
void set_cliente_nome(struct cliente *cliente_atual,char nome[]);
void set_cliente_cidade_nomes(struct cliente *cliente_atual,char nome[]);
void set_cliente_cpf(struct cliente *cliente_atual,char cpf[]);
void set_cliente_tag(struct cliente *cliente_atual,struct tag *tag_atual,int i);
void set_cliente_data(struct cliente *cliente_atual,struct data nasc);
void set_tag_nome(struct tag *tag_atual,char nome[]);

char *get_cidade_nome(struct cidade *cidade_atual);
char *get_roteiro_nome(struct roteiro *roteiro_atual);
char *get_roteiro_obs(struct roteiro *roteiro_atual);
struct data get_roteiro_data(struct roteiro *roteiro_atual);
struct data get_passeio_data(struct passeio *passeio_atual);
struct data get_passeio_horario(struct passeio *passeio_atual);
int get_passeio_estado(struct passeio *passeio_atual);
struct cliente **get_passeio_clientes(struct passeio *passeio_atual);
char *get_cliente_nome(struct cliente *cliente_atual);
char *get_cliente_cpf(struct cliente *cliente_atual);
char *get_cliente_cidade_nome(struct cliente *cliente_atual);
struct tag **get_cliente_tags(struct cliente *cliente_atual);
char *get_tag_nome(struct tag *tag_atual);
int get_tag_chamadas(struct tag *tag_atual);


void listar_cidades(struct cidade *cidades);
void listar_tags();
void listar_tags_cliente(struct cliente *cliente_atual);
void listar_clientes(struct cidade *cidade_atual);
void listar_roteiros_cidade(struct cidade *cidade_atual);
int compare_strings(char string1[],char string2[],int length);
char *string_upp(char string[],int length);
struct cidade *buscarCidade(struct cidade *cidades,char nome[]);
void demo_call(struct cidade *cidades);
void cadastro_cliente(struct cidade *cidades);





