// Requires C++17 to manage alignment properly
#include <iostream>
#include <ctime>
#include <intrin.h>
using namespace std;

#define OFFSET 8

void main()
{
	const int elements = 52428800;
	time_t start, end;
	bool result = true;

	struct alignas(alignof(__m256)) floatP {
		float f[OFFSET];
	};

	unique_ptr<floatP[]> A(make_unique<floatP[]>(elements / OFFSET));
	unique_ptr<floatP[]> B(make_unique<floatP[]>(elements / OFFSET));
	unique_ptr<floatP[]> C(make_unique<floatP[]>(elements / OFFSET));

	for (int i = 0; i < elements / OFFSET; i++)
	{
		for (int j = 0; j < OFFSET; j++)
		{
			A[i].f[j] = static_cast<float>(i * OFFSET + j);
			B[i].f[j] = static_cast<float>(i * OFFSET + j);
		}
	}

	__m256 vA, vB, vC;

	start = clock();
	for (int i = 0; i < elements / OFFSET; i++)
	{
		vA = _mm256_load_ps(A[i].f);
		vB = _mm256_load_ps(B[i].f);
		vC = _mm256_add_ps(vA, vB);
		_mm256_store_ps(C[i].f, vC);
	}
	end = clock();

	// Validation
	int j = 0;
	while (result && j < elements/OFFSET )
	{
		int k = 0;
		for (auto& i : C[j].f)
		{
			if (i != j*8 + j*8 + k + k)
			{
				result = false;
				break;
			}
			k++;
		}
		j++;
	}

	cout.precision(2);
	for (int i = 0; i < 8; i++)
		cout << "C[" << i << "] = " << C[0].f[i] << endl;

	if (result)
		cout << "Results verified!!! : " << static_cast<long> (end - start) << endl;
	else
		cout << "Wrong results!!! : " << endl;
}
