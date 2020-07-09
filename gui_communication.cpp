#include "gui_communication.h"
#include <mutex>

WSADATA wsaData;
SOCKET hServSock;
struct sockaddr_in hServAddr, hClntAddr;
int slen = sizeof(hServAddr);
const char* IPaddress = "127.0.0.1";
const char* portNumber = "502";
char flagInput;
clock_t last, current;
clock_t last2, current2;
mutex m;

char c2s_buf[MAX] = "\0";
char s2c_buf[MAX] = "\0";

void gui_input() {

	last = clock();
	while (1) {
		current = clock();
		if (current < last) last = 0; // code for clock overflow
		if (current - last > INPUT_INTERVAL) {
			last = current;
			m.lock();
			display_current(&s2c_data);
			m.unlock();
		}
		input_callback();
	}
}
void commun_init() {
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) /* Load Winsock 2.0 DLL */
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

	memset(&hServAddr, 0, sizeof(hServAddr));
	hServAddr.sin_family = AF_INET;
	hServAddr.sin_addr.s_addr = inet_addr(IPaddress);
	hServAddr.sin_port = htons(atoi(portNumber));

	if (::bind(hServSock, (struct sockaddr *)&hServAddr, sizeof(hServAddr)) == SOCKET_ERROR)
	{
		printf("bind() error!\n");
		WSACleanup();
		closesocket(hServSock);
		exit(1);
	}
	printf("bind() ok..\n");

}
void gui_commun() {

	last2 = clock();
	while (1) {
		current2 = clock();
		if (current2 < last2) last2 = 0; // code for clock overflow
		if (current2 - last2 > COMMUN_INTERVAL) {
			last2 = current2;
			//m.lock();
			// receive READY & FAULT data from client
			recvfrom(hServSock, c2s_buf, MAX, 0, (struct sockaddr *) &hServAddr, &slen);
			memcpy(&c2s_data, c2s_buf, sizeof(c2s_data));
			printf("%d\n", c2s_data.READY);
			printf("%d\n", c2s_data.FAULT);

			// send RUN & pos(x,y,z) & B_ref(x,y,z) data to client
			memcpy(s2c_buf, &s2c_data, MAX);
			if (c2s_data.READY && !c2s_data.FAULT) {
				s2c_data.RUN = true;
			}
			else {
				s2c_data.RUN = false;
			}
			sendto(hServSock, s2c_buf, MAX, 0, (struct sockaddr *) &hServAddr, slen);

			// receive B_act data from client
			recvfrom(hServSock, c2s_buf, MAX, 0, (struct sockaddr *) &hServAddr, &slen);
			memcpy(&c2s_data, c2s_buf, sizeof(c2s_data));
			printf("%f\n", c2s_data.B_act);
			//m.unlock();
		}
	}
}

