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
	int count=1;
	char c=p->color;
	ListNode*tmp1=p;
	if(tmp1->next!=tail){
		if(c==tmp1->next->color){
			count++;
			tmp1=tmp1->next;
			if(tmp1->next!=tail){
				if(c==tmp1->next->color){
					count++;
					tmp1=tmp1->next;
				}	
			}
		}
	}
	ListNode*tmp2=p;
	if(tmp2->pre!=head){
		if(c==tmp2->pre->color){
			count++;
			tmp2=tmp2->pre;
			if(tmp2->pre!=head){
				if(c==tmp2->pre->color){
					count++;
					tmp2=tmp2->pre;
				}
			}
		}	
	}
	ListNode* p1=tmp1->next;
	ListNode* p2=tmp2->pre;
	if(count>=3){
		tmp2->pre->next=tmp1->next;
		tmp1->next->pre=tmp2->pre;
		while(tmp1!=tmp2){
			tmp2=tmp2->next;
			delete tmp2->pre;
		}
		delete tmp2;
		if(p1!=tail)
			remove(p1);
		if(p2!=head)
			remove(p2);
	}
}

//会有两个爆栈 
//尾递归不自动优化吗23333 
