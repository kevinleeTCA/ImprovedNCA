/*
	Created by Kevin Lee 2013/7/26
	随机选择num_ISD (100~1000)个ISD，对于每个汉明重量为k的ISD根据N_k计算其前
	sub_N个proportion最大的KSD，然后保存在一个set中，最后求出set中KSD的数目m和枚举量num_ISD*sub_N
	的比值，记为ρ_k。
*/


#include "head.h"

double Q_estimate_random_sampling(u32 d,u32 num_ISD,u64 N,u64 sub_N){
	map<string,u32> counter;
	set<string> poss_KSD;
	u64 sum=0;
	//随机选择num_ISD个差分
	for(int D=1;D<=num_ISD;D++){
		if(D % 400 ==0){
			cout<<"proceed "<<setprecision(3)<<(double)D*100/num_ISD<<"%..."<<endl;
		}
			u32* pos=new u32[d]();
		for(int j=0;j<d;j++){
			pos[j]=rc4() % 160;
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
		//随机选择N个状态
		for(u64 i=0;i<N;i++){
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
			//统计各个差分出现的频率
			string str=char2HexString(Diff_KS,KSLen);
			map<string,u32>::iterator it=counter.find(str);
			if(it!=counter.end()){//已存在这个差分
				it->second+=1;
			}else
				counter.insert(make_pair(str,1));
		}
		delete [] pos;
		//通过最小值堆统计其比例最大的前sub_N个KSD proportion的平均值
		u64 dataSize=counter.size();
		u32 curr_sub_N=dataSize>sub_N?sub_N:dataSize;
		sum+=curr_sub_N;
		u32 heap_size=curr_sub_N; 
		u32 array_size=curr_sub_N+1;//堆的index从1开始计数。
		//首先建立数组
		KSD_Prop* KSD_prop_arr=new KSD_Prop[array_size];
		//将counter的前curr_sub_N个元素填充到堆中
		u64 currIdx=1;
		map<string,u32>::iterator beg=counter.begin();
		map<string,u32>::iterator end=counter.end();
		for(u32 i=0;i<curr_sub_N;i++){
			KSD_prop_arr[currIdx].KSD=beg->first;
			KSD_prop_arr[currIdx++].occurrance=beg->second;
			beg++;
		}
		//建堆操作
		BUILD_MIN_HEAP(KSD_prop_arr,heap_size);
		//从第curr_sub_N+1个元素开始，扫描所有counter中的元素，找到前sub_N个proportion最大的KSD
		for(;beg!=end;beg++){
			//首先和堆顶元素比较，如果比堆顶元素大，那么替换堆顶元素并保持堆的性质
			if(KSD_prop_arr[1].occurrance<beg->second){
				KSD_prop_arr[1].KSD=beg->first;
				KSD_prop_arr[1].occurrance=beg->second;
				HEAP_MIN_HEAPIFY(KSD_prop_arr,1,heap_size);
			}
		}
		//最后堆中的元素即为所求的前sub_N个proportion最大的KSD
		//u64 sum_occur=0;
		for(int i=1;i<array_size;i++){
			poss_KSD.insert(KSD_prop_arr[i].KSD);
		}
		////对KSD及其prop按照prop的大小进行排序
		//u64 dataSize=counter.size();
		//KSD_Prop* KSD_prop_arr=new KSD_Prop[dataSize];
		//u64 currIdx=0;
		//map<string,u32>::iterator beg=counter.begin();
		//map<string,u32>::iterator end=counter.end();
		//for(;beg!=end;beg++){
		//	KSD_prop_arr[currIdx].KSD=beg->first;
		//	KSD_prop_arr[currIdx++].occurrance=beg->second;
		//}
		////进行排序
		//qsort(KSD_prop_arr,dataSize,sizeof(KSD_Prop),comp_struct_KSD_Prop);
		////记录其前sub_N个KSD，当dataSize<sub_N时，就保存全部的dataSize个KSD
		//u64 curr_sub_N=dataSize>sub_N?sub_N:dataSize;
		//sum+=curr_sub_N;
		//for(u64 i=0;i<curr_sub_N;i++){
		//	poss_KSD.insert(KSD_prop_arr[i].KSD);
		//}
		counter.clear();
		delete [] KSD_prop_arr;
	}
	double prop_q=(double)poss_KSD.size()/sum;
	cout<<"对于(d,l)=("<<d<<","<<KSLen*8<<")而言，最终的比例为No. of KSD/No.of Sampling："
		<<poss_KSD.size()<<"/"<<sum<<",比例为q:"<<prop_q<<endl;
	return prop_q;
}


