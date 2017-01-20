#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<fcntl.h>
#include<unistd.h>
#include<wiringPi.h>
#include<stdint.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#define BUF_LEN 128

#define SDATA 6
#define STR_CLK 13 
#define SHR_CLK 19
#define SHR_CLEAR 26

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
	char buffer[BUF_LEN];

	struct sockaddr_in server_addr, client_addr;
	char temp[20];

	int server_fd, client_fd;

	int len, msg_size;
	char test[20];

	if(argc != 2)
	{
		printf("input error \n");
		exit(0);
	}

	memset(&server_addr, 0x00, sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	//	server_addr.sin_addr.s_addr = inet_addr("203.253.23.60");
	//	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(atoi(argv[1]));

	if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		printf("server : can not open socket\n");
		exit(0);
	}

	if(bind(server_fd, (struct sockaddr *) &server_addr, sizeof(server_addr))< 0)
	{
		printf("Server : can not bind local address \n");
		exit(0);
	}

	if(listen(server_fd, 5) < 0)
	{
		printf("Server : can not listen connect \n");
		exit(0);
	}

	memset(buffer, 0x00, sizeof(buffer));
	len = sizeof(client_addr);
	printf("[PORT] : %d \n", atoi(argv[1]));
	printf("Server : waiting connection request \n");

	int i;
	init();

		while(1)
		{
			for(i = 0 ; i < 8 ; ++i)
			{
				tmp = (a_[i] << 8 | col[i]);
				set16(tmp);
			}
		}

	while(1)
	{
		client_fd = accept(server_fd, (struct sockaddr *)&client_addr, (socklen_t *)&len);

		if(client_fd < 0)
		{
			printf("Server: accept failed \n");
			exit(0);
		}

		inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, temp, sizeof(temp));


		printf("Server : %s client connected.\n", temp);

		/*
		   msg_size = recv(client_fd, (char *)buffer, BUF_LEN, 0);

		   send(client_fd, (char *)buffer, msg_size, 0);

		   close(client_fd);

		   printf("Server : %s client closed. \n", temp);
		 */
		read(client_fd,buffer,30);

		buffer[30] = 0;

		printf("get message [%s]\n", buffer);


		while(1)
		{
			for(i = 0 ; i < 8 ; ++i)
			{
				tmp = (a_[i] << 8 | col[i]);
				set16(tmp);
			}
		}
	}

	close(server_fd);

	return 0;
}

