/*#include <stdio.h>
#include <stdlib.h>


#define Max 100005    //空间直接炸了 

int dist[Max][Max];

void floyed(int n){
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			for(int k=1;k<=n;k++){
				if(dist[i][k]==1||dist[k][j]==1)
					continue;
				if(dist[i][j]==1||dist[i][k]+dist[k][j]<dist[i][j])
					dist[i][j]=dist[i][k]+dist[k][j];
			}		
}

int main(){
	int n,m;
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)
			dist[i][j]=1;
		dist[i][i]=0;	
	}	
	for(int k=1;k<=m;k++){
		int i,j;
		scanf("%d %d",&i,&j);
		dist[i][j]=-1;
	}
	floyed(n);
	int max=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(dist[i][j]<max)
				max=dist[i][j];
		}	
	}	
	printf("%d\n",abs(max)+1);
	return 0;
}*/


#include <stdio.h>
#include <malloc.h>

const int Max=1000005;

struct eNode{
	int adjvex;
	eNode *next;
};

struct vNode{
	int date;
	eNode *firstnext;
	int inDegree;
	int distance; //记录的vNode作为终点时的距离、 
};

class Graph{
	public:
		vNode* Town[Max];
		void create(int n){
			for(int i=1;i<=n;i++){
				vNode* tmpNode=(vNode*)malloc(sizeof(vNode));
				tmpNode->date=i;
				tmpNode->firstnext=NULL;
				tmpNode->inDegree=0;
				tmpNode->distance=1;
				Town[i]=tmpNode;
			}
		}
		void insert(int i,int j){
			eNode* tmpNode=(eNode*)malloc(sizeof(eNode));
			tmpNode->adjvex=j;
			tmpNode->next=Town[i]->firstnext;
			Town[i]->firstnext=tmpNode;
			Town[j]->inDegree++;
		}
};

Graph graph;

template <typename T>
class Stack{
	private:
		int num=0;
		T stack[Max]; 	
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

Stack <vNode*> S;

int main(){
	int n,m;
	scanf("%d %d",&n,&m);
	graph.create(n);
	for(int k=0;k<m;k++){
		int i,j;
		scanf("%d %d",&i,&j);
		graph.insert(i,j);
	}
	for(int i=1;i<=n;i++)
		if(graph.Town[i]->inDegree==0)
			S.push(graph.Town[i]);
	int maxdist=1;
	while(!S.isEmpty()){
		vNode* tmpNode=S.pop();
		eNode* edge=tmpNode->firstnext;
		while(edge){
			int j=edge->adjvex;
			if(tmpNode->distance+1>graph.Town[j]->distance)
				graph.Town[j]->distance=tmpNode->distance+1;
			if(graph.Town[j]->distance>maxdist)
				maxdist=graph.Town[j]->distance;
			graph.Town[j]->inDegree--;
			if(graph.Town[j]->inDegree==0)
				S.push(graph.Town[j]);
			edge=edge->next;
		}
	}
	printf("%d",maxdist);
	return 0;
}


