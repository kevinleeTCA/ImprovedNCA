/*
	Created by Kevin Lee 2013/6/16
	This is Grain analysis main function
*/

#include "head.h"

void convertHexArray(u32 *arr,u32 Len,u8 *hexArr){
	for(int i=0;i<Len;i++){
		u32 hexArrIdx=i/8;
		u32 hexArrRot=i%8;
		hexArr[hexArrIdx]+=arr[i]<<hexArrRot;
	}
	
}

int main(){
	/*u32 L1[80]={1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1};
	u32 L2[80]={1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1};
	u32 N1[80]={0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1};
	u32 N2[80]={0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1};
	u8 *hexArr=new u8[10]();
	for(int i=0;i<10;i++)
		hexArr[i]=0;
	convertHexArray(N2,80,hexArr);
	
	for(int i=0;i<10;i++){
		printf("%02x",hexArr[i]);
	}
	delete [] hexArr;*/
	//ö������С�ڵ���d��ISD��Ӧ��E-KSDC
	//E_KSDC_enumerate_all_ISD(2,100000);


	//����grain v1 with sampling resistance
	//srand((unsigned)time(NULL));
	//rc4_setup();
	////���ѡ��һ����ʼ״̬L��N
	//for(int D=1;D<10;D++){
	//	/*u32 L[80];
	//	u32 N[80];
	//	for(int j=0;j<80;j++){
	//		L[j]=rc4()%2;
	//		N[j]=rc4()%2;
	//	}*/
	//	u8 state[LEN];
	//	for(int i=0;i<LEN;i++)
	//		state[i]=rc4();
	//	ECRYPT_ctx ctx;
	//	//ȷ���ڲ���139���ص�״̬
	//	grain_v1_sampling_resistance(&ctx,state);
	//	//������Կ��
	//	u8 keyStream_1[3];
	//	ECRYPT_keystream_bytes(&ctx,keyStream_1,3);
	//	for(int i=0;i<3;i++){
	//		printf("%02x ",keyStream_1[i]);
	//	}
	//	printf("\n");
	//}
	//����maple������backward�����KSD�Ĳ�ֲַ�  ���Ԫ�Ľ���
	/*srand((unsigned)time(NULL));
	rc4_setup();
	int d=1;*/
	////LFSR[80]������
	//cout<<"LFSR[80]"<<endl;
	//u32 pos[1]={159};
	//BW_KSD_pos_with_fixed_diff(d,pos,1,100000);
	////LFSR[63]������
	//cout<<"\nLFSR[63]"<<endl;
	//pos[0]=142;
	//BW_KSD_pos_with_fixed_diff(d,pos,1,100000);
	////LFSR[30]������
	//cout<<"\nLFSR[30]"<<endl;
	//pos[0]=109;
	//BW_KSD_pos_with_fixed_diff(d,pos,1,100000);
	////LFSR[10]������
	//cout<<"\nLFSR[10]"<<endl;
	//pos[0]=89;
	//BW_KSD_pos_with_fixed_diff(d,pos,1,100000);

	//d=2;
	////LFSR[79]��LFSR[80]������
	//cout<<"\nLFSR[79]��LFSR[80]"<<endl;
	//u32 pos_2[2]={158,159};
	//BW_KSD_pos_with_fixed_diff(d,pos_2,1,100000);
	////LFSR[77]��LFSR[78]������
	//cout<<"\nLFSR[77]��LFSR[78]"<<endl;
	//u32 pos_3[2]={156,157};
	//BW_KSD_pos_with_fixed_diff(d,pos_3,1,100000);
	////LFSR[65]��LFSR[67]������
	//cout<<"\nLFSR[65]��LFSR[67]"<<endl;
	//u32 pos_4[2]={144,146};
	//BW_KSD_pos_with_fixed_diff(d,pos_4,1,100000);
	////LFSR[3]��LFSR[60]������
	//cout<<"\nLFSR[3]��LFSR[60]"<<endl;
	//u32 pos_5[2]={82,139};
	//BW_KSD_pos_with_fixed_diff(d,pos_5,1,100000);

	/*d=14;
	cout<<"\nLFSR[1],LFSR[2],..LFSR[14]"<<endl;
	u32 pos_14[14]={80,81,82,83,84,85,86,87,88,89,90,91,92,93};
	BW_KSD_pos_with_fixed_diff(d,pos_14,1,100000);
	
	d=27;
	cout<<"\nLFSR[1],LFSR[2],..LFSR[27]"<<endl;
	u32 pos_27[27];
	for(int i=0;i<27;i++){
		pos_27[i]=80+i;
	}
	BW_KSD_pos_with_fixed_diff(d,pos_27,1,100000);
	cout<<"\nLFSR[1],LFSR[2],...,LFSR[18],LFSR[20],...,LFSR[28]"<<endl;
	pos_27[18]=80+27;
	BW_KSD_pos_with_fixed_diff(d,pos_27,1,100000);*/
	//���Ȳ���backward��forward����ȷ�ԣ�Ҳ������������Ƿ�һ��
	//ECRYPT_ctx ctx_1;
	//ctx_1.keysize=80;
	//ctx_1.ivsize=64;
	//u8 rnd_state_1[LEN];		//	���ѡ��һ���ڲ�״̬
	//for(int j=0;j<LEN;j++){
	//	rnd_state_1[j]=rc4();
	//}
	//u8 keyStream_1[KSLen];
	//ECRYPT_grain_state_load(&ctx_1,rnd_state_1);
	//ECRYPT_keystream_bytes(&ctx_1,keyStream_1,KSLen);
	//cout<<"ǰ����Կ��Ϊ��";
	//for(int i=0;i<KSLen;i++){
	//	for(int j=0;j<8;j++){
	//		printf("%d",(keyStream_1[i]>>j)&0x01);
	//	}
	//	printf(" ");
	//	
	//}
	//printf("\n");
	//u8 rnd_state_2[LEN];
	//ECRYPT_grain_state_read(&ctx_1,rnd_state_2);
	//ECRYPT_ctx ctx_2;
	//ctx_2.keysize=80;
	//ctx_2.ivsize=64;
	//u8 keyStream_2[KSLen];
	//ECRYPT_grain_state_load(&ctx_2,rnd_state_2);
	//ECRYPT_keystream_backward_bytes(&ctx_2,keyStream_2,KSLen);
	//cout<<"������Կ��Ϊ��";
	//for(int i=KSLen-1;i>=0;--i){
	//	for(int j=0;j<8;j++){
	//		printf("%d",(keyStream_1[i]>>j)&0x01);
	//	}
	//	printf(" ");
	//}
	//printf("\n");

	//����maple������KSD�Ĳ�ֲַ�  ���Դ�Ľ���
	//srand((unsigned)time(NULL));
	//rc4_setup();
	//int d=1;
	////LFSR[80]������
	//cout<<"LFSR[80]"<<endl;
	//u32 pos[1]={159};
	//KSD_pos_with_fixed_diff(d,pos,1,100000);
	////LFSR[63]������
	//cout<<"\nLFSR[63]"<<endl;
	//pos[0]=142;
	//KSD_pos_with_fixed_diff(d,pos,1,100000);
	////LFSR[30]������
	//cout<<"\nLFSR[30]"<<endl;
	//pos[0]=109;
	//KSD_pos_with_fixed_diff(d,pos,1,100000);
	////LFSR[10]������
	//cout<<"\nLFSR[10]"<<endl;
	//pos[0]=89;
	//KSD_pos_with_fixed_diff(d,pos,1,100000);

	//d=2;
	////LFSR[79]��LFSR[80]������
	//cout<<"\nLFSR[79]��LFSR[80]"<<endl;
	//u32 pos_2[2]={158,159};
	//KSD_pos_with_fixed_diff(d,pos_2,1,100000);
	////LFSR[77]��LFSR[78]������
	//cout<<"\nLFSR[77]��LFSR[78]"<<endl;
	//u32 pos_3[2]={156,157};
	//KSD_pos_with_fixed_diff(d,pos_3,1,100000);
	////LFSR[65]��LFSR[67]������
	//cout<<"\nLFSR[65]��LFSR[67]"<<endl;
	//u32 pos_4[2]={144,146};
	//KSD_pos_with_fixed_diff(d,pos_4,1,100000);
	////LFSR[3]��LFSR[60]������
	//cout<<"\nLFSR[3]��LFSR[60]"<<endl;
	//u32 pos_5[2]={82,139};
	//KSD_pos_with_fixed_diff(d,pos_5,1,100000);

	/*d=14;
	cout<<"\nLFSR[1],LFSR[2],..LFSR[14]"<<endl;
	u32 pos_14[14]={80,81,82,83,84,85,86,87,88,89,90,91,92,93};
	KSD_pos_with_fixed_diff(d,pos_14,1,100000);
	
	d=27;
	cout<<"\nLFSR[1],LFSR[2],..LFSR[27]"<<endl;
	u32 pos_27[27];
	for(int i=0;i<27;i++){
		pos_27[i]=80+i;
	}
	KSD_pos_with_fixed_diff(d,pos_27,1,100000);
	cout<<"\nLFSR[1],LFSR[2],...,LFSR[18],LFSR[20],...,LFSR[28]"<<endl;
	pos_27[18]=80+27;
	KSD_pos_with_fixed_diff(d,pos_27,1,100000);*/
	//Q(n,d,l)�Ĺ��ƣ�Ԥ���㽨��
	//u32 d=1;
	////u64 N_array[4]={16,64,256,1024};
	////u64 sub_N_array[4]={100,200,300,400};
	////u64 N_array[3]={128,1024,1024*16};
	////u64 sub_N_array[4]={100,200,300};
	////u64 N_array[2]={1024*2,1024*128};
	////u64 sub_N_array[2]={100,200};
	//u64 N_array[1]={1024*64};
	//u64 sub_N_array[1]={100};
	//for(int i=1;i<=d;i++){
	//	Q_estimate_precomputation(i,N_array,sub_N_array);
	//}


	//Q(n,d,l)�Ĺ��ơ��������
	//srand((unsigned)time(NULL));
	//rc4_setup();
	//int d=10;
	//u64 N_array[10]={1024*1024*4,1024*1024,1024*1024,1024*1024,1024*1024,1024*1024,1024*1024,1024*1024,1024*1024,1024*1024};
	////u32 num_ISD_arr[1]={100};
	//u64 N_array[10]={1024*64,1024*1024,1024*1024,1024*1024,1024*1024,1024*1024,1024*1024,1024*1024,1024*1024,1024*1024};
	////u32 num_ISD_arr[2]={100,200};
	//u32 num_ISD_arr[10]={100,1000,2000,4000,8000,8000,8000,8000,8000,8000};
	////u32 num_ISD_arr[4]={100,200,200,200};
	////u64 N_array[4]={1024*2,1024*128,1024*1024*2,1024*1024*16};
	////u64 N_array[10]={1024*2,1024*128,1024*1024*2,1024*1024,1024*1024,1024*1024,1024*1024,1024*1024,1024*1024,1024*1024};
	////u64 N_array[10]={128,1024,1024*16,1024*64,1024*256,1024*1024,1024*1024*2,1024*1024,1024*1024,1024*1024};
	////u64 N_array[10]={16,64,256,1024,1024*2,1024*8,1024*16,1024*32,1024*64,1024*128};
	//for(int i=1;i<=d;i++){
	//	cout<<"****************d:"<<i<<"**************"<<endl;
	//	Q_estimate_random_sampling(i,num_ISD_arr[i-1],N_array[i-1],100*i);
	//}

	//ISD proportion�Ĝyԇ   l=32�r
	//���Դ�Ľ���
	//srand((unsigned)time(NULL));
	//rc4_setup();
	//int d=10;
	////u64 N_array[10]={128,1024,1024*16,1024*64,1024*256,1024*1024,1024*1024*2,1024*1024*8,1024*1024*16,1024*1024*32};
	////u64 N_array[10]={16,64,256,1024,1024*2,1024*8,1024*16,1024*32,1024*64,1024*128};
	////u32 num_ISD_arr[10]={100,200,200,200,200,200,200,200,200,200};
	////u64 N_array[4]={1024*2,1024*128,1024*1024*2,1024*1024*16};
	////u32 num_ISD_arr[4]={100,200,200,200};
	////u32 num_ISD_arr[2]={100,200};
	////u64 N_array[2]={1024*64,1024*1024*16};
	////u64 N_array[1]={1024*1024*4};
	////u32 num_ISD_arr[1]={100};
	
	////�����ļ���������2^20������
	////u64 N_array[10]={1024*2,1024*128,1024*1024*2,1024*1024,1024*1024,1024*1024,1024*1024,1024*1024,1024*1024,1024*1024};
	//u64 N_array[10]={1024*64,1024*1024,1024*1024,1024*1024,1024*1024,1024*1024,1024*1024,1024*1024,1024*1024,1024*1024};
	//u64 N_array[10]={1024*1024*4,1024*1024,1024*1024,1024*1024,1024*1024,1024*1024,1024*1024,1024*1024,1024*1024,1024*1024};
	//u32 num_ISD_arr[10]={100,200,200,200,200,200,200,200,200,200};
	/*for(int i=1;i<=d;i++){
		cout<<"****************d:"<<i<<"**************"<<endl;
		ISD_prop_test(i,num_ISD_arr[i-1],N_array[i-1],100*i);
	}*/
	
	//��֤d-near-collision״̬�Ĵ�����  ���ظ�����״̬
	//���Դ�Ľ���
	srand((unsigned)time(NULL));
	rc4_setup();
	u32 N_total=100;
	u32 step=10;
	u32 total=0;
	for(int i=0;i<N_total;i++){//�ظ�100��
		cout<<"************i:"<<i<<"*************"<<endl;
		u32 res=validate_d_near_collision_Lemma_1(43,15,step);
		if(res)
			total++;
	}
	cout<<"�ɹ���Ϊ��"<<setprecision(3)<<(double)total/N_total<<endl;
	//u32 num_col=0;
	//u32 N_total=100;
	// u32 step=1;
	////u32 step=rc4() % KSLen*8;  //���ѡ��һ���ص���С
	////while(step==0)
	////	step=rc4() % KSLen*8;
	//for(int i=0;i<N_total;i++){		//�ظ�100��
	//	//for(u32 step=1;step<KSLen*8;step++){
	//		cout<<"************i:"<<i<<"*************"<<endl;
	//		if(validate_d_near_collision_non_reuse(43,30,step))
	//			num_col++;
	//		cout<<endl;
	//	//}
	//}
	//cout<<"�ɹ���Ϊ��"<<setprecision(3)<<(double)num_col/N_total<<endl;

	//��֤d-near-collision״̬�Ĵ�����  �ظ�����״̬������Ҫ��������С
	//���Դ�Ľ���
	//srand((unsigned)time(NULL));
	//rc4_setup();
	//u32 num_col=0;
	//u32 N_total=100;
	//u32 step=1;
	//for(int i=0;i<N_total;i++){//�ظ�5��
	//	//for(u32 step=1;step<KSLen*8;step++){
	//	cout<<"************i:"<<i<<"*************"<<endl;
	//	num_col+=validate_d_near_collision(43,16,step);
	//	cout<<endl;
	//	//}
	//}
	//cout<<"d-near-collision����ĿΪ��"<<num_col<<" �ɹ���Ϊ��"<<setprecision(3)
	//	<<(double)num_col/N_total<<endl;

	//����������������ȷ��
	//u8 ISD[LEN];
	//u8 S1[LEN];
	//u8 S2[LEN];
	//for(int i=0;i<LEN;i++){
	//	//ISD[i]=0x00;
	//	S1[i]=0x00;
	//	S2[i]=0x00;
	//}
	//S1[0]=0x03;
	//S1[2]=0x0f;
	//u32 HM_val=0;
	//for(int k=0;k<LEN;k++){
	//	ISD[k]=S1[k]^S2[k];
	//	for(int m=0;m<8;m++)
	//		HM_val+=(ISD[k]>>m)&0x01;	
	//}
	//cout<<HM_val<<endl;

	/*
		cal_all_KSD_with_Random_Sampling
		KSLen:8
	*/
	//����N*V(n,d)�Ѿ�����2^l�Ĳ��֣����ǲ���ö����ô��
	//u64 N_array[6]={1024*32,1024*4,1024*2,1024,512,256};
	//u32 test_runs=10;
	//u32 num_ISD_arr[6]={100,1000,2000,4000,8000,16000};
	////���Դ�Ľ���
	//srand((unsigned)time(NULL));
	//rc4_setup();
	//for(int d=1;d<=6;d++){
	//	double ave_q=0.0;
	//	u32 num_ISD=num_ISD_arr[d-1];
	//	cout<<"****************************"<<endl;
	//	for(int i=0;i<test_runs;i++){
	//	//cout<<"-------------i:"<<i<<"----------------"<<endl;
	//		ave_q+=cal_all_KSD_with_Random_Sampling(d,N_array,num_ISD);
	//	}
	//	ave_q=ave_q/test_runs;
	//	cout<<"����(d,l)=("<<d<<","<<KSLen*8<<")�����״̬��ָ���Ϊ"<<num_ISD<<"�����յı���Ϊq:"<<ave_q<<endl;
	//	cout<<"****************************"<<endl;
	//}

	/*
		cal_all_KSD_with_Random_Sampling
		KSLen:7
	*/
	//����N*V(n,d)�Ѿ�����2^l�Ĳ��֣����ǲ���ö����ô��
	//u64 N_array[6]={1024*32,1024*4,1024*2,1024,512,256};
	//u32 test_runs=10;
	//u32 num_ISD_arr[6]={100,1000,2000,4000,8000,16000};
	////���Դ�Ľ���
	//srand((unsigned)time(NULL));
	//rc4_setup();
	//for(int d=1;d<=6;d++){
	//	double ave_q=0.0;
	//	u32 num_ISD=num_ISD_arr[d-1];
	//	cout<<"****************************"<<endl;
	//	for(int i=0;i<test_runs;i++){
	//	//cout<<"-------------i:"<<i<<"----------------"<<endl;
	//		ave_q+=cal_all_KSD_with_Random_Sampling(d,N_array,num_ISD);
	//	}
	//	ave_q=ave_q/test_runs;
	//	cout<<"����(d,l)=("<<d<<","<<KSLen*8<<")�����״̬��ָ���Ϊ"<<num_ISD<<"�����յı���Ϊq:"<<ave_q<<endl;
	//	cout<<"****************************"<<endl;
	//}



	/*
		cal_all_KSD_with_Random_Sampling
		KSLen:7
	*/
	//����N*V(n,d)�Ѿ�����2^l�Ĳ��֣����ǲ���ö����ô��
	//u64 N_array[6]={1024*32,1024*4,1024*2,1024,512,256};
	//u32 test_runs=10;
	//u32 num_ISD_arr[6]={100,1000,2000,4000,8000,16000};
	////���Դ�Ľ���
	//srand((unsigned)time(NULL));
	//rc4_setup();
	//for(int d=1;d<=6;d++){
	//	double ave_q=0.0;
	//	u32 num_ISD=num_ISD_arr[d-1];
	//	cout<<"****************************"<<endl;
	//	for(int i=0;i<test_runs;i++){
	//	//cout<<"-------------i:"<<i<<"----------------"<<endl;
	//		ave_q+=cal_all_KSD_with_Random_Sampling(d,N_array,num_ISD);
	//	}
	//	ave_q=ave_q/test_runs;
	//	cout<<"����(d,l)=("<<d<<","<<KSLen*8<<")�����״̬��ָ���Ϊ"<<num_ISD<<"�����յı���Ϊq:"<<ave_q<<endl;
	//	cout<<"****************************"<<endl;
	//}



	/*
		cal_all_KSD_with_Random_Sampling
		KSLen:6
	*/
	//����N*V(n,d)�Ѿ�����2^l�Ĳ��֣����ǲ���ö����ô��
	//u64 N_array[6]={1024*2,1024*4,1024*2,1024,512,256};
	//u32 test_runs=10;
	//u32 num_ISD_arr[6]={100,1000,2000,4000,8000,16000};
	////���Դ�Ľ���
	//srand((unsigned)time(NULL));
	//rc4_setup();
	//for(int d=1;d<=6;d++){
	//	double ave_q=0.0;
	//	u32 num_ISD=num_ISD_arr[d-1];
	//	cout<<"****************************"<<endl;
	//	for(int i=0;i<test_runs;i++){
	//	//cout<<"-------------i:"<<i<<"----------------"<<endl;
	//		ave_q+=cal_all_KSD_with_Random_Sampling(d,N_array,num_ISD);
	//	}
	//	ave_q=ave_q/test_runs;
	//	cout<<"����(d,l)=("<<d<<","<<KSLen*8<<")�����״̬��ָ���Ϊ"<<num_ISD<<"�����յı���Ϊq:"<<ave_q<<endl;
	//	cout<<"****************************"<<endl;
	//}

	/*
		cal_all_KSD_with_Random_Sampling
		KSLen:5
	*/
	//����N*V(n,d)�Ѿ�����2^l�Ĳ��֣����ǲ���ö����ô��
	//u64 N_array[6]={128,1024,1024*2,1024,512,256};
	//u32 test_runs=10;
	//u32 num_ISD_arr[6]={100,1000,2000,4000,8000,16000};
	////���Դ�Ľ���
	//srand((unsigned)time(NULL));
	//rc4_setup();
	//for(int d=1;d<=6;d++){
	//	double ave_q=0.0;
	//	u32 num_ISD=num_ISD_arr[d-1];
	//	cout<<"****************************"<<endl;
	//	for(int i=0;i<test_runs;i++){
	//	//cout<<"-------------i:"<<i<<"----------------"<<endl;
	//		ave_q+=cal_all_KSD_with_Random_Sampling(d,N_array,num_ISD);
	//	}
	//	ave_q=ave_q/test_runs;
	//	cout<<"����(d,l)=("<<d<<","<<KSLen*8<<")�����״̬��ָ���Ϊ"<<num_ISD<<"�����յı���Ϊq:"<<ave_q<<endl;
	//	cout<<"****************************"<<endl;
	//}
	/*
		cal_all_KSD_with_Random_Sampling
		KSLen:4
	*/
	//u64 N_array[6]={16,64,256,1024,512,256};
	//u32 test_runs=10;
	//u32 num_ISD_arr[6]={100,1000,2000,4000,8000,16000};
	////���Դ�Ľ���
	//srand((unsigned)time(NULL));
	//rc4_setup();
	//for(int d=1;d<=6;d++){
	//	double ave_q=0.0;
	//	u32 num_ISD=num_ISD_arr[d-1];
	//	cout<<"****************************"<<endl;
	//	for(int i=0;i<test_runs;i++){
	//	//cout<<"-------------i:"<<i<<"----------------"<<endl;
	//		ave_q+=cal_all_KSD_with_Random_Sampling(d,N_array,num_ISD);
	//	}
	//	ave_q=ave_q/test_runs;
	//	cout<<"����(d,l)=("<<d<<","<<KSLen*8<<")�����״̬��ָ���Ϊ"<<num_ISD<<"�����յı���Ϊq:"<<ave_q<<endl;
	//	cout<<"****************************"<<endl;
	//}
	
	
	/*string str="abcd";
	cout<<str.substr(0,2)<<endl;*/
	//KSLen:4
	/*u64 N_array[3]={16,64,512};
	cal_all_KSD_construct_table(1,N_array);
	cal_all_KSD_construct_table(2,N_array);
	cal_all_KSD_construct_table(3,N_array);*/

	//KSLen:5
	/*u64 N_array[3]={64,1024};
	cal_all_KSD_construct_table(1,N_array);
	cal_all_KSD_construct_table(2,N_array);*/
	//cal_all_KSD_construct_table(3,N_array);

	//KSLen:6
	/*u64 N_array[1]={2048};
	cal_all_KSD_construct_table(1,N_array);*/

	//srand((unsigned)time(NULL));
	//rc4_setup();	
	//for(int d=1;d<=25;d++){
	//	cout<<"*************************d:"<<d<<"************************"<<endl;
	//	ave_KSD_pos_with_fixed_diff_with_SP(d,300,100000);
	//	//ave_KSD_pos_with_fixed_diff(d,500,100000);
	//	//BW_ave_KSD_pos_with_fixed_diff(d,300,100000);
	//	//BW_ave_KSD_pos_with_fixed_diff_with_SP(d,300,100000);
	//}
	//for(int i=0;i<40;i++){
	//	cout<<(rc4() % 10)+150<<endl;
	//}

	//d \in [7,10]�����䣬��LFSR��NFSR�����������
	//srand((unsigned)time(NULL));
	//rc4_setup();
	//u32 num_ISD_arr[10]={80,1000,1000,1000,1000,1000,1000,1000,1000,1000};
	//for(int d=1;d<=10;d++){
	//	if(d>6){
	//		cout<<"---------------------d:"<<d<<"--------------------------"<<endl;
	//		ave_KSD_pos_with_fixed_diff(d,num_ISD_arr[(d-1)],10000);
	//		ave_KSD_pos_with_fixed_diff(d,num_ISD_arr[(d-1)],100000);
	//		ave_KSD_pos_with_fixed_diff(d,num_ISD_arr[(d-1)],200000);
	//		//ave_KSD_pos_with_fixed_diff(d,100,160000);
	//		//ave_KSD_pos_with_fixed_diff(d,100,400000);
	//	}
	//}
  
	

	//S=10 ȡ10��λ�õ����
	//���Դ�Ľ���
	//srand((unsigned)time(NULL));
	//rc4_setup();
	//u32 num_ISD_arr[10]={10,20,60,100,150,100,60,20,10,1};
	//for(int d=1;d<=10;d++){
	//	cout<<"---------------------d:"<<d<<"--------------------------"<<endl;
	//	ave_KSD_pos_with_fixed_diff(d,num_ISD_arr[(d-1)],10000);
	//	ave_KSD_pos_with_fixed_diff(d,num_ISD_arr[(d-1)],100000);
	//	ave_KSD_pos_with_fixed_diff(d,num_ISD_arr[(d-1)],200000);

	//	//ave_KSD_pos_with_fixed_diff(d,100,160000);
	//	//ave_KSD_pos_with_fixed_diff(d,100,400000);
	//}

	//S=20 ȡ20��λ�õ����
	//���Դ�Ľ���
	//srand((unsigned)time(NULL));
	//rc4_setup();
	//u32 num_ISD_arr[20]={10,100,500,1000,2000,2000,2000,2000,2000,2000,
	//					2000,2000,2000,2000,2000,1000,500,100,10,1};
	//for(int d=1;d<=20;d++){
	//	cout<<"---------------------d:"<<d<<"--------------------------"<<endl;
	//	ave_KSD_pos_with_fixed_diff(d,num_ISD_arr[(d-1)],5000);
	//	ave_KSD_pos_with_fixed_diff(d,num_ISD_arr[(d-1)],10000);
	//	ave_KSD_pos_with_fixed_diff(d,num_ISD_arr[(d-1)],50000);

	//	//ave_KSD_pos_with_fixed_diff(d,100,160000);
	//	//ave_KSD_pos_with_fixed_diff(d,100,400000);
	//}


	//S=30 ȡ30��λ�õ����
	//���Դ�Ľ���
	//srand((unsigned)time(NULL));
	//rc4_setup();
	//u32 num_ISD_arr[30]={10,100,500,1000,2000,2000,2000,2000,2000,2000,
	//					2000,2000,2000,2000,2000,2000,2000,2000,2000,2000,
	//					2000,2000,2000,2000,2000,1000,500,100,10,1};
	//for(int d=1;d<=30;d++){
	//	cout<<"---------------------d:"<<d<<"--------------------------"<<endl;
	//	ave_KSD_pos_with_fixed_diff(d,num_ISD_arr[(d-1)],5000);
	//	ave_KSD_pos_with_fixed_diff(d,num_ISD_arr[(d-1)],10000);
	//	ave_KSD_pos_with_fixed_diff(d,num_ISD_arr[(d-1)],50000);

	//	//ave_KSD_pos_with_fixed_diff(d,100,160000);
	//	//ave_KSD_pos_with_fixed_diff(d,100,400000);
	//}
	getchar();
	return 0;
}



