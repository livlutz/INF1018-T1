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
   
   int mostSiga, mostSigb, mostSigRes, overFlow, i = 0;

  for (; i < (NUM_BITS / 8); i++) {
  
    if ((overFlow == 1) && (a[i] != 0xFF)) {
      
      a[i]++; 
      
      overFlow = 0;
    
    }
    
    else if((overFlow == 1) && (b[i] != 0xFF)) {
    
    	b[i]++;
    	
    	overFlow = 0;
    
    }
    
  
    if((a[i] & 0x80) == 0x80) {
    	mostSiga = 1;
    }
    
    else{
      mostSiga = 0;
     
    if ((b[i] & 0x80) == 0x80) {
    	mostSigb = 1;
    }
    
    else{
    	mostSigb = 0;	
    } 
  
    res[i] = a[i] + b[i];
    
    if ((res[i] & 0x80) == 0x80) {
       mostSigRes = 1;
    }
    
    else{
      mostSigRes = 0;
    }
    
    if ((mostSiga == 1) && (mostSigb == 1)) {
      overFlow = 1;
    }
    
    else if ((mostSiga == 1 || mostSigb == 1) && (mostSigRes == 0)) { 
    
      overFlow = 1; 
      
      res[i] &= 0x80;
     
    }
    
   }
    
}

/* res = a - b */

void big_sub(BigInt res, BigInt a, BigInt b) {
  
    BigInt b2;
  
    big_comp2(b2, b);
 
    big_sum(res, a, b2);
}
  
  
/* res = a * b */

void big_mul(BigInt res, BigInt a, BigInt b);
  
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

  unsigned char shiftLeft, posterior,mostSig;

  for (int i = 0; i < (NUM_BITS/8); i++) {
    res[i] = a[i];
  }

  mostSig=res[(NUM_BITS/8)-1];

  if((mostSig & 0x80) == 0x80){
    posterior = 0xFF << (n % 8);
  }

  else{
    posterior = 0x00;
  }

  for(; j < (n/8); j++){
   
    for(int k = 0; k < (NUM_BITS/8); k++){
   	
   		if (k == (NUM_BITS/8)-1){
   			if((res[k] & 0x80) == 0x80){
          res[k] = 0xFF;
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

      shiftLeft=res[j] << (8-(n%8));

      res[j] >>= (n%8);

      res[j] |= posterior;

      posterior=shiftLeft; 
    }
  

  }


}
