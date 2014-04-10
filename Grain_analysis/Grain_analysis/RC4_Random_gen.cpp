#include "head.h"


u8 rc4_s[256];
u32 a11, b11;

void rc4_setup()
{
	srand((unsigned)time(NULL));
	int i,k;
	u8 rc4_key[16], temp;

	for(i=0; i<16; i++)rc4_key[i] = 0x00;
	for(i=0; i<16; i++)rc4_key[i] = ( ( ( rand() + rand() ) << 16 ) + ( rand() - rand() ) ) & 0xff;

	for(a11=0; a11<256; a11++)rc4_s[a11] = (u8)a11;

	b11 = 0;
    for(a11=0; a11<256; a11++)
	{
		b11 = ( b11 + rc4_s[a11] + rc4_key[ a11 % 5 ] ) & 0xff;
  		temp = rc4_s[a11];
	    rc4_s[a11] = rc4_s[b11];
	    rc4_s[b11] = temp;

	}

	a11 = 0; 
	b11 = 0;

	for(k=0; k<8192; k++)
	{
		a11 = ( a11 + 1 ) & 0xff;
		b11 = ( b11 + rc4_s[a11] ) & 0xff;
		temp = rc4_s[a11];
	    rc4_s[a11] = rc4_s[b11];
	    rc4_s[b11] = temp;
	
	}
}


u8 rc4( )
{
	u8 temp;
	
	a11 = ( a11 + 1 ) & 0xff;
	b11 = ( b11 + rc4_s[a11] ) & 0xff;
	temp = rc4_s[a11];
	rc4_s[a11] = rc4_s[b11];
	rc4_s[b11] = temp;
	return( rc4_s[( rc4_s[a11] + rc4_s[b11] ) & 0xff ] );

}




void randomIV(u32 *iv)
{
	int i;

	for(i=0; i<4; i++)iv[i]= ( ( rc4() << 24 ) + ( rc4() << 16 ) + ( rc4() << 8 ) + ( rc4() ) ) & 0xffffffff;
	
}

int intcmp(const void *v1, const void *v2)
 {
     return (*(int *)v1 - *(int *)v2);

 }