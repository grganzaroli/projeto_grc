#ifndef DEMAP_H
#define DEMAP_H

#include <gnuradio/io_signature.h>
#include <stdio.h>

class demap
{
private:
	int size; //tamanho do frame
	int mod_size; //modulacao
	int rate; //taxa de codificacao
	int M; //bits por simbolo
	float D[2]; //distancia bit 0 e bit 1
	gr_complex *tab; //tabela dos pontos da modulacao
	gr_complex tabela[4096];
	float var; //variancia do ruido
	float *aux_r; //aux real
	float *aux_i; //aux imag
	float *aux; //aux dist euclidiana

public:
	void init(int s, int ms, int r, float v); //inicializa variavais

	void mapper(const unsigned short *i, gr_complex *o); //faz o mapeamento

	int get_M(); //retorna o valor de M

	void demapper_soft(const gr_complex *i, float *o); // faz o demap de i em o (LLR)
	void demapper_hard(const gr_complex *i, unsigned short *o); // faz o demap de i em o (bit)

};

void pack(unsigned short *bytes, const unsigned char *bits, int nbytes, int d_k);
void unpack(unsigned short *bits, const unsigned char *bytes, int nbytes, int d_k);

#endif
