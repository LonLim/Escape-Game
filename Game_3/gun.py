# USAGE
# python barcode_scanner_video.py

# import the necessary packages
from imutils.video import VideoStream
from pyzbar import pyzbar
import argparse
import datetime
import imutils
import time
import cv2
from luma.core.interface.serial import spi, noop
from luma.core.render import canvas
from luma.led_matrix.device import max7219
import time
import sys

serial = spi(port=0, device=0, gpio=noop())
device = max7219(serial,rotate=2)
# construct the argument parser and parse the arguments
ap = argparse.ArgumentParser()
ap.add_argument("-o", "--output", type=str, default="barcodes.csv",
	help="path to output CSV file containing barcodes")
args = vars(ap.parse_args())

# initialize the video stream and allow the camera sensor to warm up
print("[INFO] starting video stream...")
# vs = VideoStream(src=0).start()
vs = VideoStream(usePiCamera=True).start()
time.sleep(2.0)

# open the output CSV file for writing and initialize the set of
# barcodes found thus far
csv = open(args["output"], "w")
found = set()
text = ""
# loop over the frames from the video stream
while True:
	# grab the frame from the threaded video stream and resize it to
	# change frame to grayscale
	# have a maximum width of 400 pixels
	frame = vs.read()
	frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
	frame = imutils.resize(frame, width=400,inter= cv2.INTER_CUBIC)
	
	# find the barcodes in the frame and decode each of the barcodes
	barcodes = pyzbar.decode(frame)

	# loop over the detected barcodes
	for barcode in barcodes:

		# the barcode data is a bytes object so if we want to draw it
		# on our output image we need to convert it to a string first
		barcodeData = barcode.data.decode("utf-8")
		barcodeType = barcode.type
		text = "{} ({})".format(barcodeData, barcodeType)
		text= text[0]
    		if(text.isdigit()):
     			bytes = "{0:04b}".format(int(c))
     			print(bytes)
    		with canvas(device) as draw:
     			for index,item in enumerate(bytes):
     				if(item !="0"):
       				print(index)
     				draw.line((2*index, 0, 2*index, device.height), fill="white")
     				draw.line((2*index+1, 0, 2*index+1, device.height), fill="white")
	

# close the output CSV file do a bit of cleanup
print("[INFO] cleaning up...")
csv.close()
#cv2.destroyAllWindows()
vs.stop()
