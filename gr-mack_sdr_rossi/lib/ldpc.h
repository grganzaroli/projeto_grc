﻿#ifndef LDPC_H
#define LDPC_H

class ldpc
{
private:
	unsigned short n; //quantidade de bits de entrada
	unsigned short k; //quantidade de bits de saída
	unsigned short r; //code rate
	unsigned short max_it; //numero de iterações
	unsigned short Q_ldpc; //constante que vem da norma
	bool tipo; //false = tipo A, true = tipo B

	unsigned short **C; // matriz de check nodes
	unsigned short *INDX; // indices para calcular a matriz C, numero de 1s por linha

	unsigned short **err; //contagem de 1s e 0s no hard-decision
	unsigned char *r_aux; //in para eu manipular
	double *LLR_aux; //in em formato LLR pra eu manipular
	unsigned char *SIN; //sindrome

	unsigned short *p_erros; //posicao dos erros
	double** R; //matriz R
	double** Q; //matriz Q

public:
	void init(unsigned short N, unsigned short K); //inicializa variavais

	double aTanh(double x); //arco tangente hiperbólico

	void alocar_hard();//alocação de variáveis para hard_decision
	void alocar_soft();//alocação de variáveis para soft_decision

	void free_hard();//desalocação de variáveis para hard_decision
	void free_soft();//desalocação de variáveis para soft_decision

	bool decode_hard(const unsigned char *r, unsigned char *u); //decodifica [r] em [u] -> hard-decision
	bool decode_soft(const float *r, unsigned char *u); //decodifica [r] em [u] -> soft-decision

};

#endif
