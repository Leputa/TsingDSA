#include<iostream>
#include<stdio.h>
#include<cstring>
using namespace std;

struct ListNode{
	char color;
	ListNode *pre;
	ListNode *next;
}*head,*tail;

const int N=20005;
char sequence[N];


void create(ListNode* head,ListNode* tail,int length);
ListNode* Insert(ListNode*head,ListNode* tail,int m,char a);
void remove(ListNode*p);

int main(){
	head=new ListNode;
	tail=new ListNode;
	head->next=tail;
	tail->pre=head;
	gets(sequence);
	int length=strlen(sequence);
	if(length>0)
		create(head,tail,length);
	int n;
	cin>>n;
	for(int i=0;i<n;i++){
		int m;
		char a;
		scanf("%d %c",&m,&a);
		ListNode*p=Insert(head,tail,m,a);
		remove(p);
		if(head->next==tail){
			cout<<"-"<<endl;
		}
		else{
			ListNode *q=head->next;
			while(q!=tail){
				printf("%c",q->color);
				q=q->next;
			}
			printf("\n");	
		}
	}
	return 0;
}

void create(ListNode* head,ListNode* tail,int length){
	for(int i=length-1;i>=0;i--){
		ListNode *tmp=new ListNode;
		tmp->color=sequence[i];
		tmp->next=head->next;
		tmp->pre=head;
		head->next->pre=tmp;
		head->next=tmp;			
	}
}


ListNode* Insert(ListNode*head,ListNode* tail,int m,char a){
	ListNode *p=head;
	for(int i=0;i<m;i++){
		p=p->next;
	}
	ListNode *tmp=new ListNode;
	tmp->color=a;
	tmp->next=p->next;
	tmp->pre=p;
	p->next->pre=tmp;
	p->next=tmp;	
	return tmp;
}

void remove(ListNode*p){
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
}

//╦дак╥г╣щ╧И 

