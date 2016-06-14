#ifndef RMR_QUATERNION_H_
#define RMR_QUATERNION_H_

typedef struct {
	float a;
	float b;
	float c;
	float d;
} quaternion;

quaternion quaternion_add(const quaternion q1, const quaternion q2);
quaternion quaternion_mult(const quaternion q1, const quaternion q2);

void quaternion_print(const quaternion quaternion);


#endif /* RMR_QUATERNION_H_ */
