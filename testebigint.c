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

int test_big_val (char*msg) {
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

   //numero positivo grande

   BigInt gab4 = {0x00, 0x00, 0x01, 0x00, 0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

   big_val(res, 65536);

    if (test_igual(res, gab4, msg, 4)){
      falhas += 1;
   }

   //numero negativo grande

   BigInt gab5 = {0x00,0x00,0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

   big_val(res, -65536);

    if (test_igual(res, gab5, msg, 5)){
      falhas += 1;
   }

   return (falhas != 0);
}

int test_big_comp2(char*msg) {

   int falhas = 0;

   //numero positivo

   BigInt res,res1;


   big_val(res, 5);
   big_val(res1, -5);
   
   big_comp2(res, res);

   if (test_igual(res, res1, msg, 1)){
      falhas += 1;
   }

   //numero negativo

   BigInt res2,res3;

   big_val(res2,-7);

   big_val(res3,7);

   big_comp2(res2, res2);

   if (test_igual(res2, res3, msg, 2)){
      falhas += 1;
   }


   //zero

   BigInt res4;

   big_val(res4,0);

   big_comp2(res4, res4);

   if (test_igual(res4, res4, msg, 3)){
      falhas += 1;
   }


   //numero muito grande

   BigInt res5,res6;

   big_val(res5,4294967296);

   big_val(res6,-4294967296);

   big_comp2(res5, res5);

   if (test_igual(res5, res6, msg, 4)){
      falhas += 1;
   }

   return (falhas != 0);
}

int test_big_sum(char*msg) {

   int falhas = 0;

   BigInt a,b,c,d,pos,grande;

   //numero positivo, negativo, zero e grande (overflow)

   big_val(a, 10);

   big_val(b,-8);

   big_val(c,0);

   big_val(d,4294967296);

   //resultados esperados

   //a+b = 2

   big_val(pos,2);

   // d+d = 8589934592

   big_val(grande,8589934592);

   BigInt res,res1,res2;

   big_sum(res,a,b);

   big_sum(res1,a,c);

   big_sum(res2,d,d);

   if (test_igual(res, pos, msg, 1)){
      falhas += 1;
   }

   if (test_igual(res1, a, msg, 2)){
      falhas += 1;
   }

   if (test_igual(res2, grande, msg, 3)){
      falhas += 1;
   }

   return (falhas != 0);

}

int test_big_sub(char*msg) {
   int falhas = 0;

   BigInt a,b,c,d,e,pos,grande;

   //numero positivo, negativo, zero e grande (overflow)

   big_val(a, 6);

   big_val(b,-3);

   big_val(c,0);

   big_val(d,4294967296);

   big_val(e,4294967587);

   //resultados esperados

   //a-b = 9

   big_val(pos,9);

   //d-e = −291

   big_val(grande,-291);

   BigInt res,res1,res2;

   big_sub(res,a,b);

   big_sub(res1,a,c);

   big_sub(res2,d,e);

   if (test_igual(res, pos, msg, 1)){
      falhas += 1;
   }

   if (test_igual(res1, a, msg, 2)){
      falhas += 1;
   }

   if (test_igual(res2, grande, msg, 3)){
      falhas += 1;
   }

   return (falhas != 0);

}

int teste_big_mul(char*msg){
   int falhas = 0;

   //numero positivo e negativo pequeno

   BigInt a,b,c,d,e,f;

   big_val(a, 5);

   big_val(b, -3);

   big_val(c, 0);

   big_val(d, 4294967296);

   big_val(e, 1500000000);

   big_val(f, -128);

   //resultados esperados

   //a*b = -15

   BigInt pos,grande;

   big_val(pos, -15);

  //d*e = 6442450944000000000

   big_val(grande, 6442450944000000000);

   //d*f = −549755813888

   BigInt gab;

   big_val(gab, -549755813888);

   BigInt res,res1,res2,res3;

   big_mul(res,a,b);

   big_mul(res1,a,c);

   big_mul(res2,d,e);

   big_mul(res3,d,f);

   if (test_igual(res, pos, msg, 1)){
      falhas += 1;
   }

   if (test_igual(res1, c, msg, 2)){
      falhas += 1;
   }

   if (test_igual(res2, grande, msg, 3)){
      falhas += 1;
   }

   if (test_igual(res3, gab, msg, 4)){
      falhas += 1;
   }


   return(falhas != 0);

}

int teste_big_shl(char*msg){
   int falhas = 0;

   //testar shift de 0, shift de 127, shift multiplo de 8 e shift nao multiplo de 8

   BigInt a;

   big_val(a, 256);

   BigInt res,res1,res2,res3;

   big_shl(res,a,0);

   big_shl(res1,a,127);

   big_shl(res2,a,8);

   big_shl(res3,a,7);

   BigInt pos,pos1,pos2,pos3;

   big_val(pos, 256);

   big_val(pos1, 0);

   big_val(pos2, 65536);

   big_val(pos3, 32768);

   if (test_igual(res, pos, msg, 1)){
      falhas += 1;
   }

   if (test_igual(res1, pos1, msg, 2)){
      falhas += 1;
   }

   if (test_igual(res2, pos2, msg, 3)){
      falhas += 1;
   }

   if (test_igual(res3, pos3, msg, 4)){
      falhas += 1;
   }

   return(falhas != 0);

}

int teste_big_shr(char*msg){
   int falhas = 0;

   //testar shift de 0, shift de 127, shift multiplo de 8 e shift nao multiplo de 8

   BigInt a;

   big_val(a, 256);

   BigInt res,res1,res2,res3;

   big_shr(res,a,0);

   big_shr(res1,a,127);

   big_shr(res2,a,8);

   big_shr(res3,a,7);

   BigInt pos,pos1,pos2,pos3;

   big_val(pos, 256);

   big_val(pos1, 0);

   big_val(pos2, 1);

   big_val(pos3, 2);

   if (test_igual(res, pos, msg, 1)){
      falhas += 1;
   }

   if (test_igual(res1, pos1, msg, 2)){
      falhas += 1;
   }

   if (test_igual(res2, pos2, msg, 3)){
      falhas += 1;
   }

   if (test_igual(res3, pos3, msg, 4)){
      falhas += 1;
   }

   return (falhas!=0);

}

int teste_big_sar(char*msg){

   int falhas = 0;

   //testar shift de 0, shift de 127, shift multiplo de 8 e shift nao multiplo de 8

   BigInt a;

   big_val(a, -256);

   BigInt res,res1,res2,res3;

   big_sar(res,a,0);

   big_sar(res1,a,127);

   for(int i =0;i<16;i++){
      printf("res1:%02x\n",res1[i]);
   }

   big_sar(res2,a,8);

   big_sar(res3,a,7);

   for(int i =0;i<16;i++){
      printf("res3:%02x\n",res3[i]);
   }

   BigInt pos,pos1,pos2,pos3;

   big_val(pos, -256);

   big_val(pos1, -1);

   big_val(pos2, -1);

   big_val(pos3, -2);

   if (test_igual(res, pos, msg, 1)){
      falhas += 1;
   }

   if (test_igual(res1, pos1, msg, 2)){
      falhas += 1;
   }

   if (test_igual(res2, pos2, msg, 3)){
      falhas += 1;
   }

   if (test_igual(res3, pos3, msg, 4)){
      falhas += 1;
   }

   return (falhas!=0);
}

int main() {
   int falhas = 0;
   
   falhas += test_big_val("big_val");
   falhas += test_big_comp2("big_comp2");
   falhas += test_big_sum("big_sum");
   falhas += test_big_sub("big_sub");
   falhas += teste_big_mul("big_mul");
   falhas += teste_big_shl("big_shl");
   falhas += teste_big_shr("big_shr");
   falhas += teste_big_sar("big_sar");

   
   printf("Total de falhas %d de 31\n", falhas);
   return 0;
}

