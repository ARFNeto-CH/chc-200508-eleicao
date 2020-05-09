#include "base-el.h"

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
	double  erro = 0;
	double  Fa = 0.;
	double  Fb = 1.;
	double  f = 0.0;
	double  intervalo = 0.;

	f = 0.5;
	do
	{
		intervalo = Fb - Fa;
		f = Fa + (Fb - Fa) / 2;
		ativa_sorteador(); // reproduz a serie para o novo f
		erro = prob_erro(N, a, f, T);
		if (erro > tol)
		{	// baixa a margem
			Fb = f;
		}
		else
		{	// aumenta a margem
			Fa = f;
		};	// if()
	} while (intervalo >= BISSEC_TOL);
	return f;
};	// bissecta()


double  bissecta_v(int N, double a, int T, double tol)
{
	double  erro = 0;
	double  Fa = 0.;
	double  Fb = 1.;
	double  f = 0.0;
	double  intervalo = 0.;

	printf("Bissecta()\n");
	printf("    N = %d votantes\n", N);
	printf("    Margem A = %.2f\n", a);
	printf("    %d simulacoes\n", T);
	printf("    tol = %.4f\n\n", tol);
	f = 0.5;
	do
	{
		intervalo = Fb - Fa;
		f = Fa + (Fb - Fa) / 2;
		printf("\nf = %f    (Fb = %f, Fa = %f)\n",
			f, Fb, Fa);
		ativa_sorteador(); // reproduz a serie para o novo f
		erro = prob_erro(N, a, f, T);
		printf("prob_erro() = %.7f Prob A = %.4f%%\n",
			erro, 100. * (1 - erro));
		if (erro > tol)
		{	// baixa a margem
			Fb = f;
			printf("    baixa f\n");
		}
		else
		{	// aumenta a margem
			Fa = f;
			printf("    sobe f\n");
		};	// if()
		//printf("(%f,%f) Tecle enter ", Fb, Fa);
		//getchar();
	} while (intervalo >= BISSEC_TOL);
	return f;
};	// bissecta_v()


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
	int limite = (N / 2) + 1;
	erros = 0;
	// T simulacoes
	for (sim = 1; sim <= T; sim += 1)
	{	// uma simulacao
		int votos_em_A = 0;
		int votos_em_B = 0;
		// em cada eleicao a*N eleitores vao votar em A
		int eleitores = (int)(a * N); // esses vieram pra votar em A
		for (v = 0; v < eleitores; v += 1)
		{	// cada voto
			if (sorteia_voto_com_falha(f))
				votos_em_B += 1;
			else
				votos_em_A += 1;
		};	// for()

		// agora o outro lado: (N - (a * N)) vieram votar em B
		eleitores = N - eleitores;
		for (v = 0; v < eleitores; v += 1)
		{	// cada voto
			if (sorteia_voto_com_falha(f))
				votos_em_A += 1;
			else
				votos_em_B += 1;
		};	// for() 
		// fim da eleicao
		if (votos_em_A < limite) erros += 1;
	};	// for()
	return (double)erros / (double)(T);
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
	int limite = (N / 2) + 1;

	printf("\n  %d simulacoes\n", T);
	printf("    N = %d votantes\n", N);
	printf("    Margem A = %.2f\n", a);
	printf("    Taxa de erro f = %.7f\n", f);
	printf("    Minimo de  votos para vencer = %d\n\n", limite);

	erros = 0;
	// T simulacoes
	for (sim = 1; sim <= T; sim += 1)
	{	// uma simulacao
		int votos_em_A = 0;
		int votos_em_B = 0;
		// em cada eleicao a*N eleitores vao votar em A
		int eleitores = (int)(a * N); // esses vieram pra votar em A
		//printf("De %5d eleitores de A ", eleitores);
		for (v = 0; v < eleitores; v += 1)
		{	// cada voto
			if (sorteia_voto_com_falha(f))
				votos_em_B += 1;
			else
				votos_em_A += 1;
		};	// for()
		//printf("%5d tiveram o voto confirmado\n", votos_em_A);

		// agora o outro lado: (N - (a * N)) vieram votar em B
		eleitores = N - eleitores;
		//printf("De %5d eleitores de B ", eleitores);
		for (v = 0; v < eleitores; v += 1)
		{	// cada voto
			if (sorteia_voto_com_falha(f))
				votos_em_A += 1;
			else
				votos_em_B += 1;
		};	// for() 
		//printf("%5d tiveram o voto confirmado\n", votos_em_B);
		// fim da eleicao
		if (votos_em_A < limite) erros += 1;
		printf("\nResultado [%5d de %5d]:\n\n\t    Votos em A: %5d\n",
			sim, T, votos_em_A);
		printf("\t    Votos em B: %5d\n", votos_em_B);
		printf("\tErros ate aqui: %5d\n\n", erros);
	};	// for()

	printf("Final: %d erros com %d eleitores e f = %.7f. Margem = %.2f%%\n",
		erros, N, f, 100. * (double)erros / (double)(T));
	return (double)erros / (double)(T);
};	// prob_erro_v()


/* devolve um real sorteado uniformemente no intervalo [0,1] */
double sorteia_real()
{
	return (double)rand() / RAND_MAX;
};


int sorteia_voto_com_falha(double f)
{
	int res = (sorteia_real() < f);
	return res;
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