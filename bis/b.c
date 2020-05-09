#include <stdio.h>
#include <stdlib.h>


int main(int argc, char** argv)
{
	double B = 1.0;
	double A = 0.0;
	double F = 0;
	char buffer[12];
	F = (B - A) / 2;
	while (1)
	{
		printf("intervalo (%f,%f) bis. = %f: Tecle + ou - ", B, A, F);
		fgets(buffer, 5, stdin);
		char c = buffer[0];
		printf(" C = %d\n", c);
		if (c == '+')
		{
			// na direcao de B
			A = A + F;
		}
		else
		{
			// na direcao de A
			B = B - F;
		};
		F = (B - A) / 2;
	};
	return 0;
};


// fim
// https://www.clubedohardware.com.br/forums/topic/
//1446705-fun%C3%A7%C3%B5es-em-c-com-esquema-pr%C3%A9-definido/