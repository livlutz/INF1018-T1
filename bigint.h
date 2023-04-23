#define NUM_BITS 128
typedef unsigned char BigInt[NUM_BITS / 8];

/* Atribuicao */

/* res = val (extensao com sinal) */
void big_val(BigInt res, long val);

/* Operacoes aritmeticas */

/* res = -a */
void big_comp2(BigInt res, BigInt a);

/* res = a + b */
void big_sum(BigInt res, BigInt a, BigInt b);

/* res = a - b */
void big_sub(BigInt res, BigInt a, BigInt b);

/* res = a * b */
void big_mul(BigInt res, BigInt a, BigInt b);

/* Operacoes de deslocamento */

/* res = a << n */
void big_shl(BigInt res, BigInt a, int n);

/* res = a >> n (logico) */
void big_shr(BigInt res, BigInt a, int n);

/* res = a >> n (aritmetico) */
void big_sar(BigInt res, BigInt a, int n);
