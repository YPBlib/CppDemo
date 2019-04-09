#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <openssl/bn.h>
//#include <openssl/md5.h>
//#include <openssl/sha.h>
//#include <openssl/rsa.h>
//#include <openssl/rand.h>

void printBN(char* msg, BIGNUM* a)
{
	char* number_str=BN_bn2hex(a);
	printf("%s %s\n",msg,number_str);
	OPENSSL_free(number_str);
}

int main()
{
	BN_CTX *ctx=BN_CTX_new();
	
	BIGNUM *n=BN_new();
	BIGNUM *e=BN_new();
	BIGNUM *d=BN_new();
	BIGNUM *M=BN_new();
	
	BIGNUM* cipher=BN_new();
	BIGNUM* plaintext=BN_new();

	

	
	BN_hex2bn(&n,"DCBFFE3E51F62E09CE7032E2677A78946A849DC4CDDE3A4D0CB81629242FB1A5");
	BN_hex2bn(&e,"010001");
	BN_hex2bn(&d,"74D806F9F3A62BAE331FFE3F0A68AFE35B3D2E4794148AACBC26AA381CD7D30D");
	BN_hex2bn(&M,"4120746F702073656372657421");
	
	
	BN_mod_exp(cipher, M, e, n, ctx);
	printBN("the cipher is", cipher);
	
	BN_mod_exp(plaintext,cipher,d,n,ctx);
	printBN("the plaintext is", plaintext);
	
	printBN("the original M is", M);
	
	return 0;
}
