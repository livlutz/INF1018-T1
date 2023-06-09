/* Lívia Lutz dos Santos - 2211055 - 3WB */

#include "bigint.h"
#include <stdio.h>

#define NUM_BITS 128
typedef unsigned char BigInt[NUM_BITS / 8];

/* Atribuicao */

/* res = val (extensao com sinal) */

void big_val(BigInt res, long val) {

  /* Váriavel de contagem */
  
	int i = 0;
  
  /* Percorre o long */ 

  for (; i < sizeof(val) ; i++) {

    /* Coloca os bytes menos significativos nas primeiras posições do array */

    res[i] = val | 0x00; 

    /* Right shift (com sinal) para passar para o próximo byte do long */

    val >>= 8;      
  }
  
  /* Se o byte mais significativo do long passado para res for 1, preenchemos as 8 primeiras posições do array com esse byte */
  
  if((res[7] & 0x80) == 0x80) { 

     for(; i < (NUM_BITS/8) ; i++){

        res[i] = 0xFF;

     }

  }
     
  /* Caso contrário preenchemos com 0 */
     
  else{

     for(; i < (NUM_BITS/8) ; i++){

        res[i] = 0x00;

     }
      
  }

}

/* Operacoes aritmeticas */

/* res = -a */

void big_comp2(BigInt res, BigInt a) {

  /* Passamos os bytes para o array de resposta */

  for (int i = 0; i < (NUM_BITS / 8) ; i++) {

    res[i] = a[i];

  }

  /* Inverte todos os bits de cada byte do array de resposta */

  for (int i = 0; i < (NUM_BITS / 8); i++) {

    res[i] = ~res[i];

  }

  /* Comecando do byte menos significativo do array (BigInt[0]) adicionamos 1 */

  for (int i = 0; i < (NUM_BITS / 8) ; i++) {

    /* Se o byte for 0xFF sua organização em binário é 1111 1111, se somarmos 1,
     * sabemos que 1 + 1 = 0,logo se fizermos isso neste número o resultado será
     * 0000 0000, que equivale a 0x00 em hexadecimal */

    if (res[i] == 0xFF) {

    	res[i] = 0x00;

    }

    /* Caso contrário, guardamos no byte o resultado da sua soma com 1 e paramos o loop */

    else {

      res[i]++;

      break;

    }

  }
}

/* res = a + b */

void big_sum(BigInt res, BigInt a, BigInt b) {

  /*Variável para guardar o valor do bit mais significativo de cada byte e para controlar o overflow da soma*/

  unsigned char overflow = 0;

  /*Variável para guardar o resultado da soma dos bytes (um short tem 2 bytes, então usamos um short para guardar o resultado da soma de 2 bytes)*/

  unsigned short soma;

  /* Percorremos todo o array para fazer a soma dos bytes */

  for (int i = 0; i < (NUM_BITS/8) ; i++) {

    /* Faz a soma dos bytes com o overflow e guarda no short soma */

    soma = a[i] + b[i] + overflow;

    /* Pega o byte menos significativo do resultado da soma e guarda no array de resposta das menores até as maiores posições */

    res[i] = soma & 0xFF;

    /* Guarda o valor do bit mais significativo da soma para controlar o overflow que sera passado para o próximo byte */

    overflow = soma >> 8;
  }

}

/* res = a - b */

void big_sub(BigInt res, BigInt a, BigInt b) {

  /* A subtração pode ser pensada como a + (-b) para isso, fazemos a soma de a com o complemento a 2 de b */
  
  /* Usei um array BigInt diferente para fazer o complemento a 2 para não alterar o array original passado como parâmetro */
  
  BigInt b2;
    
  /*Guarda o resultado do complemento a 2 de b em um novo array BigInt b2 usando a função big_comp2*/
  
  big_comp2(b2, b);
    
  /* Soma esse novo array a a e guarda o resultado no array de resposta usando a função big_sum */
    
  big_sum(res, a, b2);
   
}

/* res = a * b */

void big_mul(BigInt res, BigInt a, BigInt b) {

  /* Variável int para guardar o resultado da multiplicação dos 2 bytes */

  unsigned int mult;

  /* Inicializa o array de resposta com 0 para que possamos alocar os bytes posteriormente */

  for(int i = 0; i < (NUM_BITS/8) ; i++){

    res[i] = 0x00;

  }

  /*Percorre todo o array para fazer a multiplicação dos bytes */

  for(int i = 0; i < (NUM_BITS/8) ; i++){
        
    for(int j = 0; j < (NUM_BITS/8) ; j++){
          
      if((i+j) < (NUM_BITS/8)){
            
        /* Multiplica os bytes e guarda em uma variavel short (2 bytes, 1 byte para cada byte multiplicado) */
            
        mult = a[i] * b[j];
            
        /* Guarda o byte menos significativo do resultado da multiplicação no array de resposta */
            
        res[i+j] += mult & 0xFF;
            
        /* Guarda o byte mais significativo do resultado da multiplicação no array de resposta */
            
        res[i+j+1] += mult >> 8;
      }
    
    }
  }

    /* Faz o tratamento do overflow */

  for(int i = 0; i < (NUM_BITS/8) -1 ; i++){

    /* Guarda o byte menos significativo do resultado da multiplicação no array de resposta */
        
    res[i] &= 0xFF;

    /* Soma na proxima posição do array de resposta o bit mais significativo do byte anterior na posição de bit menos significativo
       para permitir futuras somas, já que os outros bits estarão todos em 0 */

    res[i+1] += res[i] >> 8;
  }

}

/* Operacoes de deslocamento */

/* res = a << n */

void big_shl(BigInt res, BigInt a, int n) {

  /* Variável de contagem de posição no array */
   
   int j = 0;

  /* Variáveis para guardar o byte a ser passado nas operações */

   unsigned char shiftRight,anterior=0x00;

  /* Passando os bytes recebidos para o array de resposta */

   for (int i = 0; i < (NUM_BITS/8); i++) {
      res[i] = a[i];
    }

  /* Para o número se shifts de 8 completos, preenchemos os bytes a direita com 0 do byte mais significativo para o byte menos significativo */

   
   for(; j < (n/8); j++){
   
    for(int k = (NUM_BITS/8) - 1; k >= 0; k--){

      /* Caso seja o primeiro byte do array ,preenchemos com 0 */
   	
   		if (k == 0){
   			res[k] = 0x00;
   		}

      /* Passamos os bytes para a esquerda */
   		
   		else{
   			res[k] = res[k-1];
   		}
   	
   	}
   	
  }

  /* Caso a quantidade de shifts não seja um múltiplo de 8,continuamos o deslocamento */
   
   
  if ((n % 8) != 0){

    /* Da última posição que era um múltiplo de 8, continuamos o shift */
    
    for(;j < (NUM_BITS/8); j++){

      /* Guardamos o bit mais significativo do byte anterior com o shift de quanto "Falta" para chegar a 8 */
    	
    	shiftRight= res[j] >> (8-(n % 8));

      /* Guardamos o byte menos significativo do byte atual com o shift de quanto "Sobra" para chegar a 8 */
    	
    	res[j] <<= (n%8);

      /* Fazemos uma operação  de ou aritmético entre o byte atual e o byte anterior para juntar os bits que foram separados */
    		
    	res[j] |= anterior;

      /* Definimos o que passar para o próximo byte, guardando o valor de quanto "Falta" para chegar a 8 na variável anterior */
    	
    	anterior = shiftRight;
    	
    }
    
  }
  
}

/* res = a >> n (logico) */

void big_shr(BigInt res, BigInt a, int n){

  /* Variável de contagem de posição no array */

  int j = 0;

  /* Variáveis para guardar o byte a ser passado nas operações */

  unsigned char shiftLeft, posterior = 0x00;

  /* Passando os bytes recebidos para o array de resposta */

  for (int i = 0; i < (NUM_BITS/8); i++){
    res[i] = a[i]; 
  }

  /* Para o número se shifts de 8 completos, passamos os bytes para a esquerda do byte menos para o mais siginificativo do array */

  for (int i = 0; i < (NUM_BITS/8); i++){

    for (; j < (n / 8); j++) {

        for (int k = 0; k  < (NUM_BITS/8); k++) {

          res[k] = res[k + 1];

        }
      }
  }

  /* Caso a quantidade de shifts não seja um múltiplo de 8, continuamos o deslocamento */
    
  if ((n % 8) != 0){

    /* Do byte mais significativo para o menos significativo */

    for (j = (NUM_BITS/8) - 1; j >= 0; j--){

      /* Guardamos o bit menos significativo do byte posterior com o shift de quanto "Falta" para chegar a 8 */

      shiftLeft = res[j] << (8 - (n % 8));

      /* Guardamos o byte mais significativo do byte atual com o shift de quanto "Sobra" para chegar a 8 */

      res[j] >>= (n%8);

      /* Fazemos uma operação de ou aritmético entre o byte atual e o byte posterior para juntar os bits que foram separados */
      
      res[j] |= posterior;

      /* Definimos o que passar para o byte anterior, guardando o valor de quanto "Falta" para chegar a 8 na variável posterior */

      posterior = shiftLeft;

    }
  }

}
    
/* res = a >> n (aritmetico) */

void big_sar(BigInt res, BigInt a, int n){

  /* Variável de contagem de posição no array */

  int i = 0;

  /* Passamos os bytes recebidos como parâmetro para o array de resposta */

  for (; i < (NUM_BITS/8) ; i++) {
    res[i] = a[i];
  }

  /* Para o número de shifts */

  for (i = 0; i < n ; i++) {

    /* Para cada byte do menos significativo para o mais significativo do array */

    for (int j = 0; j < (NUM_BITS/8) - 1 ; j++) {

      /* No byte atual, fazemos um shift a direita de 1 bit para adicionar o bit mais significativo do próximo byte */ 

      res[j] >>= 1;

      /* Guardamos o bit menos significativo do byte seguinte com o shift de 7 e
       fazemos uma operação de ou aritmético com o byte atual para juntar os bits que foram separados */

      res[j] |= (res[j+1] & 0x01) << 7;
    }

    /* Caso seja o último byte, fazemos um shift a direita de 1 bit para adicionar o bit mais significativo dele mesmo*/ 
    
    res[(NUM_BITS/8) - 1] >>= 1;

    res[(NUM_BITS/8) - 1] |= (res[(NUM_BITS/8) - 1] & 0x40) << 1;
  }
  
}
