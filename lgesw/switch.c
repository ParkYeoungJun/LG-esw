#include<stdio.h>
#include<stdlib.h>
#include<wiringPi.h>

#define SW 23
#define LED1 17
#define LED2 27
#define LED3 22
#define EXIT_SUCC 0
#define EXIT_FAIL 1



int main(void)
{
	int i ;
	int dr;

	if(wiringPiSetupGpio() == -1)
		return EXIT_FAIL;

	setbuf(stdout, NULL);

	pinMode(SW, INPUT);
	pinMode(LED1, OUTPUT);
	pinMode(LED2, OUTPUT);
	pinMode(LED3, OUTPUT);

	while(1){
		delay(10);

		if((dr = digitalRead(SW)) == 1){
			printf("%d:-----\r", dr);
		}
		else{
			printf("%d:--  -- \n" , dr);

			for(i = 0 ; i < 10 ; ++i){
				printf("LED ON \n");
				
				digitalWrite(LED1, HIGH);
				digitalWrite(LED2, HIGH);
				digitalWrite(LED3, HIGH);
				delay(50);

				printf("LED OFF \n");
				digitalWrite(LED1, LOW);
				digitalWrite(LED2, LOW);
				digitalWrite(LED3, LOW);
				delay(50);
			}
		}
	}

	return EXIT_SUCC;
}
