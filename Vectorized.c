#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <intrin.h>

#define AVX 1

#if AVX
#define OFFSET_F 8
#define ALIGNMENT 32
#else
#define OFFSET_F 4
#define ALIGNMENT 16
#endif

// Single Threaded Array Addition FLOATs
int main() {
	int i;
	float* A = NULL;
	float* B = NULL;
	float* C = NULL;
	int result = 1;
	const int elements = 52428800;
	time_t start, end;

	//Array creation
	size_t datasize = sizeof(float) * elements;
	A = (float*)_aligned_malloc(datasize,ALIGNMENT);
	B = (float*)_aligned_malloc(datasize,ALIGNMENT);
	C = (float*)_aligned_malloc(datasize,ALIGNMENT);

	//Array initialization (Normally you would get this from a file)
	for (i = 0; i < elements; i++) {
		A[i] = (float)i;
		B[i] = (float)i;
	}

#if AVX
	//Vector vars
	__m256 vA, vB, vC;

	start = clock();
	//This loop can be optimized using Intrinsics
	for (i = 0; i < elements / OFFSET_F; i++)
	{
		vA = _mm256_load_ps(A + (i * OFFSET_F));
		vB = _mm256_load_ps(B + (i * OFFSET_F));
		vC = _mm256_add_ps(vA, vB);
		_mm256_store_ps(C + (i * OFFSET_F), vC);
	}
	end = clock();
#else 
	//Vector vars
	__m128 vA, vB, vC;

	start = clock();
	//This loop can be optimized using Intrinsics
	for (i = 0; i < elements / OFFSET_F; i++)
	{
		vA = _mm_load_ps(A + (i * OFFSET_F));
		vB = _mm_load_ps(B + (i * OFFSET_F));
		vC = _mm_add_ps(vA, vB);
		_mm_store_ps(C + (i * OFFSET_F), vC);
	}
	end = clock();
#endif

	//Validation
	for (i = 0; i < elements; i++) {
		if (C[i] != i + i) {
			result = 0;
			break;
		}
	}

	//Print first 10 results
	for (i = 0; i < 10; i++) {
		printf("C[%d]=%10.2lf\n", i, C[i]);
	}

	if (result) {
		printf("Results verified!!! (%ld)\n", (long)(end - start));
	}
	else {
		printf("Wrong results!!!\n");
	}

	//Memory deallocation
	_aligned_free(A);
	_aligned_free(B);
	_aligned_free(C);

	return 0;
}