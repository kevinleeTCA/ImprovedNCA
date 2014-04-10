#include "head.h"

//���Զ�������һ�������ISD��Ӧ��KSD characteristic�й̶�λ�õĸ���
/*������
d:�����ֵ����������
num_ISD:���ѡ��������Ϊd�������ֵĸ���
N:ÿһ����ֶ�Ӧ�Ĳ�������������
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
		//���ѡȡ142 bit ״̬�Ĳ��λ�� NFSR��0~79��LFSR��80~159
		u32* pos=new u32[d]();
		for(int j=0;j<d;j++){
			pos[j]=rc4() % 160;
			while(isExistWithSP(pos,j,pos[j],17))		//��֤���λ�ò�������ظ�
				pos[j]=rc4() % 160;
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
		//����KSD characteristic
		u8 And_logic[KSLen];   //����ȷ�������ȫ1��λ��
		u8 Or_logic[KSLen];		//����ȷ�������ȫ0��λ��
		//��ʼ�� and �� or logic
		for(int i=0;i<KSLen;i++){
			And_logic[i]=255;
			Or_logic[i]=0;
		}
		for(int i=0;i<N;i++){
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
			//���Ȼ��18�����ڲ�״̬��ȡֵ
			grain_v1_sampling_resistance(&ctx_1,rnd_state_1);
			grain_v1_sampling_resistance(&ctx_2,rnd_state_2);
			//��״̬����grain��,��ö�Ӧ�ĳ���ΪKSLen����Կ�������������
			ECRYPT_keystream_bytes(&ctx_1,keyStream_1,KSLen);
			ECRYPT_keystream_bytes(&ctx_2,keyStream_2,KSLen);
			//����������
			u8 Diff_KS[KSLen];
			for(int j=0;j<KSLen;j++){
				Diff_KS[j]=keyStream_1[j]^keyStream_2[j];
			}
			//����KSD characteristic
			for(int j=0;j<KSLen;j++){
				And_logic[j]&=Diff_KS[j];
				Or_logic[j]|=Diff_KS[j];
			}
		}
		//���㵱ǰ�����ֶ�Ӧ��KSD��characteristic  
		//And�߼�ȷ��ȫ1��λ��  Or�߼�ȷ��ȫ0��λ��  ʣ�µľ��ǲ�ȷ����λ��
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
			cout<<"�����ֵ�KSD characteristicΪ:"<<KSD_character<<endl;
			cout<<" �̶�λ�õĸ�����"<<KW_KSD_CH<<endl<<endl;
		}*/
		delete [] pos;
	/*	cout<<"�����ֵ�KSD characteristicΪ:"<<KSD_character<<endl;
		cout<<" �̶�λ�õĸ�����"<<KW_KSD_CH<<endl<<endl;*/
	}
	average_KSD_fixed_pos_num=(double)average_KSD_fixed_pos_num/num_ISD;
	//average_HM_val=(double)average_HM_val/num_ISD;
		//cout<<"Average Hamming weight:"<<setprecision(3)<<average_HM_val<<"  The average fixed pos(d,l,N):("
		//	<<d<<","<<KSLen<<","<<N<<") is "<<setprecision(3)<<average_KSD_fixed_pos_num<<endl;
	cout<<"The average fixed pos(d,l,N):("
			<<d<<","<<KSLen<<","<<N<<") is "<<setprecision(3)<<average_KSD_fixed_pos_num<<endl;
}