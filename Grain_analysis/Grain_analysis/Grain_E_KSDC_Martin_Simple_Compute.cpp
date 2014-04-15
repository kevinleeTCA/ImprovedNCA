/*
	Created by Kevin Lee 2014/4/11
	Given ISDs with hamming weight at most d, calculate its E-KSDC and record the average number
	of fixed positions in the keystream
*/


#include "head.h"

/*
  d: ISD hamming weight
  num_ISD: number of ISDs enumerated

  this function calculte the average number of fixed positions in E-KSDC
*/

void average_fixed_pos_E_KSDC(u32 d,u32 num_ISD){
	double average_E_KSDC_pos_num=0.0;
	for(int D=1;D<=num_ISD;D++){
		//randomly induce the differences to d positions.  NFSR:0~79，LFSR:80~159
		u32* pos=new u32[d]();
		for(int j=0;j<d;j++){
			//pos[j]=rc4() % 160;
			//pos[j]=(rc4() % 80)+80;				//只给LFSR中引入差分
				//pos[j]=(rc4() % 80);				//只给NFSR中引入差分
			//pos[j]=(rc4() % 40)+80;			//只給LFSR的左半部分引入差分 80-119
			pos[j]=(rc4() % 40)+120;			//只给LFSR的右半部分引入差分 120-159
			while(isExist(pos,j,pos[j]))		//to ensure the non-duplicated positions
				//pos[j]=rc4() % 160;
				//pos[j]=(rc4() % 80)+80;			//只给LFSR中引入差分
				//pos[j]=(rc4() % 80);				//只给NFSR中引入差分
			//pos[j]=(rc4() % 40)+80;			//只給LFSR的左半部分引入差分 80-119
			pos[j]=(rc4() % 40)+120;			//只给LFSR的右半部分引入差分 120-159
		}
		// induce the differece to selected position
		u8 ISD[LEN];
		for(int j=0;j<LEN;j++){
			ISD[j]=0;
		}
		for(int j=0;j<d;j++){
			u32 p=posIdx(pos[j]);
			u32 r=rotateIdx(pos[j]);
			ISD[p]=ISD[p]^(1<<r);
		}
		// generate E-KSDC and record the number of fixed positions
		ECRYPT_ctx ctx;
		ctx.keysize=80;
		ctx.ivsize=64;
		ECRYPT_grain_state_load(&ctx,ISD);
		u8 E_KSDC_Array[KSLen*8];
		for(int j=0;j<KSLen*8;j++){
			E_KSDC_Array[j]=ENCRYPT_grain_E_KSDC(&ctx);
			if(E_KSDC_Array[j]<2)
				average_E_KSDC_pos_num++;
		}
	}
	average_E_KSDC_pos_num=(double)average_E_KSDC_pos_num/num_ISD;
	cout<<"The average fixed pos(d,l):("
			<<d<<","<<KSLen*8<<",) is "<<setprecision(3)<<average_E_KSDC_pos_num<<endl;
}



/*
  d: ISD hamming weight
  num_ISD: number of ISDs enumerated
  pos: position indexes of active bit    NFSR:0~79，LFSR:80~159
  this function calculte the E-KSDC sequence and record the number of fixed positions, give a specific ISD
*/

void E_KSDC_fixed_pos_with_given_ISD(u32 d,u32 *pos){
	//induce differences
	u32 E_KSDC_pos_num=0;
	u8 ISD[LEN];
	for(int j=0;j<LEN;j++){
		ISD[j]=0;
	}
	for(int j=0;j<d;j++){
		u32 p=posIdx(pos[j]);
		u32 r=rotateIdx(pos[j]);
		ISD[p]=ISD[p]^(1<<r);
	}
	// generate E-KSDC and record the number of fixed positions, 
	// and generate the 0,1,* sequences
	// and record the position of active, non-active, pending bits
	vector<int> act_pos;
	vector<int> non_act_pos;
	vector<int> pending_pos;
	ECRYPT_ctx ctx;
	ctx.keysize=80;
	ctx.ivsize=64;
	ECRYPT_grain_state_load(&ctx,ISD);
	u8 E_KSDC_Array[KSLen*8];
	string E_KSDC="";
	for(int j=0;j<KSLen*8;j++){
		E_KSDC_Array[j]=ENCRYPT_grain_E_KSDC(&ctx);
		if(E_KSDC_Array[j]==0){
			E_KSDC.append("0");
			E_KSDC_pos_num++;
			non_act_pos.push_back(j+1);
		}else if(E_KSDC_Array[j]==1){
			E_KSDC.append("1");
			E_KSDC_pos_num++;
			act_pos.push_back(j+1);
		}else{
			E_KSDC.append("*");
			pending_pos.push_back(j+1);
		}
	}
	cout<<"E-KSDC:"<<E_KSDC;
	cout<<"\nNumber of fixed positions："<<E_KSDC_pos_num;
	cout<<"\nAbsolute active positions(Y):{";
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
	beg=pending_pos.begin();
	end=pending_pos.end();
	for(;beg!=end;beg++){
		cout<<*beg<<",";
	}
	cout<<"}"<<endl;

}



/*
  d: ISD hamming weight
  pos: position indexes of active bit    NFSR:0~79，LFSR:80~159
  this function return the E-KSDC sequence , give a specific ISD
*/
string E_KSDC_seq_with_given_ISD(u32 d,u32 *pos){
	//induce differences
	//u32 E_KSDC_pos_num=0;
	u8 ISD[LEN];
	for(int j=0;j<LEN;j++){
		ISD[j]=0;
	}
	for(int j=0;j<d;j++){
		u32 p=posIdx(pos[j]);
		u32 r=rotateIdx(pos[j]);
		ISD[p]=ISD[p]^(1<<r);
	}
	// generate E-KSDC and record the number of fixed positions, 
	// and generate the 0,1,* sequences
	// and record the position of active, non-active, pending bits
	//vector<int> act_pos;
	//vector<int> non_act_pos;
	//vector<int> pending_pos;
	ECRYPT_ctx ctx;
	ctx.keysize=80;
	ctx.ivsize=64;
	ECRYPT_grain_state_load(&ctx,ISD);
	u8 E_KSDC_Array[KSLen*8];
	string E_KSDC="";
	for(int j=0;j<KSLen*8;j++){
		E_KSDC_Array[j]=ENCRYPT_grain_E_KSDC(&ctx);
		if(E_KSDC_Array[j]==0){
			E_KSDC.append("0");
			//E_KSDC_pos_num++;
			//non_act_pos.push_back(j+1);
		}else if(E_KSDC_Array[j]==1){
			E_KSDC.append("1");
			//E_KSDC_pos_num++;
			//act_pos.push_back(j+1);
		}else{
			E_KSDC.append("*");
			//pending_pos.push_back(j+1);
		}
	}
	return E_KSDC;
	/*cout<<"E-KSDC:"<<E_KSDC;
	cout<<"\nNumber of fixed positions："<<E_KSDC_pos_num;
	cout<<"\nAbsolute active positions(Y):{";
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
	beg=pending_pos.begin();
	end=pending_pos.end();
	for(;beg!=end;beg++){
		cout<<*beg<<",";
	}
	cout<<"}"<<endl;*/

}