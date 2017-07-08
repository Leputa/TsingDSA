#include<stdio.h>
#include<string.h>
#include<stdlib.h>
const int SZ = 1<<20;   
struct fastio{   //fast io
    char inbuf[SZ];  
    char outbuf[SZ];  
    fastio(){  
        setvbuf(stdin,inbuf,_IOFBF,SZ);  
        setvbuf(stdout,outbuf,_IOFBF,SZ);  
    }  
}io;

struct ListNode{
	char color;
	ListNode *pre;
	ListNode *next;
}*head,*tail;

const int N=20005;
char sequence[N];
char str[2*N];

void create(ListNode* head,ListNode* tail,int length);
ListNode* Insert(ListNode*head,ListNode* tail,int m,char a);
bool remove(ListNode*p);

int main(){
//	freopen("input.txt", "r", stdin);
	head=(ListNode*)malloc(sizeof(ListNode));
	tail=(ListNode*)malloc(sizeof(ListNode));
	head->next=tail;
	tail->pre=head;
	gets(str);
	int len=strlen(str);
	if(len>0)
		create(head,tail,len);
	int n;
	scanf("%d", &n);
	for(int i=0;i<n;i++){
		int m;
		char a; 
		scanf("%d ",&m);
		a=getchar();
		ListNode*p=Insert(head,tail,m,a);
		if(remove(p))
		{
			len++;
			strcpy(sequence, str+m);
			sequence[len-m] = '\0';
			strcpy(str+m+1, sequence);
			str[m] = a;
			str[len] = '\0';
		}
		else
		{
			len = 0;
			if(head->next==tail){
				str[0] = '\0';
				printf("-");
			}
			else{
				len = 0;
				ListNode *q=head->next;
				while(q!=tail){
					str[len++]=q->color;
					q=q->next;
				}	
				str[len]='\0';
			}
		}
		printf("%s\n", str);
	}
	return 0;
}

void create(ListNode* head,ListNode* tail,int length){
	for(int i=length-1;i>=0;i--){
		ListNode *tmp=(ListNode*)malloc(sizeof(ListNode));
		tmp->color=str[i];
		tmp->next=head->next;
		tmp->pre=head;
		head->next->pre=tmp;
		head->next=tmp;			
		if(i == length-1) tail->pre = tmp;
	}
}


ListNode* Insert(ListNode*head,ListNode* tail,int m,char a){
	ListNode *p=head;
	for(int i=0;i<m;i++){
		p=p->next;
	}
	ListNode *tmp=(ListNode*)malloc(sizeof(ListNode));
	tmp->color=a;
	tmp->next=p->next;
	tmp->pre=p;
	p->next->pre=tmp;
	p->next=tmp;	
	return tmp;
}

bool remove(ListNode*p){
	char ch = p->color;
	ListNode* q1=p, *q2=p->next;
	ListNode* p1=p;
	ListNode* p2=p->next;
	int count = 0;
	while(p1!=head&&p1->color == ch) p1 = p1->pre, count++;
	while(p2!=tail&&p2->color == ch) p2 = p2->next, count++;
	while(count>=3)
	{	
		q1=p1;
		q2=p2;
		count = 0;
		ch = p1->color;
		while(p1!=head&&p1->color == ch ) p1 = p1->pre, count++;
		while(p2!=tail&&p2->color == ch) p2 = p2->next, count++;
	}
	q1->next = q2;
	q2->pre = q1;
	return q1 == p;
}
