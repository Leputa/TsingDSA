#include <stdio.h>
#include <malloc.h>
#include "temperature.h"


const int MAX=50005;

const int MAXBUFFER = 1 << 20;

struct fastio {
	char inbuf[MAXBUFFER];
	char outbuf[MAXBUFFER];
	fastio() {
		setvbuf(stdin, inbuf, _IOFBF, MAXBUFFER);
		setvbuf(stdout, outbuf, _IOFBF, MAXBUFFER);
	}
}io;

template <typename T>
class Stack{
	private:
		int num=0;
		T stack[MAX]; 	
	public:
		void push(T a){
			num++;
			stack[num]=a;
			return;
		}
		T pop(){
			return stack[num--];
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

class Node{
	public:
		Node *lChild;
		Node *rChild;
		int x,y;
		int temp;
		int tag;              //≈º∫·∆Ê ˙ 
		Node(){
			lChild=NULL;
			rChild=NULL;
		}
}nodes[50000];

Stack<Node*>S;

class KdTree{
	public:
		Node *node;
		Node *root;
		int num=0;
		
		KdTree(){
			node=(Node*)malloc(sizeof(Node));
			root=(Node*)malloc(sizeof(Node));
		}
		
		void create(Node*node){
			root->x=node->x;
			root->y=node->y;
			root->temp=node->temp;
			root->tag=0;
			root->lChild=NULL;
			root->rChild=NULL;	
			num++;
		}
		
		void insert(Node *node){
			Node *currentNode=(Node*)malloc(sizeof(Node));
			currentNode->lChild=NULL;
			currentNode->rChild=NULL;
			Node *tmpNode=root;
			Node *par;            //º«¬º∏∏Ω⁄µ„ 
			while(true){
				par=tmpNode;
				if((par->tag)%2==0){
					if(node->y>=tmpNode->y){
						if(tmpNode->rChild)
							tmpNode=tmpNode->rChild;
						else{
							tmpNode->rChild=currentNode;
							break;
						}
					}	
					else{
						if(tmpNode->lChild)
							tmpNode=tmpNode->lChild;
						else{
							tmpNode->lChild=currentNode;
							break;
						}
					}
						
				}
				if((par->tag)%2==1){
					if(node->x>=tmpNode->x){
						if(tmpNode->rChild)
							tmpNode=tmpNode->rChild;
						else{
							tmpNode->rChild=currentNode;
							break;
						}
					}	
					else{
						if(tmpNode->lChild)
							tmpNode=tmpNode->lChild;
						else{
							tmpNode->lChild=currentNode;
							break;
						}
					}
						
				}
			}

			currentNode->tag=(par->tag)+1;
			currentNode->x=node->x;
			currentNode->y=node->y;
			currentNode->temp=node->temp;
			num++;
		}
		
		int search(int x1,int y1,int x2,int y2){
			long long sum=0;
			long long number=0;
			Node *tmpNode=root;
			while(tmpNode||!S.isEmpty()){
				if(tmpNode){
					if(tmpNode->x>=x1&&tmpNode->x<=x2&&tmpNode->y>=y1&&tmpNode->y<=y2){
						number++;
						sum+=tmpNode->temp;
						S.push(tmpNode);
						tmpNode=tmpNode->lChild;
					}
					else if(tmpNode->x>=x1&&tmpNode->x<=x2&&(tmpNode->tag)%2==1){
						S.push(tmpNode);
						tmpNode=tmpNode->lChild;
					}
					else if(tmpNode->y>=y1&&tmpNode->y<=y2&&(tmpNode->tag)%2==0){
						S.push(tmpNode);
						tmpNode=tmpNode->lChild;
					}
					else if((tmpNode->tag)%2==1&&tmpNode->x>x2)
						tmpNode=tmpNode->lChild;
					else if((tmpNode->tag)%2==1&&tmpNode->x<x1)
						tmpNode=tmpNode->rChild;
					else if((tmpNode->tag)%2==0&&tmpNode->y>y2)
						tmpNode=tmpNode->lChild;
					else if((tmpNode->tag)%2==0&&tmpNode->y<y1)
						tmpNode=tmpNode->rChild;	
				}
				else{
					tmpNode=S.pop();
					tmpNode=tmpNode->rChild;
				}
			}
			if(number==0)
				return 0;
			else
				return sum/number;
		}
};

/*
int main(){
	KdTree station;
	int n,m;
	scanf("%d %d",&n,&m);
	for(int i=0;i<n;i++){
		int x,y,temp;
		scanf("%d %d %d",&station.node->x,&station.node->y,&station.node->temp);
		if(i==0)
			station.create(station.node);
		else
			station.insert(station.node);	
	}
	for(int i=0;i<m;i++){
		int x1,y1,x2,y2;
		scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
		station.search(x1,y1,x2,y2);
		
	}	
	return 0;	
}
*/


int main(){
	KdTree station;
	int n=GetNumOfStation();
	int addx,addy,addt;
	for(int i=0;i<n;i++){
		int *x,*y,*temp;
		x=&addx,y=&addy,temp=&addt;
		GetStationInfo(i,x,y,temp);
		station.node->x=*x;
		station.node->y=*y;
		station.node->temp=*temp;
		if(i==0)
			station.create(station.node);
		else
			station.insert(station.node);
	}
	int *x1,*y1,*x2,*y2;
	int addx1,addx2,addy1,addy2;
	x1=&addx1;
	y1=&addy1;
	x2=&addx2;
	y2=&addy2;
	int x11,y11,x22,y22;
	while(GetQuery(x1, y1, x2, y2)){
		x11=*x1;
		y11=*y1;
		x22=*x2;
		y22=*y2;
		int temp=station.search(x11,y11,x22,y22);
		Response(temp);
	}
	return 0;
}
