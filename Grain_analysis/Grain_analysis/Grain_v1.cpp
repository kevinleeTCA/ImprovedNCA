/*
	Created by Kevin Lee 2013/6/16
	This is an implemention of Grain v1
*/

#include "head.h"


//kevin edit, used for state reading
void ECRYPT_grain_state_read(ECRYPT_ctx* ctx, u8* state){
	for(int i=0;i<10;i++){
		state[i]=0;
		for (int j=0;j<8;++j) {
			state[i]+=(ctx->NFSR[i*8+j])<<j;
		}
	}
	for(int i=10;i<20;i++){
		state[i]=0;
		for (int j=0;j<8;++j) {
			state[i]+=(ctx->LFSR[(i-10)*8+j])<<j;
		}
	}
}

//kevin edit, used for state loading
void ECRYPT_grain_state_load(ECRYPT_ctx* ctx, u8* state){
	for(int i=0;i<10;i++){
		for (int j=0;j<8;++j) {
			ctx->NFSR[i*8+j]=((state[i]>>j)&1);  
		}
	}
	for(int i=10;i<20;i++){
		for (int j=0;j<8;++j) {
			ctx->LFSR[(i-10)*8+j]=((state[i]>>j)&1);  
		}
	}
}
//kevin edit for position index and rotate index
u32 posIdx(u32 pos){
	return (u32) (pos/8);
}
u32 rotateIdx(u32 pos){
	return (u32)(pos%8);
}

void ECRYPT_init(void){}
/*
 * Function: grain_keystream
 *
 * Synopsis
 *  Generates a new bit and updates the internal state of the cipher.
 */
u8 ENCRYPT_grain_keystream(ECRYPT_ctx* ctx) {
	u8 i,NBit,LBit,outbit;
	/* Calculate feedback and output bits */
	outbit = N(79)^N(78)^N(76)^N(70)^N(49)^N(37)^N(24)^boolTable[(X4<<4) | (X3<<3) | (X2<<2) | (X1<<1) | X0];
	NBit=L(80)^N(18)^N(66)^N(80)^NFTable[(N(17)<<9) | (N(20)<<8) | (N(28)<<7) | (N(35)<<6) | (N(43)<<5) | (N(47)<<4) | (N(52)<<3) | (N(59)<<2) | (N(65)<<1) | N(71)];
	LBit=L(18)^L(29)^L(42)^L(57)^L(67)^L(80);
	/* Update registers */
	for (i=1;i<(ctx->keysize);++i) {
		ctx->NFSR[i-1]=ctx->NFSR[i];
		ctx->LFSR[i-1]=ctx->LFSR[i];
	}
	ctx->NFSR[(ctx->keysize)-1]=NBit;
	ctx->LFSR[(ctx->keysize)-1]=LBit;
	return outbit;
}

/*
 for E-KSDC calculation
*/
u8 ENCRYPT_grain_E_KSDC(ECRYPT_ctx* ctx){
	u8 i,NBit,LBit,outbit;
	//calculate output bit
	if(X4|X3|X2|X1|X0){
		outbit=2;    // pending state
	}else if(N(79)>1 || N(78)>1 || N(76)>1 || N(70)>1 
		|| N(49)>1 || N(37)>1 || N(24)>1){
		outbit=2;    // pending state
	}else
		outbit= N(79)^N(78)^N(76)^N(70)^N(49)^N(37)^N(24);
	//calculate LFSR newly updated bit
	LBit=L(18)^L(29)^L(42)^L(57)^L(67)^L(80);
	//calculate NFSR newly updated bit
	if(N(17)|N(20)|N(28)|N(35)|N(43)|N(47)|N(52)|N(59)|N(65)|N(71)){
		NBit=2;		//pending state
	}else if (L(80)>1 || N(18)>1 || N(66)>1 || N(80)>1){
		NBit=2;
	}else
		NBit=L(80)^N(18)^N(66)^N(80);
	/* Update registers */
	for (i=1;i<(ctx->keysize);++i) {
		ctx->NFSR[i-1]=ctx->NFSR[i];
		ctx->LFSR[i-1]=ctx->LFSR[i];
	}
	ctx->NFSR[(ctx->keysize)-1]=NBit;
	ctx->LFSR[(ctx->keysize)-1]=LBit;
	return outbit;
}


/*
  backward direction
*/
u8 ENCRYPT_grain_keystream_backward(ECRYPT_ctx* ctx){
	u8 L0,N0,outbit,L79,N79;
	//先保存当前的LFSR[79]和NFSR[79]
	L79=ctx->LFSR[(ctx->keysize)-1];
	N79=ctx->NFSR[(ctx->keysize)-1];
	//然后再循环移位寄存器 到上一个状态
	for (int i=(ctx->keysize)-1;i>0;--i) {
		ctx->NFSR[i]=ctx->NFSR[i-1];
		ctx->LFSR[i]=ctx->LFSR[i-1];
	}
	//利用当前LFSR[79]和NFSR[79]计算 上一个时刻的LFSR[0]和NFSR[0]
	L0=L(18)^L(29)^L(42)^L(57)^L(67)^L79;
	N0=N79^L0^N(18)^N(66)^NFTable[(N(17)<<9) | (N(20)<<8) | (N(28)<<7) | (N(35)<<6) | (N(43)<<5) | (N(47)<<4) | (N(52)<<3) | (N(59)<<2) | (N(65)<<1) | N(71)];
	//更新LFSR[0]和NFSR[0]
	ctx->NFSR[0]=N0;
	ctx->LFSR[0]=L0;
	//计算上一个时刻的输出bit
	outbit = N(79)^N(78)^N(76)^N(70)^N(49)^N(37)^N(24)^boolTable[(X4<<4) | (X3<<3) | (X2<<2) | (X1<<1) | X0];
	return outbit;
}
/*
  for BW-E-KSDC calculation
*/
u8 ENCRYPT_grain_BW_E_KSDC(ECRYPT_ctx* ctx){
	u8 L0,N0,outbit,L79,N79;
	//先保存当前的LFSR[79]和NFSR[79]
	L79=ctx->LFSR[(ctx->keysize)-1];
	N79=ctx->NFSR[(ctx->keysize)-1];
	//然后再循环移位寄存器 到上一个状态
	for (int i=(ctx->keysize)-1;i>0;--i) {
		ctx->NFSR[i]=ctx->NFSR[i-1];
		ctx->LFSR[i]=ctx->LFSR[i-1];
	}
	//利用当前LFSR[79]和NFSR[79]计算 上一个时刻的LFSR[0]和NFSR[0]
	L0=L(18)^L(29)^L(42)^L(57)^L(67)^L79;
	if(N(17)|N(20)|N(28)|N(35)|N(43)|N(47)|N(52)|N(59)|N(65)|N(71)){
		N0=2;		//pending state
	}else if (N79>1 || L0>1 || N(18)>1 || N(66)>1){
		N0=2;
	}else
		N0=N79^L0^N(18)^N(66);
	//更新LFSR[0]和NFSR[0]
	ctx->NFSR[0]=N0;
	ctx->LFSR[0]=L0;
		//calculate output bit
	if(X4|X3|X2|X1|X0){
		outbit=2;    // pending state
	}else if(N(79)>1 || N(78)>1 || N(76)>1 || N(70)>1 
		|| N(49)>1 || N(37)>1 || N(24)>1){
		outbit=2;    // pending state
	}else
		outbit= N(79)^N(78)^N(76)^N(70)^N(49)^N(37)^N(24);
	return outbit;
}

/* Functions for the ECRYPT API */

void ECRYPT_keysetup(
  ECRYPT_ctx* ctx, 
  const u8* key, 
  u32 keysize,                /* Key size in bits. */ 
  u32 ivsize)				  /* IV size in bits. */ 
{
	ctx->p_key=key;
	ctx->keysize=keysize;
	ctx->ivsize=ivsize;
}

/*
 * Function: ECRYPT_ivsetup
 *
 * Synopsis
 *  Load the key and perform initial clockings.
 *
 * Assumptions
 *  The key is 10 bytes and the IV is 8 bytes. The
 *  registers are loaded in the following way:
 *  
 *  NFSR[0] = lsb of key[0]
 *  ...
 *  NFSR[7] = msb of key[0]
 *  ...
 *  ...
 *  NFSR[72] = lsb of key[9]
 *  ...
 *  NFSR[79] = msb of key[9]
 *  LFSR[0] = lsb of IV[0]
 *  ...
 *  LFSR[7] = msb of IV[0]
 *  ...
 *  ...
 *  LFSR[56] = lsb of IV[7]
 *  ...
 *  LFSR[63] = msb of IV[7]
 */
void ECRYPT_ivsetup(
  ECRYPT_ctx* ctx, 
  const u8* iv)
{
	u32 i,j;
	u8 outbit;
	/* load registers */
	for (i=0;i<(ctx->ivsize)/8;++i) {
		for (j=0;j<8;++j) {
			ctx->NFSR[i*8+j]=((ctx->p_key[i]>>j)&1);  
			ctx->LFSR[i*8+j]=((iv[i]>>j)&1);
		}
	}
	for (i=(ctx->ivsize)/8;i<(ctx->keysize)/8;++i) {
		for (j=0;j<8;++j) {
			ctx->NFSR[i*8+j]=((ctx->p_key[i]>>j)&1);
			ctx->LFSR[i*8+j]=1;
		}
	}
	/* do initial clockings */
	for (i=0;i<INITCLOCKS;++i) {
		outbit=ENCRYPT_grain_keystream(ctx);
		ctx->LFSR[79]^=outbit;
		ctx->NFSR[79]^=outbit;             
	}
}

/*
 * Function: ECRYPT_keystream_bytes
 *
 * Synopsis
 *  Generate keystream in bytes.
 *
 * Assumptions
 *  Bits are generated in order z0,z1,z2,...
 *  The bits are stored in a byte in order:
 *  
 *  lsb of keystream[0] = z0
 *  ...
 *  msb of keystream[0] = z7
 *  ...
 *  lsb of keystream[1] = z8
 *  ...
 *  msb of keystream[1] = z15
 *  ...
 *  ...
 *  ...
 *  Example: The bit keystream: 10011100 10110011 ..
 *  corresponds to the byte keystream: 39 cd ..
 */
void ECRYPT_keystream_bytes(
  ECRYPT_ctx* ctx, 
  u8* keystream, 
  u32 msglen)
{
	u32 i,j;
	for (i = 0; i < msglen; ++i) {
		keystream[i]=0;
		for (j = 0; j < 8; ++j) {
			keystream[i]|=(ENCRYPT_grain_keystream(ctx)<<j);
		}
	}
}



//kevin edit for backward keystream calculate
void ECRYPT_keystream_backward_bytes(
  ECRYPT_ctx* ctx, 
  u8* keystream, 
  u32 msglen)
{
	u32 i,j;
	for (i = 0; i < msglen; ++i) {
		keystream[i]=0;
		for (j = 0; j < 8; ++j) {
			keystream[i]|=(ENCRYPT_grain_keystream_backward(ctx)<<j);
			//grain_keystream_backward(ctx);
		}

	}
	/*//正向输出
	for (i = 0; i < msglen; ++i) {
		keystream[i]=0;
		for (j = 0; j < 8; ++j) {
			//keystream[i]|=(grain_keystream_backward(ctx)<<j);
			keystream[i]|=(grain_keystream(ctx)<<j);
		}

	}
	*/
	
}

void ECRYPT_encrypt_bytes(
  ECRYPT_ctx* ctx, 
  const u8* plaintext, 
  u8* ciphertext, 
  u32 msglen)
{
	u32 i,j;
	u8 k;
	for (i = 0; i < msglen; ++i) {
		k=0;
		for (j = 0; j < 8; ++j) {	
			k|=(ENCRYPT_grain_keystream(ctx)<<j);
		}
		ciphertext[i]=plaintext[i]^k;
	}
}

void ECRYPT_decrypt_bytes(
  ECRYPT_ctx* ctx, 
  const u8* ciphertext, 
  u8* plaintext, 
  u32 msglen)
{
	u32 i,j;
	u8 k=0;
	for (i = 0; i < msglen; ++i) {
		k=0;
		for (j = 0; j < 8; ++j) {
			k|=(ENCRYPT_grain_keystream(ctx)<<j);
		}
		plaintext[i]=ciphertext[i]^k;
	}
}