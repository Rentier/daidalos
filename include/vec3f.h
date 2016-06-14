#ifndef RMR_VEC3F_H_
#define RMR_VEC3F_H_

typedef struct {
	float x;
	float y;
	float z;
} vec3f ;

vec3f vec3f_add(const vec3f v1, const vec3f v2);
vec3f vec3f_sadd(const vec3f v1, const float r);

vec3f vec3f_sub(const vec3f v1, const vec3f v2);
vec3f vec3f_ssub(const vec3f v1, const float r);

vec3f vec3f_mult(const vec3f v1, const vec3f v2);
vec3f vec3f_smult(const vec3f v1, const float r);

float vec3f_dot(const vec3f v1, const vec3f v2);
vec3f vec3f_cross(const vec3f v1, const vec3f v2);

vec3f vec3f_neg(const vec3f v);

void vec3f_print(const vec3f v);


#endif /* RMR_INCLUDE_VEC3F_H_ */
