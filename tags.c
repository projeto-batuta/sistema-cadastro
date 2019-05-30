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

struct tag *criar_tag(char *nome)
{
	struct tag *nova_tag = (struct tag*)
		malloc(sizeof(struct tag));
	nova_tag -> nome = nome;
	nova_tag -> chamadas = 0;
	nova_tag -> next = NULL;
	return nova_tag;
}

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

int get_tag_chamadas(struct tag *tag_atual)
{
	return tag_atual -> chamadas;
}

void inserir_tag(struct tag *tag_nova)
{	
	struct tag *pont_temp = tags;
	if (tags == NULL) 
		tags = tag_nova;
	else {
		while (pont_temp -> next != NULL){
			pont_temp = pont_temp -> next;
		}
		pont_temp -> next = tag_nova;
	}
	// tag_cont++;
}

void insere_tag_cliente(struct cliente *cliente_atual, struct tag *tag_atual)
{
	for(int i = 0;i < MAX_TAGS_LENGTH;i++){
		if(cliente_atual -> tags[i] == NULL){
			cliente_atual -> tags[i] = tag_atual;
			tag_atual -> chamadas++;
			break;
		}
		else if (i == MAX_TAGS_LENGTH - 1)
			break;
	}
}



void listar_tags()
{
	struct tag *pont_temp = tags;
	printf("\nTags cadastradas:\n");
	while(pont_temp != NULL)
	{
		printf("- %s\n",get_tag_nome(pont_temp));
		pont_temp = pont_temp -> next;
	}
}

void listar_tags_cliente(struct cliente *cliente_atual)
{
	printf("\nTags de %s:\n",get_cliente_nome(cliente_atual));
	for(int i = 0;i < MAX_TAGS_LENGTH;i++)
	{
		if(get_cliente_tags(cliente_atual)[i] != NULL)
		{
			printf("- %s\n",get_tag_nome(get_cliente_tags(cliente_atual)[i]));
		}
		else printf("- Espaco disponivel\n");
	}
}
