#include "input_functions.h"

using namespace std;

bool userInputMode = false;
bool change_q_key = false;
bool change_w_key = false;
bool change_e_key = false;
bool change_r_key = false;
bool change_t_key = false;
bool change_y_key = false;
bool change_u_key = false;
bool change_a_key = false;
bool change_s_key = false;
bool change_d_key = false;
bool inputFinish = false;


void initialize_regs(c2s_DATA& my_regs) {
	my_regs.READY = false;
	my_regs.FAULT = 0.;
	my_regs.B_act = 0.;
}
void initialize_regs(s2c_DATA& my_regs) {
	my_regs.RUN = false;
	my_regs.pos_x = 0.;
	my_regs.pos_y = 0.;
	my_regs.pos_z = 0.;
	my_regs.Bref_x = 0.;
	my_regs.Bref_y = 0.;
	my_regs.Bref_z = 0.;
	my_regs.B_mag = 0;

}


bool* ToBinaryString(int value) {

	int bitCount = sizeof(float) * 8; // never rely on your knowledge of the size
	bool* result = new bool[bitCount]; // better not use string, to avoid ineffective string concatenation repeated in a loop

	// now, most important thing: (int)value would be "semantic" cast of the same
	// mathematical value (with possible rounding), something we don't want; so:
	int intValue = int(value);

	for (int bit = 0; bit < bitCount; ++bit) {
		int maskedValue = intValue & (1 << bit); // this is how shift and mask is done.
		if (maskedValue > 0)
			maskedValue = 1;
		// at this point, masked value is either int 0 or 1
		result[bitCount - bit - 1] = bool(maskedValue); // bits go right-to-left in usual Western Arabic-based notation
	}

	return result; // string from character array
}



void display_current(s2c_DATA* my_regs) {
	cout << endl;
	std::cout << "**********Current Input Register Display Mode**********" << std::endl;
	std::cout << "Pos x: " << my_regs->pos_x << std::endl;
	std::cout << "Pos y: " << my_regs->pos_y << std::endl;
	std::cout << "Pos z: " << my_regs->pos_z << std::endl;
	std::cout << "B_ref x: " << my_regs->Bref_x << std::endl;
	std::cout << "B_ref y: " << my_regs->Bref_y << std::endl;
	std::cout << "B_ref z: " << my_regs->Bref_z << std::endl;
	std::cout << "B_mag: " << my_regs->B_mag << std::endl;
	std::cout << "********Current Input Register Display Mode END********" << endl << endl;
}

void input_callback() {
	//Process q
	if (GetKeyState('Q') & 0x8000 && !change_q_key) {
		userInputMode = true;
		change_q_key = true;
		cout << "Pos X editing ..." << endl;

	}
	else if (GetKeyState('Q') & 0x8000 && change_q_key) {

	}
	else if (change_q_key && inputFinish) {
		change_q_key = false;
		inputFinish = false;
	}
	// Process w
	if (GetKeyState('W') & 0x8000 && !change_w_key) {
		userInputMode = true;
		change_w_key = true;
		cout << "Pos Y editing ..." << endl;

	}
	else if (GetKeyState('W') & 0x8000 && change_w_key) {

	}
	else if (change_w_key && inputFinish) {
		change_w_key = false;
		inputFinish = false;
	}
	// Process e
	if (GetKeyState('E') & 0x8000 && !change_e_key) {
		userInputMode = true;
		change_e_key = true;
		cout << "Pos Z editing ..." << endl;

	}
	else if (GetKeyState('E') & 0x8000 && change_e_key) {

	}
	else if (change_e_key && inputFinish) {
		change_e_key = false;
		inputFinish = false;
	}
	// Process r
	if (GetKeyState('R') & 0x8000 && !change_r_key) {
		userInputMode = true;
		change_r_key = true;
		cout << "B_ref X editing ..." << endl;

	}
	else if (GetKeyState('R') & 0x8000 && change_r_key) {

	}
	else if (change_r_key && inputFinish) {
		change_r_key = false;
		inputFinish = false;
	}
	// Process t
	if (GetKeyState('T') & 0x8000 && !change_t_key) {
		userInputMode = true;
		change_t_key = true;
		cout << "B_ref Y editing ..." << endl;

	}
	else if (GetKeyState('T') & 0x8000 && change_t_key) {

	}
	else if (change_t_key && inputFinish) {
		change_t_key = false;
		inputFinish = false;
	}
	// Process y
	if (GetKeyState('Y') & 0x8000 && !change_y_key) {
		userInputMode = true;
		change_y_key = true;
		cout << "B_ref Z editing ..." << endl;

	}
	else if (GetKeyState('Y') & 0x8000 && change_y_key) {

	}
	else if (change_y_key && inputFinish) {
		change_y_key = false;
		inputFinish = false;
	}
	// Process u
	if (GetKeyState('U') & 0x8000 && !change_u_key) {
		userInputMode = true;
		change_u_key = true;
		cout << "B_mag editing ..." << endl;

	}
	else if (GetKeyState('U') & 0x8000 && change_u_key) {

	}
	else if (change_u_key && inputFinish) {
		change_u_key = false;
		inputFinish = false;
	}

	if (userInputMode && GetKeyState('A') & 0x8000 && !change_a_key) {
		if (change_q_key) {
			s2c_data.pos_x += 0.1;
		}
		else if (change_w_key) {
			s2c_data.pos_y += 0.1;
		}
		else if (change_e_key) {
			s2c_data.pos_z += 0.1;
		}
		else if (change_r_key) {
			s2c_data.Bref_x += 0.1;
		}
		else if (change_t_key) {
			s2c_data.Bref_y += 0.1;
		}
		else if (change_y_key) {
			s2c_data.Bref_z += 0.1;
		}
		else if (change_u_key) {
			s2c_data.B_mag += 0.1;
		}
		inputFinish = true;
		userInputMode = false;
		cout << "+ 0.1" << endl;
	}

	if (userInputMode && GetKeyState('D') & 0x8000 && !change_d_key) {
		if (change_q_key) {
			s2c_data.pos_x -= 0.1;
		}
		else if (change_w_key) {
			s2c_data.pos_y -= 0.1;
		}
		else if (change_e_key) {
			s2c_data.pos_z -= 0.1;
		}
		else if (change_r_key) {
			s2c_data.Bref_x -= 0.1;
		}
		else if (change_t_key) {
			s2c_data.Bref_y -= 0.1;
		}
		else if (change_y_key) {
			s2c_data.Bref_z -= 0.1;
		}
		else if (change_u_key) {
			s2c_data.B_mag -= 0.1;
		}
		inputFinish = true;
		userInputMode = false;
		cout << "- 0.1" << endl;
	}

}



