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

	printf("\n\nAgora umas eleicoes pra ver a mecanica\n\n\n");

	int votantes = 10000;
	double	margemA = 0.51;
	double	falha = 0.01;
	testes = 100;
	double erro = prob_erro(votantes, margemA, falha, testes);
	//printf("prob_erro() retornou %f\n", erro);
	return 0;
};


void ativa_sorteador()
{
#ifdef RANDOM_SEED
	srand(RANDOM_SEED);
#else
	//srand(time(NULL));
	srand(20200805);
#endif
};


double  prob_erro(int N, double a, double f, int T)
{
	/*
	estima a probabilidade de erro de uma elei��o com N votantes,
	dos quais uma fra��o a vota no candidato A, e com probabilidade de
	falha f, utilizando T simula��es.Os limites dos par�metros s�o
	como no exemplo de entrada e sa�da
	*/
	int erros = 0;  // erros
	int sim = 0;    // simulacoes
	int v = 0;      // votos

	printf("\n%d simulacoes\n", T);
	printf("    N = %d votantes\n", N);
	printf("    Margem A = %.2f\n", a);
	printf("    Taxa de erro f = %.2f\n\n\n\n", f);

	double grande_total = 0;
	for (int sim = 1; sim <= T; sim += 1)
	{	// executa T simulacoes
		erros = 0;
		for (int v = 0; v < N; v += 1)
		{	// N votos
			if (sorteia_voto_com_falha(f)) erros += 1;
		};
		printf("[%4d de %4d]: %4d erros. ",
			sim, T, erros);
		grande_total += erros;
		printf("Media de erros apos %4d eleicoes: %.3f\n",
			sim, grande_total / sim);
	};	// for()

	printf("Final\n");
	return 1.234;
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
	return (i < j);
};

