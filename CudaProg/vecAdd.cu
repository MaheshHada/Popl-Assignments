#include <stdio.h>

__global__ void vecAdd(float *A,float *B,float *C) {
	int i = threadIdx.x + blockDim.x*blockIdx.x;
	C[i] = A[i] + B[i];
}

int main() {
	int N;
	scanf("%d",&N);
	float *h_a = (float*)malloc(N*sizeof(float));
	float *h_b = (float*)malloc(N*sizeof(float));
	float *h_c = (float*)malloc(N*sizeof(float));
	float *d_a,*d_b,*d_c;
	cudaMalloc((void**)&d_a,N*sizeof(float));
	cudaMalloc((void**)&d_b,N*sizeof(float));
	cudaMalloc((void**)&d_c,N*sizeof(float));
	int i;
	for(i=0;i<N;i++) {
		*(h_a + i) = (float)rand()/(float)(RAND_MAX/100);
	}
	for(i=0;i<N;i++) {
		*(h_b + i) = (float)rand()/(float)(RAND_MAX/100);
	}
	for(i=0;i<N;i++) {
		*(h_c + i) = (float)rand()/(float)(RAND_MAX/100);
	}
	cudaMemcpy(d_a,h_a,N*sizeof(float),cudaMemcpyHostToDevice);
	cudaMemcpy(d_b,h_b,N*sizeof(float),cudaMemcpyHostToDevice);
	cudaMemset(d_c,0,N*sizeof(float));
	vecAdd<<<N/256,256>>>(d_a,d_b,d_c);
	cudaMemcpy(h_c,d_c,N*sizeof(float),cudaMemcpyDeviceToHost);
	for(i=0;i<N;i++) {
		printf("%d ",h_a[i]);
	}
	printf("\n");
	for(i=0;i<N;i++) {
		printf("%d ",h_b[i]);
	}
	printf("\n");
	for(i=0;i<N;i++) {
		printf("%d ",h_c[i]);
	}
	printf("\n");
	free(h_a);
	free(h_b);
	free(h_c);
	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_c);
	return 0;
}