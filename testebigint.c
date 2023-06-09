/* Lívia Lutz dos Santos - 2211055 - 3WB */

#include <stdio.h>
#include "bigint.h"

/* Função para testar se a resposta obtida é igual a resposta esperada para cada teste */

int testa_certo(BigInt a, BigInt b, char *msg, int test) {

   /* Variável para contar erros */

   int erro = 0;

   /* Percorre os arrays BigInt comparando cada byte */
   
   for (int i = 0; i < (NUM_BITS/8); i++){

      /* Se os bytes foram diferentes, aponta o erro e define que erro = 1 */

      if (a[i] != b[i]){
         printf("Erro: %02x no byte %d\n",a[i],i);
         erro = 1;
      } 

   }

   /* Se teve erro, exibe mensagem indicando onde está o erro */
      
   if (erro == 1){
      printf("Erro em %s no teste %d\n", msg, test);
   }

   /* Retorna erro */
      
   return erro;
}

int teste_da_big_val (char*msg) {

   /* Variável para contar erros nos testes */

   int erros = 0;

   /* Testando extensão de um número positivo (1) */

   BigInt resp1 = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

   /* Variável que guarda o valor de todas as chamadas da função */

   BigInt res;
   big_val (res, 1);

   /* Se houveram erros, adicona 1 a variável de contagem de erros */
   
   if (testa_certo(res, resp1, msg, 1) == 1){
      erros += 1;
   } 

   /* Testando a extensão de um número negativo (-2) */


   BigInt resp2 = {0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
   big_val (res, -2);

   /* Se houveram erros, adicona 1 à variável de contagem de erros */
   
   if (testa_certo(res, resp2, msg, 2) == 1){
      erros += 1;
   }

   /* Testando a extensão de 0 */ 

   BigInt resp3 = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

   big_val(res,0);

   /* Se houveram erros, adiciona 1 a variável de contagem de erros */

    if (testa_certo(res, resp3, msg, 3) == 1){
      erros += 1;
   }

   /* Testando a extensão de um número positivo grande (65536) */

   BigInt resp4 = {0x00, 0x00, 0x01, 0x00, 0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

   big_val(res, 65536);

   /* Se houveram erros, adiciona 1 à variável de contagem de erros */

    if (testa_certo(res, resp4, msg, 4) == 1){
      erros += 1;
   }

   /* Testando a extensão de um número negativo grande (-65536) */

   BigInt resp5 = {0x00,0x00,0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

   big_val(res, -65536);

    if (testa_certo(res, resp5, msg, 5)){
      erros += 1;
   }

   /* Retorna 1 (False) se tivemos erros ou 0 (True) se não tivemos erros */

   return (erros != 0);
}

int teste_da_big_comp2(char*msg) {

   /* Variável para contar erros nos testes */

   int erros = 0;

   /* Variáveis para guardar os resultados gerados por cada chamada de função para número positivo */

   BigInt res,res1;

   /* Testando o complemento a 2 de um número positivo (5) */

   /* Estratégia usada: Estendi o valor que usarei para fazer o teste e o valor do resultado esperado de um long para BigInt para
     depois comparar os arrays dos 2 números estendidos, aplicando essa estratégia em todo programa de teste */

   big_val(res, 5);
   big_val(res1, -5);
   
   big_comp2(res, res);

   if (testa_certo(res, res1, msg, 1) == 1){
      erros += 1;
   }

   /* Testando o complemento a 2 de um número negativo (-7) */

   BigInt res2,res3;

   big_val(res2,-7);

   big_val(res3,7);

   big_comp2(res2, res2);

   if (testa_certo(res2, res3, msg, 2) == 1){
      erros += 1;
   }

   /* Testando o complemento a 2 de 0 */

   BigInt res4;

   big_val(res4,0);

   big_comp2(res4, res4);

   if (testa_certo(res4, res4, msg, 3) == 1){
      erros += 1;
   }

   /* Testando o complemento a 2 de um número muito grande (4294967296) */

   BigInt res5,res6;

   big_val(res5,4294967296);

   big_val(res6,-4294967296);

   big_comp2(res5, res5);

   if (testa_certo(res5, res6, msg, 4) == 1){
      erros += 1;
   }

   /* Retorna 1 (False) se tivemos erros ou 0 (True) se não tivemos erros */

   return (erros != 0);
}

int teste_da_big_sum(char*msg) {

   /* Variável para contar erros nos testes */

   int erros = 0;

   /* Variáveis para guardar a extensão de cada número a ser usado nos testes */

   BigInt a,b,c,d,pos,grande,f;

   /* Variáveis para guardar os resultados gerados por cada chamada de função */

   BigInt res,res1,res2,res3;

   /* Extendendo números positivo, negativo, zero e grande (overflow) */

   big_val(a, 10);

   big_val(b,-8);

   big_val(c,0);

   big_val(d,4294967296);

   /* Resultados esperados */

   /* a + b = 2 */

   big_val(pos,2);

   big_sum(res,a,b);

   if (testa_certo(res, pos, msg, 1) == 1){
      erros += 1;
   }

   /* a + c = 10 */

   big_sum(res1,a,c);

   if (testa_certo(res1, a, msg, 2) == 1){
      erros += 1;
   }

   /* d + d = 8589934592 */

   big_val(grande,8589934592);

   big_sum(res2,d,d);

   if (testa_certo(res2, grande, msg, 3) == 1){
      erros += 1;
   }

   /* b + b = -16 */

   big_val(f,-16);

   big_sum(res3,b,b);

   if (testa_certo(res3, f, msg, 4) == 1){
      erros += 1;
   }


   return (erros != 0);

}

int teste_da_big_sub(char*msg) {

   /* Variável para contar erros nos testes */

   int erros = 0;

   /* Variáveis para guardar a extensão de cada número a ser usado nos testes */

   BigInt a,b,c,d,e,f,pos,grande;

   /* Variáveis para guardar os resultados gerados por cada chamada de função */

   BigInt res,res1,res2,res3;

   /* Testando com número positivo, negativo, zero e grande */ 

   big_val(a, 6);

   big_val(b,-3);

   big_val(c,0);

   big_val(d,4294967296);

   big_val(e,4294967587);

   /* resultados esperados */

   /* a - b = 9 */

   big_val(pos,9);

   big_sub(res,a,b);

   if (testa_certo(res, pos, msg, 1) == 1){
      erros += 1;
   }

   /* a - c = a */

   big_sub(res1,a,c);

   if (testa_certo(res1, a, msg, 2) == 1){
      erros += 1;
   }

   /* d - e = −291 */

   big_val(grande,-291);

   big_sub(res2,d,e);

   if (testa_certo(res2, grande, msg, 3) == 1){
      erros += 1;
   }

   /* b - a = -9 */

   big_val(f,-9);

   big_sub(res3,b,a);

   if (testa_certo(res3, f, msg, 4) == 1){
      erros += 1;
   }

   return (erros != 0);

}

int teste_da_big_mul(char*msg){

   /* Variável para contar erros nos testes */

   int erros = 0;

   /* Variáveis para guardar a extensão de cada número a ser usado nos testes */

   BigInt a,b,c,d,e,f;

   /* Variáveis para guardar os resultados esperados */

   BigInt pos,grande,g;

   /* Variáveis para guardar os resultados gerados por cada chamada de função */

   BigInt res,res1,res2,res3;

   /*Extendendo os valores a serem usados: Números positivo, negativo, zero e muito grande (com overflow)*/

   big_val(a, 5);

   big_val(b, -3);

   big_val(c, 0);

   big_val(d, 4294967296);

   big_val(e, 1500000000);

   big_val(f, -128);

   big_val(pos, -15);

   big_val(grande, 6442450944000000000);

   big_val(g, -549755813888);

   /* a * b = -15 */

   big_mul(res,a,b);

   if (testa_certo(res, pos, msg, 1) == 1){
      erros += 1;
   }

   /* a * c = 0 */

   big_mul(res1,a,c);

   if (testa_certo(res1, c, msg, 2) == 1){
      erros += 1;
   }

   /* d * e = 6442450944000000000 */

   big_mul(res2,d,e);

   if (testa_certo(res2, grande, msg, 3) == 1){
      erros += 1;
   }

   /* d * f = −549755813888 */
  
   big_mul(res3,d,f);

   if (testa_certo(res3, g, msg, 4) == 1){
      erros += 1;
   }

   return(erros != 0);

}

int teste_da_big_shl(char*msg){

   /* Variável para contar erros nos testes */

   int erros = 0;

   /* Variáveis para guardar a extensão de cada número a ser usado nos testes (Números positivo e negativo) */

   BigInt a,b;

   /* Variáveis para guardar os resultados esperados para números positivos */

   BigInt res,res1,res2,res3;

   /* Variáveis para guardar os resultados das chamadas da função */

   BigInt pos,pos1,pos2,pos3;

   /* Variáveis para guardar os resultados esperados para números negativos */

   BigInt res4,res5,res6,res7;

   /* Variáveis para guardar os resultados das chamadas da função */

   BigInt neg,neg1,neg2,neg3;

   /* Extendendo um número positivo e um negativo */

   big_val(a, 256);

   big_val(b, -256);

   /* Testes do número positivo */

   /* Shift de 0 bits para  */

   big_shl(res,a,0);

   big_val(pos, 256);

   if (testa_certo(res, pos, msg, 1) == 1){
      erros += 1;
   }

   /* Shift de 127 bits */

   big_shl(res1,a,127);

   big_val(pos1, 0);

   if (testa_certo(res1, pos1, msg, 2) == 1){
      erros += 1;
   }

   /* Shift de 8 bits */

   big_shl(res2,a,8);

   big_val(pos2, 65536);

   if (testa_certo(res2, pos2, msg, 3) == 1){
      erros += 1;
   }

   /* Shift de 7 bits */

   big_shl(res3,a,7);

   big_val(pos3, 32768);

   if (testa_certo(res3, pos3, msg, 4) == 1){
      erros += 1;
   }

   /* Testes do número negativo */

   /* Shift de 0 bits */

   big_shl(res4,b,0);

   big_val(neg, -256);

   if (testa_certo(res4, neg, msg, 5) == 1){
      erros += 1;
   }

   /* Shift de 127 bits */

   big_shl(res5,b,127);

   big_val(neg1, 0);

   if (testa_certo(res5, neg1, msg, 6) == 1){
      erros += 1;
   }

   /* Shift de 8 bits */

   big_shl(res6,b,8);

   big_val(neg2, -65536);

   if (testa_certo(res6, neg2, msg, 7) == 1){
      erros += 1;
   }

   /* Shift de 7 bits */

   big_shl(res7,b,7);

   big_val(neg3, -32768);

   if (testa_certo(res7, neg3, msg, 8) == 1){
      erros += 1;
   }

   return(erros != 0);

}

int teste_da_big_shr(char*msg){

   /* Variável para contar erros nos testes */

   int erros = 0;

   /* Variáveis para guardar a extensão de cada número a ser usado nos testes (Números positivo e negativo) */

   BigInt a,b;

   /* Variáveis para guardar o retorno esperado para cada chamada de função (Números positivos) */

   BigInt res,res1,res2,res3;

   /* Variáveis para guardar os resultados esperados para números positivos */

   BigInt pos,pos1,pos2,pos3;

   /* Variável para guardar o resultado esperado para números negativos */

   BigInt neg;

   /* Variáveis para guardar o retorno esperado para cada chamada de função (Números negativos) */

   BigInt res4,res5;

   /* Extendendo um número positivo e um negativo */

   big_val(a, 256);

   big_val(b, -1);

   /* Testes para número positivo */

   /* Shift de 0 bits */

   big_shr(res,a,0);

   big_val(pos, 256);

   if (testa_certo(res, pos, msg, 1) == 1){
      erros += 1;
   }

   /* Shift de 127 bits */

   big_shr(res1,a,127);

   big_val(pos1,0);

   if (testa_certo(res1, pos1, msg, 2) == 1){
      erros += 1;
   }

   /* Shift de 8 bits */

   big_shr(res2,a,8);

   big_val(pos2, 1);

   if (testa_certo(res2, pos2, msg, 3) == 1){
      erros += 1;
   }

   /* Shift de 7 bits */

   big_shr(res3,a,7);

   big_val(pos3, 2);
   
   if (testa_certo(res3, pos3, msg, 4) == 1){
      erros += 1;
   }

   /* Testes para números negativos */

   /* Shift de 0 bits */

   big_shr(res4,b,0);

   big_val(neg, -1);

   if (testa_certo(res4, neg, msg, 5) == 1){
      erros += 1;
   }

   /* Shift de 7 bits */

   big_shr(res5,b,7);

   BigInt neg2 = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01};

   if (testa_certo(res5, neg2, msg, 6) == 1){
      erros += 1;
   }

   /* Shift de 16 */

   BigInt res6;

   big_shr(res6,b,16);

   BigInt neg3 = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00};

   if (testa_certo(res6, neg3, msg, 7) == 1){
      erros += 1;
   }

   /* Shift de 127 */

   BigInt res7;

   big_shr(res7,b,127);

   BigInt neg4 = {0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

   if (testa_certo(res7, neg4, msg, 8) == 1){
      erros += 1;
   }

   return (erros!=0);
}

int teste_da_big_sar(char*msg){

   /* Variável para contar erros nos testes */

   int erros = 0;

   /* Variáveis para extensão de cada número a ser usado nos testes (números positivo e negativo) */

   BigInt a,b;

   /* Variáveis para guardar o resultado da chamada da função para cada shift de número negativo */

   BigInt res,res1,res2,res3;

   /* Variáveis para guardar os resultados esperados para números negativos */

   BigInt pos,pos1,pos2,pos3;

   /* Variáveis para guardar o resultado da chamada da função para cada shift de número negativo */

   BigInt res4,res5,res6,res7;

   /* Variáveis para guardar os resultados esperados para números negativos */

   BigInt pos4,pos5,pos6,pos7;

   /*Extendendo valores a serem usados nos testes (Números positivo e negativo)*/

   big_val(a, -256);

   big_val(b, 256);

   /* Testes para número positivo */

   /* Shift de 0 bits */

   big_sar(res,a,0);

   big_val(pos, -256);

   if (testa_certo(res, pos, msg, 1) == 1){
      erros += 1;
   }

   /* Shift de 127 bits */

   big_sar(res1,a,127);

   big_val(pos1, -1);

   if (testa_certo(res1, pos1, msg, 2) == 1){
      erros += 1;
   }

   /* Shift de 8 bits */

   big_sar(res2,a,8);

   big_val(pos2, -1);

   if (testa_certo(res2, pos2, msg, 3) == 1){
      erros += 1;
   }

   /* Shift de 7 bits */

   big_sar(res3,a,7);

   big_val(pos3, -2);

   if (testa_certo(res3, pos3, msg, 4) == 1){
      erros += 1;
   }

   /* Shift de 0 bits */

   big_sar(res4,b,0);

   big_val(pos4, 256);

   if (testa_certo(res4, pos4, msg, 5) == 1){
      erros += 1;
   }

   /* Shift de 127 bits */

   big_sar(res5,b,127);

   big_val(pos5, 0);

   if (testa_certo(res5, pos5, msg, 6) == 1){
      erros += 1;
   }

   /* Shift de 8 bits */

   big_sar(res6,b,8);

   big_val(pos6, 1);

   if (testa_certo(res6, pos6, msg, 7) == 1){
      erros += 1;
   }

   /* Shift de 7 bits */

   big_sar(res7,b,7);

   big_val(pos7, 2);

   if (testa_certo(res7, pos7, msg, 8) == 1){
      erros += 1;
   }

   return (erros!=0);
}

int main() {

   /* Variável para contar erros nos testes */
   int erros = 0;

   /* Para cada chamada de cada função de teste, somamos o retorno a erros */
   
   erros += teste_da_big_val("big_val");
   erros += teste_da_big_comp2("big_comp2");
   erros += teste_da_big_sum("big_sum");
   erros += teste_da_big_sub("big_sub");
   erros += teste_da_big_mul("big_mul");
   erros += teste_da_big_shl("big_shl");
   erros += teste_da_big_shr("big_shr");
   erros += teste_da_big_sar("big_sar");

   /* Exibimos quantos erros tivemos em comparacao com a quantidade de testes feitos */

   printf("Total de falhas %d de 45\n", erros);
   return 0;
}

