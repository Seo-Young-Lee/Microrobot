#pragma once
#pragma comment(lib, "Ws2_32.lib")
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <time.h>
#include <stdio.h>
#include <WinSock.h>
#include <Windows.h>
#include "functions.h"
#include "gui_data.h"
#include "current_calc.h"

#define MAX 512
#define GUI_COMMUN_INTERVAL 1000

using namespace std;

void commun_init();
void gui_commun();
void gui_commun_calc();
void initialize_regs(c2s_DATA& );
void initialize_regs(s2c_DATA& );


