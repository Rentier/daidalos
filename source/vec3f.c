#include "vec3f.h"

#include <stdio.h>

vec3f vec3f_add(const vec3f v1, const vec3f v2) {
	vec3f result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return result;
}

vec3f vec3f_sadd(const vec3f v1, const float r) {
	vec3f result;

	result.x = v1.x + r;
	result.y = v1.y + r;
	result.z = v1.z + r;

	return result;
}

vec3f vec3f_sub(const vec3f v1, const vec3f v2) {
	vec3f result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;

	return result;
}

vec3f vec3f_ssub(const vec3f v1, const float r) {
	vec3f result;

	result.x = v1.x - r;
	result.y = v1.y - r;
	result.z = v1.z - r;

	return result;
}

vec3f vec3f_mult(const vec3f v1, const vec3f v2) {
	vec3f result;

	result.x = v1.x * v2.x;
	result.y = v1.y * v2.y;
	result.z = v1.z * v2.z;


	return result;
}

vec3f vec3f_smult(const vec3f v1, const float r) {
	vec3f result;

	result.x = v1.x * r;
	result.y = v1.y * r;
	result.z = v1.z * r;

	return result;
}

float vec3f_dot(const vec3f v1, const vec3f v2) {
	float result;

	result = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;

	return result;
}

vec3f vec3f_cross(const vec3f v1, const vec3f v2) {
	vec3f result;

	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;

	return result;
}

vec3f vec3f_neg(const vec3f v) {
	vec3f result;

	result.x = - v.x;
	result.y = - v.y;
	result.z = - v.z;

	return result;
}

void vec3f_print(const vec3f v) {
	printf("(%.2f, %.2f, %.2f)\n", v.x, v.y, v.z);
}
