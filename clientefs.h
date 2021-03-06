struct cliente *criar_cliente(char *nome);
void deletar_cliente(struct cliente *cliente_atual);
void set_cliente_next(struct cliente *cliente_atual,struct cliente *next);
void set_cliente_prev(struct cliente *cliente_atual,struct cliente *prev);
void set_cliente_data_n(struct cliente *cliente_atual,int ano,int mes,int dia);
void set_cliente_cpf(struct cliente *cliente_atual,char *cpf);
void set_cliente_genero(struct cliente *cliente_atual,char genero);
char *get_cliente_nome(struct cliente *cliente_atual);
char *get_cliente_cpf(struct cliente *cliente_atual);
char get_cliente_genero(struct cliente *cliente_atual);
struct data get_cliente_data_n(struct cliente *cliente_atual);
int *get_cliente_tags(struct cliente *cliente_atual);
void inserir_cliente(struct cidade *cidade_base,struct cliente *cliente_novo);
void listar_clientes(struct cidade *cidade_atual);
struct cliente *buscar_cliente(struct cidade *main,char *cpf);
void limpar_clientes(struct cliente *clientes);
void carrega_cli_cid(struct cidade *root);
void registra_cli_cid(struct cidade *root);