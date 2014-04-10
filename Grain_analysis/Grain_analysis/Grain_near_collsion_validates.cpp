/*
	Created by Kevin Lee 2013/6/16
	������֤ͨ��overlapping�ķ�ʽѡȡ����Կ������Ӧ���ڲ�״̬Ӧ���Ǵ���d-near-collision�ġ�
*/


#include "head.h"
/*
	һ��d��ֵȷ���ˣ���Ӧ��V(n,d)��ֵҲ��ȷ���ˣ����ǾͿ���ȷ��
	����Ҫ�Ĳ��|H|=2^{n/2}/sqrt(V(n,d))
	��������Ҫ�Ĳ�ֵ���Ŀ�����������Ҫ����Կ������������
	���軬������Ϊ1����ô����|H|���ǾͿ����������Ҫ��D
	�Ӷ���֤������ô����Կ��������Ӧ���ڲ�״̬֮���Ƿ����
	d-near-collision
	�����б�
	d:ISD�����������
	D:�������������bits��
	step:�������� ������1-KSlen*8֮��,���_���������ص����ص�
*/
u32 validate_d_near_collision(u32 d,u64 D,u32 step){
	u32 res=0;
	//�������������ļ�
	//string curr_DIR="E:\\�о����γ�\\���۰�\\Cryptalysis of Grain v1\\��֤d-near-collision�Ĵ�����\\validate_d_near_collision\\";
	string curr_DIR="D:\\kevin_grain\\��֤d-near-collision�Ĵ�����\\validate_d_near_collision\\";
	string part="(d,D)_(";
	curr_DIR=curr_DIR+part+int_2_string(d)+",2^"+int_2_string(D)+")_step_"
		+int_2_string(step)+".txt";
	string fileName=curr_DIR;
	ofstream outfile;
	outfile.open(fileName.c_str(),ofstream::app);
	//���ѡ��һ����ʼ״̬
	u8 rnd_state[LEN];
	for(int j=0;j<LEN;j++){
		rnd_state[j]=rc4();
	}
	//�������ʼ״̬���뵽Grain��
	ECRYPT_ctx ctx;
	ctx.keysize=80;
	ctx.ivsize=64;
	ECRYPT_grain_state_load(&ctx,rnd_state);
	//����H bits����������Ӧ���ڲ�״̬���ϡ�
	u64 H=(u64)pow(2,(double)D);
	State_array *SA=new State_array[H]();
	u64 clock_t=0;
	for(u64 i=0;i<H;i++){
		//��¼ÿһ�Ķ�Ӧ���ڲ�״̬
		SA[i].clock_t=clock_t;
		ECRYPT_grain_state_read(&ctx,SA[i].STATE);
		for(u32 j=0;j<step;j++){
			ENCRYPT_grain_keystream(&ctx);
			clock_t++;
		}
	}
	//���ڲ�״̬�����У�����d-near-collision��״̬,ö�����е�C(D,2)��״̬��֣��ж����Ƿ�Ϊd-near-collision
	/*ECRYPT_grain_state_load(&ctx,SA[D-1].STATE);
	for(u64 i=0;i<D-1;i++){
		ENCRYPT_grain_keystream_backward(&ctx);
	}
	u8 rnd_state_bw[LEN];
	ECRYPT_grain_state_read(&ctx,rnd_state_bw);
	cout<<"�˻�����״̬Ϊ��";
	for(int j=0;j<LEN;j++){
		printf("%02x",rnd_state_bw[j]);
	}
	cout<<endl;*/
	//for(u64 i=0;i<D;i++){
	//	cout<<"clock:"<<SA[i].clock_t<<endl;
	//	cout<<"state:";
	//	for(int j=0;j<20;j++){
	//		printf("%02x",SA[i].STATE[j]);
	//	}
	//	cout<<endl<<endl;
	//}
	for(u64 i=0;i<H-1;i++){
		if(i % 10000==0){
			cout<<"proceed "<<setprecision(3)<<(double)i*100/H<<"%..."<<endl;
		}
		for(u64 j=i+1;j<H;j++){
			u8 ISD[LEN];
			u32 HM_val=0;
			//�������ֵĺ�������  ��������ֻ������LFSR�������֣���������ֻ����LFSR״̬�ĺ�������
			/*for(int k=0;k<LEN;k++){
				ISD[k]=(SA[i].STATE[k])^(SA[j].STATE[k]);
				if(k>=10){
					for(int m=0;m<8;m++)
					HM_val+=(ISD[k]>>m)&0x01;
						if(HM_val>d) break;
				}
			}*/
			//�������ֵĺ������� ��LFSR��NFSR�����������
			for(int k=0;k<LEN;k++){
				ISD[k]=(SA[i].STATE[k])^(SA[j].STATE[k]);
				for(int m=0;m<8;m++)
					HM_val+=(ISD[k]>>m)&0x01;
						if(HM_val>d) break;
			}
			if(HM_val<=d){
				//����ʼ��̬���
				outfile<<"״̬����d-near-collision����ײ.��������Ϊ��"<<HM_val<<endl;
				outfile<<"������ײ����ʼ��״̬Ϊ��"<<endl;
				for(int k=0;k<LEN;k++){
					outfile<<setw(2)<<hex<<(u32)rnd_state[k];
				}
				outfile<<endl;
				//������d-near-collision��Hamming weight
				outfile<<"����d-near-collision��״̬��֣�"<<endl;
				outfile<<"NFSR:";
				for(int k=0;k<10;k++){
					outfile<<setw(2)<<hex<<(u32)ISD[k];
				}
				outfile<<endl;
				outfile<<"LFSR:";
				for(int k=10;k<LEN;k++){
					outfile<<setw(2)<<hex<<(u32)ISD[k];
				}
				outfile<<endl;
				outfile<<"����d-near-collision��ʱ�̷ֱ�Ϊ��"<<dec<<SA[i].clock_t<<"  "<<dec<<SA[j].clock_t<<endl;
				outfile<<endl;
				res++;
			}
		}
	}
	//cout<<"No d-near-collision found."<<endl;
	outfile.close();
	delete [] SA;
	return res;
}


/*
 A��B�������ϵ������|A|*|B|>2^n/V(n,d)
*/

u32 validate_d_near_collision_Lemma_1(u32 d,u64 D,u32 step){
	u32 res=0;
	//�������������ļ�
	//string curr_DIR="E:\\�о����γ�\\���۰�\\Cryptalysis of Grain v1\\��֤d-near-collision�Ĵ�����\\validate_d_near_collision_Lemma_1\\";
	string curr_DIR="D:\\kevin_grain\\��֤d-near-collision�Ĵ�����\\validate_d_near_collision_Lemma_1\\";
	string part="(d,D)_(";
	curr_DIR=curr_DIR+part+int_2_string(d)+",2^"+int_2_string(D)+")_step_"
		+int_2_string(step)+".txt";
	string fileName=curr_DIR;
	ofstream outfile;
	outfile.open(fileName.c_str(),ofstream::app);
	//���ѡ��������ʼ״̬����load
	
	u8 rnd_state1[LEN];
	for(int j=0;j<LEN;j++){
		rnd_state1[j]=rc4();
	}
	u8 rnd_state2[LEN];
	for(int j=0;j<LEN;j++){
		rnd_state2[j]=rc4();
	}
	//����������ʼ״̬���뵽Grain��
	ECRYPT_ctx ctx1;
	ctx1.keysize=80;
	ctx1.ivsize=64;
	ECRYPT_grain_state_load(&ctx1,rnd_state1);

	ECRYPT_ctx ctx2;
	ctx2.keysize=80;
	ctx2.ivsize=64;
	ECRYPT_grain_state_load(&ctx2,rnd_state2);
	//����H bits����������Ӧ���ڲ�״̬����A��B��
	u64 H=(u64)pow(2,(double)D);
	State_array *SA1=new State_array[H]();
	State_array *SA2=new State_array[H]();
	u64 clock_t=0;
	for(u64 i=0;i<H;i++){
		//��¼ÿһ�Ķ�Ӧ���ڲ�״̬
		SA1[i].clock_t=clock_t;
		SA2[i].clock_t=clock_t;
		ECRYPT_grain_state_read(&ctx1,SA1[i].STATE);
		ECRYPT_grain_state_read(&ctx2,SA2[i].STATE);
		for(u32 j=0;j<step;j++){
			ENCRYPT_grain_keystream(&ctx1);
			ENCRYPT_grain_keystream(&ctx2);
			clock_t++;
		}
	}

	for(u64 i=0;i<H-1;i++){
		/*if(i % 10000==0){
			cout<<"proceed "<<setprecision(3)<<(double)i*100/H<<"%..."<<endl;
		}*/
		for(u64 j=0;j<H-1;j++){
			u8 ISD[LEN];
			u32 HM_val=0;
			//�������ֵĺ������� ��LFSR��NFSR�����������
			for(int k=0;k<LEN;k++){
				ISD[k]=(SA1[i].STATE[k])^(SA2[j].STATE[k]);
				for(int m=0;m<8;m++)
					HM_val+=(ISD[k]>>m)&0x01;
						if(HM_val>d) break;
			}
			if(HM_val<=d){
				//����ʼ��̬���
				outfile<<"״̬����d-near-collision����ײ.��������Ϊ��"<<HM_val<<endl;
				outfile<<"������ײ����ʼ��״̬ΪS_A��";
				for(int k=0;k<LEN;k++){
					outfile<<setw(2)<<hex<<(u32)rnd_state1[k];
				}
				outfile<<"  S_B��";
				for(int k=0;k<LEN;k++){
					outfile<<setw(2)<<hex<<(u32)rnd_state2[k];
				}
				outfile<<endl;
				//������d-near-collision��Hamming weight
				outfile<<"����d-near-collision��״̬��֣�"<<endl;
				outfile<<"NFSR:";
				for(int k=0;k<10;k++){
					outfile<<setw(2)<<hex<<(u32)ISD[k];
				}
				outfile<<endl;
				outfile<<"LFSR:";
				for(int k=10;k<LEN;k++){
					outfile<<setw(2)<<hex<<(u32)ISD[k];
				}
				outfile<<endl;
				outfile<<"����d-near-collision��ʱ�̷ֱ�Ϊ t_A��"<<dec<<SA1[i].clock_t<<"  t_B"<<dec<<SA2[j].clock_t<<endl;
				outfile<<endl;
				res++;

			}
		}
	}
	outfile.close();
	delete [] SA1;
	delete [] SA2;
	return res;
}

/*
	���ظ�����ͬһʱ�̵�״̬��������״̬���õ��Ĳ������Ϊ�ж�
	���մ���˳������״̬�Լ���Ӧ�Ĳ�֡�
	����жϲ���Ƿ�Ϊd-near-collision��
	ֱ���жϵ�����������|H|>= 2^{n/2}/sqrt(V(n,d))
	�����б�
	d:ISD�����������
	H:����Ĳ�ֵĸ��� 
	step:�������� ������1-KSlen*8֮��,���_���������ص����ص�
*/
bool validate_d_near_collision_non_reuse(u32 d,u64 H,u32 step){
	//�������������ļ�
	string curr_DIR="E:\\�о����γ�\\���۰�\\Cryptalysis of Grain v1\\��֤d-near-collision�Ĵ�����\\";
	string part="(d,D)_(";
	curr_DIR=curr_DIR+part+int_2_string(d)+",2^"+int_2_string(H)+")_step_"
		+int_2_string(step)+".txt";
	string fileName=curr_DIR;
	ofstream outfile;
	outfile.open(fileName.c_str(),ofstream::app);
	//���ѡ��һ����ʼ״̬
	u8 S1[LEN];
	for(int j=0;j<LEN;j++){
		S1[j]=rc4();
	}
	//�������ʼ״̬���뵽Grain��
	ECRYPT_ctx ctx_1;
	ctx_1.keysize=80;
	ctx_1.ivsize=64;
	ECRYPT_grain_state_load(&ctx_1,S1);
	//��ctx_1����step��clock֮��õ���״̬��Ϊctx_2��״̬
	for(u32 i=0;i<step;i++)
		ENCRYPT_grain_keystream(&ctx_1);
	u8 S2[LEN];
	ECRYPT_grain_state_read(&ctx_1,S2);
	//��ԭctx_1�ĳ�̬
	ECRYPT_grain_state_load(&ctx_1,S1);
	//��ʼ��ctx_2
	ECRYPT_ctx ctx_2;
	ctx_2.keysize=80;
	ctx_2.ivsize=64;
	ECRYPT_grain_state_load(&ctx_2,S2);
	//Ȼ���𲽲���d-near-collision��״̬
	u64 clock_t=0;
	u64 D=(u64)pow(2,(double)H);
	for(u64 i=0;i<D;i++){
		if(i % 10000000==0){
			cout<<"proceed "<<setprecision(3)<<(double)i*100/D<<"%..."<<endl;
		}
		u8 curr_S1[LEN];
		u8 curr_S2[LEN];
		ECRYPT_grain_state_read(&ctx_1,curr_S1);
		ECRYPT_grain_state_read(&ctx_2,curr_S2);
		//���㵱ǰ״̬�Ĳ��
		u8 ISD[LEN];
		u32 HM_val=0;
		//��������ֻ������LFSR�������֣���������ֻ����LFSR״̬�ĺ�������
		/*for(int j=0;j<LEN;j++){
			ISD[j]=curr_S1[j]^curr_S2[j];
			if(j>=10){
				for(int m=0;m<8;m++)
					HM_val+=(ISD[j]>>m)&0x01;
				if(HM_val>d) break;
			}
		}*/
		//�������ֵĺ������� ��LFSR��NFSR�����������
		for(int j=0;j<LEN;j++){
			ISD[j]=curr_S1[j]^curr_S2[j];
			for(int m=0;m<8;m++)
				HM_val+=(ISD[j]>>m)&0x01;
			if(HM_val>d) break;
		}
		//�жϵ�ǰ״̬����Ƿ���d-near-collision��
		if(HM_val<=d){
			if(outfile){
				outfile<<"LFSR�ϵ�״̬����d-near-collision����ײ.��������Ϊ��"<<HM_val<<endl;
						//����ʼ��̬���
				outfile<<"������ײ����ʼ��״̬ΪS1��";
				for(int j=0;j<LEN;j++){
					outfile<<setw(2)<<hex<<(u32)S1[j];
				}
				outfile<<endl;
				outfile<<"������ײ����ʼ��״̬ΪS2��";
				for(int j=0;j<LEN;j++){
					outfile<<setw(2)<<hex<<(u32)S2[j];
				}
				outfile<<endl;
				//������d-near-collision��Hamming weight
				outfile<<"����d-near-collision��״̬��֣�";
				outfile<<"NFSR:";
				for(int k=0;k<10;k++){
					outfile<<setw(2)<<hex<<(u32)ISD[k];
				}
				outfile<<endl;
				outfile<<"LFSR:";
				for(int k=10;k<LEN;k++){
					outfile<<setw(2)<<hex<<(u32)ISD[k];
				}
				outfile<<endl;
				outfile<<"����d-near-collision��ʱ��Ϊ��"<<clock_t<<"��StepΪ"<<step<<endl;
			}
			return true;
		}	
		//������Ǽ�������
		clock_t++;
		ENCRYPT_grain_keystream(&ctx_1);
		ENCRYPT_grain_keystream(&ctx_2);
	}
	outfile.close();
	return false;
}