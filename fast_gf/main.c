/*
 * main.c
 *
 *  Created on: Dec 6, 2017
 *      Author: vader
 */

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include "param.h"
#include "types_def.h"
#include "cpucycles.h"
#include "gf_6.h"
#include "gf.h"

long long todstart;
long long todend;
long long cpustart;
long long cpuend;
long long t[1001];

int start() {
	int i;
	for (i = 0; i <= 1000; ++i) {
		t[i] = cpucycles();
	}
	for (i = 0; i < 1000; ++i)
		if (t[i] > t[i + 1]) {
			fprintf(stderr, "t[%d] = %lld\n", i, t[i]);
			fprintf(stderr, "t[%d] = %lld\n", i + 1, t[i + 1]);
			fprintf(stderr, "cpucycles_persecond() = %lld\n",
			cpucycles_persecond());
			return 100;
		}
	if (t[0] == t[1000]) {
		fprintf(stderr, "t[%d] = %lld\n", 0, t[0]);
		fprintf(stderr, "t[%d] = %lld\n", 1000, t[1000]);
		fprintf(stderr, "cpucycles_persecond() = %lld\n",
		cpucycles_persecond());
		return 100;
	}
	if (cpucycles_persecond() <= 0) {
		fprintf(stderr, "cpucycles_persecond() = %lld\n",
		cpucycles_persecond());
		return 100;
	}
	return 0;
}
int main() {

	int i;
	if (start()) {
		return 100;
	}
	gf a = 4095; //160
	gf b = 4095;
	gf temp_1; //2232 & 499
	gf_dump_12(a);
	temp_1 = gf_mult((a), b);
	gf temp_2;
	temp_2 = gf_multiplication((a), b);

	gf_dump_12(temp_1);
	gf_dump_12(temp_2);
	printf("%"PRIu16"\n", temp_1);
	printf("%"PRIu16"\n", temp_2);
	/*for (i = 0; i < 10; i++) {
	 temp_1 = gf_mult((a << i), b);
	 temp_2 = gf_multiplication((a << i), b);
	 if (temp_1 != temp_2) {
	 gf_dump((a << i));
	 printf("%"PRIu16"\n", (a << i));
	 printf("round: %d \n", i);
	 gf_dump(temp_1);
	 gf_dump(temp_2);
	 printf("%"PRIu16"\n", temp_1);
	 printf("%"PRIu16"\n", temp_2);

	 }

	 }*/
	/*for (i = 0; i <= 100; ++i) {
	 t[i] = cpucycles();
	 //gf_dump(a);
	 temp_2 = gf_multiplication(a, b);

	 }*/

	/*gf temp_2 = gf_multiplication(b, b);
	 printf("%"PRIu16"\n", temp);
	 printf("%"PRIu16"\n", temp_2);
	 gf_dump(temp);*/
	/*gf_dump(temp_2);
	 printf("%s", cpucycles_implementation);
	 printf("CPU Cycles per second: %lld \n", cpucycles_persecond());
	 printf(" %lld",
	 (long long) (((double) cpuend) * 1000000.0 / (double) todend));

	 for (i = 0; i < 100; ++i)
	 printf(" %lld", t[i + 1] - t[i]);
	 printf("\n");*/

	/*if (start()) {
	 return 100;
	 }
	 for (i = 0; i <= 100; ++i) {
	 t[i] = cpucycles();
	 //gf_dump(a);
	 gf_multiplication(a,b);

	 }
	 printf("%s", cpucycles_implementation);
	 printf("CPU Cycles per second: %lld \n", cpucycles_persecond());
	 printf(" %lld",
	 (long long) (((double) cpuend) * 1000000.0 / (double) todend));

	 for (i = 0; i < 100; ++i)
	 printf(" %lld", t[i + 1] - t[i]);
	 printf("\n");*/

	//printf("%"PRIu16"\n", temp);
	/*printf("%"PRIu16" * %"PRIu16 "\n", a, b);
	 gf_dump(a);
	 gf temp = gf_multiplication(a, b);
	 gf temp = gf_mult_fast(a, b);
	 printf("%"PRIu16"\n", temp);
	 gf_dump(temp);

	 a = 1026;
	 b = 2050;

	 printf("%"PRIu16" * %"PRIu16 "\n", a, b);
	 //gf temp = gf_multiplication(a, b);
	 temp = gf_multiplication(a, b);
	 printf("%"PRIu16"\n", temp);

	 printf("%"PRIu16" * %"PRIu16 "\n", a, b);
	 //gf temp = gf_multiplication(a, b);
	 temp = gf_mult(a, b);
	 printf("%"PRIu16"\n", temp);*/
	return 0;
}
