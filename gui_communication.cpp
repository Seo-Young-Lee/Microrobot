#include "gui_communication.h"

WSADATA wsaData;
SOCKET hServSock;
struct sockaddr_in servAddr;
int slen = sizeof(servAddr);
const char* IPaddress = "127.0.0.1";
const char* portNumber = "502";
clock_t last, current;
int data_send_cnt = 0;

char c2s_buf[MAX] = "\0";
char s2c_buf[MAX] = "\0";


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

void commun_init() {


	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		fprintf(stderr, "WSAStartup() failed");
		exit(1);
	}

	if ((hServSock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
	{
		fprintf(stderr, "socket() failed");
		WSACleanup();
		exit(1);
	}

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(IPaddress);
	servAddr.sin_port = htons(atoi(portNumber));

}
void gui_commun() {

	last = clock();
	while (1) {
		current = clock();
		if (current < last) last = 0;
		if (current - last > GUI_COMMUN_INTERVAL) {
			last = current;

			//m.lock();
			// send READY & FAULT data to server
			data_send_cnt++;
			printf("data sent to server (data # %d).\n", data_send_cnt);
			memcpy(c2s_buf, &c2s_data, MAX);
			sendto(hServSock, c2s_buf, MAX, 0, (struct sockaddr *) &servAddr, slen);
			
			// receive RUN & pos(x,y,z) & B_ref(x,y,z) data from server
			recvfrom(hServSock, s2c_buf, MAX, 0, (struct sockaddr *) &servAddr, &slen);
			memcpy(&s2c_data, s2c_buf, sizeof(s2c_data));
			pos_global[0] = s2c_data.pos_x;		printf("Pos X : %f\n", s2c_data.pos_x);
			pos_global[1] = s2c_data.pos_y;		printf("Pos Y : %f\n", s2c_data.pos_y);
			pos_global[2] = s2c_data.pos_z;		printf("Pos Z : %f\n", s2c_data.pos_z);
			B_ref_global[0] = s2c_data.Bref_x;	printf("B_ref X : %f\n", s2c_data.Bref_x);
			B_ref_global[1] = s2c_data.Bref_y;	printf("B_ref Y : %f\n", s2c_data.Bref_y);
			B_ref_global[2] = s2c_data.Bref_z;	printf("B_ref Z : %f\n", s2c_data.Bref_z);
			B_mag_global= s2c_data.B_mag;		printf("B_mag : %f\n", s2c_data.B_mag);
			/* TODO : consider the case when Bref x, y, z is unit vector */

			// send B_act data to server
			c2s_data.B_act = clock(); // TO BE CHANGED
			memcpy(c2s_buf, &c2s_data, MAX);
			sendto(hServSock, c2s_buf, MAX, 0, (struct sockaddr *) &servAddr, slen);
			//m.unlock();
		}
		
	}
}

void gui_commun_calc() {
	last = clock();
	while (1) {
		current = clock();
		if (current < last) last = 0;
		if (current - last > GUI_COMMUN_INTERVAL) {
			last = current;

			//m.lock();
			// send READY & FAULT data to server
			data_send_cnt++;
			printf("data sent to server (data # %d).\n", data_send_cnt);
			memcpy(c2s_buf, &c2s_data, MAX);
			sendto(hServSock, c2s_buf, MAX, 0, (struct sockaddr *) &servAddr, slen);

			// receive RUN & pos(x,y,z) & B_ref(x,y,z) data from server
			recvfrom(hServSock, s2c_buf, MAX, 0, (struct sockaddr *) &servAddr, &slen);
			memcpy(&s2c_data, s2c_buf, sizeof(s2c_data));
			pos_global[0] = s2c_data.pos_x;		printf("Pos X : %f\n", s2c_data.pos_x);
			pos_global[1] = s2c_data.pos_y;		printf("Pos Y : %f\n", s2c_data.pos_y);
			pos_global[2] = s2c_data.pos_z;		printf("Pos Z : %f\n", s2c_data.pos_z);
			B_ref_global[0] = s2c_data.Bref_x;	printf("B_ref X : %f\n", s2c_data.Bref_x);
			B_ref_global[1] = s2c_data.Bref_y;	printf("B_ref Y : %f\n", s2c_data.Bref_y);
			B_ref_global[2] = s2c_data.Bref_z;	printf("B_ref Z : %f\n", s2c_data.Bref_z);
			B_mag_global = s2c_data.B_mag;		printf("B_mag : %f\n", s2c_data.B_mag);
			/* TODO : consider the case when Bref x, y, z is unit vector */

			get_cur_ref(pos_global, B_ref_global, Current_ref_global);

			// send B_act data to server
			c2s_data.B_act = clock(); // TO BE CHANGED
			memcpy(c2s_buf, &c2s_data, MAX);
			sendto(hServSock, c2s_buf, MAX, 0, (struct sockaddr *) &servAddr, slen);
			//m.unlock();
		}

	}
}