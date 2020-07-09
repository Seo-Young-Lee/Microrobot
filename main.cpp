/* Micro-robot server_test_GUI_ver0.3  (07.08 update) */
/* UDP client */
/* client test code for GUI communication */
/* MODBUS TCP/IP communication with 4-machines server & UDP (local) communication with GUI server */

#include <thread>
#include <iostream>
#include <mutex>
#include "current_calc.h"
#include "modbus.h"
#include "functions.h"
#include "gui_communication.h"

Module md1, md2, md3, md4;
std::mutex m;
float pos_global[3] = { 0.,0.,0. };
float B_ref_global[3] = { 0.,0.,0. };
float B_mag_global = 0.;
float Current_ref_global[8] = { 0., 0., 0., 0., 0., 0., 0., 0. };
c2s_DATA c2s_data;
s2c_DATA s2c_data;

int main() {

	//create MODBUS module for communication with 4-machines
	md1.mb = modbus("127.0.0.1", 502); // temporarily make single module and use local IP (for test with easyMODBUS server program) 
	md1.num = 1;
	md1.mb.modbus_set_slave_id(1);
	//connect with the 4-machines server
	md1.mb.modbus_connect();

	// initialize data & initiate UDP communication with GUI server
	cout << "Initializing s2c & c2s data" << endl;
	initialize_regs(s2c_data);
	initialize_regs(c2s_data);
	commun_init();

	//send READY to GUI server(for test only: TO BE CHANGED)
	c2s_data.READY = true;
	c2s_data.FAULT = false;

	// multithread (thread1:(GUI) UDP communication & current calculation, thread2: (4-machines) MODBUS TCP/IP communication)
	thread t1(gui_commun_calc);
	thread t2(modbus_communication);

	t1.join();
	t2.join();

	return 0;
}
	
	




