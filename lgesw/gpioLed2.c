#include<stdio.h>
#include<wiringPi.h>

#define LED1 5
#define LED2 6
#define LED3 13
#define LED4 19
#define LED5 26

#define EXIT_SUCC 0
#define EXIT_FAIL 1

int led[5] = {5,6,13,19,26};

int main(void){

	int i,j;
	wiringPiSetupGpio();



	
	for(i = 0 ; i < 5 ; ++i)
		pinMode(led[i], OUTPUT);


	while(1){
	
	for(j = 0 ; j < 5 ; ++j){
	for(i = 0 ; i < 5 ; ++i)
		digitalWrite(led[i], 1);

	delay(500);

	for(i = 4 ; i >= 0 ; --i)
		digitalWrite(led[i], 0);

	delay(500);
	}

	for(i = 0 ; i < 5 ; ++i)
	{

		digitalWrite(led[i], 1);
		delay(100);
		digitalWrite(led[i], 0);
	}	

	for(i = 4 ; i >=0 ; --i)
	{
		digitalWrite(led[i], 1);
		delay(100);
		digitalWrite(led[i], 0);

	}
	}

	return 0;
}
