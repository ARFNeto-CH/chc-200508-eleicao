#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define BISSEC_TOL (1e-6)

void    ativa_sorteador();
double  sorteia_real();
int     sorteia_voto_com_falha(double);
int     sorteia_voto_com_falha2(double);


int main(int argc, char** argv)
{
	double f = 0.1;
	int    falhas = 0;
	int    falhas2 = 0;
	int    r = 0;
	int    testes = 10000;

	ativa_sorteador();

	srand(20200505);
	for (int i = 0; i < testes; i += 1)
	{
		r = sorteia_voto_com_falha(f);
		if (r != 0) falhas = falhas + 1;
	};

	srand(20200505);
	for (int i = 0; i < testes; i += 1)
	{
		r = sorteia_voto_com_falha2(f);
		if (r != 0) falhas2 = falhas2 + 1;
	};

	printf("Para %d testes e f=%4.2f a funcao retornou %d falhas\n",
		testes, f, falhas);
	printf("    e a segunda funcao retornou %d falhas\n",
		falhas2);
	return 0;
};


void ativa_sorteador()
{
#ifdef RANDOM_SEED
	srand(RANDOM_SEED);
#else
	srand(time(NULL));
#endif
};


/* devolve um real sorteado uniformemente no intervalo [0,1] */
double sorteia_real()
{
	return (double)rand() / RAND_MAX;
};


int sorteia_voto_com_falha(double f)
{
	return (sorteia_real() < f);
};


int sorteia_voto_com_falha2(double f)
{
	int i = rand() % 100;
	int j = (int)(f * 100);
	return (i<j);
};
