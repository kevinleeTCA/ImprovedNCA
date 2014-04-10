/*
	Created by Kevin Lee 2013/10/02
	This is an implemention of Grain v1 with sampling resistance
*/

#include "head.h"


//void grain_v1_sampling_resistance(ECRYPT_ctx* ctx,u32 *L,u32 *N){
void grain_v1_sampling_resistance(ECRYPT_ctx* ctx,u8 *IS){
	u32 L[80],N[80];
	for(int j=0;j<80;j++){
		N[j]=(IS[j/8]>>j%8)&0x01;
		L[j]=(IS[10+j/8]>>j%8)&0x01;
	}
	//get the unknown internal state bits
	//the first 16 bits
	for(int i=0;i<8;i++){
		N[10+i]= N[1+i]^N[2+i]^N[4+i]^N[31+i]^N[43+i]^N[56+i]^boolTable[(N[63+i]<<4)|(L[64+i]<<3)|(L[46+i]<<2)|(L[25+i]<<1)|(L[3+i])];
	}
	//the 17th bit
	//u32 newL=L[0]^L[13]^L[23]^L[38]^L[51]^L[62];
	//N[26]=N[17]^N[18]^N[20]^N[47]^N[59]^N[72]^boolTable[(N[79]<<4)|(newL<<3)|(L[62]<<2)|(L[41]<<1)|(L[19])];
	//the 18th bit
	//newL=L[1]^L[14]^L[24]^L[39]^L[52]^L[63];
	//u32 newN=L[0]^N[62]^N[14]^N[0]
	//	 ^NFTable[(N[63]<<9) | (N[60]<<8) | (N[52]<<7) | (N[45]<<6) | (N[37]<<5) | (N[33]<<4) | (N[28]<<3) | (N[21]<<2) | (N[15]<<1) | N[9]];
	//N[27]=N[18]^N[19]^N[21]^N[48]^N[60]^N[73]^boolTable[(newN<<4)|(newL<<3)|(L[63]<<2)|(L[42]<<1)|(L[20])];
	//
	////the 19th bit
	//newL=L[2]^L[15]^L[25]^L[40]^L[53]^L[64];
	//u32 x_4_REST=L[43]^(L[21]&newL)^(L[64]&newL)^(L[21]&L[43]&L[64])^(L[21]&L[64]&newL);
	//u32 x_4_factor=1^newL^(L[21]&L[64])^(L[43]&L[64])^(L[64]&newL) ;
	//if(x_4_factor!=0){
	//	u32 N_i_28_factor=1^(N[34]&N[22])^(N[64]&N[46]&N[10])^(N[34]&N[22]&N[16]&N[10])^(N[53]&N[46]&N[38]&N[34]&N[22]);
	//	u32 N_i_28_rest=L[1]^N[63]^N[61]^N[53]^N[46]^N[38]^N[34]^N[22]^N[15]^N[10]^N[1]
	//					^(N[64]&N[61])^(N[38]&N[34])^(N[16]&N[10])^(N[61]&N[53]&N[46])
	//					^(N[61]&N[53]&N[38]&N[34])^(N[64]&N[61]&N[22]&N[16])
	//					^(N[64]&N[61]&N[53]&N[46]&N[38]);
	//	if(N_i_28_factor!=0)
	//		N[29]=N[19]^N[20]^N[22]^N[28]^N[49]^N[61]^N[74]^x_4_REST^N_i_28_rest;		
	//}
	////the 20th bit
	//newL=L[3]^L[16]^L[26]^L[41]^L[54]^L[65];
	//x_4_REST=L[44]^(L[22]&newL)^(L[65]&newL)^(L[22]&L[44]&L[65])^(L[22]&L[65]&newL);
	//x_4_factor=1^newL^(L[22]&L[65])^(L[44]&L[65])^(L[65]&newL);
	//if(x_4_factor!=0){
	//	u32 N_i_28_factor=1^(N[35]&N[23])^(N[65]&N[47]&N[11])^(N[35]&N[23]&N[17]&N[11])^(N[54]&N[47]&N[39]&N[35]&N[23]);
	//	u32 N_i_28_rest=L[2]^N[64]^N[62]^N[54]^N[47]^N[39]^N[35]^N[23]^N[16]^N[11]^N[2]
	//					^(N[65]&N[62])^(N[39]&N[35])^(N[17]&N[11])^(N[62]&N[54]&N[47])
	//					^(N[62]&N[54]&N[39]&N[35])^(N[65]&N[62]&N[23]&N[17])
	//					^(N[65]&N[62]&N[54]&N[47]&N[39]);
	//	if(N_i_28_factor!=0)
	//		N[30]=N[20]^N[21]^N[23]^N[29]^N[50]^N[62]^N[75]^x_4_REST^N_i_28_rest;
	//}	
	////the 21st bit
	//
	//newL=L[4]^L[17]^L[27]^L[42]^L[55]^L[66];
	//newN=L[3]^N[65]^N[17]^N[3]
	//	^NFTable[(N[66]<<9) | (N[64]<<8) | (N[55]<<7) | (N[48]<<6) | (N[40]<<5) | (N[36]<<4) | (N[31]<<3) | (N[24]<<2) | (N[18]<<1) | N[12]];
	//u32 x_1_REST=newN^(L[23]&newL)^(L[66]&newL)^(newL&newN)^(L[23]&L[66]&newL)^(L[23]&L[66]&newN)^(L[66]&newL&newN);
	//u32 x_1_factor=1^(L[23]&L[66])^(L[45]&newN);
	//if(x_1_factor!=0){
	//	L[45]=N[21]^N[22]^N[24]^N[30]^N[51]^N[63]^N[76]^x_1_REST;
	//}
	//load the state
	for(int i=0;i<80;i++){
		ctx->LFSR[i]=L[i];
		ctx->NFSR[i]=N[i];
	}
	ctx->keysize=80;
	ctx->ivsize=64;
}

//给定142个内部状态之后，输出18个0之外的 比特流
void grain_sampling_resistance_genKSBytes(ECRYPT_ctx* ctx,
  u8* keystream,
  u32 length){
	//首先输出18个全0的pattern
	for(int k=1;k<=18;k++)
		ENCRYPT_grain_keystream(ctx);
	//然后输出的密钥流作为真正的密钥流
	ECRYPT_keystream_bytes(ctx,keystream,length);
}