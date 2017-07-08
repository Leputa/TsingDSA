#include <stdio.h>
#include <iostream>
using namespace std;

const int Max=3200005;


class Stack{
	private:
		int num=0;
		int stack[Max]; 	
	public:
		void push(int a){
			num++;
			stack[num]=a;
			return;
		}
		void pop(){
			num--;
		}
		int gettop(){
			return stack[num];
		}
		int size(){
			return num;
		}
		bool isEmpty(){
			if(num==0)
				return true;
			else 
				return false;
		}
};

int tag[Max];
Stack s;

int main(){
	int n,m;
	cin>>n>>m;

	int k=1;
	int j=1;
	int flag=0;
	for(int i=0;i<n;i++){
		int tmp;
		scanf("%d",&tmp);
		while(tmp>=k){
			s.push(k);
			tag[j]=1;
			k++; 
			j++;
		}
		if(s.size()>m){
			flag=1;
			break;
		}
		while(!s.isEmpty()&&s.gettop()==tmp){
			s.pop();
			tag[j]=0;
			j++;
		}
	}
	//cout<<s.size()<<endl;
	//cout<<j<<endl;
	if(flag==1)
		printf("No\n");
	else if(s.size()==0){
		for(int i=1;i<j;i++){
			if(tag[i]==1)
				printf("push\n");
			if(tag[i]==0)
				printf("pop\n");
		}
	}
	else
		printf("No\n");
	return 0;
}


















