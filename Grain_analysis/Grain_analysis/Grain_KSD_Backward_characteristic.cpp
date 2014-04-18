/*
	Created by Kevin Lee 2013/9/23
	Observation of backward KSD characteristic of Grain v1.
	for each ISD�� observe its positions in KSD with fixed differential value (0/1)
	counter the average number of those positions.
*/

#include "head.h"
//���Զ�������һ�������ISD��Ӧ��backward KSD characteristic�й̶�λ�õĸ���
/*������
d:�����ֵ����������
num_ISD:���ѡ��������Ϊd�������ֵĸ���
N:ÿһ����ֶ�Ӧ�Ĳ�������������
*/
void BW_ave_KSD_pos_with_fixed_diff(u32 d,u32 num_ISD,u32 N){
	double average_KSD_fixed_pos_num=0.0;
	double average_HM_val=0.0;
	//map<string,u32> counter;
	for(int D=1;D<=num_ISD;D++){
		u32* pos=new u32[d]();
		for(int j=0;j<d;j++){
			pos[j]=rc4() % 160;
			while(isExist(pos,j,pos[j]))		//��֤���λ�ò�������ظ�
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
			//��״̬����grain��,��ö�Ӧ�ĳ���ΪKSLen��ǰ����Կ�������������
			ECRYPT_grain_state_load(&ctx_1,rnd_state_1);
			ECRYPT_grain_state_load(&ctx_2,rnd_state_2);
			ECRYPT_keystream_backward_bytes(&ctx_1,keyStream_1,KSLen);
			ECRYPT_keystream_backward_bytes(&ctx_2,keyStream_2,KSLen);
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
		delete [] pos;
	}
	average_KSD_fixed_pos_num=(double)average_KSD_fixed_pos_num/num_ISD;
	cout<<"The average fixed pos(d,l,N)-Backward:("
			<<d<<","<<KSLen<<","<<N<<") is "<<setprecision(3)<<average_KSD_fixed_pos_num<<endl;
}




//���Զ�������һ��ָ����ISD��Ӧ��KSD characteristic�й̶�λ�õĸ������Լ�0,1,*λ�õķֲ�
/*������
d:�����ֵ����������,Ҳ��������pos�ĳ���
pos:������λ�õ��±�����
num_ISD:���ѡ��������Ϊd�������ֵĸ���
N:ÿһ����ֶ�Ӧ�Ĳ�������������
*/

void BW_KSD_pos_with_fixed_diff(u32 d,u32 *pos,u32 num_ISD,u32 N){
	for(int D=1;D<=num_ISD;D++){
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
		u8 And_logic[KSLen];   //����ȷ��ǰ������ȫ1��λ��
		u8 Or_logic[KSLen];		//����ȷ��ǰ������ȫ0��λ��
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
			//��״̬����grain��,��ö�Ӧ�ĳ���ΪKSLen��ǰ����Կ�������������
			ECRYPT_grain_state_load(&ctx_1,rnd_state_1);
			ECRYPT_grain_state_load(&ctx_2,rnd_state_2);
			ECRYPT_keystream_backward_bytes(&ctx_1,keyStream_1,KSLen);
			ECRYPT_keystream_backward_bytes(&ctx_2,keyStream_2,KSLen);
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
		//�ֱ��¼Active  non-active��possible activeλ�õ��±�
		vector<int> act_pos;
		vector<int> non_act_pos;
		vector<int> poss_act_pos;
		string KSD_character="";
		int KW_KSD_CH=0;
		for(int i=0;i<KSLen;i++){
			u8 t_and=And_logic[i];
			u8 t_or=Or_logic[i];
			for(int j=0;j<8;j++){
				if((t_and>>j)&0x01){
					KW_KSD_CH++;
					KSD_character.append("1");
					act_pos.push_back(i*8+j+1);
				}
				else if(!( (t_or>>j)&0x01 )){
					KW_KSD_CH++;
					KSD_character.append("0");
					non_act_pos.push_back(i*8+j+1);
				}
				else{
					KSD_character.append("*");
					poss_act_pos.push_back(i*8+j+1);
				}
			}
		}
		cout<<"Backward KSD characteristic:"<<KSD_character;
		cout<<"\n�̶�λ�õĸ�����"<<KW_KSD_CH;
		cout<<"\n��Ծλ��Ϊ��{";
		vector<int>::iterator beg=act_pos.begin();
		vector<int>::iterator end=act_pos.end();
		for(;beg!=end;beg++){
			cout<<*beg<<",";
		}
		cout<<"}\n�ǻ�Ծλ��Ϊ��{";
		beg=non_act_pos.begin();
		end=non_act_pos.end();
		for(;beg!=end;beg++){
			cout<<*beg<<",";
		}
		cout<<"}\n";
	}
}



/*numerical experiment
  d: ISD hamming weight
  pos: position indexes of active bit    NFSR:0~79��LFSR:80~159
  this function return the BW-E-KSDC sequence , give a specific ISD
 */
string BW_KSD_seq_with_fixed_diff(u32 d,u32 *pos,u32 N){
	    //initial ISD
		u8 ISD[LEN];
		for(int j=0;j<LEN;j++){
			ISD[j]=0;
		}
		//induce differences
		for(int j=0;j<d;j++){
			u32 p=posIdx(pos[j]);
			u32 r=rotateIdx(pos[j]);
			ISD[p]=ISD[p]^(1<<r);
		}
		u8 And_logic[KSLen];   //to determine the absolute active state
		u8 Or_logic[KSLen];		//to determine the non-active state
		for(int i=0;i<KSLen;i++){
			And_logic[i]=255;
			Or_logic[i]=0;
		}
		for(int i=0;i<N;i++){
			//randomly generate a state
			u8 rnd_state_1[LEN];
			for(int j=0;j<LEN;j++){
				rnd_state_1[j]=rc4();
			}
			//calculate the companion state, according to the ISD
			u8 rnd_state_2[LEN];
			for(int j=0;j<LEN;j++){
				rnd_state_2[j]=rnd_state_1[j]^ISD[j];
			}
			//load to Grain v1
			ECRYPT_ctx ctx_1;
			ctx_1.keysize=80;
			ctx_1.ivsize=64;
			u8 keyStream_1[KSLen];
			ECRYPT_ctx ctx_2;
			ctx_2.keysize=80;
			ctx_2.ivsize=64;
			u8 keyStream_2[KSLen];
			//calculate the backward KSD
			ECRYPT_grain_state_load(&ctx_1,rnd_state_1);
			ECRYPT_grain_state_load(&ctx_2,rnd_state_2);
			ECRYPT_keystream_backward_bytes(&ctx_1,keyStream_1,KSLen);
			ECRYPT_keystream_backward_bytes(&ctx_2,keyStream_2,KSLen);
			//calculate the difference
			u8 Diff_KS[KSLen];
			for(int j=0;j<KSLen;j++){
				Diff_KS[j]=keyStream_1[j]^keyStream_2[j];
			}
			//calculate backward KSD characteristic
			for(int j=0;j<KSLen;j++){
				And_logic[j]&=Diff_KS[j];
				Or_logic[j]|=Diff_KS[j];
			}
		}
		string BW_KSD_character="";
		for(int i=0;i<KSLen;i++){
			u8 t_and=And_logic[i];
			u8 t_or=Or_logic[i];
			for(int j=0;j<8;j++){
				if((t_and>>j)&0x01){
					BW_KSD_character.append("1");
				}
				else if(!( (t_or>>j)&0x01 )){
					BW_KSD_character.append("0");
				}
				else{
					BW_KSD_character.append("*");
				}
			}
		}
		return BW_KSD_character;
}