from luma.core.interface.serial import spi, noop
from luma.core.render import canvas
from luma.led_matrix.device import max7219
import time
import sys

serial = spi(port=0, device=0, gpio=noop())
device = max7219(serial,rotate=2)



str = ""
while True:
    c = sys.stdin.read(1) # reads one byte at a time, similar to getchar()
    if(c.isdigit()):
        bytes = "{0:b}".format(int(c))
        print(bytes)
    for idx, item in enumerate(bytes):
        with canvas(device) as draw:
            if(item !="0"):
                draw.line((idx, 0, idx, device.height), fill="white")
                draw.line((idx+1, 0, idx+1, device.height), fill="white")
                time.sleep(0.3)
