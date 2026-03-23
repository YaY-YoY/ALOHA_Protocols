#include <stdio.h>
#include <math.h>

#define a 16807.0
#define b 2147483647.0

#define TOTAL_SNED 1000000

void s_exp(double *seed, double mean_t, double *inter_t) {
	long i;
	double x;
	if (mean_t == 0) *inter_t = 0.0;
	else {
		x = a * *seed;
		i = x / b;
		*seed = x - b * i;
		x = *seed / b;
		*inter_t = - mean_t * log(x);
	}
}
int main() {
	double seed = 1491701989.0;
	float G = 0.5;
	double mean_time = 1.0/G;
	double inter_time;
	double total = 0.0;
	int i;
	int check = 0;
	int success = 0;
	for (i=0; i<TOTAL_SNED*G; i++) {
		s_exp(&seed, mean_time, &inter_time);
		total += inter_time;
		if (inter_time >= 1) {
			if (check == 0)
			check = 1;
			else if(check == 1)
			success++;
		}
		else check = 0;
	}
	printf("G:%f, Success=%f", G, (double)success/total);
	return 0;
}
