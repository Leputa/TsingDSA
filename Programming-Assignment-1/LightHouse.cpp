#include<iostream>
#include<stdio.h>
using namespace std;

const long MAX=4000005;

const int MAXBUFFER = 1 << 20;

struct fastio {
	char inbuf[MAXBUFFER];
	char outbuf[MAXBUFFER];
	fastio() {
		setvbuf(stdin, inbuf, _IOFBF, MAXBUFFER);
		setvbuf(stdout, outbuf, _IOFBF, MAXBUFFER);
	}
}io;


struct Point{
	long x;
	long y;
};

Point point[MAX];
long pointY[MAX];
long cnt=0;

void qsort(Point ps[], int l, int r)
{
	if (l < r)
	{
		int i = l, j = r;
		Point tmp;
		tmp.x = ps[i].x;
		tmp.y = ps[i].y;
		int key = ps[i].x;

		while (i < j)
		{
			while (i < j && key < ps[j].x) --j;			
			ps[i].x = ps[j].x;
			ps[i].y = ps[j].y;
			while (i < j && ps[i].x < key) ++i;
			ps[j].x = ps[i].x;
			ps[j].y = ps[i].y;
		}

		ps[i].x = tmp.x;
		ps[i].y = tmp.y;
		
		qsort(ps, l, i - 1);
		qsort(ps, i + 1, r);
	}
}

void invInside(long*y,int lo,int hi);
void invBetween(long*y,int lo,int mid,int hi);

int main(){
	int n;
	cin>>n;
	
	long x,y;
	for(int i=0;i<n;i++){
		scanf("%ld %ld",&x,&y);
		point[i].x=x;
		point[i].y=y;
	}
	
	qsort(point,0,n-1);
	
	for(int i=0;i<n;i++)
		pointY[i]=point[i].y;
		
	invInside(pointY,0,n-1);
	cout<<cnt<<endl;
}

void invBetween(long*y,int lo,int mid,int hi){
	long aux[hi];
	for(int i=lo;i<=hi;i++)
		aux[i]=y[i];
	int i=lo,j=mid+1;
	int k=lo;
	while(i<=mid&&j<=hi){
		if(aux[i]<=aux[j]){
			y[k++]=aux[i++];
			cnt+=hi-j+1;
		}
		else{
			y[k++]=aux[j++];
		}
	}
	while(j<=hi){
		y[k++]=aux[j++];
	}
	while(i<=mid){
		y[k++]=aux[i++];
	}
}

void invInside(long*y,int lo,int hi){
	if(lo>=hi)
		return; 
	int mid=(hi+lo)/2;
	invInside(y,lo,mid);
	invInside(y,mid+1,hi);
	invBetween(y,lo,mid,hi);	
}


 



