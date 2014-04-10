/*
	Created by Kevin Lee 2013/6/16
	random sampling ISD with Hamming weight <= d
	calculating all possible KSD.
	N��ÿһ��ISD���ѡ���״̬��Ŀ
	��������п���KSD��N*num_ISD�ı���q����Ϊ���ǹ���Q(n,d,l)�Ĺ���:
	Q(n,d,l)=(Լ����)q*N*V(n,d) 
	��ȻQ(n,d,l)�����ֵΪ2^{l}
*/


#include "head.h"

double cal_all_KSD_with_Random_Sampling(u32 d, u64* N_array, u32 num_ISD){
	set<string> poss_KSD;
	double prop_q=0.0;
	u64 N_sum=0;
	u64 N=N_array[d-1];
	for(int D=1;D<=num_ISD;D++){
		////���ѡȡ��������HW_d <=d
		//u32 HW_d=0;
		//while(HW_d==0)
		//	HW_d= rc4() % (d+1);
		////����HW_dѡ��������
		//u64 N=N_array[HW_d-1];
		//N_sum+=N;
		//���ѡȡ160bit ״̬�Ĳ��λ�� NFSR��0~79��LFSR��80~159
		u32* pos=new u32[d]();
		for(int j=0;j<d;j++){
			pos[j]=rc4() % 160;
			//pos[j]=(rc4() % 80)+80;			//ֻ��LFSR��������
		}
		//��ʼ�� ������Ϊȫ0
		u8 ISD[LEN];
		for(int j=0;j<LEN;j++){
			ISD[j]=0;
		}
		//������
		for(int j=0;j<d;j++){
			u32 p=posIdx(pos[j]);
			u32 r=rotateIdx(pos[j]);
			ISD[p]=ISD[p]^(1<<r);
		}
		//��ÿ��������ѡȡN��״̬
		for(u64 i=0;i<N;i++){
			//���ѡ��һ������״̬
			u8 rnd_state_1[LEN];
			for(int j=0;j<LEN;j++){
				rnd_state_1[j]=rc4();
			}
			//���ݲ��λ�ã��õ���һ��״̬rud_state_2
			u8 rnd_state_2[LEN];
			for(int j=0;j<LEN;j++){
				rnd_state_2[j]=rnd_state_1[j]^ISD[j];
			}
			//�ֱ����Grain��
			ECRYPT_ctx ctx_1;
			ctx_1.keysize=80;
			ctx_1.ivsize=64;
			u8 keyStream_1[KSLen];
			ECRYPT_ctx ctx_2;
			ctx_2.keysize=80;
			ctx_2.ivsize=64;
			u8 keyStream_2[KSLen];
			//��״̬����grain��,��ö�Ӧ�ĳ���ΪKSLen����Կ�������������
			ECRYPT_grain_state_load(&ctx_1,rnd_state_1);
			ECRYPT_grain_state_load(&ctx_2,rnd_state_2);
			ECRYPT_keystream_bytes(&ctx_1,keyStream_1,KSLen);
			ECRYPT_keystream_bytes(&ctx_2,keyStream_2,KSLen);
			//����������
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
	cout<<"����(d,l)=("<<d<<","<<KSLen*8<<")���ԣ����յı���ΪNo. of KSD/No.of Sampling��"
		<<poss_KSD.size()<<"/"<<num_ISD*N<<",����Ϊq:"<<prop_q<<endl;
	return prop_q;
}