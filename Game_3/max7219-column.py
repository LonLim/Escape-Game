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
        bytes = "{0:04b}".format(int(c))
        print(bytes)
    with canvas(device) as draw:
        for index,item in enumerate(bytes):
                if(item !="0"):
                    print(index)
                    draw.line((2*index, 0, 2*index, device.height), fill="white")
                    draw.line((2*index+1, 0, 2*index+1, device.height), fill="white")
           
             
