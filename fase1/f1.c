#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "base-el.h"

void    testa_falhas(int, double);

int main()
{
	double f = 0.5;
	int    testes = 50;

	ativa_sorteador();
	printf("\nsorteia_real(%.7f)\n\n", f);
	for (int i = 1; i <= testes; i += 1)
	{
		double res = sorteia_real(f);
		printf("%4d: %.7f\n", i, res);
	};

	testes = 100000;
	testa_falhas(testes, .50);
	testa_falhas(testes, .25);
	testa_falhas(testes, .10);
	testa_falhas(testes, .01);
	return 0;
};	// main()


void    testa_falhas(int n, double f)
{	// n testes com falha = f
	ativa_sorteador();
	int falhas = 0;

	printf("\nsorteia_voto_com_falha(%.7f)\n\n", f);
	for (int i = 1; i <= n; i += 1)
	{
		int r = sorteia_voto_com_falha(f);
		if (r != 0)
			falhas += 1;
		if (n <= 500)
		{
			printf("%2d ", r);
			if ((i % 20) == 0) printf("\n");
		};	// if()
	};
	printf("\n");
	printf("\n%4d: %d errados, f = %.7f, Erro = %.2f%%\n",
		n, falhas, f, (100. * falhas) / (double)n);


}
// fim
// https://www.clubedohardware.com.br/forums/topic/
//1446705-fun%C3%A7%C3%B5es-em-c-com-esquema-pr%C3%A9-definido/