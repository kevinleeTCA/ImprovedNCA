/*
	Created by Kevin Lee 2013/7/26
	���ѡ��num_ISD (100~1000)��ISD������ÿ����������Ϊk��ISD����N_k������ǰ
	sub_N��proportion����KSD��Ȼ�󱣴���һ��set�У�������set��KSD����Ŀm��ö����num_ISD*sub_N
	�ı�ֵ����Ϊ��_k��
*/


#include "head.h"

double Q_estimate_random_sampling(u32 d,u32 num_ISD,u64 N,u64 sub_N){
	map<string,u32> counter;
	set<string> poss_KSD;
	u64 sum=0;
	//���ѡ��num_ISD�����
	for(int D=1;D<=num_ISD;D++){
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
		for(u64 i=0;i<N;i++){
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
		sum+=curr_sub_N;
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
		//u64 sum_occur=0;
		for(int i=1;i<array_size;i++){
			poss_KSD.insert(KSD_prop_arr[i].KSD);
		}
		////��KSD����prop����prop�Ĵ�С��������
		//u64 dataSize=counter.size();
		//KSD_Prop* KSD_prop_arr=new KSD_Prop[dataSize];
		//u64 currIdx=0;
		//map<string,u32>::iterator beg=counter.begin();
		//map<string,u32>::iterator end=counter.end();
		//for(;beg!=end;beg++){
		//	KSD_prop_arr[currIdx].KSD=beg->first;
		//	KSD_prop_arr[currIdx++].occurrance=beg->second;
		//}
		////��������
		//qsort(KSD_prop_arr,dataSize,sizeof(KSD_Prop),comp_struct_KSD_Prop);
		////��¼��ǰsub_N��KSD����dataSize<sub_Nʱ���ͱ���ȫ����dataSize��KSD
		//u64 curr_sub_N=dataSize>sub_N?sub_N:dataSize;
		//sum+=curr_sub_N;
		//for(u64 i=0;i<curr_sub_N;i++){
		//	poss_KSD.insert(KSD_prop_arr[i].KSD);
		//}
		counter.clear();
		delete [] KSD_prop_arr;
	}
	double prop_q=(double)poss_KSD.size()/sum;
	cout<<"����(d,l)=("<<d<<","<<KSLen*8<<")���ԣ����յı���ΪNo. of KSD/No.of Sampling��"
		<<poss_KSD.size()<<"/"<<sum<<",����Ϊq:"<<prop_q<<endl;
	return prop_q;
}


