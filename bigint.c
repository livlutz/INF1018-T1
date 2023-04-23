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
