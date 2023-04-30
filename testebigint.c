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

   //numero positivo
   BigInt gab1 = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
   BigInt res;
   big_val (res, 1);
   
   if (test_igual(res, gab1, msg, 1)){
      falhas += 1;
   } 

   //numero negativo


   BigInt gab2 = {0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
   big_val (res, -2);
   
   if (test_igual(res, gab2, msg, 2)){
      falhas += 1;
   }

   //zero

   BigInt gab3 = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

   big_val(res,0);

    if (test_igual(res, gab3, msg, 3)){
      falhas += 1;
   }

   //numero grande

   BigInt gab4 = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF ,0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
   big_val(res, 0xFFFFFFFFFFFFFFFF);

   if (test_igual(res, gab4, msg, 4)){
      falhas += 1;
   }


   return (falhas != 0);
}

int test_big_comp2(char *msg) {
   int falhas = 0;
   BigInt res;

   //numero positivo

   BigInt gab1 = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
   BigInt a = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

   big_comp2(res,a);

   if (test_igual(res, gab1, msg, 1)){
      falhas += 1;
   }

   //numero negativo

   BigInt b = {0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
   BigInt gab2 = {0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
   
   big_comp2(res,b);

   if (test_igual(res, gab2, msg, 2)){
      falhas += 1;
   }

   //zero

   BigInt gab3 = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
   BigInt c = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

   big_comp2(res,c);

   if (test_igual(res, gab3, msg, 3)){
      falhas += 1;
   }

   //numero grande

   BigInt gab4 = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 ,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF ,0xFF, 0xFF};
   BigInt d = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF ,0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00 ,0x00, 0x00};

   big_comp2(res,d);

   if (test_igual(res, gab4, msg, 4)){
      falhas += 1;
   }

   return (falhas != 0);
   
}

int test_big_sum(char *msg) {
  int falhas = 0;

   BigInt res;

   BigInt a = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
   BigInt b = {0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
   BigInt c = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

   BigInt gab1 = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

   big_sum(res, a, b);

   if (test_igual(res, gab1, msg, 1)){
      falhas += 1;
   }
   
   BigInt gab2 = {0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

   big_sum(res,b,c);

   if (test_igual(res, gab2, msg, 2)){
      falhas += 1;
   }

   //numero grande com overflow, nao funciona

   BigInt gab3 = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00 ,0x00, 0x00, 0x00, 0x00, 0x00, 0x00 ,0x00, 0x00 ,0x00, 0x00};
   BigInt d = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF ,0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF ,0xFF, 0xFF ,0xFF, 0xFF};

   big_sum(res,d,a);

   if (test_igual(res, gab3, msg, 3)){
      falhas += 1;
   }

   return (falhas != 0);

}

int test_big_sub(char*msg) {
  int falhas = 0;

   BigInt a = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
   BigInt b = {0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
   BigInt c = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
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

   big_sub(res,b,c);

   if (test_igual(res, b, msg, 3)){
      falhas += 1;
   }

   //numero grande, nao funciona para overflow
   BigInt d = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF ,0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF ,0xFF, 0xFF};

   BigInt gab3 = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00 ,0x00, 0x00, 0x00, 0x00, 0x00, 0x00 ,0x00, 0x00 ,0x00, 0x00};

   big_sub(res,d,b);

   if (test_igual(res, gab3, msg, 4)){
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

   //numero positivo

   BigInt a = { 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
   BigInt gab1 = { 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; 
   BigInt gab12 = { 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

   //numero negativo

   BigInt b = { 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

   BigInt gab2 = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
   BigInt gab22 = { 0x00, 0x00, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

   //zero

   BigInt c = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

   BigInt res;

   big_shl(res,a,16);

   if (test_igual(res, gab1, msg, 1)){
      falhas += 1;
   }

   big_shl(res,a,5);

   if (test_igual(res, gab12, msg, 2)){
      falhas += 1;
   }

   big_shl(res,b,64);

   if (test_igual(res, gab2, msg, 3)){
      falhas += 1;
   }

   big_shl(res,b,18);

   if (test_igual(res, gab22, msg, 4)){
      falhas += 1;
   }

   big_shl(res,c,87);

   if (test_igual(res, c, msg, 5)){
      falhas += 1;
   }
   
   //falta numero grande

   return(falhas != 0);

}

int teste_big_shr(char*msg){
   int falhas = 0;

   //numeros positivo, negativo e zero

   BigInt a = { 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
   BigInt b = { 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
   BigInt c = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

   BigInt res;

   BigInt gab1 = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
   BigInt gab2 = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00};
   BigInt gab21 = {0xFF ,0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x00};

   big_shr(res,a,72);

   if (test_igual(res, gab1, msg, 1)){
      falhas += 1;
   }

   big_shr(res,a,7);

   if (test_igual(res, gab1, msg, 2)){
      falhas += 1;
   }

   big_shr(res,b,32);

   if (test_igual(res, gab2, msg, 3)){
      falhas += 1;
   }

   big_shr(res,b,23);

   if (test_igual(res, gab21, msg, 4)){
      falhas += 1;
   }

   big_shr(res,c,67);

   if (test_igual(res, c, msg, 5)){
      falhas += 1;
   }
   
   //falta numero grande

   return (falhas!=0);

}

int teste_big_sar(char*msg){

   int falhas = 0;

   //numeros positivo,negativo e zero

   BigInt a = { 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
   BigInt b = { 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
   BigInt c = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};


   BigInt res;

   BigInt gab1 = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
   BigInt gab2 = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
   BigInt gab21 = {0xFF ,0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x81, 0xFF};

   big_sar(res,a,72);

   if (test_igual(res, gab1, msg, 1)){
      falhas += 1;
   }

   big_sar(res,a,7);

   if (test_igual(res, gab1, msg, 2)){
      falhas += 1;
   }

   big_sar(res,b,32);

   if (test_igual(res, gab2, msg, 3)){
      falhas += 1;
   }

   big_sar(res,b,23);

   if (test_igual(res, gab21, msg, 4)){
      falhas += 1;
   }

   big_sar(res,c,67);

   if (test_igual(res, c, msg, 5)){
      falhas += 1;
   }
   
   //falta numero grande

   return (falhas!=0);
   
   
}


int main() {
   int falhas = 0;
   
   falhas += test_big_val("big_val");
   falhas += test_big_comp2("big_comp2");
   falhas += test_big_sum("big_sum");
   falhas += test_big_sub("big_sub");
   //falhas += teste_big_mul("big_mul");
   falhas += teste_big_shl("big_shl");
   falhas += teste_big_shr("big_shr");
   falhas += teste_big_sar("big_sar");
   
   //por enquanto da 2 falhas pois o overflow ta errado

   
   printf("Total de falhas %d de 30\n", falhas);
   return 0;
}
