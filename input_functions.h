#pragma once

#include <bitset>
#include <string>
#include <iostream>
#include "gui_data.h"
#include "Windows.h"

void initialize_regs(c2s_DATA&);
void initialize_regs(s2c_DATA&);
bool* ToBinaryString(int);
void display_current(s2c_DATA*);
void input_callback();