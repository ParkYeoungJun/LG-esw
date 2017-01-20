#include<stdio.h>
#include<stdlib.h>
#include<wiringPi.h>
#include<stdint.h>

#define SDATA	6
#define STR_CLK 13
#define SHR_CLK 19
#define SHR_CLEAR 26

void allclear(void);

void init(void)
{
	if(wiringPiSetupGpio() == -1){
		fprintf(stderr, "wiringPiSetupGpio() erorr\n");
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

	for(i = 0 ; i < 16 ; ++i){
		int mask = 1 << i;
		if((value & mask) == 0){
			digitalWrite(SDATA, 0);
		}
		else{
			digitalWrite(SDATA, 1);
		}
		digitalWrite(SHR_CLK, 0);
		digitalWrite(SHR_CLK, 1);
	}
	digitalWrite(STR_CLK, 0);
	digitalWrite(STR_CLK, 1);
}

int main(void)
{
	int i;
	int j;
	uint8_t row[] = {0xC0,0xC0,0xC0,0xC0,0xFF,0xFF,0xFF,0xFF};
	uint8_t col[] = {0x00,0x00,0x00,0x00,0x3F,0x3F,0x3F,0x3F}; 
	uint16_t tmp;

	uint8_t row_t[] = {0xFF,0xFF,0x18,0x18,0x18,0x18,0x18,0x18};
	uint8_t col_t[] = {0xFC,0xFC,0x00,0x00,0x00,0x00,0x00,0x00};

	uint8_t row_k[] = {0x63,0x66,0x6C,0x78,0x78,0x6C,0x66,0x63};
	uint8_t col_k[] = {0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7F};

	init();

	while(1){
		for(j = 0 ; j < 100000 ; ++j)
		for(i = 0 ; i < 8 ; ++i)
		{
			tmp =  (row[i] << 8) | col[i];
			set16(tmp);
		}

		for(j = 0 ; j < 100000 ; ++j)
		for(i = 0 ; i < 8 ; ++i)
		{
			tmp =  (row_t[i] << 8) | col_t[i];
			set16(tmp);
		}

		for(j = 0 ; j <100000 ; ++j)
			for(i = 0 ; i < 8 ; ++i)
			{
				tmp = (row_k[i] << 8) | col_k[i];
				set16(tmp);
			}
		
	}

	return 0;
}
