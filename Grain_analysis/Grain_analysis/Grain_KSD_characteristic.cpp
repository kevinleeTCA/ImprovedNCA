/*
	Created by Kevin Lee 2013/6/16
	Observation of KSD characteristic of Grain v1.
	for each ISD�� observe its positions in KSD with fixed differential value (0/1)
	counter the average number of those positions.
*/


#include "head.h"

//���Զ�������һ�������ISD��Ӧ��KSD characteristic�й̶�λ�õĸ���
/*������
d:�����ֵ����������
num_ISD:���ѡ��������Ϊd�������ֵĸ���
N:ÿһ����ֶ�Ӧ�Ĳ�������������
*/
//����ȥ��������λ���е��ظ�λ��
bool isExist(u32 *pos,int j,u32 curr_val){
	for(int i=0;i<j;i++){
		if(curr_val==pos[i])
			return true;
	}
	return false;
}

void ave_KSD_pos_with_fixed_diff(u32 d,u32 num_ISD,u32 N){
	double average_KSD_fixed_pos_num=0.0;
	double average_HM_val=0.0;
	//map<string,u32> counter;
	for(int D=1;D<=num_ISD;D++){
		//���ѡȡ160bit ״̬�Ĳ��λ�� NFSR��0~79��LFSR��80~159
		u32* pos=new u32[d]();
		for(int j=0;j<d;j++){
			//pos[j]=rc4() % 160;
			//pos[j]=(rc4() % 80)+80;				//ֻ��LFSR��������
			pos[j]=(rc4() % 80);				//ֻ��NFSR��������
			//pos[j]=(rc4() % 40)+80;			//ֻ�oLFSR����벿�������� 80-119
			//pos[j]=(rc4() % 40)+120;			//ֻ��LFSR���Ұ벿�������� 120-159
			while(isExist(pos,j,pos[j]))		//��֤���λ�ò�������ظ�
				//pos[j]=rc4() % 160;
				//pos[j]=(rc4() % 80)+80;			//ֻ��LFSR��������
				pos[j]=(rc4() % 80);			//ֻ��NFSR��������
			//pos[j]=(rc4() % 40)+80;			//ֻ�oLFSR����벿�������� 80-119
			//pos[j]=(rc4() % 40)+120;			//ֻ��LFSR���Ұ벿�������� 120-159
			//pos[j]=(rc4() % 10)+150;			//ֻ��LFSR���Ұ벿�������� 150-159
			//pos[j]=(rc4() % 20)+140;			//ֻ��LFSR���Ұ벿�������� 140-159
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
		//�����ǰISD�Ͷ�Ӧ�ĺ�������
		u32 HM_val=0;
		for(int k=0;k<LEN;k++){
			for(int m=0;m<8;m++)
				HM_val+=(ISD[k]>>m)&0x01;
		}
		average_HM_val+=HM_val;
		/*cout<<"\n-----State Differential-"<<D<<":"<<ends;
		for(int j=0;j<LEN;j++){
				printf("%02x ",ISD[j]);
		}
		average_HM_val+=HM_val;
		cout<<"--HM:"<<HM_val<<"-----"<<endl;*/
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
	average_HM_val=(double)average_HM_val/num_ISD;
		cout<<"Average Hamming weight:"<<setprecision(3)<<average_HM_val<<"  The average fixed pos(d,l,N):("
			<<d<<","<<KSLen<<","<<N<<") is "<<setprecision(3)<<average_KSD_fixed_pos_num<<endl;
}


//���Զ�������һ��ָ����ISD��Ӧ��KSD characteristic�й̶�λ�õĸ������Լ�0,1,*λ�õķֲ�
/*������
d:�����ֵ����������,Ҳ��������pos�ĳ���
pos:������λ�õ��±�����
N:ÿһ����ֶ�Ӧ�Ĳ�������������
*/
void KSD_pos_with_fixed_diff(u32 d,u32 *pos,u32 N){
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
	//�����ǰISD
	/*	cout<<"\n-------------State Differential-"<<D<<":"<<ends;
	for(int j=0;j<LEN;j++){
			printf("%x ",ISD[j]);
	}
	cout<<"-----------"<<endl;*/
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
	cout<<"E-KSDC:"<<KSD_character;
	cout<<"\nNumber of fixed positions��"<<KW_KSD_CH;
	cout<<"\nAbsolute active positions(Y)��{";
	vector<int>::iterator beg=act_pos.begin();
	vector<int>::iterator end=act_pos.end();
	for(;beg!=end;beg++){
		cout<<*beg<<",";
	}
	cout<<"}\nNon-active positions(N)��{";
	beg=non_act_pos.begin();
	end=non_act_pos.end();
	for(;beg!=end;beg++){
		cout<<*beg<<",";
	}
	cout<<"}\nPending positions(P)��{";
	beg=poss_act_pos.begin();
	end=poss_act_pos.end();
	for(;beg!=end;beg++){
		cout<<*beg<<",";
	}
	cout<<"}"<<endl;
}


//�������һ����ֶ�Ӧ�����KSD��characteristic ����ֵʵ�飩
/*������
d:�����ֵ����������,Ҳ��������pos�ĳ���
pos:������λ�õ��±�����
N:ÿһ����ֶ�Ӧ�Ĳ�������������

���ض�Ӧ��KSD characteristic
*/
string KSD_sequence_with_fixed_diff(u32 d,u32 *pos,u32 N){
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
	//�����ǰISD
	/*	cout<<"\n-------------State Differential-"<<D<<":"<<ends;
	for(int j=0;j<LEN;j++){
			printf("%x ",ISD[j]);
	}
	cout<<"-----------"<<endl;*/
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
		//����KSD characteristic
		for(int j=0;j<KSLen;j++){
			And_logic[j]&=Diff_KS[j];
			Or_logic[j]|=Diff_KS[j];
		}
	}
	//���㵱ǰ�����ֶ�Ӧ��KSD��characteristic  
	//And�߼�ȷ��ȫ1��λ��  Or�߼�ȷ��ȫ0��λ��  ʣ�µľ��ǲ�ȷ����λ��
	//�ֱ��¼Active  non-active��possible activeλ�õ��±�
	//vector<int> act_pos;
	//vector<int> non_act_pos;
	//vector<int> poss_act_pos;
	string KSD_character="";
	//int KW_KSD_CH=0;
	for(int i=0;i<KSLen;i++){
		u8 t_and=And_logic[i];
		u8 t_or=Or_logic[i];
		for(int j=0;j<8;j++){
			if((t_and>>j)&0x01){
				//KW_KSD_CH++;
				KSD_character.append("1");
				//act_pos.push_back(i*8+j+1);
			}
			else if(!( (t_or>>j)&0x01 )){
				//KW_KSD_CH++;
				KSD_character.append("0");
				//non_act_pos.push_back(i*8+j+1);
			}
			else{
				KSD_character.append("*");
				//poss_act_pos.push_back(i*8+j+1);
			}
		}
	}
	return KSD_character;
	/*cout<<"E-KSDC:"<<KSD_character;
	cout<<"\nNumber of fixed positions��"<<KW_KSD_CH;
	cout<<"\nAbsolute active positions(Y)��{";
	vector<int>::iterator beg=act_pos.begin();
	vector<int>::iterator end=act_pos.end();
	for(;beg!=end;beg++){
		cout<<*beg<<",";
	}
	cout<<"}\nNon-active positions(N)��{";
	beg=non_act_pos.begin();
	end=non_act_pos.end();
	for(;beg!=end;beg++){
		cout<<*beg<<",";
	}
	cout<<"}\nPending positions(P)��{";
	beg=poss_act_pos.begin();
	end=poss_act_pos.end();
	for(;beg!=end;beg++){
		cout<<*beg<<",";
	}
	cout<<"}"<<endl;*/

}




/*
ö�����������ֺ�������С�ڵ���d��ISD����������E_KSDC��ֵ���洢���ļ���
������
d:�����ֵ����������
N:ÿһ����ֶ�Ӧ�Ĳ�������������
*/
void E_KSDC_enumerate_all_ISD(u32 d,u64 N){
	//���Դ�Ľ���
	srand((unsigned)time(NULL));
	rc4_setup();
	//����Ŀ¼��������������Զ�����Ŀ¼
	cout<<"----------------------d:"<<d<<"--------------------"<<endl;
	string head_DIR="E:\\�о����γ�\\���۰�\\Cryptalysis of Grain v1\\ISD��Ӧ��ֲַ�[Y,N,P]-��ֵʵ��\\";
	string part="LFSR_(d,l)_(";
	//make_DIR(curr_DIR);
	for(int i=1;i<=d;i++){
		cout<<"��ʼ���������ֺ�������Ϊ:"<<i<<"�����."<<endl;
		string fileName=head_DIR+part+int_2_string(i)+","+int_2_string(KSLen)+").txt";
		//E_KSDC_enu_for_search(LEN*8,i,N,fileName);		//������160����״̬�������֡�
		E_KSDC_enu_for_search(80,i,N,fileName);			//����ֻ��LFSR��80����������
		cout<<"�����ֺ�������Ϊ:"<<i<<"������Ѿ��������.\n\n"<<endl;
	}
}

void E_KSDC_enu_for_search(u32 n,u32 k,u64 N,string fileName){
	//����һ���������������������Ľ���
	u64 counter=0;
	//Ԥ�ȴ洢һ�����Ƶ��ܵļ�����
	u64 t_Sum[5]={160,12720,669920,26294360,820384032};
	//��ʼ���������
	u32 *v=new u32[k+1]();
	for(int i=0;i<k;i++){
		v[i]=i+1;
	}
	v[k]=n+1;
	//�ó�ʼ��������������Գ�ʼ����Ͻ��в���
	E_KSDC_calculation(k,v,N,fileName);
	//���C(n,k)��������ϣ�Ϊÿ������趨����״̬��֣���ִ��grain�õ�������
	while(E_KSDC_enu_for_search_sub(k,v,N,fileName)){
		if((++counter) % 30000 ==0){
			cout<<"proceed "<<setprecision(3)<<(double)counter*100/t_Sum[k-1]<<"%..."<<endl;
		}
	}
}

bool E_KSDC_enu_for_search_sub(u32 k,u32 *v,u64 N,string fileName){
	for(int i=k-1;i>=0;i--){
		if(v[i]+1!=v[i+1]){
			v[i]++;
			//���ݵ�ǰ��Ͻ��в���
			for(int j=i+1;j<k;j++)
				v[j]=v[j-1]+1;
			E_KSDC_calculation(k,v,N,fileName);
			return true;
		}
	}
	return false;
}

void E_KSDC_calculation(u32 k,u32 *v,u64 N,string fileName){
	u32 KSD_fixed_pos_num=0;
	//��ʼ�� ������Ϊȫ0 �������ǰ���v�Ķ�Ӧ������״̬���
	u8 *ISD=new u8[LEN]();
	for(int m=0;m<k;m++){
		//cout<<v[m]<<" "<<ends;
		u32 p=posIdx(v[m]-1);
		u32 r=rotateIdx(v[m]-1);
		//ISD[p]=ISD[p]^(1<<r);  //��ȫ��160����������
		ISD[10+p]=ISD[10+p]^(1<<r);    //ֻ��LFSR��������
	}
	//����KSD characteristic
	u8 And_logic[KSLen];   //����ȷ�������ȫ1��λ��
	u8 Or_logic[KSLen];		//����ȷ�������ȫ0��λ��
	//��ʼ�� and �� or logic
	for(int i=0;i<KSLen;i++){
		And_logic[i]=255;
		Or_logic[i]=0;
	}
	//���ѡ��N��״̬
	for(int i=0;i<N;i++){
		u8 rnd_state_1[LEN];
		for(int j=0;j<LEN;j++){
			rnd_state_1[j]=rc4();
		}
		//���ݲ��λ�ã��õ���һ��״̬rud_state_2
		u8 rnd_state_2[LEN];
		for(int j=0;j<LEN;j++){
			rnd_state_2[j]=rnd_state_1[j]^ISD[j];
		}
		//�ֱ����Grain�� ���l������Կ��
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
		//����KSD characteristic
		for(int j=0;j<KSLen;j++){
			And_logic[j]&=Diff_KS[j];
			Or_logic[j]|=Diff_KS[j];
		}
	}
	//���㵱ǰ�����ֶ�Ӧ��KSD��characteristic  
	//And�߼�ȷ��ȫ1��λ��  Or�߼�ȷ��ȫ0��λ��  ʣ�µľ��ǲ�ȷ����λ��
	string KSD_character="";
	for(int i=0;i<KSLen;i++){
		u8 t_and=And_logic[i];
		u8 t_or=Or_logic[i];
		for(int j=0;j<8;j++){
			if((t_and>>j)&0x01){
				KSD_fixed_pos_num++;
				KSD_character.append("1");
			}
			else if(!( (t_or>>j)&0x01 )){
				KSD_fixed_pos_num++;
				KSD_character.append("0");
			}
			else
				KSD_character.append("*");
		}
	}
	//�������Ӧ���ļ���
	ofstream outfile;
	outfile.open(fileName.c_str(),ofstream::app);
	if(outfile){
		outfile<<"[";
		for(int m=0;m<k;m++){
			if(m!=k-1)
				outfile<<v[m]<<",";
			else
				outfile<<v[m]<<"]";
		}
		outfile<<"    "<<KSD_fixed_pos_num<<"    "<<KSD_character<<endl;
	}
	outfile.close();
}