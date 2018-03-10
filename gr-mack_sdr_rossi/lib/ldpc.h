#ifndef BCH_H
#define BCH_H

class bch
{
private:
	int n; //quantidade de bits de entrada
	int k; //quantidade de bits de saída
	int n_extension; //numero de zeros a adicionar ao inicio da palavra-codigo recebida para obter n+n_extension = (2^m)-1
	bool tipo; //false = tipo A, true = tipo B
	unsigned char *pol_primitivo; //polinomio primitivo
	unsigned char *pol_gerador; //polinomio gerador

	int *GF; //campo de galois [potencias] = valor decimal
	int *inv_GF; //campo de galois [valor decimal] = potencias
	int *tab_inv_alpha; //tabela inversa alpha
	int *tab_inv_dec; //tabela inversa decimal

	int *p_erros; //posicao dos erros

public:
	void init(int n, int k); //inicializa variavais

	void encode(unsigned char *u, unsigned char *v); // codifica u[k] em v[n+n_extension] (nao funciona direito)
	bool decode(unsigned char *rr, int &n_err); //decodifica [r] e retorna sucessso (true) ou fracasso (false) na decodificação
};

#endif
