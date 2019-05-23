#include <stdio.h>
#include <stdlib.h>
#include "estruturas.h"
#include "funcoes.h"
#define NAME_LENGTH 50
#define OBS_LENGTH 400
#define CPF_LENGTH 12
#define MAX_CIDADES 100
#define MAX_CLIENTES 10
#define MAX_TAGS_LENGTH 5
#define TRUE 1
#define FALSE 0
// #define NULL ((void *)0)



/*
Project by: ORUN Group from CESAR School

IN DEVELOPMENT...

 ______     ______     __  __     __   __    
/\  __ \   /\  == \   /\ \/\ \   /\ "-.\ \   
\ \ \/\ \  \ \  __<   \ \ \_\ \  \ \ \-.  \  
 \ \_____\  \ \_\ \_\  \ \_____\  \ \_\\"\_\ 
  \/_____/   \/_/ /_/   \/_____/   \/_/ \/_/ 
                                             

Coders: Antonio Almeida, Giovanni Procida e Jonathas Barreto;

More info on: https://sites.google.com/cesar.school/orun/home


/*Main:-------------------------------------------------*/

int main(void){
	struct cidade *cidade_base = criar_cidade("RECIFE");
	
	demo_call(cidade_base);

}