#include <stdio.h>
#include <stdlib.h>

struct tag {
    int id;
    struct tag *next;
    char *nome;
    int chamadas;
};

int main()
{
    
    return 0;
}

struct tag *criar_tag(char *nome) {
    struct tag *nova_tag = (struct tag *)malloc(sizeof(struct tag));
    nova_tag->nome = nome;
    nova_tag->chamadas = 0;
    nova_tag->next = NULL;

    return nova_tag;
}

void insere_tag (struct tag *root, struct tag *nova_tag) {
    struct tag *aux = root;

    int count = 1;

    while (aux->next != NULL) {
        aux = aux->next;
        count++;
    }

    nova_tag->id = count;
    aux->next = nova_tag;
}

struct tag *constroi_tags (){
    char *nomes[10];
    nomes[0] = ""
}
