from flask import Flask, render_template
from flask_ask import Ask, statement, question, session
import RPi.GPIO as GPIO
import logging
import os
from random import randint

win = 50 

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

@ask.intent("AgreeIntent")

def OK():
	text = render_template('ok')
	pid = os.fork();
	if pid == 0 :
		pid =os.execl('./dot_wave', 'dot_wave', '')
	return question(text)

@ask.intent("NumberIntent", convert={'number':int})

def answer(number):

	pid = os.fork();
	if pid == 0 :
		pid =os.execl('./dot_wave', 'dot_wave', '')

	if number < 0 or number > 100:
		text = render_template('wrong')
		return question(text)
	elif number < win:
		text = render_template('bigger')
		return question(text)
	elif number > win:
		text = render_template('lower')
		return question(text)
	elif number == win:
		text = render_template('win')
		return statement(text)

	return question(text)

@ask.intent("giveupIntent")

def giveup():
	text = render_template('giveup', number = win)
	pid = os.fork();
	if pid == 0 :
		pid =os.execl('./dot_wave', 'dot_wave', '')

	return statement(text)


if __name__ == '__main__':
	app.run(debug=True)
