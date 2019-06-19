#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "defs.h"
#include "data.h"
#include "clientefs.h"
#include "cidade.h"
#include "roteiro.h"
#include "passeio.h"
#include "tags.h"
#include "session.h"

void set_tag_nome(struct tag *tag_atual,char *nome)
{
	tag_atual -> nome = nome;
}

void set_tag_chamadas(struct tag *tag_atual,int chamadas)
{
	tag_atual -> chamadas = chamadas;
}

void set_tag_next(struct tag *tag_atual,struct tag *next)
{
	tag_atual -> next = next;
}

char *get_tag_nome(struct tag  *tag_atual)
{
	return tag_atual -> nome;
}

int get_tag_id(struct tag *tag_atual)
{
	return tag_atual -> id;
}

struct tag *buscar_id_tag(struct tag *root,int id)
{
	struct tag *tmp = root;
	while(tmp != NULL){
		if (get_tag_id(tmp) == id) {
			return tmp;
		}
		tmp = tmp -> next;
	}
	return NULL;
}

int get_tag_chamadas(struct tag *tag_atual)
{
	return tag_atual -> chamadas;
}

struct tag *criar_tag(char *nome)
{
        struct tag *nova_tag = malloc(sizeof(struct tag));
        nova_tag->nome = nome;
        nova_tag->chamadas = 0;
        nova_tag->next = NULL;

        return nova_tag;
}

int insere_tag_cliente(struct cliente *cliente, struct session *session, int tag_id)
{
	struct tag *tag_atual = buscar_id_tag(session->tag_root,tag_id);
	if(tag_atual != NULL) {
		for(int i = 0;i < MAX_TAGS_LENGTH;i++) {
			if (cliente->tags[i] == 0){
                                cliente->tags[i] = tag_id;
                                tag_atual->chamadas++;
                                return TRUE;
                        }

                        if (cliente->tags[i] == tag_id)
                                return FALSE;
		}
	}
        return FALSE;
}

void listar_tags(struct tag *root)
{
	struct tag *pont_temp = root;
	printf("\nTags cadastradas:\n");
	while(pont_temp != NULL)
	{
		printf("[%d] - %s\n",get_tag_id(pont_temp),get_tag_nome(pont_temp));
		pont_temp = pont_temp -> next;
	}
}

void listar_tags_cliente(struct cliente *cliente_atual,struct tag *tag_root)
{	
	int *list = cliente_atual ->tags;
	int count = 0;
	printf("\nTags de %s:\n",get_cliente_nome(cliente_atual));
	for(int i = 0; i < MAX_TAGS_LENGTH;i++){
		if(list[i] != 0){
			printf("- %s\n",get_tag_nome(buscar_id_tag(tag_root,list[i])));
		}
		else{
			printf("- Espaco disponivel\n");
		}
		
	}
}

void insere_tag (struct tag *root, char *nome)
{
        struct tag *nova_tag = criar_tag(nome);
        int count = 1;


        while (root->next != NULL) {
                root = root->next;
                count++;
        }
        nova_tag->id = count;

        root->next = nova_tag;
        nova_tag->next = NULL;
}

struct tag *constroi_tags (struct tag *root)
{
        char *nomes[10];
        nomes[0] = "GASTRONOMIA";
        nomes[1] = "AVENTURA";
        nomes[2] = "ESPORTES";
        nomes[3] = "EXPLORACAO";
        nomes[4] = "ARQUITETURA";
        nomes[5] = "HISTORIA";
        nomes[6] = "ARTESANATO";
        nomes[7] = "ECOLOGIA";
        nomes[8] = "CULTURA";
        nomes[9] = "FESTIVAIS";

        for(int i = 0; i < 10; i++) {
                insere_tag(root, nomes[i]);
        }
        return root;
}

void escreve_tags(struct tag *root)
{
        FILE *fp;
        if (!(fp = fopen("reg_tags.dat", "wb"))) {
                printf("erro ao abrir reg_tags\n");
                return;
        }
        struct tag *aux = root->next;

        while(aux != NULL) {
                fwrite(aux, sizeof(struct tag), 1, fp);
                aux = aux->next;
        }

        if (fclose(fp)){
                printf("error closing file.");
                exit(-1);
        }
}

void carrega_tags (struct tag *root)
{
        char *nomes[10];
        nomes[0] = "GASTRONOMIA";
        nomes[1] = "AVENTURA";
        nomes[2] = "ESPORTES";
        nomes[3] = "EXPLORACAO";
        nomes[4] = "ARQUITETURA";
        nomes[5] = "HISTORIA";
        nomes[6] = "ARTESANATO";
        nomes[7] = "ECOLOGIA";
        nomes[8] = "CULTURA";
        nomes[9] = "FESTIVAIS";
        
        FILE *fp = fopen("reg_tags.dat", "rb");
        if (!fp) {
                printf("Erro ao ler arquivo reg_tags.dat\n");
                exit(1);
        }
                
        for (int i = 0; i < 10; i++) {
                struct tag *tag_atual = criar_tag(NULL);

                fread(tag_atual, sizeof(struct tag), 1, fp);
                
                root->next = tag_atual;
                tag_atual->nome = nomes[i];
                tag_atual->next = NULL;
                root = root->next;
        }

        if (fclose(fp)){
                printf("error closing file.");
                exit(-1);
        }
}

void limpar_tags (struct tag *tag_root)
{
        if (tag_root->next != NULL)
                limpar_tags(tag_root->next);
        
        free(tag_root);
}


void stats_tag_geral (struct tag *tag_root)
{
        printf("----------------------------------------\n");
        printf("\n\n## Recorrência geral de Tags\n\n");
        tag_root = tag_root->next;

        int maior_ocorrencia = get_max_tagarray(tag_root);
        int menor_ocorrencia = get_min_tagarray(tag_root);

        while (tag_root != NULL) {
                plotar_graf(menor_ocorrencia, maior_ocorrencia,tag_root->chamadas,60);
                printf(" %s\n", tag_root->nome);

                tag_root = tag_root->next;
        }
}

int get_max_tagarray (struct tag *tag_root)
{
        int max = tag_root->chamadas;

        while (tag_root != NULL) {
                if (tag_root->chamadas > max)
                        max = tag_root->chamadas;
                tag_root = tag_root->next;
        }
        return max;
}

int get_min_tagarray (struct tag *tag_root)
{
        int min = tag_root->chamadas;

        while (tag_root != NULL) {
                if (tag_root->chamadas < min)
                        min = tag_root->chamadas;
                tag_root = tag_root->next;
        }
        return min;
}