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
	//re-check the E-KSDC calculation
	//srand((unsigned)time(NULL));
	//rc4_setup();
	//u32 pos[5]={93,106,68,27,67};
	//E_KSDC_fixed_pos_with_given_ISD(5,pos);


	//test the speed of E-KSDC calculation
	//srand((unsigned)time(NULL));
	//rc4_setup();
	////randomly induce d differnt positions to ISD
	//u32 d=rc4() % 30+1;  //  consider hamming weight lower than 30
	//u32 *pos=new u32[d]();
	//cout<<"ISD differential index:{";
	//for(int i=0;i<d;i++){
	//	pos[i]=rc4() % 160;
	//	cout<<pos[i]<<",";
	//}
	//cout<<"}"<<endl;
	//u8 ISD[LEN];
	//for(int j=0;j<LEN;j++){
	//	ISD[j]=0;
	//}
	//for(int j=0;j<d;j++){
	//	u32 p=posIdx(pos[j]);
	//	u32 r=rotateIdx(pos[j]);
	//	ISD[p]=ISD[p]^(1<<r);
	//}
	//ECRYPT_ctx ctx;
	//ctx.keysize=80;
	//ctx.ivsize=64;
	//ECRYPT_grain_state_load(&ctx,ISD);
	//u8 E_KSDC_Array[KSLen*8];
	////start testing the speed
	//clock_t start_R, finish_R;
	//double duration_R,speed_R;
	//start_R=clock();
	//for(int j=0;j<KSLen*8;j++){
	//	ENCRYPT_grain_E_KSDC(&ctx);
	//}
	//finish_R=clock();
	//duration_R=((double)finish_R-start_R)/CLOCKS_PER_SEC;
	////2.83 GHz CPU frequence
	//speed_R=duration_R*2.83*1000*1000*1000/((double)KSLen*8);
	//printf("time：%4.4f sec\n"
	//	"The encryption speed is %3.4f cycles/bit \n"
	//	,duration_R,speed_R);

	//delete [] pos;
	//ECRYPT_ctx_reduce* ctx_reduce=new ECRYPT_ctx_reduce;
	//u8* key_R=new u8[4]();
	//u8* IV_R=new u8[3]();
	//for(int i=0;i<4;i++){
	//	key_R[i]=i;
	//}
	//for(int i=0;i<3;i++){
	//	IV_R[i]=0;
	//}
	//ECRYPT_keysetup_reduce(ctx_reduce,key_R,32,24);
	//ECRYPT_ivsetup_reduce(ctx_reduce,IV_R);
	//u8* keyStream_R=new u8[KSLen_Reduced];
	//clock_t start_R, finish_R;
	//double duration_R,speed_R;
	//start_R=clock();
	//ECRYPT_keystream_bytes_reduce(ctx_reduce,keyStream_R,KSLen_Reduced);
	//finish_R=clock();
	//duration_R=((double)finish_R-start_R)/CLOCKS_PER_SEC;
	////2.83 GHz CPU frequence
	//speed_R=duration_R*2.83*1000*1000*1000/((double)KSLen_Reduced*8);
	//printf("time：%4.4f sec\n"
	//	"The encryption speed is %3.4f cycles/bit \n"
	//	,duration_R,speed_R);
	
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

	//test the average number of fixed positions in BW-E-KSDC
	/*srand((unsigned)time(NULL));
	rc4_setup();
	average_fixed_pos_BW_E_KSDC(10,50000);*/
    
	
	//Test the correctness of calculation BW-E-KSDC
	//compared with numerical results
	//srand((unsigned)time(NULL));
	//rc4_setup();
	//test 1000 times
	//u32 counter=0;
	//for(int D=0;D<1000;D++){
	//	u32 d=rc4() % 25+1;  //  consider hamming weight lower than 25
	//	u32 N=100000;		// sampling size of numerical experiment
	//	u32 *pos=new u32[d]();
	//	randomly induce differences
	//	for(int i=0;i<d;i++){
	//		pos[i]=rc4() % 160;
	//	}
	//	if((++counter) % 250 ==0){
	//		cout<<"proceed "<<setprecision(3)<<(double)counter*100/1000<<"%..."<<endl;
	//	}

	//	string BW_KSDC_Gen_Alo="";
	//	string BW_KSDC_num_exp="";
	//	BW_KSDC_Gen_Alo=BW_E_KSDC_seq_with_given_ISD(d,pos);
	//	BW_KSDC_num_exp=BW_KSD_seq_with_fixed_diff(d,pos,N);
	//	if(BW_KSDC_Gen_Alo.compare(BW_KSDC_num_exp)!=0){ //record the exceptional cases, i.e., inconsistent cases
	//		cout<<"ISD differential index:{";
	//		for(int i=0;i<d;i++){
	//			cout<<pos[i]<<",";
	//		}
	//		cout<<"}"<<endl;
	//		cout<<"BW-E-KSDC (GA):"<<BW_KSDC_Gen_Alo<<endl;
	//		cout<<"BW-E-KSDC (NE):"<<BW_KSDC_num_exp<<endl;
	//		vector<int> act_pos;
	//		vector<int> non_act_pos;
	//		vector<int> pending_pos;

	//		vector<int> act_pos_NE;
	//		vector<int> non_act_pos_NE;
	//		vector<int> pending_pos_NE;
	//		u32 KSDC_gen_alo_fixed_num=0;
	//		u32 KSDC_num_exp_fixed_num=0;
	//		for(int j=0;j<KSLen*8;j++){
	//			if(BW_KSDC_Gen_Alo.at(j)=='0'){
	//				KSDC_gen_alo_fixed_num++;
	//				non_act_pos.push_back(j+1);
	//			}else if(BW_KSDC_Gen_Alo.at(j)=='1'){
	//				KSDC_gen_alo_fixed_num++;
	//				act_pos.push_back(j+1);
	//			}else
	//				pending_pos.push_back(j+1);


	//			if(BW_KSDC_num_exp.at(j)=='0'){
	//				KSDC_num_exp_fixed_num++;
	//				non_act_pos_NE.push_back(j+1);
	//			}else if(BW_KSDC_num_exp.at(j)=='1'){
	//				KSDC_num_exp_fixed_num++;
	//				act_pos_NE.push_back(j+1);
	//			}else
	//				pending_pos_NE.push_back(j+1);


	//		}
	//		cout<<"Number of fixed positions (GA)："<<KSDC_gen_alo_fixed_num;
	//		cout<<"\nNumber of fixed positions (NE)："<<KSDC_num_exp_fixed_num;
	//		cout<<"\nAbsolute active positions(Y) (GA):{";
	//		vector<int>::iterator beg=act_pos.begin();
	//		vector<int>::iterator end=act_pos.end();
	//		for(;beg!=end;beg++){
	//			cout<<*beg<<",";
	//		}
	//		cout<<"}\nAbsolute active positions(Y) (NE):{";
	//		beg=act_pos_NE.begin();
	//		end=act_pos_NE.end();
	//		for(;beg!=end;beg++){
	//			cout<<*beg<<",";
	//		}
	//
	//		cout<<"}\nNon-active positions(N) (GA)：{";
	//		beg=non_act_pos.begin();
	//		end=non_act_pos.end();
	//		for(;beg!=end;beg++){
	//			cout<<*beg<<",";
	//		}
	//		cout<<"}\nNon-active positions(N) (NE)：{";
	//		beg=non_act_pos_NE.begin();
	//		end=non_act_pos_NE.end();
	//		for(;beg!=end;beg++){
	//			cout<<*beg<<",";
	//		}


	//		cout<<"}\nPending positions(P) (GA)：{";
	//		beg=pending_pos.begin();
	//		end=pending_pos.end();
	//		for(;beg!=end;beg++){
	//			cout<<*beg<<",";
	//		}
	//		cout<<"}\nPending positions(P) (NE)：{";
	//		beg=pending_pos_NE.begin();
	//		end=pending_pos_NE.end();
	//		for(;beg!=end;beg++){
	//			cout<<*beg<<",";
	//		}
	//		cout<<"}"<<endl<<endl<<endl;
	//	}
	//	delete [] pos;
	//	/*cout<<"------General Algorithm-----"<<endl;
	//	E_KSDC_seq_with_given_ISD(d,pos);
	//	cout<<"------Numberical Experiments----Number of sampling internal states:"<<N<<"----"<<endl;
	//	KSD_pos_with_fixed_diff(d,pos,1,N);
	//	cout<<endl<<endl;*/
	//}
	//cout<<"test complete..."<<endl;

	////Test the correctness of calculation E-KSDC
	////compared with numerical results
	//srand((unsigned)time(NULL));
	//rc4_setup();
	////test 1000 times
	//u32 counter=0;
	//for(int D=0;D<1000;D++){
	//	u32 d=rc4() % 25+1;  //  consider hamming weight lower than 25
	//	u32 N=100000;		// sampling size of numerical experiment
	//	u32 *pos=new u32[d]();
	//	//randomly induce differences
	//	for(int i=0;i<d;i++){
	//		pos[i]=rc4() % 160;
	//	}
	//	if((++counter) % 250 ==0){
	//		cout<<"proceed "<<setprecision(3)<<(double)counter*100/1000<<"%..."<<endl;
	//	}

	//	string KSDC_Gen_Alo="";
	//	string KSDC_num_exp="";
	//	KSDC_Gen_Alo=E_KSDC_seq_with_given_ISD(d,pos);
	//	KSDC_num_exp=KSD_sequence_with_fixed_diff(d,pos,N);
	//	if(KSDC_Gen_Alo.compare(KSDC_num_exp)!=0){ //record the exceptional cases, i.e., inconsistent cases
	//		cout<<"ISD differential index:{";
	//		for(int i=0;i<d;i++){
	//			cout<<pos[i]<<",";
	//		}
	//		cout<<"}"<<endl;
	//		cout<<"KSDC (GA):"<<KSDC_Gen_Alo<<endl;
	//		cout<<"KSDC (NE):"<<KSDC_num_exp<<endl;
	//		vector<int> act_pos;
	//		vector<int> non_act_pos;
	//		vector<int> pending_pos;

	//		vector<int> act_pos_NE;
	//		vector<int> non_act_pos_NE;
	//		vector<int> pending_pos_NE;
	//		u32 KSDC_gen_alo_fixed_num=0;
	//		u32 KSDC_num_exp_fixed_num=0;
	//		for(int j=0;j<KSLen*8;j++){
	//			if(KSDC_Gen_Alo.at(j)=='0'){
	//				KSDC_gen_alo_fixed_num++;
	//				non_act_pos.push_back(j+1);
	//			}else if(KSDC_Gen_Alo.at(j)=='1'){
	//				KSDC_gen_alo_fixed_num++;
	//				act_pos.push_back(j+1);
	//			}else
	//				pending_pos.push_back(j+1);


	//			if(KSDC_num_exp.at(j)=='0'){
	//				KSDC_num_exp_fixed_num++;
	//				non_act_pos_NE.push_back(j+1);
	//			}else if(KSDC_num_exp.at(j)=='1'){
	//				KSDC_num_exp_fixed_num++;
	//				act_pos_NE.push_back(j+1);
	//			}else
	//				pending_pos_NE.push_back(j+1);


	//		}
	//		cout<<"Number of fixed positions (GA)："<<KSDC_gen_alo_fixed_num;
	//		cout<<"\nNumber of fixed positions (NE)："<<KSDC_num_exp_fixed_num;
	//		cout<<"\nAbsolute active positions(Y) (GA):{";
	//		vector<int>::iterator beg=act_pos.begin();
	//		vector<int>::iterator end=act_pos.end();
	//		for(;beg!=end;beg++){
	//			cout<<*beg<<",";
	//		}
	//		cout<<"}\nAbsolute active positions(Y) (NE):{";
	//		beg=act_pos_NE.begin();
	//		end=act_pos_NE.end();
	//		for(;beg!=end;beg++){
	//			cout<<*beg<<",";
	//		}
	//
	//		cout<<"}\nNon-active positions(N) (GA)：{";
	//		beg=non_act_pos.begin();
	//		end=non_act_pos.end();
	//		for(;beg!=end;beg++){
	//			cout<<*beg<<",";
	//		}
	//		cout<<"}\nNon-active positions(N) (NE)：{";
	//		beg=non_act_pos_NE.begin();
	//		end=non_act_pos_NE.end();
	//		for(;beg!=end;beg++){
	//			cout<<*beg<<",";
	//		}


	//		cout<<"}\nPending positions(P) (GA)：{";
	//		beg=pending_pos.begin();
	//		end=pending_pos.end();
	//		for(;beg!=end;beg++){
	//			cout<<*beg<<",";
	//		}
	//		cout<<"}\nPending positions(P) (NE)：{";
	//		beg=pending_pos_NE.begin();
	//		end=pending_pos_NE.end();
	//		for(;beg!=end;beg++){
	//			cout<<*beg<<",";
	//		}
	//		cout<<"}"<<endl<<endl<<endl;
	//	}
	//	delete [] pos;
	////	/*cout<<"------General Algorithm-----"<<endl;
	////	E_KSDC_seq_with_given_ISD(d,pos);
	////	cout<<"------Numberical Experiments----Number of sampling internal states:"<<N<<"----"<<endl;
	////	KSD_pos_with_fixed_diff(d,pos,1,N);
	////	cout<<endl<<endl;*/
	//}
	//cout<<"test complete..."<<endl;



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
	//srand((unsigned)time(NULL));
	//rc4_setup();
	//u32 N_total=100;
	//u32 step=10;
	//u32 total=0;
	//for(int i=0;i<N_total;i++){//重复100次
	//	cout<<"************i:"<<i<<"*************"<<endl;
	//	u32 res=validate_d_near_collision_Lemma_1(43,15,step);
	//	if(res)
	//		total++;
	//}
	//cout<<"成功率为："<<setprecision(3)<<(double)total/N_total<<endl;
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


	//calculate the average number of fixed positions in BW-E-KSDC
	//srand((unsigned)time(NULL));
	//rc4_setup();	
	//for(int d=3;d<=30;d++){
	//	cout<<"*************************d:"<<d<<"************************"<<endl;
	//	//ave_KSD_pos_with_fixed_diff_with_SP(d,300,100000);
	//	
	//	average_fixed_pos_BW_E_KSDC(d,1000000);
	//	//ave_KSD_pos_with_fixed_diff(d,500,100000);
	//	//BW_ave_KSD_pos_with_fixed_diff(d,300,100000);
	//	//BW_ave_KSD_pos_with_fixed_diff_with_SP(d,300,100000);
	//}




	//calculate the average number of fixed positions in E-KSDC
	//srand((unsigned)time(NULL));
	//rc4_setup();	
	//for(int d=3;d<=30;d++){
	//	cout<<"*************************d:"<<d<<"************************"<<endl;
	//	//ave_KSD_pos_with_fixed_diff_with_SP(d,300,100000);
	//	
	//	average_fixed_pos_E_KSDC(d,1000000);
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



