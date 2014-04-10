#include "head.h"

//kevin edit. for byte to string (hex)
string char2HexString(u8* bArray,u32 bLen){
	string res="";
	for(int i=0;i<bLen;i++){
		u8 high=bArray[i]>>4;
		u8 low=bArray[i]&(0x0f);
		if(high<10)
			res+='0'+high;
		else
			res+='a'+(high-10);
		if(low<10)
			res+='0'+low;
		else
			res+='a'+(low-10);
	}
	return res;
}

string int_2_string(int a){
	string out;
	stringstream ss;
	ss<<a;
	ss>>out;
	return out;
}

//如果某个路径不存在，则创建这个路径
void make_DIR(string curr_DIR){
	char *tag;
	for(tag=(char*)curr_DIR.c_str();*tag;tag++){
		if(*tag=='\\'){
			char buf[1024],path[1024];
			strcpy(buf,curr_DIR.c_str());
			buf[strlen(curr_DIR.c_str())-strlen(tag)+1]=NULL;
			strcpy(path,buf);
			if(access(path,6)==-1)
				mkdir(path);
		}
	}
}