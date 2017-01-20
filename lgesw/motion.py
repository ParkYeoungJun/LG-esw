import numpy as np
import picamera
import picamera.array

class DetectMotion(picamera.array.PiMotionAnalysis):
	def analyse(self, a):
		a = np.sqrt(
				np.square(a['x'].astype(np.float))+
				np.square(a['y'].astype(np.float))
				).clip(0, 255).astype(np.uint8)
		if(a > 60).sum() > 10:
			print('Motion detected!')

with picamera.PiCamera() as camera:
	with DetectMotion(camera) as output:
		camera.resolution = (640, 480)
		camera.start_recording(
				'/dev/null', format='h264', motion_output=output)
		camera.wait_recording(30)
		camera.stop_recording()
