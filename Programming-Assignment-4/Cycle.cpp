#include <stdio.h>
#include <cstring>

const int MAXBUFFER = 1 << 22;
struct fastio {
	char inbuf[MAXBUFFER];
	char outbuf[MAXBUFFER];
	fastio() {
		setvbuf(stdin, inbuf, _IOFBF, MAXBUFFER);
		setvbuf(stdout, outbuf, _IOFBF, MAXBUFFER);
	}
}io;

const int MAX=100005;
char s1[MAX];
char s2[MAX*2];      //s1为模式串P，s2为文本串T 

int *buildNext(int len){
	int j=0;
	int *N=new int[len];
	int t=N[0]=-1;
	while(j<len-1)
		if(0>t||s1[j]==s1[t]){
			j++;
			t++;
			N[j]=s1[j]!=s1[t]?t:N[t];  //实测并没有更快 
		}
		else
			t=N[t];
	return N;
}

int match(int len){   
	int *next=buildNext(len);   
	int i=0,j=0;              // i--s2;j--s1
	while(i<2*len&&j<len)
		if(j<0||s1[j]==s2[i]){
			i++;
			j++;
		} 
		else
			j=next[j];
	delete []next;
	return i-j;	 
}

int main(){
	int cnt=0;
	while(scanf("%s %s",s1,s2)!=EOF){
		cnt++;
		if(cnt>5000)
			break;
		int len=strlen(s1);
		if(len!=strlen(s2)){
			printf("NO\n");
			continue;
		}
		for(int i=len,j=0;i<2*len;i++,j++)
			s2[i]=s2[j];									
		int ans=match(len);
		if(ans<len)
			printf("YES\n");
		else 
			printf("NO\n");
	}
	return 0;
}
