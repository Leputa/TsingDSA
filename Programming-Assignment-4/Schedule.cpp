#include <stdio.h>
#include <cstring>
#include <iostream>
using namespace std;

const int MAX=4000005;
const long long  boundary=(long long) 1<<32;


const int MAXBUFFER = 1 << 22;
struct fastio {
	char inbuf[MAXBUFFER];
	char outbuf[MAXBUFFER];
	fastio() {
		setvbuf(stdin, inbuf, _IOFBF, MAXBUFFER);
		setvbuf(stdout, outbuf, _IOFBF, MAXBUFFER);
	}
}io;


class task{
	public:
		long long prior;
		char str[10];
		bool operator< (const task &a)const{
			return prior<a.prior||prior==a.prior&&strcmp(str,a.str)<0;
		}
		bool operator > (const task &a)const{
			return prior>a.prior||prior==a.prior&&strcmp(str,a.str)>0;
		}
		bool operator == (const task &a)const{
			return prior==a.prior&&strcmp(str,a.str)==0;
		}
}a[MAX];

task min(task a,task b){
	if(a.prior<b.prior)
		return a;
	else if(a.prior==b.prior&&strcmp(a.str,b.str)<0)
		return a;
	else 
		return b;
}

void percolateUp(int i){  //上滤
	 int j=i;
	 while(j!=1&&a[j]<a[j/2]){
	 	swap(a[j],a[j/2]);
	 	j/=2;
	 }	
}

void percolateDown(int i){  //下溢 
	int j=1;
	while(j*2+1<=i&&a[j]>min(a[j*2],a[j*2+1])){
		//task b=min(a[j*2],a[j*2+1]);
		//exchange(a[j],b);
		if(min(a[j*2],a[j*2+1])==a[j*2]){
			swap(a[j],a[j*2]);
			j=j*2;
		}	
		else{
			swap(a[j],a[j*2+1]);
			j=j*2+1;
		} 
	}
	if(j*2==i&&a[j]>a[i])
		swap(a[i],a[j]);
}

int main(){
	int n,m;
	scanf ("%d %d",&n,&m);
	int i;
	for(i=1;i<=n;i++){                         //从1开始编号，左右孩纸方便些 
		scanf("%lld %s",&a[i].prior,a[i].str);
		percolateUp(i);
	}
	i--;
	for(int k=1;i&&k<=m;k++){
		if(a[1].prior>=boundary)
			break;
		puts(a[1].str);
		a[1].prior*=2;
		percolateDown(i);
	}
	return 0;
}
