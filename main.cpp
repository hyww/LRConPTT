#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <cmath>

using namespace std;

typedef struct timing{
	int m;
	double s;
}Timing;

struct timingComp{
	bool operator()(const Timing& a, const Timing& b){
		if(a.m<b.m)return true;
		else if(a.m==b.m){
			return a.s<b.s;
		}
		else return false;
	}
};

int main(int argc, char **argv){
	ifstream fin;
	string strin;
	string artist, title, album, by;
	char *tok, *stok;
	char *cstrin, *lyric;
	vector<Timing> timings;
	Timing ttmp, ttmp2;
	map<Timing, char *, timingComp> lyrics;
	double gap;
	double inacc=0;
	double total=0;
	
	fin.open(argv[1]);
	while(getline(fin, strin)){	//read in lrc file line by line
		
		if(strin[0]!='['){
			//cout<<"not"<<strin[0]<<endl;
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
				//cout<<"timing "<<ttmp.m<<" "<<ttmp.s<<endl;
			}
			else{
				lyric=new char[strlen(strstr(strin.c_str(), tok))+1];
				strcpy(lyric, strstr(strin.c_str(), tok));
				for(vector<Timing>::iterator i=timings.begin();i!=timings.end();i++){
					lyrics.insert(pair<Timing, char *>(*i, lyric));
				}
				timings.clear();
				//cout<<"lyric "<<lyric<<endl;
				break;
			}
			
			tok=strtok(NULL, "[]");
		}
		if(timings.size()>0){
			lyric=new char[1];
			strcpy(lyric, "");
			for(vector<Timing>::iterator i=timings.begin();i!=timings.end();i++){
				lyrics.insert(pair<Timing, char *>(*i, lyric));
			}
			timings.clear();
		}
		
	}
	
	for(map<Timing, char *, timingComp>::iterator i=lyrics.begin();i!=lyrics.end();i++){
		if(i==lyrics.begin()){
			ttmp=i->first;
			gap=(ttmp.m)*60+ttmp.s;
			inacc+=round(gap*10)/10-gap;
			gap=round(gap*10)/10;
			if(inacc>0){
				gap-=0.1;
				inacc-=0.1;
			}
			else if(inacc<0){
				gap+=0.1;
				inacc+=0.1;
			}
			total+=gap;
			printf("^L%.1lf\n\n", gap);
			lyric=i->second;
			continue;
		}
		gap=(i->first.m-ttmp.m)*60+i->first.s-ttmp.s;
		
		inacc+=round(gap*10)/10-gap;
		gap=round(gap*10)/10;
		if(inacc>0){
			gap-=0.1;
			inacc-=0.1;
		}
		else if(inacc<0){
			gap+=0.1;
			inacc+=0.1;
		}
		total+=gap;
		printf("^L%.1lf\n", gap);
		printf("%s\n", lyric);
		ttmp=i->first;
		lyric=i->second;
		
		//cout<<i->first.m<<" "<<i->first.s<<" "<<i->second<<endl;
	}
	
	printf("^LE\n");
	printf("%s\n", lyric);
	cout<<total<<" "<<inacc<<endl;
	
	//system("pause");
	return 0;
}
