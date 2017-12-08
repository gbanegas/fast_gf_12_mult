/*
 * gf.c
 *
 *  Created on: Dec 8, 2017
 *      Author: vader
 */

#include "gf_6.h"

gf gf_multiplication(gf x, gf y) {
	gf a1, b1, a2, b2, a3, b3;

	a1 = x >> gf_extd_sf;
	b1 = x & (u_val - 1);
	a2 = y >> gf_extd_sf;
	b2 = y & (u_val - 1);

	a3 = gf_mult_fast(gf_mult_fast(a1, a2), primitive_element_in_f_q)
			^ gf_mult_fast(a1, b2) ^ gf_mult_fast(b1, a2);

	b3 = gf_mult_fast(gf_mult_fast(a1, a2), 2) ^ gf_mult_fast(b1, b2);

	return (a3 << gf_extd_sf) ^ b3;
}

gf gf_mult_fast(gf in0, gf in1) {
	uint64_t i, tmp, t0 = in0, t1 = in1;

	//Multiplication
	tmp = t0 * (t1 & 1);

	for (i = 1; i < 7; i++)
		tmp ^= (t0 * (t1 & (1 << i)));

	//reduction
	tmp = tmp & 0x7FF; // tmp & 0000 0111 1111 1111
	tmp = tmp ^ (tmp >> 6);
	tmp = tmp ^ ((tmp >> 5) & 0x1E);
	tmp = tmp & 0x3F;
	return tmp;
}
/*t1 = f2 * g2
 t2 = f2 * g0
 t3 = f2 * g1
 t4 = f0 * g2
 t5 = f1 * g2
 t6 = f1 * g1
 t7 = f1 * g0
 t8 = f0 * g1
 t9 = f0 * g0
 t10 = t8 + t7
 t11 = t6 + t4
 t12 = t11 + t2
 t13 = t5 + t3
 t14 = f5 * g5
 t15 = f5 * g3
 t16 = f5 * g4
 t17 = f3 * g5
 t18 = f4 * g5
 t19 = f4 * g4
 t20 = f4 * g3
 t21 = f3 * g4
 t22 = f3 * g3
 t23 = t21 + t20
 t24 = t19 + t17
 t25 = t24 + t15
 t26 = t18 + t16
 t27 = g0 + g3
 t28 = g1 + g4
 t29 = g2 + g5
 t30 = f0 + f3
 t31 = f1 + f4
 t32 = f2 + f5
 t33 = t32 * t29
 t34 = t32 * t27
 t35 = t32 * t28
 t36 = t30 * t29
 t37 = t31 * t29
 t38 = t31 * t28
 t39 = t31 * t27
 t40 = t30 * t28
 t41 = t30 * t27
 t42 = t40 + t39
 t43 = t38 + t36
 t44 = t43 + t34
 t45 = t37 + t35
 t46 = t13 + t22
 t47 = t1 + t23
 t48 = t41 + t46
 t49 = t42 + t47
 t50 = t44 + t25
 t51 = t45 + t26
 t52 = t33 + t14
 t53 = t48 + t9
 t54 = t49 + t10
 t55 = t50 + t12
 t56 = t51 + t46
 t57 = t52 + t47
 h0 = t9
 h1 = t10
 h2 = t12
 h3 = t53
 h4 = t54
 h5 = t55
 h6 = t56
 h7 = t57
 h8 = t25
 h9 = t26
 h10 = t14*/
