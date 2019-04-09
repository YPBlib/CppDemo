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
	BIGNUM *M2=BN_new();
	
	BIGNUM* sig_1=BN_new();
	BIGNUM* sig_2=BN_new();
	

	
	BN_hex2bn(&n,"DCBFFE3E51F62E09CE7032E2677A78946A849DC4CDDE3A4D0CB81629242FB1A5");
	BN_hex2bn(&e,"010001");
	BN_hex2bn(&d,"74D806F9F3A62BAE331FFE3F0A68AFE35B3D2E4794148AACBC26AA381CD7D30D");
	BN_hex2bn(&M,"49206f776520796f75202432303030");
	BN_hex2bn(&M2,"49206f776520796f75202433303030");
	
	
	BN_mod_exp(sig_1,M,e,n,ctx);
	printBN("sig_1 is ",sig_1);
	
	BN_mod_exp(sig_2,M2,e,n,ctx);
	printBN("sig_2 is ",sig_2);
	
	
	return 0;
}
