#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string.h>
#include "current_calc.h"

#include <time.h>
using namespace std;



void get_cur_ref(float* pos, float* B_ref, float* I_ref) {

	for (int i = 0; i < 8; i++) {
		I_ref[i] = clock();
	}
}

