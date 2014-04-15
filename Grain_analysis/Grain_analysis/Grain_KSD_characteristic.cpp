/*
	Created by Kevin Lee 2013/6/16
	Observation of KSD characteristic of Grain v1.
	for each ISD， observe its positions in KSD with fixed differential value (0/1)
	counter the average number of those positions.
*/


#include "head.h"

//测试对于任意一个随机的ISD对应的KSD characteristic中固定位置的个数
/*参数：
d:输入差分的最大汉明重量
num_ISD:随机选择汉明重量为d的输入差分的个数
N:每一个差分对应的测试样本的数量
*/
//用来去除引入差分位置中的重复位置
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
		//随机选取160bit 状态的差分位置 NFSR从0~79，LFSR从80~159
		u32* pos=new u32[d]();
		for(int j=0;j<d;j++){
			//pos[j]=rc4() % 160;
			//pos[j]=(rc4() % 80)+80;				//只给LFSR中引入差分
			pos[j]=(rc4() % 80);				//只给NFSR中引入差分
			//pos[j]=(rc4() % 40)+80;			//只給LFSR的左半部分引入差分 80-119
			//pos[j]=(rc4() % 40)+120;			//只给LFSR的右半部分引入差分 120-159
			while(isExist(pos,j,pos[j]))		//保证随机位置不会出现重复
				//pos[j]=rc4() % 160;
				//pos[j]=(rc4() % 80)+80;			//只给LFSR中引入差分
				pos[j]=(rc4() % 80);			//只给NFSR中引入差分
			//pos[j]=(rc4() % 40)+80;			//只給LFSR的左半部分引入差分 80-119
			//pos[j]=(rc4() % 40)+120;			//只给LFSR的右半部分引入差分 120-159
			//pos[j]=(rc4() % 10)+150;			//只给LFSR的右半部分引入差分 150-159
			//pos[j]=(rc4() % 20)+140;			//只给LFSR的右半部分引入差分 140-159
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
		//输出当前ISD和对应的汉明重量
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
	average_HM_val=(double)average_HM_val/num_ISD;
		cout<<"Average Hamming weight:"<<setprecision(3)<<average_HM_val<<"  The average fixed pos(d,l,N):("
			<<d<<","<<KSLen<<","<<N<<") is "<<setprecision(3)<<average_KSD_fixed_pos_num<<endl;
}


//测试对于任意一个指定的ISD对应的KSD characteristic中固定位置的个数，以及0,1,*位置的分布
/*参数：
d:输入差分的最大汉明重量,也就是数组pos的长度
pos:引入差分位置的下标数组
N:每一个差分对应的测试样本的数量
*/
void KSD_pos_with_fixed_diff(u32 d,u32 *pos,u32 N){
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
	//输出当前ISD
	/*	cout<<"\n-------------State Differential-"<<D<<":"<<ends;
	for(int j=0;j<LEN;j++){
			printf("%x ",ISD[j]);
	}
	cout<<"-----------"<<endl;*/
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
		//计算KSD characteristic
		for(int j=0;j<KSLen;j++){
			And_logic[j]&=Diff_KS[j];
			Or_logic[j]|=Diff_KS[j];
		}
	}
	//计算当前输入差分对应的KSD的characteristic  
	//And逻辑确定全1的位置  Or逻辑确定全0的位置  剩下的就是不确定的位置
	//分别记录Active  non-active和possible active位置的下标
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
	cout<<"\nNumber of fixed positions："<<KW_KSD_CH;
	cout<<"\nAbsolute active positions(Y)：{";
	vector<int>::iterator beg=act_pos.begin();
	vector<int>::iterator end=act_pos.end();
	for(;beg!=end;beg++){
		cout<<*beg<<",";
	}
	cout<<"}\nNon-active positions(N)：{";
	beg=non_act_pos.begin();
	end=non_act_pos.end();
	for(;beg!=end;beg++){
		cout<<*beg<<",";
	}
	cout<<"}\nPending positions(P)：{";
	beg=poss_act_pos.begin();
	end=poss_act_pos.end();
	for(;beg!=end;beg++){
		cout<<*beg<<",";
	}
	cout<<"}"<<endl;
}


//计算给定一个差分对应的输出KSD的characteristic （数值实验）
/*参数：
d:输入差分的最大汉明重量,也就是数组pos的长度
pos:引入差分位置的下标数组
N:每一个差分对应的测试样本的数量

返回对应的KSD characteristic
*/
string KSD_sequence_with_fixed_diff(u32 d,u32 *pos,u32 N){
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
	//输出当前ISD
	/*	cout<<"\n-------------State Differential-"<<D<<":"<<ends;
	for(int j=0;j<LEN;j++){
			printf("%x ",ISD[j]);
	}
	cout<<"-----------"<<endl;*/
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
		//计算KSD characteristic
		for(int j=0;j<KSLen;j++){
			And_logic[j]&=Diff_KS[j];
			Or_logic[j]|=Diff_KS[j];
		}
	}
	//计算当前输入差分对应的KSD的characteristic  
	//And逻辑确定全1的位置  Or逻辑确定全0的位置  剩下的就是不确定的位置
	//分别记录Active  non-active和possible active位置的下标
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
	cout<<"\nNumber of fixed positions："<<KW_KSD_CH;
	cout<<"\nAbsolute active positions(Y)：{";
	vector<int>::iterator beg=act_pos.begin();
	vector<int>::iterator end=act_pos.end();
	for(;beg!=end;beg++){
		cout<<*beg<<",";
	}
	cout<<"}\nNon-active positions(N)：{";
	beg=non_act_pos.begin();
	end=non_act_pos.end();
	for(;beg!=end;beg++){
		cout<<*beg<<",";
	}
	cout<<"}\nPending positions(P)：{";
	beg=poss_act_pos.begin();
	end=poss_act_pos.end();
	for(;beg!=end;beg++){
		cout<<*beg<<",";
	}
	cout<<"}"<<endl;*/

}




/*
枚举所有输出差分汉明重量小于等于d的ISD，并计算其E_KSDC的值并存储在文件中
参数：
d:输入差分的最大汉明重量
N:每一个差分对应的测试样本的数量
*/
void E_KSDC_enumerate_all_ISD(u32 d,u64 N){
	//随机源的建立
	srand((unsigned)time(NULL));
	rc4_setup();
	//建立目录，如果不存在则自动建立目录
	cout<<"----------------------d:"<<d<<"--------------------"<<endl;
	string head_DIR="E:\\研究生课程\\讨论班\\Cryptalysis of Grain v1\\ISD对应差分分布[Y,N,P]-数值实验\\";
	string part="LFSR_(d,l)_(";
	//make_DIR(curr_DIR);
	for(int i=1;i<=d;i++){
		cout<<"开始处理输入差分汉明重量为:"<<i<<"的情况."<<endl;
		string fileName=head_DIR+part+int_2_string(i)+","+int_2_string(KSLen)+").txt";
		//E_KSDC_enu_for_search(LEN*8,i,N,fileName);		//给所有160比特状态中引入差分。
		E_KSDC_enu_for_search(80,i,N,fileName);			//考虑只给LFSR的80比特引入差分
		cout<<"输入差分汉明重量为:"<<i<<"的情况已经处理完毕.\n\n"<<endl;
	}
}

void E_KSDC_enu_for_search(u32 n,u32 k,u64 N,string fileName){
	//定义一个计数器，用来检测试验的进度
	u64 counter=0;
	//预先存储一个估计的总的计算量
	u64 t_Sum[5]={160,12720,669920,26294360,820384032};
	//初始化组合向量
	u32 *v=new u32[k+1]();
	for(int i=0;i<k;i++){
		v[i]=i+1;
	}
	v[k]=n+1;
	//用初始化的组合数，并对初始化组合进行操作
	E_KSDC_calculation(k,v,N,fileName);
	//穷举C(n,k)的所有组合，为每个组合设定输入状态差分，并执行grain得到输出差分
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
			//根据当前组合进行操作
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
	//初始化 输入差分为全0 并输出当前组合v的对应的输入状态差分
	u8 *ISD=new u8[LEN]();
	for(int m=0;m<k;m++){
		//cout<<v[m]<<" "<<ends;
		u32 p=posIdx(v[m]-1);
		u32 r=rotateIdx(v[m]-1);
		//ISD[p]=ISD[p]^(1<<r);  //在全部160比特引入差分
		ISD[10+p]=ISD[10+p]^(1<<r);    //只在LFSR中引入差分
	}
	//计算KSD characteristic
	u8 And_logic[KSLen];   //用来确定差分中全1的位置
	u8 Or_logic[KSLen];		//用来确定差分中全0的位置
	//初始化 and 和 or logic
	for(int i=0;i<KSLen;i++){
		And_logic[i]=255;
		Or_logic[i]=0;
	}
	//随机选择N个状态
	for(int i=0;i<N;i++){
		u8 rnd_state_1[LEN];
		for(int j=0;j<LEN;j++){
			rnd_state_1[j]=rc4();
		}
		//根据差分位置，得到另一个状态rud_state_2
		u8 rnd_state_2[LEN];
		for(int j=0;j<LEN;j++){
			rnd_state_2[j]=rnd_state_1[j]^ISD[j];
		}
		//分别代入Grain中 输出l长的密钥流
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
		//计算KSD characteristic
		for(int j=0;j<KSLen;j++){
			And_logic[j]&=Diff_KS[j];
			Or_logic[j]|=Diff_KS[j];
		}
	}
	//计算当前输入差分对应的KSD的characteristic  
	//And逻辑确定全1的位置  Or逻辑确定全0的位置  剩下的就是不确定的位置
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
	//输出到对应的文件中
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