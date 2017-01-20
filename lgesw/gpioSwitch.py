import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
GPIO.setup(17, GPIO.OUT)
GPIO.setup(27, GPIO.OUT)
GPIO.setup(22, GPIO.OUT)
GPIO.setup(23, GPIO.IN)

try:
	while True :
		GPIO.output(17,False)
		GPIO.output(27,False)
		GPIO.output(22,False)
		if GPIO.input(23)==0:
			GPIO.output(17,True)
			GPIO.output(27,True)
			GPIO.output(22,True)
			time.sleep(1)

except KeyboardInterrupt:
	GPIO.cleanup()
