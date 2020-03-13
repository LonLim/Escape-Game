from luma.core.interface.serial import spi, noop
from luma.core.render import canvas
from luma.led_matrix.device import max7219
import time
import sys

serial = spi(port=0, device=0, gpio=noop())
device = max7219(serial,rotate=2)



len = 0
while True:
    c = sys.stdin.read(1) # reads one byte at a time, similar to getchar()
    if(c.isdigit()):
        bytes = "{0:b}".format(int(c))
        print(bytes)
    with canvas(device) as draw:
        for index,item in enumerate(bytes):
            draw.line((index, 0, index, device.height*bytes[index]), fill="white")
            draw.line((index+1, 0, index+1, device.height*bytes[index]), fill="white")
           
             
