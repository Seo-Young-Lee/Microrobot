#include <cstdio>
#include <stdlib.h>
#include <string.h>
#include <ctime>
#include <thread>
#include <mutex>
#include <time.h>
#include "current_calc.h"
#include "modbus.h"
#include "functions.h"


int main() {
	
	//load LUTs
	LUT_init();

	//create modules

	md1.mb = modbus("127.0.0.1", 502);
	md1.num = 1;
	//module1.mb = modbus("192.168.0.253", 504);

	//set slave id
	md1.mb.modbus_set_slave_id(1);
	//connect with the server
	md1.mb.modbus_connect();

	thread t1(input_to_cur_ref);
	thread t2(modbus_communication);

	t1.join();
	t2.join();
	
	while (1) {}
	return 0;

}


