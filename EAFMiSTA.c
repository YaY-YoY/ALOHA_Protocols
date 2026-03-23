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

struct Variable {
	int mini_slot_probability;
	int data_slot_probability;
	int threshold;
	int iaoi[DEVICE_NUM];
	int accumulated_aoi[DEVICE_NUM];
	bool ifsend[DEVICE_NUM];
	bool sent;
}device;

void initial() {
	device.mini_slot_probability = 0.02 * B;
	device.data_slot_probability = 0.385 * B;
	device.threshold = 150;
	int i;
	for (i=0; i<DEVICE_NUM; i++) {
		device.iaoi[i] = 1;
		device.accumulated_aoi[i] = 0;
	}
	device.sent = false;
}
void mini_slot_receive();
void data_slot_receive();

double inter_arrival;
void mini_slot_transmit() {
	long long int i;
	for (i=0; i<DEVICE_NUM; i++) {
		if (device.iaoi[i] >= device.threshold) {
			s_exp(&sensor_seed, 1.0, &inter_arrival);
			if ((int)sensor_seed <= device.mini_slot_probability)
				device.ifsend[i] = true;
			else
				device.ifsend[i] = false;
		}
		else
			device.ifsend[i] = false;
	}
	mini_slot_receive();
}

void mini_slot_receive() {
	long long int i;
	int device_number = -1;
	int send_num = 0;
	for (i=0; i<DEVICE_NUM; i++) {
		if (device.ifsend[i] == true) {
			device_number = i;
			send_num++;
		}
	}
	if (send_num == 1) { 
		/*for (i=0; i<DEVICE_NUM; i++) {
			device.accumulated_aoi[i] += device.iaoi[i];
			device.iaoi[i]++;
		}*/
		device.iaoi[device_number] = 1;
		device.sent = true;
	}
}

void data_slot_transmit() {
	long long int i;
	for (i=0; i<DEVICE_NUM; i++) {
		if (device.ifsend[i] == true && device.iaoi[i] >= device.threshold) {
			s_exp(&sensor_seed, 1.0, &inter_arrival);
			if ((int)sensor_seed <= device.data_slot_probability)
				device.ifsend[i] = true;
			else
				device.ifsend[i] = false;
		}
		else
			device.ifsend[i] = false;
	}
	data_slot_receive();
}

void data_slot_receive() {
	long long int i;
	int device_number[DEVICE_NUM];
	int send_num = 0;
	for (i=0; i<DEVICE_NUM; i++) {
		if (device.ifsend[i] == true) {
			device_number[send_num] = i;
			send_num++;
		}
	//	device.accumulated_aoi[i] += device.iaoi[i];
	//	device.iaoi[i]++;
	}
	if (send_num == 1) {
		device.iaoi[device_number[0]] = 1;
	}
	else {
		int old_num = device_number[0];
		for (i=1; i<send_num; i++) {
			int test_num = device_number[i];
			if(device.iaoi[test_num] > device.iaoi[old_num])
				old_num = test_num;
		}
		device.iaoi[old_num] = 1;
	}
}

int main(int argc, char *argv[]) {
	initial();
	long long int i;
	int j;
	for (i=0; i<SLOT_MAX; i++) {
		for (j=0; j<DEVICE_NUM; j++) {
			device.accumulated_aoi[j] += device.iaoi[j];
			device.iaoi[j]++;
		}
		for (j=0; j<2; j++)
			if(device.sent == false)
				mini_slot_transmit();
		if(device.sent == false)
			data_slot_transmit();
		device.sent = false; 
		
	/*	for (j=0; j<DEVICE_NUM; j++) {
			printf("%d:%d ", j+1, device.accumulated_aoi[j]);
		}
		printf("\n"); */
		
	} 
	for (i=0; i<DEVICE_NUM; i++)
		device.accumulated_aoi[i] += device.iaoi[i];
	double sum_accumulated_aoi = 0.0;
	for (i=0; i<DEVICE_NUM; i++) {
		printf("設備 %02lld 的 AAOI：%f\n", i+1, (double)device.accumulated_aoi[i] / SLOT_MAX);
		sum_accumulated_aoi += (double)device.accumulated_aoi[i]  / SLOT_MAX;
	}
	printf("系統的 AAOI：%f\n", sum_accumulated_aoi / DEVICE_NUM);
	return 0;
}
