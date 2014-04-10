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
	//枚举所有小于等于d的ISD对应的E-KSDC
	//E_KSDC_enumerate_all_ISD(2,100000);


	//测试grain v1 with sampling resistance
	//srand((unsigned)time(NULL));
	//rc4_setup();
	////随机选择一个初始状态L和N
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
	//	//确定内部的139比特的状态
	//	grain_v1_sampling_resistance(&ctx,state);
	//	//生成密钥流
	//	u8 keyStream_1[3];
	//	ECRYPT_keystream_bytes(&ctx,keyStream_1,3);
	//	for(int i=0;i<3;i++){
	//		printf("%02x ",keyStream_1[i]);
	//	}
	//	printf("\n");
	//}
	//测试maple给出的backward方向的KSD的差分分布  随机元的建立
	/*srand((unsigned)time(NULL));
	rc4_setup();
	int d=1;*/
	////LFSR[80]引入差分
	//cout<<"LFSR[80]"<<endl;
	//u32 pos[1]={159};
	//BW_KSD_pos_with_fixed_diff(d,pos,1,100000);
	////LFSR[63]引入差分
	//cout<<"\nLFSR[63]"<<endl;
	//pos[0]=142;
	//BW_KSD_pos_with_fixed_diff(d,pos,1,100000);
	////LFSR[30]引入差分
	//cout<<"\nLFSR[30]"<<endl;
	//pos[0]=109;
	//BW_KSD_pos_with_fixed_diff(d,pos,1,100000);
	////LFSR[10]引入差分
	//cout<<"\nLFSR[10]"<<endl;
	//pos[0]=89;
	//BW_KSD_pos_with_fixed_diff(d,pos,1,100000);

	//d=2;
	////LFSR[79]和LFSR[80]引入差分
	//cout<<"\nLFSR[79]和LFSR[80]"<<endl;
	//u32 pos_2[2]={158,159};
	//BW_KSD_pos_with_fixed_diff(d,pos_2,1,100000);
	////LFSR[77]和LFSR[78]引入差分
	//cout<<"\nLFSR[77]和LFSR[78]"<<endl;
	//u32 pos_3[2]={156,157};
	//BW_KSD_pos_with_fixed_diff(d,pos_3,1,100000);
	////LFSR[65]和LFSR[67]引入差分
	//cout<<"\nLFSR[65]和LFSR[67]"<<endl;
	//u32 pos_4[2]={144,146};
	//BW_KSD_pos_with_fixed_diff(d,pos_4,1,100000);
	////LFSR[3]和LFSR[60]引入差分
	//cout<<"\nLFSR[3]和LFSR[60]"<<endl;
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
	//首先测试backward和forward的正确性，也即正向和逆向是否一致
	//ECRYPT_ctx ctx_1;
	//ctx_1.keysize=80;
	//ctx_1.ivsize=64;
	//u8 rnd_state_1[LEN];		//	随机选择一个内部状态
	//for(int j=0;j<LEN;j++){
	//	rnd_state_1[j]=rc4();
	//}
	//u8 keyStream_1[KSLen];
	//ECRYPT_grain_state_load(&ctx_1,rnd_state_1);
	//ECRYPT_keystream_bytes(&ctx_1,keyStream_1,KSLen);
	//cout<<"前向密钥流为：";
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
	//cout<<"后向密钥流为：";
	//for(int i=KSLen-1;i>=0;--i){
	//	for(int j=0;j<8;j++){
	//		printf("%d",(keyStream_1[i]>>j)&0x01);
	//	}
	//	printf(" ");
	//}
	//printf("\n");

	//测试maple给出的KSD的差分分布  随机源的建立
	//srand((unsigned)time(NULL));
	//rc4_setup();
	//int d=1;
	////LFSR[80]引入差分
	//cout<<"LFSR[80]"<<endl;
	//u32 pos[1]={159};
	//KSD_pos_with_fixed_diff(d,pos,1,100000);
	////LFSR[63]引入差分
	//cout<<"\nLFSR[63]"<<endl;
	//pos[0]=142;
	//KSD_pos_with_fixed_diff(d,pos,1,100000);
	////LFSR[30]引入差分
	//cout<<"\nLFSR[30]"<<endl;
	//pos[0]=109;
	//KSD_pos_with_fixed_diff(d,pos,1,100000);
	////LFSR[10]引入差分
	//cout<<"\nLFSR[10]"<<endl;
	//pos[0]=89;
	//KSD_pos_with_fixed_diff(d,pos,1,100000);

	//d=2;
	////LFSR[79]和LFSR[80]引入差分
	//cout<<"\nLFSR[79]和LFSR[80]"<<endl;
	//u32 pos_2[2]={158,159};
	//KSD_pos_with_fixed_diff(d,pos_2,1,100000);
	////LFSR[77]和LFSR[78]引入差分
	//cout<<"\nLFSR[77]和LFSR[78]"<<endl;
	//u32 pos_3[2]={156,157};
	//KSD_pos_with_fixed_diff(d,pos_3,1,100000);
	////LFSR[65]和LFSR[67]引入差分
	//cout<<"\nLFSR[65]和LFSR[67]"<<endl;
	//u32 pos_4[2]={144,146};
	//KSD_pos_with_fixed_diff(d,pos_4,1,100000);
	////LFSR[3]和LFSR[60]引入差分
	//cout<<"\nLFSR[3]和LFSR[60]"<<endl;
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
	//Q(n,d,l)的估计，预计算建表
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


	//Q(n,d,l)的估计。随机抽样
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

	//ISD proportion的測試   l=32時
	//随机源的建立
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
	
	////超过的计算量按照2^20来进行
	////u64 N_array[10]={1024*2,1024*128,1024*1024*2,1024*1024,1024*1024,1024*1024,1024*1024,1024*1024,1024*1024,1024*1024};
	//u64 N_array[10]={1024*64,1024*1024,1024*1024,1024*1024,1024*1024,1024*1024,1024*1024,1024*1024,1024*1024,1024*1024};
	//u64 N_array[10]={1024*1024*4,1024*1024,1024*1024,1024*1024,1024*1024,1024*1024,1024*1024,1024*1024,1024*1024,1024*1024};
	//u32 num_ISD_arr[10]={100,200,200,200,200,200,200,200,200,200};
	/*for(int i=1;i<=d;i++){
		cout<<"****************d:"<<i<<"**************"<<endl;
		ISD_prop_test(i,num_ISD_arr[i-1],N_array[i-1],100*i);
	}*/
	
	//验证d-near-collision状态的存在性  不重复利用状态
	//随机源的建立
	srand((unsigned)time(NULL));
	rc4_setup();
	u32 N_total=100;
	u32 step=10;
	u32 total=0;
	for(int i=0;i<N_total;i++){//重复100次
		cout<<"************i:"<<i<<"*************"<<endl;
		u32 res=validate_d_near_collision_Lemma_1(43,15,step);
		if(res)
			total++;
	}
	cout<<"成功率为："<<setprecision(3)<<(double)total/N_total<<endl;
	//u32 num_col=0;
	//u32 N_total=100;
	// u32 step=1;
	////u32 step=rc4() % KSLen*8;  //随机选择一个重叠大小
	////while(step==0)
	////	step=rc4() % KSLen*8;
	//for(int i=0;i<N_total;i++){		//重复100次
	//	//for(u32 step=1;step<KSLen*8;step++){
	//		cout<<"************i:"<<i<<"*************"<<endl;
	//		if(validate_d_near_collision_non_reuse(43,30,step))
	//			num_col++;
	//		cout<<endl;
	//	//}
	//}
	//cout<<"成功率为："<<setprecision(3)<<(double)num_col/N_total<<endl;

	//验证d-near-collision状态的存在性  重复利用状态，所需要的数据量小
	//随机源的建立
	//srand((unsigned)time(NULL));
	//rc4_setup();
	//u32 num_col=0;
	//u32 N_total=100;
	//u32 step=1;
	//for(int i=0;i<N_total;i++){//重复5次
	//	//for(u32 step=1;step<KSLen*8;step++){
	//	cout<<"************i:"<<i<<"*************"<<endl;
	//	num_col+=validate_d_near_collision(43,16,step);
	//	cout<<endl;
	//	//}
	//}
	//cout<<"d-near-collision的数目为："<<num_col<<" 成功率为："<<setprecision(3)
	//	<<(double)num_col/N_total<<endl;

	//测试求汉明重量的正确性
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
	//对于N*V(n,d)已经超过2^l的部分，我们不用枚举那么多
	//u64 N_array[6]={1024*32,1024*4,1024*2,1024,512,256};
	//u32 test_runs=10;
	//u32 num_ISD_arr[6]={100,1000,2000,4000,8000,16000};
	////随机源的建立
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
	//	cout<<"对于(d,l)=("<<d<<","<<KSLen*8<<")，随机状态差分个数为"<<num_ISD<<"，最终的比例为q:"<<ave_q<<endl;
	//	cout<<"****************************"<<endl;
	//}

	/*
		cal_all_KSD_with_Random_Sampling
		KSLen:7
	*/
	//对于N*V(n,d)已经超过2^l的部分，我们不用枚举那么多
	//u64 N_array[6]={1024*32,1024*4,1024*2,1024,512,256};
	//u32 test_runs=10;
	//u32 num_ISD_arr[6]={100,1000,2000,4000,8000,16000};
	////随机源的建立
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
	//	cout<<"对于(d,l)=("<<d<<","<<KSLen*8<<")，随机状态差分个数为"<<num_ISD<<"，最终的比例为q:"<<ave_q<<endl;
	//	cout<<"****************************"<<endl;
	//}



	/*
		cal_all_KSD_with_Random_Sampling
		KSLen:7
	*/
	//对于N*V(n,d)已经超过2^l的部分，我们不用枚举那么多
	//u64 N_array[6]={1024*32,1024*4,1024*2,1024,512,256};
	//u32 test_runs=10;
	//u32 num_ISD_arr[6]={100,1000,2000,4000,8000,16000};
	////随机源的建立
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
	//	cout<<"对于(d,l)=("<<d<<","<<KSLen*8<<")，随机状态差分个数为"<<num_ISD<<"，最终的比例为q:"<<ave_q<<endl;
	//	cout<<"****************************"<<endl;
	//}



	/*
		cal_all_KSD_with_Random_Sampling
		KSLen:6
	*/
	//对于N*V(n,d)已经超过2^l的部分，我们不用枚举那么多
	//u64 N_array[6]={1024*2,1024*4,1024*2,1024,512,256};
	//u32 test_runs=10;
	//u32 num_ISD_arr[6]={100,1000,2000,4000,8000,16000};
	////随机源的建立
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
	//	cout<<"对于(d,l)=("<<d<<","<<KSLen*8<<")，随机状态差分个数为"<<num_ISD<<"，最终的比例为q:"<<ave_q<<endl;
	//	cout<<"****************************"<<endl;
	//}

	/*
		cal_all_KSD_with_Random_Sampling
		KSLen:5
	*/
	//对于N*V(n,d)已经超过2^l的部分，我们不用枚举那么多
	//u64 N_array[6]={128,1024,1024*2,1024,512,256};
	//u32 test_runs=10;
	//u32 num_ISD_arr[6]={100,1000,2000,4000,8000,16000};
	////随机源的建立
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
	//	cout<<"对于(d,l)=("<<d<<","<<KSLen*8<<")，随机状态差分个数为"<<num_ISD<<"，最终的比例为q:"<<ave_q<<endl;
	//	cout<<"****************************"<<endl;
	//}
	/*
		cal_all_KSD_with_Random_Sampling
		KSLen:4
	*/
	//u64 N_array[6]={16,64,256,1024,512,256};
	//u32 test_runs=10;
	//u32 num_ISD_arr[6]={100,1000,2000,4000,8000,16000};
	////随机源的建立
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
	//	cout<<"对于(d,l)=("<<d<<","<<KSLen*8<<")，随机状态差分个数为"<<num_ISD<<"，最终的比例为q:"<<ave_q<<endl;
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

	//d \in [7,10]的区间，在LFSR和NFSR中随机引入差分
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
  
	

	//S=10 取10个位置的情况
	//随机源的建立
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

	//S=20 取20个位置的情况
	//随机源的建立
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


	//S=30 取30个位置的情况
	//随机源的建立
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



