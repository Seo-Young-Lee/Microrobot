#pragma once
#pragma comment(lib, "Ws2_32.lib")
#include <stdlib.h>
#include <string.h>
#include "input_functions.h"
#include <iostream>
#include <time.h>
#include <stdio.h>
#include <WinSock.h>

#define MAX 512
#define COMMUN_INTERVAL 1000
#define INPUT_INTERVAL 2000

using namespace std;
void gui_input();
void commun_init();
void gui_commun();
