struct tag *criar_tag(char *nome);
void set_tag_nome(struct tag *tag_atual,char *nome);
void set_tag_chamadas(struct tag *tag_atual,int chamadas);
void set_tag_next(struct tag *tag_atual,struct tag *next);
char *get_tag_nome(struct tag  *tag_atual);
int get_tag_chamadas(struct tag *tag_atual);
int get_tag_id(struct tag *tag_atual);
struct tag *buscar_id_tag(struct tag *root,int id);
int insere_tag_cliente(struct cliente *cliente,struct session *session, int tag_id);
void listar_tags(struct tag *root);
void listar_tags_cliente(struct cliente *cliente_atual, struct tag *tag_root);
void insere_tag (struct tag *root, char *nome);
void escreve_tags(struct tag *root);
void carrega_tags (struct tag *root);
struct tag *constroi_tags (struct tag *root);
void limpar_tags (struct tag *tag_root);
void stats_tag_geral (struct tag *tag_root);
int *qtd_tags (struct tag *tag_root, int *array_qtd);
int get_max_tagarray (struct tag *tag_root);
int get_min_tagarray (struct tag *tag_root);