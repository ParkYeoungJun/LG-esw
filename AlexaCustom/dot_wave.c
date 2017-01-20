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
	int i,a,b,c,d;
	uint8_t col_list[] = {0x80, 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFF};
	uint8_t row[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
	uint8_t col[8];
	uint16_t tmp;

	delay(1500);
	init();
	
	for(a=0;a<10;a++)
	{	
		for(b=0;b<8;b++)
			col[b] = col_list[rand()%9];
		for(c=0;c<6000;c++)
				for(i = 0 ; i < 8 ; ++i)
				{
						tmp = (row[i] << 8 ) | col[i];
						set16(tmp);
				}
	}
	init();
	return 0;
}
