#include <stdio.h>
#include <cstring>

const int MAX=600005;

const int MAXBUFFER = 1 << 20;

struct fastio {
	char inbuf[MAXBUFFER];
	char outbuf[MAXBUFFER];
	fastio() {
		setvbuf(stdin, inbuf, _IOFBF, MAXBUFFER);
		setvbuf(stdout, outbuf, _IOFBF, MAXBUFFER);
	}
}io;

//���ƶ���ʽ�������ϳ��ģ���̫���Ǹ�λ������
int hashcode(char s[]){
	int h=0;
	for(int len=strlen(s),i=0;i<len;i++){
		//h=(h<<5)|(h>>27);
		h+=(int)s[i]*i;
	}
	return (int) h;
} 

struct Hash{
	Hash *next;    //������ 
	char str[45];
	Hash(){
		next=NULL;
	}
}*s[MAX];

char str[45];

int Search(int add){
	int cnt=0;
	Hash *p=s[add];
	while(p->next!=NULL){
		p=p->next;
		if(strcmp(p->str,str)==0)  //�����ַ������
			cnt++;
		if(cnt==2)                 //�Ѿ����޳��� 
			return cnt;  
	}
	Hash *temp=new Hash;
	strcpy(temp->str,str);
	p->next=temp;
	return cnt;
}

int main(){
	int n;
	scanf("%d",&n);
	int i,j;
	for(int i=0;i<MAX;i++)
		s[i]=new Hash;
	for(int i=0;i<n;i++){
		scanf("%s",str);
		int add=hashcode(str);//�����Խ�磿 
		int cnt=Search(add);
		if(cnt==1)
			puts(str);	
	}
	return 0;
}















