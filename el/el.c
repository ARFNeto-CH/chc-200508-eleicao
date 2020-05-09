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