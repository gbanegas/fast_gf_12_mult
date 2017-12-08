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
#include "cycles.h"
#include "gf_6.h"
#include "gf.h"

int main() {

	/*	gf_init_antilog_sf();
	 gf_init_log_sf();
	 for(int i = 0; i < 65; i++){
	 printf("%"PRIu16"-", gf_a_sf[i]);
	 printf("%"PRIu16"\n", gf_l_sf[i]);

	 }*/

	gf a = 5;
	gf b = 34;

	printf("%"PRIu16" * %"PRIu16 "\n", a, b);
	uint64_t initial_enc = rdtsc();
	//gf temp = gf_multiplication(a, b);
	gf temp = gf_mult_fast(a, b);
	uint64_t final_enc = rdtsc();
	uint64_t enc_count = final_enc - initial_enc;
	printf("mult cycles: %" PRId64 "\n", enc_count);
	printf("%"PRIu16"\n", temp);

	a = 1026;
	b = 2050;

	printf("%"PRIu16" * %"PRIu16 "\n", a, b);
	initial_enc = rdtsc();
	//gf temp = gf_multiplication(a, b);
	temp = gf_multiplication(a, b);
	final_enc = rdtsc();
	enc_count = final_enc - initial_enc;
	printf("mult cycles: %" PRId64 "\n", enc_count);
	printf("%"PRIu16"\n", temp);

	printf("%"PRIu16" * %"PRIu16 "\n", a, b);
	initial_enc = rdtsc();
	//gf temp = gf_multiplication(a, b);
	temp = gf_mult(a, b);
	final_enc = rdtsc();
	enc_count = final_enc - initial_enc;
	printf("mult cycles: %" PRId64 "\n", enc_count);
	printf("%"PRIu16"\n", temp);

	/*initial_enc = rdtsc();
	 temp = gf_sq(a);
	 final_enc = rdtsc();
	 enc_count = final_enc - initial_enc;
	 printf("sq cycles: %" PRId64 "\n", enc_count);
	 printf("%"PRIu16"\n", temp);

	 initial_enc = rdtsc();
	 temp = gf_inv(a);
	 final_enc = rdtsc();
	 enc_count = final_enc - initial_enc;
	 printf("inv cycles: %" PRId64 "\n", enc_count);
	 printf("%"PRIu16"\n", temp);*/

	return 0;
}
