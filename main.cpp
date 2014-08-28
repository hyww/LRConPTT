#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>


using namespace std;

typedef struct timing{
	int m;
	double s;
}Timing;

int main(int argc, char **argv){
	ifstream fin;
	string strin;
	string artist, title, album, by;
	char *tok, *stok;
	char *cstrin, *lyric;
	vector<Timing> timings;
	Timing ttmp;
	
	fin.open(argv[1]);
	while(getline(fin, strin)){	//read in lrc file line by line
		timings.clear();
		if(strin[0]!='['){
			cout<<"not"<<strin[0]<<endl;
			continue;
		}
		cstrin=new char[strin.size()+1];
		strcpy(cstrin, strin.c_str());
		//cout<<cstrin<<endl;
		tok=strtok(cstrin, "[]");
		while(tok!=NULL){
			//cout<<tok<<endl;
			if((strlen(tok)==8&&tok[2]==':'&&tok[5]=='.')||(strlen(tok)==5&&tok[2]==':')){
				ttmp.m=atoi(tok);
				ttmp.s=atof(tok+3);
				timings.push_back(ttmp);
				cout<<"timing "<<ttmp.m<<" "<<ttmp.s<<endl;
			}
			else{
				lyric=new char[strlen(strstr(strin.c_str(), tok))+1];
				strcpy(lyric, strstr(strin.c_str(), tok));
				
				
				cout<<"lyric "<<lyric<<endl;
				break;
			}
			
			tok=strtok(NULL, "[]");
		}
		
		
		
	}
	system("pause");
	return 0;
}
