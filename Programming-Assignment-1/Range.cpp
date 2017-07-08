/*#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

int main(){
	int n,m;
	cin>>n>>m;
	if(n<0||n>1e5||m<0||m>1e5)
		return -1;
	vector<double>v(n);
	for(int i=0;i<n;i++){
		double tmp;
		cin>>tmp;
		v[i]=tmp;
	}
	for(int i=0;i<m;i++){
		int count=0;
		double a,b;
		cin>>a>>b;
		if(a>b)
			return -1;
		for(int j=0;j<n;j++){
			if((v[j]>a&&v[j]<b)||fabs(v[j]-a)<1e-7||fabs(v[j]-b)<1e-7)
				count++;
		}
		cout<<count<<endl;
	}
	return 0;
}
*/
#include<iostream>
#include<cmath>
#include<stdio.h>
using namespace std;

const int N=5*1e5+5;
int v[N];

int Position(int low,int high,int e){
	while(low<high){
		int mid=(low+high)/2;
		if(v[mid]>e)
			high=mid;
		else
			low=mid+1;
	}
	low--;
	return low;    
}

void QuickSort(int lo, int hi){
    if(lo<hi){
        int i=lo,j=hi,x=v[lo];
        while(i<j){
            while(i < j && v[j] >= x)
                --j;
            if(i < j)
                v[i++] = v[j];
            while(i < j && v[i] < x)
                ++i;
            if(i < j)
                v[j--] = v[i];
        }
        v[i] = x;
        QuickSort(lo,i-1);
        QuickSort(i+1,hi);  
    }
}


int main(){
	int n,m;
	cin>>n>>m;
	for(int i=0;i<n;i++)
		scanf("%d",&v[i]);
	QuickSort(0,n-1);
	for(int i=0;i<m;i++){
		int a,b;
		scanf("%d %d",&a,&b);
		int p1=Position(0,n,a);
		while(v[p1]==a&&p1>=0)
			p1--;
		int p2=Position(0,n,b);
		int count=p2-p1;
		printf("%d\n",count);
	}
	return 0;
}
