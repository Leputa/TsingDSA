#include <stdio.h>
#include <malloc.h>

const int MaxN=10005;
const int MaxM=30005;

struct eNode{
	int adjvex;
	eNode *next;
};

struct vNode{
	int date;
	eNode *firstnext;
	int tag;  
	int visited;
};


template <typename T>
class Queue{
	private:
		T queue[MaxN];
		int head=0,tail=0;
	public:
		void EnQueue(T vertex){
			queue[tail]=vertex;
			tail++;
		}
		T DeQueue(){
			return queue[head++];
		}
		bool isEmpty(){
			return head==tail;
		}	
};

//template <typename T>
class Graph{
	public:
		vNode* Town[MaxN];
		void create(int n){
			for(int i=1;i<=n;i++){
				vNode* tmpNode=(vNode*)malloc(sizeof(vNode));
				tmpNode->date=i;
				tmpNode->firstnext=NULL;
				tmpNode->visited=0;
				tmpNode->tag=0;
				Town[i]=tmpNode;
			}
		}
		void insert(int i,int j){
			eNode* tmpNode=(eNode*)malloc(sizeof(eNode));
			tmpNode->adjvex=j;
			tmpNode->next=Town[i]->firstnext;
			Town[i]->firstnext=tmpNode;
		}
};

Graph graph;

int main(){
	int n,m;
	scanf("%d %d",&n,&m);
	graph.create(n);
	for(int k=0;k<m;k++){
		int i,j;
		scanf("%d %d",&i,&j);
		graph.insert(i,j);
		graph.insert(j,i);
	}
	for(int i=1;i<=n;i++){
		if(graph.Town[i]->visited==0){
				Queue<vNode*>Q;
				Q.EnQueue(graph.Town[i]);
				graph.Town[i]->visited=1;
				graph.Town[i]->tag=1;
				while(!Q.isEmpty()){
					vNode*tmp=Q.DeQueue();
					int parenttag=tmp->tag;
					eNode*edge=tmp->firstnext;
					while(edge){
						int j=edge->adjvex;
						if(graph.Town[j]->visited==0){
							graph.Town[j]->tag=-parenttag;
							Q.EnQueue(graph.Town[j]);
							graph.Town[j]->visited=1;
						}
						else{
							if(graph.Town[j]->tag==parenttag){
								printf("-1");
								return 0;
							}
						}
						edge=edge->next;
					}	
				}
		}
	}
	printf("1");
	return 0;
}
