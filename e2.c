#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define BISSEC_TOL (1e-6)

void    ativa_sorteador();
double  prob_erro(int, double, double, int);
double  sorteia_real();
int     sorteia_voto_com_falha(double);
int     sorteia_voto_com_falha2(double);


int main(int argc, char** argv)
{
	double f = 0.1;
	int    falhas = 0;
	int    r = 0;
	int    testes = 10000;

	ativa_sorteador();
	for (int i = 0; i < testes; i += 1)
	{
		r = sorteia_voto_com_falha(f);
		if (r != 0) falhas = falhas + 1;
	};
	printf("Para %d testes e f=%4.2f a funcao retornou %d falhas\n",
		testes, f, falhas);


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


double  prob_erro(int N, double a, double f, int T)
{
	/*
	estima a probabilidade de erro de uma eleição com N votantes, 
	dos quais uma fração a vota no candidato A, e com probabilidade de
	falha f, utilizando T simulações.Os limites dos parâmetros são
	como no exemplo de entrada e saída
	*/
	int erros = 0;  // erros
	int sim = 0;    // simulacoes
	int v = 0;      // votos

	float grande_total = 0;

	for (int sim = 0; sim < T; sim += 1)
	{	// executa T simulacoes
		erros = 0;
		for (int v = 0; v < N; v += 1)
		{	// N votos
			if (sorteia_voto_com_falha(f)) erros += 1;
		};
		printf("simulacao %d de %d: %d erros\n",
			sim, T, erros);
		grande_total +=  erros;
		printf("media de erros apos %d eleicoes: %f\n",
			sim, grande_total / sim);
	};	// for()

	printf("Final\n");
	return 0.;
};	// porb_erro()

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
	return (i < j);
};

