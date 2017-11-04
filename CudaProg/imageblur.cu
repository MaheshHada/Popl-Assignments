#include <stdio.h>
#include <stdlib.h>

#define N1 3	
#define N2 3

__global__ void blur_kernel(int *image_d,float *filter_d,int *blurimage_d) {
	int row = threadIdx.x + blockDim.x*blockIdx.x;
	int col = threadIdx.y + blockDim.y*blockIdx.y;
	if(row < N1 && col < N2) {
		int i,j;
		float sum = 0,wsum = 0;
		for(int i=0;i<3;i++) {
			for(j=0;j<3;j++) {
				wsum += *(filter + i*3 + j);
			}
		}
		int k = 0,l = 0;
		for(i=row-1;i<=row+1;i++) {
			for(j=col-1;j<=col+1;j++) {
				if(i >= 0 && j >= 0 && i < N1 && j < N2) {
					sum += ((*(image_d + i*N2+j)) * (*(filter_d + k*3+l)));
				}
				l++;
			}
			k++;
		}
		blurimage_d[row*N2+col] = (int)(sum/wsum);
	}
}


int main() {
	//int N1,N2;
	//scanf("%d %d",&N1,&N2);
	int *image_h = (int*)malloc(N1*N2*sizeof(int));
	int i,j;
	for(i=0;i<N1;i++) {
		for(j=0;j<N2;j++) {
			*(image_h + i*N2 + j) = rand()%256;
		}
	}
	float f[3][3] = {{1.0,2.0,1.0},{2.0,3.0,2.0},{1.0,2.0,1.0}};
	float *filter_h = (float*)malloc(3*3*sizeof(float));
	for(i=0;i<3;i++) {
		for(j=0;j<3;j++) {
			*(filter_h + i*3 + j) = f[i][j];
		}
	} 
	for(i=0;i<N1;i++) {
		for(j=0;j<N2;j++) {
			printf("%d ",*(image_h + i*N2 + j));
		}
		printf("\n");	
	}
	printf("\n");
	for(i=0;i<3;i++) {
		for(j=0;j<3;j++) {
			printf("%d ",*(filter_h + i*3 + j));
		}
		printf("\n");	
	}
	printf("\n");
	int *image_d,*blurimage_d;
	float *filter_d;
	cudaMalloc((void**)&image_d,N1*N2*sizeof(int));
	cudaMalloc((void**)&filter_d,3*3*sizeof(float));
	cudaMalloc((void**)&blurimage_d,N1*N2*sizeof(int));
	cudaMemcpy(image_d,image_h,N1*N2*sizeof(int),cudaMemcpyHostToDevice);
	cudaMemcpy(filter_d,filter_h,3*3*sizeof(float),cudaMemcpyHostToDevice);
	dim3 grid(N2,N1);
	dim3 block(1,1);
	blur_kernel<<<grid,block>>>(image_d,filter_d,blurimage_d);
	cudaMemcpy(image_h,blurimage_d,N1*N2*sizeof(int),cudaMemcpyDeviceToHost);
	for(i=0;i<N1;i++) {
		for(j=0;j<N2;j++) {
			printf("%d ",*(image_h + i*N2 + j));
		}
		printf("\n");	
	}
	printf("\n");
	free(image_h);
	free(filter_h);
	cudaFree(image_d);
	cudaFree(filter_d);
	cudaFree(blurimage_d);
}
