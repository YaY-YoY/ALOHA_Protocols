#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define A 16807.0
#define B 2147483647.0

#define DEVICE_NUM 50
#define SLOT_MAX 1000000.0
#define MINI_NUM 4
                                                                                                                   
double sensor_seed = 10101;
double inter_arrival;

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
	long long int i, j, k;
	double probability = 0.078f * B;
	int threshold = 67;
	int iaoi[DEVICE_NUM], accumulated_aoi[DEVICE_NUM], sum_devices_aaoi[DEVICE_NUM];
	int successful_device_number;
	int send_num;
	for (i=0; i<DEVICE_NUM; i++) {
		iaoi[i] = 0;
		accumulated_aoi[i] = 0;
		sum_devices_aaoi[i] = 0;
	}
	
	
	for (i=0; i<SLOT_MAX; i++) {
	
		// AOI++
		for (j=0; j<DEVICE_NUM; j++) {
			iaoi[j]++;
			accumulated_aoi[j] += iaoi[j];
		}
		
		for (j=0; j<=MINI_NUM; j++) {
			
			// 歸零
			send_num = 0;
			     
			// 判斷傳送與否
			for (k=0; k<DEVICE_NUM; k++) {
				if (iaoi[k] >= threshold) {
					s_exp(&sensor_seed, 1.0, &inter_arrival);
					if ((int)sensor_seed <= probability) {
						successful_device = k;
						send_num++;
					}
				}
			}
			
			// 傳送成功，slot結束
			if (send_num == 1) {
				iaoi[successful_device] = 1;
				sum_devices_aaoi[successful_device] += accumulated_aoi[successful_device];
				accumulated_aoi[successful_device] = 0;
				break;
			}
		}
	}
	
	double network_aaoi = 0.0;
	for (i=0; i<DEVICE_NUM; i++) {
		// printf("設備 %02lld 的 AAOI：%f\n", i+1, (double)accumulated_aoi[i] / SLOT_MAX);
		sum_devices_aaoi[i] += accumulated_aoi[i]; //最後一筆資料 
		network_aaoi += (double)sum_devices_aaoi[i]  / SLOT_MAX;
	}
	
	printf("%d個設備, probability:%f, threshold:%d, %d個mini slot, AAOI:%f\n", DEVICE_NUM, probability/B, threshold, MINI_NUM, network_aaoi / DEVICE_NUM);
	return 0;
}
