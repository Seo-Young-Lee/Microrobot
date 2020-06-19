#pragma once
#ifndef current_calc
#define current_calc



extern void LUT_init();
void lenear_search(float* pos);
void get_LUT_inter();

extern void get_cur_ref(float* pos, float* B_ref, float* I_ref);
extern void input_to_cur_ref();


#endif // current_calc