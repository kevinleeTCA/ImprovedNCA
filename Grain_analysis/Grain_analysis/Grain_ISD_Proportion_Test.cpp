/*
	Created by Kevin Lee 2013/7/25
	用来估计对于一个汉明重量为k的ISD而言，平均情况下N_k^{~}<N_k
	应该取多大时才能保证这个ISD以50%或更高的概率出现在其对应的ISD table当中。
	因为对于一个ISD而言，其KSD的分布是不均匀的
*/


#include "head.h"
/*参数：
d:输入差分的最大汉明重量
num_ISD:随机选择汉明重量为d的输入差分的个数
N:每一个差分对应的测试样本的数量
sub_N:实际存储的前sub_N个KSD（依据proportion排序，降序）
*/
void ISD_prop_test(u32 d,u32 num_ISD,u64 N,u32 sub_N){
	map<string,u32> counter;
	//随机选择num_ISD个差分
	double ave_KSD_prop=0.0;
	for(int D=1;D<=num_ISD;D++){
		//cout<<"*********ISD:"<<D<<"*********"<<endl;
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
		u64 sum_occur=0;
		for(int i=1;i<array_size;i++){
			sum_occur+=KSD_prop_arr[i].occurrance;
		}
		ave_KSD_prop+=(double)sum_occur;
		//ave_KSD_prop+=(double)sum_occur/N;
		counter.clear();
		delete [] KSD_prop_arr;
	}
	/*cout<<"(d,l):("<<d<<","<<KSLen*8<<")時平均情况下随机选取的"<<num_ISD<<"个差分中，当我们最多只存储"<<sub_N
		<<"个KSD时，对应的proportion的和是:"<<ave_KSD_prop/num_ISD<<endl;*/
	cout<<"(d,l):("<<d<<","<<KSLen*8<<")時平均情况下随机选取的"<<num_ISD<<"个差分中，当我们最多只存储"<<sub_N
		<<"个KSD时，对应的occurrance的和是:"<<ave_KSD_prop/num_ISD<<endl;
}

int comp_struct_KSD_Prop(const void *a,const void *b){
	KSD_Prop* val_a=(KSD_Prop*)a;
	KSD_Prop* val_b=(KSD_Prop*)b;
	u64 occur_a=val_a->occurrance;
	u64 occur_b=val_b->occurrance;
	return occur_b-occur_a;
}


u32 HEAP_PARENT(u32 i){
	return i/2;
}
u32 HEAP_LEFT(u32 i){
	return 2*i;
}
u32 HEAP_RIGHT(u32 i){
	return 2*i+1;
}
void HEAP_MIN_HEAPIFY(KSD_Prop* A,u32 i,u32 heap_size){
	u32 l=HEAP_LEFT(i);
	u32 r=HEAP_RIGHT(i);
	u32 minimum=0;
	if(l<=heap_size && A[l].occurrance<A[i].occurrance)
		minimum=l;
	else
		minimum=i;
	if(r<=heap_size && A[r].occurrance<A[minimum].occurrance)
		minimum=r;
	if(minimum!=i){
		//exchange A[i] and A[minimum]
		string KSD=A[i].KSD;
		u32 occurr=A[i].occurrance;
		A[i].KSD=A[minimum].KSD;
		A[i].occurrance=A[minimum].occurrance;
		A[minimum].KSD=KSD;
		A[minimum].occurrance=occurr;
		HEAP_MIN_HEAPIFY(A,minimum,heap_size);
	}
}
void BUILD_MIN_HEAP(KSD_Prop* A,u32 heap_size){
	for(u32 i=heap_size/2;i>=1;i--)
		HEAP_MIN_HEAPIFY(A,i,heap_size);
}
