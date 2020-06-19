#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"
#include "B_LUT_variables.h"
#include "current_calc.h"


using namespace std;

int LUT_index[8] = { 0,0,0,0,0,0,0,0 };
Matrix grid_weight(8, 1);
Matrix Act(3, 8);

void LUT_init() {
	string s1;
	string s2;
	string s3;
	string s4;
	string s5;
	string s6;
	string s7;
	string s8;
	grid_sq = GRID_NUM * GRID_NUM;
	grid_3sq = GRID_NUM * GRID_NUM * GRID_NUM;

	ifstream f1("./B_LUT_large/coil1_B_raw.csv");
	if (!f1.is_open()) {
		printf("Cannot open B_LUT1.CSV\n");
	}
	ifstream f2("./B_LUT_large/coil2_B_raw.csv");
	if (!f2.is_open()) {
		printf("Cannot open B_LUT2.CSV\n");
	}
	ifstream f3("./B_LUT_large/coil3_B_raw.csv");
	if (!f3.is_open()) {
		printf("Cannot open B_LUT3.CSV\n");
	}
	ifstream f4("./B_LUT_large/coil4_B_raw.csv");
	if (!f4.is_open()) {
		printf("Cannot open B_LUT4.CSV\n");
	}
	ifstream f5("./B_LUT_large/coil5_B_raw.csv");
	if (!f5.is_open()) {
		printf("Cannot open B_LUT5.CSV\n");
	}
	ifstream f6("./B_LUT_large/coil6_B_raw.csv");
	if (!f6.is_open()) {
		printf("Cannot open B_LUT6.CSV\n");
	}
	ifstream f7("./B_LUT_large/coil7_B_raw.csv");
	if (!f7.is_open()) {
		printf("Cannot open B_LUT7.CSV\n");
	}
	ifstream f8("./B_LUT_large/coil8_B_raw.csv");
	if (!f8.is_open()) {
		printf("Cannot open B_LUT8.CSV\n");
	}


	int i = 0, j = 0, k = 0, num;
	int inicheck = 0;
	double dummy;



	while (getline(f1, s1)) {
		istringstream iss(s1);
		if (!inicheck) {
			inicheck = 1;
			continue;
		}
		while (getline(iss, s1, ',')) {
			char *cstr = new char[s1.length() + 1];
			strcpy(cstr, s1.c_str());
			if (i == 0) {
				dummy = atof(cstr);
			}
			else if (i <= 3) {
				Grid_Index[j][i - 1][0] = atof(cstr);
			}
			else {
				B_LUT[j][i - 4][0] = atof(cstr);
			}
			delete[] cstr;
			if (++i == 7) break;
		}
		if (j == grid_3sq - 1) break;
		i = 0;
		j++;
	}
	i = 0, j = 0, inicheck = 0;

	while (getline(f2, s2)) {
		istringstream iss(s2);
		if (!inicheck) {
			inicheck = 1;
			continue;
		}
		while (getline(iss, s2, ',')) {
			char *cstr = new char[s2.length() + 1];
			strcpy(cstr, s2.c_str());
			if (i == 0) {
				dummy = atof(cstr);
			}
			else if (i <= 3) {
				Grid_Index[j][i - 1][1] = atof(cstr);
			}
			else {
				B_LUT[j][i - 4][1] = atof(cstr);
			}
			delete[] cstr;
			if (++i == 7) break;
		}
		if (j == grid_3sq - 1) break;
		i = 0;
		j++;
	}
	i = 0, j = 0, inicheck = 0;
	while (getline(f3, s3)) {
		istringstream iss(s3);
		if (!inicheck) {
			inicheck = 1;
			continue;
		}
		while (getline(iss, s3, ',')) {
			char *cstr = new char[s3.length() + 1];
			strcpy(cstr, s3.c_str());
			if (i == 0) {
				dummy = atof(cstr);
			}
			else if (i <= 3) {
				Grid_Index[j][i - 1][2] = atof(cstr);
			}
			else {
				B_LUT[j][i - 4][2] = atof(cstr);
			}
			delete[] cstr;
			if (++i == 7) break;
		}
		if (j == grid_3sq - 1) break;
		i = 0;
		j++;
	}
	i = 0, j = 0, inicheck = 0;
	while (getline(f4, s4)) {
		istringstream iss(s4);
		if (!inicheck) {
			inicheck = 1;
			continue;
		}
		while (getline(iss, s4, ',')) {
			char *cstr = new char[s4.length() + 1];
			strcpy(cstr, s4.c_str());
			if (i == 0) {
				dummy = atof(cstr);
			}
			else if (i <= 3) {
				Grid_Index[j][i - 1][3] = atof(cstr);
			}
			else {
				B_LUT[j][i - 4][3] = atof(cstr);
			}
			delete[] cstr;
			if (++i == 7) break;
		}
		if (j == grid_3sq - 1) break;
		i = 0;
		j++;
	}
	i = 0, j = 0, inicheck = 0;
	while (getline(f5, s5)) {
		istringstream iss(s5);
		if (!inicheck) {
			inicheck = 1;
			continue;
		}
		while (getline(iss, s5, ',')) {
			char *cstr = new char[s5.length() + 1];
			strcpy(cstr, s5.c_str());
			if (i == 0) {
				dummy = atof(cstr);
			}
			else if (i <= 3) {
				Grid_Index[j][i - 1][4] = atof(cstr);
			}
			else {
				B_LUT[j][i - 4][4] = atof(cstr);
			}
			delete[] cstr;
			if (++i == 7) break;
		}
		if (j == grid_3sq - 1) break;
		i = 0;
		j++;
	}
	i = 0, j = 0, inicheck = 0;
	while (getline(f6, s6)) {
		istringstream iss(s6);
		if (!inicheck) {
			inicheck = 1;
			continue;
		}
		while (getline(iss, s6, ',')) {
			char *cstr = new char[s6.length() + 1];
			strcpy(cstr, s6.c_str());
			if (i == 0) {
				dummy = atof(cstr);
			}
			else if (i <= 3) {
				Grid_Index[j][i - 1][5] = atof(cstr);
			}
			else {
				B_LUT[j][i - 4][5] = atof(cstr);
			}
			delete[] cstr;
			if (++i == 7) break;
		}
		if (j == grid_3sq - 1) break;
		i = 0;
		j++;
	}
	i = 0, j = 0, inicheck = 0;
	while (getline(f7, s7)) {
		istringstream iss(s7);
		if (!inicheck) {
			inicheck = 1;
			continue;
		}
		while (getline(iss, s7, ',')) {
			char *cstr = new char[s7.length() + 1];
			strcpy(cstr, s7.c_str());
			if (i == 0) {
				dummy = atof(cstr);
			}
			else if (i <= 3) {
				Grid_Index[j][i - 1][6] = atof(cstr);
			}
			else {
				B_LUT[j][i - 4][6] = atof(cstr);
			}
			delete[] cstr;
			if (++i == 7) break;
		}
		if (j == grid_3sq - 1) break;
		i = 0;
		j++;
	}
	i = 0, j = 0, inicheck = 0;
	while (getline(f8, s8)) {
		istringstream iss(s8);
		if (!inicheck) {
			inicheck = 1;
			continue;
		}
		while (getline(iss, s8, ',')) {
			char *cstr = new char[s8.length() + 1];
			strcpy(cstr, s8.c_str());
			if (i == 0) {
				dummy = atof(cstr);
			}
			else if (i <= 3) {
				Grid_Index[j][i - 1][7] = atof(cstr);
			}
			else {
				B_LUT[j][i - 4][7] = atof(cstr);
			}
			delete[] cstr;
			if (++i == 7) break;
		}
		if (j == grid_3sq - 1) break;
		i = 0;
		j++;
	}
	
	for (num = 0; num < 8; num++) {
		for (i = 0; i < 3; i++) {
			for (j = 0; j < grid_3sq; j++) {
				B_LUT[j][i][num] = B_LUT[j][i][num] * SCALE_T2mT / SCALE_CURRENT;
			}
		}
	}


	f1.close();
	f2.close();
	f3.close();
	f4.close();
	f5.close();
	f6.close();
	f7.close();
	f8.close();

}


void get_cur_ref(float* pos, float* B_ref, float* I_ref) {
	Matrix I_calc(8, 1);
	Matrix B_ref_M(3, 1);

	int i;
	for (i = 0; i < 3; i++) {
		B_ref_M(i, 0) = B_ref[i];
	}

	lenear_search(pos);
	get_LUT_inter();

	I_calc = B_ref_M / Act;

	for (i = 0; i < 8; i++) {
		I_ref[i] = I_calc(i, 0);
	}

}

void lenear_search(float* pos) {


	if (pos[0] > GRID_MAX){
		pos[0] = GRID_MAX - 0.0001;
	}
	else if (pos[0] < GRID_MIN){
		pos[0] = GRID_MIN + 0.0001;
	}

	if (pos[1] > GRID_MAX) {
		pos[1] = GRID_MAX - 0.0001;
	}
	else if (pos[2] < GRID_MIN) {
		pos[1] = GRID_MIN + 0.0001;
	}

	if (pos[2] > GRID_MAX) {
		pos[2] = GRID_MAX - 0.0001;
	}
	else if (pos[2] < GRID_MIN) {
		pos[2] = GRID_MIN + 0.0001;
	}
	
	int x_ceil = ceil((pos[0] - GRID_MIN) / GRID_SIZE) - 1;
	int y_ceil = ceil((pos[1] - GRID_MIN) / GRID_SIZE) - 1;
	int z_ceil = ceil((pos[2] - GRID_MIN) / GRID_SIZE) - 1;

	//z->y->x
	int x_num = (x_ceil) * (GRID_NUM*GRID_NUM);
	int y_num = (y_ceil) * (GRID_NUM);
	int z_num = (z_ceil);

	int base_index = x_num + y_num + z_num;//matlab case -1

	

	LUT_index[0] = base_index;
	LUT_index[1] = LUT_index[0] + 1;
	LUT_index[2] = base_index + GRID_NUM;
	LUT_index[3] = LUT_index[2] + 1;
	LUT_index[4] = base_index + grid_sq;
	LUT_index[5] = LUT_index[4] + 1;
	LUT_index[6] = base_index + GRID_NUM + grid_sq;
	LUT_index[7] = LUT_index[6] + 1;

	float x_weight = (pos[0] - GRID_MIN) / GRID_SIZE - x_ceil;
	float y_weight = (pos[1] - GRID_MIN) / GRID_SIZE - y_ceil;
	float z_weight = (pos[2] - GRID_MIN) / GRID_SIZE - z_ceil;
	float xd_weight = 1 - x_weight;
	float yd_weight = 1 - y_weight;
	float zd_weight = 1 - z_weight;

	

	grid_weight(0, 0) = xd_weight * yd_weight * zd_weight;
	grid_weight(1, 0) = xd_weight * yd_weight * z_weight;
	grid_weight(2, 0) = xd_weight * y_weight  * zd_weight;
	grid_weight(3, 0) = xd_weight * y_weight  * z_weight;
	grid_weight(4, 0) = x_weight  * yd_weight * zd_weight;
	grid_weight(5, 0) = x_weight  * yd_weight * z_weight;
	grid_weight(6, 0) = x_weight  * y_weight  * zd_weight;
	grid_weight(7, 0) = x_weight  * y_weight  * z_weight;






}



void get_LUT_inter() {
	int i, j,num;	Matrix B_temp(3, 8);
	Matrix B_inter_temp(3, 1);
	for (num = 0; num < 8; num++) {
		for (i = 0; i < 8; i++) {
			B_temp(0, i) = B_LUT[LUT_index[i]][0][num];
			B_temp(1, i) = B_LUT[LUT_index[i]][1][num];
			B_temp(2, i) = B_LUT[LUT_index[i]][2][num];

		}
		B_inter_temp = B_temp * grid_weight;
		

		for (i = 0; i < 3; i++) {
			Act(i, num) = B_inter_temp(i, 0);
		}
	}

}





