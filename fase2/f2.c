#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "base-el.h"

void    testa_prob_erro(int, double, double, int);

int     main()
{
	int     testes = 10;
	int     votantes = 1000;
	double	margemA = 0.51;
	double	falha = 0.0001;

	ativa_sorteador();
	falha = .05;
	testes = 100;
	do
	{
		testa_prob_erro(votantes, margemA, falha, testes);
		falha /= 2;
	} while (falha >= BISSEC_TOL);
	return 0;
};	// main()


void     testa_prob_erro(int N, double A, double f, int T)
{
	double erro = prob_erro(N, A, f, T);
	printf("    prob_erro() retornou %.7f para f = %.7f\n", erro, f);
	printf("    Chance de A vencer = %.7f ou %d%%\n",
		(1 - erro), (int)((1 - erro) * 100));
	return;
};	// testa_prob_erro()

// fim
// https://www.clubedohardware.com.br/forums/topic/
//1446705-fun%C3%A7%C3%B5es-em-c-com-esquema-pr%C3%A9-definido/