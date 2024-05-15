#include <limits.h>
#include <math.h>
#include <time.h>
#include <xmmintrin.h>

inline static float Q_rsqrt(float number)
{
  long i;
  float x2, y;
  const float threehalfs = 1.5F;

  x2 = number * 0.5F;
  y  = number;
  i  = * ( long * ) &y;                       // evil floating point bit level hacking
  i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
  y  = * ( float * ) &i;
  y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
  // y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

  return y;
}

// ./a.out  0.18s user 0.01s system 99% cpu 0.192 total                                                                                                                                                                                                              195ms 
// ./a.out  0.16s user 0.00s system 99% cpu 0.163 total                                                                                                                                                                                                               166ms 
// ./a.out  0.16s user 0.00s system 99% cpu 0.165 total                                                                                                                                                                                                               168ms 
// ./a.out  0.16s user 0.00s system 99% cpu 0.166 total                                                                                                                                                                                                               169ms 
// ./a.out  0.19s user 0.00s system 99% cpu 0.190 total                                                                                                                                                                                                                193ms 
// ./a.out  0.16s user 0.00s system 99% cpu 0.164 total                                                                                                                                                                                                                 167ms 
// ./a.out  0.17s user 0.00s system 99% cpu 0.174 total                                                                                                                                                                                                                  177ms 
// ./a.out  0.16s user 0.00s system 99% cpu 0.162 total                                                                                                                                                                                                                   165ms 
// ./a.out  0.16s user 0.00s system 99% cpu 0.163 total
#include <immintrin.h>

// __m256 multiply_and_add(__m256 a, __m256 b, __m256 c)
// {
// 	return _mm256_fmadd_ps(a, b, c);
// }
// typedef float __m256 __attribute__ ((__vector_size__ (32), __aligned__(32)));
// __extension__ (__m256){ __h, __g, __f, __e, __d, __c, __b, __a };

#include <stdio.h>

int main(void)
{
	float f = (float)10000000;
	// long i;
	// float y;

	while (f > 0)
	{
		// Q_rsqrt(f);
		
		// y  = f;
		// i  = * ( long * ) &y;                       // evil floating point bit level hacking
		// i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
		// y  = * ( float * ) &i;
		// y  = y * ( 1.5f - ( f * 0.5F * y * y ) ); 
		(void)(1. / sqrtf(f));
		f--;
	}
	__m128 b, c;

	// a = _mm256_set1_ps(0.2);
	// b = _mm256_set1_ps(0.5);
	//  __m256 result = _mm256_sub_ps(a, b);
	__m128	a = _mm_set1_ps(0.2);

	c = _mm_set1_ps(0.1);
	b = c;
	c[1] = 2;
	c[2] = 2;
	c[0] = 2;
	c[3] = 0;
	// a = __extension__ (__m256){ 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5 };
	for(int i = 0; i < 4; i++)
	{
		printf("%f, ",a[i]);
	}
	printf("\n");
	for(int i = 0; i < 4; i++)
	{
		printf("%f, ",b[i]);
	}
	printf("\n");
	for(int i = 0; i < 4; i++)
	{
		printf("%f, ",c[i]);
	}
	int t = _mm_movemask_ps( _mm_cmp_ps(c, a, _MM_CMPINT_GT));
	printf("\n%d\n", t);
	if ((t ^ 0b1000) == 7)
		printf("\noyoyoyooy\n");

	// t_point2 e, r;
	
	// e.hex = 412;
	// r.hex = 21;
	// t_point2 t = {e.hex + r.hex};

}