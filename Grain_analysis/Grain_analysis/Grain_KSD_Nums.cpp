/*
	Created by Kevin Lee 2013/6/16
	enumerated all possible ISD with Hamming weight <= d
	calculating all possible KSD.
*/


#include "head.h"

/*������
d:�����ֵ����������
N_array:��ÿһ����֣���Ҫö�ٵ�״̬��Ŀ ��һ�����飬��Բ�ͬ��dѡȡ��ͬ��С��sampling size
*/

void cal_all_KSD_construct_table(u32 d, u64* N_array){
	//���Դ�Ľ���
	srand((unsigned)time(NULL));
	rc4_setup();
	//����Ŀ¼��������������Զ�����Ŀ¼
	cout<<"----------------------d:"<<d<<"--------------------"<<endl;
	string part="(d,l)_(";
	string curr_DIR=DIR+part+int_2_string(d)+","+int_2_string(KSLen)+")\\";
	make_DIR(curr_DIR);
	for(int i=1;i<=d;i++){
		cout<<"��ʼ���������ֺ�������Ϊ:"<<i<<"�����."<<endl;
		combination_for_search_imp(LEN*8,i,N_array[i-1],curr_DIR);
		cout<<"�����ֺ�������Ϊ:"<<i<<"������Ѿ��������.\n\n"<<endl;
	}
}
//��������⣬��ӡ��1~n������ѡȡk�����������,����������k��n�Ƚ�С��ʱ���ٶȿ�,�ǵݹ�ʵ��
//���ڸ��������ֵ�����
void combination_for_search_imp(u32 n,u32 k,u64 N, string curr_DIR){
	//����һ���������������������Ľ���
	long long counter=0;
	//Ԥ�ȴ洢һ�����Ƶ��ܵļ�����
	long long t_Sum[5]={160,12720,669920,26294360,820384032};
	//��ʼ���������
	u32 *v=new u32[k+1]();
	for(int i=0;i<k;i++){
		v[i]=i+1;
	}
	v[k]=n+1;
	//�ó�ʼ��������������Գ�ʼ����Ͻ��в���
	genOutput_diff_imp(k,v,N,curr_DIR);
	//���C(n,k)��������ϣ�Ϊÿ������趨����״̬��֣���ִ��grain�õ�������
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
			//���ݵ�ǰ��Ͻ��в���
			for(int j=i+1;j<k;j++)
				v[j]=v[j-1]+1;
			genOutput_diff_imp(k,v,N,curr_DIR);
			
			return true;
		}
	}
	return false;
}
void genOutput_diff_imp(u32 k,u32 *v,u64 N,string curr_DIR){
	//��ʼ�� ������Ϊȫ0 �������ǰ���v�Ķ�Ӧ������״̬���
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
	//cout<<"��Ӧ�����֣�"<<ends;
	//	for(int j=0;j<20;j++){
	//			printf("%x ",ISD[j]);
	//}
	//cout<<endl;
	
	map<string,u32> counter;
	//���ѡ��N��״̬
	for(int i=0;i<N;i++){
		//cout<<"\n------Sample:"<<i+1<<"------"<<endl;
		u8 rnd_state_1[LEN];
		for(int j=0;j<LEN;j++){
			rnd_state_1[j]=rc4();
		}
		//���ݲ��λ�ã��õ���һ��״̬rud_state_2
		u8 rnd_state_2[LEN];
		for(int j=0;j<LEN;j++){
			rnd_state_2[j]=rnd_state_1[j]^ISD[j];
		}
		//�ֱ����Grain�� ���l������Կ��
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
	//��counter�ж�Ӧ�������ִ洢��һ��txt�ļ��У��������ֵ�16���Ʊ�ʾ��������
	//��ISDת����16����+����ò�ֵı������洢��txt��һ�С�
	//���ͳ��ÿ��txt�����������ƽ����������Ҳ��ÿ��table�Ĵ�С���������ֵ�16������������
	string inputDiffStr=char2HexString(ISD,LEN);
	//���ȱ���counter�е�����������
	map<string,u32>::iterator beg=counter.begin();
	map<string,u32>::iterator end=counter.end();
	for(;beg!=end;beg++){
		string outDiff=beg->first;
		u32 occurs=beg->second;
		double occur_prop=(double)occurs/N;
		//�������ֺͱ��� д�뵽��outDiff������txt�С�
		string fileName=outDiff+".txt";
		//����outDiff��1���ֽڽ������� ������������ݸ�8�����������ͬ���ļ�����
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