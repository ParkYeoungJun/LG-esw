#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<wiringPi.h>
#include<stdint.h>
#include<unistd.h>
#include<fcntl.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>

#define BUF_SIZE 128

#define SDATA 6
#define STR_CLK 13
#define SHR_CLK 19
#define SHR_CLEAR 26

int i;

uint8_t a_[] = {0x04, 0x2A, 0x2A, 0x2A, 0x1E};
uint8_t b_[] = {0x7E, 0x0A, 0x12, 0x12, 0x0C};
uint8_t	c_[] = {0x1C, 0x22, 0x22, 0x22, 0x14};
uint8_t d_[] = {0x0C, 0x12, 0x12, 0x0A, 0x7E};
uint8_t	e_[] = {0x1C, 0x2A, 0x2A, 0x2A, 0x18};
uint8_t	f_[] = {0x10, 0x3E, 0x50, 0x40, 0x20};
uint8_t	g_[] = {0x04, 0x12, 0x2A, 0x2A, 0x3C};
uint8_t	h_[] = {0x7E, 0x08, 0x10, 0x10, 0x0E};
uint8_t	i_[] = {0x5E};
uint8_t	j_[] = {0x04, 0x02, 0x22, 0xBC};
uint8_t k_[] = {0x7E, 0x08, 0x14, 0x22};
uint8_t	l_[] = {0x42, 0x7E, 0x02};
uint8_t	m_[] = {0x3E, 0x20, 0x18, 0x20, 0x1E};
uint8_t	n_[] = {0x3E, 0x10, 0x20, 0x20, 0x1E};
uint8_t	o_[] = {0x1C, 0x22, 0x22, 0x22, 0x1C};
uint8_t	p_[] = {0x3E, 0x28, 0x28, 0x28, 0x10};
uint8_t q_[] = {0x18, 0x24, 0x24, 0x18, 0x3E};
uint8_t r_[] = {0x3E, 0x10, 0x20, 0x20, 0x10};
uint8_t s_[] = {0x12, 0x2A, 0x2A, 0x2A, 0x04};
uint8_t t_[] = {0x10, 0x3E, 0x12, 0x04};
uint8_t u_[] = {0x3C, 0x02, 0x02, 0x04, 0x3E};
uint8_t v_[] = {0x38, 0x04, 0x02, 0x04, 0x38};
uint8_t w_[] = {0x3C, 0x02, 0x0C, 0x02, 0x3C};
uint8_t x_[] = {0x22, 0x14, 0x08, 0x14, 0x22};
uint8_t y_[] = {0x30, 0x0A, 0x0A, 0x0A, 0x3C};
uint8_t z_[] = {0x22, 0x26, 0x2A, 0x32, 0x22};

uint8_t col[] = {0x7F, 0xBF, 0xDF, 0xEF, 0xF7, 0xFB, 0xFD, 0xFE};
uint16_t tmp;


void allclear(void);

void init(void)
{   
	if(wiringPiSetupGpio() == -1){
		fprintf(stderr, "wiringPiSetupGpio() error\n");
		exit(1);
	}
	pinMode(SDATA, OUTPUT);
	pinMode(STR_CLK, OUTPUT);
	pinMode(SHR_CLK, OUTPUT);
	pinMode(SHR_CLEAR, OUTPUT);
	allclear();
}

void allclear(void)
{
	digitalWrite(SHR_CLEAR, 0);
	digitalWrite(SHR_CLEAR, 1);
	digitalWrite(STR_CLK, 0);
	digitalWrite(STR_CLK, 1);
}

void set16(uint16_t value)
{
	int i;

	for(i = 0 ; i < 16 ; ++i)
	{
		int mask = 1 << i;
		if((value & mask) == 0){
			digitalWrite(SDATA, 0);
		}
		else
		{
			digitalWrite(SDATA, 1);
		}

		digitalWrite(SHR_CLK, 0);
		digitalWrite(SHR_CLK, 1);
	}
	digitalWrite(STR_CLK, 0);
	digitalWrite(STR_CLK, 1);
}



int main(int argc, char *argv[])
{
	struct sockaddr_in client_addr;
	int client_fd, len;

	char senddata[BUF_SIZE];

	if(argc != 4)
	{
		printf("input error \n");
		exit(0);
	}



	//	client_addr.sin_addr.s_addr = inet_addr("203.253.23.60");
	client_addr.sin_addr.s_addr = inet_addr(argv[1]);
	client_addr.sin_family = PF_INET;
	client_addr.sin_port = htons(atoi(argv[2]));

	if((client_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("socket creation error \n");
		exit(0);
	}

	if(connect(client_fd, (struct sockaddr *)&client_addr, sizeof(client_addr)) == -1)
	{
		printf("connect error \n");
		exit(0);
	}


	write(client_fd, argv[3], strlen(argv[3]));

	while(1)
	{
		for(i = 0 ; i < 8 ; ++i)
		{
			tmp = (a_[i] << 8 | col[i]);
			set16(tmp);
		}
	}

}
