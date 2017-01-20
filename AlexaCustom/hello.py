from flask import Flask, render_template
from flask_ask import Ask, statement, question, session
import os
import RPi.GPIO as GPIO
import logging

light = 12

app = Flask(__name__)
ask = Ask(app, '/')

logging.getLogger("flask_ask").setLevel(logging.DEBUG)

@ask.launch

def start_alexa(): 

	welcome_msg = render_template('welcome')

	pid = os.fork();
	if pid == 0 :
		pid =os.execl('./dot_wave', 'dot_wave', '')

	return question(welcome_msg)

@ask.intent("HongIntent")

def Hong():
	text = render_template('hong')
	pid = os.fork();
	if pid == 0 :
		pid =os.execl('./dot_wave', 'dot_wave', '')

	return question(text)

@ask.intent("onLEDIntent")

def onLED():
	text = render_template('onled')

	pid = os.fork();
	if pid == 0 :
		pid =os.execl('./dot_wave', 'dot_wave', '')

	GPIO.output(light, GPIO.HIGH)

	return question(text)

@ask.intent("offLEDIntent")

def offLED():
	text = render_template('offled')

	pid = os.fork();
	if pid == 0 :
		pid =os.execl('./dot_wave', 'dot_wave', '')

	GPIO.output(light, GPIO.LOW)

	return question(text)

@ask.intent("smileIntent")

def smile_():
	text = render_template('smile')

	pid = os.fork();
	if pid == 0 :
		pid =os.execl('./dot_smile', 'dot_smile', '')

	return question(text)

@ask.intent("byeIntent")

def byebye():
	text = render_template('byebye')

	pid = os.fork();
	if pid == 0 :
		pid =os.execl('./dot_wave', 'dot_wave', '')

	GPIO.output(light,GPIO.LOW)

	return statement(text)

if __name__ == '__main__':
	GPIO.setwarnings(False)
	GPIO.cleanup()
	GPIO.setmode(GPIO.BCM)
	GPIO.setup(light, GPIO.OUT)
	GPIO.output(light, GPIO.LOW)
	app.run(debug=True)
