#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio_ext.h>
#include "defs.h"
#include "data.h"
#include "clientefs.h"
#include "cidade.h"
#include "roteiro.h"
#include "passeio.h"
#include "tags.h"
#include "session.h"

int main(void)
{
	struct session *root = criar_session();
        carrega_tags(root->tag_root);
        carrega_cli_cid(root->root_cidade);
        printf("\n[%d/%d/%d]\n",root ->data_atual.dia,root -> data_atual.mes, root -> data_atual.ano );
        while (TRUE) {
                int teste_saida;
                teste_saida = interface(root);
                if (teste_saida) {
                        registra_cli_cid(root->root_cidade);
                        escreve_tags(root->tag_root);
                        break;
                }
        }

        limpar_session(root);
	return 0;
}