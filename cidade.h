struct cidade *criar_cidade(char *nome);
void set_cidade_nome(struct cidade *cidade_atual,char *nome);
void set_cidade_last_cliente(struct cidade *cidade_atual, struct cliente *last);
void set_cidade_next(struct cidade *cidade_atual,struct cidade *cidade_add);
void set_cidade_last_cliente(struct cidade *cidade_atual, struct cliente *last);
char *get_cidade_nome(struct cidade *cidade_atual);
void inserir_cidade(struct cidade *cidade_base,struct cidade *cidade_nova);
void listar_cidades(struct cidade *cidades);