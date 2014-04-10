/*
	Created by Kevin Lee 2013/6/16
	enumerated all possible ISD with Hamming weight <= d
	calculating all possible KSD.
*/


#include "head.h"

/*参数：
d:输入差分的最大汉明重量
N_array:对每一个差分，需要枚举的状态数目 是一个数组，针对不同的d选取不同大小的sampling size
*/

void cal_all_KSD_construct_table(u32 d, u64* N_array){
	//随机源的建立
	srand((unsigned)time(NULL));
	rc4_setup();
	//建立目录，如果不存在则自动建立目录
	cout<<"----------------------d:"<<d<<"--------------------"<<endl;
	string part="(d,l)_(";
	string curr_DIR=DIR+part+int_2_string(d)+","+int_2_string(KSLen)+")\\";
	make_DIR(curr_DIR);
	for(int i=1;i<=d;i++){
		cout<<"开始处理输入差分汉明重量为:"<<i<<"的情况."<<endl;
		combination_for_search_imp(LEN*8,i,N_array[i-1],curr_DIR);
		cout<<"输入差分汉明重量为:"<<i<<"的情况已经处理完毕.\n\n"<<endl;
	}
}
//简单组合问题，打印从1~n个数中选取k个的所有组合,这个程序对于k和n比较小的时候速度快,非递归实现
//用于辅助输入差分的搜索
void combination_for_search_imp(u32 n,u32 k,u64 N, string curr_DIR){
	//定义一个计数器，用来检测试验的进度
	long long counter=0;
	//预先存储一个估计的总的计算量
	long long t_Sum[5]={160,12720,669920,26294360,820384032};
	//初始化组合向量
	u32 *v=new u32[k+1]();
	for(int i=0;i<k;i++){
		v[i]=i+1;
	}
	v[k]=n+1;
	//用初始化的组合数，并对初始化组合进行操作
	genOutput_diff_imp(k,v,N,curr_DIR);
	//穷举C(n,k)的所有组合，为每个组合设定输入状态差分，并执行grain得到输出差分
	while(combin_for_search_imp_sub(k,v,N,curr_DIR)){
		if((++counter) % 30000 ==0){
			cout<<"proceed "<<setprecision(3)<<(double)counter*100/t_Sum[k-1]<<"%..."<<endl;
		}
	}
}
bool combin_for_search_imp_sub(u32 k,u32* v,u64 N,string curr_DIR){
	for(int i=k-1;i>=0;i--){
		if(v[i]+1!=v[i+1]){
			v[i]++;
			//根据当前组合进行操作
			for(int j=i+1;j<k;j++)
				v[j]=v[j-1]+1;
			genOutput_diff_imp(k,v,N,curr_DIR);
			
			return true;
		}
	}
	return false;
}
void genOutput_diff_imp(u32 k,u32 *v,u64 N,string curr_DIR){
	//初始化 输入差分为全0 并输出当前组合v的对应的输入状态差分
	u8 *ISD=new u8[LEN]();
	for(int m=0;m<k;m++){
		//cout<<v[m]<<" "<<ends;
		u32 p=posIdx(v[m]-1);
		u32 r=rotateIdx(v[m]-1);
		ISD[p]=ISD[p]^(1<<r);
	}
	
	//for(int i=0;i<k;i++){
	//		if(v[i])
	//			cout<<v[i]<<" "<<ends;
	//}
	//cout<<"对应输入差分："<<ends;
	//	for(int j=0;j<20;j++){
	//			printf("%x ",ISD[j]);
	//}
	//cout<<endl;
	
	map<string,u32> counter;
	//随机选择N个状态
	for(int i=0;i<N;i++){
		//cout<<"\n------Sample:"<<i+1<<"------"<<endl;
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
		//统计各个差分出现的频率
		string str=char2HexString(Diff_KS,KSLen);
		map<string,u32>::iterator it=counter.find(str);
		if(it!=counter.end()){//已存在这个差分
			it->second+=1;
		}else
			counter.insert(make_pair(str,1));
	}
	//将counter中对应的输出差分存储到一个txt文件中（以输出差分的16进制表示命名），
	//将ISD转化成16进制+输出该差分的比例，存储在txt的一行。
	//最后统计每个txt的行数，求出平均的行数，也即每个table的大小（以输出差分的16进制命名）。
	string inputDiffStr=char2HexString(ISD,LEN);
	//首先遍历counter中的所有输出差分
	map<string,u32>::iterator beg=counter.begin();
	map<string,u32>::iterator end=counter.end();
	for(;beg!=end;beg++){
		string outDiff=beg->first;
		u32 occurs=beg->second;
		double occur_prop=(double)occurs/N;
		//将输入差分和比例 写入到以outDiff命名的txt中。
		string fileName=outDiff+".txt";
		//根据outDiff高1个字节进行索引 将所有输出根据高8比特输出到不同的文件夹中
		string Index_DIR=curr_DIR+outDiff.substr(0,2)+"\\";
		make_DIR(Index_DIR);
		fileName=Index_DIR+fileName;
		ofstream outfile;
		outfile.open(fileName.c_str(),ofstream::app);
		if(outfile){
			//cout<<"file \'"<<fileName<<"\' created."<<endl;
			outfile<<inputDiffStr<<" "<<occur_prop<<"\n";
			//cout<<"Successfully write:"<<inputDiffStr<<" "<<occur_prop<<" to file:" <<fileName<<endl;
		}
		outfile.close();
	}
	counter.clear();
	delete [] ISD;
}