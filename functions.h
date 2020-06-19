#pragma once
#ifndef functions
#define functions

constexpr auto NUM_COIL_BITS = 5;
constexpr auto NUM_DISCRETE_INPUTS = 22;
constexpr auto NUM_INPUT_REGS = 12;
constexpr auto TYPES_INPUT_REGS = 6;
constexpr auto NUM_HOLD_REGS = 4;
constexpr auto TYPES_HOLD_REGS = 2;
constexpr auto NUM_SERVERS = 1;

constexpr auto CALC_DELAY = 200;
constexpr auto COMMUN_DELAY = 20;
constexpr auto RAND_RANGE = 101;

constexpr auto READY = 0;
constexpr auto RUN = 1;
constexpr auto FAULT = 2;
constexpr auto STOP = 3;


union float2int {
	uint16_t int_16[2];
	float f;
};
union coil_bits {
	bool c_bits_gen[NUM_COIL_BITS];
	struct {
		bool run;
		bool stop;
		bool reset;
		bool A_on;
		bool B_on;
	}c_bits_spec;
};
union discrete_inputs {
	bool d_inputs_gen[NUM_DISCRETE_INPUTS];
	struct {
		bool sys_ready;
		bool sys_run;
		bool sys_fault;
		bool commun;
		bool main_sw_on;
		bool aux_sw_on;
		bool sys_A_on;
		bool sys_B_on;
		bool sys_A_run;
		bool sys_B_run;
		bool em_sw_on;
		bool overheat;
		bool A_fault;
		bool B_fault;
		bool DCL_uv;
		bool DCL_ov;
		bool A_uv;
		bool A_ov;
		bool A_oc;
		bool B_uv;
		bool B_ov;
		bool B_oc;
	}d_inputs_spec;
};
union input_regs {
	float2int i_regs_gen[TYPES_INPUT_REGS];
	struct {
		float2int DLC_v;
		float2int A_v;
		float2int A_c;
		float2int B_v;
		float2int B_c;
		float2int temp;
	}i_regs_spec;
};
union holding_regs {
	float2int h_regs_gen[TYPES_HOLD_REGS];
	struct {
		float2int A_c_ref;
		float2int B_c_ref;
	}h_regs_spec;
};

struct Module {
	// Module number
	int num;
	// Modbus communication
	modbus mb;
	// DATA Protocol	
	coil_bits c_bits;
	discrete_inputs d_inputs;
	input_regs i_regs;
	holding_regs h_regs;
};
struct GUI {
	int gui_mode;
};
extern Module md1, md2, md3, md4;
extern GUI gui_md;

extern void input_to_cur_ref();
extern void modbus_communication();

#endif