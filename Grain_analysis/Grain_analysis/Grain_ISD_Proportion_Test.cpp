/*
	Created by Kevin Lee 2013/7/25
	�������ƶ���һ����������Ϊk��ISD���ԣ�ƽ�������N_k^{~}<N_k
	Ӧ��ȡ���ʱ���ܱ�֤���ISD��50%����ߵĸ��ʳ��������Ӧ��ISD table���С�
	��Ϊ����һ��ISD���ԣ���KSD�ķֲ��ǲ����ȵ�
*/


#include "head.h"
/*������
d:�����ֵ����������
num_ISD:���ѡ��������Ϊd�������ֵĸ���
N:ÿһ����ֶ�Ӧ�Ĳ�������������
sub_N:ʵ�ʴ洢��ǰsub_N��KSD������proportion���򣬽���
*/
void ISD_prop_test(u32 d,u32 num_ISD,u64 N,u32 sub_N){
	map<string,u32> counter;
	//���ѡ��num_ISD�����
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
		//���ѡ��N��״̬
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
			//ͳ�Ƹ�����ֳ��ֵ�Ƶ��
			string str=char2HexString(Diff_KS,KSLen);
			map<string,u32>::iterator it=counter.find(str);
			if(it!=counter.end()){//�Ѵ���������
				it->second+=1;
			}else
				counter.insert(make_pair(str,1));
		}

		delete [] pos;
		//ͨ����Сֵ��ͳ�����������ǰsub_N��KSD proportion��ƽ��ֵ
		u64 dataSize=counter.size();
		u32 curr_sub_N=dataSize>sub_N?sub_N:dataSize;
		u32 heap_size=curr_sub_N; 
		u32 array_size=curr_sub_N+1;//�ѵ�index��1��ʼ������
		//���Ƚ�������
		KSD_Prop* KSD_prop_arr=new KSD_Prop[array_size];
		//��counter��ǰcurr_sub_N��Ԫ����䵽����
		u64 currIdx=1;
		map<string,u32>::iterator beg=counter.begin();
		map<string,u32>::iterator end=counter.end();
		for(u32 i=0;i<curr_sub_N;i++){
			KSD_prop_arr[currIdx].KSD=beg->first;
			KSD_prop_arr[currIdx++].occurrance=beg->second;
			beg++;
		}
		//���Ѳ���
		BUILD_MIN_HEAP(KSD_prop_arr,heap_size);
		//�ӵ�curr_sub_N+1��Ԫ�ؿ�ʼ��ɨ������counter�е�Ԫ�أ��ҵ�ǰsub_N��proportion����KSD
		for(;beg!=end;beg++){
			//���ȺͶѶ�Ԫ�رȽϣ�����ȶѶ�Ԫ�ش���ô�滻�Ѷ�Ԫ�ز����ֶѵ�����
			if(KSD_prop_arr[1].occurrance<beg->second){
				KSD_prop_arr[1].KSD=beg->first;
				KSD_prop_arr[1].occurrance=beg->second;
				HEAP_MIN_HEAPIFY(KSD_prop_arr,1,heap_size);
			}
		}
		//�����е�Ԫ�ؼ�Ϊ�����ǰsub_N��proportion����KSD
		u64 sum_occur=0;
		for(int i=1;i<array_size;i++){
			sum_occur+=KSD_prop_arr[i].occurrance;
		}
		ave_KSD_prop+=(double)sum_occur;
		//ave_KSD_prop+=(double)sum_occur/N;
		counter.clear();
		delete [] KSD_prop_arr;
	}
	/*cout<<"(d,l):("<<d<<","<<KSLen*8<<")�rƽ����������ѡȡ��"<<num_ISD<<"������У����������ֻ�洢"<<sub_N
		<<"��KSDʱ����Ӧ��proportion�ĺ���:"<<ave_KSD_prop/num_ISD<<endl;*/
	cout<<"(d,l):("<<d<<","<<KSLen*8<<")�rƽ����������ѡȡ��"<<num_ISD<<"������У����������ֻ�洢"<<sub_N
		<<"��KSDʱ����Ӧ��occurrance�ĺ���:"<<ave_KSD_prop/num_ISD<<endl;
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
