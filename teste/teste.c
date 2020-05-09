#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Header.h"

int main(int argc, char** argv)
{
	double f = 0.5;
	int    falhas = 0;
	int    r = 0;
	int    testes = 10000;

	ativa_sorteador();
	for (int i = 0; i < testes; i += 1)
	{
		r = sorteia_voto_com_falha(f);
		if (r != 0) falhas = falhas + 1;
	};
	printf("Para %d testes e f=%.7f: %d falhas. Indice %.2f%%\n",
		testes, f, falhas, (double)falhas/testes);

	printf("\n\nAgora uma simulacao pra ver a mecanica\n\n");

	int     votantes = 100;
	double	margemA = 0.51;
	double	falha = 0.01;
	double  erro1 = 0.;
	double  erro2 = 0.;
	double tol = 0.;
	testes = 100;

	erro1 = prob_erro_v(votantes, margemA, falha, testes);
	printf("    prob_erro() retornou %.4f para f = %.7f\n", erro1, falha);
	printf("    Chance de A vencer = %.7f ou %d%%\n", 
		(1-erro1), (int)((1-erro1) * 100));

	printf("\n\nAgora simulando mudando f e sem mensagens\n\n");

	f = 1;
	testes = 10000;
	do
	{	ativa_sorteador();
		f = f / 2;
		erro1 = prob_erro(votantes, margemA, f, testes);
		printf("    prob_erro() retornou %.4f para f = %.7f, %d testes\n",
			erro1, f, testes);
	} while ((erro1 >= .001) && (f > BISSEC_TOL));

	printf("\n\nAgora a tal bissecta()\n\n\n");

	double limite = 0.;
	tol = 0.01;
	limite = bissecta(votantes, margemA, testes, tol);
	printf("bissecta() retornou %.7f\n", limite);

	//erro2 = bissecta(1000, 0.51, 10000, 0.01);
	//printf("bissecta() retornou %.7f\n", erro2);


	return 0;
};	// main()


// fim
// https://www.clubedohardware.com.br/forums/topic/
//1446705-fun%C3%A7%C3%B5es-em-c-com-esquema-pr%C3%A9-definido/