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
#include "session.h"
#endif

struct session *criar_session(){
	struct session *nova_session = (struct session*)
		malloc(sizeof(struct session));
	nova_session -> root_cidade = criar_cidade("ROOT");
	nova_session -> root_roteiro = criar_roteiro("ROOT");
	nova_session -> tag_root = criar_tag("ROOT");
	return nova_session;
}

void plotar_graf(int min,int max,int valor,int niveis)
{
	float range = (max - min);
	float niveis_tam = range / niveis;
	int valor_adaptado = valor / niveis_tam;
	// printf("\n");
	for(int i = 0;i<valor_adaptado;i++){
		if(i == valor_adaptado - 1){
			printf("|%d",valor);
			break;
		}
		else
			printf("=");
	}
}

