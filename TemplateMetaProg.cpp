#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#define SIZE 100000000
using namespace std;

template <class T>	
void Copy(T *A, T *B, int N, int n, int curr)
{

	if (n<=0 || N<=0)
		return;
	Copy(A,B,N-1,n-1,curr);
	B[curr+N-1] = A[curr+N-1];
};

template <class S>
void CM(S *A, S *B, int u, int n)
{
	int UNROLL = u;	
	int i=0;	
	clock_t begin = clock();	
	for(i=0; i<n; i+=UNROLL)
	{
		Copy(A,B,UNROLL,n,i);
	}
	clock_t end = clock();
	double elapsed = double(end - begin) / CLOCKS_PER_SEC;
    cout<<"Unroll Factor = "<<UNROLL<<" time elapsed = "<<elapsed*1000<<" ms"<<endl;	
};

void loop_over_copy(int A[], int B[])
{
	cout<<endl;
	for(int i=1;i<1024;i=i*2) {
		CM(A,B,i,SIZE);		
	}
}

int main()
{
	srand(time(0));
	int *A, *B;
	A = new int[SIZE];
	B = new int[SIZE];
	
	for(int i=0;i<SIZE;i++){
		A[i]=rand()%1000;
	}

	CM(A,B,1,SIZE);
	CM(A,B,5,SIZE);
	CM(A,B,15,SIZE);
	CM(A,B,35,SIZE);
	CM(A,B,40,SIZE);
	CM(A,B,77,SIZE);
	CM(A,B,94,SIZE);
	CM(A,B,133,SIZE);
	CM(A,B,225,SIZE);
	CM(A,B,297,SIZE);
	CM(A,B,512,SIZE);
	cout<<endl;
	loop_over_copy(A, B);

	return 0;

}
