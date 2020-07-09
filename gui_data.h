#pragma once
struct c2s_DATA {
	bool READY;
	bool FAULT;
	float B_act;
};

struct s2c_DATA {
	bool RUN;
	float pos_x;
	float pos_y;
	float pos_z;
	float Bref_x;
	float Bref_y;
	float Bref_z;
	float B_mag;
};

extern c2s_DATA c2s_data;
extern s2c_DATA s2c_data;