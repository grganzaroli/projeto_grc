#ifndef DEMAP_H
#define DEMAP_H

#include <gnuradio/io_signature.h>
#include <stdio.h>

class demap
{
private:
	int size; //tamanho do frame
	int mod_size; //modula��o
	int rate; //taxa de codifica��o
	int M; //bits por simbolo
	float D[2]; //distancia bit 0 e bit 1
	gr_complex *tab; //tabela dos pontos da modu�la��o
	float var; //variancia do ruido
	float *aux_r; //aux real
	float *aux_i; //aux imag
	float *aux; //aux dist euclidiana

public:
	void init(int s, int ms, int r, gr_complex *t, float v); //inicializa variavais

	void demapper_soft(const gr_complex *i, float *o); // faz o demap de i em o (LLR)
	void demapper_hard(const gr_complex *i, unsigned char *o); // faz o demap de i em o (bit)

};

#endif
