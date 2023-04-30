/* Lívia Lutz dos Santos - 2211055 - 3WB */

#include <stdio.h>
#include "bigint.h"

int test_igual(BigInt a, BigInt b, char *msg, int test) {
   int deu_erro = 0;
   
   for (int i=0; i<(NUM_BITS/8); i++){

      if (a[i] != b[i]){
         printf("%02x no byte %d\n",a[i],i);
         deu_erro = 1;
      } 

   }
      
   if (deu_erro){
      printf("Erro em %s no teste %d\n", msg, test);
   }
      

   return deu_erro;
}

int test_big_val (char *msg) {
   int falhas = 0;
   BigInt gab1 = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
   BigInt res;
   big_val (res, 1);
   
   if (test_igual(res, gab1, msg, 1)){
      falhas += 1;
   } 

   BigInt gab2 = {0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
   big_val (res, -2);
   
   if (test_igual(res, gab2, msg, 2)){
      falhas += 1;
   } 

   return (falhas != 0);
}

int test_big_comp2(char *msg) {

   int falhas = 0;

   BigInt gab1 = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
   BigInt res;
   BigInt a = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
   BigInt b = {0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
   BigInt gab2 = {0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
   
   big_comp2(res,a);

   if (test_igual(res, gab1, msg, 1)){
      falhas += 1;
   }

   big_comp2(res,b);

   if (test_igual(res, gab2, msg, 2)){
      falhas += 1;
   } 

   return (falhas != 0);
}

int test_big_sum(char *msg) {
   int falhas = 0;

   BigInt a = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
   BigInt b = {0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
   BigInt res;
   BigInt gab1 = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
   
   big_sum(res, a, b);

   if (test_igual(res, gab1, msg, 1)){
      falhas += 1;
   }

   return (falhas != 0);

}

int test_big_sub(char*msg) {
   int falhas = 0;

   BigInt a = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
   BigInt b = {0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
   BigInt res;
   BigInt gab1 = {0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
   BigInt gab2 = {0xFD, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE};

   big_sub(res,a,b);

   if (test_igual(res, gab1, msg, 1)){
      falhas += 1;
   }

   big_sub(res,b,a);

   if (test_igual(res, gab2, msg, 2)){
      falhas += 1;
   }

   return (falhas != 0);

}

/*int teste_big_mul(char*msg){
   int falhas = 0;
   BigInt a = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
   BigInt b = {0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
   BigInt res;
   BigInt gab1; //definir o gabarito

   big_mul(res,a,b);

   if (test_igual(res, gab1, msg, 1)){
      falhas += 1;
   }

   return(falhas != 0);


}*/

int teste_big_shl(char*msg){
   int falhas = 0;

   BigInt a = { 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
   BigInt gab1 = { 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; 
   BigInt gab12 = { 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

   BigInt b = { 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

   BigInt gab2 = { 0x00, 0x00, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
   BigInt gab22 = { 0x00, 0x00, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

   BigInt res;

   big_shl(res,a,16);

   if (test_igual(res, gab1, msg, 1)){
      falhas += 1;
   }

   big_shl(res,a,5);

   if (test_igual(res, gab12, msg, 2)){
      falhas += 1;
   }

   big_shl(res,b,16);

   if (test_igual(res, gab2, msg, 4)){
      falhas += 1;
   }

   big_shl(res,b,18);

   if (test_igual(res, gab22, msg, 5)){
      falhas += 1;
   }

   return(falhas != 0);

}

int teste_big_shr(char*msg){
   /*int falhas = 0;
   BigInt a = { 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
   BigInt b = { 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};



   return (falhas!=0);*/

}

int teste_big_sar(char*msg);


int main() {
   int falhas = 0;
   
   falhas += test_big_val("big_val");
   falhas += test_big_comp2("big_comp2");
   falhas += test_big_sum("big_sum");
   falhas += test_big_sub("big_sub");
   //falhas += teste_big_mul("big_mul");
   falhas += teste_big_shl("big_shl");
   //falhas += teste_big_shr("big_shr");
   //falhas += teste_big_sar("big_sar");

   
   printf("Total de falhas %d de 8\n", falhas);
   return 0;
}

