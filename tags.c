#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#ifndef DEFS
#define DEFS
#include "defs.h"
#include "data.h"
#include "clientefs.h"
#include "cidade.h"
#include "roteiro.h"
#include "passeio.h"
#include "tags.h"
#endif

// struct tag *criar_tag(char *nome)
// {
// 	struct tag *nova_tag = (struct tag*)
// 		malloc(sizeof(struct tag));
// 	nova_tag -> id = 0;
// 	nova_tag -> nome = nome;
// 	nova_tag -> chamadas = 0;
// 	nova_tag -> next = NULL;
// 	return nova_tag;
// }

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

void insere_tag (struct tag *root, char *nome)
{
        struct tag *nova_tag = criar_tag(nome);
        struct tag *aux = root;

        int count = 1;

        while (aux->next != NULL) {
                aux = aux->next;
                count++;
        }

        nova_tag->id = count;
        aux->next = nova_tag;
}


// void inserir_tag(struct tag *root,struct tag *tag_nova)
// {	
// 	struct tag *pont_temp = root;
// 	if (pont_temp -> next == NULL) 
// 		pont_temp -> next = tag_nova;
// 	else {
// 		while (pont_temp -> next != NULL) 
// 			pont_temp = pont_temp -> next;
// 		pont_temp -> next = tag_nova;
// 	}
// 	root -> chamadas++;
// }

void insere_tag_cliente(struct cliente *cliente_atual,struct tag *tag_root, int tag_id)
{
	struct tag *tag_atual = buscar_id_tag(tag_root,tag_id);
	int *list = cliente_atual -> tags;
	int inserido = FALSE;
	if(tag_atual != NULL){
		for(int i = 0;i < MAX_TAGS_LENGTH;i++){
			if(list[i] == 0 && inserido == FALSE){
				list[i] = get_tag_id(tag_atual);
				inserido = TRUE;
			}
		}
	}
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
