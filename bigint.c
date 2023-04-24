/* Lívia Lutz dos Santos - 2211055 - 3WB */

/* Atribuicao */

/* res = val (extensao com sinal) */

void big_val(BigInt res, long val) {

  /* Para cada 8 bytes do long, preenchemos as 8 últimas posições do array BigInt */
  
  for (int i = 0; i < 8 ; i++) {
    res[i] = val | 0x00; /*Pega o byte menos significativo*/
    val = (val >> 8);      /*Passa para o proximo byte (8 bits)*/
  }
  
  /* Para preencher as 8 posições restantes do array, existem 2 condições: */
  
  /* Se o byte mais significativo é 1, o número é negativo, então os outros bytes tem q ser FF*/
  
  if((res[7] & 0x80) == 0x80) { 
  
     for(int i = 8; i < (NUM_BITS/8) ; i++){
        res[i] = 0xFF;
     }
  }
     
  /* Caso contrário, os outros bytes tem que ser 0 */
     
  else{
   
     for(int i = 8; i < (NUM_BITS/8) ; i++){
        res[i] = 0x00;
     }
      
  }

}

/*Como o array BigInt é unsigned, fazemos as operações sem sinal*/

/* Operacoes aritmeticas */

/* res = -a */

void big_comp2(BigInt res, BigInt a) {


  /* Passa cada byte do array que queremos calcular o complemento a 2 para o
   * array de resposta */

  for (int i = 0; i < (NUM_BITS / 8) ; i++) {
    res[i] = a[i];
  }

  // Inverte todos os bits de cada byte do array

  for (int i = 0; i < (NUM_BITS / 8); i++) {
    res[i] = ~res[i];
  }

  /* Começando do byte menos significativo na primeira posição do array,
   * adicionamos 1 ao byte para completar o cálculo de seu complemento a 2 */

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


   /* Variáveis para guardar o valor do bit mais significativo de cada byte 
      e para controlar o overflow da soma */
   
   int mostSiga,mostSigb,mostSigRes,overFlow;
   
   /* Percorremos todo o array para fazer a soma dos bytes */

  for (int i = 0; i < NUM_BITS / 8; i++) {
  
   /* Caso tenha overflow, devemos somar seu valor na soma */
  
  /* Caso haja espaço no byte de a para somar o overflow, somamos */
  
    if (overFlow == 1 && a[i] != 0xFF) {
    
      a[i]++; 
      
      /* Já que o overflow foi somado, zeramos seu valor */
      
      overFlow = 0;
    
    }
    
  /* Caso contrário, somamos no byte de b */
    
    else if((overFlow == 1) && (b[i] != 0xFF)) {
    
    	b[i]++;
    	
    	overFlow = 0;
    
    }
    
  /* Se não houver espaço em nenhum dos 2 bytes, temos que calcular a soma e atualizar o overflow */
  
    /* Se o bit mais siginificativo de a e b for 1, 
    guardamos esse valor como 1 nas variáveis de controle declarada acima (mostSiga -> guarda o valor do bit mais significativo de a e mostSigb -> guarda o valor do bit mais significativo de b*/
  
    if((a[i] & 0x80) == 0x80) {
    	mostSiga = 1;
    }
     
    if ((b[i] & 0x80) == 0x80) {
    	mostSigb = 1;
    }
    
    // Senão guardamos 0 como seu valor nas variáveis
    
    else{
    	mostSiga = 0;
    	mostSigb = 0;	
    } 
    
    //Soma os bytes e guarda no array de resposta
  
    res[i] = a[i] + b[i];
    
    /* Guarda o bit mais significativo do byte no array BigInt*/
    
    if ((res[i] & 0x80) == 0x80) {
    /* Caso o valor do bit mais significativo de res seja 1, guardamos em mostSigRes -> variável de controle que guarda o valor do bit mais significativo de res*/
       mostSigRes = 1;
    }
    
    //Senão, guardamos seu valor como 0
    
    else{
      mostSigRes = 0;
    }
    
    /* Se os bits mais significativos de a e b forem 1, 
    a soma dá 0 e teremos overflow de 1 bit, então guardamos 1 na variavel de overflow */
    
    if ((mostSiga == 1) && (mostSigb == 1)) {
    	
      overFlow = 1;
      
    }
    
   /* Se os bits mais significativos de a ou b forem 1,mas o bit mais significativo de res = 0, então guardamos 1 na variavel de overflow e o bit mais significativo de res será 1 */
    
    else if ((mostSiga == 1 || mostSigb == 1) && (mostSigRes == 0)) { 
    
      overFlow = 1; 
      
      res[i] |= 0x80;
     
    }
    
   }
}

/* res = a - b */

void big_sub(BigInt res, BigInt a, BigInt b) {


  /* A subtração pode ser pensada como a + (-b) para isso, fazemos a soma de a com o complemento a 2 de b */

  
   /* Usei um array BigInt diferente para fazer o complemento a 2 para nao alterar o array original passado como parametro */
  
    BigInt b2;
    
    /*Guarda o resultado do complemento a 2 de b em um novo array BigInt b2 usando a função big_comp2*/
  
    big_comp2(b2, b);
    
    /* soma esse novo array a a e guarda o resultado no array de resposta usando a função big_sum */
    
    big_sum(res, a, b2);
   
}
