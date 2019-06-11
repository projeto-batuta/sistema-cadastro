struct cidade *criar_cidade(char *nome);
void set_cidade_nome(struct cidade *cidade_atual,char *nome);
void set_cidade_last_cliente(struct cidade *cidade_atual, struct cliente *last);
void set_cidade_next(struct cidade *cidade_atual,struct cidade *cidade_add);
void set_cidade_last_cliente(struct cidade *cidade_atual, struct cliente *last);
char *get_cidade_nome(struct cidade *cidade_atual);
int get_cidade_clientes_count(struct cidade *atual);
int get_cidade_count(struct cidade *root);
int get_roteiros_count(struct cidade *base);
void inserir_cidade(struct cidade *cidade_base,struct cidade *cidade_nova);
void listar_cidades(struct cidade *cidades);
void listar_cidades_cadastro(struct cidade *cidades);
struct cidade *buscar_cidade_index(struct cidade *main,int i);
void limpar_cidades(struct cidade *cidade_root);
int cadastro_cidade(struct cidade *root);
int cadastro(struct cidade *cidade_base);


