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

	void pack_bits(const unsigned char *pack_in, unsigned char *pack_out, int n_bits); //empacota n_bits de pack_in em pack_out

	void mapper(const unsigned char *i, gr_complex *o); //faz o mapeamento

	void demapper_soft(const gr_complex *i, float *o); // faz o demap de i em o (LLR)
	void demapper_hard(const gr_complex *i, unsigned char *o); // faz o demap de i em o (bit)

};

#endif
