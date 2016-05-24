#ifndef RMR_QUATERNION_H_
#define RMR_QUATERNION_H_

typedef struct {
	float a;
	float b;
	float c;
	float d;
} quaternion_t ;

quaternion_t quaternion_add(const quaternion_t q1, const quaternion_t q2);
quaternion_t quaternion_mult(const quaternion_t q1, const quaternion_t q2);


void quaternion_print(const quaternion_t quaternion);


#endif /* RMR_QUATERNION_H_ */
