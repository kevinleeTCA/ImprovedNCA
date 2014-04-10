/*
	Created by Kevin Lee 2013/6/16
	用来验证通过overlapping的方式选取的密钥流，对应的内部状态应该是存在d-near-collision的。
*/


#include "head.h"
/*
	一旦d的值确定了，对应的V(n,d)的值也就确定了，我们就可以确定
	所需要的差分|H|=2^{n/2}/sqrt(V(n,d))
	根据所需要的差分的数目，可以算出需要的密钥流的数据量。
	假设滑动窗口为1，那么根据|H|我们就可以算出，需要的D
	从而验证生成这么多密钥流，所对应的内部状态之间是否存在
	d-near-collision
	参数列表：
	d:ISD的最大汉明重量
	D:所需的数据量（bits）
	step:滑动步长 步长在1-KSlen*8之间,密鈅流都是有重叠比特的
*/
u32 validate_d_near_collision(u32 d,u64 D,u32 step){
	u32 res=0;
	//建立结果的输出文件
	//string curr_DIR="E:\\研究生课程\\讨论班\\Cryptalysis of Grain v1\\验证d-near-collision的存在性\\validate_d_near_collision\\";
	string curr_DIR="D:\\kevin_grain\\验证d-near-collision的存在性\\validate_d_near_collision\\";
	string part="(d,D)_(";
	curr_DIR=curr_DIR+part+int_2_string(d)+",2^"+int_2_string(D)+")_step_"
		+int_2_string(step)+".txt";
	string fileName=curr_DIR;
	ofstream outfile;
	outfile.open(fileName.c_str(),ofstream::app);
	//随机选择一个起始状态
	u8 rnd_state[LEN];
	for(int j=0;j<LEN;j++){
		rnd_state[j]=rc4();
	}
	//将这个起始状态载入到Grain中
	ECRYPT_ctx ctx;
	ctx.keysize=80;
	ctx.ivsize=64;
	ECRYPT_grain_state_load(&ctx,rnd_state);
	//生成H bits的数据量对应的内部状态集合。
	u64 H=(u64)pow(2,(double)D);
	State_array *SA=new State_array[H]();
	u64 clock_t=0;
	for(u64 i=0;i<H;i++){
		//记录每一拍对应的内部状态
		SA[i].clock_t=clock_t;
		ECRYPT_grain_state_read(&ctx,SA[i].STATE);
		for(u32 j=0;j<step;j++){
			ENCRYPT_grain_keystream(&ctx);
			clock_t++;
		}
	}
	//在内部状态集合中，查找d-near-collision的状态,枚举所有的C(D,2)个状态差分，判断其是否为d-near-collision
	/*ECRYPT_grain_state_load(&ctx,SA[D-1].STATE);
	for(u64 i=0;i<D-1;i++){
		ENCRYPT_grain_keystream_backward(&ctx);
	}
	u8 rnd_state_bw[LEN];
	ECRYPT_grain_state_read(&ctx,rnd_state_bw);
	cout<<"退回来的状态为：";
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
			//计算其差分的汉明重量  由于我们只考虑在LFSR中引入差分，所以我们只计算LFSR状态的汉明重量
			/*for(int k=0;k<LEN;k++){
				ISD[k]=(SA[i].STATE[k])^(SA[j].STATE[k]);
				if(k>=10){
					for(int m=0;m<8;m++)
					HM_val+=(ISD[k]>>m)&0x01;
						if(HM_val>d) break;
				}
			}*/
			//计算其差分的汉明重量 在LFSR和NFSR中随机引入差分
			for(int k=0;k<LEN;k++){
				ISD[k]=(SA[i].STATE[k])^(SA[j].STATE[k]);
				for(int m=0;m<8;m++)
					HM_val+=(ISD[k]>>m)&0x01;
						if(HM_val>d) break;
			}
			if(HM_val<=d){
				//将起始初态输出
				outfile<<"状态出现d-near-collision的碰撞.汉明重量为："<<HM_val<<endl;
				outfile<<"发生碰撞的起始的状态为："<<endl;
				for(int k=0;k<LEN;k++){
					outfile<<setw(2)<<hex<<(u32)rnd_state[k];
				}
				outfile<<endl;
				//命中了d-near-collision的Hamming weight
				outfile<<"发生d-near-collision的状态差分："<<endl;
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
				outfile<<"发生d-near-collision的时刻分别为："<<dec<<SA[i].clock_t<<"  "<<dec<<SA[j].clock_t<<endl;
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
 A和B两个集合的情况，|A|*|B|>2^n/V(n,d)
*/

u32 validate_d_near_collision_Lemma_1(u32 d,u64 D,u32 step){
	u32 res=0;
	//建立结果的输出文件
	//string curr_DIR="E:\\研究生课程\\讨论班\\Cryptalysis of Grain v1\\验证d-near-collision的存在性\\validate_d_near_collision_Lemma_1\\";
	string curr_DIR="D:\\kevin_grain\\验证d-near-collision的存在性\\validate_d_near_collision_Lemma_1\\";
	string part="(d,D)_(";
	curr_DIR=curr_DIR+part+int_2_string(d)+",2^"+int_2_string(D)+")_step_"
		+int_2_string(step)+".txt";
	string fileName=curr_DIR;
	ofstream outfile;
	outfile.open(fileName.c_str(),ofstream::app);
	//随机选择两个起始状态，并load
	
	u8 rnd_state1[LEN];
	for(int j=0;j<LEN;j++){
		rnd_state1[j]=rc4();
	}
	u8 rnd_state2[LEN];
	for(int j=0;j<LEN;j++){
		rnd_state2[j]=rc4();
	}
	//将这两个起始状态载入到Grain中
	ECRYPT_ctx ctx1;
	ctx1.keysize=80;
	ctx1.ivsize=64;
	ECRYPT_grain_state_load(&ctx1,rnd_state1);

	ECRYPT_ctx ctx2;
	ctx2.keysize=80;
	ctx2.ivsize=64;
	ECRYPT_grain_state_load(&ctx2,rnd_state2);
	//生成H bits的数据量对应的内部状态集合A和B。
	u64 H=(u64)pow(2,(double)D);
	State_array *SA1=new State_array[H]();
	State_array *SA2=new State_array[H]();
	u64 clock_t=0;
	for(u64 i=0;i<H;i++){
		//记录每一拍对应的内部状态
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
			//计算其差分的汉明重量 在LFSR和NFSR中随机引入差分
			for(int k=0;k<LEN;k++){
				ISD[k]=(SA1[i].STATE[k])^(SA2[j].STATE[k]);
				for(int m=0;m<8;m++)
					HM_val+=(ISD[k]>>m)&0x01;
						if(HM_val>d) break;
			}
			if(HM_val<=d){
				//将起始初态输出
				outfile<<"状态出现d-near-collision的碰撞.汉明重量为："<<HM_val<<endl;
				outfile<<"发生碰撞的起始的状态为S_A：";
				for(int k=0;k<LEN;k++){
					outfile<<setw(2)<<hex<<(u32)rnd_state1[k];
				}
				outfile<<"  S_B：";
				for(int k=0;k<LEN;k++){
					outfile<<setw(2)<<hex<<(u32)rnd_state2[k];
				}
				outfile<<endl;
				//命中了d-near-collision的Hamming weight
				outfile<<"发生d-near-collision的状态差分："<<endl;
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
				outfile<<"发生d-near-collision的时刻分别为 t_A："<<dec<<SA1[i].clock_t<<"  t_B"<<dec<<SA2[j].clock_t<<endl;
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
	不重复利用同一时刻的状态来与其他状态异或得到的差分来作为判断
	按照次序顺序生成状态以及对应的差分。
	逐个判断差分是否为d-near-collision的
	直到判断的数量超过了|H|>= 2^{n/2}/sqrt(V(n,d))
	参数列表：
	d:ISD的最大汉明重量
	H:所需的差分的个数 
	step:滑动步长 步长在1-KSlen*8之间,密鈅流都是有重叠比特的
*/
bool validate_d_near_collision_non_reuse(u32 d,u64 H,u32 step){
	//建立结果的输出文件
	string curr_DIR="E:\\研究生课程\\讨论班\\Cryptalysis of Grain v1\\验证d-near-collision的存在性\\";
	string part="(d,D)_(";
	curr_DIR=curr_DIR+part+int_2_string(d)+",2^"+int_2_string(H)+")_step_"
		+int_2_string(step)+".txt";
	string fileName=curr_DIR;
	ofstream outfile;
	outfile.open(fileName.c_str(),ofstream::app);
	//随机选择一个起始状态
	u8 S1[LEN];
	for(int j=0;j<LEN;j++){
		S1[j]=rc4();
	}
	//将这个起始状态载入到Grain中
	ECRYPT_ctx ctx_1;
	ctx_1.keysize=80;
	ctx_1.ivsize=64;
	ECRYPT_grain_state_load(&ctx_1,S1);
	//将ctx_1进行step步clock之后得到的状态作为ctx_2的状态
	for(u32 i=0;i<step;i++)
		ENCRYPT_grain_keystream(&ctx_1);
	u8 S2[LEN];
	ECRYPT_grain_state_read(&ctx_1,S2);
	//还原ctx_1的初态
	ECRYPT_grain_state_load(&ctx_1,S1);
	//初始化ctx_2
	ECRYPT_ctx ctx_2;
	ctx_2.keysize=80;
	ctx_2.ivsize=64;
	ECRYPT_grain_state_load(&ctx_2,S2);
	//然后逐步查找d-near-collision的状态
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
		//计算当前状态的差分
		u8 ISD[LEN];
		u32 HM_val=0;
		//由于我们只考虑在LFSR中引入差分，所以我们只计算LFSR状态的汉明重量
		/*for(int j=0;j<LEN;j++){
			ISD[j]=curr_S1[j]^curr_S2[j];
			if(j>=10){
				for(int m=0;m<8;m++)
					HM_val+=(ISD[j]>>m)&0x01;
				if(HM_val>d) break;
			}
		}*/
		//计算其差分的汉明重量 在LFSR和NFSR中随机引入差分
		for(int j=0;j<LEN;j++){
			ISD[j]=curr_S1[j]^curr_S2[j];
			for(int m=0;m<8;m++)
				HM_val+=(ISD[j]>>m)&0x01;
			if(HM_val>d) break;
		}
		//判断当前状态差分是否是d-near-collision的
		if(HM_val<=d){
			if(outfile){
				outfile<<"LFSR上的状态出现d-near-collision的碰撞.汉明重量为："<<HM_val<<endl;
						//将起始初态输出
				outfile<<"发生碰撞的起始的状态为S1：";
				for(int j=0;j<LEN;j++){
					outfile<<setw(2)<<hex<<(u32)S1[j];
				}
				outfile<<endl;
				outfile<<"发生碰撞的起始的状态为S2：";
				for(int j=0;j<LEN;j++){
					outfile<<setw(2)<<hex<<(u32)S2[j];
				}
				outfile<<endl;
				//命中了d-near-collision的Hamming weight
				outfile<<"发生d-near-collision的状态差分：";
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
				outfile<<"发生d-near-collision的时刻为："<<clock_t<<"，Step为"<<step<<endl;
			}
			return true;
		}	
		//如果不是继续查找
		clock_t++;
		ENCRYPT_grain_keystream(&ctx_1);
		ENCRYPT_grain_keystream(&ctx_2);
	}
	outfile.close();
	return false;
}