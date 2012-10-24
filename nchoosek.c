#include <stdio.h>

#ifndef USE_GMP
#define USE_GMP 0
#endif

#if USE_GMP == 1
#include <gmp.h>
#endif

#if USE_GMP == 0
unsigned long long nchoosek_native(unsigned long long n, 
				   unsigned long long k) {
	// special cases
	if(k < 0) {
		return 0;
	}
	if(k > n) {
		return 0;
	}
	// symmetry
	if(k > n - k) {
		k = n - k;
	}
	if(k > n / 2) {
		k = n - k;
	}

	unsigned long long c = 1;
	unsigned long long result = 1;
	for(;c <= k; c++) {
		result *= n--;
		result /= c;
	}

	return result;
}
#else
void nchoosek_gmp(mpz_t result, mpz_t n, mpz_t k) {
	// special cases
	if(mpz_cmp_ui(k, 0) < 0) {
		mpz_set_ui(result, 0);
		return;
	}
	if(mpz_cmp(k, n) > 0) {
		mpz_set_ui(result, 0);
		return;
	}
	mpz_t c;
	mpz_init_set_ui(c, 0);
	// symmetry
	mpz_sub(c, n, k);
	if(mpz_cmp(k, c) > 0) {
		mpz_set(k, c);
	}
	mpz_cdiv_q_ui(c, n, 2);
	if(mpz_cmp(k, c) > 0) {
		mpz_sub(k, n, k);
	}

	mpz_set_ui(result, 1);
	mpz_set_ui(c, 1);
	for(; mpz_cmp(c, k) <= 0; mpz_add_ui(c, c, 1)) {
		mpz_mul(result, result, n);
		mpz_sub_ui(n, n, 1);
		mpz_tdiv_q(result, result, c);
	}
	mpz_clear(c);
}
#endif

int main(int argc, char** argv) {
	if(argc < 3) {
		fprintf(stderr, "usage: %s <n> <k>\n", argv[0]);
		return 1;
	}

#if USE_GMP == 0
	unsigned long long n = atoll(argv[1]);
	unsigned long long k = atoll(argv[2]);
	printf("calculating nchoosek(%li, %li) (native)... \n", n, k);

	printf("result: %li\n", nchoosek_native(n, k));
#else
	mpz_t n;
	mpz_t k;
	mpz_t result;
	mpz_init(result);
	mpz_init_set_str(n, argv[1], 10);
	mpz_init_set_str(k, argv[2], 10);

	gmp_printf("calculating nchoosek(%Zd, %Zd) (GMP)... \n", n, k);

	nchoosek_gmp(result, n, k);

	gmp_printf("result: %Zd\n", result); 

	mpz_clear(n);
	mpz_clear(k);
	mpz_clear(result);
#endif
		
	return 0;
}
