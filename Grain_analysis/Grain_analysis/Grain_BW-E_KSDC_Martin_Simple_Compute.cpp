/*
	Created by Kevin Lee 2014/4/11
	Given ISDs with hamming weight at most d, calculate its BW-E-KSDC and record the average number
	of fixed positions in the keystream
*/


#include "head.h"

/* general algorithm
  d: ISD hamming weight
  num_ISD: the number of ISDs enumerated.
  this function return the average number of fixed positions in the keystreams
*/
void average_fixed_pos_BW_E_KSDC(u32 d,u32 num_ISD){
	
	double average_E_KSDC_pos_num=0.0;
	for(int D=1;D<=num_ISD;D++){
		//randomly induce the differences to d positions.  NFSR:0~79，LFSR:80~159
		u32* pos=new u32[d]();
		for(int j=0;j<d;j++){
			pos[j]=rc4() % 160;
			//pos[j]=(rc4() % 80)+80;				//只给LFSR中引入差分
				//pos[j]=(rc4() % 80);				//只给NFSR中引入差分
			//pos[j]=(rc4() % 40)+80;			//只給LFSR的左半部分引入差分 80-119
			//pos[j]=(rc4() % 40)+120;			//只给LFSR的右半部分引入差分 120-159
			while(isExist(pos,j,pos[j]))		//to ensure the non-duplicated positions
				pos[j]=rc4() % 160;
				//pos[j]=(rc4() % 80)+80;			//只给LFSR中引入差分
				//pos[j]=(rc4() % 80);				//只给NFSR中引入差分
			//pos[j]=(rc4() % 40)+80;			//只給LFSR的左半部分引入差分 80-119
			//pos[j]=(rc4() % 40)+120;			//只给LFSR的右半部分引入差分 120-159
		}
		// induce the differece to selected position
		u8 ISD[LEN];
		for(int j=0;j<LEN;j++){
			ISD[j]=0;
		}
		for(int j=0;j<d;j++){
			u32 p=posIdx(pos[j]);
			u32 r=rotateIdx(pos[j]);
			ISD[p]=ISD[p]^(1<<r);
		}
		// generate BW-E-KSDC and record the number of fixed positions
		ECRYPT_ctx ctx;
		ctx.keysize=80;
		ctx.ivsize=64;
		ECRYPT_grain_state_load(&ctx,ISD);
		u8 BW_E_KSDC_Array[KSLen*8];
		for(int j=0;j<KSLen*8;j++){
			BW_E_KSDC_Array[j]=ENCRYPT_grain_BW_E_KSDC(&ctx);
			if(BW_E_KSDC_Array[j]<2)
				average_E_KSDC_pos_num++;
		}
	}
	average_E_KSDC_pos_num=(double)average_E_KSDC_pos_num/num_ISD;
	cout<<"The average fixed pos(d,l):("
			<<d<<","<<KSLen*8<<",) is "<<setprecision(3)<<average_E_KSDC_pos_num<<endl;
}




/* general algorithm
  d: ISD hamming weight
  pos: position indexes of active bit    NFSR:0~79，LFSR:80~159
  this function return the BW-E-KSDC sequence , give a specific ISD
*/

string BW_E_KSDC_seq_with_given_ISD(u32 d,u32 *pos){
	//induce differences
	u8 ISD[LEN];
	for(int j=0;j<LEN;j++){
		ISD[j]=0;
	}
	for(int j=0;j<d;j++){
		u32 p=posIdx(pos[j]);
		u32 r=rotateIdx(pos[j]);
		ISD[p]=ISD[p]^(1<<r);
	}
	// generate BW-E-KSDC
	ECRYPT_ctx ctx;
	ctx.keysize=80;
	ctx.ivsize=64;
	ECRYPT_grain_state_load(&ctx,ISD);
	u8 BW_E_KSDC_Array[KSLen*8];
	string BW_E_KSDC="";
	for(int j=0;j<KSLen*8;j++){
		BW_E_KSDC_Array[j]=ENCRYPT_grain_BW_E_KSDC(&ctx);
		if(BW_E_KSDC_Array[j]==0){
			BW_E_KSDC.append("0");
			//E_KSDC_pos_num++;
			//non_act_pos.push_back(j+1);
		}else if(BW_E_KSDC_Array[j]==1){
			BW_E_KSDC.append("1");
			//E_KSDC_pos_num++;
			//act_pos.push_back(j+1);
		}else{
			BW_E_KSDC.append("*");
			//pending_pos.push_back(j+1);
		}
	}
	return BW_E_KSDC;
}