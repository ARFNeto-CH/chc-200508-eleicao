#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "base-el.h"

int main()
{
	int     testes = 10000;
	int     votantes = 100;
	double	margemA = 0.51;
	double  erro1 = 0.;
	double  tol = 0.;
	
	testes = 100;
	double limite = 0.;
	tol = 0.01;
	votantes = 100;
	margemA = 0.55;
	testes = 10000;
	tol = 0.01;
	limite = bissecta(votantes, margemA, testes, tol);
	printf("bissecta() retornou %.7f\n", limite);
	// testando com esse valor
	erro1 = prob_erro(votantes, margemA, limite, testes);
	printf("prob_erro() para esse valor de f = %.7f\n",	erro1);

	votantes = 1000;
	margemA = 0.51;
	testes = 10000;
	tol = 0.01;
	ativa_sorteador();
	limite = bissecta(votantes, margemA, testes, tol);
	printf("bissecta() retornou %.7f\n", limite);
	ativa_sorteador();
	erro1 = prob_erro(votantes, margemA, limite, testes);
	printf("prob_erro() para esse valor de f = %.7f\n", erro1);

	return 0;
};	// main()


// fim
// https://www.clubedohardware.com.br/forums/topic/
//1446705-fun%C3%A7%C3%B5es-em-c-com-esquema-pr%C3%A9-definido/