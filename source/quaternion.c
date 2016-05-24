#include "quaternion.h"

#include <stdio.h>

quaternion_t quaternion_add(const quaternion_t q1, const quaternion_t q2) {
	quaternion_t result;
	result.a = q1.a + q2.a;
	result.b = q1.b + q2.b;
	result.c = q1.c + q2.c;
	result.d = q1.d + q2.d;
	return result;
}

quaternion_t quaternion_mult(const quaternion_t q1, const quaternion_t q2) {
	quaternion_t result;

	result.a = q1.a*q2.a - q1.b*q2.b - q1.c*q2.c - q1.d*q2.d;
	result.b = q1.a*q2.b + q1.b*q2.a + q1.c*q2.d - q1.d*q2.c;
	result.c = q1.a*q2.c - q1.b*q2.d + q1.c*q2.a + q1.d*q2.b;
	result.d = q1.a*q2.d + q1.b*q2.c - q1.c*q2.b + q1.d*q2.a;

	return result;
}


void quaternion_print(const quaternion_t q) {
	printf("{%.2f, %.2f, %.2f, %.2f}", q.a, q.b, q.c, q.d);
}
