#include<stdio.h>
#include<bcm2835.h>

#define PIN RPI_BPLUS_GPIO_J8_40 

int main(int argc, char** argv){

	int i;
	int pin_num =atoi(argv[1]);
	int loop = atoi(argv[2]);

	if(!bcm2835_init())
		return 1;

	bcm2835_gpio_fsel(pin_num, BCM2835_GPIO_FSEL_OUTP);

	if(loop == -1)
		while(1){
			bcm2835_gpio_write(pin_num, HIGH);
			bcm2835_delay(1000);
			bcm2835_gpio_write(pin_num, LOW);
			bcm2835_delay(1000);
		}
	else
	{
		for(i = 0 ; i < loop ; ++i)
		{
			bcm2835_gpio_write(pin_num, HIGH);
			bcm2835_delay(1000);
			bcm2835_gpio_write(pin_num, LOW);
			bcm2835_delay(1000);
		}
	}

	bcm2835_close();

	return 0;
}
