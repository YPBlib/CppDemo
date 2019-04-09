#include <stdio.h>
#include <stdlib.h>
#include <openssl/bn.h>

void printBN(char* msg, BIGNUM* a)
{
	char* number_str=BN_bn2hex(a);
	printf("%s %s\n",msg,number_str);
	OPENSSL_free(number_str);
}

int main()
{
	BN_CTX *ctx=BN_CTX_new();
	
	BIGNUM *p=BN_new();
	BIGNUM *q=BN_new();
	BIGNUM *e=BN_new();
	
	BIGNUM *one=BN_new();
	BIGNUM *e_rev=BN_new();
	BIGNUM *p_minus_one=BN_new();
	BIGNUM *q_minus_one=BN_new();
	BIGNUM *temp=BN_new();
	
	BN_hex2bn(&p,"F7E75FDC469067FFDC4E847C51F452DF");
	BN_hex2bn(&q,"E85CED54AF57E53E092113E62F436F4F");
	BN_hex2bn(&e,"0D88C3");
	BN_dec2bn(&one,"1");
	
	BN_sub(p_minus_one,p,one);
	BN_sub(q_minus_one,q,one);
	BN_mul(temp,p_minus_one,q_minus_one,ctx);
	
	BN_mod_inverse(e_rev,e,temp,ctx);
	
	// use (e, n) as the public key.
	// then (e_rev,n) is private key
	printf("the private key is {e_rev,n},n is given already, and e_rev is\n");
	printBN("e_rev = ",e_rev);
	
	return 0;
}
