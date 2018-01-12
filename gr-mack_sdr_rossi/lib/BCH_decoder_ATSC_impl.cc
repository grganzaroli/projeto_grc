/* -*- c++ -*- */
/* 
 * Copyright 2017 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "BCH_decoder_ATSC_impl.h"
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <volk/volk.h>
#pragma warning	(disable: 4996)

//BCH 10/15 short_frame (10800,10632,12) - 168 bits de paridade

#define m 14
#define n 10800 //acrescentar n_extension zeros no come�o do vetor recebido ate atingir 16383 amostras
#define k 10632	
#define n_extension 5583  //numero de zeroas a acrescntar em n
#define t 12
int pol_gerador[n-k+1] = {1,0,1,0,0,0,0,0,0,0,1,1,0,0,0,1,0,1,1,0,1,1,0,1,1,1,1,1,0,1,0,1,0,1,0,0,1,1,0,0,0,0,1,1,0,1,0,0,1,1,0,1,1,
0,0,1,0,0,1,1,0,0,0,1,0,1,1,0,0,1,1,0,1,0,0,1,0,0,0,1,1,1,0,1,0,0,0,1,1,1,0,0,1,0,0,0,0,0,1,1,0,1,0,0,1,0,1,0,1,0,0,1,0,1,0,0,0,1,1,
1,1,1,1,1,0,0,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,0,0,1,0,0,0,1,1,0,0,1,0,0,0,0,0,1,0,1,1,0,1,0,0,1,0,1}; //(norma)
int pol_primitivo[m+1] = {1,1,0,1,0,1,0,0,0,0,0,0,0,0,1};

//BCH 10/15 normal_frame (43200,43008,12) - 192 bits de paridade
/*
#define m 16
#define n 43200 //acrescentar n_extension zeros no come�o do vetor recebido ate atingir 65535 amostras
#define k 43008	
#define n_extension 22335  //numero de zeroas a acrescntar em n
#define t 12
int pol_gerador[n-k+1] = {1,0,1,0,0,1,1,1,0,0,0,1,0,0,1,1,0,0,0,0,0,1,1,1,0,1,0,0,0,0,0,1,1,1,0,0,0,0,1,0,0,0,1,0,1,1,1,0,0,0,1,0,1,
0,0,0,1,0,0,0,1,1,1,0,0,0,1,0,1,0,0,0,0,1,1,0,0,1,1,1,1,0,0,1,0,1,1,0,0,1,1,0,1,1,0,0,0,1,1,0,1,1,1,0,0,0,0,1,1,0,1,0,1,0,0,0,0,1,0,
0,0,1,0,0,0,1,0,0,1,0,0,0,0,0,0,1,1,0,1,0,0,0,1,1,1,1,0,0,0,0,1,0,1,1,1,1,1,0,1,1,1,0,1,1,0,0,1,1,0,0,0,0,0,0,0,1,0,0,1,0,1,0,1,0,1,
1,1,1,0,0,1,1,1}; //(norma)
//int pol_primitivo[m+1] = {1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,1,1}; // NAO RECONHECEU
int pol_primitivo[m+1] = {1,1,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1}; // NAO RECONHECEU (MATLAB)
//int pol_primitivo[m+1] = {1,0,0,1,1,1,0,0,0,1,1,0,0,1,0,1,1}; // NAO RECONHECEU
//int pol_primitivo[m+1] = {1,1,0,1,0,0,1,1,0,0,0,1,1,1,0,0,1}; // NAO RECONHECEU
//int pol_primitivo[m+1] = {1,0,0,1,1,0,1,1,0,1,1,0,0,0,0,1,1};	// NAO RECONHECEU		
//int pol_primitivo[m+1] = {1,1,0,0,0,0,1,1,0,1,1,0,1,1,0,0,1}; // NAO RECONHECEU
//int pol_primitivo[m+1] = {1,1,0,0,0,1,1,1,0,0,1,0,0,0,1,1,1};	// NAO RECONHECEU	
//int pol_primitivo[m+1] = {1,1,1,0,0,0,1,0,0,1,1,1,0,0,0,1,1}; // NAO RECONHECEU
//int pol_primitivo[m+1] = {1,1,0,0,0,1,1,1,1,0,1,0,1,0,1,1,1};	// NAO RECONHECEU		
//int pol_primitivo[m+1] = {1,1,1,0,1,0,1,0,1,1,1,1,0,0,0,1,1}; // NAO RECONHECEU
//int pol_primitivo[m+1] = {1,1,0,0,0,1,1,0,0,1,1,1,0,1,1,1,1};	// NAO RECONHECEU		
//int pol_primitivo[m+1] = {1,1,1,1,0,1,1,1,0,0,1,1,0,0,0,1,1}; // NAO RECONHECEU
//int pol_primitivo[m+1] = {1,0,0,0,0,0,0,1,1,1,1,0,1,1,1,0,1};	// NAO RECONHECEU
//int pol_primitivo[m+1] = {1,0,1,1,1,0,1,1,1,1,0,0,0,0,0,0,1}; // NAO RECONHECEU
//int pol_primitivo[m+1] = {1,0,1,1,1,0,1,0,0,1,0,0,0,0,0,0,1};	// NAO RECONHECEU			
//int pol_primitivo[m+1] = {1,0,0,0,0,0,0,1,0,0,1,0,1,1,1,0,1}; // NAO RECONHECEU
//int pol_primitivo[m+1] = {1,0,1,0,0,0,1,0,1,0,0,0,0,1,0,1,1};	// NAO RECONHECEU			
//int pol_primitivo[m+1] = {1,1,0,1,0,0,0,0,1,0,1,0,0,0,1,0,1}; // NAO RECONHECEU
//int pol_primitivo[m+1] = {1,0,1,1,1,0,0,0,0,0,1,1,0,1,1,0,1};	// NAO RECONHECEU			
//int pol_primitivo[m+1] = {1,0,1,1,0,1,1,0,0,0,0,0,1,1,1,0,1}; // NAO RECONHECEU
//int pol_primitivo[m+1] = {1,1,0,0,0,0,1,0,0,0,1,1,0,1,1,1,1};	// NAO RECONHECEU			
//int pol_primitivo[m+1] = {1,1,1,1,0,1,1,0,0,0,1,0,0,0,0,1,1}; // NAO RECONHECEU
*/

//VARIAVEIS AUXILIARES
int *GF; //campo de galois [potencias] = valor decimal
int *inv_GF; //campo de galois [valor decimal] = potencias
int aux_GF[2][m+1] = {0}; //auxiliar para calcular o valor decimal
int *tab_inv_alpha; //tabela inversa alpha
int *tab_inv_dec; //tabela inversa decimal
unsigned char *r; //palavra c�digo recebida
unsigned char *err; //vetor com as posi��es de erro
int sindrome[2*t+1] = {0}; //sindrome da palavra recebida

//DECODIFICADOR PETERSON (GAUSS)
int S[t][t+1] = {0}; //matriz s�ndrome
int LAMBDA[t+1] = {0}; //vetor lambda final
int aux_LAMBDA[t+1] = {0}; //vetor lambda final auxiliar
int lamb = 0; //lambda com alpha substituido
int inv_S_i_i; //inverso de S[i][i]
int n_err = t; //numero de erros
int pos_err[t] = {0}; //posi��o dos erros
int teste_erros[t] = {0}; //posi�ao dos erros a serem testados
unsigned char *aux_r; //auxiliar para calcular r no metodo de gauss
int pre_sindrome[2*t+1] = {0}; //pre-sindrome da palavra no metodo de gauss

namespace gr {
  namespace mack_sdr_rossi {

    BCH_decoder_ATSC::sptr
    BCH_decoder_ATSC::make(size_t N)
    {
      return gnuradio::get_initial_sptr
        (new BCH_decoder_ATSC_impl(N));
    }

    /*
     * The private constructor
     */
    BCH_decoder_ATSC_impl::BCH_decoder_ATSC_impl(size_t N)
      : gr::block("BCH_decoder_ATSC",
              gr::io_signature::make(1, 1, sizeof(unsigned char)*N),
              gr::io_signature::make(1, 1, sizeof(unsigned char)*(10632)))
        {
          N_size = N;
          //ESSA PARTE RODA SÓ UMA VEZ

          unsigned int alignment = volk_get_alignment();

          GF = (int*)volk_malloc(sizeof(int)*(n+n_extension), alignment);
          inv_GF = (int*)volk_malloc(sizeof(int)*(n+n_extension+1), alignment);
          tab_inv_alpha = (int*)volk_malloc(sizeof(int)*(n+n_extension), alignment);
          tab_inv_dec = (int*)volk_malloc(sizeof(int)*(n+n_extension), alignment);
          r = (unsigned char*)volk_malloc(sizeof(unsigned char)*(n+n_extension), alignment);
          err = (unsigned char*)volk_malloc(sizeof(unsigned char)*(n+n_extension), alignment);
          aux_r = (unsigned char*)volk_malloc(sizeof(unsigned char)*(n+n_extension), alignment);

          //zerar vari�veis
          
          memset (GF, 0, sizeof(GF[0])*(n+n_extension));
          memset (inv_GF, 0, sizeof(inv_GF[0])*(n+n_extension+1));
          memset (tab_inv_alpha, 0, sizeof(tab_inv_alpha[0])*(n+n_extension));
          memset (tab_inv_dec, 0, sizeof(tab_inv_dec[0])*(n+n_extension));
          memset (r, 0, sizeof(r[0])*(n+n_extension));
          memset (err, 0, sizeof(err[0])*(n+n_extension));
          memset (aux_r, 0, sizeof(aux_r[0])*(n+n_extension));

          printf("BCH - VARIAVEIS ZERADAS OK\n");

          // ------------------------------CAMPO DE GALOIS 2^m -----------------------------

          int index = m;

          for(int i = 0; i < n+n_extension; i++) // cada linha (potencia) do GF
          {
            for(int j = 0; j < m; j++) // zerar aux_GF
            {
              aux_GF[1][j] = aux_GF[0][j];
              aux_GF[0][j] = 0;
            }

            if(i < m)
              aux_GF[0][i] = 1;
            else if(i == m)
            {
              for(int j = 0; j < m; j++)
                aux_GF[0][j] = pol_primitivo[j];
            }
            else
            {
              for(int j = 0; j < m; j++)
                aux_GF[0][j+1] = aux_GF[1][j];

              if(aux_GF[0][m] == 1)
              {
                aux_GF[0][m] = 0;
                for(int j = 0; j < m; j++)
                {
                  aux_GF[0][j] = aux_GF[0][j]^pol_primitivo[j];
                }
              }
            }

            for(int j = 0; j < m; j++)
            {
              if(aux_GF[0][j] == 1)
              {
                GF[i] += pow(2, j);
              }
            }

            inv_GF[GF[i]] = i;
          }         

          printf("BCH - CAMPO DE GALOIS OK\n");

          // ------------------------------TABELA INVERSA -----------------------------

          for(int i = 0; i <= (n+n_extension); i++)
          {
            for(int j = 0; j <= (n+n_extension); j++)
            {
              //if(tab_multi[i][j] == 1)
              if(tab_mult(i,j) == 1)
              {
                tab_inv_dec[i-1] = j; // tabela inversa decimal

                for(int l = 1; l < (n+n_extension)+1; l++)
                {
                  if(GF[l] == i)
                  {
                    for(int L = 1; L < (n+n_extension)+1; L++)
                    {
                      if(GF[L] == j)
                        tab_inv_alpha[l] = L;
                    }
                  }
                }
                break;
              }
            }
          }

          printf("BCH - TABELA INVERSA OK\n");

        }

  /*
    * Our virtual destructor.
    */
  BCH_decoder_ATSC_impl::~BCH_decoder_ATSC_impl()
  {
  }

  void
  BCH_decoder_ATSC_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
  {
    ninput_items_required[0] = noutput_items;
  }

  int BCH_decoder_ATSC_impl::tab_mult(int multi1, int multi2)
  {
    if((multi1 == 0)||(multi2 == 0))
      return 0;
    else
      return GF[(inv_GF[multi1]+inv_GF[multi2])%(n+n_extension)];
  }

	//ESCREVER FUNÇÃO AQUI
	void BCH_decoder_ATSC_impl::decoder_BCH(const char *in, char *out)
	{	
    //FUNÇÃO PRINCIPAL

    int count = 0;

    //copiar entrada para um vetor que eu possa manipular e zerar vetor de erro

    memset (r,0, sizeof(r[0])*(n+n_extension));
    //memcpy(&r[n_extension],&in[0], sizeof(r[0])*(n));

    for (int j = 0; j < n; j++) //grandes
    {
      r[n-1-j] = in[j];
    }

    //zerar vetor de erros e sindrome
    
    memset (err,0, sizeof(err[0])*(n+n_extension));
    memset (sindrome,0, sizeof(sindrome[0])*(2*t+1));
    memset (pos_err,0, sizeof(pos_err[0])*(t));
    
    n_err = t;
    /*
    FILE *F = fopen("vetor_IN_BCH.txt", "w+");
    for (int j = 0; j < (n+n_extension); j++)
    {
        fprintf(F, "%i", r[j]);
    }
    fprintf(F, "\n");
    fclose(F);
    printf("vetor_IN OK\n");
    */
		// ------------------------------SINDROME BCH - METODO DE HORNER ------------------------------

    for(int i = 1; i < 2*t+1; i++)
    {
      for(int j = 0; j < (n+n_extension); j++)
      {
        sindrome[i] = sindrome[i]^(tab_mult(r[j],GF[(i*j)%(n+n_extension)])); //soma em binario
      }
    }

    for(int i = 0; i < 2*t; i++)
    {
      sindrome[i] = sindrome[i+1];
    }
    sindrome[2*t] = 0;

    int aux_s = 1; //auxiliar para verificar sindromes

    for(int l = 0; l < 2*t+1; l++)
    {
      if(sindrome[l] == 0)
        aux_s = aux_s*1;
      else
        aux_s = 0;
    }
    /*
    for(int l = 0; l < 2*t+1; l++)
    {
      printf("%i ", sindrome[l]);
    }
    printf("\n");
    */
    if(aux_s == 1)
    {
      printf("SINAL RECEBIDO OK\n"); // ------------ FIM ------------
      goto end;
    }

    // ------------------------------SINDROME BCH - CALCULO DO POLINOMIO LAMBDA - PETERSON (GAUSS) (https://martin-thoma.com/solving-linear-equations-with-gaussian-elimination/)------------------------------

    //calcular as matrizes S e C
    for(int i = 0; i < t; i++)
    {
      for(int j = 0; j < t; j++)
      {
        S[i][j] = sindrome[i+j];
      }

      S[i][t] = sindrome[i+t];
    }
    /*
    for(int i = 0; i < t; i++)
    {
      for(int j = 0; j < t; j++)
      {
        printf("%.5i ", S[i][j]);
      }
      printf("\n");
    }
    printf("\n");
    */
    //----------------------------------------------------------------
    for(int i=0; i<t; i++) 
    {
      // Search for maximum in this column
      int maxEl = S[i][i];
      int maxRow = i;
      for (int j=i+1; j<t; j++) 
      {
        if (S[j][i] > maxEl) 
        {
          maxEl = S[j][i];
          maxRow = j;
        }
      }

      // Make all rows below this one 0 in current column
      for (int KK=i+1; KK<t; KK++) 
      {

        if(S[i][i] == 0)
				  inv_S_i_i = 0;
		  	else
			  	inv_S_i_i = tab_inv_dec[S[i][i]-1];

        int c = tab_mult(S[KK][i],inv_S_i_i);
        for (int j=i; j<t+1; j++) 
        {
          if (i==j) 
            S[KK][j] = 0;
          else 
          {
            S[KK][j] = S[KK][j]^tab_mult(c,S[i][j]);
          }
        }
      }
      /*
      for(int i = 0; i < t; i++)
      {
        for(int j = 0; j < t; j++)
        {
          printf("%.5i ", S[i][j]);
        }
        printf("\n");
      }
      printf("\n");
      */
    }

    // Solve equation Ax=b for an upper triangular matrix S
    for (int i=t-1; i>=0; i--) 
    {

      if(S[i][i] == 0)
        inv_S_i_i = 0;
      else
        inv_S_i_i = tab_inv_dec[S[i][i]-1];

      aux_LAMBDA[i] = tab_mult(S[i][t],inv_S_i_i);
      for (int j=i-1;j>=0; j--) 
      {
        S[j][t] = S[j][t] ^ tab_mult(S[j][i],aux_LAMBDA[i]);
      }

    }
    //----------------------------------------------------------------

    for(int i = 0; i <= t; i++)
    {
      LAMBDA[i] = aux_LAMBDA[t-i];
    }

    LAMBDA[0] = 1;
    // ------------------------------DECODIFICADOR BCH - ENCONTRAR POSI��O DOS ERROS - FORNEY ------------------------------

    count = 0;

    for(int i = 0; i < (n+n_extension); i++)
    {
      lamb = 0;
      for(int j = 0; j <= t; j++)
      {
        if(j == 0)
          lamb = LAMBDA[j];
        else
        {
          lamb = lamb^tab_mult(LAMBDA[j],GF[tab_inv_alpha[(i*j)%(n+n_extension)]]);
        }
      }

      if(lamb == 0)
      {
        err[i] = 1;

        pos_err[count] = i;
        count++;
      }
    }

    //o numero de erros � dado pelo numero de linhas n�o-nulas da matriz S.
    //se 1 > n_err > t, eu calculo todas as possibilidades de posi��o de erro at� a sindrome zerar que d� no m�ximo 924 tentativas para 6 de 12 bits de erro

    int gamb;

    //contar numero de erros
    for(int i = t-1; i >= 0; i--)
    {
      gamb = 0;
      for(int j = 0; j <= t; j++)
      {
        gamb = gamb + S[i][j];
      }

      if(gamb == 0)
      {
        n_err--;
      }
    }

    if(n_err < t)
    {
      //PR�-SINDROME (deixar calculadoas s�ndromes das posi�oes que est�o certas)

      memset (pre_sindrome,0, sizeof(pre_sindrome[0])*(2*t+1));

      int a = 0;

      for(int I = 1; I < 2*t+1; I++)
      {
        for(int j = 0; j < (n+n_extension); j++)
        {
          if(j != pos_err[a]) //ignorar posi�oes com erro
          {
            pre_sindrome[I] = pre_sindrome[I]^(tab_mult(aux_r[j],GF[(I*j)%(n+n_extension)])); //soma em binario
          }
          else 
          {
            a++;
          }
        }
        a = 0;
      }
      //permutar os erros
      int aux;
      for(int i = 0; i < pow(2, t); i++)
      {
        again:
      
        count = 0;
        aux = i;
        for(int j = 0; j < t; j++)
        {
          if(aux%2 == 1)
          {
            teste_erros[j] = 1;
            count ++;
          }
          else
            teste_erros[j] = 0;

          if(count > n_err)//mais erros que n_err, nao preciso testar
          {
            i++;
            goto again;
          }

          aux = aux/2;
        }
        
        if(count < n_err)//menos erros que n_err, nao preciso testar
        {
          i++;
          goto again;
        }

        for(int ii = 0; ii < (n+n_extension); ii++)
        {
          aux_r[ii] = r[ii];
        }

        for(int ii = 0; ii < t; ii++)
        {
          if(teste_erros[ii] == 1)
            aux_r[pos_err[ii]] = aux_r[pos_err[ii]]^1;
        }

        //CALCULAR SINDROME (GAUSS)

        for(int I = 0; I < 2*t+1; I++)
        {
          sindrome[I] = pre_sindrome[I];
        }

        for(int I = 1; I < 2*t+1; I++)
        {
          for(int j = 0; j < n_err; j++)
          {
            sindrome[I] = sindrome[I]^(tab_mult(aux_r[pos_err[j]],GF[(I*pos_err[j])%(n+n_extension)])); //soma em binario
          }
        }

        for(int I = 0; I < 2*t; I++)
        {
          sindrome[I] = sindrome[I+1];
        }
        sindrome[2*t] = 0;

        int aux_s = 1; //auxiliar para verificar sindromes

        for(int l = 0; l < 2*t+1; l++)
        {
          if(sindrome[l] == 0)
            aux_s = aux_s*1;
          else
            aux_s = 0;
        }

        if(aux_s == 1)
        {
          for(int I = 0; I < (n+n_extension); I++)
          {
            r[I] = aux_r[I];
          }
          printf("%i ERROS, SINAL CORRIGIDO\n", n_err); // ------------ FIM ------------
          goto end;
        }
      }
    }
    else if (n_err == t)
    {

      memset (sindrome,0, sizeof(sindrome[0])*(2*t+1));

      for(int ii = 0; ii < (n+n_extension); ii++)
      {
        aux_r[ii] = r[ii];
      }

      for(int i = 0; i < t; i++)
      {
        aux_r[pos_err[i]] = aux_r[pos_err[i]]^1;
      }

      //SINDROME (GAUSS)

      for(int i = 1; i < 2*t+1; i++)
      {
        for(int j = 0; j < (n+n_extension); j++)
        {
          sindrome[i] = sindrome[i]^(tab_mult(aux_r[j],GF[(i*j)%(n+n_extension)])); //soma em binario
        }
      }
  
      for(int i = 0; i < 2*t; i++)
      {
        sindrome[i] = sindrome[i+1];
      }
      sindrome[2*t] = 0;
  
      int aux_s = 1; //auxiliar para verificar sindromes
  
      for(int l = 0; l < 2*t+1; l++)
      {
        if(sindrome[l] == 0)
          aux_s = aux_s*1;
        else
          aux_s = 0;
      }

      if(aux_s == 1)
      {
        for(int I = 0; I < (n+n_extension); I++)
        {
          r[I] = aux_r[I];
        }
        printf("%i ERROS, SINAL CORRIGIDO\n", n_err); // ------------ FIM ------------
        goto end;
      }
      else
        printf("SINDROMES != 0, SINAL NAO CORRIGIDO\n"); // ------------ FIM ------------
    } 

    end:
      /*
      for(int l = 0; l < 10; l++)
      {
        printf("%i ", r[l+n_extension-4]);
      }
      printf("\n");
      for(int l = 0; l < t; l++)
      {
        printf("%i ", pos_err[l]);
      }
      printf("\n");
      for(int l = 0; l < 2*t+1; l++)
      {
        printf("%i ", sindrome[l]);
      }
      printf("\n");
      */
      
      //copiar saida

      for (int j = 0; j < k; j++) //grandes
      {
        out[k-1-j] = r[j];
      }

      //memcpy(&out[0],&r[n_extension], sizeof(out[0])*(k));

      /*
      for(int l = 0; l < 6; l++)
      {
        printf("%i ", out[l]);
      }
      printf("\n");
      */
	}


  int
  BCH_decoder_ATSC_impl::general_work (int noutput_items,
                      gr_vector_int &ninput_items,
                      gr_vector_const_void_star &input_items,
                      gr_vector_void_star &output_items)
  {
    const char *in = (const char *) input_items[0];
    char *out = (char *) output_items[0];

    // Do <+signal processing+>

    //FUNÇÃO RODA AQUI
    

    for (int nnn = 0; nnn < noutput_items; nnn++ )
    {
      decoder_BCH(in, &*out);
      
      //Incremento dos ponteiros para o GRC
      in += n;
      out += k;
    }
	  
      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (noutput_items);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace mack_sdr_rossi */
} /* namespace gr */

