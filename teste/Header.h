#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Header.h"

#define BISSEC_TOL (1e-6)

void    ativa_sorteador();
double  bissecta(int, double, int, double);
double  prob_erro(int, double, double, int);
double  prob_erro_v(int, double, double, int); // com comentarios
double  sorteia_real();
int     sorteia_voto_com_falha(double);
int     sorteia_voto_com_falha2(double);
