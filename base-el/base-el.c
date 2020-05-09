#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define BISSEC_TOL (1e-6)

void    ativa_sorteador();
double  bissecta(int, double, int, double);
double  prob_erro(int, double, double, int);
double  prob_erro_v(int, double, double, int); // com comentarios
double  sorteia_real();
int     sorteia_voto_com_falha(double);
int     sorteia_voto_com_falha2(double);


void ativa_sorteador()
{
#ifdef RANDOM_SEED
	srand(RANDOM_SEED);
#else
	//srand(time(NULL));
	srand(20200805);
#endif
};


double  bissecta(int N, double a, int T, double tol)
{
	double erro = 0;
	double Fa = 0.;
	double Fb = 1.;
	double f = 0.;
	printf("Bissecta()\n");
	printf("    N = %d votantes\n", N);
	printf("    Margem A = %.2f\n", a);
	printf("    %d simulacoes\n", T);
	printf("    tol = %.4f\n\n", tol);
	do
	{
		f = (Fb - Fa) / 2;
		printf("    (Fa = %.7f, Fb = %.7f) f = %.7f\n", Fa, Fb, f);
		ativa_sorteador();
		erro = prob_erro(N, a, f, T);
		printf("prob_erro() retornou %.7f (tol = %.7f) para f = %.7f\n",
			erro, tol, f);
		printf("prob A vencer = %.7f \n", (1 - erro));
		if (erro > tol)
		{	// baixa a margem
			Fb = f;
		}
		else
		{	// aumenta a margem
			Fa = f;
		};	// if()
		printf("Tecle enter "); getchar();
	} while (fabs(Fa - Fb) >= BISSEC_TOL);
	return f;
};	// bissecta()


double  prob_erro(int N, double a, double f, int T)
{
	int erros = 0;  // erros
	int sim = 0;    // simulacoes
	int v = 0;      // votos
	int votos_em_A = 0;
	int limite = (N / 2) + 1;
	erros = 0;
	double razao = 0;
	for (int sim = 1; sim <= T; sim += 1) // T simulacoes
	{	// uma simulacao
		votos_em_A = 0;
		// N votos
		for (int v = 0; v < N; v += 1)
		{	// cada voto
			if (sorteia_real() < a)
			{	// voto em A
				if (!sorteia_voto_com_falha(f))
					votos_em_A += 1;
			}
			else
			{	// voto em B
				if (sorteia_voto_com_falha(f))
					votos_em_A += 1;
			};	// if()
		};	// for() fim da eleicao
		if (votos_em_A < limite)
		{
			erros += 1;
		};
	};	// for()
	razao = (double)erros / (double)(T);
	return razao;
};	// prob_erro()


double  prob_erro_v(int N, double a, double f, int T)
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
	int votos_em_A = 0;
	int limite = (N / 2) + 1;
	printf("\n%d simulacoes\n", T);
	printf("    N = %d votantes\n", N);
	printf("    Margem A = %.2f\n", a);
	printf("    Taxa de erro f = %.2f\n", f);
	printf("    Minimo para vencer = %d\n\n", limite);

	double grande_total = 0;
	erros = 0;
	// T simulacoes
	for (int sim = 1; sim <= T; sim += 1)
	{	// uma simulacao
		votos_em_A = 0;
		// N votos
		for (int v = 0; v < N; v += 1)
		{	// cada voto
			if (sorteia_real() < a)
			{	// voto em A
				if (sorteia_voto_com_falha(f))
				{	// deu pau: foi pra B
				}
				else
				{
					votos_em_A += 1;
				}
			}
			else
			{	// voto em B
				if (sorteia_voto_com_falha(f))
				{	// o mundo da voltas: aqui era B foi pra A
					votos_em_A += 1;
				};	// if()	
			};	// if()
		};	// for() fim da eleicao
		printf("[%4d de %4d]: %4d votos em A. Margem %.2f\n",
			sim, T, votos_em_A, (double)(votos_em_A) / (double)(N));
		if (votos_em_A < limite)
		{
			erros += 1;
			printf("[%4d ERRO! ]: %4d votos em A. Margem %.4f\n",
				sim, votos_em_A, (double)(votos_em_A) / (double)(N));
		};	// if()
	};	// for()
	printf("    %d/%d erros na eleicao com %d eleitores e f = %.7f. Margem = %.2f%%\n", 
		erros, T, N, f, 100.*(double)erros / (double)(T));
	return (double)erros / (double)(T);
};	// prob_erro_v()


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
	if (i < j)
		return 1;
	else 
		return 0;
};

// fim
// https://www.clubedohardware.com.br/forums/topic/
//1446705-fun%C3%A7%C3%B5es-em-c-com-esquema-pr%C3%A9-definido/