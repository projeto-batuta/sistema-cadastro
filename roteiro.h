struct roteiro *criar_roteiro(char *nome);
void set_roteiro_nome(struct roteiro *roteiro_atual,char *nome);
void set_roteiro_info(struct roteiro *roteiro_atual,char *info);
void set_roteiro_duracao(struct roteiro *roteiro_atual,int dia,int hora,int min);
void set_roteiro_last_passeio(struct roteiro *roteiro_atual, struct passeio *last);
char *get_roteiro_nome(struct roteiro *roteiro_atual);
char *get_roteiro_info(struct roteiro *roteiro_atual);
struct data get_roteiro_duracao(struct roteiro *roteiro_atual); 
void inserir_roteiro(struct cidade *cidade_base, struct roteiro *roteiro_novo);