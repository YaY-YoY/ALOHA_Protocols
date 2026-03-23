#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define A 16807.0
#define B 2147483647.0

#define DEVICE_NUM 10
#define SLOT_MAX 10000000.0

double sensor_seed = 10101;

void s_exp(double *seed, double mean_t, double *inter_t) {
    long i;
    double x;
    if (mean_t == 0) {
        *inter_t = 0.0;
    }
	else {
        x = A * (*seed);
        i = (long)(x / B);
        *seed = x - B * i;
        x = *seed / B;
        *inter_t = -mean_t * log(x);
    }
}

int main(int argc, char *argv[]) {
	long long int i, j;
    double inter_arrival;
	double probability = 1.0 / DEVICE_NUM;
	int threshold = 150;
	long long int iaoi[DEVICE_NUM], accumulated_aoi[DEVICE_NUM], sum_device_aaoi[DEVICE_NUM];
	for (i=0; i<DEVICE_NUM; i++) {
		iaoi[i] = 1;
		accumulated_aoi[i] = 0;
		sum_device_aaoi[i] = 0;
	}
	
	for (j=0; j<SLOT_MAX; j++) {
		int device_number = -1;
		int send_num = 0;
		for (i=0; i<DEVICE_NUM; i++) {
			if (iaoi[i] >= threshold) {
		    	s_exp(&sensor_seed, 1.0, &inter_arrival);
				if (sensor_seed / B < probability) {
					device_number = i;
					send_num++;
				}
			}
			accumulated_aoi[i] += iaoi[i];
			iaoi[i]++;
		}
		if (send_num == 1) {
			iaoi[device_number] = 1;
			sum_device_aaoi[device_number] += accumulated_aoi[device_number];
			accumulated_aoi[device_number] = 0;
		}
	}
	
	for (i=0; i<DEVICE_NUM; i++)
		sum_device_aaoi[i] += accumulated_aoi[i];
	double network_aaoi = 0.0;
	for (i=0; i<DEVICE_NUM; i++) {
		printf("設備 %02d 的 AAOI：%f\n", i+1, (double)sum_device_aaoi[i] / SLOT_MAX);
		network_aaoi += (double)sum_device_aaoi[i]  / SLOT_MAX;
	}
	printf("系統的 AAOI：%f\n", network_aaoi / DEVICE_NUM);
	return 0;
}
