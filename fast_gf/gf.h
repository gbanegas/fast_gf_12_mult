/*
 * gf.h
 *
 *  Created on: Dec 8, 2017
 *      Author: vader
 */

#ifndef GF_H_
#define GF_H_
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>

#include "param.h"

#include "types_def.h"

//#define primitive_element_in_f_q 36

#define primitive_element_in_f_q 2

extern gf gf_multiplication(gf a, gf b);

extern gf gf_mult_fast(gf a, gf b);

#endif /* GF_H_ */
