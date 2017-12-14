/*
 * gf.c
 *
 *  Created on: Dec 8, 2017
 *      Author: vader
 */

#include "gf_6.h"

gf gf_multiplication(gf x, gf y) {
	gf a1, b1, a2, b2, a3, b3;

	a1 = (x >> gf_extd_sf);
	b1 = (x & (u_val - 1));
	a2 = (y >> gf_extd_sf);
	b2 = (y & (u_val - 1));

	gf tmp = gf_mult_fast_6(a1, a2);

	gf_p tmp1 = (a1 << 16) | a2;
	gf_p tmp2 = (b2 << 16) | b1;
	//gf result_1 = gf_mult_fast_6(a1, b2);
	//gf result = gf_mult_fast_6(b1, a2);
	gf_p r = gf_mult_parallel_4(tmp1, tmp2);
	a3 = gf_mult_fast_6(tmp, 36) ^ r ^ (r >> 16);

	//a3 = gf_mult_fast_6(tmp, 36) ^ result ^ result_1;

	//printf("temp_result %"PRIu16"\n", temp_result);
	//printf("a3 %"PRIu16"\n", a3);

	gf_p tmp11 = (tmp << 16) | b1;
	gf_p tmp12 = (2 << 16) | b2;
	gf_p r1 = gf_mult_parallel_4(tmp11, tmp12);
	b3 = (r1 >> 16) ^ r1;

	//b3 = gf_mult_fast_6(tmp, 2) ^ gf_mult_fast_6(b1, b2);

	//printf("temp_result %"PRIu16"\n", temp_result);
	//printf("b3 %"PRIu16"\n", b3);

	gf tmp_1 = (a3 << gf_extd_sf) ^ b3;

	return tmp_1;
}

gf gf_sq_6(gf in) {
	const uint32_t B[] = { 0x55555555, 0x33333333, 0x0F0F0F0F, 0x00FF00FF };

	uint32_t x = in;
	uint32_t t;

	x = (x | (x << 8)) & B[3];
	x = (x | (x << 4)) & B[2];
	x = (x | (x << 2)) & B[1];
	x = (x | (x << 1)) & B[0];

	t = x & 0xFFF;
	x ^= t >> 6;
	x ^= ((t >> 5) & 0x3E);

	x = x & 0x3F;

	return x & ((1 << 6) - 1);
}

/*inline gf gf_mult_fast(gf in0, gf in1) {
 uint64_t i, tmp, t0 = in0, t1 = in1;

 //Multiplication
 tmp = t0 * (t1 & 1);

 for (i = 1; i < 6; i++)
 tmp ^= (t0 * (t1 & (1 << i)));

 //reduction
 tmp = tmp & 0x7FF; // tmp & 0000 0111 1111 1111
 tmp = tmp ^ (tmp >> 6);
 tmp = tmp ^ ((tmp >> 5) & 0x1E);
 tmp = tmp & 0x3F;
 return tmp;
 }*/

void vec64_mul(uint64_t *result, uint64_t *in0, uint64_t *in1) {
	int value = (2 * 6) - 1;
	int i, j;
	uint64_t r[value];
	for (i = 0; i < value; i++)
		r[i] = 0;
	for (i = 0; i < 6; i++)
		for (j = 0; j < 6; j++)
			r[i + j] ^= r[i + j] ^ (in0[i] & in1[j]);
	for (i = value - 1; i >= 6; i--) {
		r[i - 6] ^= r[i];
		r[i - 5] ^= r[i];
		/*r[i - 12] ^= r[i];
		 r[i - 13] ^= r[i];*/
	}
	for (i = 0; i < 6; i++)
		result[i] = r[i];
}

void gf_dump(gf a) {
	int i;

	printf("(");
	printf("%d", a & 1);
	for (i = 1; i < 7; i++)
		printf(" + %d * a^%d", (a >> i) & 1, i);
	printf(")");
	printf("\n");
	//sleep(1);
}

void gf_dump_12(gf a) {
	int i;

	printf("(");
	printf("%d", a & 1);
	for (i = 1; i < 12; i++)
		printf(" + %d * a^%d", (a >> i) & 1, i);
	printf(")");
	printf("\n");
	//sleep(1);
}

void gf_dump_p(gf* a) {
	gf_dump(a[0]);
	gf_dump(a[1]);
	//sleep(1);
}

void GF_dump(gf *p) {
	int i;

	printf("(");
	gf_dump(p[0]);

	for (i = 1; i < 6; i++) {
		printf(" + ");
		gf_dump(p[i]);
		printf(" * x^%d", i);
	}

	printf(")");
}

