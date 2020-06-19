#pragma once
#ifndef B_LUT_variables
#define B_LUT_variables

#define GRID_NUM 11
#define GRID_MIN -0.05 //CSV �������� ����
#define GRID_MAX 0.05 //CSV �������� ����
#define GRID_SIZE 0.01 //CSV �������� ����
#define SCALE_CURRENT 50 //CSV �������� ����
#define SCALE_T2mT 1000


extern int grid_sq;
extern int grid_3sq;

extern float B_LUT[GRID_NUM * GRID_NUM * GRID_NUM][3][8];
extern int Grid_Index[GRID_NUM * GRID_NUM * GRID_NUM][3][8];




#endif // B_LUT_variables