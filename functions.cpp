#include "functions.h"


void read_com_module(Module*);
void sys_mode_decision();
void write_com_module(Module* md);

int sys_mode;

void input_to_cur_ref() {
	clock_t start_time = clock();
	while (1) {
		if (clock() > start_time + CALC_DELAY) {

			//current reference calculator
			//input : global_pos, global_b_ref
			//output : global_current_ref
			m.lock();
			get_cur_ref(pos_global, B_ref_global, Current_ref_global);
			m.unlock();			// reset time delay
			start_time = clock();
		}
	}
}


void modbus_communication() {
	clock_t start_time = clock();
	bool fault_flag = false;
	while (1) {
		if (clock() > start_time + COMMUN_DELAY) {

			//from GUI
			/*
			// make random pos, B_ref input(for test only)
			srand((unsigned int)time(NULL));
			for (int i = 0; i < 3; i++) {
				pos_temp[i] = (float)(rand() % RAND_RANGE - 50) / 1000;
			}
			for (int i = 0; i < 3; i++) {
				B_ref_temp[i] = (rand() % 11) - 5;
			}
			*pos_global = *pos_temp;
			*B_ref_global = *B_ref_temp;

			*/

		

			/* read discrete inputs and input regs from modules */
			read_com_module(&md1);
			//read_com_module(&md2);
			//read_com_module(&md3);
			//read_com_module(&md4);

			/*system mode managing (fault, save data, ...)*/
			sys_mode_decision();
			cout << "SYS_MODE: "<< sys_mode << endl;

			/* write coil bits and holding regs to modules */
			write_com_module(&md1);
			//write_com_module(&md2);
			//write_com_module(&md3);
			//write_com_module(&md4);

			// reset time delay
			start_time = clock();
		}

	}
}


void read_com_module(Module* md) {

	// read discrete inputs(read status & fault of modules)  function 0x02
	bool read_discrete_inputs[NUM_DISCRETE_INPUTS];
	md->mb.modbus_read_input_bits(0, NUM_DISCRETE_INPUTS, read_discrete_inputs);
	memcpy(md->d_inputs.d_inputs_gen, read_discrete_inputs, sizeof read_discrete_inputs);

	for (int j = 0; j < NUM_DISCRETE_INPUTS; j++) {
		printf("module %d : read discrete input[ %d ]: %d \n", md->num, j, md->d_inputs.d_inputs_gen[j]);
	}

	// read input registers             function 0x04
	uint16_t read_input_regs[NUM_INPUT_REGS];
	md->mb.modbus_read_input_registers(0, NUM_INPUT_REGS, read_input_regs);

	for (int j = 0; j < NUM_INPUT_REGS; j++) {
		printf("read input reg[ %d ]: %d \n", j, read_input_regs[j]);
	}

}


void sys_mode_decision() {

	if (md1.d_inputs.d_inputs_spec.sys_fault) {
		sys_mode = FAULT;
		c2s_data.READY = false;
		c2s_data.FAULT = true;
	}
	else if (s2c_data.RUN  && md1.d_inputs.d_inputs_spec.sys_run ) {
		sys_mode = RUN;
	}
	else {
		sys_mode = STOP;
		//c2s_data.READY = false;
	}
}

void write_com_module(Module* md) {


	if (sys_mode == RUN) {
		// make coil bits DATA
		md->c_bits.c_bits_spec.run = true;
		md->c_bits.c_bits_spec.stop = false;
		md->c_bits.c_bits_spec.reset = false;
		md->c_bits.c_bits_spec.A_on = true;
		md->c_bits.c_bits_spec.B_on = true;

		// make holding regs DATA
		md->h_regs.h_regs_spec.A_c_ref.f = Current_ref_global[2 * md->num - 2];
		md->h_regs.h_regs_spec.B_c_ref.f = Current_ref_global[2 * md->num - 1];

	}
	else if (sys_mode == FAULT) {
		if (getchar() == 'r') {		//reset each module when reset is typed
			// make coil bits DATA
			md->c_bits.c_bits_spec.run = false;
			md->c_bits.c_bits_spec.stop = false;
			md->c_bits.c_bits_spec.reset = true;
			md->c_bits.c_bits_spec.A_on = true;
			md->c_bits.c_bits_spec.B_on = true;
		}
		else {	// stop operation of each module
			// make coil bits DATA
			md->c_bits.c_bits_spec.run = false;
			md->c_bits.c_bits_spec.stop = true;
			md->c_bits.c_bits_spec.reset = false;
			md->c_bits.c_bits_spec.A_on = false;
			md->c_bits.c_bits_spec.B_on = false;
		}
		// make holding regs DATA
		md->h_regs.h_regs_spec.A_c_ref.f = 0;
		md->h_regs.h_regs_spec.B_c_ref.f = 0;
	}
	else { // sys_mode == READY or sys_mode == STOP
		// make coil bits DATA
		md->c_bits.c_bits_spec.run = false;
		md->c_bits.c_bits_spec.stop = false;
		md->c_bits.c_bits_spec.reset = false;
		md->c_bits.c_bits_spec.A_on = false;
		md->c_bits.c_bits_spec.B_on = false;
		// make holding regs DATA
		md->h_regs.h_regs_spec.A_c_ref.f = 0;
		md->h_regs.h_regs_spec.B_c_ref.f = 0;
	}

	// write multiple coils             function 0x0F
	md->mb.modbus_write_coils(0, NUM_COIL_BITS, md->c_bits.c_bits_gen);
	// write multiple holding regs (send current reference to modules)              function 0x10
	md->mb.modbus_write_registers(0, NUM_HOLD_REGS, md->h_regs.h_regs_gen->int_16);

}