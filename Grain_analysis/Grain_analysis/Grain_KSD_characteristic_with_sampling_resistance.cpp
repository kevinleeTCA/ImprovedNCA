#include "head.h"

//测试对于任意一个随机的ISD对应的KSD characteristic中固定位置的个数
/*参数：
d:输入差分的最大汉明重量
num_ISD:随机选择汉明重量为d的输入差分的个数
N:每一个差分对应的测试样本的数量
*/

bool isExistWithSP(u32 *pos,int j,u32 curr_val,u32 range){
	for(int i=0;i<j;i++){
		if(curr_val==pos[i] || (curr_val>=10 && curr_val<=range))
			return true;
	}
	return false;
}


void ave_KSD_pos_with_fixed_diff_with_SP(u32 d,u32 num_ISD,u32 N){
	double average_KSD_fixed_pos_num=0.0;
	//double average_HM_val=0.0;
	//map<string,u32> counter;
	for(int D=1;D<=num_ISD;D++){
		//随机选取142 bit 状态的差分位置 NFSR从0~79，LFSR从80~159
		u32* pos=new u32[d]();
		for(int j=0;j<d;j++){
			pos[j]=rc4() % 160;
			while(isExistWithSP(pos,j,pos[j],17))		//保证随机位置不会出现重复
				pos[j]=rc4() % 160;
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
		//计算KSD characteristic
		u8 And_logic[KSLen];   //用来确定差分中全1的位置
		u8 Or_logic[KSLen];		//用来确定差分中全0的位置
		//初始化 and 和 or logic
		for(int i=0;i<KSLen;i++){
			And_logic[i]=255;
			Or_logic[i]=0;
		}
		for(int i=0;i<N;i++){
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
			//首先获得18比特内部状态的取值
			grain_v1_sampling_resistance(&ctx_1,rnd_state_1);
			grain_v1_sampling_resistance(&ctx_2,rnd_state_2);
			//将状态代入grain中,获得对应的长度为KSLen的密钥流，并输出其差分
			ECRYPT_keystream_bytes(&ctx_1,keyStream_1,KSLen);
			ECRYPT_keystream_bytes(&ctx_2,keyStream_2,KSLen);
			//计算输出差分
			u8 Diff_KS[KSLen];
			for(int j=0;j<KSLen;j++){
				Diff_KS[j]=keyStream_1[j]^keyStream_2[j];
			}
			//计算KSD characteristic
			for(int j=0;j<KSLen;j++){
				And_logic[j]&=Diff_KS[j];
				Or_logic[j]|=Diff_KS[j];
			}
		}
		//计算当前输入差分对应的KSD的characteristic  
		//And逻辑确定全1的位置  Or逻辑确定全0的位置  剩下的就是不确定的位置
		string KSD_character="";
		int KW_KSD_CH=0;
		for(int i=0;i<KSLen;i++){
			u8 t_and=And_logic[i];
			u8 t_or=Or_logic[i];
			for(int j=0;j<8;j++){
				if((t_and>>j)&0x01){
					average_KSD_fixed_pos_num++;
					KW_KSD_CH++;
					KSD_character.append("1");
				}
				else if(!( (t_or>>j)&0x01 )){
					average_KSD_fixed_pos_num++;
					KW_KSD_CH++;
					KSD_character.append("0");
				}
				else
					KSD_character.append("*");
			}
		}
		/*if(KW_KSD_CH>15){
			cout<<"输出差分的KSD characteristic为:"<<KSD_character<<endl;
			cout<<" 固定位置的个数："<<KW_KSD_CH<<endl<<endl;
		}*/
		delete [] pos;
	/*	cout<<"输出差分的KSD characteristic为:"<<KSD_character<<endl;
		cout<<" 固定位置的个数："<<KW_KSD_CH<<endl<<endl;*/
	}
	average_KSD_fixed_pos_num=(double)average_KSD_fixed_pos_num/num_ISD;
	//average_HM_val=(double)average_HM_val/num_ISD;
		//cout<<"Average Hamming weight:"<<setprecision(3)<<average_HM_val<<"  The average fixed pos(d,l,N):("
		//	<<d<<","<<KSLen<<","<<N<<") is "<<setprecision(3)<<average_KSD_fixed_pos_num<<endl;
	cout<<"The average fixed pos(d,l,N):("
			<<d<<","<<KSLen<<","<<N<<") is "<<setprecision(3)<<average_KSD_fixed_pos_num<<endl;
}