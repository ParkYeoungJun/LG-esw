import os
import time
import datetime
from picamera import PiCamera

camera = PiCamera()
cur_dir = os.getcwd()

def get_file_name():
	return datetime.datetime.now().strftime("%Y-%m-%d_%H.%M.%S.h264")

def record_video():
	fileName = "%s %s" % (cur_dir, get_file_name())

	camera.start_preview()
	camera.start_recording(fileName)

	time.sleep(5)

def finish_video():
	camera.stop_recording()
	camera.stop_preview()

record_video()
finish_video()


