/* Lívia Lutz dos Santos - 2211055 - 3WB */

/* Atribuicao */

/* res = val (extensao com sinal) */

void big_val(BigInt res, long val) {
  
  for (int i = 0; i < 8 ; i++) {
    res[i] = val | 0x00; 
    val = (val >> 8);   
  }
  
  if((res[7] & 0x80) == 0x80) { 
  
     for(int i = 8; i < (NUM_BITS/8) ; i++){
        res[i] = 0xFF;
     }
  }
  
  else{
   
     for(int i = 8; i < (NUM_BITS/8) ; i++){
        res[i] = 0x00;
     }
      
  }

}

/* Operacoes aritmeticas */

/* res = -a */

void big_comp2(BigInt res, BigInt a) {

  for (int i = 0; i < (NUM_BITS / 8) ; i++) {
    res[i] = a[i];
  }

  for (int i = 0; i < (NUM_BITS / 8); i++) {
    res[i] = ~res[i];
  }

  for (int i = 0; i < (NUM_BITS / 8) ; i++) {

    if (res[i] == 0xFF) {
    	res[i] = 0x00;
    }

    else {
      res[i]++;
      break;
    }

  }
  
}

/* res = a + b */

void big_sum(BigInt res, BigInt a, BigInt b) {

  //Variável para guardar o valor do bit mais significativo de cada byte e para controlar o overflow da soma

  unsigned char overflow = 0x00;

  //Variável para guardar o resultado da soma dos bytes (um short tem 2 bytes, então usamos um short para guardar o resultado da soma de 2 bytes)
  
  unsigned short soma;

  // Percorremos todo o array para fazer a soma dos bytes

  for (int i = 0; i < (NUM_BITS/8) ; i++) {

    // Faz a soma dos bytes com o overflow e guarda no short soma
    soma = a[i] + b[i] + overflow;

    // Pega o byte menos significativo do resultado da soma e guarda no array de resposta
    res[i] = soma & 0xFF;

    // Guarda o valor do bit mais significativo da soma para controlar o overflow que sera passado para o proximo byte
    overflow = soma >> 8;
  }
}

/* res = a - b */

void big_sub(BigInt res, BigInt a, BigInt b) {
  
    BigInt b2;
  
    big_comp2(b2, b);
 
    big_sum(res, a, b2);
}
  
  
/* res = a * b */

void big_mul(BigInt res, BigInt a, BigInt b) {

  //Variável int para guardar o resultado da multiplicação dos 2 bytes

  unsigned int mult;

  //inicializa o array de resposta com 0

  for(int i = 0; i < (NUM_BITS/8) ; i++){
    res[i] = 0x00;
  }

    //Percorre todo o array para fazer a multiplicação dos bytes

  for(int i = 0; i < (NUM_BITS/8) ; i++){
        
    for(int j = 0; j < (NUM_BITS/8) ; j++){
          
      if((i+j) < (NUM_BITS/8)){
            
        //multiplica os bytes e guarda em uma variavel short (2 bytes, 1 byte para cada byte multiplicado)
            
        mult =  a[i] * b[j];
            
        //guarda o byte menos significativo do resultado da multiplicação no array de resposta
            
        res[i+j] += mult & 0xFF;
            
        //guarda o byte mais significativo do resultado da multiplicação no array de resposta
            
        res[i+j+1] += mult >> 8;
      }
    
    }
  }

    //faz o tratamento do overflow

  for(int i = 0; i < (NUM_BITS/8) -1 ; i++){
    //guarda o byte menos significativo do resultado da multiplicação no array de resposta
        
    res[i] &= 0xFF;

    //guarda o byte mais significativo do resultado da multiplicação no array de resposta

    res[i+1] += res[i] >> 8;
  }

}
  
/* Operacoes de deslocamento */

/* res = a << n */

void big_shl(BigInt res, BigInt a, int n) {
   
   int j = 0;

   unsigned char shiftRight,anterior=0x00;

   for (int i = 0; i < (NUM_BITS/8); i++) {
      res[i] = a[i];
    }
   
   for(; j < (n/8); j++){
   
    for(int k = (NUM_BITS/8) - 1; k >= 0; k--){
   	
   		if (k == 0){
   			res[k] = 0x00;
   		}
   		
   		else{
   			res[k] = res[k-1];
   		}
   	
   	}
   	
  }
   
   
  if ((n % 8) != 0){
    
    for(;j< (NUM_BITS/8);j++){
    	
    	if(j == 0){
    		shiftRight=0x00;
    	}
    	
    	else{
    		shiftRight= res[j] >> (8-(n%8));
    	}
    	
    	res[j] <<= (n%8);
    		
    	res[j] |= anterior;
    	
    	anterior=shiftRight;
    	
    }
    
  }
  
}
  
/* res = a >> n (logico) */

void big_shr(BigInt res, BigInt a, int n){

  int j = 0;

  unsigned char shiftLeft, posterior = 0x00;

  for (int i = 0; i < (NUM_BITS/8); i++) {
    res[i] = a[i];
  }

  for(; j < (n/8); j++){
   
    for(int k = 0; k < (NUM_BITS/8); k++){
   	
   		if (k == (NUM_BITS/8)-1){
   			res[k] = 0x00;
   		}
   		
   		else{
   			res[k] = res[k+1];
   		}
   	
   	}
   	
  }
   
  if ((n % 8) != 0){

    j = (NUM_BITS/8) - j;

    for(;j >= 0;j--){

      if(j == (NUM_BITS/8)-1){
        shiftLeft = 0x00;
      }

      else{
        shiftLeft=res[j] << (8-(n%8));
      }

      res[j] >>= (n%8);

      res[j] |= posterior;

      posterior=shiftLeft; 
    }
  

  }
    
}

/* res = a >> n (aritmetico) */

void big_sar(BigInt res, BigInt a, int n){

  int j = 0;

  unsigned char shiftLeft, posterior = 0x00,mostSig;

  mostSig = a[(NUM_BITS/8)-1];

  for (int i = 0; i < (NUM_BITS/8); i++) {
    res[i] = a[i];
  }

  for(; j < (n/8); j++){
   
    for(int k = 0; k < (NUM_BITS/8); k++){
   	
   		if (k == (NUM_BITS/8)-1){
   			if((res[k] & 0x80) == 0x80){
          res[k] = mostSig;
        }
        else{
          res[k] = 0x00;
        }
   		}
   		else{
   			res[k] = res[k+1];
   		}
   	
   	}
   	
  }
   
  if ((n % 8) != 0){

    j = (NUM_BITS/8) - j;

    for(;j >= 0;j--){

      if(j == (NUM_BITS/8)-1){
        shiftLeft = mostSig;
      }

      else{
        shiftLeft=res[j] << (8-(n%8));
      }

      res[j] >>= (n%8);

      res[j] |= posterior;

      posterior=shiftLeft; 
    }
  

  }


}

//função que funciona da big_sar

/*void big_sar(BigInt res, BigInt a, int n) {
  int i = 0;
  for (; i < (NUM_BITS/8) ; i++) {
    res[i] = a[i];
  }
  for (i = 0; i < n ; i++) {
    for (int j = 0; j < (NUM_BITS/8) - 1 ; j++) {
      res[j] >>= 1;
      res[j] |= (res[j+1] & 0x01) << 7;
    }
    res[(NUM_BITS/8) - 1] >>= 1;
    res[(NUM_BITS/8) - 1] |= (res[(NUM_BITS/8) - 1] & 0x40) << 1;
  }
}*/



