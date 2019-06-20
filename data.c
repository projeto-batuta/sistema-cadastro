#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include "data.h"

struct data data_base()
{
	struct data data_padrao;
	data_padrao.ano = 0;
	data_padrao.dia = 0;
	data_padrao.hora = 0;
	data_padrao.min = 0;
	data_padrao.mes = 0;
	return data_padrao;
}