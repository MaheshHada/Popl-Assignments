#include <stdio.h>

__global__ void kernel(int *a) {
	int idx = blockIdx.x*blockDim.x + threadIdx.x;
	a[idx] = 7;
}

int main() {
	int dimx = 16;
	int num_bytes = dimx*sizeof(int);
	int *d_a = 0,*h_a = 0;	//device and host paraemters
	h_a = (int*)malloc(num_bytes);
	cudaMalloc((void**)&d_a,num_bytes);
	if( h_a == 0 || d_a == 0) {
		printf("Couldn't Allocate Memory\n");
		return 1;
	}
	cudaMemset(d_a,0,num_bytes);
	dim3 grid,block;
	block.x = 4;
	grid.x = dimx/block.x;
	kernel<<<grid,block>>>(d_a);
	cudaMemcpy(h_a,d_a,num_bytes,cudaMemcpyDeviceToHost);
	for(int i=0;i<dimx;i++) {
		printf("%d",h_a[i]);
	}
	printf("\n");
	free(h_a);
	cudaFree(d_a);
	return 0;
}