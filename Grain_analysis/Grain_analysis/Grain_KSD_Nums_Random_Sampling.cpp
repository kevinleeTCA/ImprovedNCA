/*
	Created by Kevin Lee 2013/6/16
	random sampling ISD with Hamming weight <= d
	calculating all possible KSD.
	N是每一个ISD随机选择的状态数目
	计算出所有可能KSD与N*num_ISD的比例q，作为我们估计Q(n,d,l)的估计:
	Q(n,d,l)=(约等于)q*N*V(n,d) 
	当然Q(n,d,l)的最大值为2^{l}
*/


#include "head.h"

double cal_all_KSD_with_Random_Sampling(u32 d, u64* N_array, u32 num_ISD){
	set<string> poss_KSD;
	double prop_q=0.0;
	u64 N_sum=0;
	u64 N=N_array[d-1];
	for(int D=1;D<=num_ISD;D++){
		////随机选取汉明重量HW_d <=d
		//u32 HW_d=0;
		//while(HW_d==0)
		//	HW_d= rc4() % (d+1);
		////根据HW_d选择样本量
		//u64 N=N_array[HW_d-1];
		//N_sum+=N;
		//随机选取160bit 状态的差分位置 NFSR从0~79，LFSR从80~159
		u32* pos=new u32[d]();
		for(int j=0;j<d;j++){
			pos[j]=rc4() % 160;
			//pos[j]=(rc4() % 80)+80;			//只给LFSR中引入差分
		}
		//初始化 输入差分为全0
		u8 ISD[LEN];
		for(int j=0;j<LEN;j++){
			ISD[j]=0;
		}
		//引入差分
		for(int j=0;j<d;j++){
			u32 p=posIdx(pos[j]);
			u32 r=rotateIdx(pos[j]);
			ISD[p]=ISD[p]^(1<<r);
		}
		//对每个差分随机选取N个状态
		for(u64 i=0;i<N;i++){
			//随机选择一个输入状态
			u8 rnd_state_1[LEN];
			for(int j=0;j<LEN;j++){
				rnd_state_1[j]=rc4();
			}
			//根据差分位置，得到另一个状态rud_state_2
			u8 rnd_state_2[LEN];
			for(int j=0;j<LEN;j++){
				rnd_state_2[j]=rnd_state_1[j]^ISD[j];
			}
			//分别代入Grain中
			ECRYPT_ctx ctx_1;
			ctx_1.keysize=80;
			ctx_1.ivsize=64;
			u8 keyStream_1[KSLen];
			ECRYPT_ctx ctx_2;
			ctx_2.keysize=80;
			ctx_2.ivsize=64;
			u8 keyStream_2[KSLen];
			//将状态代入grain中,获得对应的长度为KSLen的密钥流，并输出其差分
			ECRYPT_grain_state_load(&ctx_1,rnd_state_1);
			ECRYPT_grain_state_load(&ctx_2,rnd_state_2);
			ECRYPT_keystream_bytes(&ctx_1,keyStream_1,KSLen);
			ECRYPT_keystream_bytes(&ctx_2,keyStream_2,KSLen);
			//计算输出差分
			u8 Diff_KS[KSLen];
			for(int j=0;j<KSLen;j++){
				Diff_KS[j]=keyStream_1[j]^keyStream_2[j];
			}
			string str=char2HexString(Diff_KS,KSLen);
			poss_KSD.insert(str);
		}

		delete [] pos;
	}
	prop_q=(double)poss_KSD.size()/(num_ISD*N);
	cout<<"对于(d,l)=("<<d<<","<<KSLen*8<<")而言，最终的比例为No. of KSD/No.of Sampling："
		<<poss_KSD.size()<<"/"<<num_ISD*N<<",比例为q:"<<prop_q<<endl;
	return prop_q;
}