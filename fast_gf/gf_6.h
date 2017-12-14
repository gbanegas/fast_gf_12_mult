/*
 * gf.h
 *
 *  Created on: Dec 8, 2017
 *      Author: vader
 */

#ifndef GF_6_H_
#define GF_6_H_
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "param.h"

#include "types_def.h"

#define primitive_element_in_f_q 36

static inline gf gf_mult_fast_6(gf in0, gf in1) {
	uint32_t i, tmp, t0 = in0, t1 = in1;

	//Multiplication
	tmp = t0 * (t1 & 1);

	for (i = 1; i < 7; i++)
		tmp ^= (t0 * (t1 & (1 << i)));

	//reduction
	tmp = tmp & 0xFFF; // tmp & 0000 1111 1111 1111
	tmp = tmp ^ (tmp >> 6);
	tmp = tmp ^ ((tmp >> 5) & 0x3E);
	tmp = tmp & 0x3F;
	return tmp;
}

static inline gf_p gf_mult_parallel_4(gf_p a, gf_p b) {
	uint64_t i, tmp, t0 = a, t1 = b;

	//Multiplication
	tmp = ( (t0 & 0x7F) * (t1 & 0x1) ) | ( (t0 & 0x7F0000) * (t1 & 0x10000));

	for (i = 1; i < 7; i++) {
		uint64_t ta = ((t0 & 0x7F) * (t1 & (1 << i)));
		uint64_t tb = ((t0 & 0x7F0000) * (t1 & (1 << (i + 16))));
		tmp ^=  ((ta ) | (tb));
	}

	//reduction
	tmp = tmp & 0xFFF00000FFF; // tmp & 0000 1111 1111 1111
	tmp = tmp ^ (tmp >> 6);
	tmp = tmp ^ ((tmp >> 5) & 0x3E0000003E);
	tmp = (tmp | (tmp >> 16));
	tmp = tmp & 0x3F003F;
	return tmp;
}

gf gf_multiplication(gf x, gf y);

void gf_dump(gf p);
void gf_dump_12(gf a);

void gf_dump_p(gf*p);

void GF_dump(gf *pol);

#endif /* GF_6_H_ */
