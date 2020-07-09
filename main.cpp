/* Micro-robot server_test_GUI_ver0.3  (07.08 update) */
/* UDP server */
/* server test code for GUI communication */
/* UDP communication with main program(client) */

#include "gui_communication.h"
#include <thread>
#include<iostream>

c2s_DATA c2s_data;
s2c_DATA s2c_data;

int main() {
	
	// GUI data Initialize
	cout << "This is temporal version of modbus tcp server module." << endl;
	cout << "Initializing s2c & c2s data" << endl;
	initialize_regs(s2c_data);
	initialize_regs(c2s_data);
	commun_init();

	// multithread (thread1:GUI Input, thread2: GUI UDP communication)
	thread t1(gui_input);
	thread t2(gui_commun);

	t1.join();
	t2.join();
	
	return 0;

}
