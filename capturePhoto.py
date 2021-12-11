import picamera
import datetime

camera = picamera.PiCamera()
camera.hflip = True
camera.vflip = True

camera.resolution = (2592,1944)
camera.capture(str(datetime.datetime.now())+'.jpg')
