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
	uint8_t row = 0xFF;
	uint8_t col[] = {0x7F,0xBF,0xDF,0xEF,0xF7,0xFB,0xFD,0xFE};
	uint16_t tmp;

	init();

	while(1)
		for(i = 0 ; i < 8 ; ++i)
		{
			tmp =  (row << 8) | col[i];
			set16(tmp);
			delay(100);
		}
	return 0;
}
