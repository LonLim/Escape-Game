from luma.core.interface.serial import spi, noop
from luma.core.render import canvas
from luma.led_matrix.device import max7219
import time

serial = spi(port=0, device=0, gpio=noop())
device = max7219(serial)


while True:
    
 with canvas(device) as draw:
    draw.line((0, 0, 0, device.height), fill="white")
