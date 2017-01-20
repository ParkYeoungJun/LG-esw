import RPi.GPIO as GPIO
import time
import os
import sys

GPIO.setmode(GPIO.BCM)
GPIO.setup(17, GPIO.OUT)
GPIO.setup(27, GPIO.OUT)
GPIO.setup(22, GPIO.OUT)
GPIO.setup(23, GPIO.IN)

try:
	while True :
		if GPIO.input(23)==0:
			os.system('shutdown')

except KeyboardInterrupt:
	GPIO.cleanup()
