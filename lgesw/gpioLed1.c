#include<stdio.h>
#include<wiringPi.h>

#define LED1 12 

#define EXIT_SUCC 0
#define EXIT_FAIL 1

int
main(void){
	if(wiringPiSetupGpio() == -1)
		return EXIT_FAIL;

	pinMode(LED1, OUTPUT);


	int i = 0;

	while(i < 10){
		digitalWrite(LED1, 1);
	
		delay(50);

		digitalWrite(LED1, 0);

		delay(50);

		++i;
	}

	return EXIT_SUCC;

}

